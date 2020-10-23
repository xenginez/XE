#include "AnimationState.h"

#include "AnimationController.h"

BEG_META( XE::AnimationState )
END_META()

XE::AnimationState::AnimationState()
{

}

XE::AnimationState::~AnimationState()
{

}

XE::AnimationControllerPtr XE::AnimationState::GetAnimationController() const
{
	return SP_CAST< XE::AnimationController >( GetStateMachine() );
}
