#include "PhysicsConstraint.h"

BEG_META( XE::PhysicsConstraint )
END_META()

XE::PhysicsConstraint::PhysicsConstraint()
{

}

XE::PhysicsConstraint::~PhysicsConstraint()
{

}

XE::PhysicsConstraintHandle XE::PhysicsConstraint::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsConstraint::SetHandle( XE::PhysicsConstraintHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::PhysicsConstraint::GetPhysicsSceneHandle() const
{
	return _SceneHandle;
}

void XE::PhysicsConstraint::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_SceneHandle = val;
}

const XE::Vec3f & XE::PhysicsConstraint::GetForce() const
{
	return _Force;
}

void XE::PhysicsConstraint::SetForce( const XE::Vec3f & val )
{
	_Force = val;
}

const XE::Vec3f & XE::PhysicsConstraint::GetTorque() const
{
	return _Torque;
}

void XE::PhysicsConstraint::SetTorque( const XE::Vec3f & val )
{
	_Torque = val;
}

XE::float32 XE::PhysicsConstraint::GetBreakForce() const
{
	return _BreakForce;
}

void XE::PhysicsConstraint::SetBreakForce( XE::float32 val )
{
	_BreakForce = val;
}

XE::float32 XE::PhysicsConstraint::GetBreakTorque() const
{
	return _BreakTorque;
}

void XE::PhysicsConstraint::SetBreakTorque( XE::float32 val )
{
	_BreakTorque = val;
}

XE::float32 XE::PhysicsConstraint::GetMinResponseThreshold() const
{
	return _MinResponseThreshold;
}

void XE::PhysicsConstraint::SetMinResponseThreshold( XE::float32 val )
{
	_MinResponseThreshold = val;
}

XE::PhysicsConstraintFlags XE::PhysicsConstraint::GetConstraintFlags() const
{
	return _ConstraintFlags;
}

void XE::PhysicsConstraint::SetConstraintFlags( XE::PhysicsConstraintFlags val )
{
	_ConstraintFlags = val;
}

const XE::Pair<XE::PhysicsRigidBodyHandle, XE::PhysicsRigidBodyHandle> & XE::PhysicsConstraint::GetRigidActorHandle() const
{
	return _RigidActor;
}

void XE::PhysicsConstraint::SetRigidActorHandle( const XE::Pair<XE::PhysicsRigidBodyHandle, XE::PhysicsRigidBodyHandle> & val )
{
	_RigidActor = val;
}
