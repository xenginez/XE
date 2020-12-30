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

BEG_AI_NAMESPACE

class AI_API Condition : public XE::Object
{
	OBJECT( Condition, Object )

public:
	Condition();

	~Condition() override;

public:
	virtual bool Judgment() const;

public:
	const AI::ModulePtr & GetAIModule() const;

	void SetAIModule( const AI::ModulePtr & val );

	AI::StateHandle GetNextStateHandle() const;

	void SetNextStateHandle( AI::StateHandle val );

private:
	AI::ModulePtr _AIModule;
	AI::StateHandle _NextState;
};

class AI_API State : public XE::Object
{
	OBJECT( State, Object )

public:
	friend class StateMachine;

public:
	State();

	~State();

public:
	AI::StateHandle GetHandle() const;

	void SetHandle( AI::StateHandle val );

	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Array< AI::Condition > & GetConditions() const;

	void SetConditions( const XE::Array< AI::Condition > & val );

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
	AI::StateHandle _Handle;
	AI::StateMachinePtr _StateMachine;
	XE::Array< AI::Condition > _Conditions;
};

class AI_API SubState : public AI::State
{
	OBJECT( SubState, State )

public:
	SubState();

	~SubState();

public:
	const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<AI::BlackboardKey, AI::BlackboardKey> & val );

protected:
	void OnStartup() override;

	void OnEnter() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnQuit() override;

	void OnClearup() override;

	void AssetLoad() override;

private:
	XE::AssetInstance< AI::Module > _AIModule;
	XE::Map<AI::BlackboardKey, AI::BlackboardKey> _ConnectKeys;
};

END_AI_NAMESPACE

#endif // __STATE_H__0F576F56_4DD5_458C_8B62_10766BAE42AF
