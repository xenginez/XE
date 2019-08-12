/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__1C1C3DA4_0D11_418D_8EC6_B03DB2644537
#define __TYPE_H__1C1C3DA4_0D11_418D_8EC6_B03DB2644537

#include "Global.h"

BEG_XE_NAMESPACE

enum class PhysicsContextType
{
	HAVOK,
	PHYSX,
	BULLET,
};
DECL_META_ENUM( PHYSICS_API, PhysicsContextType );

END_XE_NAMESPACE

#endif // __TYPE_H__1C1C3DA4_0D11_418D_8EC6_B03DB2644537
