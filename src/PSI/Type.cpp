#include "Type.h"

USING_XE

XE::RayHitResult::RayHitResult( const XE::Ray & ray )
	: Ray( ray )
{

}

XE::BoxHitResult::BoxHitResult( const XE::AABB & box )
	: Box( box )
{

}

XE::PointHitResult::PointHitResult( const XE::Vec3 & beg, const XE::Vec3 & end )
	: Beg( beg ), End( end )
{

}

XE::SphereHitResult::SphereHitResult( const XE::Sphere & sphere )
	: Sphere( sphere )
{

}
