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

template< typename Ty, typename ... Types > XE::SharedPtr<Ty> MakeShared( Types && ...args )
{
	return std::allocate_shared<Ty>( XE::AllocatorProxy<Ty>::GetAllocator(), std::forward<Types>( args )... );
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


#define OBJECT_ALLOCATOR_PROXY( TYPE ) \
template<> class XE::AllocatorProxy<TYPE> \
{ \
public: \
	static std::pmr::polymorphic_allocator< T > * GetAllocator() \
	{ \
		static std::pmr::polymorphic_allocator< T > _alloc( GetResource() ); \
		return &_alloc; \
	} \
	static std::pmr::memory_resource * GetResource() \
	{ \
		return XE::MemoryResource::GetObjectMemoryResource(); \
	} \
};

#endif // ALLOCATORPROXY_H__9E739449_6D91_4558_AF69_2D49ED89AB2F
