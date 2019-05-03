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

BEG_XE_NAMESPACE

class MATH_API Ray
{
public:
	Vec3 origin;
	Vec3 direction;

public:
	Ray();

	Ray( const Vec3& origin, const Vec3& direction );

public:
	Ray& operator=( const Ray & val );

	bool operator ==( const Ray& val ) const;

	bool operator !=( const Ray& val ) const;

public:
	Vec3 GetPoint( float val ) const;

public:
	std::pair<bool, float> Intersect( const OBB& val ) const;

	std::pair<bool, float> Intersect( const AABB& val ) const;

	std::pair<bool, float> Intersect( const Line& val ) const;

	std::pair<bool, float> Intersect( const Plane& val ) const;

	std::pair<bool, float> Intersect( const Sphere& val ) const;

	std::pair<bool, float> Intersect( const Frustum& val ) const;

	std::pair<bool, float> Intersect( const Ray& ray, bool discardInside = true ) const;

	std::pair<bool, float> Intersect( const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& normal, bool positiveSide = true, bool negativeSide = true ) const;

public:
	void Transform( const Mat4& val );

	void TransformAffine( const Mat4& val );

};
DECL_META_CLASS( MATH_API, Ray );

END_XE_NAMESAPCE

#endif // __RAY_H__5874E305_1881_4FDF_B7EE_44A07BD36195
