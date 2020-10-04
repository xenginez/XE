/*!
 * \file   Allocator.hpp
 *
 * \author ZhengYuanQing
 * \date   2020/10/04
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef ALLOCATOR_H__27881BD6_7BF3_4927_873E_C4CD80D8C9A5
#define ALLOCATOR_H__27881BD6_7BF3_4927_873E_C4CD80D8C9A5

#include "MemoryResource.h"

BEG_XE_NAMESPACE

template< typename T > class Allocator
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

#endif // ALLOCATOR_H__27881BD6_7BF3_4927_873E_C4CD80D8C9A5
