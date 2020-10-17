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

#include "RigidActor.h"

BEG_XE_NAMESPACE

class XE_API RigidBody : public XE::RigidActor
{
	OBJECT( RigidBody, RigidActor )

public:
	RigidBody();

	~RigidBody() override;

public:
	XE::float32 GetMass() const;

	XE::float32 GetInvMass() const;

	void SetMass( XE::float32 val );

	XE::Vec3 GetMassSpaceInertiaTensor() const;

	XE::Vec3 GetMassSpaceInvInertiaTensor() const;

	void SetMassSpaceInertiaTensor( const XE::Vec3 & val );

public:
	XE::float32 GetLinearDamping() const;

	void SetLinearDamping( XE::float32 val );

	XE::float32 GetAngularDamping() const;

	void SetAngularDamping( XE::float32 val );

	XE::float32 GetMaxContactImpulse() const;

	void SetMaxContactImpulse( XE::float32 val );

	XE::Vec3 GetLienarVelocity() const;

	void SetLinearVelocity( const XE::Vec3 & val );

	XE::Vec3 GetAngularVelocity() const;

	void SetAngularVelocity( const XE::Vec3 & val );

	XE::Mat4 GetCMassLocalPose() const;

	void SetCMassLocalPose( const XE::Mat4 & val );

	XE::float32 GetMaxLienarVelocity() const;

	void SetMaxLinearVelocity( const XE::float32 & val );

	XE::float32 GetMaxAngularVelocity() const;

	void SetMaxAngularVelocity( const XE::float32 & val );

	XE::RigidBodyFlags GetRigidBodyFlags() const;

	void SetRigidBodyFlags( XE::RigidBodyFlags val );

	XE::float32 GetMinCCDAdvanceCoefficient() const;

	void SetMinCCDAdvanceCoefficient( XE::float32 val );

	XE::float32 GetMaxDepenetrationVelocity() const;

	void SetMaxDepenetrationVelocity( XE::float32 val );

public:
	void AddForce( const XE::Vec3 & force, ForceMode mode = ForceMode::FORCE );

	void AddTorque( const XE::Vec3 & torque, ForceMode mode = ForceMode::FORCE );

	void ClearForce( ForceMode mode = ForceMode::FORCE );

	void ClearTorque( ForceMode mode = ForceMode::FORCE );

	void SetForceAndTorque( const XE::Vec3 & force, const XE::Vec3 & torque, ForceMode mode = ForceMode::FORCE );

};

END_XE_NAMESPACE

#endif // RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
