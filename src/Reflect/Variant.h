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

#include <atomic>

#include "TypeID.hpp"

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
		INVALID = 0,
		NIL = 1 << 0,
		ENUM = 1 << 1,
		FUNDAMENTAL = 1 << 2,
		CONTAINER = 1 << 3,
		POINTER = 1 << 4,
		SHAREDPTR = 1 << 5,
		PRIVATEPTR = 1 << 6,
		HANDLE = 1 << 7,
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
		XE::SharedPtr<void> * sp;
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

	Variant( const char * val );

	Variant( const Variant & val );

	template< typename T > Variant( T * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if constexpr( std::is_same_v<type, Variant> )
		{
			_Data = val->_Data;
			_Flag = val->_Flag;
			_Type = val->_Type;
		}
		else
		{
			_Type = ::XE_TypeID< type >::Get( val );
			_Data.p = (void * )val;
			_Flag = Variant::Flag::POINTER;
		}

		Lock();
	}

	template< typename T > Variant( const T * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if constexpr( std::is_same_v<type, Variant> )
		{
			_Data = val->_Data;
			_Flag = val->_Flag;
			_Type = val->_Type;
		}
		else
		{
			_Type = TypeID<type>::Get( val );
			_Data.p = (void * )val;
			_Flag = Variant::Flag::POINTER;
		}

		Lock();
	}

	template< typename T > Variant( const T & val )
	{
		VariantCreate< T >::Create( this, val );

		Lock();
	}

	Variant( IMetaTypePtr meta, UnionData data, XE::Variant::Flag flag );

	Variant( IMetaTypePtr meta, XE::SharedPtr<void> data, XE::Variant::Flag flag );

	~Variant();

public:
	Variant & operator=( const Variant & val );

public:
	Variant operator!() const;

	Variant operator~() const;

	Variant operator-() const;

	Variant operator++();

	Variant operator--();

	Variant operator++(int);

	Variant operator--(int);

public:
	Variant operator+( const Variant & val )const;

	Variant operator-( const Variant & val )const;

	Variant operator*( const Variant & val )const;

	Variant operator/( const Variant & val )const;

	Variant operator%( const Variant & val )const;

	Variant operator^( const Variant & val )const;

	Variant operator&( const Variant & val )const;

	Variant operator|( const Variant & val )const;

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

	XE::Array<XE::Variant> ToArray() const;

public:
	Flag GetFlag() const;

	UnionData GetData() const;

	IMetaTypePtr GetType() const;

public:
	void Reset();

	void * Detach();

public:
	template< typename T > T Value() const
	{
		return VariantCast<T>::Cast( this );
	}

private:
	void Lock();

	void Unlock();

private:
	static XE::SharedPtr<void> * RegisterSharedPtr( const XE::SharedPtr<void> & p );

private:
	Flag _Flag;
	UnionData _Data;
	IMetaTypePtr _Type;
};

END_XE_NAMESPACE

namespace std
{
	template <> struct hash< XE::Variant >
	{
		typedef XE::Variant argument_type;
		typedef XE::uint64 result_type;

		XE::uint64 operator()( const XE::Variant & _Keyval ) const noexcept
		{
			return std::hash<void *>()( _Keyval.ToPointer() );
		}
	};
}

