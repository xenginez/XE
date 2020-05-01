#include "Buffer.h"

USING_XE

IMPLEMENT_META( Buffer )

Buffer::Buffer()
	:_pos( 0 )
{

}

Buffer::Buffer( Buffer && _Right )
: _pos( _Right._pos ), _data( std::move( _Right._data ) )
{
}

Buffer::Buffer( const Buffer & _Right )
	:_pos( _Right._data.size() ), _data( _Right._data )
{
}

Buffer::Buffer( XE::memory_view _Right )
	:_pos( _Right.size() ), _data( _Right.data(), _Right.data() + _Right.size() )
{

}

Buffer::~Buffer()
{

}

Buffer & Buffer::operator=( Buffer && _Right )
{
	if( this != std::addressof( _Right ) )
	{
		_data = std::move( _Right._data );
		_pos = _data.size();
	}

	return *this;
}

Buffer & Buffer::operator=( const Buffer & _Right )
{
	if( this != std::addressof( _Right ) )
	{
		_data = _Right._data;
		_pos = _data.size();
	}

	return *this;
}

XE::uint64 XE::Buffer::pos() const
{
	return _pos;
}

void XE::Buffer::seek( XE::uint64 val )
{
	if( val > _data.size() )
	{
		_pos = _data.size();
	}
	else
	{
		_pos = val;
	}
}

void XE::Buffer::resize( XE::uint64 val )
{
	if( _data.size() < val )
	{
		_data.resize( val );
		_pos = val;
	}
}

void XE::Buffer::read( std::string & val )
{
	XE::uint64 size = 0;

	read( size );
	val.resize( size );

	read( val.data(), size );
}

void XE::Buffer::wirte( const std::string & val )
{
	wirte( val.size() );
	wirte( val.c_str(), val.size() );
}

void XE::Buffer::read( char * ptr, XE::uint64 size )
{
	std::memcpy( &( *( _data.begin() + _pos ) ), ptr, size );
	_pos += size;
}

void XE::Buffer::wirte( const char * ptr, XE::uint64 size )
{
	_data.insert( _data.begin() + _pos, ptr, ptr + size );
	_pos += size;
}

XE::memory_view Buffer::view() const
{
	return XE::memory_view( _data.data(), _data.size() );
}
