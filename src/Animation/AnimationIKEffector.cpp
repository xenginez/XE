#include "AnimationIKEffector.h"

#include <ik/node.h>
#include <ik/effector.h>
#include <ik/solver.h>
#include <ik/util.h>

USING_XE

BEG_META( AnimationIKEffector )
END_META()

XE::AnimationIKEffector::AnimationIKEffector()
	:_WeightNlerp( false ), _InheritParentRotation( false ), _ChainLength( 0 ), _Weight( 0.0f ), _RotationWeight( 0.0f ), _RotationDecay( 0.0f )
{

}

XE::AnimationIKEffector::~AnimationIKEffector()
{

}

IKEffectorHandle AnimationIKEffector::GetHandle() const
{
	return _Handle;
}

void AnimationIKEffector::SetHandle( IKEffectorHandle val )
{
	_Handle = val;
}

bool AnimationIKEffector::GetWeightNlerp() const
{
	return _WeightNlerp;
}

void AnimationIKEffector::SetWeightNlerp( bool val )
{
	_WeightNlerp = val;
}

bool AnimationIKEffector::GetInheritParentRotation() const
{
	return _InheritParentRotation;
}

void AnimationIKEffector::SetInheritParentRotation( bool val )
{
	_InheritParentRotation = val;
}

const XE::Vec3 & AnimationIKEffector::GetTargetPosition() const
{
	return _TargetPosition;
}

void AnimationIKEffector::SetTargetPosition( const XE::Vec3 & val )
{
	_TargetPosition = val;
}

const XE::Quat & AnimationIKEffector::GetTargetRotation() const
{
	return _TargetRotation;
}

void AnimationIKEffector::SetTargetRotation( const XE::Quat & val )
{
	_TargetRotation = val;
}

XE::uint32 AnimationIKEffector::GetChainLength() const
{
	return _ChainLength;
}

void AnimationIKEffector::SetChainLength( XE::uint32 val )
{
	_ChainLength = val;
}

XE::float32 AnimationIKEffector::GetWeight() const
{
	return _Weight;
}

void AnimationIKEffector::SetWeight( XE::float32 val )
{
	_Weight = val;
}

XE::float32 AnimationIKEffector::GetRotationWeight() const
{
	return _RotationWeight;
}

void AnimationIKEffector::SetRotationWeight( XE::float32 val )
{
	_RotationWeight = val;
}

XE::float32 AnimationIKEffector::GetRotationDecay() const
{
	return _RotationDecay;
}

void AnimationIKEffector::SetRotationDecay( XE::float32 val )
{
	_RotationDecay = val;
}
