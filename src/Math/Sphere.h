/*!
 * \file   Sphere.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SPHERE_H__06E9A06D_DAE8_4648_8E21_51748C5A3BC7
#define __SPHERE_H__06E9A06D_DAE8_4648_8E21_51748C5A3BC7

#include "Vec3.h"
#include "Mat4.h"

BEG_XE_NAMESPACE

class XE_API alignas( 16 ) Sphere
{
public:
	static const Sphere Zero;

public:
	Vec3f center;
	XE::float32 radius;

public:
	Sphere();

	Sphere( const Sphere& val );

	Sphere( const Vec3f&center, XE::float32 radius );

public:
	Sphere& operator=( const Sphere & val );

	bool operator ==( const Sphere& val ) const;

	bool operator !=( const Sphere& val ) const;

public:
	bool Contains( const Vec3f& val ) const;

public:
	bool Intersect( const OBB& val ) const;

	bool Intersect( const AABB& val ) const;

	bool Intersect( const Line& val ) const;

	bool Intersect( const Plane& val ) const;

	bool Intersect( const Sphere& val ) const;

	bool Intersect( const Frustum& val ) const;

	std::pair<bool, XE::float32> Intersect( const Ray& ray, bool discardInside = true ) const;

public:
	void Merge( const Vec3f& val );

	void Merge( const Sphere& val );

public:
	void Transform( const Mat4f& val );
};
DECL_META_CLASS( XE_API, Sphere );

END_XE_NAMESPACE

#endif // __SPHERE_H__06E9A06D_DAE8_4648_8E21_51748C5A3BC7
