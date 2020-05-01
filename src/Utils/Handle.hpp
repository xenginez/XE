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
		auto nvp = XE::Archive::NVP( "@value", value );
		arc & nvp;

		*val = Handle< T >( nvp.Value );
	}
};

template< typename T > class HandleAlloctor
{
public:
	HandleAlloctor()
		:_Value( 0 )
	{

	}

	HandleAlloctor( XE::uint64 val )
		:_Value( val )
	{ }

public:
	XE::Handle< T > Alloc()
	{
		return _Value++;
	}

	void Reset( XE::uint64 val )
	{
		_Value = val;
	}

	XE::uint64 GetValue() const
	{
		return _Value;
	}

private:
	XE::uint64 _Value;
};

template< typename T > struct VariantCreate<HandleAlloctor<T>>
{
	static void Create( Variant * var, const HandleAlloctor<T> & val )
	{
		using type = typename TypeTraits<HandleAlloctor<T>>::raw_t;

		var->_Type = TypeID<type>::Get();
		var->_Data.u64 = val.GetValue();
		var->_Flag = Variant::Flag::HANDLE;
	}
};

template< typename T > struct VariantCast<HandleAlloctor<T>>
{
	static HandleAlloctor<T> Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == TypeID< HandleAlloctor<T> >::Get() )
		{
			return val->_Data.u64;
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<HandleAlloctor<T> *>
{
	static Handle<T> * Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == TypeID< HandleAlloctor<T> >::Get() )
		{
			return ( HandleAlloctor<T> * ) & ( val->_Data.u64 );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct Serializable< HandleAlloctor< T > >
{
public:
	static void Serialize( Archive & arc, HandleAlloctor< T > * val )
	{
		XE::uint64 value = val->GetValue();
		auto nvp = XE::Archive::NVP( "@value", value );
		arc & nvp;

		*val = HandleAlloctor< T >( nvp.Value );
	}
};

template< typename T, XE::uint64 Max > class FreeHandleAlloctor
{
public:
	FreeHandleAlloctor()
	{
		Reset();
	}

public:
	XE::Handle< T > Alloc()
	{
		if( _Pos < Max )
		{
			XE::uint64 index = _Pos++;

			_Next[_Prev[index]] = index;

			return _Prev[index];
		}

		return XE::Handle< T >::Invalid;
	}

	void Free( XE::Handle< T > handle )
	{
		XE::uint64 _handle = handle.GetValue();

		XE::uint64 index = _Next[_handle];
		
		--_Pos;
		
		XE::uint64 temp = _Prev[_Pos];

		_Prev[_Pos] = _handle;
		_Next[temp] = index;
		_Prev[index] = temp;
	}

	bool IsValid( XE::Handle< T > handle )
	{
		XE::uint64 _handle = handle.GetValue();

		uint16_t  index = _Next[_handle];

		return index < _Pos && _Prev[index] == _handle;
	}

	void Reset()
	{
		_Pos = 0;

		for( XE::uint64 i = 0; i < Max; ++i )
		{
			_Prev[i] = i;
		}
	}

private:
	XE::uint64 _Pos;
	XE::uint64 _Prev[Max];
	XE::uint64 _Next[Max];
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
