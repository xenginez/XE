#include "Variant.h"

#include "CXXMetaClass.hpp"

USING_XE

class VariantSharedPool : public XE::Singleton<VariantSharedPool>
{
public:
	struct Data
	{
		std::atomic_size_t Count;
		std::shared_ptr<void> Ptr;
	};

public:
	static std::shared_ptr<void> * Register( std::shared_ptr<void> val )
	{
		std::lock_guard<std::mutex> lock( This()->_Lock );

		Data &d = This()->_Ptr[val.get()];

		d.Count = 0;
		d.Ptr = val;

		return &( d.Ptr );
	}

	static void Lock( std::shared_ptr<void> * val )
	{
		std::lock_guard<std::mutex> lock( This()->_Lock );

		auto it = This()->_Ptr.find( val->get() );
		if (it != This()->_Ptr.end())
		{
			it->second.Count++;
		}
	}

	static void Unlock( std::shared_ptr<void> * val )
	{
		std::lock_guard<std::mutex> lock( This()->_Lock );

		auto it = This()->_Ptr.find( val->get() );
		if ( it != This()->_Ptr.end() )
		{
			it->second.Count--;
			if ( it->second.Count == 0 )
			{
				This()->_Ptr.erase( val );
			}
		}
	}

private:
	std::mutex _Lock;
	Map<void *, Data> _Ptr;
};



XE::Variant::Variant()
	:_Data( ( void* )nullptr ), _Flag( 0 )
{

}

XE::Variant::Variant( std::nullptr_t )
	: _Data( ( void* )nullptr ), _Meta( MetaID<std::nullptr_t>::Get() ), _Flag( 0 )
{

}

