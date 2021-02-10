/*!
 * \file	PhysicsRigidStatic.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/11
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PHYSICSRIGIDSTATIC_H__9FFFFAAC_6141_4B82_804D_06BA61E39E62
#define PHYSICSRIGIDSTATIC_H__9FFFFAAC_6141_4B82_804D_06BA61E39E62

#include "PhysicsRigidActor.h"

BEG_XE_NAMESPACE

class XE_API PhysicsRigidStatic : public XE::PhysicsRigidActor
{
	OBJECT( PhysicsRigidStatic, PhysicsRigidActor )

public:
	PhysicsRigidStatic();

	~PhysicsRigidStatic();
};

END_XE_NAMESPACE

#endif // PHYSICSRIGIDSTATIC_H__9FFFFAAC_6141_4B82_804D_06BA61E39E62
