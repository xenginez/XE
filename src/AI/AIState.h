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

#include "Utils/Asset.h"

#include "BlackboardKey.h"

BEG_XE_NAMESPACE

class XE_API Condition : public XE::Object
{
	OBJECT( Condition, Object )

public:
	Condition();

	~Condition() override;

public:
	virtual bool Judgment() const;

public:
	const XE::AIModulePtr & GetAIModule() const;

	void SetAIModule( const XE::AIModulePtr & val );

	XE::AIStateHandle GetNextStateHandle() const;

	void SetNextStateHandle( XE::AIStateHandle val );

private:
	XE::AIModulePtr _AIModule;
	XE::AIStateHandle _NextState;
};

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

	const XE::Array< XE::Condition > & GetConditions() const;

	void SetConditions( const XE::Array< XE::Condition > & val );

public:
	const StateMachinePtr & GetStateMachine() const;

private:
	void SetStateMachine( const StateMachinePtr & val );

public:
	virtual void Startup();

	virtual void Enter();

	virtual void Update( XE::float32 dt );

	virtual void Quit();

	virtual void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnEnter();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnQuit();

	virtual void OnClearup();

private:
	XE::String _Name;
	XE::AIStateHandle _Handle;
	XE::StateMachinePtr _StateMachine;
	XE::Array< XE::Condition > _Conditions;
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
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

	void AssetLoad() override;

private:
	XE::AssetInstance< XE::AIModule > _AIModule;
	XE::Map<XE::BlackboardKey, XE::BlackboardKey> _ConnectKeys;
};

END_XE_NAMESPACE

#endif // __STATE_H__0F576F56_4DD5_458C_8B62_10766BAE42AF
