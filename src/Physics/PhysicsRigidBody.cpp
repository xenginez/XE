#include "PhysicsRigidBody.h"

BEG_META( XE::PhysicsRigidBody )
END_META()

XE::PhysicsRigidBody::PhysicsRigidBody()
{

}

XE::PhysicsRigidBody::~PhysicsRigidBody()
{

}



XE::PhysicsRigidBodyHandle XE::PhysicsRigidBody::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsRigidBody::SetHandle( XE::PhysicsRigidBodyHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::PhysicsRigidBody::GetPhysicsSceneHandle() const
{
	return _PhysicsSceneHandle;
}

void XE::PhysicsRigidBody::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_PhysicsSceneHandle = val;
}

const XE::String & XE::PhysicsRigidBody::GetName() const
{
	return _Name;
}

void XE::PhysicsRigidBody::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Mat4x4f & XE::PhysicsRigidBody::GetWorldTransform() const
{
	return _WorldTransform;
}

void XE::PhysicsRigidBody::SetWorldTransform( const XE::Mat4x4f & val )
{
	_WorldTransform = val;
}





XE::float32 XE::PhysicsRigidBody::GetMass() const
{
	return _Mass;
}

void XE::PhysicsRigidBody::SetMass( XE::float32 val )
{
	_Mass = val;
}

XE::float32 XE::PhysicsRigidBody::GetLinearDamping() const
{
	return _LinearDamping;
}

void XE::PhysicsRigidBody::SetLinearDamping( XE::float32 val )
{
	_LinearDamping = val;
}

XE::float32 XE::PhysicsRigidBody::GetAngularDamping() const
{
	return _AngularDamping;
}

void XE::PhysicsRigidBody::SetAngularDamping( XE::float32 val )
{
	_AngularDamping = val;
}

XE::float32 XE::PhysicsRigidBody::GetMaxContactImpulse() const
{
	return _MaxContactImpulse;
}

void XE::PhysicsRigidBody::SetMaxContactImpulse( XE::float32 val )
{
	_MaxContactImpulse = val;
}

const XE::Vec3f & XE::PhysicsRigidBody::GetLienarVelocity() const
{
	return _LienarVelocity;
}

void XE::PhysicsRigidBody::SetLinearVelocity( const XE::Vec3f & val )
{
	_LienarVelocity = val;
}

const XE::Vec3f & XE::PhysicsRigidBody::GetAngularVelocity() const
{
	return _AngularVelocity;
}

void XE::PhysicsRigidBody::SetAngularVelocity( const XE::Vec3f & val )
{
	_AngularVelocity = val;
}

const XE::Mat4x4f & XE::PhysicsRigidBody::GetCMassLocalPose() const
{
	return _CMassLocalPose;
}

void XE::PhysicsRigidBody::SetCMassLocalPose( const XE::Mat4x4f & val )
{
	_CMassLocalPose = val;
}

XE::float32 XE::PhysicsRigidBody::GetMaxLienarVelocity() const
{
	return _MaxLienarVelocity;
}

void XE::PhysicsRigidBody::SetMaxLinearVelocity( const XE::float32 & val )
{
	_MaxLienarVelocity = val;
}

XE::float32 XE::PhysicsRigidBody::GetMaxAngularVelocity() const
{
	return _MaxAngularVelocity;
}

void XE::PhysicsRigidBody::SetMaxAngularVelocity( const XE::float32 & val )
{
	_MaxAngularVelocity = val;
}

XE::PhysicsRigidBodyFlags XE::PhysicsRigidBody::GetRigidBodyFlags() const
{
	return _RigidBodyFlags;
}

void XE::PhysicsRigidBody::SetRigidBodyFlags( XE::PhysicsRigidBodyFlags val )
{
	_RigidBodyFlags = val;
}

XE::float32 XE::PhysicsRigidBody::GetMinCCDAdvanceCoefficient() const
{
	return _MinCCDAdvanceCoefficient;
}

void XE::PhysicsRigidBody::SetMinCCDAdvanceCoefficient( XE::float32 val )
{
	_MinCCDAdvanceCoefficient = val;
}

XE::float32 XE::PhysicsRigidBody::GetMaxDepenetrationVelocity() const
{
	return _MaxDepenetrationVelocity;
}

void XE::PhysicsRigidBody::SetMaxDepenetrationVelocity( XE::float32 val )
{
	_MaxDepenetrationVelocity = val;
}

const XE::Vec3f & XE::PhysicsRigidBody::GetMassSpaceInertiaTensor() const
{
	return _MassSpaceInertiaTensor;
}

void XE::PhysicsRigidBody::SetMassSpaceInertiaTensor( const XE::Vec3f & val )
{
	_MassSpaceInertiaTensor = val;
}




bool XE::PhysicsRigidBody::GetDynamic() const
{
	return _IsDynamic;
}

void XE::PhysicsRigidBody::SetDynamic( bool val )
{
	_IsDynamic = val;
}



XE::float32 XE::PhysicsRigidBody::GetSleepThreshold() const
{
	return _SleepThreshold;
}

void XE::PhysicsRigidBody::SetSleepThreshold( XE::float32 val )
{
	_SleepThreshold = val;
}

XE::uint32 XE::PhysicsRigidBody::GetPositionIteration() const
{
	return _PositionIteration;
}

void XE::PhysicsRigidBody::SetPositionIteration( XE::uint32 val )
{
	_PositionIteration = val;
}

XE::uint32 XE::PhysicsRigidBody::GetVelocityIteration() const
{
	return _VelocityIteration;
}

void XE::PhysicsRigidBody::SetVelocityIteration( XE::uint32 val )
{
	_VelocityIteration = val;
}

XE::float32 XE::PhysicsRigidBody::GetStabilizationThreshold() const
{
	return _StabilizationThreshold;
}

void XE::PhysicsRigidBody::SetStabilizationThreshold( XE::float32 val )
{
	_StabilizationThreshold = val;
}

XE::float32 XE::PhysicsRigidBody::GetContactReportThreshold() const
{
	return _ContactReportThreshold;
}

void XE::PhysicsRigidBody::SetContactReportThreshold( XE::float32 val )
{
	_ContactReportThreshold = val;
}

const XE::Mat4x4f & XE::PhysicsRigidBody::GetKinematicTarget() const
{
	return _KinematicTarget;
}

void XE::PhysicsRigidBody::SetKinematicTarget( const XE::Mat4x4f & val )
{
	_KinematicTarget = val;
}

XE::PhysicsRigidBodyLockFlag XE::PhysicsRigidBody::GetRigidBodyLockFlags() const
{
	return _RigidBodyLockFlags;
}

void XE::PhysicsRigidBody::SetRigidBodyLockFlags( XE::PhysicsRigidBodyLockFlag val )
{
	_RigidBodyLockFlags = val;
}
