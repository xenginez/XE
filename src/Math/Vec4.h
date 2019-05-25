/*!
 * \file   Vec4.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VEC4_H__F3F6A44B_20F0_4913_A1F4_A89DE089D43D
#define __VEC4_H__F3F6A44B_20F0_4913_A1F4_A89DE089D43D

#include "Type.h"

BEG_XE_NAMESPACE

class MATH_API Vec4
{
public:
	static const Vec4 One;
	static const Vec4 Zero;
	static const Vec4 Infinity;

public:
	union
	{
		struct { XE::float32 x, y, z, w; };
		XE::float32 d[4];
	};

public:
	Vec4();

	Vec4( XE::float32 x, XE::float32 y, XE::float32 z, XE::float32 w );

	Vec4( const Vec4& val );

public:
	Vec4& operator=( const Vec4& val );

public:
	XE::float32& operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 4 );
		return d[val];
	}

	XE::float32 operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 4 );
		return d[val];
	}
};
DECL_META_CLASS( MATH_API, Vec4 );

END_XE_NAMESAPCE

#endif // __VEC4_H__F3F6A44B_20F0_4913_A1F4_A89DE089D43D
