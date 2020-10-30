#include "StateMachine.h"

#include "AIState.h"

BEG_META( XE::StateMachine )
type->Property( "Root", &StateMachine::_Root );
type->Property( "States", &StateMachine::_States );
END_META()

XE::StateMachine::StateMachine()
{

}

XE::StateMachine::~StateMachine()
{

}

void XE::StateMachine::Startup()
{
	for( auto state : _States )
	{
		state->SetStateMachine( XE_THIS( StateMachine ) );
		state->Startup();

		for( auto & cond : state->_Conditions )
		{
			cond.SetAIModule( XE_THIS( AIModule ) );
		}
	}

	_Current = _Root;

	_States[_Current.GetValue()]->Enter();
}

void XE::StateMachine::Update( XE::float32 dt )
{
	for( auto cond : _States[_Current.GetValue()]->_Conditions )
	{
		if( cond.Judgment() )
		{
			auto next = _States[cond.GetNextStateHandle()];

			_States[_Current.GetValue()]->Quit();

			_Current = cond.GetNextStateHandle();

			_States[_Current.GetValue()]->Enter();

			break;
		}
	}

	_States[_Current.GetValue()]->Update( dt );
}

void XE::StateMachine::Clearup()
{
	for( auto & state : _States )
	{
		for( auto & cond : state->_Conditions )
		{
			cond.SetAIModule( nullptr );
		}

		state->Clearup();
		state->SetStateMachine( nullptr );
	}
}

XE::AIStateHandle XE::StateMachine::GetRoot() const
{
	return _Root;
}

void XE::StateMachine::SetRoot( XE::AIStateHandle val )
{
	_Root = val;
}

XE::AIStatePtr XE::StateMachine::GetCurrentState() const
{
	return _States[_Current.GetValue()];
}

XE::AIStatePtr XE::StateMachine::GetState( XE::AIStateHandle val )
{
	XE_ASSERT( val.GetValue() <= _States.size() );

	return _States[val.GetValue()];
}

const XE::Array< XE::AIStatePtr > & XE::StateMachine::GetStates() const
{
	return _States;
}

void XE::StateMachine::SetStates( const XE::Array< XE::AIStatePtr > & val )
{
	_States = val;
}

void XE::StateMachine::AssetLoad()
{
	Super::AssetLoad();

	for( auto & state : _States )
	{
		state->AssetLoad();
	}
}
