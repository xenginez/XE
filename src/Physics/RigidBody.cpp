#include "RigidBody.h"

#include "Shape.h"
#include "Constraint.h"

USING_XE

BEG_META( RigidBody )
type->Property( "Shapes", &RigidBody::_Shapes );
type->Property( "Constraints", &RigidBody::_Constraints );
type->Property( "Mass", &RigidBody::_Mass );
type->Property( "CenterMass", &RigidBody::_CenterMass );
type->Property( "LinearDamping", &RigidBody::_LinearDamping );
type->Property( "AngularDamping", &RigidBody::_AngularDamping );
type->Property( "LinearVelocity", &RigidBody::_LinearVelocity );
type->Property( "AngularVelocity", &RigidBody::_AngularVelocity );
type->Property( "MaxLinearVelocity", &RigidBody::_MaxLinearVelocity );
type->Property( "MaxAngularVelocity", &RigidBody::_MaxAngularVelocity );
type->Property( "MassSpaceInertiaTensor", &RigidBody::_MassSpaceInertiaTensor );
END_META()

XE::RigidBody::RigidBody()
{
}

XE::RigidBody::~RigidBody()
{

}

void XE::RigidBody::Startup()
{
	OnStartup();
}

void XE::RigidBody::Update()
{
	OnUpdate();
}

void XE::RigidBody::Clearup()
{
	OnClearup();
}

XE::RigidBodyHandle XE::RigidBody::GetHandle() const
{
	return _Handle;
}

void XE::RigidBody::SetHandle( RigidBodyHandle val )
{
	_Handle = val;
}

const Array<ShapePtr> & XE::RigidBody::GetShapes() const
{
	return _Shapes;
}

void XE::RigidBody::SetShapes( const Array<ShapePtr> & val )
{
	_Shapes = val;
}

const Array<ConstraintPtr> & XE::RigidBody::GetConstraints() const
{
	return _Constraints;
}

void XE::RigidBody::SetConstraints( const Array<ConstraintPtr> & val )
{
	_Constraints = val;
}

const XE::Mat4 & XE::RigidBody::GetWorldTransform() const
{
	return _Transform;
}

void XE::RigidBody::SetWorldTransform( const XE::Mat4 & val )
{
	_Transform = val;
}

const XE::Vec3 & XE::RigidBody::GetCenterMass() const
{
	return _CenterMass;
}

void XE::RigidBody::SetCenterMass( const XE::Vec3 & val )
{
	_CenterMass = val;
}

XE::float32 XE::RigidBody::GetMass() const
{
	return _Mass;
}

void XE::RigidBody::SetMass( XE::float32 val )
{
	_Mass = val;
}

const XE::Vec3 & XE::RigidBody::GetMassSpaceInertiaTensor() const
{
	return _MassSpaceInertiaTensor;
}

void XE::RigidBody::SetMassSpaceInertiaTensor( const XE::Vec3 & val )
{
	_MassSpaceInertiaTensor = val;
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

const XE::Vec3 & XE::RigidBody::GetLinearVelocity() const
{
	return _LinearVelocity;
}

void XE::RigidBody::SetLinearVelocity( const XE::Vec3 & val )
{
	_LinearVelocity = val;
}

const XE::Vec3 & XE::RigidBody::GetAngularVelocity() const
{
	return _AngularVelocity;
}

void XE::RigidBody::SetAngularVelocity( const XE::Vec3 & val )
{
	_AngularVelocity = val;
}

XE::float32 XE::RigidBody::GetMaxLinearVelocity() const
{
	return _MaxLinearVelocity;
}

void XE::RigidBody::SetMaxLinearVelocity( XE::float32 val )
{
	_MaxLinearVelocity = val;
}

XE::float32 XE::RigidBody::GetMaxAngularVelocity() const
{
	return _MaxAngularVelocity;
}

void XE::RigidBody::SetMaxAngularVelocity( XE::float32 val )
{
	_MaxAngularVelocity = val;
}

void XE::RigidBody::AddForce( const XE::Vec3 & force )
{
	_AddForce += force;
}

void XE::RigidBody::AddTorque( const XE::Vec3 & torque )
{
	_AddTorque += torque;
}
