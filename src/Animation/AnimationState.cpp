#include "AnimationState.h"

USING_XE

BEG_META( AnimationState )
END_META()

XE::AnimationState::AnimationState()
{

}

XE::AnimationState::~AnimationState()
{

}

void XE::AnimationState::Startup()
{

}

void XE::AnimationState::Entry()
{

}

void XE::AnimationState::Update( XE::float32 val )
{

}

void XE::AnimationState::Exit()
{

}

void XE::AnimationState::Clearup()
{

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
