/*!
 * \file   Variant.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VARIANT_H__87E44F7B_D250_41E0_AEEE_7D7ECB2AAF35
#define __VARIANT_H__87E44F7B_D250_41E0_AEEE_7D7ECB2AAF35

#include "MetaID.hpp"

BEG_XE_NAMESPACE

class Variant;
template< typename T > struct VariantCreate;
template< typename T > struct VariantCast;



class XE_API Variant
{
public:
	template< typename T > friend struct VariantCreate;
	template< typename T > friend struct VariantCast;

public:
	enum class Flag : XE::uint32
	{
		INVALID			= 0,
		NIL				= 1 << 0,
		ENUM			= 1 << 1,
		FUNDAMENTAL		= 1 << 2,
		CONTAINER		= 1 << 3,
		POINTER			= 1 << 4,
		SHAREDPTR		= 1 << 5,
		PRIVATEPTR		= 1 << 6,
		HANDLE			= 1 << 7,
	};

public:
	class PrivatePtr
	{
	public:
		PrivatePtr() = default;

		virtual ~PrivatePtr() = default;

	public:
		virtual void Lock() = 0;

		virtual XE::uint64 Unlock() = 0;

		virtual void * Data() const = 0;

		virtual void * Detach() = 0;

	};

	template< typename T > class PrivatePtrTpl : public PrivatePtr
	{
	public:
		using Type = typename TypeTraits<T>::raw_t;

	public:
		PrivatePtrTpl( const T & val )
			:_Data( new Type( val ) )
		{

		}

		~PrivatePtrTpl() override
		{
			if( _Data )
			{
				delete _Data;
			}
		}

	public:
		void Lock() override
		{
			_Count++;
		}

		XE::uint64 Unlock() override
		{
			return --_Count;
		}

		void * Data() const override
		{
			return _Data;
		}

		void * Detach() override
		{
			void * p = _Data;
			_Data = nullptr;
			_Count = 0;
			return p;
		}

	private:
		Type * _Data;
		std::atomic<XE::uint64> _Count;
	};

public:
	union UnionData
	{
		UnionData() :p( nullptr ) {}
		UnionData( bool b ) :b( b ) {}
		UnionData( XE::int8 i8 ) :i8( i8 ) {}
		UnionData( XE::int16 i16 ) :i16( i16 ) {}
		UnionData( XE::int32 i32 ) :i32( i32 ) {}
		UnionData( XE::int64 i64 ) :i64( i64 ) {}
		UnionData( XE::uint8 u8 ) :u8( u8 ) {}
		UnionData( XE::uint16 u16 ) :u16( u16 ) {}
		UnionData( XE::uint32 u32 ) :u32( u32 ) {}
		UnionData( XE::uint64 u64 ) :u64( u64 ) {}
		UnionData( XE::float32  f ) :f( f ) {}
		UnionData( XE::float64 d ) :d( d ) {}
		UnionData( void * p ) :p( p ) {}
		UnionData( PrivatePtr * pp ) :pp( pp ) {}

		bool b;
		XE::int8 i8;
		XE::int16 i16;
		XE::int32 i32;
		XE::int64 i64;
		XE::uint8 u8;
		XE::uint16 u16;
		XE::uint32 u32;
		XE::uint64 u64;
		XE::float32  f;
		XE::float64 d;
		void * p;
		PrivatePtr * pp;
		XE::shared_ptr<void> * sp;
	};

public:
	Variant();

	Variant( std::nullptr_t );

	Variant( bool val );

	Variant( XE::int8 val );

	Variant( XE::int16 val );

	Variant( XE::int32 val );

	Variant( XE::int64 val );

	Variant( XE::uint8 val );

	Variant( XE::uint16 val );

	Variant( XE::uint32 val );

	Variant( XE::uint64 val );

	Variant( XE::float32 val );

	Variant( XE::float64 val );

	Variant( const Variant & val );

	template< typename T > Variant( T & val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if constexpr( std::is_shared_ptr_v<T> )
		{
			VariantCreate< XE::shared_ptr< type > >::Create( this, val );
		}
		else
		{
			VariantCreate<type>::Create( this, val );
		}

		Lock();
	}

	template< typename T > Variant( const T & val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if constexpr( std::is_shared_ptr_v<T> )
		{
			VariantCreate< XE::shared_ptr< type > >::Create( this, val );
		}
		else
		{
			VariantCreate<type>::Create( this, val );
		}

		Lock();
	}

	template< typename T > Variant( T * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		_Type = TypeID<type>::Get();
		_Data.p = (void * )val;
		_Flag = Variant::Flag::POINTER;
	}

	template< typename T > Variant( const T * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		_Type = TypeID<type>::Get();
		_Data.p = (void * )val;
		_Flag = Variant::Flag::POINTER;
	}

	Variant( IMetaTypePtr meta, UnionData data, XE::Variant::Flag flag );

	Variant( IMetaTypePtr meta, XE::shared_ptr<void> data, XE::Variant::Flag flag );

	~Variant();

public:
	Variant & operator=( const Variant & val );

public:
	bool operator <( const Variant & val ) const;

	bool operator >( const Variant & val ) const;

	bool operator <=( const Variant & val ) const;

	bool operator >=( const Variant & val ) const;

	bool operator ==( const Variant & val ) const;

	bool operator !=( const Variant & val ) const;

public:
	bool IsNull() const;

	bool IsEnum() const;

	bool IsInvalid() const;

	bool IsPointer() const;

	bool IsContainer() const;

	bool IsSharedPtr() const;

	bool IsPrivatePtr() const;

	bool IsFundamental() const;

	bool IsCanConvert( IMetaTypePtr val ) const;

public:
	bool ToBool() const;

	XE::int8 ToInt8() const;

	XE::int16 ToInt16() const;

	XE::int32 ToInt32() const;

	XE::int64 ToInt64() const;

	XE::uint8 ToUInt8() const;

	XE::uint16 ToUInt16() const;

	XE::int32 ToUInt32() const;

	XE::uint64 ToUInt64() const;

	XE::float32 ToFloat32() const;

	XE::float64 ToFloat64() const;

	void * ToPointer() const;

public:
	Flag GetFlag() const;

	UnionData GetData() const;

	IMetaTypePtr GetType() const;

public:
	void Reset();

	void * Detach();

	XE::shared_ptr<void> DetachPtr();

public:
	template< typename T > T Value() const
	{
		return VariantCast<T>::Cast( this );
	}

private:
	void Lock();

	void Unlock();

private:
	static XE::shared_ptr<void> * RegisterSharedPtr( const XE::shared_ptr<void> & p );

private:
	Flag _Flag;
	UnionData _Data;
	IMetaTypePtr _Type;
};



using VariantList =  XE::List<Variant>;
using VariantDeque = XE::Deque<Variant>;
using VariantStack = XE::Stack<Variant>;
using VariantQueue = XE::Queue<Variant>;
using VariantArray = XE::Array<Variant>;
using VariantPair = XE::Pair<Variant, Variant>;
using VariantSet =  XE::Set<Variant>;
using VariantMap =  XE::Map<Variant, Variant>;
using VariantMultiSet = XE::MultiSet<Variant>;
using VariantMultiMap = XE::MultiMap<Variant, Variant>;



class XE_API VariantException : public RuntimeException
{
public:
	VariantException( const Variant & val, const String & msg );

	~VariantException();

public:
	virtual char const * What() const;

public:
	Variant GetVariant() const;

private:
	String _Msg;
	Variant _Value;
};



template< typename T > struct VariantCreate
{
	static void Create( Variant * var, const T & val )
	{
		using type = typename TypeTraits<T>::raw_t;

		var->_Type = TypeID<type>::Get();

		if constexpr( std::is_enum_v<type> )
		{
			var->_Data.i64 = ( XE::int64 )val;
			var->_Flag = Variant::Flag::ENUM;
		}
		else
		{
			var->_Data.pp = new Variant::PrivatePtrTpl<type>( val );
			var->_Flag = Variant::Flag::PRIVATEPTR;
		}
	}
};

template<> struct VariantCreate<Variant>
{
	static void Create( Variant * var, const Variant & val )
	{
		var->_Type = val._Type;
		var->_Data = val._Data;
		var->_Flag = val._Flag;
	}
};

template< typename T > struct VariantCreate<XE::shared_ptr<T>>
{
	static void Create( Variant * var, const XE::shared_ptr<T> & val )
	{
		using type = typename TypeTraits<T>::raw_t;

		var->_Type = TypeID<type>::Get();
		var->_Data.sp = Variant::RegisterSharedPtr( val );
		var->_Flag = Variant::Flag::SHAREDPTR;
	}
};


template< typename T > struct VariantCast
{
	static T Cast( const Variant * val )
	{
		if constexpr( std::is_enum_v<T> )
		{
			if( val->GetFlag() == XE::Variant::Flag::ENUM && TypeID<T>::Get() == val->GetType() )
			{
				return (T )( val->_Data.i64 );
			}
		}

		return VariantCast< T & >::Cast( val );
	}
};

template< typename T > struct VariantCast<T &>
{
	static T & Cast( const Variant * val )
	{
		if( !val->IsFundamental() )
		{
			return *( VariantCast< T * >::Cast( val ) );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<const T &>
{
	static const T & Cast( const Variant * val )
	{
		return VariantCast< T & >::Cast( val );
	}
};

template< typename T > struct VariantCast<T *>
{
	static T * Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if( ( val->IsPointer() || val->IsSharedPtr() || val->IsPrivatePtr() ) && val->IsCanConvert( TypeID< type >::Get() ) )
		{
			return (T * )val->ToPointer();
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<const T *>
{
	static const T * Cast( const Variant * val )
	{
		return VariantCast< T * >::Cast( val );
	}
};

template< typename T > struct VariantCast<XE::shared_ptr<T>>
{
	static XE::shared_ptr<T> Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if( val->IsSharedPtr() && val->IsCanConvert( TypeID< type >::Get() ) )
		{
			return SP_CAST<T>( *( val->_Data.sp ) );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<XE::shared_ptr<T> &>
{
	static XE::shared_ptr<T> & Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if( val->IsSharedPtr() && val->IsCanConvert( TypeID< type >::Get() ) )
		{
			return *( ( XE::shared_ptr<T> * )( val->_Data.sp ) );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<const XE::shared_ptr<T> &>
{
	static const XE::shared_ptr<T> & Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if( val->IsSharedPtr() && val->IsCanConvert( TypeID< type >::Get() ) )
		{
			return *( ( XE::shared_ptr<T> * )( val->_Data.sp ) );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct VariantCast<Variant>
{
	static Variant Cast( const Variant * val )
	{
		return *val;
	}
};

template<> struct VariantCast<Variant &>
{
	static Variant & Cast( const Variant * val )
	{
		return *( const_cast< Variant * >( val ) );
	}
};

template<> struct VariantCast<const Variant &>
{
	static const Variant & Cast( const Variant * val )
	{
		return *( const_cast< Variant * >( val ) );
	}
};

template<> struct VariantCast<bool>
{
	static bool Cast( const Variant * val )
	{
		return val->ToBool();
	}
};

template<> struct VariantCast<XE::int8>
{
	static XE::int8 Cast( const Variant * val )
	{
		return val->ToInt8();
	}
};

template<> struct VariantCast<XE::int16>
{
	static XE::int16 Cast( const Variant * val )
	{
		return val->ToInt16();
	}
};

template<> struct VariantCast<XE::int32>
{
	static XE::int32 Cast( const Variant * val )
	{
		return val->ToInt32();
	}
};

template<> struct VariantCast<XE::int64>
{
	static XE::int64 Cast( const Variant * val )
	{
		return val->ToInt64();
	}
};

template<> struct VariantCast<XE::uint8>
{
	static XE::uint8 Cast( const Variant * val )
	{
		return val->ToUInt8();
	}
};

template<> struct VariantCast<XE::uint16>
{
	static XE::uint16 Cast( const Variant * val )
	{
		return val->ToUInt16();
	}
};

template<> struct VariantCast<XE::uint32>
{
	static XE::uint32 Cast( const Variant * val )
	{
		return val->ToUInt32();
	}
};

template<> struct VariantCast<XE::uint64>
{
	static XE::uint64 Cast( const Variant * val )
	{
		return val->ToUInt64();
	}
};

template<> struct VariantCast<XE::float32>
{
	static XE::float32 Cast( const Variant * val )
	{
		return val->ToFloat32();
	}
};

template<> struct VariantCast<XE::float64>
{
	static XE::float64 Cast( const Variant * val )
	{
		return val->ToFloat64();
	}
};

END_XE_NAMESPACE

#endif // __VARIANT_H__87E44F7B_D250_41E0_AEEE_7D7ECB2AAF35
