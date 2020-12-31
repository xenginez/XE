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

#include "Mat.h"
#include "Vec3.h"

BEG_XE_NAMESPACE

class XE_API alignas( 16 ) AABB
{
public:
	Vec3f min;
	Vec3f max;

public:
	AABB();

	AABB( const AABB& val );

	AABB( const Vec3f& min, const Vec3f& max );

public:
	AABB& operator =( const AABB& val );

	bool operator ==( const AABB& val ) const;

	bool operator !=( const AABB& val ) const;

public:
	Vec3f GetSize() const;

	Vec3f GetCenter() const;

	XE::float32 GetRadius() const;

	XE::float32 GetVolume() const;

	Vec3f GetFarLeftTop() const;

	Vec3f GetFarRightTop() const;

	Vec3f GetFarLeftBottom() const;

	Vec3f GetFarRightBottom() const;

	Vec3f GetNearLeftTop() const;

	Vec3f GetNearRightTop() const;

	Vec3f GetNearLeftBottom() const;

	Vec3f GetNearRightBottom() const;

public:
	bool Contains( const Vec3f& val ) const;

	bool Contains( const AABB& val ) const;

public:
	bool Intersect( const OBB& val ) const;

	bool Intersect( const AABB& val ) const;

	bool Intersect( const Line& val ) const;

	bool Intersect( const Plane& val ) const;

	bool Intersect( const Sphere& val ) const;

	bool Intersect( const Frustum& val ) const;

	std::pair<bool, XE::float32> Intersect( const Ray& ray, bool discardInside = true ) const;

public:
	void Scale( XE::float32 val );

	void Scale( const Vec3f& val );

public:
	void Merge( const Vec3f& val );

	void Merge( const AABB& val );

public:
	void Transform( const Mat4x4f& val );

	void TransformAffine( const Mat4x4f& val );

};
DECL_META_CLASS( XE_API, AABB );

END_XE_NAMESPACE

#endif // __AABB_H__7996BEAA_3FEA_4C40_B467_F2323FDC0382
