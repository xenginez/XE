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

#include "PhysicsObject.h"

BEG_XE_NAMESPACE

class PHYSICS_API RigidBody : public XE::PhysicsObject
{
	OBJECT( RigidBody, PhysicsObject )

public:
	RigidBody();

	~RigidBody() override;
};

END_XE_NAMESPACE

#endif // RIGIDBODY_H__F9398FC0_E3E7_4E55_99AF_8A689017D38B
