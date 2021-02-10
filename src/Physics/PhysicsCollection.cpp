#include "PhysicsCollection.h"

BEG_META( XE::PhysicsCollection )
END_META()

XE::PhysicsCollection::PhysicsCollection()
{
	
}

XE::PhysicsCollection::~PhysicsCollection()
{

}

XE::PhysicsCollectionHandle XE::PhysicsCollection::GetHandle() const
{
	return _Handle;
}

void XE::PhysicsCollection::SetHandle( XE::PhysicsCollectionHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::PhysicsCollection::GetPhysicsSceneHandle() const
{
	return _SceneHandle;
}

void XE::PhysicsCollection::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_SceneHandle = val;
}
