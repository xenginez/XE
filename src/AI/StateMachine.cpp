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
		s->SetStateMachine( this );

		auto conds = s->GetConditions();
		for ( auto cond : conds )
		{
			cond.first->SetAIModule( this );
		}
	}

	_States[_Current.GetValue()]->Startup();
}

void XE::StateMachine::Update( XE::real dt )
{
	StatePtr s = _States[_Current.GetValue()];

	s->Update( dt );

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
}

void XE::StateMachine::Clearup()
{
	_States[_Current.GetValue()]->Clearup();
}
