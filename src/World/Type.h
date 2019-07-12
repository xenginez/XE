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

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( Component );
DECL_PTR( GameObject );
DECL_PTR( WorldObject );
DECL_PTR( SceneComponent );
DECL_PTR( RenderComponent );
DECL_PTR( BehaviorComponent );
template< typename _Ty > class MakeRect;
template< typename _Ty > class MakeAABB;


enum class GameObjectType
{
	STATIC,
	DYNAMIC,
};
DECL_META_ENUM( WORLD_API, GameObjectType );


DECL_HANDLE( WORLD_API, Component );
DECL_HANDLE( WORLD_API, GameObject );


END_XE_NAMESPACE

#endif // __TYPE_H__BB848F51_DB84_4BE8_9C2D_C6B7F7E738A9
