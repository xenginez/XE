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

#include "PhysicsObject.h"

BEG_XE_NAMESPACE

class PHYSICS_API Constraint : public XE::PhysicsObject
{
	OBJECT( Constraint, PhysicsObject )

public:
	Constraint();

	~Constraint() override;
};

END_XE_NAMESPACE

#endif // CONSTRAINT_H__FA4E88B6_1066_4795_A0C7_05765643C0B4