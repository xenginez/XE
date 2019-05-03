#include "FrameAlloc.h"

USING_XE


XE::FrameAlloc::FrameAlloc()
{
	reset();
}

XE::FrameAlloc::~FrameAlloc()
{
	clear();
}

void * XE::FrameAlloc::allocate( const XE::uint64 _Count )
{
	if ( XE::uint64( This()->_end - This()->_cur ) < _Count )
	{
		capacity();
	}

	uint8 * p = This()->_cur;

	while ( !This()->_cur.compare_exchange_strong( p, p + _Count ) )
	{
		p = This()->_cur;
	}

	return p;
}

void XE::FrameAlloc::clear()
{
	if ( This()->_beg )
	{
		Alloc::deallocate( This()->_beg );
	}

	This()->_beg = nullptr;
	This()->_cur = nullptr;
	This()->_end = nullptr;
}

void XE::FrameAlloc::reset()
{
	if ( This()->_beg == nullptr )
	{
		This()->_beg = (uint8 *)Alloc::allocate( ONE_MBYTE * 4 );
		This()->_end = This()->_beg + ( ONE_MBYTE * 4 );
	}

	This()->_cur = This()->_beg.load();
}

void XE::FrameAlloc::capacity()
{
	XE::uint64 size = ( This()->_end - This()->_beg ) * 2;
	This()->_beg = (uint8 *)Alloc::reallocate( This()->_beg, size );
	This()->_end = This()->_beg + size;
}
