#include "RigidBody.h"

#include <PhysX/PxPhysicsAPI.h>

#define _p reinterpret_cast< physx::PxRigidBody * >( GetHandle().GetValue() )

BEG_META( XE::RigidBody )
END_META()

XE::RigidBody::RigidBody()
{

}

XE::RigidBody::~RigidBody()
{

}

XE::float32 XE::RigidBody::GetMass() const
{
	return _p->getMass();
}

XE::float32 XE::RigidBody::GetInvMass() const
{
	return _p->getInvMass();
}

void XE::RigidBody::SetMass( XE::float32 val )
{
	_p->setMass( val );
}

XE::Vec3 XE::RigidBody::GetMassSpaceInertiaTensor() const
{
	auto v = _p->getMassSpaceInertiaTensor();

	return { v.x, v.y, v.z };
}

XE::Vec3 XE::RigidBody::GetMassSpaceInvInertiaTensor() const
{
	auto v = _p->getMassSpaceInvInertiaTensor();

	return { v.x, v.y, v.z };
}

void XE::RigidBody::SetMassSpaceInertiaTensor( const XE::Vec3 & val )
{
	_p->setMassSpaceInertiaTensor( { val.x, val.y, val.z } );
}

XE::float32 XE::RigidBody::GetLinearDamping() const
{
	return _p->getLinearDamping();
}

void XE::RigidBody::SetLinearDamping( XE::float32 val )
{
	_p->setLinearDamping( val );
}

XE::float32 XE::RigidBody::GetAngularDamping() const
{
	return _p->getAngularDamping();
}

void XE::RigidBody::SetAngularDamping( XE::float32 val )
{
	_p->setAngularDamping( val );
}

XE::float32 XE::RigidBody::GetMaxContactImpulse() const
{
	return _p->getMaxContactImpulse();
}

void XE::RigidBody::SetMaxContactImpulse( XE::float32 val )
{
	_p->setMaxContactImpulse( val );
}

XE::Vec3 XE::RigidBody::GetLienarVelocity() const
{
	auto v = _p->getLinearVelocity();

	return { v.x, v.y, v.z };
}

void XE::RigidBody::SetLinearVelocity( const XE::Vec3 & val )
{
	_p->setLinearVelocity( { val.x, val.y, val.z } );
}

XE::Vec3 XE::RigidBody::GetAngularVelocity() const
{
	auto v = _p->getAngularVelocity();

	return { v.x, v.y, v.z };
}

void XE::RigidBody::SetAngularVelocity( const XE::Vec3 & val )
{
	_p->setAngularVelocity( { val.x, val.y, val.z } );
}

XE::Mat4 XE::RigidBody::GetCMassLocalPose() const
{
	auto trans = _p->getCMassLocalPose();

	return XE::Mathf::TRS( { trans.p.x,trans.p.y,trans.p.z }, { trans.q.x, trans.q.y, trans.q.z, trans.q.w }, XE::Vec3::One );
}

void XE::RigidBody::SetCMassLocalPose( const XE::Mat4 & val )
{
	XE::Quat rot;
	XE::Vec3 pos, scale;

	XE::Mathf::TRS( val, pos, rot, scale );

	_p->setCMassLocalPose( physx::PxTransform( { pos.x, pos.y, pos.z }, { rot.x, rot.y, rot.z, rot.w } ) );
}

XE::float32 XE::RigidBody::GetMaxLienarVelocity() const
{
	return _p->getMaxLinearVelocity();
}

void XE::RigidBody::SetMaxLinearVelocity( const XE::float32 & val )
{
	_p->setMaxLinearVelocity( val );
}

XE::float32 XE::RigidBody::GetMaxAngularVelocity() const
{
	return _p->getMaxAngularVelocity();
}

void XE::RigidBody::SetMaxAngularVelocity( const XE::float32 & val )
{
	_p->setMaxAngularVelocity( val );
}

XE::RigidBodyFlags XE::RigidBody::GetRigidBodyFlags() const
{
	return XE::uint8( _p->getRigidBodyFlags() );
}

void XE::RigidBody::SetRigidBodyFlags( XE::RigidBodyFlags val )
{
	_p->setRigidBodyFlags( physx::PxRigidBodyFlags( val.GetValue() ) );
}

XE::float32 XE::RigidBody::GetMinCCDAdvanceCoefficient() const
{
	return _p->getMinCCDAdvanceCoefficient();
}

void XE::RigidBody::SetMinCCDAdvanceCoefficient( XE::float32 val )
{
	_p->setMinCCDAdvanceCoefficient( val );
}

XE::float32 XE::RigidBody::GetMaxDepenetrationVelocity() const
{
	return _p->getMaxDepenetrationVelocity();
}

void XE::RigidBody::SetMaxDepenetrationVelocity( XE::float32 val )
{
	_p->setMaxDepenetrationVelocity( val );
}

void XE::RigidBody::AddForce( const XE::Vec3 & force, ForceMode mode /*= ForceMode::FORCE */ )
{
	_p->addForce( { force.x, force.y, force.z }, static_cast< physx::PxForceMode::Enum >( mode ) );
}

void XE::RigidBody::AddTorque( const XE::Vec3 & torque, ForceMode mode /*= ForceMode::FORCE */ )
{
	_p->addTorque( { torque.x, torque.y, torque.z }, static_cast< physx::PxForceMode::Enum >( mode ) );
}

void XE::RigidBody::ClearForce( ForceMode mode /*= ForceMode::FORCE */ )
{
	_p->clearForce( static_cast< physx::PxForceMode::Enum >( mode ) );
}

void XE::RigidBody::ClearTorque( ForceMode mode /*= ForceMode::FORCE */ )
{
	_p->clearTorque( static_cast< physx::PxForceMode::Enum >( mode ) );
}

void XE::RigidBody::SetForceAndTorque( const XE::Vec3 & force, const XE::Vec3 & torque, ForceMode mode /*= ForceMode::FORCE */ )
{
	_p->setForceAndTorque( { force.x, force.y, force.z }, { torque.x, torque.y, torque.z }, static_cast< physx::PxForceMode::Enum >( mode ) );
}
