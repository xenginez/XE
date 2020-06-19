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

class XE_API alignas( 16 ) Vec2
{
public:
	static const Vec2 One;
	static const Vec2 Zero;
	static const Vec2 Infinity;

public:
	union
	{
		XE::real d[2];
		struct { XE::real x, y; };
	};

public:
	Vec2();

	Vec2( XE::real val );

	Vec2( const Vec2& val );

	Vec2( XE::real x, XE::real y );

public:
	Vec2& operator=( XE::real val );

	Vec2& operator=( const Vec2& val );

public:
	XE::real& operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 2 );
		return d[val];
	}

	XE::real operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 2 );
		return d[val];
	}

};
DECL_META_CLASS( XE_API, Vec2 );

END_XE_NAMESPACE

#endif // __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8
