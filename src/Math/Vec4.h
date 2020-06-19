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

class XE_API alignas( 16 ) Vec4
{
public:
	static const Vec4 One;
	static const Vec4 Zero;
	static const Vec4 Infinity;

public:
	union
	{
		struct { XE::real x, y, z, w; };
		XE::real d[4];
	};

public:
	Vec4();

	Vec4( XE::real x, XE::real y, XE::real z, XE::real w );

	Vec4( const Vec4& val );

public:
	Vec4& operator=( const Vec4& val );

public:
	XE::real& operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 4 );
		return d[val];
	}

	XE::real operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 4 );
		return d[val];
	}
};
DECL_META_CLASS( XE_API, Vec4 );

END_XE_NAMESPACE

#endif // __VEC4_H__F3F6A44B_20F0_4913_A1F4_A89DE089D43D
