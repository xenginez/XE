#include "Joint.h"

#include <PhysX/PxPhysicsAPI.h>

#include "Math/Mathf.h"

#define _p reinterpret_cast< physx::PxJoint * >( GetHandle().GetValue() )

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

XE::String XE::Joint::GetName() const
{
	return _p->getName();
}

void XE::Joint::SetName( const XE::String & val )
{
	_p->setName( val.ToCString() );
}

XE::float32 XE::Joint::GetBreakForce() const
{
	XE::float32 force, torque;

	_p->getBreakForce( force, torque );

	return force;
}

void XE::Joint::SetBreakForce( XE::float32 val )
{
	_p->setBreakForce( val, GetBreakTorque() );
}

XE::float32 XE::Joint::GetBreakTorque() const
{
	XE::float32 force, torque;

	_p->getBreakForce( force, torque );

	return torque;
}

void XE::Joint::SetBreakTorque( XE::float32 val )
{
	_p->setBreakForce( GetBreakForce(), val );
}

XE::float32 XE::Joint::GetFirstInvMassScale() const
{
	return _p->getInvMassScale0();
}

void XE::Joint::SetFirstInvMassScale( XE::float32 val )
{
	_p->setInvMassScale0( val );
}

XE::float32 XE::Joint::GetSecondInvMassScale() const
{
	return _p->getInvMassScale1();
}

void XE::Joint::SetSecondInvMassScale( XE::float32 val )
{
	_p->setInvMassScale1( val );
}

XE::float32 XE::Joint::GetFirstInvInertiaScale() const
{
	return _p->getInvInertiaScale0();
}

void XE::Joint::SetFirstInvInertiaScale( XE::float32 val )
{
	_p->setInvInertiaScale0( val );
}

XE::float32 XE::Joint::GetSecondInvInertiaScale() const
{
	return _p->getInvInertiaScale1();
}

void XE::Joint::SetSecondInvInertiaScale( XE::float32 val )
{
	_p->setInvInertiaScale1( val );
}

XE::ConstraintFlags XE::Joint::GetConstraintFlags() const
{
	return { XE::uint16( _p->getConstraintFlags() ) };
}

void XE::Joint::SetConstraintFlags( XE::ConstraintFlags val )
{
	_p->setConstraintFlags( physx::PxConstraintFlags( val.GetValue() ) );
}

const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & XE::Joint::GetRigidActorHandle() const
{
	physx::PxRigidActor * actor0, * actor1;
	
	_p->getActors( actor0, actor1 );

	return { reinterpret_cast< XE::uint64 >( actor0 ), reinterpret_cast< XE::uint64 >( actor1 ) };
}

void XE::Joint::SetRigidActorHandle( const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & val )
{
	_p->setActors( reinterpret_cast< physx::PxRigidActor * >( val.first.GetValue() ), reinterpret_cast< physx::PxRigidActor * >( val.second.GetValue() ) );
}

XE::Mat4 XE::Joint::GetRelativeTransform() const
{
	auto trans = _p->getRelativeTransform();

	return XE::Mathf::TRS( { trans.p.x,trans.p.y,trans.p.z }, { trans.q.x, trans.q.y, trans.q.z, trans.q.w }, XE::Vec3::One );
}

XE::Mat4 XE::Joint::GetFirstRigidActorPose() const
{
	auto trans = _p->getLocalPose( physx::PxJointActorIndex::eACTOR0 );

	return XE::Mathf::TRS( { trans.p.x,trans.p.y,trans.p.z }, { trans.q.x, trans.q.y, trans.q.z, trans.q.w }, XE::Vec3::One );
}

XE::Mat4 XE::Joint::GetSecondRigidActorPose() const
{
	auto trans = _p->getLocalPose( physx::PxJointActorIndex::eACTOR1 );

	return XE::Mathf::TRS( { trans.p.x,trans.p.y,trans.p.z }, { trans.q.x, trans.q.y, trans.q.z, trans.q.w }, XE::Vec3::One );
}

XE::Vec3 XE::Joint::GetRelativeLinearVelocity() const
{
	auto linear = _p->getRelativeLinearVelocity();

	return { linear.x, linear.y, linear.z };
}

XE::Vec3 XE::Joint::GetRelativeAngularVelocity() const
{
	auto angular = _p->getRelativeAngularVelocity();

	return { angular.x, angular.y, angular.z };
}

XE::PhysicsSceneHandle XE::Joint::GetSceneHandle() const
{
	return reinterpret_cast< XE::uint64 >( _p->getScene() );
}

XE::ConstraintHandle XE::Joint::GetConstraintHandle() const
{
	return reinterpret_cast< XE::uint64 >( _p->getConstraint() );
}
