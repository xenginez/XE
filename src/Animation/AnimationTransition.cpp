#include "AnimationTransition.h"

USING_XE

BEG_META( AnimationTransition )
END_META()

XE::AnimationTransition::AnimationTransition()
	:_State( 0 )
{

}

XE::AnimationTransition::~AnimationTransition()
{

}

bool XE::AnimationTransition::Condition()
{
	return false;
}

XE::uint32 XE::AnimationTransition::GetNextState() const
{
	return _State;
}

void XE::AnimationTransition::SetNextState( XE::uint32 val )
{
	_State = val;
}

AnimationControllerPtr XE::AnimationTransition::GetAnimationController() const
{
	return _Controller.lock();
}

void XE::AnimationTransition::SetAnimationController( const AnimationControllerPtr & val )
{
	_Controller = val;
}
