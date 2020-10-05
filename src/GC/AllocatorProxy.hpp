/*!
 * \file   AllocatorProxy.hpp
 *
 * \author ZhengYuanQing
 * \date   2020/10/05
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef ALLOCATORPROXY_H__9E739449_6D91_4558_AF69_2D49ED89AB2F
#define ALLOCATORPROXY_H__9E739449_6D91_4558_AF69_2D49ED89AB2F

#include "MemoryResource.h"

BEG_XE_NAMESPACE

template< typename T > class AllocatorProxy
{
public:
	static std::pmr::polymorphic_allocator< T > & GetAllocator()
	{
		static std::pmr::polymorphic_allocator< T > _alloc( GetResource() );
		return _alloc;
	}

	static std::pmr::memory_resource * GetResource()
	{
		return XE::MemoryResource::GetDefaultMemoryResource();
	}
};

END_XE_NAMESPACE

#endif // ALLOCATORPROXY_H__9E739449_6D91_4558_AF69_2D49ED89AB2F
