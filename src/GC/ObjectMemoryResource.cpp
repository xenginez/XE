#include "ObjectMemoryResource.h"

#include "PageCache.h"
#include "ThreadCache.h"
#include "CentralCache.h"

struct XE::ObjectMemoryResource::Private
{
	Private()
		:_Central( &_Page )
	{

	}

	PageCache _Page;
	CentralCache _Central;
};

XE::ObjectMemoryResource::ObjectMemoryResource()
	:_p( new Private )
{

}

XE::ObjectMemoryResource::~ObjectMemoryResource() noexcept
{
	delete _p;
}

void * XE::ObjectMemoryResource::do_allocate( size_t _Bytes, size_t _Align )
{
	std::size_t size = ( _Bytes + _Align - 1 ) & ~( _Align - 1 );

	return _p->_Central.Allocate( size );
}

void XE::ObjectMemoryResource::do_deallocate( void * _Ptr, size_t _Bytes, size_t _Align )
{
	_p->_Central.Deallocate( _Ptr );
}

bool XE::ObjectMemoryResource::do_is_equal( const std::pmr::memory_resource & _That ) const noexcept
{
	return &_That == this;
}
