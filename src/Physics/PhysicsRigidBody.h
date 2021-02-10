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

#include "PhysicsRigidActor.h"

BEG_XE_NAMESPACE

class XE_API PhysicsRigidBody : public XE::PhysicsRigidActor
{
	OBJECT( PhysicsRigidBody, PhysicsRigidActor )

public:
	PhysicsRigidBody();

	~PhysicsRigidBody() override;

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
};

END_XE_NAMESPACE

#endif // PHYSICSRIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
