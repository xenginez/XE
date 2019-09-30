#include "RigidDynamic.h"

#include <physx/PxPhysicsAPI.h>

USING_XE

BEG_META( RigidDynamic )
END_META()

XE::RigidDynamic::RigidDynamic()
{

}

XE::RigidDynamic::~RigidDynamic()
{

}

const XE::Mat4 & XE::RigidDynamic::GetKinematicTarget() const
{
	return _KinematicTarget;
}

void XE::RigidDynamic::SetKinematicTarget( const XE::Mat4 & val )
{
	_KinematicTarget = val;
}

XE::float32 XE::RigidDynamic::GetSleepThreshold() const
{
	return _SleepThreshold;
}

void XE::RigidDynamic::SetSleepThreshold( XE::float32 val )
{
	_SleepThreshold = val;
}

XE::float32 XE::RigidDynamic::GetStabilizationThreshold() const
{
	return _StabilizationThreshold;
}

void XE::RigidDynamic::SetStabilizationThreshold( XE::float32 val )
{
	_StabilizationThreshold = val;
}

XE::RigidDynamicLockFlag XE::RigidDynamic::GetRigidDynamicLockFlags() const
{
	return _RigidDynamicLockFlags;
}

void XE::RigidDynamic::SetRigidDynamicLockFlags( RigidDynamicLockFlag val )
{
	_RigidDynamicLockFlags = val;
}

XE::uint32 XE::RigidDynamic::GetSolverIterationCounts() const
{
	return _SolverIterationCounts;
}

void XE::RigidDynamic::SetSolverIterationCounts( XE::uint32 val )
{
	_SolverIterationCounts = val;
}

XE::float32 XE::RigidDynamic::GetContactReportThreshold() const
{
	return _ContactReportThreshold;
}

void XE::RigidDynamic::SetContactReportThreshold( XE::float32 val )
{
	_ContactReportThreshold = val;
}

void XE::RigidDynamic::WakeUp()
{

}

void XE::RigidDynamic::PutToSleep()
{

}

bool XE::RigidDynamic::IsSleeping() const
{
	return false;
}
