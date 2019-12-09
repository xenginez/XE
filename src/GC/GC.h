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

#include "GCObject.h"
#include "Allocator.hpp"
#include "FrameAllocator.hpp"
#include "ObjectAllocator.hpp"

BEG_XE_NAMESPACE

template< typename T >
using WeakPtr = std::weak_ptr<T>;
template< typename T >
using SharedPtr = std::shared_ptr<T>;

template< typename Ty, typename ... Types > XE::SharedPtr<Ty> MakeShared( Types && ...args )
{
	typename XE::AllocatorProxy<Ty>::allocator_type _alloc;

	return std::allocate_shared<Ty>( _alloc, args... );
}
END_XE_NAMESPACE

#define DECL_PTR( TYPE ) \
class TYPE; \
typedef XE::WeakPtr< TYPE > TYPE##WPtr; \
typedef XE::SharedPtr< TYPE > TYPE##Ptr; \
typedef XE::SharedPtr< const TYPE > TYPE##CPtr; \
typedef TYPE * TYPE##RPtr

#define DECL_ALLOCATOR_POLL( TYPE ) \
template<> struct AllocatorProxy< TYPE > \
{ \
public: \
	using allocator_type = XE::ObjectAllocator< TYPE >; \
}

#define DECL_ALLOCATOR_FRAME( TYPE ) \
template<> struct AllocatorProxy< TYPE > \
{ \
public: \
	using allocator_type = XE::FrameAllocator< TYPE >; \
} 

#define CP_CAST std::const_pointer_cast
#define SP_CAST std::static_pointer_cast
#define DP_CAST std::dynamic_pointer_cast
#define RP_CAST std::reinterpret_pointer_cast
#define XE_THIS(TYPE) std::static_pointer_cast<TYPE>( shared_from_this() )

#endif // GC_H__FA923875_63B1_4537_BFB7_E063B491B0B7
