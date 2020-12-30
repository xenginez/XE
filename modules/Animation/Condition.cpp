#include "Condition.h"

BEG_META( Animation::Condition )
type->Property( "NextState", &Animation::Condition::_NextState );
END_META()

Animation::Condition::Condition()
{

}

Animation::Condition::~Condition()
{

}

Animation::StateHandle Animation::Condition::GetNextStateHandle() const
{
	return _NextState;
}

void Animation::Condition::SetNextStateHandle( Animation::StateHandle val )
{
	_NextState = val;
}

Animation::ControllerPtr Animation::Condition::GetAnimationController() const
{
	return _AnimationController.lock();
}

void Animation::Condition::SetAnimationController( Animation::ControllerPtr val )
{
	_AnimationController = val;
}
