#include "Variant.h"

#include "CXXMetaClass.hpp"

USING_XE

class VariantSharedPool : public XE::Singleton<VariantSharedPool>
{
public:
	struct Data
	{
		std::atomic_size_t Count;
		XE::shared_ptr<void> Ptr;
	};

public:
	~VariantSharedPool()
	{
		int i = 0;
	}

public:
	XE::shared_ptr<void> * Register( XE::shared_ptr<void> val )
	{
		std::lock_guard<std::mutex> lock( Instance()->_Lock );

		Data & d = _Ptr[val.get()];

		d.Count = 0;
		d.Ptr = val;

		return &( d.Ptr );
	}

	void Lock( XE::shared_ptr<void> * val )
	{
		std::lock_guard<std::mutex> lock( Instance()->_Lock );

		auto it = _Ptr.find( val->get() );
		if( it != _Ptr.end() )
		{
			it->second.Count++;
		}
	}

	void Unlock( XE::shared_ptr<void> * val )
	{
		std::lock_guard<std::mutex> lock( Instance()->_Lock );

		auto it = _Ptr.find( val->get() );
		if( it != _Ptr.end() )
		{
			it->second.Count--;
			if( it->second.Count == 0 )
			{
				_Ptr.erase( it );
			}
		}
	}

private:
	std::mutex _Lock;
	Map<void *, Data> _Ptr;
};



XE::Variant::Variant()
	:_Data( ( void * )nullptr ), _Flag( Flag::INVALID )
{

}

XE::Variant::Variant( std::nullptr_t )
	: _Data( ( void * )nullptr ), _Type( TypeID<std::nullptr_t>::Get() ), _Flag( Flag::NIL )
{

}

