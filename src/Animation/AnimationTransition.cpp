#include "AnimationTransition.h"

#include "AnimationCondition.h"



BEG_META( XE::AnimationTransition )
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

XE::AnimationControllerPtr XE::AnimationTransition::GetAnimationController() const
{
	return _Controller.lock();
}

void XE::AnimationTransition::SetAnimationController( const XE::AnimationControllerPtr & val )
{
	_Controller = val;

	for( auto & cond : _Conditions )
	{
		cond->SetAnimationController( val );
	}
}

const XE::Array<XE::AnimationConditionPtr> & XE::AnimationTransition::GetAnimationConditions() const
{
	return _Conditions;
}

void XE::AnimationTransition::SetAnimationConditions( const XE::Array<XE::AnimationConditionPtr> & val )
{
	_Conditions = val;
}
