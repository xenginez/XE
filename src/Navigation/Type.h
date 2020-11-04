/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__25FF3200_FE17_4091_8E4B_16F76E16ABC5
#define __TYPE_H__25FF3200_FE17_4091_8E4B_16F76E16ABC5

#include "Utils/Handle.hpp"

BEG_XE_NAMESPACE

DECL_PTR( NavigationMesh );
DECL_PTR( NavigationObstacle );

DECL_HANDLE( XE_API, NavigationMesh );
DECL_HANDLE( XE_API, NavigationObstacle );

enum class NavigationObstacleType
{
	OBB,
	AABB,
	CAPSULE,
};
DECL_META_ENUM( XE_API, NavigationObstacleType );

END_XE_NAMESPACE

#endif // __TYPE_H__25FF3200_FE17_4091_8E4B_16F76E16ABC5
