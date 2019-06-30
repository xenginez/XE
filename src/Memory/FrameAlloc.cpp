#include "FrameAlloc.h"

USING_XE

struct XE::FrameAlloc::Private
{
	std::mutex Lock;
	XE::uint64 Mask = 0;
	std::atomic<XE::uint8 *> _beg = nullptr;
	std::atomic<XE::uint8 *> _cur = nullptr;
	std::atomic<XE::uint8 *> _end = nullptr;
};

XE::FrameAlloc::FrameAlloc()
	:_p( new Private )
{
	_p->_beg = ( XE::uint8 * )Alloc::Allocate( MBYTE( 4 ) );
	_p->_cur = _p->_beg.load();
	_p->_end = _p->_beg + ( MBYTE( 4 ) );
}

XE::FrameAlloc::~FrameAlloc()
{
	Clear();

	delete _p;
}

void * XE::FrameAlloc::Allocate( const XE::uint64 _Count )
{
	_P();

	if( XE::uint64( _p->_end - _p->_cur ) < _Count )
	{
		std::lock_guard<std::mutex> lock( _p->Lock );

		if( XE::uint64( _p->_end - _p->_cur ) < _Count )
		{
			Capacity();
		}
	}

	XE::uint8 * p = _p->_cur;
	while( !_p->_cur.compare_exchange_weak( p, p + _Count ) );

	return p;
}

void XE::FrameAlloc::Clear()
{
	_P();

	if( _p->_beg )
	{
		Alloc::Deallocate( _p->_beg );
	}

	_p->_beg = nullptr;
	_p->_cur = nullptr;
	_p->_end = nullptr;
}

void XE::FrameAlloc::Reset()
{
	_P();

	if( _p->_beg == nullptr )
	{
		_p->_beg = ( XE::uint8 * )Alloc::Allocate( MBYTE( 4 ) );
		_p->_end = _p->_beg + ( MBYTE( 4 ) );
	}

	if( _p->Mask == 1 )
	{
		_p->_cur = _p->_beg.load();
	}

	_p->Mask = ( _p->Mask + 1 ) % 2;
}

void XE::FrameAlloc::Capacity()
{
	_P();

	XE::uint64 size = ( _p->_end - _p->_beg ) * 2;
	_p->_beg = ( XE::uint8 * )Alloc::Reallocate( _p->_beg, size );
	_p->_end = _p->_beg + size;
}
