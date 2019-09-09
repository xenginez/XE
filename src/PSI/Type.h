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

DECL_PTR( IPhysicsContext );

DECL_HANDLE( PSI_API, Shape );
DECL_HANDLE( PSI_API, Joint );
DECL_HANDLE( PSI_API, SoftBody );
DECL_HANDLE( PSI_API, RigidBody );
DECL_HANDLE( PSI_API, Collision );
DECL_HANDLE( PSI_API, Constraint );

enum class PhysicsContextType
{
	EMPTY,
	BOX2D,
	PHYSX,
	BULLET,
};
DECL_META_ENUM( PSI_API, PhysicsContextType );

struct HitResult
{
	Array< XE::Vec3 > HitBegs;
	Array< XE::Vec3 > HitEnds;
	Array< XE::real > HitFractions;
	Array< CollisionHandle > Collisions;
};

struct PSI_API RayHitResult : public HitResult
{
	RayHitResult( const XE::Ray & ray );

	XE::Ray Ray;
};

struct PSI_API BoxHitResult : public HitResult
{
	BoxHitResult( const XE::AABB & box );

	XE::AABB Box;
};

struct PSI_API PointHitResult : public HitResult
{
	PointHitResult( const XE::Vec3 & beg, const XE::Vec3 & end );

	XE::Vec3 Beg;
	XE::Vec3 End;
};

struct PSI_API SphereHitResult : public HitResult
{
	SphereHitResult( const XE::Sphere & sphere );

	XE::Sphere Sphere;
};

END_XE_NAMESPACE

#endif // TYPE_H__5D749CD1_5506_4CF0_9AD1_5E75D29FACCB
