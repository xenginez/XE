#include "Alloc.h"

USING_XE

void * XE::Alloc::Allocate( XE::uint64 size )
{
	return ::malloc( size );
}

void * XE::Alloc::Reallocate( void * ptr, XE::uint64 size )
{
	return ::realloc( ptr, size );
}

void XE::Alloc::Deallocate( void * ptr )
{
	::free( ptr );
}
