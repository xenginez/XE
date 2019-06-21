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

#include "Global.h"

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

	inline std::string to_string( bool _Val )
	{
		return _Val ? "true" : "false";
	}

	inline std::string to_string( char _Val )
	{
		std::string s;
		s.push_back( _Val );
		return s;
	}

	inline std::string to_string( char * _Val )
	{
		return _Val;
	}

	inline std::string to_string( const char * _Val )
	{
		return _Val;
	}
	
	inline std::string to_string( const std::string& _Val )
	{
		return _Val;
	}

	inline std::string to_string( const std::filesystem::path & _Val )
	{
		return _Val.string();
	}

	inline std::string to_string( const std::chrono::system_clock::time_point & _Val )
	{
		std::ostringstream oss;

		const time_t t = std::chrono::system_clock::to_time_t( _Val );

		const char * put_time_format = "%Y-%m-%d %X";

	#if PLATFORM_OS == OS_WINDOWS
		std::tm tm;
		gmtime_s( &tm, &t );
		localtime_s( &tm, &t );
		oss << std::put_time( &tm, put_time_format );
	#else
		oss << std::put_time( std::gmtime( &t ), put_time_format );
	#endif

		return oss.str();
	}

	namespace chrono
	{
		inline system_clock::time_point from_string( const std::string & _Val )
		{
			std::tm tm;

			tm.tm_wday = 0;
			tm.tm_yday = 0;
			tm.tm_isdst = 0;

			tm.tm_year = std::stoi( _Val.substr( 0, 4 ) ) - 1900;
			tm.tm_mon = std::stoi( _Val.substr( 5, 2 ) ) - 1;
			tm.tm_mday = std::stoi( _Val.substr( 8, 2 ) );
			tm.tm_hour = std::stoi( _Val.substr( 11, 2 ) );
			tm.tm_min = std::stoi( _Val.substr( 14, 2 ) );
			tm.tm_sec = std::stoi( _Val.substr( 17, 2 ) );

		#if PLATFORM_OS == OS_WINDOWS
			const std::time_t t = _mkgmtime( &tm );
		#else
			const std::time_t t = timegm( &tm );
		#endif

			return system_clock::from_time_t( t );
		}
	};
};

BEG_XE_NAMESPACE

typedef signed char        int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;
typedef float 			   float32;
typedef double 			   float64;

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

END_XE_NAMESPACE

#endif // __TYPE_H__B9857ED9_F6EE_4A0A_8E87_0DAA433A5E40
