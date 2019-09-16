#include "Animator.h"

#include "AnimationState.h"
#include "AnimationTransition.h"

USING_XE

BEG_META( Animator )
type->Property( "Name", &Animator::_Name );
type->Property( "Enable", &Animator::_Enable );
type->Property( "IsPlaying", &Animator::_IsPlaying );
type->Property( "States", &Animator::_States );
type->Property( "Transitions", &Animator::_Transitions );
END_META()

XE::Animator::Animator()
	:_Enable( true ), _IsPlaying( true ), _CurState( 0 )
{

}

XE::Animator::~Animator()
{

}

void XE::Animator::Startup()
{
	for( auto & stat : _States )
	{
		stat->SetAnimationController( GetAnimationController() );
		stat->Startup();
	}

	for( auto & tran : _Transitions )
	{
		tran->SetAnimationController( GetAnimationController() );
	}

	_States[0]->Entry();
}

void XE::Animator::Update( XE::float32 val )
{
	_States[_CurState]->Update( val );

	const auto & trans = _States[_CurState]->GetTransitions();

	for( auto i : trans )
	{
		if( _Transitions[i]->Condition() )
		{
			_States[_CurState]->Exit();
			_CurState = _Transitions[i]->GetNextState();
			_States[_CurState]->Entry();
		}
	}
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

}

void XE::Animator::Deactivate()
{

}

void XE::Animator::Play()
{
	_IsPlaying = true;
}

void XE::Animator::Stop()
{
	_IsPlaying = false;
}

bool XE::Animator::IsEnable() const
{
	return _Enable;
}

bool XE::Animator::IsPlaying() const
{
	return _IsPlaying;
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
