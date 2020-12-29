#include "Constraint.h"

BEG_META( XE::Constraint )
END_META()

XE::Constraint::Constraint()
{

}

XE::Constraint::~Constraint()
{

}

XE::ConstraintHandle XE::Constraint::GetHandle() const
{
	return _Handle;
}

void XE::Constraint::SetHandle( XE::ConstraintHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::Constraint::GetPhysicsSceneHandle() const
{
	return _SceneHandle;
}

void XE::Constraint::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_SceneHandle = val;
}

const XE::Vec3f & XE::Constraint::GetForce() const
{
	return _Force;
}

void XE::Constraint::SetForce( const XE::Vec3f & val )
{
	_Force = val;
}

const XE::Vec3f & XE::Constraint::GetTorque() const
{
	return _Torque;
}

void XE::Constraint::SetTorque( const XE::Vec3f & val )
{
	_Torque = val;
}

XE::float32 XE::Constraint::GetBreakForce() const
{
	return _BreakForce;
}

void XE::Constraint::SetBreakForce( XE::float32 val )
{
	_BreakForce = val;
}

XE::float32 XE::Constraint::GetBreakTorque() const
{
	return _BreakTorque;
}

void XE::Constraint::SetBreakTorque( XE::float32 val )
{
	_BreakTorque = val;
}

XE::float32 XE::Constraint::GetMinResponseThreshold() const
{
	return _MinResponseThreshold;
}

void XE::Constraint::SetMinResponseThreshold( XE::float32 val )
{
	_MinResponseThreshold = val;
}

XE::ConstraintFlags XE::Constraint::GetConstraintFlags() const
{
	return _ConstraintFlags;
}

void XE::Constraint::SetConstraintFlags( XE::ConstraintFlags val )
{
	_ConstraintFlags = val;
}

const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & XE::Constraint::GetRigidActorHandle() const
{
	return _RigidActor;
}

void XE::Constraint::SetRigidActorHandle( const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & val )
{
	_RigidActor = val;
}
