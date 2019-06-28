#include "ObjectAlloc.h"

#include "Alloc.h"

#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_priority_queue.h>

USING_XE

struct PMemGroup
{
	PMemGroup( XE::uint64 size )
		:Size( size ), Mems( size * 32 )
	{
		for( XE::uint64 i = 0; i < 32; ++i )
		{
			Frees.push( i );
		}
	}

	PMemGroup( const PMemGroup & val )
		:Size( val.Size ), Mems( val.Mems ), Frees( val.Frees )
	{

	}

	void * alloc()
	{
		XE::int64 i = 0;

		if( Frees.try_pop( i ) )
		{
			return &( Mems[i * Size] );
		}

		ResizeMutex.lock();
		try
		{
			XE::uint64 m_size = Mems.size();
			Mems.resize( m_size * 2 );
			for( XE::uint64 j = 0; j < m_size / Size; ++j )
			{
				Frees.push( j + ( m_size / Size ) );
			}
		}
		catch( ... )
		{
			ResizeMutex.unlock();
		}
		ResizeMutex.unlock();

		if( Frees.try_pop( i ) )
		{
			return &( Mems[i * Size] );
		}

		return nullptr;
	}

	void free( void * ptr )
	{
		XE::uint64 i = ( XE::uint64 )ptr - ( XE::uint64 )( &( Mems[0] ) );

		Frees.push( i / Size );
	}

	XE::uint64 Size;
	std::mutex ResizeMutex;
	tbb::concurrent_vector<XE::uint8> Mems;
	tbb::concurrent_priority_queue<XE::int64> Frees;
};

struct XE::ObjectAlloc::Private
{
	tbb::concurrent_hash_map< XE::uint64, PMemGroup > Groups;
};

XE::ObjectAlloc::ObjectAlloc()
	:_p( new Private )
{
	reset();
}

XE::ObjectAlloc::~ObjectAlloc()
{
	clear();

	delete _p;
}

void * XE::ObjectAlloc::allocate( XE::uint64 size )
{
	size = ALIGNED64( size );

	tbb::concurrent_hash_map< XE::uint64, PMemGroup >::accessor accessor;

	if( This()->_p->Groups.find( accessor, size ) )
	{
		return accessor->second.alloc();
	}
	else if( This()->_p->Groups.insert( accessor, { size, PMemGroup( size ) } ) )
	{
		return accessor->second.alloc();
	}

	return nullptr;
}

void XE::ObjectAlloc::deallocate( void * ptr, XE::uint64 size )
{
	size = ALIGNED64( size );

	tbb::concurrent_hash_map< XE::uint64, PMemGroup >::accessor accessor;
	if( This()->_p->Groups.find( accessor, size ) )
	{
		return accessor->second.free( ptr );
	}
}

void XE::ObjectAlloc::clear()
{
	This()->_p->Groups.clear();
}

void XE::ObjectAlloc::reset()
{
	clear();

	This()->_p->Groups.insert( std::make_pair( 8, PMemGroup( 8 ) ) );
	This()->_p->Groups.insert( std::make_pair( 16, PMemGroup( 16 ) ) );
	This()->_p->Groups.insert( std::make_pair( 32, PMemGroup( 32 ) ) );
	This()->_p->Groups.insert( std::make_pair( 64, PMemGroup( 64 ) ) );
	This()->_p->Groups.insert( std::make_pair( 80, PMemGroup( 80 ) ) );
	This()->_p->Groups.insert( std::make_pair( 112, PMemGroup( 112 ) ) );
	This()->_p->Groups.insert( std::make_pair( 176, PMemGroup( 176 ) ) );
	This()->_p->Groups.insert( std::make_pair( 256, PMemGroup( 256 ) ) );
}
