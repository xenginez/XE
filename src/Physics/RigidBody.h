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

	const XE::Mat4f & GetCMassLocalPose() const;

	void SetCMassLocalPose( const XE::Mat4f & val );

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
	XE::Mat4f _CMassLocalPose;
	XE::float32 _MaxLienarVelocity;
	XE::float32 _MaxAngularVelocity;
	XE::RigidBodyFlags _RigidBodyFlags;
	XE::float32 _MinCCDAdvanceCoefficient;
	XE::float32 _MaxDepenetrationVelocity;
	XE::Vec3f _MassSpaceInertiaTensor;
};

END_XE_NAMESPACE

#endif // RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
