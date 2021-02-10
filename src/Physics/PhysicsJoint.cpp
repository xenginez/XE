#include "PhysicsJoint.h"

#include "Math/Mathf.h"

BEG_META( XE::PhysicsJoint )
END_META()

XE::PhysicsJoint::PhysicsJoint()
{

}

XE::PhysicsJoint::~PhysicsJoint()
{

}

XE::PhysicsJointHandle XE::PhysicsJoint::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsJoint::SetHandle( XE::PhysicsJointHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::PhysicsJoint::GetPhysicsSceneHandle() const
{
	return _PhysicsSceneHandle;
}

void XE::PhysicsJoint::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_PhysicsSceneHandle = val;
}

XE::PhysicsConstraintHandle XE::PhysicsJoint::GetConstraintHandle() const
{
	return _ConstraintHandle;
}

void XE::PhysicsJoint::SetConstraintHandle( XE::PhysicsConstraintHandle val )
{
	_ConstraintHandle = val;
}

const XE::String & XE::PhysicsJoint::GetName() const
{
	return _Name;
}

void XE::PhysicsJoint::SetName( const XE::String & val )
{
	_Name = val;
}

XE::float32 XE::PhysicsJoint::GetBreakForce() const
{
	return _BreakForce;
}

void XE::PhysicsJoint::SetBreakForce( XE::float32 val )
{
	_BreakForce = val;
}

XE::float32 XE::PhysicsJoint::GetBreakTorque() const
{
	return _BreakTorque;
}

void XE::PhysicsJoint::SetBreakTorque( XE::float32 val )
{
	_BreakTorque = val;
}

XE::float32 XE::PhysicsJoint::GetFirstInvMassScale() const
{
	return _FirstInvMassScale;
}

void XE::PhysicsJoint::SetFirstInvMassScale( XE::float32 val )
{
	_FirstInvMassScale = val;
}

XE::float32 XE::PhysicsJoint::GetSecondInvMassScale() const
{
	return _SecondInvMassScale;
}

void XE::PhysicsJoint::SetSecondInvMassScale( XE::float32 val )
{
	_SecondInvMassScale = val;
}

XE::float32 XE::PhysicsJoint::GetFirstInvInertiaScale() const
{
	return _FirstInvInertiaScale;
}

void XE::PhysicsJoint::SetFirstInvInertiaScale( XE::float32 val )
{
	_FirstInvInertiaScale = val;
}

XE::float32 XE::PhysicsJoint::GetSecondInvInertiaScale() const
{
	return _SecondInvInertiaScale;
}

void XE::PhysicsJoint::SetSecondInvInertiaScale( XE::float32 val )
{
	_SecondInvInertiaScale = val;
}

XE::PhysicsConstraintFlags XE::PhysicsJoint::GetConstraintFlags() const
{
	return _ConstraintFlags;
}

void XE::PhysicsJoint::SetConstraintFlags( XE::PhysicsConstraintFlags val )
{
	_ConstraintFlags = val;
}

const XE::Pair<XE::PhysicsRigidActorHandle, XE::PhysicsRigidActorHandle> & XE::PhysicsJoint::GetRigidActorHandle() const
{
	return _RigidActor;
}

void XE::PhysicsJoint::SetRigidActorHandle( const XE::Pair<XE::PhysicsRigidActorHandle, XE::PhysicsRigidActorHandle> & val )
{
	_RigidActor = val;
}

const XE::Mat4x4f & XE::PhysicsJoint::GetRelativeTransform() const
{
	return _RelativeTransform;
}

void XE::PhysicsJoint::SetRelativeTransform( const XE::Mat4x4f & val )
{
	_RelativeTransform = val;
}

const XE::Vec3f & XE::PhysicsJoint::GetRelativeLinearVelocity() const
{
	return _RelativeLinearVelocity;
}

void XE::PhysicsJoint::SetRelativeLinearVelocity( const XE::Vec3f & val )
{
	_RelativeLinearVelocity = val;
}

const XE::Vec3f & XE::PhysicsJoint::GetRelativeAngularVelocity() const
{
	return _RelativeAngularVelocity;
}

void XE::PhysicsJoint::SetRelativeAngularVelocity( const XE::Vec3f & val )
{
	_RelativeAngularVelocity = val;
}
