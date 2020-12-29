#include "Collection.h"

BEG_META( XE::Collection )
END_META()

XE::Collection::Collection()
{
	
}

XE::Collection::~Collection()
{

}

XE::CollectionHandle XE::Collection::GetHandle() const
{
	return _Handle;
}

void XE::Collection::SetHandle( XE::CollectionHandle val )
{
	_Handle = val;
}

XE::PhysicsSceneHandle XE::Collection::GetPhysicsSceneHandle() const
{
	return _SceneHandle;
}

void XE::Collection::SetPhysicsSceneHandle( XE::PhysicsSceneHandle val )
{
	_SceneHandle = val;
}
