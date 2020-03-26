/*!
 * \file	AssetInstance.hpp
 *
 * \author	ZhengYuanQing
 * \date	2020/03/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ASSETINSTANCE_HPP__979615A6_2FC3_4E67_A1A7_6750FA6D0024
#define ASSETINSTANCE_HPP__979615A6_2FC3_4E67_A1A7_6750FA6D0024

#include "Asset.h"

BEG_XE_NAMESPACE

template< typename T > class AssetInstance
{
public:
	AssetInstance()
	{

	}

	AssetInstance( nullptr_t )
	{

	}

	AssetInstance( const Asset<T> & val )
		:_Path( val._Path )
	{
	}

	AssetInstance( const AssetInstance & val )
		:_Path( val._Path )
	{
		if( val._Obj )
		{
			_Obj = XE::Cloneable<T>::Clone( val._Obj );
		}
	}

	AssetInstance( const XE::String & val )
		:_Path( val )
	{

	}

	~AssetInstance()
	{

	}

public:
	AssetInstance & operator=( std::nullptr_t )
	{
		_Path = "";
		_Obj = nullptr;

		return *this;
	}

	AssetInstance & operator=( const Asset<T> & val )
	{
		if( _Path != val._Path )
		{
			_Path = val._Path;
		}

		return *this;
	}

	AssetInstance & operator=( const AssetInstance & val )
	{
		if( _Path != val._Path )
		{
			_Path = val._Path;

			if( val._Obj )
			{
				_Obj = XE::Cloneable<T>::Clone( val._Obj );
			}
		}

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
			AssetLoad::AsyncLoad( _Path );
		}

		return false;
	}

public:
	T * get()
	{
		if( _Obj == nullptr && _Path != "" )
		{
			_Obj = DP_CAST<T>( AssetLoad::Load( _Path ) );
			_Obj = XE::Cloneable<T>::Clone( _Obj );
		}

		return _Obj.get();
	}

	XE::SharedPtr< T > get_shared()
	{
		if( _Obj == nullptr && _Path != "" )
		{
			_Obj = DP_CAST<T>( AssetLoad::Load( _Path ) );
			_Obj = XE::Cloneable<T>::Clone( _Obj );
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
	XE::SharedPtr< T > _Obj;
};



template<> struct XE_API ClassID< AssetInstance< Object > >
{
	static IMetaClassPtr Get( const AssetInstance< Object > * val = nullptr )
	{
		static auto meta = XE::MakeShared< CXXMetaClass< AssetInstance< Object > > >( "AssetInstance", nullptr, nullptr );
		return meta;
	}
};

template< typename T > struct ClassID< AssetInstance< T > >
{
	static IMetaClassPtr Get( const AssetInstance< T > * val = nullptr )
	{
		return ClassID< AssetInstance< Object > >::Get();
	}
};



template< typename T > struct VariantCreate< AssetInstance< T > >
{
	static void Create( Variant * var, const AssetInstance< T > & val )
	{
		var->_Flag = Variant::Flag::PRIVATEPTR;
		var->_Type = TypeID<AssetInstance<Object>>::Get();
		var->_Data = new Variant::PrivatePtrTpl< AssetInstance< Object > >( AssetInstance<Object>( val.GetPath() ) );
	}
};

template< typename T > struct VariantCast< AssetInstance< T > >
{
	static AssetInstance< T > Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< AssetInstance< Object > >::Get() )
		{
			return ( ( AssetInstance< Object > * )val->ToPointer() )->GetPath();
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< AssetInstance< Object > >
{
	static AssetInstance< Object > Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< AssetInstance< Object > >::Get() )
		{
			return *( ( AssetInstance< Object > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< AssetInstance< Object > * >
{
	static AssetInstance< Object > * Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< AssetInstance< Object > >::Get() )
		{
			return ( ( AssetInstance< Object > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< const AssetInstance< Object > * >
{
	static const AssetInstance< Object > * Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< AssetInstance< Object > >::Get() )
		{
			return ( ( AssetInstance< Object > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template<> struct XE_API VariantCast< AssetInstance< Object > & >
{
	static AssetInstance< Object > & Cast( const Variant * val )
	{
		return *( VariantCast< AssetInstance< Object > * >::Cast( val ) );
	}
};

template<> struct XE_API VariantCast< const AssetInstance< Object > & >
{
	static const AssetInstance< Object > & Cast( const Variant * val )
	{
		return *( VariantCast< const AssetInstance< Object > * >::Cast( val ) );
	}
};


template< typename T > struct Serializable< AssetInstance< T > >
{
public:
	static void Serialize( Archive & arc, AssetInstance< T > * val )
	{
		auto path = val->GetPath();
		auto nvp = XE::Archive::NVP( "path", path );
		arc & nvp;

		( *val ) = AssetInstance< T >( nvp.Value );
	}
};


END_XE_NAMESPACE

#endif // ASSETINSTANCE_HPP__979615A6_2FC3_4E67_A1A7_6750FA6D0024
