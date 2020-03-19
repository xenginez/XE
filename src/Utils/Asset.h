/*!
 * \file	Asset.hpp
 *
 * \author	ZhengYuanQing
 * \date	2019/12/09
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ASSET_HPP__96069A9E_65B1_4690_98CC_D3AE42C61B61
#define ASSET_HPP__96069A9E_65B1_4690_98CC_D3AE42C61B61

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AssetLoad
{
public:
	static XE::ObjectPtr Load( const XE::String & val );

	static void AsyncLoad( const XE::String & val );

};

template< typename T > class Asset
{
public:
	Asset()
	{

	}

	Asset( nullptr_t )
	{

	}

	Asset( const Asset & val )
		:_Path( val._Path ), _Obj( val._Obj )
	{

	}

	Asset( const XE::String & val )
		:_Path( val )
	{

	}

	~Asset()
	{

	}

public:
	Asset & operator=( std::nullptr_t )
	{
		_Path = "";
		_Obj = nullptr;

		return *this;
	}

	Asset & operator=( const Asset & val )
	{
		if( _Path != val._Path )
		{
			_Path = val._Path;

			_Obj = val._Obj;
		}

		return *this;
	}

public:
	const T * operator->()
	{
		return get();
	}

	const T * operator->() const
	{
		return get();
	}

	const T & operator *()
	{
		return *( get() );
	}

	const T & operator *() const
	{
		return *( get() );
	}

	operator bool() const
	{
		if( _Obj )
		{
			return true;
		}

		if( _Path != "" )
		{
			AssetLoad::AsyncLoad( _Path );

			return AssetLoad::Load( _Path ) != nullptr;
		}

		return false;
	}

public:
	const T * get()
	{
		if( _Obj == nullptr && _Path != "" )
		{
			_Obj = AssetLoad::Load( _Path )
		}

		return _Obj.get();
	}

	const T * get() const
	{
		if( _Obj == nullptr && _Path != "" )
		{
			return AssetLoad::Load( _Path ).get();
		}

		return nullptr;
	}

	XE::SharedPtr< const T > get_shared()
	{
		if( _Obj == nullptr && _Path != "" )
		{
			_Obj = AssetLoad::Load( _Path )
		}

		return _Obj;
	}

	XE::SharedPtr< const T > get_shared() const
	{
		if( _Obj == nullptr && _Path != "" )
		{
			_Obj = AssetLoad::Load( _Path )
		}

		return _Obj;
	}

public:
	void async()
	{
		if( _Obj == nullptr && _Path != "" )
		{
			AssetLoad::AsyncLoad( _Path )
		}
	}

public:
	const XE::String & GetPath() const
	{
		return _Path;
	}

private:
	XE::String _Path;
	XE::SharedPtr< const T > _Obj;
};

template<> struct XE_API ClassID< Asset< Object > >
{
	static IMetaClassPtr Get( const Asset< Object > * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass< Asset< Object > > >( "Asset", nullptr, nullptr );
		return meta;
	}
};

template< typename T > struct ClassID< Asset< T > >
{
	static IMetaClassPtr Get( const Asset< T > * val = nullptr )
	{
		return ClassID< Asset< Object > >::Get();
	}
};



template< typename T > struct VariantCreate< Asset< T > >
{
	static void Create( Variant * var, const Asset< T > & val )
	{
		var->_Flag = Variant::Flag::PRIVATEPTR;
		var->_Type = TypeID<Asset<Object>>::Get();
		var->_Data = new Variant::PrivatePtrTpl< Asset< Object > >( Asset<Object>( val.GetPath() ) );
	}
};

template< typename T > struct VariantCast< Asset< T > >
{
	static Asset< T > Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< Asset< Object > >::Get() )
		{
			return ( ( Asset< Object > * )val->ToPointer() )->GetPath();
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< Asset< Object > >
{
	static Asset< Object > Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< Asset< Object > >::Get() )
		{
			return *( ( Asset< Object > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< Asset< Object > * >
{
	static Asset< Object > * Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< Asset< Object > >::Get() )
		{
			return ( ( Asset< Object > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< const Asset< Object > * >
{
	static const Asset< Object > * Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< Asset< Object > >::Get() )
		{
			return ( ( Asset< Object > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< Asset< Object > & >
{
	static Asset< Object > & Cast( const Variant * val )
	{
		return *( VariantCast< Asset< Object > * >::Cast( val ) );
	}
};

template<> struct XE_API VariantCast< const Asset< Object > & >
{
	static const Asset< Object > & Cast( const Variant * val )
	{
		return *( VariantCast< const Asset< Object > * >::Cast( val ) );
	}
};


template< typename T > struct Serializable< Asset< T > >
{
public:
	static void Serialize( Archive & arc, Asset< T > * val )
	{
		auto path = val->GetPath();

		arc & path;

		( *val ) = Asset< T >( path );
	}
};

END_XE_NAMESPACE

#endif // ASSET_HPP__96069A9E_65B1_4690_98CC_D3AE42C61B61
