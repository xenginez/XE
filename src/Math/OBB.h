/*!
 * \file   OBB.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/28
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __OBB_H__C092424D_239B_4C6E_857D_2CEC52810C85
#define __OBB_H__C092424D_239B_4C6E_857D_2CEC52810C85

#include "Vec3.h"
#include "Quat.h"

BEG_XE_NAMESPACE

class XE_API alignas( 16 ) OBB
{
public:
	Vec3 center;
	Vec3 extent;
	Quat rotation;

public:
	OBB();

	OBB( const OBB& val );

	OBB( const AABB& box, const Quat& orient );

	OBB( const Vec3& center, const Vec3& extent, const Quat& orient );

	~OBB();

public:
	OBB& operator =( const OBB& val );

public:
	bool Intersect( const OBB& val ) const;

	bool Intersect( const AABB& val ) const;

	bool Intersect( const Line& val ) const;

	bool Intersect( const Plane& val ) const;

	bool Intersect( const Sphere& val ) const;

	bool Intersect( const Frustum& val ) const;

	std::pair<bool, XE::float32> Intersect( const Ray& ray, bool discardInside = true ) const;

};
DECL_META_CLASS( XE_API, OBB );

END_XE_NAMESPACE

#endif // __OBB_H__C092424D_239B_4C6E_857D_2CEC52810C85
