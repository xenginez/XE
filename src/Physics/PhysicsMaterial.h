/*!
 * \file	PhysicsMaterial.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSMATERIAL_H__6AD29062_3EA4_4E14_B361_D3FB8DBEE49B
#define PHYSICSMATERIAL_H__6AD29062_3EA4_4E14_B361_D3FB8DBEE49B

#include "PhysicsObject.h"

BEG_XE_NAMESPACE

class PHYSICS_API PhysicsMaterial : public XE::PhysicsObject
{
	OBJECT( PhysicsMaterial, PhysicsObject )

public:
	PhysicsMaterial();

	~PhysicsMaterial() override;
};

END_XE_NAMESPACE

#endif // PHYSICSMATERIAL_H__6AD29062_3EA4_4E14_B361_D3FB8DBEE49B
