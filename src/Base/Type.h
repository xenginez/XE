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

XE_INLINE std::string ToString( bool _Val )
{
	return _Val ? "true" : "false";
}

XE_INLINE std::string ToString( char _Val )
{
	return { 1, _Val };
}

XE_INLINE std::string ToString( uint8 _Val )
{
	return std::to_string( ( int32 ) _Val );
}

XE_INLINE std::string ToString( int16 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( uint16 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( int32 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( uint32 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( int64 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( uint64 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( float32 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( float64 _Val )
{
	return std::to_string( _Val );
}

XE_INLINE std::string ToString( char * _Val )
{
	return _Val;
}

XE_INLINE std::string ToString( const char * _Val )
{
	return _Val;
}

XE_INLINE std::string ToString( const std::string & _Val )
{
	return _Val;
}

XE_INLINE std::string ToString( const std::filesystem::path & _Val )
{
	return _Val.u8string();
}

XE_INLINE std::string ToString( const std::chrono::system_clock::time_point & _Val )
{
	std::tm _tm;
	std::ostringstream _oss;
	const time_t _tt = std::chrono::system_clock::to_time_t( _Val );

#if PLATFORM_OS == OS_WINDOWS
	localtime_s( &_tm, &_tt );
#else
	localtime_r( &_tt, &_tm );
#endif

	_oss << std::put_time( &_tm, "%Y-%m-%d %X" );

	return _oss.str();
}


XE_INLINE bool FromString( const std::string & _Str, bool & _Val )
{
	if( _Str == "true" || _Str == "false" )
	{
		_Val = _Str == "true";
		return true;
	}

	return false;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int8 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int16 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int32 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::int64 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint8 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint16 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint32 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::uint64 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::float32 & _Val )
{
	size_t size = 0;

	_Val = std::stof( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, XE::float64 & _Val )
{
	size_t size = 0;

	_Val = std::stod( _Str, &size );

	return size > 0;
}

XE_INLINE bool FromString( const std::string & _Str, std::string & _Val )
{
	_Val = _Str;

	return true;
}

XE_INLINE bool FromString( const std::string & _Str, std::filesystem::path & _Val )
{
	_Val = _Str;

	return true;
}

XE_INLINE bool FromString( const std::string & _Str, std::chrono::system_clock::time_point & _Val )
{
	if( _Str.size() == 18 )
	{
		std::tm _tm;

		_tm.tm_year = std::stoi( _Str.substr( 0, 4 ) ) - 1900;
		_tm.tm_mon = std::stoi( _Str.substr( 5, 2 ) ) - 1;
		_tm.tm_mday = std::stoi( _Str.substr( 8, 2 ) );
		_tm.tm_hour = std::stoi( _Str.substr( 11, 2 ) );
		_tm.tm_min = std::stoi( _Str.substr( 14, 2 ) );
		_tm.tm_sec = std::stoi( _Str.substr( 17, 2 ) );

		_Val = std::chrono::system_clock::from_time_t( std::mktime( &_tm ) );

		return true;
	}

	return false;
}

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
