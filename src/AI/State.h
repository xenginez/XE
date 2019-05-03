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

#include "Type.h"

BEG_XE_NAMESPACE

class AI_API State
{
	OBJECT( State )

public:
	State();

	~State();

public:
	StateHandle GetHandle() const;

	const Array< Pair<ConditionPtr, StateHandle> >& GetConditions() const;

public:
	StateMachine * GetStateMachine() const;

	void SetStateMachine( StateMachine * val );

public:
	void Startup();

	void Update( float dt );

	void Clearup();

protected:
	virtual void OnStartup();

	virtual void OnUpdate( float dt );

	virtual void OnClearup();

private:
	StateHandle _Handle;
	StateMachine * _StateMachine;
	Array< Pair<ConditionPtr, StateHandle> > _Conditions;
};

END_XE_NAMESAPCE

#endif // __STATE_H__0F576F56_4DD5_458C_8B62_10766BAE42AF
