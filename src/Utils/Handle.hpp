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

template< typename T > class HandleAlloctor;
template< typename T, XE::uint64 Max > class FreeHandleAlloctor;

template< typename T > class Handle
{
	template< typename T > friend struct Serializable;

	template< typename T > friend class HandleAlloctor;

	template< typename T, XE::uint64 Max > friend class FreeHandleAlloctor;

public:
	using Type = T;

public:
	static const Handle< T > Invalid;

public:
	Handle()
		:_value( std::numeric_limits<XE::uint64>::max() )
	{
	}

	Handle( const Handle & val )
		:_value( val._value )
	{
	}

private:
	Handle( XE::uint64 val )
		:_value( val )
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
		if( !_Queue.empty() )
		{
			auto handle = _Queue.top();
			_Queue.pop();
			return handle;
		}

		return XE::Handle< T >::Invalid;
	}

	void Free( XE::Handle< T > handle )
	{
		_Queue.push( handle.GetValue() );
	}

	void Reset()
	{
		_Queue = {};

		for( XE::uint64 i = 0; i < Max; ++i )
		{
			_Queue.push( i );
		}
	}

private:
	std::priority_queue<XE::uint64, XE::Array<XE::uint64>> _Queue;
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
