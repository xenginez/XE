/*!
 * \file	Key.h
 *
 * \author	ZhengYuanQing
 * \date	2020/03/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef KEY_H__88D541E2_6D11_4128_AF3F_BC8253B6A753
#define KEY_H__88D541E2_6D11_4128_AF3F_BC8253B6A753

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Key : public XE::Object
{
	OBJECT( Key, Object )

public:
	Key();

	Key( const Key & val );

	Key( const XE::String & val );

	~Key() override;

public:
	bool operator<( const Key & val ) const;

	bool operator>( const Key & val ) const;

	bool operator<=( const Key & val ) const;

	bool operator>=( const Key & val ) const;

	bool operator==( const Key & val ) const;

	bool operator!=( const Key & val ) const;

public:
	const XE::String & GetKey() const;

	void SetKey( const XE::String & val );

private:
	XE::String _Key;
};

template< typename T > class KeyT : public Key
{};


template< typename T > struct ClassID< KeyT< T > >
{
	static IMetaClassPtr Get( const KeyT< T > * val = nullptr )
	{
		return ClassID< Key >::Get();
	}
};



template< typename T > struct VariantCreate< KeyT< T > >
{
	static void Create( Variant * var, const KeyT< T > & val )
	{
		var->_Flag = Variant::Flag::PRIVATEPTR;
		var->_Type = TypeID<Key>::Get();
		var->_Data = new Variant::PrivatePtrTpl< Key >( Key( val ) );
	}
};

template< typename T > struct VariantCast< KeyT< T > >
{
	static KeyT< T > Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< Key >::Get() )
		{
			return ( ( KeyT< T > * )val->ToPointer() )->GetPath();
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast< KeyT< T > * >
{
	static KeyT< T > * Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< Key >::Get() )
		{
			return ( ( KeyT< T > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast< const KeyT< T > * >
{
	static const KeyT< T > * Cast( const Variant * val )
	{
		if( val->IsPrivatePtr() && val->GetType() == TypeID< Key >::Get() )
		{
			return ( ( KeyT< T > * )val->ToPointer() );
		}

		throw VariantException( *val, "cast fail" );
	}
};

template< typename T > struct VariantCast< KeyT< T > & >
{
	static KeyT< T > & Cast( const Variant * val )
	{
		return *( VariantCast< KeyT< T > * >::Cast( val ) );
	}
};

template< typename T > struct VariantCast< const KeyT< T > & >
{
	static const KeyT< T > & Cast( const Variant * val )
	{
		return *( VariantCast< const KeyT< T > * >::Cast( val ) );
	}
};


template< typename T > struct Serializable< KeyT< T > >
{
public:
	static void Serialize( Archive & arc, KeyT< T > * val )
	{
		auto key = val->GetKey();

		arc & key;

		val->SetKey( key );
	}
};


END_XE_NAMESPACE

#endif // KEY_H__88D541E2_6D11_4128_AF3F_BC8253B6A753
