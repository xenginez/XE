#include "AnimationCondition.h"

#include "AnimationController.h"

USING_XE

BEG_META( AnimationCondition )
END_META()

AnimationCondition::AnimationCondition()
{

}

AnimationCondition::~AnimationCondition()
{

}

AnimationControllerPtr AnimationCondition::GetAnimationController() const
{
	return _Controller.lock();
}

void AnimationCondition::SetAnimationController( const AnimationControllerPtr & val )
{
	_Controller = val;
}

BEG_META( AnimationConditionBool )
type->Property( "KeyValue", &AnimationConditionBool::_KeyValue );
type->Property( "DefValue", &AnimationConditionBool::_DefValue );
END_META()

AnimationConditionBool::AnimationConditionBool()
	:_DefValue( false )
{

}

AnimationConditionBool::~AnimationConditionBool()
{

}

bool AnimationConditionBool::Condition() const
{
	return GetAnimationController()->GetParameterBool( _KeyValue ) == _DefValue;
}

BEG_META( AnimationConditionInt )
type->Property( "KeyValue", &AnimationConditionInt::_KeyValue );
type->Property( "Compare", &AnimationConditionInt::_Compare );
type->Property( "DefValue", &AnimationConditionInt::_DefValue );
END_META()

AnimationConditionInt::AnimationConditionInt()
	:_DefValue( 0 )
{

}

AnimationConditionInt::~AnimationConditionInt()
{

}

bool AnimationConditionInt::Condition() const
{
	switch( _Compare )
	{
	case XE::AnimationCompare::EQUAL:
		return GetAnimationController()->GetParameterInt( _KeyValue ) == _DefValue;
	case XE::AnimationCompare::LESS:
		return GetAnimationController()->GetParameterInt( _KeyValue ) < _DefValue;
	case XE::AnimationCompare::GREA:
		return GetAnimationController()->GetParameterInt( _KeyValue ) > _DefValue;
	case XE::AnimationCompare::LEQUAL:
		return GetAnimationController()->GetParameterInt( _KeyValue ) <= _DefValue;
	case XE::AnimationCompare::GEQUAL:
		return GetAnimationController()->GetParameterInt( _KeyValue ) >= _DefValue;
	case XE::AnimationCompare::NOTEQUAL:
		return GetAnimationController()->GetParameterInt( _KeyValue ) != _DefValue;
	}

	return false;
}

BEG_META( AnimationConditionFloat )
type->Property( "KeyValue", &AnimationConditionFloat::_KeyValue );
type->Property( "Compare", &AnimationConditionFloat::_Compare );
type->Property( "DefValue", &AnimationConditionFloat::_DefValue );
END_META()

AnimationConditionFloat::AnimationConditionFloat()
	:_DefValue( 0.0f )
{

}

AnimationConditionFloat::~AnimationConditionFloat()
{

}

bool AnimationConditionFloat::Condition() const
{
	switch( _Compare )
	{
	case XE::AnimationCompare::EQUAL:
		return GetAnimationController()->GetParameterFloat( _KeyValue ) == _DefValue;
	case XE::AnimationCompare::LESS:
		return GetAnimationController()->GetParameterFloat( _KeyValue ) < _DefValue;
	case XE::AnimationCompare::GREA:
		return GetAnimationController()->GetParameterFloat( _KeyValue ) > _DefValue;
	case XE::AnimationCompare::LEQUAL:
		return GetAnimationController()->GetParameterFloat( _KeyValue ) <= _DefValue;
	case XE::AnimationCompare::GEQUAL:
		return GetAnimationController()->GetParameterFloat( _KeyValue ) >= _DefValue;
	case XE::AnimationCompare::NOTEQUAL:
		return GetAnimationController()->GetParameterFloat( _KeyValue ) != _DefValue;
	}

	return false;
}

BEG_META( AnimationConditionString )
type->Property( "KeyValue", &AnimationConditionString::_KeyValue );
type->Property( "DefValue", &AnimationConditionString::_DefValue );
END_META()

AnimationConditionString::AnimationConditionString()
{

}

AnimationConditionString::~AnimationConditionString()
{

}

bool AnimationConditionString::Condition() const
{
	return GetAnimationController()->GetParameterString( _KeyValue ) == _DefValue;
}
