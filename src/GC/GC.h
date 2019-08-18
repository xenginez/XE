/*!
 * \file	GC.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GC_H__23E4C3C2_7560_44FC_949E_DACFAF9F36EC
#define GC_H__23E4C3C2_7560_44FC_949E_DACFAF9F36EC

#include "Alloc.h"
#include "FrameAlloc.h"
#include "ObjectAlloc.h"
#include "Allocator.hpp"
#include "FrameAllocator.hpp"
#include "ObjectAllocator.hpp"

#include "GCObject.h"

BEG_XE_NAMESPACE

template< typename Ty, typename ... Types > std::shared_ptr<Ty> make_shared( Types && ...args )
{
	typename XE::AllocatorProxy<Ty>::allocator_type _alloc;

	return std::allocate_shared<Ty>( _alloc, args... );
}

END_XE_NAMESPACE


#define DECL_PTR( TYPE ) \
class TYPE; \
typedef std::shared_ptr< TYPE > TYPE##Ptr; \
typedef std::shared_ptr< const TYPE > TYPE##CPtr; \
typedef std::weak_ptr< TYPE > TYPE##WPtr; \
typedef std::unique_ptr< TYPE > TYPE##UPtr; \
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

#endif // GC_H__23E4C3C2_7560_44FC_949E_DACFAF9F36EC
