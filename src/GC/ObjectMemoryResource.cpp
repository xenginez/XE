#include "ObjectMemoryResource.h"

#include <tbb/scalable_allocator.h>

void * XE::ObjectMemoryResource::do_allocate( size_t _Bytes, size_t _Align )
{
	std::size_t size = ( _Bytes + _Align - 1 ) & ~( _Align - 1 );

	return scalable_malloc( size );
}

void XE::ObjectMemoryResource::do_deallocate( void * _Ptr, size_t _Bytes, size_t _Align )
{
	scalable_free( _Ptr );
}

bool XE::ObjectMemoryResource::do_is_equal( const std::pmr::memory_resource & _That ) const noexcept
{
	return &_That == this;
}
