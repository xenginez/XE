/*!
 * \file	RigidBody.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
#define RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B

#include "Math/Math.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RigidBody : public XE::Object
{
	OBJECT( RigidBody, Object )

public:
	RigidBody();

	~RigidBody() override;

public:
	XE::RigidBodyHandle GetHandle() const;

	void SetHandle( XE::RigidBodyHandle val );

	XE::PhysicsSceneHandle GetSceneHandle() const;

public:
	XE::String GetName() const;

	void SetName( const XE::String & val );

	XE::Mat4 GetWorldPose() const;

	void SetWorldPose( const XE::Mat4 & val );

public:
	void AttachShape( XE::ShapeHandle val );

	void DetachShape( XE::ShapeHandle val );

	XE::Array<XE::ShapeHandle> GetShapes() const;

	void SetShapes( const XE::Array<XE::ShapeHandle> & val );

	XE::Array<XE::ConstraintHandle> GetConstraints() const;

	void SetConstraints( const XE::Array<XE::ConstraintHandle> & val );

private:
	XE::RigidBodyHandle _Handle;
	XE::PhysicsSceneHandle _SceneHandle;
};

END_XE_NAMESPACE

#endif // RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
