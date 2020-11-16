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

#include "Math/Math.h"
#include "Utils/Flags.hpp"
#include "Utils/Handle.hpp"

BEG_XE_NAMESPACE

DECL_PTR( Joint );
DECL_PTR( Shape );
DECL_PTR( BoxShape );
DECL_PTR( PlaneShape );
DECL_PTR( SphereShape );
DECL_PTR( CapsuleShape );
DECL_PTR( ConvexMeshShape );
DECL_PTR( HeightFieldShape );
DECL_PTR( RigidBody );
DECL_PTR( RigidActor );
DECL_PTR( RigidStatic );
DECL_PTR( RigidDynamic );
DECL_PTR( Constraint );
DECL_PTR( Collection );
DECL_PTR( PhysicsScene );
DECL_PTR( PhysicsMaterial );

DECL_HANDLE( XE_API, Joint );
DECL_HANDLE( XE_API, Shape );
DECL_HANDLE( XE_API, RigidActor );
DECL_HANDLE( XE_API, Constraint );
DECL_HANDLE( XE_API, Collection );
DECL_HANDLE( XE_API, PhysicsScene );
DECL_HANDLE( XE_API, PhysicsMaterial );

OBJECT_ALLOCATOR_PROXY( XE::Shape );
OBJECT_ALLOCATOR_PROXY( XE::BoxShape );
OBJECT_ALLOCATOR_PROXY( XE::PlaneShape );
OBJECT_ALLOCATOR_PROXY( XE::SphereShape );
OBJECT_ALLOCATOR_PROXY( XE::CapsuleShape );
OBJECT_ALLOCATOR_PROXY( XE::ConvexMeshShape );
OBJECT_ALLOCATOR_PROXY( XE::HeightFieldShape );
OBJECT_ALLOCATOR_PROXY( XE::RigidStatic );
OBJECT_ALLOCATOR_PROXY( XE::RigidDynamic );

enum class ShapeFlag
{
	SIMULATION_SHAPE = 1 << 0,
	SCENE_QUERY_SHAPE = 1 << 1,
	TRIGGER_SHAPE = 1 << 2,
	VISUALIZATION = 1 << 3,
};
DECL_META_FLAGS( XE_API, ShapeFlag, ShapeFlags );

enum class RigidActorFlag
{
	VISUALIZATION = 1 << 0,
	DISABLE_GRAVITY = 1 << 1,
	SEND_SLEEP_NOTIFIES = 1 << 2,
	DISABLE_SIMULATION = 1 << 3,
};
DECL_META_FLAGS( XE_API, RigidActorFlag, RigidActorFlags );

enum class ConstraintFlag
{
	BROKEN = 1 << 0,
	PROJECT_TO_ACTOR0 = 1 << 1,
	PROJECT_TO_ACTOR1 = 1 << 2,
	PROJECTION = PROJECT_TO_ACTOR0 | PROJECT_TO_ACTOR1,
	COLLISION_ENABLED = 1 << 3,
	VISUALIZATION = 1 << 4,
	DRIVE_LIMITS_ARE_FORCES = 1 << 5,
	IMPROVED_SLERP = 1 << 7,
	DISABLE_PREPROCESSING = 1 << 8,
	ENABLE_EXTENDED_LIMITS = 1 << 9,
	GPU_COMPATIBLE = 1 << 10,
};
DECL_META_FLAGS( XE_API, ConstraintFlag, ConstraintFlags );

enum class RigidBodyFlag
{
	KINEMATIC = 1 << 0,
	USE_KINEMATIC_TARGET_FOR_SCENE_QUERIES = 1 << 1,
	ENABLE_CCD = 1 << 2,
	ENABLE_CCD_FRICTION = 1 << 3,
	ENABLE_POSE_INTEGRATION_PREVIEW = 1 << 4,
	ENABLE_SPECULATIVE_CCD = 1 << 5,
	ENABLE_CCD_MAX_CONTACT_IMPULSE = 1 << 6,
	RETAIN_ACCELERATIONS = 1 << 7,
};
DECL_META_FLAGS( XE_API, RigidBodyFlag, RigidBodyFlags );

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

enum class RigidDynamicLockFlag
{
	LINEAR_X = 1 << 0,
	LINEAR_Y = 1 << 1,
	LINEAR_Z = 1 << 2,
	ANGULAR_X = 1 << 3,
	ANGULAR_Y = 1 << 4,
	ANGULAR_Z = 1 << 5,
};
DECL_META_FLAGS( XE_API, RigidDynamicLockFlag, RigidDynamicLockFlags );

enum class ForceMode
{
	FORCE,
	IMPULSE,
	VELOCITY_CHANGE,
	ACCELERATION
};
DECL_META_ENUM( XE_API, ForceMode );

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

enum class FrictionType
{
	PATCH,
	ONE_DIRECTIONAL,
	TWO_DIRECTIONAL,
	FRICTION_COUNT
};
DECL_META_ENUM( XE_API, FrictionType );

struct XE_API HullPolygon
{
	XE::Plane Plane;
	XE::uint32 IndexCount;
	XE::uint32 IndexOffset;
};

struct XE_API QueryHitResult
{
	XE::ShapeHandle Shape;
	XE::RigidActorHandle Actor;

	XE::Vec3f Position;
	XE::Vec3f Normal;
	XE::float32 Depth;
};

END_XE_NAMESPACE

#endif // __TYPE_H__1C1C3DA4_0D11_418D_8EC6_B03DB2644537
