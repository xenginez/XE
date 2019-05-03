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
		float d[2];
		struct { float x, y; };
	};

public:
	Vec2();

	Vec2( float val );

	Vec2( const Vec2& val );

	Vec2( float x, float y );

public:
	Vec2& operator=( float val );

	Vec2& operator=( const Vec2& val );

public:
	float& operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 2 );
		return d[val];
	}

	float operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 2 );
		return d[val];
	}

};
DECL_META_CLASS( MATH_API, Vec2 );

END_XE_NAMESAPCE

#endif // __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8
