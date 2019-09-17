#include "AnimationTransition.h"

#include "AnimationCondition.h"

USING_XE

BEG_META( AnimationTransition )
type->Property( "State", &AnimationTransition::_State );
type->Property( "Conditions", &AnimationTransition::_Conditions );
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
	for( auto & cond : _Conditions )
	{
		if( !cond->Condition() )
		{
			return false;
		}
	}

	return true;
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

	for( auto & cond : _Conditions )
	{
		cond->SetAnimationController( val );
	}
}

const Array<AnimationConditionPtr> & AnimationTransition::GetAnimationConditions() const
{
	return _Conditions;
}

void AnimationTransition::SetAnimationConditions( const Array<AnimationConditionPtr> & val )
{
	_Conditions = val;
}
