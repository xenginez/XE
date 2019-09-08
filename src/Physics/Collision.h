/*!
 * \file	Collision.h
 *
 * \author	ZhengYuanQing
 * \date	2019/06/14
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef COLLISION_H__C797CEAC_5306_4EF1_BDAC_B2E5BD0A7A84
#define COLLISION_H__C797CEAC_5306_4EF1_BDAC_B2E5BD0A7A84

#include "PhysicsObject.h"

BEG_XE_NAMESPACE

class PHYSICS_API Collision : public XE::PhysicsObject
{
	OBJECT( Collision, PhysicsObject )

public:
	Collision();

	~Collision() override;
};

END_XE_NAMESPACE

#endif // COLLISION_H__C797CEAC_5306_4EF1_BDAC_B2E5BD0A7A84

