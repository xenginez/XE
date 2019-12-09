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

#include "IFramework.h"
#include "IAssetsService.h"

BEG_XE_NAMESPACE

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
		:_Path( val._Path )
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
	Asset & operator=( const Asset & val )
	{
		_Path = val->_Path;

		return *this;
	}

public:
	T * operator->()
	{
		return get();
	}

	T * operator->() const
	{
		return get();
	}

	T & operator *()
	{
		return *( get() );
	}

	T & operator *() const
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
			return false;
		}

		return XE::IFramework::GetCurrentFramework()->GetServiceT<XE::IAssetsService>()->GetAssetStatus( _Path ) == AssetStatus::Ready;
	}

public:
	T * get()
	{
		if( _Obj == nullptr && _Path != "" )
		{
			_Obj = DP_CAST<T>( XE::IFramework::GetCurrentFramework()->GetServiceT<XE::IAssetsService>()->GetAsset( _Path ) );
		}

		return _Obj.get();
	}

	T * get() const
	{
		if( _Obj == nullptr && _Path != "" )
		{
			return DP_CAST<T>( XE::IFramework::GetCurrentFramework()->GetServiceT<XE::IAssetsService>()->GetAsset( _Path ) ).get();
		}

		return _Obj.get();
	}

public:
	void Load()
	{
		if( _Path != "" )
		{
			_Obj = XE::IFramework::GetCurrentFramework()->GetServiceT<XE::IAssetsService>()->Load( _Path );
		}
	}

	void AsynLoad()
	{
		if( _Path != "" )
		{
			XE::IFramework::GetCurrentFramework()->GetServiceT<XE::IAssetsService>()->AsynLoad( _Path );
		}
	}

	const XE::String & GetPath() const
	{
		return _Path;
	}

private:
	XE::String _Path;
	XE::SharedPtr< T > _Obj;
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

END_XE_NAMESPACE

#endif // ASSET_HPP__96069A9E_65B1_4690_98CC_D3AE42C61B61
