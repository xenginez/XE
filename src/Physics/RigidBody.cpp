#include "RigidBody.h"

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
	return _Mass;
}

void XE::RigidBody::SetMass( XE::float32 val )
{
	_Mass = val;
}

XE::float32 XE::RigidBody::GetLinearDamping() const
{
	return _LinearDamping;
}

void XE::RigidBody::SetLinearDamping( XE::float32 val )
{
	_LinearDamping = val;
}

XE::float32 XE::RigidBody::GetAngularDamping() const
{
	return _AngularDamping;
}

void XE::RigidBody::SetAngularDamping( XE::float32 val )
{
	_AngularDamping = val;
}

XE::float32 XE::RigidBody::GetMaxContactImpulse() const
{
	return _MaxContactImpulse;
}

void XE::RigidBody::SetMaxContactImpulse( XE::float32 val )
{
	_MaxContactImpulse = val;
}

const XE::Vec3f & XE::RigidBody::GetLienarVelocity() const
{
	return _LienarVelocity;
}

void XE::RigidBody::SetLinearVelocity( const XE::Vec3f & val )
{
	_LienarVelocity = val;
}

const XE::Vec3f & XE::RigidBody::GetAngularVelocity() const
{
	return _AngularVelocity;
}

void XE::RigidBody::SetAngularVelocity( const XE::Vec3f & val )
{
	_AngularVelocity = val;
}

const XE::Mat4f & XE::RigidBody::GetCMassLocalPose() const
{
	return _CMassLocalPose;
}

void XE::RigidBody::SetCMassLocalPose( const XE::Mat4f & val )
{
	_CMassLocalPose = val;
}

XE::float32 XE::RigidBody::GetMaxLienarVelocity() const
{
	return _MaxLienarVelocity;
}

void XE::RigidBody::SetMaxLinearVelocity( const XE::float32 & val )
{
	_MaxLienarVelocity = val;
}

XE::float32 XE::RigidBody::GetMaxAngularVelocity() const
{
	return _MaxAngularVelocity;
}

void XE::RigidBody::SetMaxAngularVelocity( const XE::float32 & val )
{
	_MaxAngularVelocity = val;
}

XE::RigidBodyFlags XE::RigidBody::GetRigidBodyFlags() const
{
	return _RigidBodyFlags;
}

void XE::RigidBody::SetRigidBodyFlags( XE::RigidBodyFlags val )
{
	_RigidBodyFlags = val;
}

XE::float32 XE::RigidBody::GetMinCCDAdvanceCoefficient() const
{
	return _MinCCDAdvanceCoefficient;
}

void XE::RigidBody::SetMinCCDAdvanceCoefficient( XE::float32 val )
{
	_MinCCDAdvanceCoefficient = val;
}

XE::float32 XE::RigidBody::GetMaxDepenetrationVelocity() const
{
	return _MaxDepenetrationVelocity;
}

void XE::RigidBody::SetMaxDepenetrationVelocity( XE::float32 val )
{
	_MaxDepenetrationVelocity = val;
}

const XE::Vec3f & XE::RigidBody::GetMassSpaceInertiaTensor() const
{
	return _MassSpaceInertiaTensor;
}

void XE::RigidBody::SetMassSpaceInertiaTensor( const XE::Vec3f & val )
{
	_MassSpaceInertiaTensor = val;
}
