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

#include "AIModule.h"

BEG_XE_NAMESPACE

class AI_API StateMachine :  public XE::AIModule
{
	OBJECT( StateMachine, AIModule )

public:
	StateMachine();

	~StateMachine();

public:
	virtual void Startup() override;

	virtual void Update( XE::float32 dt ) override;

	virtual void Clearup() override;

private:
	StateHandle _Root;
	StateHandle _Current;
	Array< StatePtr > _States;
};

END_XE_NAMESPACE

#endif // __STATEMACHINE_H__3DD22731_F659_468F_92EE_F7E7F88C3CFE
