/*!
 * \file	PhysicsRigidActor.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSRIGIDACTOR_H__1E45A27D_5B5D_43E8_9361_DF2E1F39D4F3
#define PHYSICSRIGIDACTOR_H__1E45A27D_5B5D_43E8_9361_DF2E1F39D4F3

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsRigidActor : public XE::Object
{
	OBJECT( PhysicsRigidActor, Object )

public:
	PhysicsRigidActor();

	~PhysicsRigidActor() override;

public:
	XE::PhysicsRigidActorHandle GetHandle() const;

	void SetHandle( XE::PhysicsRigidActorHandle val );

	XE::PhysicsSceneHandle GetPhysicsSceneHandle() const;

	void SetPhysicsSceneHandle( XE::PhysicsSceneHandle val );

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Mat4x4f & GetWorldTransform() const;

	void SetWorldTransform( const XE::Mat4x4f & val );

	XE::PhysicsRigidActorFlags GetRigidActorFlags() const;

	void SetRigidActorFlags( XE::PhysicsRigidActorFlags val );

public:
	virtual XE::uint64 GetShapeCount() const = 0;

	virtual XE::uint64 GetConstraintCount() const = 0;

	virtual void AttachShape( XE::PhysicsShapeHandle val ) = 0;

	virtual void DetachShape( XE::PhysicsShapeHandle val ) = 0;

	virtual const XE::Array<XE::PhysicsShapeHandle> & GetShapes() const = 0;

	virtual const XE::Array<XE::PhysicsConstraintHandle> & GetConstraints() const = 0;

private:
	XE::String _Name;
	XE::Mat4x4f _WorldTransform;
	XE::PhysicsRigidActorFlags _RigidActorFlags;

	XE::PhysicsRigidActorHandle _Handle;
	XE::PhysicsSceneHandle _PhysicsSceneHandle;
};

END_XE_NAMESPACE

#endif // PHYSICSRIGIDACTOR_H__1E45A27D_5B5D_43E8_9361_DF2E1F39D4F3