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

class GC_API ObjectAlloc : public XE::Singleton< ObjectAlloc >
{
private:
	struct Private;

public:
	ObjectAlloc();

	~ObjectAlloc();

public:
	static void * Allocate( XE::uint64 hash_code, XE::uint64 size, XE::uint64 count );

	static void Deallocate( void * ptr, XE::uint64 hash_code );

public:
	static void Clear();

	static void ShrinkToFit();

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // __OBJECTALLOC_H__25E6C688_5248_454F_8C87_E1A7A28B17B7
