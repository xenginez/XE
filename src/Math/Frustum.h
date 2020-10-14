/*!
 * \file   Frustum.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/28
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __FRUSTUM_H__A9A7B11B_8DB7_4F63_BD17_1B7487E1141A
#define __FRUSTUM_H__A9A7B11B_8DB7_4F63_BD17_1B7487E1141A

#include "Type.h"
#include "Plane.h"

BEG_XE_NAMESPACE

class XE_API alignas( 16 ) Frustum
{
public:
	union
	{
		struct  
		{
			Plane top;
			Plane bottom;
			Plane left;
			Plane right;
			Plane near;
			Plane far;
		};
		Plane plane[6];
	};

public:
	Frustum();

	Frustum( const Frustum& val );

	~Frustum();

public:
	Frustum & operator=( const Frustum & val );

public:
	bool Intersect( const OBB& val ) const;

	bool Intersect( const AABB& val ) const;

	bool Intersect( const Line& val ) const;

	bool Intersect( const Plane& val ) const;

	bool Intersect( const Sphere& val ) const;

	bool Intersect( const Frustum& val ) const;

	std::pair<bool, XE::float32> Intersect( const Ray& ray, bool discardInside = true ) const;

};
DECL_META_CLASS( XE_API, Frustum );

END_XE_NAMESPACE

#endif // __FRUSTUM_H__A9A7B11B_8DB7_4F63_BD17_1B7487E1141A
