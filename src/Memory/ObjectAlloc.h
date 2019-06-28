/*!
 * \file   ObjectAlloc.h
 *
 * \author ZhengYuanQing
 * \date   2019/06/28
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __OBJECTALLOC_H__25E6C688_5248_454F_8C87_E1A7A28B17B7
#define __OBJECTALLOC_H__25E6C688_5248_454F_8C87_E1A7A28B17B7

#include "Type.h"

BEG_XE_NAMESPACE

class MEMORY_API ObjectAlloc : public XE::NonCopyable
{
public:
	ObjectAlloc() = delete;

	~ObjectAlloc() = delete;

public:
	static void * allocate( XE::uint64 size );

	static void * reallocate( void * ptr, XE::uint64 size );

	static void deallocate( void * ptr );

};

END_XE_NAMESPACE

#endif // __OBJECTALLOC_H__25E6C688_5248_454F_8C87_E1A7A28B17B7
