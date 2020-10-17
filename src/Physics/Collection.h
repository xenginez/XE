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

	XE::PhysicsSceneHandle GetSceneHandle() const;

	void GetSceneHandle( XE::PhysicsSceneHandle val );

public:
	void InsertRigidActor( XE::RigidActorHandle val );

	void RemoveRigidActor( XE::RigidActorHandle val );

	void ContainsRigidActor( XE::RigidActorHandle val );

	XE::RigidActorHandle  FindRigidActor( const XE::String val );

public:
	XE::uint64 GetRigidActorCount() const;

	XE::Array<XE::RigidActorHandle> GetRigidActors() const;

	XE::RigidActorHandle GetRigidActor( XE::uint64 val ) const;

public:
	void InsertCollection( XE::CollectionHandle val );

	void RemoveCollection( XE::CollectionHandle val );

private:
	XE::CollectionHandle _Handle;
	XE::PhysicsSceneHandle _SceneHandle;
};

END_XE_NAMESPACE

#endif // COLLECTION_H__53398583_89A5_42B5_978E_36A445CA6C63
