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

	for( auto s : _States )
	{
		s->SetStateMachine( XE_THIS( StateMachine ) );

		auto conds = s->GetConditions();
		for( auto cond : conds )
		{
			cond->SetAIModule( XE_THIS( AIModule ) );
		}
	}

	_States[_Current.GetValue()]->Startup();
}

void XE::StateMachine::Update( XE::float32 dt )
{
	StatePtr s = _States[_Current.GetValue()];

	auto conds = s->GetConditions();
	for( auto c : conds )
	{
		if( c->Judgment() )
		{
			s->Clearup();

			_Current = c->GetNextStateHandle();

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

XE::StateHandle XE::StateMachine::GetRoot() const
{
	return _Root;
}

void XE::StateMachine::SetRoot( XE::StateHandle val )
{
	_Root = val;
}

XE::StatePtr XE::StateMachine::GetState( XE::StateHandle val )
{
	XE_ASSERT( val.GetValue() <= _States.size() );

	return _States[val.GetValue()];
}

const XE::Array< XE::StatePtr > & XE::StateMachine::GetAllState() const
{
	return _States;
}

XE::StateHandle XE::StateMachine::AddState( const XE::IMetaClassPtr & val )
{
	if( val->CanConvert( XE::State::GetMetaClassStatic() ) )
	{
		auto state = val->ConstructPtr().Value<XE::StatePtr>();

		state->SetName( val->GetName() );
		state->SetStateMachine( XE_THIS( XE::StateMachine ) );

		for( XE::uint64 i = 0; i < _States.size(); ++i )
		{
			if( _States[i] == nullptr )
			{
				state->_Handle = i;
				_States[i] = state;
				return state->_Handle;
			}
		}

		state->_Handle = _States.size();
		_States.push_back( state );
		return state->_Handle;
	}

	return XE::StateHandle::Invalid;
}

void XE::StateMachine::RemoveState( XE::StateHandle val )
{
	XE_ASSERT( val.GetValue() < _States.size() );

	_States[val.GetValue()] = nullptr;

	for( auto & s : _States )
	{
		if( s )
		{
			for( auto it = s->_Conditions.begin(); it != s->_Conditions.end(); ++it )
			{
				if( ( *it )->GetNextStateHandle() == val )
				{
					it = s->_Conditions.erase( it );
				}
			}
		}
	}
}
