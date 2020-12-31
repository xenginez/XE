/*!
 * \file	Joint.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef JOINT_H__E597880A_FE98_41A0_9AFB_C6EBEA13CCB1
#define JOINT_H__E597880A_FE98_41A0_9AFB_C6EBEA13CCB1

#include "Math/Mat.h"
#include "Math/Vec3.h"
#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Joint : public XE::Object
{
	OBJECT( Joint, Object )

public:
	Joint();

	~Joint() override;

public:
	XE::JointHandle GetHandle() const;

	void SetHandle( XE::JointHandle val );

	XE::ConstraintHandle GetConstraintHandle() const;

	void SetConstraintHandle( XE::ConstraintHandle val );

	XE::PhysicsSceneHandle GetPhysicsSceneHandle() const;

	void SetPhysicsSceneHandle( XE::PhysicsSceneHandle val );

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	XE::float32 GetBreakForce() const;

	void SetBreakForce( XE::float32 val );

	XE::float32 GetBreakTorque() const;

	void SetBreakTorque( XE::float32 val );

	XE::float32 GetFirstInvMassScale() const;

	void SetFirstInvMassScale( XE::float32 val );

	XE::float32 GetSecondInvMassScale() const;

	void SetSecondInvMassScale( XE::float32 val );

	XE::float32 GetFirstInvInertiaScale() const;

	void SetFirstInvInertiaScale( XE::float32 val );

	XE::float32 GetSecondInvInertiaScale() const;

	void SetSecondInvInertiaScale( XE::float32 val );

	XE::ConstraintFlags GetConstraintFlags() const;

	void SetConstraintFlags( XE::ConstraintFlags val );

	const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & GetRigidActorHandle() const;

	void SetRigidActorHandle( const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & val );

public:
	const XE::Mat4x4f & GetRelativeTransform() const;

	void SetRelativeTransform( const XE::Mat4x4f & val );

	const XE::Vec3f & GetRelativeLinearVelocity() const;

	void SetRelativeLinearVelocity( const XE::Vec3f & val );

	const XE::Vec3f & GetRelativeAngularVelocity() const;

	void SetRelativeAngularVelocity( const XE::Vec3f & val );

private:
	XE::String _Name;
	XE::float32 _BreakForce;
	XE::float32 _BreakTorque;
	XE::float32 _FirstInvMassScale;
	XE::float32 _SecondInvMassScale;
	XE::float32 _FirstInvInertiaScale;
	XE::float32 _SecondInvInertiaScale;
	XE::ConstraintFlags _ConstraintFlags;
	XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> _RigidActor;

	XE::Mat4x4f _RelativeTransform;
	XE::Vec3f _RelativeLinearVelocity;
	XE::Vec3f _RelativeAngularVelocity;

	XE::JointHandle _Handle;
	XE::ConstraintHandle _ConstraintHandle;
	XE::PhysicsSceneHandle _PhysicsSceneHandle;
};

END_XE_NAMESPACE

#endif // JOINT_H__E597880A_FE98_41A0_9AFB_C6EBEA13CCB1