XE::Variant::Variant( bool val )
	: _Data( val ), _Meta( MetaID<bool>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( int8 val )
	: _Data( val ), _Meta( MetaID<int8>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( int16 val )
	: _Data( val ), _Meta( MetaID<int16>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( int32 val )
	: _Data( val ), _Meta( MetaID<int32>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( int64 val )
	: _Data( val ), _Meta( MetaID<int64>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( uint8 val )
	: _Data( val ), _Meta( MetaID<uint8>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( uint16 val )
	: _Data( val ), _Meta( MetaID<uint16>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( uint32 val )
	: _Data( val ), _Meta( MetaID<uint32>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( uint64 val )
	: _Data( val ), _Meta( MetaID<uint64>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( float val )
	: _Data( val ), _Meta( MetaID<float>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( double val )
	: _Data( val ), _Meta( MetaID<double>::Get() ), _Flag( FUNDAMENTAL )
{

}

XE::Variant::Variant( const Variant & val )
	: _Meta( val._Meta ), _Data( val._Data ), _Flag( val._Flag )
{
	Lock();
}

XE::Variant::Variant( IMetaInfoPtr Meta, UnionData Data, uint64 Flag )
	: _Data( Data ), _Meta( Meta ), _Flag( Flag )
{
	Lock();
}

XE::Variant::~Variant()
{
	Unlock();
}

XE::Variant& XE::Variant::operator=( const Variant& val )
{
	Unlock();

	_Data = val._Data;
	_Meta = val._Meta;
	_Flag = val._Flag;

	Lock();

	return *this;
}

bool XE::Variant::operator<( const Variant& val ) const
{
	return false;
}

bool XE::Variant::operator>( const Variant& val ) const
{
	return false;
}

bool XE::Variant::operator<=( const Variant& val ) const
{
	return false;
}

bool XE::Variant::operator>=( const Variant& val ) const
{
	return false;
}

bool XE::Variant::operator==( const Variant& val ) const
{
	return false;
}

bool XE::Variant::operator!=( const Variant& val ) const
{
	return false;
}

bool XE::Variant::IsNull() const
{
	return _Data.p == nullptr && !( _Flag & FUNDAMENTAL );
}

bool XE::Variant::IsInvalid() const
{
	return _Meta == nullptr && _Data.p == nullptr;
}

bool XE::Variant::IsPointer() const
{
	return ( _Flag & POINTER );
}

bool XE::Variant::IsContainer() const
{
	return ( _Flag & CONTAINER );
}

bool XE::Variant::IsSharedPtr() const
{
	return ( _Flag & SHAREDPTR );
}

bool XE::Variant::IsPrivatePtr() const
{
	return ( _Flag & PRIVATEPTR );
}

bool XE::Variant::IsFundamental() const
{
	return ( _Flag & FUNDAMENTAL );
}

void * XE::Variant::ToPointer() const
{
	if ( _Data.p == nullptr )
	{
		return nullptr;
	}

	if ( _Flag & PRIVATEPTR )
	{
		return _Data.pp->Data();
	}

	if ( _Flag & SHAREDPTR )
	{
		return _Data.sp->get();
	}

	if ( _Flag & POINTER )
	{
		return _Data.p;
	}

	if ( _Flag & FUNDAMENTAL )
	{
		if ( _Meta == MetaID<bool>::Get() )
		{
			return (void*)( &( _Data.b ) );
		}
		else if ( _Meta == MetaID<int8>::Get() )
		{
			return (void*)( &( _Data.i8 ) );
		}
		else if ( _Meta == MetaID<int16>::Get() )
		{
			return (void*)( &( _Data.i16 ) );
		}
		else if ( _Meta == MetaID<int32>::Get() )
		{
			return (void*)( &( _Data.i32 ) );
		}
		else if ( _Meta == MetaID<int64>::Get() )
		{
			return (void*)( &( _Data.i64 ) );
		}
		else if ( _Meta == MetaID<uint8>::Get() )
		{
			return (void*)( &( _Data.u8 ) );
		}
		else if ( _Meta == MetaID<uint16>::Get() )
		{
			return (void*)( &( _Data.u16 ) );
		}
		else if ( _Meta == MetaID<uint32>::Get() )
		{
			return (void*)( &( _Data.u32 ) );
		}
		else if ( _Meta == MetaID<uint64>::Get() )
		{
			return (void*)( &( _Data.u64 ) );
		}
		else if ( _Meta == MetaID<float>::Get() )
		{
			return (void*)( &( _Data.f ) );
		}
		else if ( _Meta == MetaID<double>::Get() )
		{
			return (void*)( &( _Data.d ) );
		}
	}

	return nullptr;
}

XE::uint64 XE::Variant::GetFlag() const
{
	return _Flag;
}

XE::IMetaInfoPtr XE::Variant::GetMeta() const
{
	return _Meta;
}

XE::Variant::UnionData XE::Variant::GetData() const
{
	return _Data;
}

void XE::Variant::Reset()
{
	Unlock();

	_Data.p = nullptr;
	_Meta = nullptr;
	_Flag = 0;
}

void * XE::Variant::Detach()
{
	void * p = nullptr;

	if ( _Flag & SHAREDPTR )
	{
		throw VariantException( *this, "detach fail" );
	}

	if ( _Flag & PRIVATEPTR )
	{
		p = _Data.pp->Detach();
	}

	if (_Flag & POINTER)
	{
		p = _Data.p;
	}

	Unlock();

	return p;
}

std::shared_ptr<void> XE::Variant::DetachSharedPtr()
{
	void * p = nullptr;

	if ( _Flag & SHAREDPTR )
	{
		std::shared_ptr<void> p = *_Data.sp;
		Unlock();
		return p;
	}

	throw VariantException( *this, "detach fail" );
}

void XE::Variant::Lock()
{
	if (_Flag & SHAREDPTR)
	{
		VariantSharedPool::Lock( _Data.sp );
	}

	if (_Flag & PRIVATEPTR)
	{
		_Data.pp->Lock();
	}
}

void XE::Variant::Unlock()
{
	if ( _Flag & SHAREDPTR )
	{
		VariantSharedPool::Unlock( _Data.sp );
	}

	if ( _Flag & PRIVATEPTR )
	{
		if ( _Data.pp->Unlock() == 0 )
		{
			delete _Data.pp;
			_Data.pp = nullptr;
		}
	}
}

std::shared_ptr<void> * XE::Variant::RegisterSharedPtr( const std::shared_ptr<void>& p )
{
	return VariantSharedPool::Register( p );
}


XE::VariantException::VariantException( const Variant& val, const String& msg )
	:_Value( val ), _Msg( msg )
{

}

XE::VariantException::~VariantException()
{

}

char const* XE::VariantException::What() const
{
	return ( "VariantException: Variant Value Type[" + _Value.GetMeta()->GetFullName() + "] " + _Msg ).ToCString();
}

XE::Variant XE::VariantException::GetVariant() const
{
	return _Value;
}
