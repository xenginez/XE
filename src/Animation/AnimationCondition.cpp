#include "AnimationCondition.h"

#include "AnimationController.h"



BEG_META( XE::AnimationCondition )
END_META()

XE::AnimationCondition::AnimationCondition()
{

}

XE::AnimationCondition::~AnimationCondition()
{

}

XE::AnimationControllerPtr XE::AnimationCondition::GetAnimationController() const
{
	return _Controller.lock();
}

void XE::AnimationCondition::SetAnimationController( const XE::AnimationControllerPtr & val )
{
	_Controller = val;
}

BEG_META( XE::AnimationConditionBool )
type->Property( "KeyValue", &AnimationConditionBool::_KeyValue );
type->Property( "DefValue", &AnimationConditionBool::_DefValue );
END_META()

XE::AnimationConditionBool::AnimationConditionBool()
	:_DefValue( false )
{

}

XE::AnimationConditionBool::~AnimationConditionBool()
{

}

bool XE::AnimationConditionBool::Condition() const
{
	return GetAnimationController()->GetParameterBool( _KeyValue ) == _DefValue;
}

BEG_META( XE::AnimationConditionInt )
type->Property( "KeyValue", &AnimationConditionInt::_KeyValue );
type->Property( "Compare", &AnimationConditionInt::_Compare );
type->Property( "DefValue", &AnimationConditionInt::_DefValue );
END_META()

XE::AnimationConditionInt::AnimationConditionInt()
	:_DefValue( 0 )
{

}

XE::AnimationConditionInt::~AnimationConditionInt()
{

}

bool XE::AnimationConditionInt::Condition() const
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

BEG_META( XE::AnimationConditionFloat )
type->Property( "KeyValue", &AnimationConditionFloat::_KeyValue );
type->Property( "Compare", &AnimationConditionFloat::_Compare );
type->Property( "DefValue", &AnimationConditionFloat::_DefValue );
END_META()

XE::AnimationConditionFloat::AnimationConditionFloat()
	:_DefValue( 0.0f )
{

}

XE::AnimationConditionFloat::~AnimationConditionFloat()
{

}

bool XE::AnimationConditionFloat::Condition() const
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

BEG_META( XE::AnimationConditionString )
type->Property( "KeyValue", &AnimationConditionString::_KeyValue );
type->Property( "DefValue", &AnimationConditionString::_DefValue );
END_META()

XE::AnimationConditionString::AnimationConditionString()
{

}

XE::AnimationConditionString::~AnimationConditionString()
{

}

bool XE::AnimationConditionString::Condition() const
{
	return GetAnimationController()->GetParameterString( _KeyValue ) == _DefValue;
}