XE::Variant::Variant( bool val )
	: _Data( val ), _Type( TypeID<bool>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::int8 val )
	: _Data( val ), _Type( TypeID<XE::int8>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::int16 val )
	: _Data( val ), _Type( TypeID<XE::int16>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::int32 val )
	: _Data( val ), _Type( TypeID<XE::int32>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::int64 val )
	: _Data( val ), _Type( TypeID<XE::int64>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::uint8 val )
	: _Data( val ), _Type( TypeID<XE::uint8>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::uint16 val )
	: _Data( val ), _Type( TypeID<XE::uint16>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::uint32 val )
	: _Data( val ), _Type( TypeID<XE::uint32>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::uint64 val )
	: _Data( val ), _Type( TypeID<XE::uint64>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::float32 val )
	: _Data( val ), _Type( TypeID<XE::float32>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( XE::float64 val )
	: _Data( val ), _Type( TypeID<XE::float64>::Get() ), _Flag( Flag::FUNDAMENTAL )
{

}

XE::Variant::Variant( const Variant & val )
	: _Type( val._Type ), _Data( val._Data ), _Flag( val._Flag )
{
	Lock();
}

XE::Variant::Variant( IMetaTypePtr meta, UnionData data, XE::Variant::Flag flag )
	: _Data( data ), _Type( meta ), _Flag( flag )
{
	Lock();
}

Variant::Variant( IMetaTypePtr meta, XE::shared_ptr<void> data, XE::Variant::Flag flag )
	: _Type( meta ), _Flag( flag )
{
	_Data.sp = RegisterSharedPtr( *_Data.sp );

	Lock();
}

XE::Variant::~Variant()
{
	Unlock();
}

XE::Variant & XE::Variant::operator=( const Variant & val )
{
	Unlock();

	_Type = val._Type;
	_Flag = val._Flag;
	_Data = val._Data;

	Lock();

	return *this;
}

bool XE::Variant::operator<( const Variant & val ) const
{
	if( _Type == val._Type && _Flag == val._Flag )
	{
		return _Data.p < val._Data.p;
	}

	return false;
}

bool XE::Variant::operator>( const Variant & val ) const
{
	if( _Type == val._Type && _Flag == val._Flag )
	{
		return _Data.p > val._Data.p;
	}

	return false;
}

bool XE::Variant::operator<=( const Variant & val ) const
{
	if( _Type == val._Type && _Flag == val._Flag )
	{
		return _Data.p <= val._Data.p;
	}

	return false;
}

bool XE::Variant::operator>=( const Variant & val ) const
{
	if( _Type == val._Type && _Flag == val._Flag )
	{
		return _Data.p >= val._Data.p;
	}

	return false;
}

bool XE::Variant::operator==( const Variant & val ) const
{
	if( _Type == val._Type && _Flag == val._Flag )
	{
		return _Data.p == val._Data.p;
	}

	return false;
}

bool XE::Variant::operator!=( const Variant & val ) const
{
	if( _Type == val._Type && _Flag == val._Flag )
	{
		return _Data.p != val._Data.p;
	}

	return true;
}

bool XE::Variant::IsNull() const
{
	return _Flag == Flag::NIL;
}

bool XE::Variant::IsEnum() const
{
	return _Flag == Flag::ENUM;
}

bool XE::Variant::IsInvalid() const
{
	return _Flag == Flag::INVALID;
}

bool XE::Variant::IsPointer() const
{
	return ( _Flag == Flag::POINTER );
}

bool XE::Variant::IsContainer() const
{
	return ( _Flag == Flag::CONTAINER );
}

bool XE::Variant::IsSharedPtr() const
{
	return ( _Flag == Flag::SHAREDPTR );
}

bool XE::Variant::IsPrivatePtr() const
{
	return ( _Flag == Flag::PRIVATEPTR || _Flag == Flag::CONTAINER );
}

bool XE::Variant::IsFundamental() const
{
	return ( _Flag == Flag::FUNDAMENTAL );
}

bool XE::Variant::IsCanConvert( IMetaTypePtr val ) const
{
	if( _Type == val )
	{
		return true;
	}
	else if( _Type->GetType() == MetaType::CLASS && val->GetType() == MetaType::CLASS )
	{
		if( auto cls = SP_CAST<IMetaClass>( _Type ) )
		{
			return cls->CanConvert( SP_CAST<IMetaClass>( val ) );
		}
	}

	return false;
}

bool XE::Variant::ToBool() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8 != 0;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16 != 0;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32 != 0;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64 != 0;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8 != 0;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16 != 0;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32 != 0;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64 != 0;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f > FLT_EPSILON || _Data.f < -FLT_EPSILON;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.f > DBL_EPSILON || _Data.f < -DBL_EPSILON;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::int8 XE::Variant::ToInt8() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::int16 XE::Variant::ToInt16() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::int32 XE::Variant::ToInt32() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::int64 XE::Variant::ToInt64() const
{
	if( _Flag == Flag::ENUM )
	{
		return _Data.i64;
	}

	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::uint8 XE::Variant::ToUInt8() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::uint16 XE::Variant::ToUInt16() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::int32 XE::Variant::ToUInt32() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::uint64 XE::Variant::ToUInt64() const
{
	if( _Flag == Flag::HANDLE )
	{
		return _Data.u64;
	}

	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::float32 XE::Variant::ToFloat32() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

XE::float64 XE::Variant::ToFloat64() const
{
	if( ( _Flag == Flag::FUNDAMENTAL ) && !( _Flag == Flag::POINTER ) )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return _Data.b ? 1 : 0;
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return _Data.i8;
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return _Data.i16;
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return _Data.i32;
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return _Data.i64;
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return _Data.u8;
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return _Data.u16;
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return _Data.u32;
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return _Data.u64;
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return _Data.f;
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return _Data.d;
		}
	}

	throw XE::VariantException( this, "not the base type !" );
}

void * XE::Variant::ToPointer() const
{
	if( _Type == nullptr )
	{
		return nullptr;
	}

	if( _Flag == Flag::PRIVATEPTR )
	{
		return _Data.pp->Data();
	}

	if( _Flag == Flag::SHAREDPTR )
	{
		return _Data.sp->get();
	}

	if( _Flag == Flag::POINTER )
	{
		return _Data.p;
	}

	if( _Flag == Flag::FUNDAMENTAL )
	{
		if( _Type == TypeID<bool>::Get() )
		{
			return (void * )( &( _Data.b ) );
		}
		else if( _Type == TypeID<XE::int8>::Get() )
		{
			return (void * )( &( _Data.i8 ) );
		}
		else if( _Type == TypeID<XE::int16>::Get() )
		{
			return (void * )( &( _Data.i16 ) );
		}
		else if( _Type == TypeID<XE::int32>::Get() )
		{
			return (void * )( &( _Data.i32 ) );
		}
		else if( _Type == TypeID<XE::int64>::Get() )
		{
			return (void * )( &( _Data.i64 ) );
		}
		else if( _Type == TypeID<XE::uint8>::Get() )
		{
			return (void * )( &( _Data.u8 ) );
		}
		else if( _Type == TypeID<XE::uint16>::Get() )
		{
			return (void * )( &( _Data.u16 ) );
		}
		else if( _Type == TypeID<XE::uint32>::Get() )
		{
			return (void * )( &( _Data.u32 ) );
		}
		else if( _Type == TypeID<XE::uint64>::Get() )
		{
			return (void * )( &( _Data.u64 ) );
		}
		else if( _Type == TypeID<XE::float32>::Get() )
		{
			return (void * )( &( _Data.f ) );
		}
		else if( _Type == TypeID<XE::float64>::Get() )
		{
			return (void * )( &( _Data.d ) );
		}
	}

	return nullptr;
}

XE::Array<XE::Variant> Variant::ToArray() const
{
	XE::VariantArray ret;

	if( _Type == TypeID<VariantList>::Get() )
	{
		VariantList list = Value< VariantList >();

		for( const auto & it : list )
		{
			ret.push_back( it );
		}
	}
	else if( _Type == TypeID<VariantDeque>::Get() )
	{
		VariantDeque deque = Value< VariantDeque >();

		for( const auto & it : deque )
		{
			ret.push_back( it );
		}
	}
	else if( _Type == TypeID<VariantStack>::Get() )
	{
		VariantStack stack = Value< VariantStack >();

		for( ; !stack.empty(); )
		{
			ret.push_back( stack.top() );
			stack.pop();
		}
	}
	else if( _Type == TypeID<VariantQueue>::Get() )
	{
		VariantQueue queue = Value< VariantQueue >();

		for( ; !queue.empty(); )
		{
			ret.push_back( queue.front() );
			queue.pop();
		}
	}
	else if( _Type == TypeID<VariantArray>::Get() )
	{
		ret = Value< VariantArray >();
	}
	else if( _Type == TypeID<VariantSet>::Get() )
	{
		VariantSet set = Value< VariantSet >();

		for( const auto & it : set )
		{
			ret.push_back( it );
		}
	}
	else if( _Type == TypeID<VariantMap>::Get() )
	{
		VariantMap map = Value< VariantMap >();

		for( const auto & it : map )
		{
			VariantPair pair;

			pair.first = it.first;
			pair.second = it.second;

			ret.push_back( pair );
		}
	}
	else if( _Type == TypeID<VariantMultiSet>::Get() )
	{
		VariantMultiSet multiset = Value< VariantMultiSet >();

		for( const auto & it : multiset )
		{
			ret.push_back( it );
		}
	}
	else if( _Type == TypeID<VariantMultiMap>::Get() )
	{
		VariantMultiMap multimap = Value< VariantMultiMap >();

		for( const auto & it : multimap )
		{
			VariantPair pair;

			pair.first = it.first;
			pair.second = it.second;

			ret.push_back( pair );
		}
	}
	else
	{
		throw XE::VariantException( *this, "cast fail !" );
	}

	return ret;
}

XE::Variant::Flag XE::Variant::GetFlag() const
{
	return _Flag;
}

XE::IMetaTypePtr XE::Variant::GetType() const
{
	return _Type;
}

XE::Variant::UnionData XE::Variant::GetData() const
{
	return _Data;
}

void XE::Variant::Reset()
{
	Unlock();

	_Data.p = nullptr;
	_Type = nullptr;
	_Flag = Flag::INVALID;
}

void * XE::Variant::Detach()
{
	void * p = nullptr;

	if( _Flag == Flag::SHAREDPTR )
	{
		throw VariantException( *this, "detach fail, is shared pointer !" );
	}

	if( _Flag == Flag::PRIVATEPTR )
	{
		p = _Data.pp->Detach();
	}

	if( _Flag == Flag::POINTER )
	{
		p = _Data.p;
	}

	if( p != nullptr )
	{
		Reset();
	}

	return p;
}

XE::shared_ptr<void> XE::Variant::DetachPtr()
{
	if( _Flag == Flag::SHAREDPTR )
	{
		XE::shared_ptr<void> p = *_Data.sp;

		Reset();

		return p;
	}

	throw VariantException( *this, "detach fail, is not shared pointer !" );
}

XE::shared_ptr<void> * XE::Variant::RegisterSharedPtr( const XE::shared_ptr<void> & p )
{
	return VariantSharedPool::Instance()->Register( p );
}

void XE::Variant::Lock()
{
	if( _Flag == Flag::SHAREDPTR )
	{
		VariantSharedPool::Instance()->Lock( _Data.sp );
	}

	if( _Flag == Flag::PRIVATEPTR )
	{
		_Data.pp->Lock();
	}
}

void XE::Variant::Unlock()
{
	if( _Flag == Flag::SHAREDPTR )
	{
		VariantSharedPool::Instance()->Unlock( _Data.sp );
	}

	if( _Flag == Flag::PRIVATEPTR )
	{
		if( _Data.pp->Unlock() == 0 )
		{
			delete _Data.pp;
		}
	}
}



XE::VariantException::VariantException( const Variant & val, const String & msg )
	:_Value( val ), _Msg( msg )
{

}

XE::VariantException::~VariantException()
{

}

char const * XE::VariantException::What() const
{
	return ( "VariantException: Variant Value Type[" + _Value.GetType()->GetFullName() + "] " + _Msg ).ToCString();
}

XE::Variant XE::VariantException::GetVariant() const
{
	return _Value;
}
