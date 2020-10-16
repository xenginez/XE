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
	XE::PhysicsSceneHandle GetSceneHandle() const;

public:
	XE::ConstraintFlags GetFlags() const;

	void SetFlags( XE::ConstraintFlags val );

	const XE::Pair<XE::RigidBodyHandle, XE::RigidBodyHandle> & GetRigidBodyHandle() const;

	void SetRigidBodyHandle( const XE::Pair<XE::RigidBodyHandle, XE::RigidBodyHandle> & val );

public:
	bool IsValid() const;

	XE::Vec3 GetForce() const;

	XE::Vec3 GetTorque() const;

	XE::float32 GetBreakForce() const;

	void SetBreakForce( XE::float32 val );

	XE::float32 GetBreakTorque() const;

	void SetBreakTorque( XE::float32 val );

	XE::float32 GetMinResponseThreshold() const;

	void SetMinResponseThreshold( XE::float32 val );

};

END_XE_NAMESPACE

#endif // CONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4
