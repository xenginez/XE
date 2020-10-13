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

#include "Utils/Flags.hpp"
#include "Utils/Handle.hpp"

BEG_XE_NAMESPACE

DECL_PTR( Shape );
DECL_PTR( Pruning );
DECL_PTR( RigidBody );
DECL_PTR( Aggregate );
DECL_PTR( Constraint );
DECL_PTR( Collection );
DECL_PTR( PhysicsScene );
DECL_PTR( PhysicsMaterial );
DECL_PTR( ConstraintConnector );

DECL_HANDLE( XE_API, Shape );
DECL_HANDLE( XE_API, Pruning );
DECL_HANDLE( XE_API, RigidBody );
DECL_HANDLE( XE_API, Aggregate );
DECL_HANDLE( XE_API, Constraint );
DECL_HANDLE( XE_API, Collection );
DECL_HANDLE( XE_API, PhysicsScene );
DECL_HANDLE( XE_API, PhysicsMaterial );

enum class ShapeFlag
{
	SIMULATION_SHAPE = 1 << 0,
	SCENE_QUERY_SHAPE = 1 << 1,
	TRIGGER_SHAPE = 1 << 2,
	VISUALIZATION = 1 << 3,
};
DECL_META_FLAGS( XE_API, ShapeFlag, ShapeFlags );

enum class FrictionType
{
	PATCH,
	ONE_DIRECTIONAL,
	TWO_DIRECTIONAL,
	FRICTION_COUNT
};
DECL_META_ENUM( XE_API, FrictionType );

enum class PhysicsSceneFlag
{
	ENABLE_ACTIVE_ACTORS = 1 << 0,
	ENABLE_CCD = 1 << 1,
	DISABLE_CCD_RESWEEP = 1 << 2,
	ADAPTIVE_FORCE = 1 << 3,
	ENABLE_PCM = 1 << 6,
	DISABLE_CONTACT_REPORT_BUFFER_RESIZE = 1 << 7,
	DISABLE_CONTACT_CACHE = 1 << 8,
	REQUIRE_RW_LOCK = 1 << 9,
	ENABLE_STABILIZATION = 1 << 10,
	ENABLE_AVERAGE_POINT = 1 << 11,
	EXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS = 1 << 12,
	ENABLE_GPU_DYNAMICS = 1 << 13,
	ENABLE_ENHANCED_DETERMINISM = 1 << 14,
	ENABLE_FRICTION_EVERY_ITERATION = 1 << 15,
	MUTABLE_FLAGS = ENABLE_ACTIVE_ACTORS | EXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS,
};
DECL_META_FLAGS( XE_API, PhysicsSceneFlag, PhysicsSceneFlags );

enum class PhysicsQueryFlag
{
	STATIC = 1 << 0,
	DYNAMIC = 1 << 1,
};
DECL_META_FLAGS( XE_API, PhysicsQueryFlag, PhysicsQueryFlags );

enum class PhysicsMaterialFlag
{
	DISABLE_FRICTION = 1 << 0,
	DISABLE_STRONG_FRICTION = 1 << 1,
	IMPROVED_PATCH_FRICTION = 1 << 2,
};
DECL_META_FLAGS( XE_API, PhysicsMaterialFlag, PhysicsMaterialFlags );

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
	LINEAR_X = 1 << 0,
	LINEAR_Y = 1 << 1,
	LINEAR_Z = 1 << 2,
	ANGULAR_X = 1 << 3,
	ANGULAR_Y = 1 << 4,
	ANGULAR_Z = 1 << 5,
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

struct XE_API QueryHitResult
{
	XE::ShapeHandle Shape;
	XE::RigidBodyHandle Body;

	XE::Vec3 Position;
	XE::Vec3 Normal;
	XE::float32 Depth;
};

END_XE_NAMESPACE

#endif // __TYPE_H__1C1C3DA4_0D11_418D_8EC6_B03DB2644537
