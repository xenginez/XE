/*!
 * \file   Alloc.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ALLOC_H__21A506C1_52E7_444B_86B0_4D35EEDDC537
#define __ALLOC_H__21A506C1_52E7_444B_86B0_4D35EEDDC537

#include "Type.h"

BEG_XE_NAMESPACE

class MEMORY_API Alloc : public XE::NonCopyable
{
public:
	Alloc() = delete;

	~Alloc() = delete;

public:
	static void * Allocate( XE::uint64 size );

	static void * Reallocate( void * ptr, XE::uint64 size );

	static void Deallocate( void * ptr );

};

END_XE_NAMESPACE

#endif // __ALLOC_H__21A506C1_52E7_444B_86B0_4D35EEDDC537
