/*!
 * \file   Plane.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PLANE_H__56D96450_7C65_4A4A_ABC2_AF8D392BB432
#define __PLANE_H__56D96450_7C65_4A4A_ABC2_AF8D392BB432

#include "Vec3.h"

BEG_XE_NAMESPACE

class MATH_API Plane
{
public:
	Vec3 normal;
	float distance;

public:
	Plane();

	Plane( const Plane& val );

	Plane( const Vec3& normal, float d );

	Plane( float a, float b, float c, float d );

	Plane( const Vec3& normal, const Vec3& point );

	Plane( const Vec3& point0, const Vec3& point1, const Vec3& point2 );

public:
	Plane& operator=( const Plane& val );

	bool operator ==( const Plane& val ) const;

	bool operator !=( const Plane& val ) const;

public:
	SideType GetSide( const Vec3& val ) const;

	SideType GetSide( const AABB& val ) const;

	SideType GetSide( const Sphere& val ) const;

public:
	float Normalize();

	float GetDistance( const Vec3& val ) const;

public:
	Vec3 Project( const Vec3& val ) const;

public:
	bool Intersect( const OBB& val ) const;

	bool Intersect( const AABB& val ) const;

	bool Intersect( const Line& val ) const;

	bool Intersect( const Plane& val ) const;

	bool Intersect( const Sphere& val ) const;

	bool Intersect( const Frustum& val ) const;

	std::pair<bool, float> Intersect( const Ray& ray, bool discardInside = true ) const;

};
DECL_META_CLASS( MATH_API, Plane );

END_XE_NAMESAPCE

#endif // __PLANE_H__56D96450_7C65_4A4A_ABC2_AF8D392BB432
