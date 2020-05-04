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

class XE_API FrameAlloc : public XE::Singleton< FrameAlloc >
{
    SINGLETON( FrameAlloc )

private:
	struct Private;

private:
	FrameAlloc();

	~FrameAlloc();

public:
	static void * Allocate( const XE::uint64 _Count );

	static void Reset();

private:
	static XE::FrameAlloc::Private * GetPrivate();

};

END_XE_NAMESPACE

#endif // __FRAMEALLOC_H__D71366DB_92AD_48B0_8FBB_E64EB203564D
