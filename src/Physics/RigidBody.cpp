#include "RigidBody.h"

#include "Shape.h"
#include "Constraint.h"

BEG_META( XE::RigidBody )
type->Property( "Name", &RigidBody::_Name );
type->Property( "Shapes", &RigidBody::_Shapes );
type->Property( "Constraints", &RigidBody::_Constraints );
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

XE::PhysicsSceneHandle XE::RigidBody::GetSceneHandle() const
{
	return _SceneHandle;
}

const XE::String & XE::RigidBody::GetName() const
{
	return _Name;
}

void XE::RigidBody::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Mat4 & XE::RigidBody::GetWorldPose() const
{
	return _WorldPose;
}

void XE::RigidBody::SetWorldPose( const XE::Mat4 & val )
{
	_WorldPose = val;
}

void XE::RigidBody::AttachShape( const XE::ShapePtr & val )
{
	auto it = std::find( _Shapes.begin(), _Shapes.end(), val );
	if( it == _Shapes.end() )
	{
		_Shapes.push_back( val );
	}
}

void XE::RigidBody::DetachShape( const XE::ShapePtr & val )
{
	auto it = std::find( _Shapes.begin(), _Shapes.end(), val );
	if( it == _Shapes.end() )
	{
		_Shapes.erase( val );
	}
}

const XE::Array<XE::ShapePtr> & XE::RigidBody::GetShapes() const
{
	return _Shapes;
}

void XE::RigidBody::SetShapes( const Array<ShapePtr> & val )
{
	_Shapes = val;
}

const XE::Array<XE::ConstraintPtr> & XE::RigidBody::GetConstraints() const
{
	return _Constraints;
}

void XE::RigidBody::SetConstraints( const Array<ConstraintPtr> & val )
{
	_Constraints = val;
}
