/*!
 * \file   Memory.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MEMORY_H__32A3DBEA_AF97_44CA_B481_147D90DC8B33
#define __MEMORY_H__32A3DBEA_AF97_44CA_B481_147D90DC8B33

#include "Alloc.h"
#include "FrameAlloc.h"
#include "ObjectAlloc.h"
#include "Allocator.hpp"
#include "FrameAllocator.hpp"
#include "ObjectAllocator.hpp"

BEG_XE_NAMESPACE

template< typename Ty, typename ... Types > std::shared_ptr<Ty> make_shared( Types && ...args )
{
	static XE::AllocatorProxy<Ty>::allocator_type _alloc;

	return std::allocate_shared<Ty>( _alloc, args... );
}

END_XE_NAMESPACE


#define DECL_PTR( TYPE ) \
class TYPE; typedef std::shared_ptr< TYPE > TYPE##Ptr; typedef std::shared_ptr< const TYPE > TYPE##CPtr; typedef std::weak_ptr< TYPE > TYPE##WPtr; typedef std::unique_ptr<TYPE> TYPE##UPtr

#define DECL_OBJECT_POOL( TYPE ) \
template<> struct AllocatorProxy< TYPE > \
{ \
public: \
	using allocator_type = XE::ObjectAllocator< TYPE >; \
}

#define CP_CAST std::const_pointer_cast
#define SP_CAST std::static_pointer_cast
#define DP_CAST std::dynamic_pointer_cast
#define RP_CAST std::reinterpret_pointer_cast
#define XE_THIS(TYPE) std::static_pointer_cast<TYPE>( shared_from_this() )

#endif // __MEMORY_H__32A3DBEA_AF97_44CA_B481_147D90DC8B33
