/*!
 * \file   Line.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/13
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __LINE_H__525C993C_1BCC_44B9_8AEF_0BE8FDF0474A
#define __LINE_H__525C993C_1BCC_44B9_8AEF_0BE8FDF0474A

#include "Ray.h"

BEG_XE_NAMESPACE

class XE_API Line
{
public:
	union
	{
		struct  
		{
			Vec3 start;
			Vec3 end;
		};

		Vec3 point[2];
	};

public:
	Line();

	Line( const Line & val );

	Line( const Ray& ray, XE::real distance );

	Line( const Vec3& start, const Vec3& end );

	~Line();

public:
	Line& operator=( const Line& val );

public:
	bool operator ==( const Line& val ) const;

	bool operator !=( const Line& val ) const;

public:
	Ray GetRay() const;

	XE::real GetDistance() const;

	Vec3 GetDirection() const;

public:
	bool Intersect( const OBB& val ) const;

	bool Intersect( const AABB& val ) const;

	bool Intersect( const Line& val ) const;

	bool Intersect( const Plane& val ) const;

	bool Intersect( const Sphere& val ) const;

	bool Intersect( const Frustum& val ) const;

	std::pair<bool, XE::real> Intersect( const Ray& ray, bool discardInside = true ) const;

};
DECL_META_CLASS( XE_API, Line );

END_XE_NAMESPACE

#endif // __LINE_H__525C993C_1BCC_44B9_8AEF_0BE8FDF0474A
