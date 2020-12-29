#include "AnimationCondition.h"

BEG_META( XE::AnimationCondition )
type->Property( "NextState", &XE::AnimationCondition::_NextState );
END_META()

XE::AnimationCondition::AnimationCondition()
{

}

XE::AnimationCondition::~AnimationCondition()
{

}

XE::AnimationStateHandle XE::AnimationCondition::GetNextStateHandle() const
{
	return _NextState;
}

void XE::AnimationCondition::SetNextStateHandle( XE::AnimationStateHandle val )
{
	_NextState = val;
}

XE::AnimationControllerPtr XE::AnimationCondition::GetAnimationController() const
{
	return _AnimationController.lock();
}

void XE::AnimationCondition::SetAnimationController( XE::AnimationControllerPtr val )
{
	_AnimationController = val;
}
