#include "AnimationState.h"

#include "AnimationTrigger.h"
#include "AnimationController.h"

USING_XE

BEG_META( AnimationState )
type->Property( "Looped", &AnimationState::_Looped );
type->Property( "WaitOut", &AnimationState::_WaitOut );
type->Property( "MaxTime", &AnimationState::_MaxTime );
type->Property( "Triggers", &AnimationState::_Triggers, IMetaProperty::NoDesign );
END_META()

XE::AnimationState::AnimationState()
	:_Looped( true ), _Playing( false ), _WaitOut( false )
{

}

XE::AnimationState::~AnimationState()
{

}

void XE::AnimationState::Startup()
{
	_Playing = true;
}

void XE::AnimationState::Entry()
{
	_Playing = true;
	_Time = 0.0f;

	for( auto & trigger : _Triggers )
	{
		trigger->_Sended = false;
	}

	OnEntry();
}

void XE::AnimationState::Update( XE::float32 val )
{
	if( _Playing )
	{
		_Time += val;

		OnUpdate( val );

		for( auto & trigger : _Triggers )
		{
			if( !trigger->_Sended && _Time >= trigger->_Time )
			{
				EventPtr event = XE::make_shared<Event>( trigger->GetEventHandle(), XE_THIS( AnimationState ), nullptr, trigger->GetEventParameter() );

				GetAnimationController()->GetGameObject()->ProcessEvent( event );

				trigger->_Sended = true;
			}
		}

		if( _Time > _MaxTime )
		{
			_Playing = false;
		}
	}
}

void XE::AnimationState::Exit()
{
	OnExit();

	_Time = 0.0f;
	_Playing = false;
}

void XE::AnimationState::Clearup()
{
	_Playing = false;
}

void AnimationState::OnEntry()
{

}

void AnimationState::OnUpdate( XE::float32 val )
{

}

void AnimationState::OnExit()
{

}

bool AnimationState::GetLooped() const
{
	return _Looped;
}

void AnimationState::SetLooped( bool val )
{
	_Looped = val;
}

bool AnimationState::GetPlaying() const
{
	return _Playing;
}

void AnimationState::SetPlaying( bool val )
{
	_Playing = val;
}

bool AnimationState::GetWaitOut() const
{
	return _WaitOut;
}

void AnimationState::SetWaitOut( bool val )
{
	_WaitOut = val;
}

const XE::Array<XE::uint32> & XE::AnimationState::GetTransitions() const
{
	return _Transitions;
}

void XE::AnimationState::SetTransitions( const Array<XE::uint32> & val )
{
	_Transitions = val;
}

const XE::Array<AnimationTriggerPtr> & AnimationState::GetTriggers() const
{
	return _Triggers;
}

void AnimationState::SetTriggers( const XE::Array<AnimationTriggerPtr> & val )
{
	_Triggers = val;
}

XE::AnimationControllerPtr XE::AnimationState::GetAnimationController() const
{
	return _Controller.lock();
}

void XE::AnimationState::SetAnimationController( const XE::AnimationControllerPtr & val )
{
	_Controller = val;
}


BEG_META( AnimationStateAny )
END_META()

AnimationStateAny::AnimationStateAny()
{

}

AnimationStateAny::~AnimationStateAny()
{

}
