#include "RigidDynamic.h"

BEG_META( XE::RigidDynamic )
END_META()

XE::RigidDynamic::RigidDynamic()
{

}

XE::RigidDynamic::~RigidDynamic()
{

}

XE::float32 XE::RigidDynamic::GetSleepThreshold() const
{
	return _SleepThreshold;
}

void XE::RigidDynamic::SetSleepThreshold( XE::float32 val )
{
	_SleepThreshold = val;
}

XE::uint32 XE::RigidDynamic::GetPositionIteration() const
{
	return _PositionIteration;
}

void XE::RigidDynamic::SetPositionIteration( XE::uint32 val )
{
	_PositionIteration = val;
}

XE::uint32 XE::RigidDynamic::GetVelocityIteration() const
{
	return _VelocityIteration;
}

void XE::RigidDynamic::SetVelocityIteration( XE::uint32 val )
{
	_VelocityIteration = val;
}

XE::float32 XE::RigidDynamic::GetStabilizationThreshold() const
{
	return _StabilizationThreshold;
}

void XE::RigidDynamic::SetStabilizationThreshold( XE::float32 val )
{
	_StabilizationThreshold = val;
}

XE::float32 XE::RigidDynamic::GetContactReportThreshold() const
{
	return _ContactReportThreshold;
}

void XE::RigidDynamic::SetContactReportThreshold( XE::float32 val )
{
	_ContactReportThreshold = val;
}

const XE::Mat4x4f & XE::RigidDynamic::GetKinematicTarget() const
{
	return _KinematicTarget;
}

void XE::RigidDynamic::SetKinematicTarget( const XE::Mat4x4f & val )
{
	_KinematicTarget = val;
}

XE::RigidDynamicLockFlags XE::RigidDynamic::GetRigidDynamicLockFlags() const
{
	return _RigidDynamicLockFlags;
}

void XE::RigidDynamic::SetRigidDynamicLockFlags( XE::RigidDynamicLockFlags val )
{
	_RigidDynamicLockFlags = val;
}
