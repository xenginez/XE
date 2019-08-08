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

template< typename T > struct VariantCreate;
template< typename T > struct VariantCast;



class REFLECT_API Variant
{
public:
	template< typename T > friend struct VariantCreate;
	template< typename T > friend struct VariantCast;

public:
	static constexpr XE::uint32 INVALID = 0;
	static constexpr XE::uint32 FUNDAMENTAL = 1 << 1;
	static constexpr XE::uint32 CONTAINER = 1 << 2;
	static constexpr XE::uint32 POINTER = 1 << 3;
	static constexpr XE::uint32 SHAREDPTR = 1 << 4;
	static constexpr XE::uint32 PRIVATEPTR = 1 << 5;

public:
	class PrivatePtr
	{
	public:
		PrivatePtr() = default;
		
		virtual ~PrivatePtr() = default;
		
	public:
		virtual void Lock() = 0;

		virtual XE::uint64 Unlock() = 0;

		virtual void * Copy() const = 0;

		virtual void * Data() const = 0;

		virtual void * Detach() = 0;

	};

	template< typename T > class PrivatePtrTpl : public PrivatePtr
	{
	public:
		using Type = typename TypeTraits<T>::raw_t;

	public:
		PrivatePtrTpl( const T &val )
			:_Data( new Type( val ) )
		{

		}

		~PrivatePtrTpl()
		{
			if ( _Data )
			{
				delete _Data;
			}
		}

	public:
		virtual void Lock() override
		{
			_Count++;
		}

		virtual XE::uint64 Unlock() override
		{
			return --_Count;
		}

		virtual void * Copy() const override
		{
			if constexpr ( std::is_abstract_v<T> )
			{
				return nullptr;
			}
			else
			{
				return new Type( *_Data );
			}
		}

		virtual void * Data() const override
		{
			return _Data;
		}

		virtual void * Detach() override
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
		UnionData( std::shared_ptr<void> * sp ) :sp( sp ) {}

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
		std::shared_ptr<void> * sp;
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

		if constexpr ( std::is_shared_ptr_v<T> )
		{
			VariantCreate< std::shared_ptr< type > >::Create( this, val );
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

		if constexpr ( std::is_shared_ptr_v<T> )
		{
			VariantCreate< std::shared_ptr< type > >::Create( this, val );
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

		_Meta = MetaID<type>::Get();
		_Data.p = (void*)val;
		_Flag = Variant::POINTER;
	}

	template< typename T > Variant( const T * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		_Meta = MetaID<type>::Get();
		_Data.p = (void*)val;
		_Flag = Variant::POINTER;
	}

	Variant( IMetaInfoPtr Meta, UnionData Data, XE::uint32 Flag );

	Variant( IMetaInfoPtr Meta, std::shared_ptr<void> Data, XE::uint32 Flag );

	~Variant();

public:
	Variant& operator=( const Variant & val );

public:
	bool operator <( const Variant& val ) const;

	bool operator >( const Variant& val ) const;

	bool operator <=( const Variant& val ) const;

	bool operator >=( const Variant& val ) const;

	bool operator ==( const Variant& val ) const;

	bool operator !=( const Variant& val ) const;

public:
	bool IsNull() const;

	bool IsInvalid() const;

	bool IsPointer() const;

	bool IsContainer() const;

	bool IsSharedPtr() const;

	bool IsPrivatePtr() const;

	bool IsFundamental() const;

public:
	void * ToPointer() const;

public:
	XE::uint32 GetFlag() const;

	UnionData GetData() const;

	IMetaInfoPtr GetMeta() const;

public:
	void Reset();

	void * Detach();

	std::shared_ptr<void> DetachPtr();

public:
	template< typename T > T Value() const
	{
		using type = typename TypeTraits<T>::raw_t;

		if constexpr ( std::is_shared_ptr_v<T> )
		{
			if constexpr ( std::is_pointer_v<T> )
			{
				return VariantCast< std::shared_ptr< type > >::Cast( this );
			}
			else
			{
				return *( VariantCast< std::shared_ptr< type > >::Cast( this ) );
			}
		}
		else
		{
			if constexpr ( std::is_pointer_v<T> )
			{
				return VariantCast< type >::Cast( this );
			}
			else
			{
				return *( VariantCast< type >::Cast( this ) );
			}
		}
	}

private:
	void Lock();

	void Unlock();

private:
	static std::shared_ptr<void> * RegisterSharedPtr( const std::shared_ptr<void>& p );

private:
	UnionData _Data;
	XE::uint32 _Flag;
	IMetaInfoPtr _Meta;
};



using VariantList = std::list<Variant, Allocator<Variant>>;
using VariantDeque = std::deque<Variant, Allocator<Variant>>;
using VariantStack = std::stack<Variant, Deque<Variant>>;
using VariantQueue = std::queue<Variant, Deque<Variant>>;
using VariantArray = std::vector<Variant, Allocator<Variant>>;
using VariantPair = std::pair<Variant, Variant>;
using VariantSet = std::set<Variant, std::less<Variant>, Allocator<Variant>>;
using VariantMap = std::map<Variant, Variant, std::less<Variant>, Allocator<Pair<const Variant, Variant>>>;
using VariantMultiSet = std::multiset<Variant, std::less<Variant>, Allocator<Variant>>;
using VariantMultiMap = std::multimap<Variant, Variant, std::less<Variant>, Allocator<Pair<const Variant, Variant>>>;



class REFLECT_API VariantException : public RuntimeException
{
public:
	VariantException( const Variant& val, const String& msg );

	~VariantException();

public:
	virtual char const* What() const;

public:
	Variant GetVariant() const;

private:
	String _Msg;
	Variant _Value;
};



template< typename T > struct VariantCreate
{
	static void Create( Variant * var, const T& val )
	{
		using type = typename TypeTraits<T>::raw_t;

		var->_Meta = MetaID<type>::Get();
		var->_Data.pp = new Variant::PrivatePtrTpl<type>( val );
		var->_Flag = Variant::PRIVATEPTR;
	}
};

template<> struct VariantCreate<Variant>
{
	static void Create( Variant * var, const Variant& val )
	{
		var->_Meta = val._Meta;
		var->_Data = val._Data;
		var->_Flag = val._Flag;
	}
};

template< typename T > struct VariantCreate<std::weak_ptr<T>>
{
	static void Create( Variant * var, const std::weak_ptr<T>& val )
	{
		using type = typename TypeTraits<T>::raw_t;

		var->_Meta = MetaID<type>::Get();
		var->_Data.sp = Variant::RegisterSharedPtr( val.lock() );
		var->_Flag = Variant::SHAREDPTR;
	}
};

template< typename T > struct VariantCreate<std::shared_ptr<T>>
{
	static void Create( Variant * var, const std::shared_ptr<T>& val )
	{
		using type = typename TypeTraits<T>::raw_t;

		var->_Meta = MetaID<type>::Get();
		var->_Data.sp = Variant::RegisterSharedPtr( val );
		var->_Flag = Variant::SHAREDPTR;
	}
};



template< typename T > struct VariantCast
{
	static T * Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if ( val->GetMeta() == MetaID< type >::Get() )
		{
			return ( T * )val->ToPointer();
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<std::weak_ptr<T>>
{
	static std::shared_ptr<T> * Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if ( val->GetMeta() == MetaID< type >::Get() && val->IsSharedPtr() )
		{
			return (std::shared_ptr<T> *)( val->_Data.sp );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast<std::shared_ptr<T>>
{
	static std::shared_ptr<T> * Cast( const Variant * val )
	{
		using type = typename TypeTraits<T>::raw_t;

		if ( val->GetMeta() == MetaID< type >::Get() && val->IsSharedPtr() )
		{
			return (std::shared_ptr<T> *)( val->_Data.sp );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct VariantCast<Variant>
{
	static Variant * Cast( const Variant * val )
	{
		return const_cast<Variant*>( val );
	}
};

END_XE_NAMESPACE

#endif // __VARIANT_H__87E44F7B_D250_41E0_AEEE_7D7ECB2AAF35
