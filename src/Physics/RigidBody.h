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
	void Startup();

	void Update();

	void Clearup();

protected:
	virtual void OnStartup() = 0;

	virtual void OnUpdate() = 0;

	virtual void OnClearup() = 0;

public:
	RigidBodyHandle GetHandle() const;

	void SetHandle( RigidBodyHandle val );

	XE::PhysicsSceneHandle GetSceneHandle() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Mat4 & GetWorldPose() const;

	void SetWorldPose( const XE::Mat4 & val );

public:
	void AttachShape( const XE::ShapePtr & val );

	void DetachShape( const XE::ShapePtr & val );

	const Array<ShapePtr> & GetShapes() const;

	void SetShapes( const Array<ShapePtr> & val );

	const Array<ConstraintPtr> & GetConstraints() const;

	void SetConstraints( const Array<ConstraintPtr> & val );

private:
	XE::String _Name;
	XE::Mat4 _WorldPose;
	XE::RigidBodyHandle _Handle;
	XE::Array<ShapePtr> _Shapes;
	XE::PhysicsSceneHandle _SceneHandle;
	XE::Array<ConstraintPtr> _Constraints;
};

END_XE_NAMESPACE

#endif // RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
