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

BEG_AI_NAMESPACE

class AI_API Module : public XE::Object
{
	OBJECT( Module, Object )

	friend class BehaviorTree;
	friend class StateMachine;

public:
	using ProcessEventCallback = std::function<void( const XE::EventPtr & )>;

public:
	Module();

	~Module();

public:
	virtual void Startup();

	virtual void Enter();

	virtual void Update( XE::float32 dt );

	virtual void Quit();

	virtual void Clearup();

	virtual bool IsStopped() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

public:
	XE::Variant GetKey( const BlackboardKey & val ) const;

	void SetKey( const BlackboardKey & key, const XE::Variant & val );

	const XE::Map<XE::String, XE::Variant> & GetKeys() const;

	void SetKeys( const XE::Map<XE::String, XE::Variant> & val );

public:
	template< typename T > T GetKeyT( const BlackboardKeyPtr<T> & val ) const
	{
		return GetKey( val ).Value<T>();
	}

	template< typename T > void SetKeyT( const BlackboardKeyPtr<T> & key, const T & val )
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

END_AI_NAMESPACE

#endif // __AIMODULE_H__A590ED03_BAEC_4291_90B5_DBFC9EB9A475
