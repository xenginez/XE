/*!
 * \file   FrameAlloc.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __FRAMEALLOC_H__D71366DB_92AD_48B0_8FBB_E64EB203564D
#define __FRAMEALLOC_H__D71366DB_92AD_48B0_8FBB_E64EB203564D

#include "Alloc.h"

BEG_XE_NAMESPACE

class MEMORY_API FrameAlloc : public XE::Singleton< FrameAlloc >
{
public:
	FrameAlloc();

	~FrameAlloc();

public:
	static void * allocate( const XE::uint64 _Count );

public:
	static void clear();

	static void reset();

	static void capacity();

private:
	std::atomic<XE::uint8 *> _beg;
	std::atomic<XE::uint8 *> _cur;
	std::atomic<XE::uint8 *> _end;
};

END_XE_NAMESPACE

#endif // __FRAMEALLOC_H__D71366DB_92AD_48B0_8FBB_E64EB203564D
