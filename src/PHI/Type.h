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

DECL_HANDLE( PHI_API, Body );
DECL_HANDLE( PHI_API, Shape );
DECL_HANDLE( PHI_API, Joint );

enum class PhysicsContextType
{
	BOX2D,
	HAVOK,
	PHYSX,
	BULLET,
};
DECL_META_ENUM( PHI_API, PhysicsContextType );

END_XE_NAMESPACE

#endif // TYPE_H__5D749CD1_5506_4CF0_9AD1_5E75D29FACCB
