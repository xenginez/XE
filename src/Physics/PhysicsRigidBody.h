/*!
 * \file	PhysicsRigidBody.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSRIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
#define PHYSICSRIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsRigidBody : public XE::Object
{
	OBJECT( PhysicsRigidBody, Object )

public:
	PhysicsRigidBody();

	~PhysicsRigidBody() override;

public:
	XE::PhysicsRigidBodyHandle GetHandle() const;

	void SetHandle( XE::PhysicsRigidBodyHandle val );

	XE::PhysicsSceneHandle GetPhysicsSceneHandle() const;

	void SetPhysicsSceneHandle( XE::PhysicsSceneHandle val );

public:
	const XE::String & GetName() const;

	void SetName( const XE::String & val );

	const XE::Mat4x4f & GetWorldTransform() const;

	void SetWorldTransform( const XE::Mat4x4f & val );

public:
	virtual XE::uint64 GetShapeCount() const = 0;

	virtual XE::uint64 GetConstraintCount() const = 0;

	virtual void AttachShape( XE::PhysicsShapeHandle val ) = 0;

	virtual void DetachShape( XE::PhysicsShapeHandle val ) = 0;

	virtual const XE::Array<XE::PhysicsShapeHandle> & GetShapes() const = 0;

	virtual const XE::Array<XE::PhysicsConstraintHandle> & GetConstraints() const = 0;

public:
	XE::float32 GetMass() const;

	void SetMass( XE::float32 val );

	XE::float32 GetLinearDamping() const;

	void SetLinearDamping( XE::float32 val );

	XE::float32 GetAngularDamping() const;

	void SetAngularDamping( XE::float32 val );

	XE::float32 GetMaxContactImpulse() const;

	void SetMaxContactImpulse( XE::float32 val );

	const XE::Vec3f & GetLienarVelocity() const;

	void SetLinearVelocity( const XE::Vec3f & val );

	const XE::Vec3f & GetAngularVelocity() const;

	void SetAngularVelocity( const XE::Vec3f & val );

	const XE::Mat4x4f & GetCMassLocalPose() const;

	void SetCMassLocalPose( const XE::Mat4x4f & val );

	XE::float32 GetMaxLienarVelocity() const;

	void SetMaxLinearVelocity( const XE::float32 & val );

	XE::float32 GetMaxAngularVelocity() const;

	void SetMaxAngularVelocity( const XE::float32 & val );

	XE::PhysicsRigidBodyFlags GetRigidBodyFlags() const;

	void SetRigidBodyFlags( XE::PhysicsRigidBodyFlags val );

	XE::float32 GetMinCCDAdvanceCoefficient() const;

	void SetMinCCDAdvanceCoefficient( XE::float32 val );

	XE::float32 GetMaxDepenetrationVelocity() const;

	void SetMaxDepenetrationVelocity( XE::float32 val );

	const XE::Vec3f & GetMassSpaceInertiaTensor() const;

	void SetMassSpaceInertiaTensor( const XE::Vec3f & val );

public:
	virtual void AddForce( const XE::Vec3f & force, ForceMode mode = ForceMode::FORCE ) = 0;

	virtual void AddTorque( const XE::Vec3f & torque, ForceMode mode = ForceMode::FORCE ) = 0;

	virtual void ClearForce( ForceMode mode = ForceMode::FORCE ) = 0;

	virtual void ClearTorque( ForceMode mode = ForceMode::FORCE ) = 0;

	virtual void SetForceAndTorque( const XE::Vec3f & force, const XE::Vec3f & torque, ForceMode mode = ForceMode::FORCE ) = 0;


public:
	bool GetDynamic() const;

	void SetDynamic( bool val );

public:
	XE::float32 GetSleepThreshold() const;

	void SetSleepThreshold( XE::float32 val );

	XE::uint32 GetPositionIteration() const;

	void SetPositionIteration( XE::uint32 val );

	XE::uint32 GetVelocityIteration() const;

	void SetVelocityIteration( XE::uint32 val );

	XE::float32 GetStabilizationThreshold() const;

	void SetStabilizationThreshold( XE::float32 val );

	XE::float32 GetContactReportThreshold() const;

	void SetContactReportThreshold( XE::float32 val );

	const XE::Mat4x4f & GetKinematicTarget() const;

	void SetKinematicTarget( const XE::Mat4x4f & val );

	XE::PhysicsRigidBodyLockFlag GetRigidBodyLockFlags() const;

	void SetRigidBodyLockFlags( XE::PhysicsRigidBodyLockFlag val );

public:
	virtual void Sleep() = 0;

	virtual void WakeUp() = 0;

	virtual bool IsSleeping() const = 0;

private:
	XE::String _Name;
	XE::Mat4x4f _WorldTransform;

	XE::PhysicsRigidBodyHandle _Handle;
	XE::PhysicsSceneHandle _PhysicsSceneHandle;

private:
	XE::float32 _Mass;
	XE::float32 _LinearDamping;
	XE::float32 _AngularDamping;
	XE::float32 _MaxContactImpulse;
	XE::Vec3f _LienarVelocity;
	XE::Vec3f _AngularVelocity;
	XE::Mat4x4f _CMassLocalPose;
	XE::float32 _MaxLienarVelocity;
	XE::float32 _MaxAngularVelocity;
	XE::PhysicsRigidBodyFlags _RigidBodyFlags;
	XE::float32 _MinCCDAdvanceCoefficient;
	XE::float32 _MaxDepenetrationVelocity;
	XE::Vec3f _MassSpaceInertiaTensor;

private:
	bool _IsDynamic;

private:
	XE::float32 _SleepThreshold;
	XE::uint32 _PositionIteration;
	XE::uint32 _VelocityIteration;
	XE::float32 _StabilizationThreshold;
	XE::float32 _ContactReportThreshold;
	XE::Mat4x4f _KinematicTarget;
	XE::PhysicsRigidBodyLockFlag _RigidBodyLockFlags;
};

END_XE_NAMESPACE

#endif // PHYSICSRIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
