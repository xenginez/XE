#include "ObjectAlloc.h"

#include "Allocator.hpp"

#include <tbb/concurrent_hash_map.h>
#include "Base/concurrent_list.hpp"

USING_XE

class Page
{
public:
	Page()
		:Size( 0 ), Bit( nullptr ), Beg( nullptr ), End( nullptr )
	{

	}

	Page( Page && val )
		:Size( val.Size ), Bit( val.Bit ), Beg( val.Beg ), End( val.End )
	{

	}

	Page( const Page & val )
		:Size( val.Size )
	{
		XE::uint64 count = ( val.End - val.Beg ) / val.Size;
		XE::uint64 bit_count = count / 32 + 1;
		Bit = static_cast< XE::uint8 * >( Alloc::Allocate( val.End - val.Bit ) );
		Beg = Bit + bit_count;
		End = Bit + Size * count + bit_count;
		std::memset( Bit, 0, Size * count + bit_count );
	}

	Page( XE::uint64 size, XE::uint64 count )
		:Size( size )
	{
		XE::uint64 bit_count = count / 32 + 1;
		Bit = static_cast< XE::uint8 * >( Alloc::Allocate( size * count + bit_count ) );
		Beg = Bit + bit_count;
		End = Bit + size * count + bit_count;
		std::memset( Bit, 0, size * count + bit_count );
	}

	~Page()
	{
		Alloc::Deallocate( Bit );
	}

public:
	XE::uint8 * Allocate()
	{
		XE::uint64 count = ( ( End - Beg ) / Size ) / 32 + 1;
		std::atomic<XE::uint32> * bp = reinterpret_cast< std::atomic<XE::uint32> * >( Bit );

		for( int i = 0; i < count; ++i )
		{
			XE::uint32 value = bp[i].load();
			if( value != 0XFFFFFFFF )
			{
				XE::uint32 index = GetFirstBitZero( value );
				if( bp[i].compare_exchange_weak( value, value | ( 1 << index ) ) )
				{
					SetBit( i * 32 + index, true );
					return Beg + ( i * 32 + index ) * Size;
				}
				index = GetFirstBitZero( value );
				if( bp[i].compare_exchange_weak( value, value | ( 1 << index ) ) )
				{
					SetBit( i * 32 + index, true );
					return Beg + ( i * 32 + index ) * Size;
				}
				index = GetFirstBitZero( value );
				if( bp[i].compare_exchange_weak( value, value | ( 1 << index ) ) )
				{
					SetBit( i * 32 + index, true );
					return Beg + ( i * 32 + index ) * Size;
				}
			}
		}

		return nullptr;
	}

	void Deallocate( void * p )
	{
		SetBit( ( static_cast< XE::uint8 * >( p ) - Beg ) / Size, false );
	}

public:
	bool Empty() const
	{
		XE::uint64 count = ( ( End - Beg ) / Size ) / 32 + 1;
		std::atomic<XE::uint32> * bp = reinterpret_cast< std::atomic<XE::uint32> * >( Bit );

		for( int i = 0; i < count; ++i )
		{
			if( bp[i].load() != 0 )
			{
				return false;
			}
		}

		return true;
	}

	XE::uint64 Count() const
	{
		return ( End - Beg ) / Size;
	}

	bool IsFrom( void * p ) const
	{
		return p >= Beg && p < End;
	}

private:
	XE_INLINE XE::uint32 GetFirstBitZero( XE::uint32 mask )
	{
		XE::uint32 index = mask;
		index = ( index - 1 ) & ~index;
		index = index & 0x55555555 + ( index >> 1 ) & 0x55555555;
		index = index & 0x33333333 + ( index >> 2 ) & 0x33333333;
		index = index & 0x0F0F0F0F + ( index >> 4 ) & 0x0F0F0F0F;
		index = index & 0xFF + ( index & 0xFF00 >> 8 ) + ( index & 0xFF0000 >> 16 ) + ( index & 0xFF000000 >> 24 );
		return index;
	}

	XE_INLINE void SetBit( XE::uint64 index, bool val )
	{
		val ?
			Bit[index / sizeof( XE::uint8 )] |= ( 1 << ( index % sizeof( XE::uint8 ) ) ) :
			Bit[index / sizeof( XE::uint8 )] &= ~( 1 << ( index % sizeof( XE::uint8 ) ) );
	}

public:
	XE::uint64 Size;
	XE::uint8 * Bit;
	XE::uint8 * Beg;
	XE::uint8 * End;
};

class Block
{
public:
	Block( XE::uint64 size )
		:Size( size ), Pages( Page( size, KBYTE( 4 ) / size ) )
	{

	}

	Block( Block && val )
		:Size( val.Size ), Pages( val.Pages )
	{

	}

public:
	void * Allocate()
	{
		for( auto it = Pages.begin(); it != Pages.end(); ++it )
		{
			XE::uint8 * p = it->Allocate();

			if( p )
			{
				return p;
			}
		}

		return Pages.emplace_back( Page( Size, KBYTE( 4 ) / Size ) )->Allocate();
	}

	void Deallocate( void * p )
	{
		for( auto it = Pages.begin(); it != Pages.end(); ++it )
		{
			if( it->IsFrom( p ) )
			{
				it->Deallocate( p );
			}
		}
	}

	void ShrinkToFit()
	{
		if( Pages.size() > 1 )
		{
			for( auto it = Pages.rbegin(); it != Pages.rend(); ++it )
			{
				if( it->Empty() )
				{
					Pages.erase( it.base() );
					return;
				}
			}
		}
	}

private:
	XE::uint64 Size;
	XE::concurrent_list<Page, XE::Allocator<Page>> Pages;
};

struct XE::ObjectAlloc::Private
{
	tbb::concurrent_hash_map< XE::uint64, Block > Blocks;
};

XE::ObjectAlloc::ObjectAlloc()
	:_p( new Private )
{
}

XE::ObjectAlloc::~ObjectAlloc()
{
	delete _p;
}

void * XE::ObjectAlloc::Allocate( XE::uint64 hash_code, XE::uint64 size, XE::uint64 count )
{
	size = ALIGNED64( size );

	tbb::concurrent_hash_map< XE::uint64, Block >::accessor accessor;

	if( Instance()->_p->Blocks.find( accessor, hash_code ) )
	{
		return accessor->second.Allocate();
	}
	else if( Instance()->_p->Blocks.insert( accessor, { hash_code, Block( size ) } ) )
	{
		return accessor->second.Allocate();
	}

	return nullptr;
}

void XE::ObjectAlloc::Deallocate( void * ptr, XE::uint64 hash_code )
{
	tbb::concurrent_hash_map< XE::uint64, Block >::accessor accessor;
	if( Instance()->_p->Blocks.find( accessor, hash_code ) )
	{
		return accessor->second.Deallocate( ptr );
	}
}

void XE::ObjectAlloc::Clear()
{
	Instance()->_p->Blocks.clear();
}

void XE::ObjectAlloc::ShrinkToFit()
{
	for( auto it = Instance()->_p->Blocks.begin(); it != Instance()->_p->Blocks.end(); ++it )
	{
		it->second.ShrinkToFit();
	}
}
