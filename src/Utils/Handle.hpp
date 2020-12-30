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

template< typename T > class Handle;
template< typename T > class RefHandle;
template< typename T > class HandleAllocator;
template< typename T, XE::uint64 _Max = std::numeric_limits<XE::uint64>::max() > class QueueHandleAllocator;
template< typename T, XE::uint64 _Max = std::numeric_limits<XE::uint64>::max() > class ConcurrentHandleAllocator;

template< typename T > class Handle
{
	template< typename T > friend struct Serializable;

	template< typename T > friend class HandleAllocator;

	template< typename T, XE::uint64 _Max > friend class FreeHandleAlloctor;

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


template< typename T > class RefHandle< XE::Handle< T > >
{
public:
	using value_type = XE::Handle< T >;
	using inc_function_type = std::function< void( XE::Handle< T > ) >;
	using dec_function_type = std::function< void( XE::Handle< T > ) >;

public:
	RefHandle()
	{
	}

	RefHandle( std::nullptr_t )
	{
	}

	RefHandle( const value_type & val, const inc_function_type & inc, const dec_function_type & dec )
		:_Value( val ), _Inc( inc ), _Dec( dec )
	{
		_Inc( _Value );
	}

	RefHandle( const RefHandle & val )
		:_Value( val._Value ), _Inc( val._Inc ), _Dec( val._Dec )
	{
		_Inc( _Value );
	}

	~RefHandle()
	{
		_Dec( _Value );
	}

public:
	RefHandle & operator=( std::nullptr_t )
	{
		if( _Value )
		{
			_Dec( _Value );
		}

		_Inc = nullptr;
		_Dec = nullptr;
		_Value = value_type::Invalid;
	}

	RefHandle & operator=( const RefHandle & val )
	{
		if( _Value )
		{
			_Dec( _Value );
		}

		_Inc = val._Inc;
		_Dec = val._Dec;
		_Value = val._Value;

		if( _Value )
		{
			_Inc( _Value );
		}

		return *this;
	}

	value_type & operator*()
	{
		return get();
	}

	const value_type & operator*() const
	{
		return get();
	}

	operator value_type & ( )
	{
		return get();
	}

	operator const value_type & ( ) const
	{
		return get();
	}

public:
	value_type & get()
	{
		return _Value;
	}

	const value_type & get() const
	{
		return _Value;
	}

	void reset()
	{
		if( _Value )
		{
			_Dec( _Value );
		}

		_Inc = nullptr;
		_Dec = nullptr;
		_Value = value_type::Invalid;
	}

private:
	value_type _Value;
	inc_function_type _Inc;
	dec_function_type _Dec;
};


template< typename T > struct VariantCreate< Handle< T > >
{
	static void Create( Variant * var, const Handle<T> & val )
	{
		using type = typename TypeTraits<Handle<T>>::raw_t;

		var->_Type = ::XE_TypeID<type>::Get();
		var->_Data.u64 = val.GetValue();
		var->_Flag = Variant::Flag::HANDLE;
	}
};

template< typename T > struct VariantCast< Handle< T > >
{
	static Handle<T> Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == ::XE_TypeID< Handle<T> >::Get() )
		{
			return val->_Data.u64;
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast< Handle<T> * >
{
	static Handle<T> * Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == ::XE_TypeID< Handle<T> >::Get() )
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

template< typename T > class HandleAllocator< Handle< T > >
{
public:
	HandleAllocator()
		:_Value( 0 )
	{ }

	HandleAllocator( XE::uint64 val )
		:_Value( val )
	{ }

public:
	XE::Handle< T > Alloc()
	{
		return _Value++;
	}

	void Reset( XE::uint64 val = 0 )
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

template< typename T, XE::uint64 _Max > class QueueHandleAllocator< Handle< T >, _Max >
{
public:
	QueueHandleAllocator()
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

		for( XE::uint64 i = 0; i < _Max; ++i )
		{
			_Queue.push( i );
		}
	}

private:
	std::priority_queue<XE::uint64, XE::Array<XE::uint64>> _Queue;
};

template< typename T, XE::uint64 _Max > class ConcurrentHandleAllocator< Handle< T >, _Max >
{
public:
	ConcurrentHandleAllocator()
	{
		Reset();
	}

public:
	XE::Handle< T > Alloc()
	{
		if( _Pos < _Max )
		{
			XE::uint64 pos = 0;
			do 
			{
				pos = _Pos;
				if( _Pos >= _Max )
				{
					return XE::Handle< T >::Invalid;
				}
			} while( !_Pos.compare_exchange_weak( pos, pos + 1 ) );

			XE::uint64 handle = _Dense[pos];
			_Sparse[handle] = pos;
			return handle;
		}

		return XE::Handle< T >::Invalid;
	}

	void Free( XE::Handle< T > handle )
	{
		XE::uint64 pos = 0;
		do
		{
			pos = _Pos;
		} while( !_Pos.compare_exchange_weak( pos, pos - 1 ) );

		XE::uint64 index = _Sparse[handle.GetValue()];
		XE::uint64 temp = _Dense[pos];
		_Dense[pos] = handle.GetValue();
		_Sparse[temp] = index;
		_Dense[index] = temp;
	}

	bool IsValid( XE::Handle< T > handle ) const
	{
		return index < _Pos && _Dense[_Sparse[handle.GetValue()]] == handle.GetValue();
	}

	void Reset()
	{
		_Pos = 0;

		for( int i = 0; i < _Max; ++i )
		{
			_Dense[i] = i;
		}
	}

private:
	std::atomic<XE::uint64> _Pos;
	std::array<XE::uint64, _Max> _Dense;
	std::array<XE::uint64, _Max> _Sparse;
};

template< typename T > struct VariantCreate< HandleAllocator< T > >
{
	static void Create( Variant * var, const HandleAllocator< T > & val )
	{
		using type = typename TypeTraits< HandleAllocator< T > >::raw_t;

		var->_Type = ::XE_TypeID<type>::Get();
		var->_Data.u64 = val.GetValue();
		var->_Flag = Variant::Flag::HANDLE;
	}
};

template< typename T > struct VariantCast< HandleAllocator< T > >
{
	static HandleAllocator< T > Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == ::XE_TypeID< HandleAllocator< T > >::Get() )
		{
			return val->_Data.u64;
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast< HandleAllocator< T > * >
{
	static HandleAllocator< T > * Cast( const Variant * val )
	{
		if( ( val->GetFlag() == Variant::Flag::HANDLE ) && val->GetType() == ::XE_TypeID< HandleAllocator< T > >::Get() )
		{
			return ( HandleAllocator< T > * ) & ( val->_Data.u64 );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct Serializable< HandleAllocator< T > >
{
public:
	static void Serialize( Archive & arc, HandleAllocator< T > * val )
	{
		XE::uint64 value = val->GetValue();
		auto nvp = XE::Archive::NVP( "@value", value );
		arc & nvp;

		*val = HandleAllocator< T >( nvp.Value );
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

#define DECL_HANDLE( _DLL_EXPORT, NAME ) class NAME; using NAME##Handle = XE::Handle< NAME >; DECL_META_CLASS( _DLL_EXPORT, NAME##Handle );using NAME##HandleAllocator = XE::HandleAllocator< XE::Handle< NAME > >; DECL_META_CLASS( _DLL_EXPORT, NAME##HandleAllocator );

#endif // __HANDLE_HPP__7920C1A9_2044_45F0_84C4_221961C006AF
