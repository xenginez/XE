#include "FrameAlloc.h"

USING_XE

struct XE::FrameAlloc::Private
{
	std::atomic<XE::uint8 *> _beg = nullptr;
	std::atomic<XE::uint8 *> _cur = nullptr;
	std::atomic<XE::uint8 *> _end = nullptr;
};

XE::FrameAlloc::FrameAlloc()
	:_p( new Private )
{
	reset();
}

XE::FrameAlloc::~FrameAlloc()
{
	clear();

	delete _p;
}

void * XE::FrameAlloc::allocate( const XE::uint64 _Count )
{
	if ( XE::uint64( This()->_p->_end - This()->_p->_cur ) < _Count )
	{
		capacity();
	}

	XE::uint8 * p = This()->_p->_cur;

	while ( !This()->_p->_cur.compare_exchange_strong( p, p + _Count ) )
	{
		p = This()->_p->_cur;
	}

	return p;
}

void XE::FrameAlloc::clear()
{
	if ( This()->_p->_beg )
	{
		Alloc::deallocate( This()->_p->_beg );
	}

	This()->_p->_beg = nullptr;
	This()->_p->_cur = nullptr;
	This()->_p->_end = nullptr;
}

void XE::FrameAlloc::reset()
{
	if ( This()->_p->_beg == nullptr )
	{
		This()->_p->_beg = (XE::uint8 *)Alloc::allocate( ONE_MBYTE * 4 );
		This()->_p->_end = This()->_p->_beg + ( ONE_MBYTE * 4 );
	}

	This()->_p->_cur = This()->_p->_beg.load();
}

void XE::FrameAlloc::capacity()
{
	XE::uint64 size = ( This()->_p->_end - This()->_p->_beg ) * 2;
	This()->_p->_beg = (XE::uint8 *)Alloc::reallocate( This()->_p->_beg, size );
	This()->_p->_end = This()->_p->_beg + size;
}
