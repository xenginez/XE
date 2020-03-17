#include "State.h"

#include "Condition.h"

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

void XE::State::AddConditions( const XE::ConditionPtr & val )
{
	_Conditions.push_back( val );
}

void XE::State::RemoveConditions( const XE::ConditionPtr & val )
{
	for( auto it = _Conditions.begin(); it != _Conditions.end(); ++it )
	{
		if( ( *it ) == val )
		{
			_Conditions.erase( it );
			return;
		}
	}
}

const XE::Array< ConditionPtr > & XE::State::GetConditions() const
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
