#include "Alloc.h"

#include <tbb/scalable_allocator.h>

USING_XE

void * XE::Alloc::allocate( XE::uint64 size )
{
	return scalable_malloc( size );
}

void * XE::Alloc::reallocate( void * ptr, XE::uint64 size )
{
	return scalable_realloc( ptr, size );
}

void XE::Alloc::deallocate( void * ptr )
{
	scalable_free( ptr );
}