BEG_XE_NAMESPACE

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
using VariantUnorderedSet = XE::UnorderedSet<Variant>;
using VariantUnorderedMap = XE::UnorderedMap<Variant, Variant>;
using VariantUnorderedMultiSet = XE::UnorderedMultiSet<Variant>;
using VariantUnorderedMultiMap = XE::UnorderedMultiMap<Variant, Variant>;


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
		if constexpr( std::is_enum_v<T> )
		{
			var->_Type = ::XE_TypeID< T >::Get();
			var->_Data.i64 = ( XE::int64 )val;
			var->_Flag = Variant::Flag::ENUM;
		}
		else if constexpr( std::is_shared_ptr_v<T> )
		{
			var->_Type = ::XE_TypeID< T >::Get( &val );
			if( val.get() )
			{
				var->_Data.sp = Variant::RegisterSharedPtr( val );
			}
			var->_Flag = Variant::Flag::SHAREDPTR;
		}
		else
		{
			var->_Type = ::XE_TypeID< T >::Get( &val );
			var->_Data.pp = new Variant::PrivatePtrTpl<T>( val );
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

template< typename T > struct VariantCreate< XE::BasicMemoryView< T > >
{
	static void Create( Variant * var, const XE::BasicMemoryView< T > & val )
	{
		var->_Type = ::XE_TypeID< XE::MemoryView >::Get( nullptr );
		var->_Data.pp = new Variant::PrivatePtrTpl<XE::MemoryView>( XE::MemoryView( ( const char * )( val.data() ), val.size() * sizeof( T ) ) );
		var->_Flag = Variant::Flag::PRIVATEPTR;
	}
};

template< typename T > struct VariantCreate< std::basic_string< T > >
{
	static void Create( Variant * var, const std::basic_string< T > & val )
	{
		VariantCreate<XE::String>::Create( var, val );
	}
};

template< typename T > struct VariantCreate< XE::List< T > >
{
	static void Create( Variant * var, const XE::List< T > & val )
	{
		VariantList list;

		for( const auto & it : val )
		{
			list.push_back( it );
		}

		var->_Type = ::XE_TypeID< VariantList >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantList>( list );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::Deque< T > >
{
	static void Create( Variant * var, const XE::Deque< T > & val )
	{
		VariantDeque deque;

		for( const auto & it : val )
		{
			deque.push_back( it );
		}

		var->_Type = ::XE_TypeID< VariantDeque >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantDeque>( deque );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::Stack< T > >
{
	static void Create( Variant * var, const XE::Stack< T > & val )
	{
		VariantStack stack;

		for( const auto & it : val )
		{
			stack.push( it );
		}

		var->_Type = ::XE_TypeID< VariantStack >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantStack>( stack );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::Queue< T > >
{
	static void Create( Variant * var, const XE::Queue< T > & val )
	{
		VariantQueue queue;

		for( const auto & it : val )
		{
			queue.push( it );
		}

		var->_Type = ::XE_TypeID< VariantQueue >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantQueue>( queue );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::Array< T > >
{
	static void Create( Variant * var, const XE::Array< T > & val )
	{
		VariantArray array;

		for( const auto & it : val )
		{
			array.push_back( it );
		}

		var->_Type = ::XE_TypeID< VariantArray >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantArray>( array );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename K, typename V > struct VariantCreate< XE::Pair< K, V > >
{
	static void Create( Variant * var, const XE::Pair< K, V > & val )
	{
		VariantPair pair;

		pair.first = val.first;
		pair.second = val.second;

		var->_Type = ::XE_TypeID< VariantPair >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantPair>( pair );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::Set< T > >
{
	static void Create( Variant * var, const XE::Set< T > & val )
	{
		VariantSet set;

		for( const auto & it : val )
		{
			set.insert( it );
		}

		var->_Type = ::XE_TypeID< VariantSet >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantSet>( set );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename K, typename V > struct VariantCreate< XE::Map< K, V > >
{
	static void Create( Variant * var, const XE::Map< K, V > & val )
	{
		VariantMap map;

		for( const auto & it : val )
		{
			VariantPair pair;

			pair.first = it.first;
			pair.second = it.second;

			map.insert( pair );
		}

		var->_Type = ::XE_TypeID< VariantMap >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantMap>( map );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::MultiSet< T > >
{
	static void Create( Variant * var, const XE::MultiSet< T > & val )
	{
		VariantMultiSet multiset;

		for( const auto & it : val )
		{
			multiset.insert( it );
		}

		var->_Type = ::XE_TypeID< VariantMultiSet >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantMultiSet>( multiset );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename K, typename V > struct VariantCreate< XE::MultiMap< K, V > >
{
	static void Create( Variant * var, const XE::MultiMap< K, V > & val )
	{
		VariantMultiMap multimap;

		for( const auto & it : val )
		{
			VariantPair pair;

			pair.first = it.first;
			pair.second = it.second;

			multimap.insert( pair );
		}

		var->_Type = ::XE_TypeID< VariantMultiMap >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantMultiMap>( multimap );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::UnorderedSet< T > >
{
	static void Create( Variant * var, const XE::UnorderedSet< T > & val )
	{
		VariantUnorderedSet set;

		for( const auto & it : val )
		{
			set.insert( it );
		}

		var->_Type = ::XE_TypeID< VariantUnorderedSet >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantUnorderedSet>( set );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename K, typename V > struct VariantCreate< XE::UnorderedMap< K, V > >
{
	static void Create( Variant * var, const XE::UnorderedMap< K, V > & val )
	{
		VariantUnorderedMap map;

		for( const auto & it : val )
		{
			VariantPair pair;

			pair.first = it.first;
			pair.second = it.second;

			map.insert( pair );
		}

		var->_Type = ::XE_TypeID< VariantUnorderedMap >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantUnorderedMap>( map );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename T > struct VariantCreate< XE::UnorderedMultiSet< T > >
{
	static void Create( Variant * var, const XE::UnorderedMultiSet< T > & val )
	{
		VariantUnorderedMultiSet multiset;

		for( const auto & it : val )
		{
			multiset.insert( it );
		}

		var->_Type = ::XE_TypeID< VariantUnorderedMultiSet >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantUnorderedMultiSet>( multiset );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};

template< typename K, typename V > struct VariantCreate< XE::UnorderedMultiMap< K, V > >
{
	static void Create( Variant * var, const XE::UnorderedMultiMap< K, V > & val )
	{
		VariantUnorderedMultiMap multimap;

		for( const auto & it : val )
		{
			VariantPair pair;

			pair.first = it.first;
			pair.second = it.second;

			multimap.insert( pair );
		}

		var->_Type = ::XE_TypeID< VariantUnorderedMultiMap >::Get();
		var->_Data = new Variant::PrivatePtrTpl<VariantUnorderedMultiMap>( multimap );
		var->_Flag = Variant::Flag::CONTAINER;
	}
};


template< typename T > struct VariantCast
{
	static T Cast( const Variant * val )
	{
		if constexpr( std::is_enum_v<T> )
		{
			if( val->GetFlag() == XE::Variant::Flag::ENUM && ::XE_TypeID< T >::Get() == val->GetType() )
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

		if( ( val->IsPointer() || val->IsSharedPtr() || val->IsPrivatePtr() ) && val->IsCanConvert( ::XE_TypeID< type >::Get() ) )
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

template< typename T > struct VariantCast<XE::SharedPtr<T>>
{
	static XE::SharedPtr<T> Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if( val->IsSharedPtr() && val->IsCanConvert( ::XE_TypeID< type >::Get() ) )
		{
			return SP_CAST<T>( *( val->_Data.sp ) );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<XE::SharedPtr<T> &>
{
	static XE::SharedPtr<T> & Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if( val->IsSharedPtr() && val->IsCanConvert( ::XE_TypeID< type >::Get() ) )
		{
			return *( ( XE::SharedPtr<T> * )( val->_Data.sp ) );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<const XE::SharedPtr<T> &>
{
	static const XE::SharedPtr<T> & Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if( val->IsSharedPtr() && val->IsCanConvert( ::XE_TypeID< type >::Get() ) )
		{
			return *( ( XE::SharedPtr<T> * )( val->_Data.sp ) );
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

template<> struct VariantCast<XE::VariantArray>
{
	static XE::VariantArray Cast( const Variant * val )
	{
		return val->ToArray();
	}
};

template< typename T > struct VariantCast< XE::BasicMemoryView< T > >
{
	static XE::BasicMemoryView< T > Cast( const Variant * val )
	{
		auto m = VariantCast<XE::MemoryView>::Cast( val );
		return { static_cast< const T * >( m.data() ), m.size() / sizeof( T ) };
	}
};

template< typename T > struct VariantCast< std::basic_string<T> >
{
	static std::basic_string<T> Cast( const Variant * val )
	{
		return VariantCast<XE::String &>::Cast( val ).std_str();
	}
};

template< typename T > struct VariantCast<const std::basic_string< T > &>
{
	static const std::basic_string< T > & Cast( const Variant * val )
	{
		return VariantCast<const XE::String &>::Cast( val ).std_str();
	}
};

template< typename T > struct VariantCast< XE::List< T > >
{
	static XE::List< T > Cast( const Variant * val )
	{
		XE::List< T > list;

		auto v_list = val->ToArray();
		for( const auto & it : v_list )
		{
			list.push_back( it.Value< T >() );
		}

		return list;
	}
};

template< typename T > struct VariantCast< XE::Deque< T > >
{
	static XE::Deque< T > Cast( const Variant * val )
	{
		XE::Deque< T > deque;

		auto v_deque = val->ToArray();
		for( const auto & it : v_deque )
		{
			deque.push_back( it.Value< T >() );
		}

		return deque;
	}
};

template< typename T > struct VariantCast< XE::Stack< T > >
{
	static XE::Stack< T > Cast( const Variant * val )
	{
		XE::Stack< T > stack;

		auto v_stack = val->ToArray();
		for( const auto & it : v_stack )
		{
			stack.push( it.Value< T >() );
		}

		return stack;
	}
};

template< typename T > struct VariantCast< XE::Queue< T > >
{
	static XE::Queue< T > Cast( const Variant * val )
	{
		XE::Queue< T > queue;

		auto v_queue = val->ToArray();
		for( const auto & it : v_queue )
		{
			queue.push( it.Value< T >() );
		}

		return queue;
	}
};

template< typename T > struct VariantCast< XE::Array< T > >
{
	static XE::Array< T > Cast( const Variant * val )
	{
		XE::Array< T > array;

		const VariantArray & v_array = val->ToArray();
		for( const auto & it : v_array )
		{
			array.push_back( it.Value< T >() );
		}

		return array;
	}
};

template< typename K, typename V > struct VariantCast< XE::Pair< K, V > >
{
	static XE::Pair< K, V > Cast( const Variant * val )
	{
		XE::Pair< K, V > pair;

		const VariantArray & v_array = val->ToArray();
		if( v_array.size() == 2 )
		{
			pair.first = v_array[0].Value<K>();
			pair.second = v_array[1].Value<V>();
		}

		return pair;
	}
};

template< typename T > struct VariantCast< XE::Set< T > >
{
	static XE::Set< T > Cast( const Variant * val )
	{
		XE::Set< T > set;

		auto v_set = val->ToArray();
		for( const auto & it : v_set )
		{
			set.insert( it.Value< T >() );
		}

		return set;
	}
};

template< typename K, typename V > struct VariantCast< XE::Map< K, V > >
{
	static XE::Map< K, V > Cast( const Variant * val )
	{
		XE::Map< K, V > map;

		auto v_map = val->ToArray();
		for( const auto & it : v_map )
		{
			map.insert( it.Value< XE::Pair<K, V> >() );
		}

		return map;
	}
};

template< typename T > struct VariantCast< XE::MultiSet< T > >
{
	static XE::MultiSet< T > Cast( const Variant * val )
	{
		XE::MultiSet< T > multiset;

		auto v_multiset = val->ToArray();
		for( const auto & it : v_multiset )
		{
			multiset.insert( it.Value< T >() );
		}

		return multiset;
	}
};

template< typename K, typename V > struct VariantCast< XE::MultiMap< K, V > >
{
	static XE::MultiMap< K, V > Cast( const Variant * val )
	{
		XE::MultiMap< K, V > multimap;

		auto v_multimap = val->ToArray();
		for( const auto & it : v_multimap )
		{
			multimap.insert( it.Value< XE::Pair<K, V> >() );
		}

		return multimap;
	}
};

template< typename T > struct VariantCast< XE::UnorderedSet< T > >
{
	static XE::UnorderedSet< T > Cast( const Variant * val )
	{
		XE::UnorderedSet< T > set;

		auto v_set = val->ToArray();
		for( const auto & it : v_set )
		{
			set.insert( it.Value< T >() );
		}

		return set;
	}
};

template< typename K, typename V > struct VariantCast< XE::UnorderedMap< K, V > >
{
	static XE::UnorderedMap< K, V > Cast( const Variant * val )
	{
		XE::UnorderedMap< K, V > map;

		auto v_map = val->ToArray();
		for( const auto & it : v_map )
		{
			map.insert( it.Value< XE::Pair<K, V> >() );
		}

		return map;
	}
};

template< typename T > struct VariantCast< XE::UnorderedMultiSet< T > >
{
	static XE::UnorderedMultiSet< T > Cast( const Variant * val )
	{
		XE::UnorderedMultiSet< T > multiset;

		auto v_multiset = val->ToArray();
		for( const auto & it : v_multiset )
		{
			multiset.insert( it.Value< T >() );
		}

		return multiset;
	}
};

template< typename K, typename V > struct VariantCast< XE::UnorderedMultiMap< K, V > >
{
	static XE::UnorderedMultiMap< K, V > Cast( const Variant * val )
	{
		XE::UnorderedMultiMap< K, V > multimap;

		auto v_multimap = val->ToArray();
		for( const auto & it : v_multimap )
		{
			multimap.insert( it.Value< XE::Pair<K, V> >() );
		}

		return multimap;
	}
};

END_XE_NAMESPACE

#endif // __VARIANT_H__87E44F7B_D250_41E0_AEEE_7D7ECB2AAF35
