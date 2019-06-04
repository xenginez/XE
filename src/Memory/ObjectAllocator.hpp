/*!
 * \file    ObjectAllocator.hpp
 *
 * \author  ZhengYuanQing
 * \date    2019-05-19
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __OBJECTALLOCATOR_HPP__16F6B961_D3BF_45F3_8A72_802188A4AD06
#define __OBJECTALLOCATOR_HPP__16F6B961_D3BF_45F3_8A72_802188A4AD06

#include "Allocator.hpp"

BEG_XE_NAMESPACE

template < typename _Ty > class ObjectAllocator
{
public:
	static_assert(!std::is_const_v < _Ty >, "The C++ Standard forbids containers of const elements because Allocator<const T> is ill-formed.");

public:
	using _Not_user_specialized = void;
	
	using value_type = _Ty;
	
	typedef _Ty * pointer;
	typedef const _Ty * const_pointer;
	
	typedef _Ty &reference;
	typedef const _Ty &const_reference;
	
	typedef XE::uint64 size_type;
	typedef ptrdiff_t difference_type;
	
	using propagate_on_container_move_assignment = std::true_type;
	using is_always_equal = std::true_type;

public:
	template < typename _Other > struct rebind
	{
		using other = ObjectAllocator < _Other >;
	};

public:
	constexpr ObjectAllocator() noexcept = default;
	
	constexpr ObjectAllocator( const ObjectAllocator & ) noexcept = default;

public:
	_Ty * address( _Ty &_Val ) const noexcept
	{
		return ( std::addressof(_Val));
	}
	
	const _Ty * address( const _Ty &_Val ) const noexcept
	{
		return ( std::addressof(_Val));
	}

public:
	void deallocate( _Ty * const _Ptr, const XE::uint64 _Count )
	{
		XE::Alloc::deallocate(_Ptr);
	}

public:
	_Ty * allocate( const XE::uint64 _Count )
	{
		return ( static_cast<_Ty *>( XE::Alloc::allocate(sizeof(_Ty) * _Count)));
	}
	
	_Ty * allocate( const XE::uint64 _Count, const void * )
	{
		return ( allocate(_Count));
	}

public:
	template < class _Objty, class... _Types > void construct( _Objty * const _Ptr, _Types &&... _Args )
	{
		::new(const_cast<void *>( static_cast<const volatile void *>( _Ptr ))) _Objty(std::forward < _Types >(_Args)...);
	}

public:
	template < class _Uty > void destroy( _Uty * const _Ptr )
	{
		_Ptr->~_Uty();
	}

public:
	XE::uint64 max_size() const noexcept
	{
		return ( std::numeric_limits < uint64 >::max() / sizeof(_Ty));
	}

public:
	template < class _Other > bool operator ==( const XE::ObjectAllocator < _Other > & ) noexcept
	{
		return ( true );
	}
	
	template < class _Other > bool operator !=( const XE::ObjectAllocator < _Other > & ) noexcept
	{
		return ( false );
	}
};

END_XE_NAMESPACE

#endif //__OBJECTALLOCATOR_HPP__16F6B961_D3BF_45F3_8A72_802188A4AD06
