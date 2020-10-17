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

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RigidActor : public XE::Object
{
	OBJECT( RigidActor, Object )

public:
	RigidActor();

	~RigidActor() override;

public:
	static XE::RigidActorPtr CreateRigidActor( XE::RigidActorHandle val );

public:
	XE::RigidActorHandle GetHandle() const;

	void SetHandle( XE::RigidActorHandle val );

	XE::PhysicsSceneHandle GetSceneHandle() const;

public:
	XE::String GetName() const;

	void SetName( const XE::String & val );

	XE::Mat4 GetWorldPose() const;

	void SetWorldPose( const XE::Mat4 & val );

	XE::RigidActorFlags GetRigidActorFlags() const;

	void SetRigidActorFlags( XE::RigidActorFlags val );

public:
	XE::uint64 GetShapeCount() const;

	XE::uint64 GetConstraintCount() const;

	void AttachShape( XE::ShapeHandle val );

	void DetachShape( XE::ShapeHandle val );

	XE::Array<XE::ShapeHandle> GetShapes() const;

	XE::Array<XE::ConstraintHandle> GetConstraints() const;

private:
	XE::RigidActorHandle _Handle;
};

END_XE_NAMESPACE

#endif // RIGIDACTOR_H__1E45A27D_5B5D_43E8_9361_DF2E1F39D4F3
