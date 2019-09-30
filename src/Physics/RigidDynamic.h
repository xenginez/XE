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
	const XE::Mat4 & GetKinematicTarget()	const;

	void SetKinematicTarget( const XE::Mat4 & val );

	XE::float32 GetSleepThreshold() const;

	void SetSleepThreshold( XE::float32 val );

	XE::float32 GetStabilizationThreshold() const;

	void SetStabilizationThreshold( XE::float32 val );

	RigidDynamicLockFlag GetRigidDynamicLockFlags() const;

	void SetRigidDynamicLockFlags( RigidDynamicLockFlag val );

	XE::uint32 GetSolverIterationCounts() const;

	void SetSolverIterationCounts( XE::uint32 val );

	XE::float32 GetContactReportThreshold() const;

	void SetContactReportThreshold( XE::float32 val );

public:
	void WakeUp();

	void PutToSleep();

	bool IsSleeping() const;

private:
	XE::Mat4 _KinematicTarget;
	XE::float32 _SleepThreshold;
	XE::uint32 _SolverIterationCounts;
	XE::float32 _StabilizationThreshold;
	XE::float32 _ContactReportThreshold;
	RigidDynamicLockFlag _RigidDynamicLockFlags;
};

END_XE_NAMESPACE

#endif // RIGIDDYNAMIC_H__EF7F30B9_F080_4C18_B0F9_D0ABD88A20CF
