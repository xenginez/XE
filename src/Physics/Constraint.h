/*!
 * \file	Constraint.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4
#define CONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4

#include "Math/Vec3.h"
#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Constraint : public XE::Object
{
	OBJECT( Constraint, Object )

public:
	Constraint();

	~Constraint() override;

public:
	XE::ConstraintHandle GetHandle() const;

	void SetHandle( XE::ConstraintHandle val );

	XE::PhysicsSceneHandle GetPhysicsSceneHandle() const;

	void SetPhysicsSceneHandle( XE::PhysicsSceneHandle val );

public:
	const XE::Vec3f & GetForce() const;

	void SetForce( const XE::Vec3f & val );

	const XE::Vec3f & GetTorque() const;

	void SetTorque( const XE::Vec3f & val );

	XE::float32 GetBreakForce() const;

	void SetBreakForce( XE::float32 val );

	XE::float32 GetBreakTorque() const;

	void SetBreakTorque( XE::float32 val );

	XE::float32 GetMinResponseThreshold() const;

	void SetMinResponseThreshold( XE::float32 val );

	XE::ConstraintFlags GetConstraintFlags() const;

	void SetConstraintFlags( XE::ConstraintFlags val );

	const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & GetRigidActorHandle() const;

	void SetRigidActorHandle( const XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> & val );

private:
	XE::Vec3f _Force;
	XE::Vec3f _Torque;
	XE::float32 _BreakForce;
	XE::float32 _BreakTorque;
	XE::float32 _MinResponseThreshold;
	XE::ConstraintFlags _ConstraintFlags;
	XE::Pair<XE::RigidActorHandle, XE::RigidActorHandle> _RigidActor;

	XE::ConstraintHandle _Handle;
	XE::PhysicsSceneHandle _SceneHandle;
};

END_XE_NAMESPACE

#endif // CONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4
