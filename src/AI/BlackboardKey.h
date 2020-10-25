/*!
 * \file	BlackboardKey.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BLACKBOARDKEY_H__039DE917_DC54_42D8_9A9D_0F3B8F39069A
#define BLACKBOARDKEY_H__039DE917_DC54_42D8_9A9D_0F3B8F39069A

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API BlackboardKey
{
public:
	BlackboardKey();

	BlackboardKey( const BlackboardKey & val );

	BlackboardKey( const XE::String & val );

	~BlackboardKey();

public:
	bool operator<( const BlackboardKey & val ) const;

	bool operator>( const BlackboardKey & val ) const;

	bool operator<=( const BlackboardKey & val ) const;

	bool operator>=( const BlackboardKey & val ) const;

	bool operator==( const BlackboardKey & val ) const;

	bool operator!=( const BlackboardKey & val ) const;

public:
	const XE::String & GetKey() const;

	void SetKey( const XE::String & val );

private:
	XE::String _Key;
};
DECL_META_CLASS( XE_API, BlackboardKey );

template< typename T, typename A > class BlackboardKeyPtr : public XE::BlackboardKey
{
public:
	using ValueType = T;
	using AIModuleType = A;

public:
	BlackboardKeyPtr() = default;

	~BlackboardKeyPtr() = default;

public:
	ValueType Get() const
	{
		XE_ASSERT( _Module != nullptr && "" );

		return _Module->GetKey( GetKey() ).Value< ValueType >();
	}

	void Set( const ValueType & val ) const
	{
		XE_ASSERT( _Module != nullptr && "" );

		_Module->SetKey( GetKey(), val );
	}

private:
	XE::SharedPtr< AIModuleType > _Module;
};

END_XE_NAMESPACE

template< typename T, typename A > struct XE::ClassID< XE::BlackboardKeyPtr< T, A > >
{
	static XE::IMetaClassPtr Get( const XE::BlackboardKeyPtr< T, A > * val = nullptr )
	{
		return XE::ClassID< XE::BlackboardKey >::Get();
	}
};

#endif // BLACKBOARDKEY_H__039DE917_DC54_42D8_9A9D_0F3B8F39069A
