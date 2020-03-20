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
		:_value( std::numeric_limits<XE::uint64>::max() )
	{
	}

	Handle( XE::uint64 val )
		:_value( val )
	{
	}

	Handle( const Handle & val )
		:_value( val._value )
	{
	}

public:
	operator bool() const
	{
		return _value != std::numeric_limits<XE::uint64>::max();
	}

	Handle & operator=( const Handle & val )
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
	bool operator<( const Handle & val ) const
	{
		return _value < val._value;
	}

	bool operator>( const Handle & val ) const
	{
		return _value > val._value;
	}

	bool operator<=( const Handle & val ) const
	{
		return _value <= val._value;
	}

	bool operator>=( const Handle & val ) const
	{
		return _value >= val._value;
	}

	bool operator!=( const Handle & val ) const
	{
		return _value != val._value;
	}

	bool operator==( const Handle & val ) const
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
	static void Create( Variant * var, const Handle<T> & val )
	{
		using type = typename TypeTraits<Handle<T>>::raw_t;

		var->_Type = TypeID<type>::Get();
		var->_Data.u64 = val.GetValue();
		var->_Flag = Variant::Flag::HANDLE;
	}
};

template< typename T > struct VariantCast<Handle<T>>
{
	static Handle<T> Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == TypeID< Handle<T> >::Get() )
		{
			return val->_Data.u64;
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<Handle<T> *>
{
	static Handle<T> * Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == TypeID< Handle<T> >::Get() )
		{
			return ( Handle<T> * ) & ( val->_Data.u64 );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct Serializable< Handle< T > >
{
public:
	static void Serialize( Archive & arc, Handle< T > * val )
	{
		XE::uint64 value = val->GetValue();

		arc & value;

		*val = Handle< T >( value );
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
