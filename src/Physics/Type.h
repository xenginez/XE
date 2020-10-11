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

#include "Utils/Handle.hpp"

BEG_XE_NAMESPACE

DECL_PTR( Shape );
DECL_PTR( RigidBody );
DECL_PTR( Constraint );
DECL_PTR( PhysicsScene );
DECL_PTR( PhysicsMaterial );

DECL_HANDLE( XE_API, Shape );
DECL_HANDLE( XE_API, RigidBody );
DECL_HANDLE( XE_API, Constraint );
DECL_HANDLE( XE_API, PhysicsScene );
DECL_HANDLE( XE_API, PhysicsMaterial );

enum ShapeFlag
{
	SIMULATION_SHAPE = ( 1 << 0 ),
	SCENE_QUERY_SHAPE = ( 1 << 1 ),
	TRIGGER_SHAPE = ( 1 << 2 ),
	VISUALIZATION = ( 1 << 3 )
};
DECL_META_ENUM( XE_API, ShapeFlag );

enum class PhysicsMaterialFlag
{
	DISABLE_FRICTION = 1 << 0,
	DISABLE_STRONG_FRICTION = 1 << 1,
	IMPROVED_PATCH_FRICTION = 1 << 2,
};
DECL_META_ENUM( XE_API, PhysicsMaterialFlag );

enum class CombineMode
{
	AVERAGE,
	MIN,
	MULTIPLY,
	MAX,
	N_VALUES,
	PAD_32 = 0x7fffffff
};
DECL_META_ENUM( XE_API, CombineMode );

enum class RigidDynamicLockFlag
{
	LINEAR_X = ( 1 << 0 ),
	LINEAR_Y = ( 1 << 1 ),
	LINEAR_Z = ( 1 << 2 ),
	ANGULAR_X = ( 1 << 3 ),
	ANGULAR_Y = ( 1 << 4 ),
	ANGULAR_Z = ( 1 << 5 ),
	LINEAR_XY = LINEAR_X | LINEAR_Y,
	LINEAR_XZ = LINEAR_X | LINEAR_Z,
	LINEAR_YZ = LINEAR_Y | LINEAR_Z,
	LINEAR_XYZ = LINEAR_X | LINEAR_Y | LINEAR_Z,
	ANGULAR_XY = ANGULAR_X | ANGULAR_Y,
	ANGULAR_XZ = ANGULAR_X | ANGULAR_Z,
	ANGULAR_YZ = ANGULAR_Y | ANGULAR_Z,
	ANGULAR_XYZ = ANGULAR_X | ANGULAR_Y | ANGULAR_Z,
};
DECL_META_ENUM( XE_API, RigidDynamicLockFlag );

END_XE_NAMESPACE

#endif // __TYPE_H__1C1C3DA4_0D11_418D_8EC6_B03DB2644537
