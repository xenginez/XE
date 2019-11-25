/*!
 * \file   Handle.hpp
 *
 * \author ZhengYuanQing
 * \date   2019/02/24
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __HANDLE_HPP__7920C1A9_2044_45F0_84C4_221961C006AF
#define __HANDLE_HPP__7920C1A9_2044_45F0_84C4_221961C006AF

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T > class Handle
{
public:
	using Type = T;

public:
	static const Handle< T > Invalid;

public:
	Handle()
		:_value( Invalid._value )
	{
	}

	Handle( XE::uint64 val )
		:_value( val )
	{
	}

	Handle( const Handle& val )
		:_value( val._value )
	{
	}

public:
	operator bool() const
	{
		return _value != Invalid._value;
	}

	Handle& operator=( const Handle& val )
	{
		_value = val._value;
		return *this;
	}

public:
	bool operator<( XE::uint64 val ) const
	{
		return _value < val;
	}

	bool operator>( XE::uint64 val ) const
	{
		return _value > val;
	}

	bool operator<=( XE::uint64 val ) const
	{
		return _value <= val;
	}

	bool operator>=( XE::uint64 val ) const
	{
		return _value >= val;
	}

	bool operator!=( XE::uint64 val ) const
	{
		return _value != val;
	}

	bool operator==( XE::uint64 val ) const
	{
		return _value == val;
	}

public:
	bool operator<( const Handle& val ) const
	{
		return _value < val._value;
	}

	bool operator>( const Handle& val ) const
	{
		return _value > val._value;
	}

	bool operator<=( const Handle& val ) const
	{
		return _value <= val._value;
	}

	bool operator>=( const Handle& val ) const
	{
		return _value >= val._value;
	}

	bool operator!=( const Handle& val ) const
	{
		return _value != val._value;
	}

	bool operator==( const Handle& val ) const
	{
		return _value == val._value;
	}

public:
	XE::uint64 GetValue() const
	{
		return _value;
	}

private:
	XE::uint64 _value;
};

template< typename T > struct VariantCreate<Handle<T>>
{
	static void Create( Variant * var, const Handle<T>& val )
	{
		using type = typename TypeTraits<Handle<T>>::raw_t;

		var->_Meta = MetaID<type>::Get();
		var->_Data.u64 = val.GetValue();
	}
};

template< typename T > struct VariantCast<Handle<T>>
{
	static Handle<T> * Cast( const Variant * val )
	{
		using type = typename TypeTraits<Handle<T>>::raw_t;

		if ( val->GetMeta() == MetaID< type >::Get() )
		{
			return (Handle<T>*)( &( val->_Data.u64 ) );
		}

		throw VariantException( *val, "cast fail" );
	}
};

END_XE_NAMESPACE

template< typename T > bool operator<( XE::uint64 left, XE::Handle< T > right )
{
	return left < right.GetValue();
}

template< typename T > bool operator>( XE::uint64 left, XE::Handle< T > right )
{
	return left > right.GetValue();
}

template< typename T > bool operator<=( XE::uint64 left, XE::Handle< T > right )
{
	return left <= right.GetValue();
}

template< typename T > bool operator>=( XE::uint64 left, XE::Handle< T > right )
{
	return left >= right.GetValue();
}

template< typename T > bool operator!=( XE::uint64 left, XE::Handle< T > right )
{
	return left != right.GetValue();
}

template< typename T > bool operator==( XE::uint64 left, XE::Handle< T > right )
{
	return left == right.GetValue();
}

template< typename T > const XE::Handle<T> XE::Handle<T>::Invalid( std::numeric_limits<XE::uint64>::max() );

#endif // __HANDLE_HPP__7920C1A9_2044_45F0_84C4_221961C006AF
