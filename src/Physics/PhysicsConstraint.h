/*!
 * \file	PhysicsConstraint.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSCONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4
#define PHYSICSCONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4

#include "Math/Vec3.h"
#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsConstraint : public XE::Object
{
	OBJECT( PhysicsConstraint, Object )

public:
	PhysicsConstraint();

	~PhysicsConstraint() override;

public:
	XE::PhysicsConstraintHandle GetHandle() const;

	void SetHandle( XE::PhysicsConstraintHandle val );

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

	XE::PhysicsConstraintFlags GetConstraintFlags() const;

	void SetConstraintFlags( XE::PhysicsConstraintFlags val );

	const XE::Pair<XE::PhysicsRigidActorHandle, XE::PhysicsRigidActorHandle> & GetRigidActorHandle() const;

	void SetRigidActorHandle( const XE::Pair<XE::PhysicsRigidActorHandle, XE::PhysicsRigidActorHandle> & val );

private:
	XE::Vec3f _Force;
	XE::Vec3f _Torque;
	XE::float32 _BreakForce;
	XE::float32 _BreakTorque;
	XE::float32 _MinResponseThreshold;
	XE::PhysicsConstraintFlags _ConstraintFlags;
	XE::Pair<XE::PhysicsRigidActorHandle, XE::PhysicsRigidActorHandle> _RigidActor;

	XE::PhysicsConstraintHandle _Handle;
	XE::PhysicsSceneHandle _SceneHandle;
};

END_XE_NAMESPACE

#endif // PHYSICSCONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4
