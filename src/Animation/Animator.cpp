#include "Animator.h"

#include "AnimationState.h"
#include "AnimationTransition.h"

USING_XE

BEG_META( Animator )
type->Property( "Name", &Animator::_Name );
type->Property( "Enable", &Animator::_Enable );
type->Property( "States", &Animator::_States, IMetaProperty::NoDesign );
type->Property( "EntryState", &Animator::_EntryState, IMetaProperty::NoDesign );
type->Property( "Transitions", &Animator::_Transitions, IMetaProperty::NoDesign );
END_META()

XE::Animator::Animator()
	:_Enable( true ), _CurState( 0 ), _EntryState( 0 )
{

}

XE::Animator::~Animator()
{

}

void XE::Animator::Startup()
{
	_CurState = _EntryState;

	for( auto & stat : _States )
	{
		stat->SetAnimationController( GetAnimationController() );
		stat->Startup();
	}

	for( auto & tran : _Transitions )
	{
		tran->SetAnimationController( GetAnimationController() );
	}

	_States[_CurState]->Entry();
}

void XE::Animator::Update( XE::float32 val )
{
	XE::uint32 next_state = npos;

	const auto & anytrans = _States[AnyState]->GetTransitions();
	for( auto i : anytrans )
	{
		if( _Transitions[i]->Condition() )
		{
			next_state = _Transitions[i]->GetNextState();
			break;
		}
	}

	if( next_state == npos )
	{
		const auto & trans = _States[_CurState]->GetTransitions();
		for( auto i : trans )
		{
			if( _Transitions[i]->Condition() )
			{
				next_state = _Transitions[i]->GetNextState();
				break;
			}
		}
	}

	if( next_state != npos )
	{
		_States[_CurState]->Exit();
		_CurState = next_state;
		_States[_CurState]->Entry();
	}

	_States[_CurState]->Update( val );
}

void XE::Animator::Clearup()
{
	for( auto & stat : _States )
	{
		stat->Clearup();
	}

	_States.clear();
	_Transitions.clear();
	_CurState = 0;
}

void XE::Animator::Activate()
{
	if ( !_Enable )
	{
		_CurState = _EntryState;

		_States[_CurState]->Entry();

		_Enable = true;
	}
}

void XE::Animator::Deactivate()
{
	if( _Enable )
	{
		_States[_CurState]->Exit();

		_CurState = 0;

		_Enable = false;
	}
}

bool XE::Animator::IsEnable() const
{
	return _Enable;
}

const XE::String & XE::Animator::GetName() const
{
	return _Name;
}

void XE::Animator::SetName( const XE::String & val )
{
	_Name = val;
}

XE::AnimationControllerPtr XE::Animator::GetAnimationController() const
{
	return _Controller.lock();
}

void XE::Animator::SetAnimationController( const XE::AnimationControllerPtr & val )
{
	_Controller = val;
}
