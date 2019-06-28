#include "ObjectAlloc.h"

#include "Alloc.h"

#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_priority_queue.h>

USING_XE

class ObjectGroup
{
public:
	ObjectGroup( XE::uint64 size )
		:ObjectSize( size ), Mems( size * 32 )
	{
		for( XE::uint64 i = 0; i < 32; ++i )
		{
			Frees.push( i );
		}
	}

	ObjectGroup( ObjectGroup && val )
		:ObjectSize( val.ObjectSize ), Mems( std::move( val.Mems ) ), Frees( std::move( val.Frees ) )
	{

	}

public:
	void * alloc( XE::uint64 count )
	{
		XE::int64 i = 0;

		if( Frees.try_pop( i ) )
		{
			return &( Mems[i * ObjectSize] );
		}

		capacity();

		if( Frees.try_pop( i ) )
		{
			return &( Mems[i * ObjectSize] );
		}

		return nullptr;
	}

	void free( void * ptr )
	{
		XE::uint64 i = ( XE::uint64 )ptr - ( XE::uint64 )( &( Mems[0] ) );

		Frees.push( i / ObjectSize );
	}

	void capacity()
	{
		std::lock_guard<std::mutex> lock( ResizeMutex );

		XE::uint64 m_size = Mems.size();
		Mems.resize( m_size * 2 );
		for( XE::uint64 j = 0; j < m_size / ObjectSize; ++j )
		{
			Frees.push( j + ( m_size / ObjectSize ) );
		}
	}

private:
	XE::uint64 ObjectSize;
	std::mutex ResizeMutex;
	tbb::concurrent_vector<XE::uint8> Mems;
	tbb::concurrent_priority_queue<XE::int64> Frees;
};

struct XE::ObjectAlloc::Private
{
	tbb::concurrent_hash_map< XE::uint64, ObjectGroup > Groups;
};

XE::ObjectAlloc::ObjectAlloc()
	:_p( new Private )
{
}

XE::ObjectAlloc::~ObjectAlloc()
{
	delete _p;
}

void * XE::ObjectAlloc::allocate( XE::uint64 hash, XE::uint64 size, XE::uint64 count )
{
	size = ALIGNED64( size );

	tbb::concurrent_hash_map< XE::uint64, ObjectGroup >::accessor accessor;

	if( This()->_p->Groups.find( accessor, hash ) )
	{
		return accessor->second.alloc( count );
	}
	else if( This()->_p->Groups.insert( accessor, { hash, ObjectGroup( size ) } ) )
	{
		return accessor->second.alloc( count );
	}

	return nullptr;
}

void XE::ObjectAlloc::deallocate( void * ptr, XE::uint64 hash )
{
	tbb::concurrent_hash_map< XE::uint64, ObjectGroup >::accessor accessor;
	if( This()->_p->Groups.find( accessor, hash ) )
	{
		return accessor->second.free( ptr );
	}
}

void XE::ObjectAlloc::clear()
{
	This()->_p->Groups.clear();
}
