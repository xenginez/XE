/*!
 * \file   State.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __STATE_H__0F576F56_4DD5_458C_8B62_10766BAE42AF
#define __STATE_H__0F576F56_4DD5_458C_8B62_10766BAE42AF

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API AIState : public XE::Object
{
	OBJECT( AIState, Object )

public:
	friend class StateMachine;

public:
	AIState();

	~AIState();

public:
	AIStateHandle GetHandle() const;

	void SetHandle( XE::AIStateHandle val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Array< XE::ConditionPtr > & GetConditions() const;

	void SetConditions( const XE::Array< XE::ConditionPtr > & val );

public:
	StateMachinePtr GetStateMachine() const;

private:
	void SetStateMachine( StateMachinePtr val );

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnClearup();

private:
	XE::String _Name;
	XE::AIStateHandle _Handle;
	XE::StateMachineWPtr _StateMachine;
	XE::Array< XE::ConditionPtr > _Conditions;
};

class XE_API SubState : public XE::AIState
{
	OBJECT( SubState, AIState )

public:
	SubState();

	~SubState();

public:
	const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<XE::BlackboardKey, XE::BlackboardKey> & val );

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::AIModulePtr _SubAI;
	XE::FileSystem::Path _SubAIPath;
	XE::Map<XE::BlackboardKey, XE::BlackboardKey> _ConnectKeys;
};

END_XE_NAMESPACE

#endif // __STATE_H__0F576F56_4DD5_458C_8B62_10766BAE42AF
