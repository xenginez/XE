#include "StateMachine.h"

#include "State.h"

BEG_META( AI::StateMachine )
type->Property( "Root", &AI::StateMachine::_Root );
type->Property( "States", &AI::StateMachine::_States );
END_META()

AI::StateMachine::StateMachine()
{

}

AI::StateMachine::~StateMachine()
{

}

void AI::StateMachine::Startup()
{
	Super::Startup();

	for( auto state : _States )
	{
		state->SetStateMachine( XE_THIS( StateMachine ) );
		state->Startup();

		for( auto & cond : state->_Conditions )
		{
			cond.SetAIModule( XE_THIS( Module ) );
		}
	}
}

void AI::StateMachine::Enter()
{
	Super::Enter();

	_Current = _Root;

	_States[_Current.GetValue()]->Enter();
}

void AI::StateMachine::Update( XE::float32 dt )
{
	Super::Update( dt );

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

void AI::StateMachine::Quit()
{
	_States[_Current.GetValue()]->Quit();

	Super::Quit();
}

void AI::StateMachine::Clearup()
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

	Super::Clearup();
}

AI::StateHandle AI::StateMachine::GetRoot() const
{
	return _Root;
}

void AI::StateMachine::SetRoot( AI::StateHandle val )
{
	_Root = val;
}

AI::StatePtr AI::StateMachine::GetCurrentState() const
{
	return _States[_Current.GetValue()];
}

AI::StatePtr AI::StateMachine::GetState( AI::StateHandle val )
{
	XE_ASSERT( val.GetValue() <= _States.size() );

	return _States[val.GetValue()];
}

const XE::Array< AI::StatePtr > & AI::StateMachine::GetStates() const
{
	return _States;
}

void AI::StateMachine::SetStates( const XE::Array< AI::StatePtr > & val )
{
	_States = val;
}

void AI::StateMachine::AssetLoad()
{
	Super::AssetLoad();

	for( auto & state : _States )
	{
		state->AssetLoad();
	}
}
