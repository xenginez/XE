/*!
 * \file	Capsule.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/05
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CAPSULE_H__F02E074A_E970_41B4_B55A_01D844A36129
#define CAPSULE_H__F02E074A_E970_41B4_B55A_01D844A36129

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API alignas( 16 ) Capsule
{
public:
	XE::float32 radius;
	XE::float32 height;

public:
	Capsule();

	Capsule( const Capsule & val );

	Capsule( XE::float32 radius, XE::float32 height );

public:
	Capsule & operator=( const Capsule & val );

	bool operator ==( const Capsule & val ) const;

	bool operator !=( const Capsule & val ) const;

public:
	bool Contains( const Vec3f & val ) const;

public:
	bool Intersect( const OBB & val ) const;

	bool Intersect( const AABB & val ) const;

	bool Intersect( const Line & val ) const;

	bool Intersect( const Plane & val ) const;

	bool Intersect( const Sphere & val ) const;

	bool Intersect( const Frustum & val ) const;

	std::pair<bool, XE::float32> Intersect( const Ray & ray, bool discardInside = true ) const;

};
DECL_META_CLASS( XE_API, Capsule );

END_XE_NAMESPACE

#endif // CAPSULE_H__F02E074A_E970_41B4_B55A_01D844A36129
