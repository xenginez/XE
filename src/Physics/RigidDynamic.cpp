#include "RigidDynamic.h"

#include <PhysX/PxPhysicsAPI.h>

#define _p reinterpret_cast< physx::PxRigidDynamic * >( GetHandle().GetValue() )

BEG_META( XE::RigidDynamic )
END_META()

XE::RigidDynamic::RigidDynamic()
{

}

XE::RigidDynamic::~RigidDynamic()
{

}

XE::Mat4 XE::RigidDynamic::GetKinematicTarget() const
{
	physx::PxTransform trans;
	if( _p->getKinematicTarget( trans ) )
	{
		return XE::Mathf::TRS( { trans.p.x,trans.p.y,trans.p.z }, { trans.q.x, trans.q.y, trans.q.z, trans.q.w }, XE::Vec3::One );
	}

	return {};
}

void XE::RigidDynamic::SetKinematicTarget( const XE::Mat4 & val )
{
	XE::Quat rot;
	XE::Vec3 pos, scale;

	XE::Mathf::TRS( val, pos, rot, scale );

	_p->setKinematicTarget( physx::PxTransform( { pos.x, pos.y, pos.z }, { rot.x, rot.y, rot.z, rot.w } ) );
}

XE::float32 XE::RigidDynamic::GetSleepThreshold() const
{
	return _p->getSleepThreshold();
}

void XE::RigidDynamic::SetSleepThreshold( XE::float32 val )
{
	_p->setSleepThreshold( val );
}

XE::uint32 XE::RigidDynamic::GetPositionIteration() const
{
	XE::uint32 pos, vel;
	
	_p->getSolverIterationCounts( pos, vel );

	return pos;
}

void XE::RigidDynamic::SetPositionIteration( XE::uint32 val )
{
	_p->setSolverIterationCounts( val, GetVelocityIteration() );
}

XE::uint32 XE::RigidDynamic::GetVelocityIteration() const
{
	XE::uint32 pos, vel;

	_p->getSolverIterationCounts( pos, vel );

	return vel;
}

void XE::RigidDynamic::SetVelocityIteration( XE::uint32 val )
{
	_p->setSolverIterationCounts( GetPositionIteration(), val );
}

XE::float32 XE::RigidDynamic::GetStabilizationThreshold() const
{
	return _p->getStabilizationThreshold();
}

void XE::RigidDynamic::SetStabilizationThreshold( XE::float32 val )
{
	_p->setStabilizationThreshold( val );
}

XE::float32 XE::RigidDynamic::GetContactReportThreshold() const
{
	return _p->getContactReportThreshold();
}

void XE::RigidDynamic::SetContactReportThreshold( XE::float32 val )
{
	_p->setContactReportThreshold( val );
}

XE::RigidDynamicLockFlags XE::RigidDynamic::GetRigidDynamicLockFlags() const
{
	return XE::uint8( _p->getRigidDynamicLockFlags() );
}

void XE::RigidDynamic::SetRigidDynamicLockFlags( XE::RigidDynamicLockFlags val )
{
	_p->setRigidDynamicLockFlags( physx::PxRigidDynamicLockFlags( val.GetValue() ) );
}

void XE::RigidDynamic::Sleep()
{
	_p->putToSleep();
}

void XE::RigidDynamic::WakeUp()
{
	_p->wakeUp();
}

bool XE::RigidDynamic::IsSleeping() const
{
	return _p->isSleeping();
}
