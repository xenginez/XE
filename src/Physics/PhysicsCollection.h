/*!
 * \file	Collection.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63
#define COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsCollection : public XE::Object
{
	OBJECT( PhysicsCollection, Object )

public:
	PhysicsCollection();

	~PhysicsCollection();

public:
	XE::PhysicsCollectionHandle GetHandle() const;

	void SetHandle( XE::PhysicsCollectionHandle val );

	XE::PhysicsSceneHandle GetPhysicsSceneHandle() const;

	void SetPhysicsSceneHandle( XE::PhysicsSceneHandle val );

public:
	virtual void InsertRigidActor( XE::PhysicsRigidActorHandle val ) = 0;

	virtual void RemoveRigidActor( XE::PhysicsRigidActorHandle val ) = 0;

	virtual void ContainsRigidActor( XE::PhysicsRigidActorHandle val ) = 0;

	virtual XE::PhysicsRigidActorHandle FindRigidActor( const XE::String & val ) = 0;

public:
	virtual XE::uint64 GetRigidActorCount() const = 0;

	virtual XE::Array<XE::PhysicsRigidActorHandle> GetRigidActors() const = 0;

	virtual XE::PhysicsRigidActorHandle GetRigidActor( XE::uint64 val ) const = 0;

public:
	virtual void InsertCollection( XE::PhysicsCollectionHandle val ) = 0;

	virtual void RemoveCollection( XE::PhysicsCollectionHandle val ) = 0;

private:
	XE::PhysicsCollectionHandle _Handle;
	XE::PhysicsSceneHandle _SceneHandle;
};

END_XE_NAMESPACE

#endif // COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63
