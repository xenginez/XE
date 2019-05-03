/*!
 * \file   Vec3.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VEC3_H__1E180C4F_2B1D_46E9_A0C6_F2CC0918BCE3
#define __VEC3_H__1E180C4F_2B1D_46E9_A0C6_F2CC0918BCE3

#include "Type.h"

BEG_XE_NAMESPACE

class MATH_API Vec3
{
public:
	static const Vec3 One;
	static const Vec3 Zero;
	static const Vec3 Forward;
	static const Vec3 Backward;
	static const Vec3 Left;
	static const Vec3 Right;
	static const Vec3 Up;
	static const Vec3 Down;
	static const Vec3 Infinity;

public:
	union
	{
		struct { float x, y, z; };
		float d[3];
	};

public:
	Vec3();

	Vec3( float val );

	Vec3( const Vec3& val );

	Vec3( float x, float y, float z );

public:
	Vec3& operator=( float val );

	Vec3& operator=( const Vec3 & val );

public:
	float& operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 3 );
		return d[val];
	}

	float operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 3 );
		return d[val];
	}

};
DECL_META_CLASS( MATH_API, Vec3 );

END_XE_NAMESAPCE

#endif // __VEC3_H__1E180C4F_2B1D_46E9_A0C6_F2CC0918BCE3
