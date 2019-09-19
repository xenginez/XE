#include "AnimationIKConstraint.h"

#include <ik/constraint.h>
#include <ik/node.h>

USING_XE

BEG_META( AnimationIKConstraint )
type->Property( "Stiffness", &AnimationIKConstraint::_Stiffness );
type->Property( "Stretchiness", &AnimationIKConstraint::_Stretchiness );
type->Property( "LengthConstraints", &AnimationIKConstraint::_LengthConstraints );
END_META()

XE::AnimationIKConstraint::AnimationIKConstraint()
	:_Stiffness( 0.0f ), _Stretchiness( 0.0f )
{

}

XE::AnimationIKConstraint::~AnimationIKConstraint()
{

}

IKConstraintHandle AnimationIKConstraint::GetHandle() const
{
	return _Handle;
}

void AnimationIKConstraint::SetHandle( IKConstraintHandle val )
{
	_Handle = val;
}

XE::float32 AnimationIKConstraint::GetStiffness() const
{
	return _Stiffness;
}

void AnimationIKConstraint::SetStiffness( XE::float32 val )
{
	_Stiffness = Mathf::Clamp( val, 0.0f, 1.0f );
}

XE::float32 AnimationIKConstraint::GetStretchiness() const
{
	return _Stretchiness;
}

void AnimationIKConstraint::SetStretchiness( XE::float32 val )
{
	_Stretchiness = val;
}

const XE::Vec2 & AnimationIKConstraint::GetLengthConstraints() const
{
	return _LengthConstraints;
}

void AnimationIKConstraint::SetLengthConstraints( const XE::Vec2 & val )
{
	_LengthConstraints = val;
}
