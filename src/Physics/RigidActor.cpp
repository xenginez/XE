#include "RigidActor.h"

#include "RigidBody.h"
#include "RigidStatic.h"
#include "RigidDynamic.h"

BEG_META( XE::RigidActor )
END_META()

XE::RigidActor::RigidActor()
{

}

XE::RigidActor::~RigidActor()
{

}

XE::RigidActorHandle XE::RigidActor::GetHandle() const
{
	return _Handle;
}

void XE::RigidActor::SetHandle( XE::RigidActorHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::RigidActor::GetPhysicsSceneHandle() const
{
	return _PhysicsSceneHandle;
}

void XE::RigidActor::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_PhysicsSceneHandle = val;
}

const XE::String & XE::RigidActor::GetName() const
{
	return _Name;
}

void XE::RigidActor::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Mat4f & XE::RigidActor::GetWorldTransform() const
{
	return _WorldTransform;
}

void XE::RigidActor::SetWorldTransform( const XE::Mat4f & val )
{
	_WorldTransform = val;
}

XE::RigidActorFlags XE::RigidActor::GetRigidActorFlags() const
{
	return _RigidActorFlags;
}

void XE::RigidActor::SetRigidActorFlags( XE::RigidActorFlags val )
{
	_RigidActorFlags = val;
}
