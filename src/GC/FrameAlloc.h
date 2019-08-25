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

class GC_API FrameAlloc : public XE::Singleton< FrameAlloc >
{
private:
	struct Private;
	struct LocalThreadData;

public:
	FrameAlloc();

	~FrameAlloc();

public:
	static void * Allocate( const XE::uint64 _Count );

	static void Reset();

	static void Clear();

private:
	static XE::FrameAlloc::LocalThreadData * GetLocalThreadData();

	static void RegisterLocalThreadData( XE::FrameAlloc::LocalThreadData * val );

	static void UnregisterLocalThreadData( XE::FrameAlloc::LocalThreadData * val );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __FRAMEALLOC_H__D71366DB_92AD_48B0_8FBB_E64EB203564D
