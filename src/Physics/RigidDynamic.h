/*!
 * \file	RigidDynamic.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RIGIDDYNAMIC_H__EF7F30B9_F080_4C18_B0F9_D0ABD88A20CF
#define RIGIDDYNAMIC_H__EF7F30B9_F080_4C18_B0F9_D0ABD88A20CF

#include "RigidBody.h"

BEG_XE_NAMESPACE

class XE_API RigidDynamic : public XE::RigidBody
{
	OBJECT( RigidDynamic, RigidBody )

public:
	RigidDynamic();

	~RigidDynamic() override;

public:
	XE::RigidDynamicFlags GetFlags() const;

	void SetFlags( XE::RigidDynamicFlags val );

	XE::RigidDynamicLockFlags GetLockFlags() const;

	void SetLockFlags( XE::RigidDynamicLockFlags val );

public:
	XE::float32 GetMass() const;

	void SetMass( XE::float32 val );

	XE::float32 GetInvMass() const;

	void SetInvMass( XE::float32 val );

	XE::float32 GetLinearDamping() const;

	void SetLinearDamping( XE::float32 val );

	XE::float32 GetAngularDamping() const;

	void SetAngularDamping( XE::float32 val );

	XE::Vec3 GetLienarVelocity() const;

	void SetLinearVelocity( const XE::Vec3 & val );

	XE::Vec3 GetAngularVelocity() const;

	void SetAngularVelocity( const XE::Vec3 & val );

	XE::Mat4 GetCMassLocalPose() const;

	void SetCMassLocalPose( const XE::Mat4 & val );

	XE::Vec3 GetMaxLienarVelocity() const;

	void SetMaxLinearVelocity( const XE::Vec3 & val );

	XE::Vec3 GetMaxAngularVelocity() const;

	void SetMaxAngularVelocity( const XE::Vec3 & val );

public:
	XE::float32 GetSleepThreshold() const;

	void SetSleepThreshold( XE::float32 val );

	XE::uint32 GetPositionIteration() const;

	void SetPositionIteration( XE::uint32 val );

	XE::uint32 GetVelocityIteration() const;

	void SetVelocityIteration( XE::uint32 val );

	XE::Mat4 GetKinematicTarget() const;

	void SetKinematicTarget( const XE::Mat4 & val );

	XE::float32 GetStabilizationThreshold() const;

	void SetStabilizationThreshold( XE::float32 val );

public:
	void AddForce( const XE::Vec3 & force, ForceMode mode = ForceMode::FORCE );

	void AddTorque( const XE::Vec3 & torque, ForceMode mode = ForceMode::FORCE );

	void ClearForce( ForceMode mode = ForceMode::FORCE );

	void ClearTorque( ForceMode mode = ForceMode::FORCE );

	void SetForceAndTorque( const XE::Vec3 & force, const XE::Vec3 & torque, ForceMode mode = ForceMode::FORCE );

public:
	void Sleep();

	void WakeUp();

	bool IsSleeping() const;

};

END_XE_NAMESPACE

#endif // RIGIDDYNAMIC_H__EF7F30B9_F080_4C18_B0F9_D0ABD88A20CF
