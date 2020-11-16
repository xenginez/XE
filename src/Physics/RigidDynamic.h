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
	XE::Mat4f GetKinematicTarget() const;

	void SetKinematicTarget( const XE::Mat4f & val );

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

	XE::RigidDynamicLockFlags GetRigidDynamicLockFlags() const;

	void SetRigidDynamicLockFlags( XE::RigidDynamicLockFlags val );

public:
	void Sleep();

	void WakeUp();

	bool IsSleeping() const;

};

END_XE_NAMESPACE

#endif // RIGIDDYNAMIC_H__EF7F30B9_F080_4C18_B0F9_D0ABD88A20CF
