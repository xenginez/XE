#include "Joint.h"

#include "Math/Mathf.h"

BEG_META( XE::Joint )
END_META()

XE::Joint::Joint()
{

}

XE::Joint::~Joint()
{

}

XE::JointHandle XE::Joint::GetHandle() const
{
	return _Handle;
}

void XE::Joint::SetHandle( XE::JointHandle val )
{
	_Handle = val;
}

XE::ConstraintHandle XE::Joint::GetConstraintHandle() const
{
	return _ConstraintHandle;
}

void XE::Joint::SetConstraintHandle( XE::ConstraintHandle val )
{
	_ConstraintHandle = val;
}

XE::PhysicsSceneHandle XE::Joint::GetPhysicsSceneHandle() const
{
	return _PhysicsSceneHandle;
}

void XE::Joint::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_PhysicsSceneHandle = val;
}

const XE::String & XE::Joint::GetName() const
{
	return _Name;
}

void XE::Joint::SetName( const XE::String & val )
{
	_Name = val;
}

XE::float32 XE::Joint::GetBreakForce() const
{
	return _BreakForce;
}

void XE::Joint::SetBreakForce( XE::float32 val )
{
	_BreakForce = val;
}

XE::float32 XE::Joint::GetBreakTorque() const
{
	return _BreakTorque;
}

void XE::Joint::SetBreakTorque( XE::float32 val )
{
	_BreakTorque = val;
}

XE::float32 XE::Joint::GetFirstInvMassScale() const
{
	return _FirstInvMassScale;
}

void XE::Joint::SetFirstInvMassScale( XE::float32 val )
{
	_FirstInvMassScale = val;
}

XE::float32 XE::Joint::GetSecondInvMassScale() const
{
	return _SecondInvMassScale;
}

void XE::Joint::SetSecondInvMassScale( XE::float32 val )
{
	_SecondInvMassScale = val;
}

XE::float32 XE::Joint::GetFirstInvInertiaScale() const
{
	return _FirstInvInertiaScale;
}

void XE::Joint::SetFirstInvInertiaScale( XE::float32 val )
{
	_FirstInvInertiaScale = val;
}

XE::float32 XE::Joint::GetSecondInvInertiaScale() const
{
	return _SecondInvInertiaScale;
}

void XE::Joint::SetSecondInvInertiaScale( XE::float32 val )
{
	_SecondInvInertiaScale = val;
}

XE::ConstraintFlags XE::Joint::GetConstraintFlags() const
{
	return _ConstraintFlags;
}

void XE::Joint::SetConstraintFlags( XE::ConstraintFlags val )
{
	_ConstraintFlags = val;
}

const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & XE::Joint::GetRigidActorHandle() const
{
	return _RigidActor;
}

void XE::Joint::SetRigidActorHandle( const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & val )
{
	_RigidActor = val;
}

const XE::Mat4f & XE::Joint::GetRelativeTransform() const
{
	return _RelativeTransform;
}

void XE::Joint::SetRelativeTransform( const XE::Mat4f & val )
{
	_RelativeTransform = val;
}

const XE::Vec3f & XE::Joint::GetRelativeLinearVelocity() const
{
	return _RelativeLinearVelocity;
}

void XE::Joint::SetRelativeLinearVelocity( const XE::Vec3f & val )
{
	_RelativeLinearVelocity = val;
}

const XE::Vec3f & XE::Joint::GetRelativeAngularVelocity() const
{
	return _RelativeAngularVelocity;
}

void XE::Joint::SetRelativeAngularVelocity( const XE::Vec3f & val )
{
	_RelativeAngularVelocity = val;
}
