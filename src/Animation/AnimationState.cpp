#include "AnimationState.h"

USING_XE

BEG_META( AnimationState )
type->Property( "Looped", &AnimationState::_Looped );
type->Property( "WaitOut", &AnimationState::_WaitOut );
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
}

void XE::AnimationState::Update( XE::float32 val )
{

}

void XE::AnimationState::Exit()
{
	_Playing = false;
}

void XE::AnimationState::Clearup()
{
	_Playing = false;
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
