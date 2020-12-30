/*!
 * \file   StateMachine.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/14
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __STATEMACHINE_H__3DD22731_F659_468F_92EE_F7E7F88C3CFE
#define __STATEMACHINE_H__3DD22731_F659_468F_92EE_F7E7F88C3CFE

#include "Module.h"

BEG_AI_NAMESPACE

class AI_API StateMachine :  public AI::Module
{
	OBJECT( StateMachine, Module )

public:
	StateMachine();

	~StateMachine();

public:
	void Startup() override;

	void Enter() override;

	void Update( XE::float32 dt ) override;

	void Quit() override;

	void Clearup() override;

	void AssetLoad() override;

public:
	AI::StateHandle GetRoot() const;

	void SetRoot( AI::StateHandle val );

	AI::StatePtr GetCurrentState() const;

	AI::StatePtr GetState( AI::StateHandle val );

	const XE::Array< AI::StatePtr > & GetStates() const;

	void SetStates( const XE::Array< AI::StatePtr > & val );

private:
	AI::StateHandle _Root;
	AI::StateHandle _Current;
	XE::Array< AI::StatePtr > _States;
};

END_AI_NAMESPACE

#endif // __STATEMACHINE_H__3DD22731_F659_468F_92EE_F7E7F88C3CFE
