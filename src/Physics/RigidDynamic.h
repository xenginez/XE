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

	XE::RigidDynamicLockFlags GetRigidDynamicLockFlags() const;

	void SetRigidDynamicLockFlags( XE::RigidDynamicLockFlags val );

public:
	virtual void Sleep() = 0;

	virtual void WakeUp() = 0;

	virtual bool IsSleeping() const = 0;

private:
	XE::float32 _SleepThreshold;
	XE::uint32 _PositionIteration;
	XE::uint32 _VelocityIteration;
	XE::float32 _StabilizationThreshold;
	XE::float32 _ContactReportThreshold;
	XE::Mat4x4f _KinematicTarget;
	XE::RigidDynamicLockFlags _RigidDynamicLockFlags;
};

END_XE_NAMESPACE

#endif // RIGIDDYNAMIC_H__EF7F30B9_F080_4C18_B0F9_D0ABD88A20CF
