/*!
 * \file	RigidActor.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RIGIDACTOR_H__1E45A27D_5B5D_43E8_9361_DF2E1F39D4F3
#define RIGIDACTOR_H__1E45A27D_5B5D_43E8_9361_DF2E1F39D4F3

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RigidActor : public XE::Object
{
	OBJECT( RigidActor, Object )

public:
	RigidActor();

	~RigidActor() override;

public:
	XE::RigidActorHandle GetHandle() const;

	void SetHandle( XE::RigidActorHandle val );

	XE::PhysicsSceneHandle GetPhysicsSceneHandle() const;

	void SetPhysicsSceneHandle( XE::PhysicsSceneHandle val );

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Mat4f & GetWorldTransform() const;

	void SetWorldTransform( const XE::Mat4f & val );

	XE::RigidActorFlags GetRigidActorFlags() const;

	void SetRigidActorFlags( XE::RigidActorFlags val );

public:
	virtual XE::uint64 GetShapeCount() const = 0;

	virtual XE::uint64 GetConstraintCount() const = 0;

	virtual void AttachShape( XE::ShapeHandle val ) = 0;

	virtual void DetachShape( XE::ShapeHandle val ) = 0;

	virtual const XE::Array<XE::ShapeHandle> & GetShapes() const = 0;

	virtual const XE::Array<XE::ConstraintHandle> & GetConstraints() const = 0;

private:
	XE::String _Name;
	XE::Mat4f _WorldTransform;
	XE::RigidActorFlags _RigidActorFlags;

	XE::RigidActorHandle _Handle;
	XE::PhysicsSceneHandle _PhysicsSceneHandle;
};

END_XE_NAMESPACE

#endif // RIGIDACTOR_H__1E45A27D_5B5D_43E8_9361_DF2E1F39D4F3
