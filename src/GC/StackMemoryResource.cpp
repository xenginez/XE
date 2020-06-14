#include "StackMemoryResource.h"

XE::StackMemoryResource::StackMemoryResource()
	:_Beg( nullptr ), _Ptr( nullptr ), _Space( 0 )
{
	_Beg = std::pmr::get_default_resource()->allocate( ONE_MBYTE * 2 );
	_Ptr = _Beg;
	_Space = ONE_MBYTE * 2;
}

XE::StackMemoryResource::~StackMemoryResource() noexcept
{
	std::pmr::get_default_resource()->deallocate( _Beg, ONE_MBYTE * 2 );
}

void * XE::StackMemoryResource::do_allocate( size_t _Bytes, size_t _Align )
{
	if( auto p = std::align( _Align, _Bytes, _Ptr, _Space ) )
	{
		if( _Space < _Bytes )
		{
			return nullptr;
		}

		_Space -= _Bytes;
		_Ptr = static_cast< char * >( _Ptr ) + _Bytes;

		return p;
	}

	return nullptr;
}

void XE::StackMemoryResource::do_deallocate( void * _Ptr, size_t _Bytes, size_t _Align )
{
	XE_ASSERT( static_cast< char * >( this->_Ptr ) - _Bytes == _Ptr );

	this->_Space += _Bytes;
	this->_Ptr = static_cast< char * >( this->_Ptr ) + _Bytes;
}

bool XE::StackMemoryResource::do_is_equal( const std::pmr::memory_resource & _That ) const noexcept
{
	return this == &_That;
}