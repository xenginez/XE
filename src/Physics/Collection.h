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

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Collection : public XE::Object
{
	OBJECT( Collection, Object )

public:
	Collection();

	~Collection();

public:
	XE::CollectionHandle GetHandle() const;

	void SetHandle( XE::CollectionHandle val );

	XE::PhysicsSceneHandle GetPhysicsSceneHandle() const;

	void SetPhysicsSceneHandle( XE::PhysicsSceneHandle val );

public:
	virtual void InsertRigidActor( XE::RigidActorHandle val ) = 0;

	virtual void RemoveRigidActor( XE::RigidActorHandle val ) = 0;

	virtual void ContainsRigidActor( XE::RigidActorHandle val ) = 0;

	virtual XE::RigidActorHandle FindRigidActor( const XE::String & val ) = 0;

public:
	virtual XE::uint64 GetRigidActorCount() const = 0;

	virtual XE::Array<XE::RigidActorHandle> GetRigidActors() const = 0;

	virtual XE::RigidActorHandle GetRigidActor( XE::uint64 val ) const = 0;

public:
	virtual void InsertCollection( XE::CollectionHandle val ) = 0;

	virtual void RemoveCollection( XE::CollectionHandle val ) = 0;

private:
	XE::CollectionHandle _Handle;
	XE::PhysicsSceneHandle _SceneHandle;
};

END_XE_NAMESPACE

#endif // COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63
