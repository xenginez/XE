#include "PhysicsRigidDynamic.h"

BEG_META( XE::PhysicsRigidDynamic )
END_META()

XE::PhysicsRigidDynamic::PhysicsRigidDynamic()
{

}

XE::PhysicsRigidDynamic::~PhysicsRigidDynamic()
{

}

XE::float32 XE::PhysicsRigidDynamic::GetSleepThreshold() const
{
	return _SleepThreshold;
}

void XE::PhysicsRigidDynamic::SetSleepThreshold( XE::float32 val )
{
	_SleepThreshold = val;
}

XE::uint32 XE::PhysicsRigidDynamic::GetPositionIteration() const
{
	return _PositionIteration;
}

void XE::PhysicsRigidDynamic::SetPositionIteration( XE::uint32 val )
{
	_PositionIteration = val;
}

XE::uint32 XE::PhysicsRigidDynamic::GetVelocityIteration() const
{
	return _VelocityIteration;
}

void XE::PhysicsRigidDynamic::SetVelocityIteration( XE::uint32 val )
{
	_VelocityIteration = val;
}

XE::float32 XE::PhysicsRigidDynamic::GetStabilizationThreshold() const
{
	return _StabilizationThreshold;
}

void XE::PhysicsRigidDynamic::SetStabilizationThreshold( XE::float32 val )
{
	_StabilizationThreshold = val;
}

XE::float32 XE::PhysicsRigidDynamic::GetContactReportThreshold() const
{
	return _ContactReportThreshold;
}

void XE::PhysicsRigidDynamic::SetContactReportThreshold( XE::float32 val )
{
	_ContactReportThreshold = val;
}

const XE::Mat4x4f & XE::PhysicsRigidDynamic::GetKinematicTarget() const
{
	return _KinematicTarget;
}

void XE::PhysicsRigidDynamic::SetKinematicTarget( const XE::Mat4x4f & val )
{
	_KinematicTarget = val;
}

XE::PhysicsRigidDynamicLockFlags XE::PhysicsRigidDynamic::GetRigidDynamicLockFlags() const
{
	return _RigidDynamicLockFlags;
}

void XE::PhysicsRigidDynamic::SetRigidDynamicLockFlags( XE::PhysicsRigidDynamicLockFlags val )
{
	_RigidDynamicLockFlags = val;
}
