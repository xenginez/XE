#include "StateMachine.h"

#include "State.h"
#include "Condition.h"

USING_XE

BEG_META( StateMachine )
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

	for (auto s : _States)
	{
		s->SetStateMachine( XE_THIS( StateMachine ) );

		auto conds = s->GetConditions();
		for ( auto cond : conds )
		{
			cond.first->SetAIModule( XE_THIS( AIModule ) );
		}
	}

	_States[_Current.GetValue()]->Startup();
}

void XE::StateMachine::Update( XE::float32 dt )
{
	StatePtr s = _States[_Current.GetValue()];

	auto conds = s->GetConditions();
	for ( auto c : conds )
	{
		if (c.first->Judgment())
		{
			s->Clearup();

			_Current = c.second;

			s = _States[_Current.GetValue()];

			s->Startup();

			break;
		}
	}

	s->Update( dt );
}

void XE::StateMachine::Clearup()
{
	_States[_Current.GetValue()]->Clearup();
}
