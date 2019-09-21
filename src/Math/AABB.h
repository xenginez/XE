/*!
 * \file   AABB.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __AABB_H__7996BEAA_3FEA_4C40_B467_F2323FDC0382
#define __AABB_H__7996BEAA_3FEA_4C40_B467_F2323FDC0382

#include "Vec3.h"

BEG_XE_NAMESPACE

class XE_API AABB
{
public:
	Vec3 min;
	Vec3 max;

public:
	AABB();

	AABB( const AABB& val );

	AABB( const Vec3& min, const Vec3& max );

public:
	AABB& operator =( const AABB& val );

	bool operator ==( const AABB& val ) const;

	bool operator !=( const AABB& val ) const;

public:
	Vec3 GetSize() const;

	Vec3 GetCenter() const;

	XE::real GetRadius() const;

	XE::real GetVolume() const;

	Vec3 GetFarLeftTop() const;

	Vec3 GetFarRightTop() const;

	Vec3 GetFarLeftBottom() const;

	Vec3 GetFarRightBottom() const;

	Vec3 GetNearLeftTop() const;

	Vec3 GetNearRightTop() const;

	Vec3 GetNearLeftBottom() const;

	Vec3 GetNearRightBottom() const;

public:
	bool Contains( const Vec3& val ) const;

	bool Contains( const AABB& val ) const;

public:
	bool Intersect( const OBB& val ) const;

	bool Intersect( const AABB& val ) const;

	bool Intersect( const Line& val ) const;

	bool Intersect( const Plane& val ) const;

	bool Intersect( const Sphere& val ) const;

	bool Intersect( const Frustum& val ) const;

	std::pair<bool, XE::real> Intersect( const Ray& ray, bool discardInside = true ) const;

public:
	void Scale( XE::real val );

	void Scale( const Vec3& val );

public:
	void Merge( const Vec3& val );

	void Merge( const AABB& val );

public:
	void Transform( const Mat4& val );

	void TransformAffine( const Mat4& val );

};
DECL_META_CLASS( XE_API, AABB );

END_XE_NAMESPACE

#endif // __AABB_H__7996BEAA_3FEA_4C40_B467_F2323FDC0382
