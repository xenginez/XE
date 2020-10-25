#include "StateMachine.h"

#include "AIState.h"
#include "Condition.h"

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
	_Current = _Root;

	for( auto state : _States )
	{
		state->SetStateMachine( XE_THIS( StateMachine ) );

		auto conds = state->GetConditions();
		for( auto cond : conds )
		{
			cond->SetAIModule( XE_THIS( AIModule ) );
		}
	}

	_States[_Current.GetValue()]->Startup();
}

void XE::StateMachine::Update( XE::float32 dt )
{
	AIStatePtr current = _States[_Current.GetValue()];

	auto conds = current->GetConditions();
	for( auto cond : conds )
	{
		if( cond->Judgment() )
		{
			auto next = _States[cond->GetNextStateHandle()];

			current->Clearup();

			_Current = cond->GetNextStateHandle();

			next->Startup();

			break;
		}
	}

	_States[_Current.GetValue()]->Update( dt );
}

void XE::StateMachine::Clearup()
{
	_States[_Current.GetValue()]->Clearup();
}

XE::AIStateHandle XE::StateMachine::GetRoot() const
{
	return _Root;
}

void XE::StateMachine::SetRoot( XE::AIStateHandle val )
{
	_Root = val;
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
