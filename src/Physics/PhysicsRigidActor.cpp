#include "PhysicsRigidActor.h"

#include "PhysicsRigidBody.h"
#include "PhysicsRigidStatic.h"
#include "PhysicsRigidDynamic.h"

BEG_META( XE::PhysicsRigidActor )
END_META()

XE::PhysicsRigidActor::PhysicsRigidActor()
{

}

XE::PhysicsRigidActor::~PhysicsRigidActor()
{

}

XE::PhysicsRigidActorHandle XE::PhysicsRigidActor::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsRigidActor::SetHandle( XE::PhysicsRigidActorHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::PhysicsRigidActor::GetPhysicsSceneHandle() const
{
	return _PhysicsSceneHandle;
}

void XE::PhysicsRigidActor::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_PhysicsSceneHandle = val;
}

const XE::String & XE::PhysicsRigidActor::GetName() const
{
	return _Name;
}

void XE::PhysicsRigidActor::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Mat4x4f & XE::PhysicsRigidActor::GetWorldTransform() const
{
	return _WorldTransform;
}

void XE::PhysicsRigidActor::SetWorldTransform( const XE::Mat4x4f & val )
{
	_WorldTransform = val;
}

XE::PhysicsRigidActorFlags XE::PhysicsRigidActor::GetRigidActorFlags() const
{
	return _RigidActorFlags;
}

void XE::PhysicsRigidActor::SetRigidActorFlags( XE::PhysicsRigidActorFlags val )
{
	_RigidActorFlags = val;
}
