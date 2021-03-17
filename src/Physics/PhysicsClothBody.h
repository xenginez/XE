/*!
 * \file	PhysicsClothBody.h
 *
 * \author	ZhengYuanQing
 * \date	2021/03/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSCLOTHBODY_H__ACFF11EA_60CD_4DB1_A60A_575DE8666159
#define PHYSICSCLOTHBODY_H__ACFF11EA_60CD_4DB1_A60A_575DE8666159

#include "Interface/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API PhysicsClothBody : public XE::Object
{
	OBJECT( PhysicsClothBody, Object )

public:
	PhysicsClothBody();

	~PhysicsClothBody();
};

END_XE_NAMESPACE

#endif // PHYSICSCLOTHBODY_H__ACFF11EA_60CD_4DB1_A60A_575DE8666159
