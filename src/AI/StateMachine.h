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

class XE_API StateMachine :  public XE::AIModule
{
	OBJECT( StateMachine, AIModule )

public:
	StateMachine();

	~StateMachine();

public:
	void Startup() override;

	void Update( XE::float32 dt ) override;

	void Clearup() override;

	void AssetLoad() override;

public:
	XE::AIStateHandle GetRoot() const;

	void SetRoot( XE::AIStateHandle val );

	XE::AIStatePtr GetCurrentState() const;

	XE::AIStatePtr GetState( XE::AIStateHandle val );

	const XE::Array< XE::AIStatePtr > & GetStates() const;

	void SetStates( const XE::Array< XE::AIStatePtr > & val );

private:
	AIStateHandle _Root;
	AIStateHandle _Current;
	Array< AIStatePtr > _States;
};

END_XE_NAMESPACE

#endif // __STATEMACHINE_H__3DD22731_F659_468F_92EE_F7E7F88C3CFE
