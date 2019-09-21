/*!
 * \file	SoftBody.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SOFTBODY_H__1980804C_6DDD_4624_A6A0_0ADB2A136D0C
#define SOFTBODY_H__1980804C_6DDD_4624_A6A0_0ADB2A136D0C

#include "PhysicsObject.h"

BEG_XE_NAMESPACE

class XE_API SoftBody : public XE::PhysicsObject
{
	OBJECT( SoftBody, PhysicsObject )

public:
	SoftBody();

	~SoftBody() override;
};

END_XE_NAMESPACE

#endif // SOFTBODY_H__1980804C_6DDD_4624_A6A0_0ADB2A136D0C
