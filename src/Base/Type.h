/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__B9857ED9_F6EE_4A0A_8E87_0DAA433A5E40
#define __TYPE_H__B9857ED9_F6EE_4A0A_8E87_0DAA433A5E40

#include <memory>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "Base/Config.h"

namespace std
{
	template<class _Ty> struct remove_pointer< weak_ptr<_Ty> >
	{
		using type = typename remove_pointer<_Ty>::type;
	};

	template<class _Ty> struct remove_pointer< shared_ptr<_Ty> >
	{
		using type = typename remove_pointer<_Ty>::type;
	};

	template< typename T > struct is_weak_ptr
	{
		using type = T;
		static constexpr bool value = false;
	};

	template< typename T > struct is_weak_ptr< weak_ptr< T > >
	{
		using type = T;
		static constexpr bool value = true;
	};

	template< typename T > inline constexpr bool is_weak_ptr_v = is_weak_ptr<T>::value;

	template< typename T > struct is_shared_ptr
	{
		using type = T;
		static constexpr bool value = false;
	};

	template< typename T > struct is_shared_ptr< shared_ptr< T > >
	{
		using type = T;
		static constexpr bool value = true;
	};

	template< typename T > inline constexpr bool is_shared_ptr_v = is_shared_ptr<T>::value;

	template <class _Kty, size_t N > struct hash< _Kty[N] >
	{
		size_t operator()( const _Kty _Keyval[] ) const
		{
			size_t _hash = 0;

			std::hash<_Kty> key_hash;
			for( size_t i = 0; i < N; ++i )
			{
				_hash ^= key_hash( _Keyval[i] );
			}

			return _hash;
		}
	};
};

BEG_XE_NAMESPACE

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using float32 = float;
using float64 = double;

template< typename T > struct TypeTraits
{
	using value_t = T;

	using remove_const_t = typename std::remove_const< value_t >::type;
	using remove_pointer_t = typename std::remove_pointer< value_t >::type;
	using remove_volatile_t = typename std::remove_volatile< value_t >::type;
	using remove_reference_t = typename std::remove_reference< value_t >::type;

	using remove_const_pointer_t = typename std::remove_const< remove_pointer_t >::type;
	using remove_const_volatile_t = typename std::remove_const< remove_volatile_t >::type;
	using remove_const_reference_t = typename std::remove_const< remove_reference_t >::type;
	using remove_pointer_volatile_t = typename std::remove_pointer< remove_volatile_t >::type;
	using remove_pointer_reference_t = typename std::remove_pointer< remove_reference_t >::type;
	using remove_volatile_reference_t = typename std::remove_volatile< remove_reference_t >::type;

	using remove_const_pointer_volatile_t = typename std::remove_const< remove_pointer_volatile_t >::type;
	using remove_const_pointer_reference_t = typename std::remove_const< remove_pointer_reference_t >::type;
	using remove_const_volatile_reference_t = typename std::remove_const< remove_volatile_reference_t >::type;
	using remove_pointer_volatile_reference_t = typename std::remove_pointer< remove_volatile_reference_t >::type;

	using raw_t = typename std::remove_pointer< typename std::remove_const< typename std::remove_volatile< typename std::remove_reference<value_t>::type >::type >::type >::type;
};

template< typename T > struct RawPointer
{
	static T * Get( T * val )
	{
		return val;
	}
};

template< typename T > struct RawPointer<T &>
{
	static T * Get( T & val )
	{
		return &val;
	}
};

template< typename T > struct RawPointer< std::weak_ptr<T> >
{
	static T * Get( std::weak_ptr<T> * val )
	{
		return val ? val->lock().get() : nullptr;
	}
};

template< typename T > struct RawPointer< std::shared_ptr<T> >
{
	static T * Get( std::shared_ptr<T> * val )
	{
		return val ? val->get() : nullptr;
	}
};

template< typename T > struct RawPointer< const std::weak_ptr<T> >
{
	static T * Get( const std::weak_ptr<T> * val )
	{
		return val ? val->lock().get() : nullptr;
	}
};

template< typename T > struct RawPointer< const std::shared_ptr<T> >
{
	static T * Get( const std::shared_ptr<T> * val )
	{
		return val ? val->get() : nullptr;
	}
};

template< typename T > struct ArrayCount;
template< typename T, XE::uint64 C > struct ArrayCount< T[C] >
{
	static constexpr XE::uint64 Count = C;
};

template< typename T > XE::uint64 constexpr countof( T & val )
{
	return ArrayCount< T >::Count;
}

END_XE_NAMESPACE

#endif // __TYPE_H__B9857ED9_F6EE_4A0A_8E87_0DAA433A5E40
