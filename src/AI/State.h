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

#include "Key.h"
#include "Item.h"

BEG_XE_NAMESPACE

class XE_API State : public XE::Item
{
	OBJECT( State, Item )

public:
	friend class StateMachine;

public:
	State();

	~State();

public:
	StateHandle GetHandle() const;

public:
	void AddConditions( const XE::ConditionPtr & val );

	void RemoveConditions( const XE::ConditionPtr & val );

	const Array< ConditionPtr > & GetConditions() const;

public:
	const StateMachinePtr & GetStateMachine() const;

	void SetStateMachine( const StateMachinePtr & val );

public:
	virtual void Startup();

	virtual void Update( XE::float32 dt );

	virtual void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( XE::float32 dt );

	virtual void OnClearup();

private:
	StateHandle _Handle;
	StateMachinePtr _StateMachine;
	Array< ConditionPtr > _Conditions;
};

class XE_API SubState : public XE::State
{
	OBJECT( SubState, State )

public:
	SubState();

	~SubState();

public:
	const XE::Map<XE::Key, XE::Key> & GetConnectKeys() const;

	void SetConnectKeys( const XE::Map<XE::Key, XE::Key> & val );

protected:
	virtual void OnStartup() override;

	virtual void OnUpdate( XE::float32 dt ) override;

	virtual void OnClearup() override;

private:
	XE::AIModulePtr _SubAI;
	XE::FileSystem::Path _SubAIPath;
	XE::Map<XE::Key, XE::Key> _ConnectKeys;
};

END_XE_NAMESPACE

#endif // __STATE_H__0F576F56_4DD5_458C_8B62_10766BAE42AF
