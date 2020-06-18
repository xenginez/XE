#include "Buffer.h"



IMPLEMENT_META( XE::Buffer )

XE::Buffer::Buffer()
	:_ReadPos( 0 ), _WirtePos( 0 )
{
}

XE::Buffer::Buffer( XE::Buffer && _Right )
	: _ReadPos( _Right._ReadPos ), _WirtePos( _Right._WirtePos ), _Data( std::move( _Right._Data ) )
{
}

XE::Buffer::Buffer( const XE::Buffer & _Right )
	: _ReadPos( _Right._ReadPos ), _WirtePos( _Right._WirtePos ), _Data( _Right._Data )
{
}

XE::Buffer::Buffer( XE::memory_view _Right )
	: _ReadPos( 0 ), _WirtePos( _Right.size() ), _Data( _Right.data(), _Right.data() + _Right.size() )
{

}

XE::Buffer::~Buffer()
{

}

XE::Buffer & XE::Buffer::operator=( Buffer && _Right )
{
	if( this != std::addressof( _Right ) )
	{
		_Data = std::move( _Right._Data );
		_ReadPos = _Right._ReadPos;
		_WirtePos = _Right._WirtePos;
	}

	return *this;
}

XE::Buffer & XE::Buffer::operator=( const Buffer & _Right )
{
	if( this != std::addressof( _Right ) )
	{
		_Data = _Right._Data;
		_ReadPos = _Right._ReadPos;
		_WirtePos = _Right._WirtePos;
	}

	return *this;
}

XE::uint64 XE::Buffer::ReadPos() const
{
	return _ReadPos;
}

XE::uint64 XE::Buffer::WirtePos() const
{
	return _WirtePos;
}

void XE::Buffer::Seek( XE::uint64 val )
{
	if( val > _Data.size() )
	{
		_ReadPos = _Data.size();
	}
	else
	{
		_ReadPos = val;
	}
}

void XE::Buffer::Resize( XE::uint64 val )
{
	if( val > _Data.size() )
	{
		_Data.resize( val );
	}
	else
	{
		_WirtePos = val;
	}
}

void XE::Buffer::Read( char * ptr, XE::uint64 size )
{
	std::memcpy( ptr, _Data.data() + _ReadPos, size );
	_ReadPos += size;
}

void XE::Buffer::Wirte( const char * ptr, XE::uint64 size )
{
	if( ( _Data.size() - _WirtePos ) >= size )
	{
		std::memcpy( _Data.data() + _WirtePos, ptr, size );
	}
	else
	{
		_Data.insert( _Data.end(), ptr, ptr + size );
	}

	_WirtePos += size;
}

void XE::Buffer::Reset()
{
	_ReadPos = 0;
	_WirtePos = 0;
}

XE::memory_view XE::Buffer::View() const
{
	return XE::memory_view( _Data.data(), _Data.size() );
}
