/*!
 * \file	GC.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GC_H__FA923875_63B1_4537_BFB7_E063B491B0B7
#define GC_H__FA923875_63B1_4537_BFB7_E063B491B0B7

#include "MemoryResource.h"

BEG_XE_NAMESPACE

template< typename T >
using WeakPtr = std::weak_ptr<T>;
template< typename T >
using SharedPtr = std::shared_ptr<T>;

template< typename Ty, typename ... Types > XE::SharedPtr<Ty> MakeShared( Types && ...args )
{
    std::pmr::polymorphic_allocator< Ty > alloc( XE::MemoryResource::GetObjectMemoryResource() );

    return std::allocate_shared<Ty>( alloc, std::forward<Types>( args )... );
}
END_XE_NAMESPACE

#define DECL_PTR( TYPE ) \
class TYPE; \
typedef XE::WeakPtr< TYPE > TYPE##WPtr; \
typedef XE::SharedPtr< TYPE > TYPE##Ptr; \
typedef XE::SharedPtr< const TYPE > TYPE##CPtr; \
typedef TYPE * TYPE##RPtr

#define CP_CAST std::const_pointer_cast
#define SP_CAST std::static_pointer_cast
#define DP_CAST std::dynamic_pointer_cast
#define RP_CAST std::reinterpret_pointer_cast
#define XE_THIS(TYPE) std::static_pointer_cast<TYPE>( shared_from_this() )

#endif // GC_H__FA923875_63B1_4537_BFB7_E063B491B0B7
