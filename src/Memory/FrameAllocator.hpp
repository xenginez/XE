/*!
 * \file   FrameFrameAllocator.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __FRAMEALLOCATOR_HPP__3B6E4D83_1935_40C5_A6F1_AECAB432DDB6
#define __FRAMEALLOCATOR_HPP__3B6E4D83_1935_40C5_A6F1_AECAB432DDB6

#include "FrameAlloc.h"

BEG_XE_NAMESPACE

template< typename _Ty > class FrameAllocator
{
public:
	static_assert( !std::is_const_v<_Ty>, "The C++ Standard forbids containers of const elements because FrameFrameAllocator<const T> is ill-formed." );

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
		using other = FrameAllocator<_Other>;
	};

public:
	constexpr FrameAllocator() noexcept
	{
	}

	constexpr FrameAllocator( const FrameAllocator& ) noexcept
	{
	}

	template<class _Other> constexpr FrameAllocator( const FrameAllocator<_Other>& ) noexcept
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
	_Ty * allocate( const XE::uint64 _Count )
	{
		return static_cast<_Ty*>( FrameAlloc::allocate( _Count ) );
	}

	_Ty * allocate( const XE::uint64 _Count, const void * )
	{
		return ( allocate( _Count ) );
	}

public:
	void deallocate( _Ty * const _Ptr, const XE::uint64 _Count )
	{

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
	bool operator==( const XE::FrameAllocator<_Other>& ) noexcept
	{
		return ( true );
	}

	template<class _Other>
	bool operator!=( const XE::FrameAllocator<_Other>& ) noexcept
	{
		return ( false );
	}

};

template< typename T >
using FList = std::list<T, FrameAllocator<T>>;
template< typename T >
using FDeque = std::deque<T, FrameAllocator<T>>;
template< typename T >
using FStack = std::stack<T, FDeque<T>>;
template< typename T >
using FQueue = std::queue<T, FDeque<T>>;
template< typename T >
using FArray = std::vector<T, FrameAllocator<T>>;
template< typename T >
using FSet = std::set<T, std::less<T>, FrameAllocator<T>>;
template< typename K, typename V >
using FMap = std::map<K, V, std::less<K>, FrameAllocator<Pair<const K, V>>>;
template< typename T >
using FMultiSet = std::multiset<T, std::less<T>, FrameAllocator<T>>;
template< typename K, typename V >
using FMultiMap = std::multimap<K, V, std::less<K>, FrameAllocator<Pair<const K, V>>>;
template< typename T >
using FUnorderedSet = std::unordered_set<T, std::hash<T>, std::equal_to<T>, FrameAllocator<T>>;
template< typename K, typename V >
using FUnorderedMap = std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, FrameAllocator<Pair<const K, V>>>;
template< typename T >
using FUnorderedMultiSet = std::unordered_multiset<T, std::hash<T>, std::equal_to<T>, FrameAllocator<T>>;
template< typename K, typename V >
using FUnorderedMultiMap = std::unordered_multimap<K, V, std::hash<K>, std::equal_to<K>, FrameAllocator<Pair<const K, V>>>;


END_XE_NAMESPACE

#endif // __FRAMEALLOCATOR_HPP__3B6E4D83_1935_40C5_A6F1_AECAB432DDB6
