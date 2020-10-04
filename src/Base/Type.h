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

	template< typename T > inline bool is_ready( std::future< T > & _Future )
	{
		return _Future.valid() && _Future.wait_for( std::chrono::seconds( 0 ) ) == std::future_status::ready;
	}
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
#ifndef XE_DOUBLE
using real = float32;
#else
using real = float64;
#endif
using thread_id = std::thread::id;

inline std::string ToString( bool _Val )
{
	return _Val ? "true" : "false";
}

inline std::string ToString( char _Val )
{
	return { 1, _Val };
}

inline std::string ToString( uint8 _Val )
{
	return std::to_string( ( int32 ) _Val );
}

inline std::string ToString( int16 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( uint16 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( int32 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( uint32 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( int64 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( uint64 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( float32 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( float64 _Val )
{
	return std::to_string( _Val );
}

inline std::string ToString( char * _Val )
{
	return _Val;
}

inline std::string ToString( const char * _Val )
{
	return _Val;
}

inline std::string ToString( const std::string & _Val )
{
	return _Val;
}

inline std::string ToString( const std::chrono::system_clock::time_point & _Val )
{
	std::ostringstream oss;

	const time_t t = std::chrono::system_clock::to_time_t( _Val );

	const char * put_time_format = "%Y-%m-%d %X";

#if PLATFORM_OS & OS_WINDOWS
	std::tm tm;
	gmtime_s( &tm, &t );
	localtime_s( &tm, &t );
	oss << std::put_time( &tm, put_time_format );
#else
	oss << std::put_time( std::gmtime( &t ), put_time_format );
#endif

	return oss.str();
}


inline bool FromString( const std::string & _Str, bool & _Val )
{
	if( _Str == "true" || _Str == "false" )
	{
		_Val = _Str == "true";
		return true;
	}

	return false;
}

inline bool FromString( const std::string & _Str, XE::int8 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::int16 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::int32 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::int64 & _Val )
{
	size_t size = 0;

	_Val = std::stol( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::uint8 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::uint16 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::uint32 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::uint64 & _Val )
{
	size_t size = 0;

	_Val = std::stoul( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::float32 & _Val )
{
	size_t size = 0;

	_Val = std::stof( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, XE::float64 & _Val )
{
	size_t size = 0;

	_Val = std::stod( _Str, &size );

	return size > 0;
}

inline bool FromString( const std::string & _Str, std::string & _Val )
{
	_Val = _Str;

	return true;
}

inline bool FromString( const std::string & _Str, std::chrono::system_clock::time_point & _Val )
{
	if( _Str.size() == 18 )
	{
		std::tm tm;

		tm.tm_wday = 0;
		tm.tm_yday = 0;
		tm.tm_isdst = 0;

		tm.tm_year = std::stoi( _Str.substr( 0, 4 ) ) - 1900;
		tm.tm_mon = std::stoi( _Str.substr( 5, 2 ) ) - 1;
		tm.tm_mday = std::stoi( _Str.substr( 8, 2 ) );
		tm.tm_hour = std::stoi( _Str.substr( 11, 2 ) );
		tm.tm_min = std::stoi( _Str.substr( 14, 2 ) );
		tm.tm_sec = std::stoi( _Str.substr( 17, 2 ) );

#if PLATFORM_OS & OS_WINDOWS
		const std::time_t t = _mkgmtime( &tm );
#else
		const std::time_t t = timegm( &tm );
#endif

		_Val = std::chrono::system_clock::from_time_t( t );

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

template <class _Elem> struct memory_traits
{
	using element_type  = _Elem;
	using int_type   = int;
	using pos_type   = std::streampos;
	using off_type   = std::streamoff;
	using state_type = _Mbstatet;

	static constexpr int compare( const _Elem * _First1, const _Elem * _First2, size_t _Count ) noexcept
	{
		for( ; 0 < _Count; --_Count, ++_First1, ++_First2 )
		{
			if( *_First1 != *_First2 )
			{
				return *_First1 < *_First2 ? -1 : +1;
			}
		}

		return 0;
	}

	static constexpr size_t length( const _Elem * _First ) noexcept
	{
		size_t _Count = 0;
		while( *_First != _Elem() )
		{
			++_Count;
			++_First;
		}

		return _Count;
	}

	static _Elem * copy( _Elem * const _First1, const _Elem * _First2, size_t _Count ) noexcept
	{
		return static_cast< _Elem * >( std::memcpy( _First1, _First2, _Count * sizeof( _Elem ) ) );
	}

	static _Elem * _Copy_s( _Elem * const _First1, const size_t _Dest_size, const _Elem * const _First2, const size_t _Count )  noexcept
	{
		ASSERT( _Count <= _Dest_size && "invalid argument" );
		return copy( _First1, _First2, _Count );
	}

	static constexpr const _Elem * find( const _Elem * _First, size_t _Count, const _Elem & _Ch ) noexcept
	{
		for( ; 0 < _Count; --_Count, ++_First )
		{
			if( *_First == _Ch )
			{
				return _First;
			}
		}

		return nullptr;
	}

	static _Elem * move( _Elem * const _First1, const _Elem * _First2, size_t _Count ) noexcept
	{
		return static_cast< _Elem * >( std::memmove( _First1, _First2, _Count * sizeof( _Elem ) ) );
	}

	static _Elem * assign( _Elem * const _First, size_t _Count, const _Elem _Ch ) noexcept
	{
		_Elem * _Next = _First;
		for( ; 0 < _Count; --_Count, ++_Next )
		{
			*_Next = _Ch;
		}

		return _First;
	}

	static constexpr void assign( _Elem & _Left, const _Elem & _Right ) noexcept
	{
		_Left = _Right;
	}

	static constexpr bool eq( const _Elem & _Left, const _Elem & _Right ) noexcept
	{
		return _Left == _Right;
	}

	static constexpr bool lt( const _Elem & _Left, const _Elem & _Right ) noexcept
	{
		return _Left < _Right;
	}

	static constexpr _Elem to_char_type( const int_type & _Meta ) noexcept
	{
		return static_cast< _Elem >( _Meta );
	}

	static constexpr int_type to_int_type( const _Elem & _Ch ) noexcept
	{
		return static_cast< int_type >( _Ch );
	}

	static constexpr bool eq_int_type( const int_type & _Left, const int_type & _Right ) noexcept
	{
		return _Left == _Right;
	}

	static constexpr int_type not_eof( const int_type & _Meta ) noexcept
	{
		return _Meta != eof() ? _Meta : !eof();
	}

	static constexpr int_type eof() noexcept
	{
		return static_cast< int_type >( EOF );
	}
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

END_XE_NAMESPACE

#endif // __TYPE_H__B9857ED9_F6EE_4A0A_8E87_0DAA433A5E40
