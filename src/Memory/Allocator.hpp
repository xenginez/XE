/*!
 * \file   Allocator.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __ALLOCATOR_HPP__56D93152_EEB6_4E08_8F6B_DA7B642407F0
#define __ALLOCATOR_HPP__56D93152_EEB6_4E08_8F6B_DA7B642407F0

#include "Alloc.h"

BEG_XE_NAMESPACE

template< typename _Ty > class Allocator
{
public:
	static_assert( !std::is_const_v<_Ty>, "The C++ Standard forbids containers of const elements because Allocator<const T> is ill-formed." );

public:
	using _Not_user_specialized = void;

	using value_type = _Ty;

	typedef _Ty * pointer;
	typedef const _Ty * const_pointer;

	typedef _Ty& reference;
	typedef const _Ty& const_reference;

	typedef XE::uint64 size_type;
	typedef ptrdiff_t difference_type;

	using propagate_on_container_move_assignment = std::true_type;
	using is_always_equal = std::true_type;

public:
	template<typename _Other> struct rebind
	{
		using other = Allocator<_Other>;
	};

public:
	constexpr Allocator() noexcept
	{
	}

	constexpr Allocator( const Allocator& ) noexcept
	{
	}
	
	template<class _Other> constexpr Allocator( const Allocator<_Other>& ) noexcept
	{
	}

public:
	_Ty * address( _Ty& _Val ) const noexcept
	{
		return ( std::addressof( _Val ) );
	}

	const _Ty * address( const _Ty& _Val ) const noexcept
	{
		return ( std::addressof( _Val ) );
	}

public:
	void deallocate( _Ty * const _Ptr, const XE::uint64 _Count )
	{
		XE::Alloc::deallocate( _Ptr );
	}

public:
	_Ty * allocate( const XE::uint64 _Count )
	{
		return ( static_cast<_Ty *>( XE::Alloc::allocate( sizeof( _Ty ) * _Count ) ) );
	}

	_Ty * allocate( const XE::uint64 _Count, const void * )
	{
		return ( allocate( _Count ) );
	}

public:
	template<class _Objty, class... _Types> void construct( _Objty * const _Ptr, _Types&&... _Args )
	{
		::new ( const_cast<void *>( static_cast<const volatile void *>( _Ptr ) ) ) _Objty( std::forward<_Types>( _Args )... );
	}

public:
	template<class _Uty> void destroy( _Uty * const _Ptr )
	{
		_Ptr->~_Uty();
	}

public:
	XE::uint64 max_size() const noexcept
	{
		return ( XE::uint64( -1 ) / sizeof( _Ty ) );
	}

public:
	template<class _Other>
	bool operator==( const XE::Allocator<_Other>& ) noexcept
	{
		return ( true );
	}

	template<class _Other>
	bool operator!=( const XE::Allocator<_Other>& ) noexcept
	{
		return ( false );
	}

};

template< typename Ty > struct AllocatorProxy
{
public:
	using allocator_type = XE::Allocator< Ty >;
};

template< typename T >
using List = std::list<T, Allocator<T>>;
template< typename T >
using Deque = std::deque<T, Allocator<T>>;
template< typename T >
using Stack = std::stack<T, Deque<T>>;
template< typename T >
using Queue = std::queue<T, Deque<T>>;
template< typename T >
using Array = std::vector<T, Allocator<T>>;
template< typename K, typename V >
using Pair = std::pair<K, V>;
template< typename T >
using Set = std::set<T, std::less<T>, Allocator<T>>;
template< typename K, typename V >
using Map = std::map<K, V, std::less<K>, Allocator<Pair<const K, V>>>;
template< typename T >
using MultiSet = std::multiset<T, std::less<T>, Allocator<T>>;
template< typename K, typename V >
using MultiMap = std::multimap<K, V, std::less<K>, Allocator<Pair<const K, V>>>;
template< typename T >
using UnorderedSet = std::unordered_set<T, std::hash<T>, std::equal_to<T>, Allocator<T>>;
template< typename K, typename V >
using UnorderedMap = std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, Allocator<Pair<const K, V>>>;
template< typename T >
using UnorderedMultiSet = std::unordered_multiset<T, std::hash<T>, std::equal_to<T>, Allocator<T>>;
template< typename K, typename V >
using UnorderedMultiMap = std::unordered_multimap<K, V, std::hash<K>, std::equal_to<K>, Allocator<Pair<const K, V>>>;

END_XE_NAMESPACE

#endif // __ALLOCATOR_HPP__56D93152_EEB6_4E08_8F6B_DA7B642407F0
