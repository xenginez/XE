#include "Collection.h"

#include <PhysX/PxPhysicsAPI.h>

#define _p reinterpret_cast< physx::PxCollection * >( GetHandle().GetValue() )

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

XE::PhysicsSceneHandle XE::Collection::GetSceneHandle() const
{
	return _SceneHandle;
}

void XE::Collection::GetSceneHandle( XE::PhysicsSceneHandle val )
{
	_SceneHandle = val;
}

void XE::Collection::InsertRigidActor( XE::RigidActorHandle val )
{
	_p->add( *reinterpret_cast< physx::PxBase * >( val.GetValue() ) );
}

void XE::Collection::RemoveRigidActor( XE::RigidActorHandle val )
{
	_p->remove( *reinterpret_cast< physx::PxBase * >( val.GetValue() ) );
}

void XE::Collection::ContainsRigidActor( XE::RigidActorHandle val )
{
	_p->contains( *reinterpret_cast< physx::PxBase * >( val.GetValue() ) );
}

XE::RigidActorHandle XE::Collection::FindRigidActor( const XE::String val )
{
	physx::PxBase * bodys[1024];

	auto size = _p->getObjects( bodys, 1024 );

	for( XE::uint32 i = 0; i < size; ++i )
	{
		if( auto body = bodys[i]->is<physx::PxRigidActor>() )
		{
			if( body->getName() == val )
			{
				return { reinterpret_cast< XE::uint64 >( body ) };
			}
		}
	}

	return {};
}

XE::uint64 XE::Collection::GetRigidActorCount() const
{
	return _p->getNbObjects();
}

XE::Array<XE::RigidActorHandle> XE::Collection::GetRigidActors() const
{
	XE::Array<XE::RigidActorHandle> res;

	physx::PxBase * bodys[1024];

	auto size = _p->getObjects( bodys, 1024 );

	for( XE::uint32 i = 0; i < size; ++i )
	{
		if( auto body = bodys[i]->is<physx::PxRigidActor>() )
		{
			res.push_back( { reinterpret_cast< XE::uint64 >( body ) } );
		}
	}

	return std::move( res );
}

XE::RigidActorHandle XE::Collection::GetRigidActor( XE::uint64 val ) const
{
	return { reinterpret_cast< XE::uint64 >( &_p->getObject( val ) ) };
}

void XE::Collection::InsertCollection( XE::CollectionHandle val )
{
	if( val )
	{
		auto other = reinterpret_cast< physx::PxCollection * >( val.GetValue() );
		_p->add( *other );
	}
}

void XE::Collection::RemoveCollection( XE::CollectionHandle val )
{
	if( val )
	{
		auto other = reinterpret_cast< physx::PxCollection * >( val.GetValue() );
		_p->remove( *other );
	}
}
