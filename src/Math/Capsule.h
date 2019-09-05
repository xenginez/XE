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

class MATH_API Capsule
{
public:
	XE::real radius;
	XE::real height;

public:
	Capsule();

	Capsule( const Capsule & val );

	Capsule( XE::real radius, XE::real height );

public:
	Capsule & operator=( const Capsule & val );

	bool operator ==( const Capsule & val ) const;

	bool operator !=( const Capsule & val ) const;

public:
	bool Contains( const Vec3 & val ) const;

public:
	bool Intersect( const OBB & val ) const;

	bool Intersect( const AABB & val ) const;

	bool Intersect( const Line & val ) const;

	bool Intersect( const Plane & val ) const;

	bool Intersect( const Sphere & val ) const;

	bool Intersect( const Frustum & val ) const;

	std::pair<bool, XE::real> Intersect( const Ray & ray, bool discardInside = true ) const;

};
DECL_META_CLASS( MATH_API, Capsule );

END_XE_NAMESPACE

#endif // CAPSULE_H__F02E074A_E970_41B4_B55A_01D844A36129
