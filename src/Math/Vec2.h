/*!
 * \file   Vec2.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8
#define __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8

#include "Type.h"

BEG_XE_NAMESPACE

class MATH_API Vec2
{
public:
	static const Vec2 One;
	static const Vec2 Zero;
	static const Vec2 Infinity;

public:
	union
	{
		XE::float32 d[2];
		struct { XE::float32 x, y; };
	};

public:
	Vec2();

	Vec2( XE::float32 val );

	Vec2( const Vec2& val );

	Vec2( XE::float32 x, XE::float32 y );

public:
	Vec2& operator=( XE::float32 val );

	Vec2& operator=( const Vec2& val );

public:
	XE::float32& operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 2 );
		return d[val];
	}

	XE::float32 operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 2 );
		return d[val];
	}

};
DECL_META_CLASS( MATH_API, Vec2 );

END_XE_NAMESPACE

#endif // __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8
