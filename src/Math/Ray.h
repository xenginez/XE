/*!
 * \file   Ray.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RAY_H__5874E305_1881_4FDF_B7EE_44A07BD36195
#define __RAY_H__5874E305_1881_4FDF_B7EE_44A07BD36195

#include "Vec3.h"
#include "Mat4.h"

BEG_XE_NAMESPACE

class XE_API alignas( 16 ) Ray
{
public:
	Vec3f origin;
	Vec3f direction;

public:
	Ray();

	Ray( const Vec3f& origin, const Vec3f& direction );

public:
	Ray& operator=( const Ray & val );

	bool operator ==( const Ray& val ) const;

	bool operator !=( const Ray& val ) const;

public:
	Vec3f GetPoint( XE::float32 val ) const;

public:
	std::pair<bool, XE::float32> Intersect( const OBB& val ) const;

	std::pair<bool, XE::float32> Intersect( const AABB& val ) const;

	std::pair<bool, XE::float32> Intersect( const Line& val ) const;

	std::pair<bool, XE::float32> Intersect( const Plane& val ) const;

	std::pair<bool, XE::float32> Intersect( const Sphere& val ) const;

	std::pair<bool, XE::float32> Intersect( const Frustum& val ) const;

	std::pair<bool, XE::float32> Intersect( const Ray& ray, bool discardInside = true ) const;

	std::pair<bool, XE::float32> Intersect( const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& normal, bool positiveSide = true, bool negativeSide = true ) const;

public:
	void Transform( const Mat4f& val );

	void TransformAffine( const Mat4f& val );

};
DECL_META_CLASS( XE_API, Ray );

END_XE_NAMESPACE

#endif // __RAY_H__5874E305_1881_4FDF_B7EE_44A07BD36195
