/*!
 * \file	Type.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TYPE_H__5D749CD1_5506_4CF0_9AD1_5E75D29FACCB
#define TYPE_H__5D749CD1_5506_4CF0_9AD1_5E75D29FACCB

#include "Global.h"

BEG_XE_NAMESPACE

DECL_HANDLE( PSI_API, Shape );
DECL_HANDLE( PSI_API, Joint );
DECL_HANDLE( PSI_API, RigidBody );
DECL_HANDLE( PSI_API, Collection );
DECL_HANDLE( PSI_API, Constraint );

enum class PhysicsContextType
{
	EMPTY,
	BOX2D,
	PHYSX,
	BULLET,
};
DECL_META_ENUM( PSI_API, PhysicsContextType );

enum class RigidBodyType
{
	CLOTH,
	STATIC,
	DYNAMIC,
};
DECL_META_ENUM( PSI_API, RigidBodyType );


END_XE_NAMESPACE

#endif // TYPE_H__5D749CD1_5506_4CF0_9AD1_5E75D29FACCB
