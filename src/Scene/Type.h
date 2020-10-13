/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__BB848F51_DB84_4BE8_9C2D_C6B7F7E738A9
#define __TYPE_H__BB848F51_DB84_4BE8_9C2D_C6B7F7E738A9

#include "Utils/Handle.hpp"

BEG_XE_NAMESPACE

DECL_PTR( World );
DECL_PTR( Entity );
DECL_PTR( GameZone );
DECL_PTR( Component );
DECL_PTR( GameObject );
DECL_PTR( SceneComponent );
DECL_PTR( RenderComponent );
DECL_PTR( BehaviorComponent );

DECL_HANDLE( XE_API, Entity );
DECL_HANDLE( XE_API, Component );

enum class GameObjectType
{
	STATIC,
	DYNAMIC,
};
DECL_META_ENUM( XE_API, GameObjectType );


END_XE_NAMESPACE

#endif // __TYPE_H__BB848F51_DB84_4BE8_9C2D_C6B7F7E738A9
