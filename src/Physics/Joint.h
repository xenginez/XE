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

#include "Math/Vec3.h"
#include "Math/Mat4.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Joint : public XE::Object
{
	OBJECT( Joint, Object )

public:
	Joint();

	~Joint() override;

public:
	XE::Mat4 GetRelativeTransform() const;

	XE::Mat4 GetFirstRigidBodyPose() const;

	XE::Mat4 GetSecondRigidBodyPose() const;

	XE::Vec3 GetRelativeLinearVelocity() const;

	XE::Vec3 GetRelativeAngularVelocity() const;

	XE::PhysicsSceneHandle GetSceneHandle() const;

	XE::ConstraintHandle GetConstraintHandle() const;

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	XE::float32 GetBreakForce() const;

	void SetBreakForce( XE::float32 val );

	XE::float32 GetBreakTorque() const;

	void SetBreakTorque( XE::float32 val );

	XE::ConstraintFlags GetFlags() const;

	void SetFlags( XE::ConstraintFlags val );

	XE::float32 GetFirstInvMassScale() const;

	void SetFirstInvMassScale( XE::float32 val );

	XE::float32 GetSecondInvMassScale() const;

	void SetSecondInvMassScale( XE::float32 val );

	XE::float32 GetFirstInvInertiaScale() const;

	void SetFirstInvInertiaScale( XE::float32 val );

	XE::float32 GetSecondInvInertiaScale() const;

	void SetSecondInvInertiaScale( XE::float32 val );

	const XE::Pair<XE::RigidBodyHandle, XE::RigidBodyHandle> & GetRigidBodyHandle() const;

	void SetRigidBodyHandle( const XE::Pair<XE::RigidBodyHandle, XE::RigidBodyHandle> & val );



};

END_XE_NAMESPACE

#endif // JOINT_H__E597880A_FE98_41A0_9AFB_C6EBEA13CCB1
