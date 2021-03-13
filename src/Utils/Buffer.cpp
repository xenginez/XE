#include "Buffer.h"

IMPLEMENT_META( XE::Buffer );

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

XE::Buffer::Buffer( XE::MemoryView _Right )
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

bool XE::Buffer::Eof() const
{
	return _ReadPos == _WirtePos;
}

XE::uint64 XE::Buffer::Size() const
{
	return _Data.size();
}

XE::uint64 XE::Buffer::ReadPos() const
{
	return _ReadPos;
}

XE::uint64 XE::Buffer::WirtePos() const
{
	return _WirtePos;
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
		_Data.resize( _Data.size() + ( size - ( _Data.size() - _WirtePos ) ) );
	}

	std::memcpy( _Data.data() + _WirtePos, ptr, size );
	_WirtePos += size;
}

void XE::Buffer::Reset()
{
	_ReadPos = 0;
	_WirtePos = 0;
}

void XE::Buffer::Clear()
{
	Reset();

	_Data.clear();
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

XE::MemoryView XE::Buffer::View() const
{
	return XE::MemoryView( _Data.data(), _Data.size() );
}

XE::RingBuffer::RingBuffer( XE::uint64 size )
{
	_Data.resize( size );
}

XE::RingBuffer::RingBuffer( XE::MemoryView _Right )
{
	_Data.insert( _Data.end(), _Right.data(), _Right.data() + _Right.size() );
}

XE::RingBuffer::~RingBuffer()
{

}

void XE::RingBuffer::Read( char * ptr, XE::uint64 size )
{
	if( _ReadPos + size >= _Data.size() )
	{
		XE::uint64 sz = _Data.size() - _ReadPos;
		Buffer::Read( ptr, sz );

		ptr += sz;
		size -= sz;
		_ReadPos = 0;
	}

	Buffer::Read( ptr, size );
}

void XE::RingBuffer::Wirte( const char * ptr, XE::uint64 size )
{
	if( _WirtePos + size >= _Data.size() )
	{
		XE::uint64 sz = _Data.size() - _WirtePos;

		Buffer::Wirte( ptr, sz );

		ptr += sz;
		size -= sz;
		_WirtePos = 0;
	}

	Buffer::Wirte( ptr, size );
}
