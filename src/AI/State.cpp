#include "State.h"

USING_XE

BEG_META( State )
type->Property( "Conditions", &State::_Conditions );
END_META()

XE::State::State()
{

}

XE::State::~State()
{

}

XE::StateHandle XE::State::GetHandle() const
{
	return _Handle;
}

const XE::Array< Pair<ConditionPtr, StateHandle> >& XE::State::GetConditions() const
{
	return _Conditions;
}

const XE::StateMachinePtr & XE::State::GetStateMachine() const
{
	return _StateMachine;
}

void XE::State::SetStateMachine( const XE::StateMachinePtr & val )
{
	_StateMachine = val;
}

void XE::State::Startup()
{
	OnStartup();
}

void XE::State::Update( XE::float32 dt )
{
	OnUpdate( dt );
}

void XE::State::Clearup()
{
	OnClearup();
}

void XE::State::OnStartup()
{

}

void XE::State::OnUpdate( XE::float32 dt )
{

}

void XE::State::OnClearup()
{

}
