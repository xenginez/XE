/*!
 * \file	Joint.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef JOINT_H__E597880A_FE98_41A0_9AFB_C6EBEA13CCB1
#define JOINT_H__E597880A_FE98_41A0_9AFB_C6EBEA13CCB1

#include "PhysicsObject.h"

BEG_XE_NAMESPACE

class PHYSICS_API Joint : public XE::PhysicsObject
{
	OBJECT( Joint, PhysicsObject )

public:
	Joint();

	~Joint() override;
};

END_XE_NAMESPACE

#endif // JOINT_H__E597880A_FE98_41A0_9AFB_C6EBEA13CCB1
