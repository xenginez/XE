/*!
 * \file   AIModule.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475
#define __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API AIModule : public XE::Object
{
	OBJECT( AIModule, Object )

public:
	using ProcessEventCallback = std::function<void( const XE::EventPtr & )>;

public:
	AIModule();

	~AIModule();

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

public:
	XE::Variant GetKey( const BlackboardKey & val ) const;

	void SetKey( const BlackboardKey & key, const XE::Variant & val );

	const XE::Map<XE::String, XE::Variant> & GetKeys() const;

	void SetKeys( const XE::Map<XE::String, XE::Variant> & val );

public:
	template< typename T > T GetKeyT( const BlackboardKeyKeyT<T> & val ) const
	{
		return GetKey( val ).Value<T>();
	}

	template< typename T > void SetKeyT( const BlackboardKeyKeyT<T> & key, const T & val )
	{
		SetKey( key, val );
	}

public:
	void AssetLoad() override;

public:
	void PostEvent( const XE::EventPtr & val );

	void SetProcessEventCallback( const ProcessEventCallback & val );

private:
	XE::String _Name;
	XE::Map<XE::String, XE::Variant> _Keys;
	ProcessEventCallback _ProcessEventCallback;
};

END_XE_NAMESPACE

#endif // __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475
