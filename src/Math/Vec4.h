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

template< typename T > class alignas( 16 ) Vec4
{
public:
	using value_type = T;

public:
	static const Vec4 One;
	static const Vec4 Zero;

public:
	union
	{
		struct { value_type x, y, z, w; };
		value_type d[4];
	};

public:
	Vec4()
		:x( 0 ), y( 0 ), z( 0 ), w( 0 )
	{
	}

	template< typename U > Vec4( const Vec4< U > & val )
		: x( val.x ), y( val.y ), z( val.z ), w( val.w )
	{
	}

	Vec4( value_type x, value_type y, value_type z, value_type w )
		: x( x ), y( y ), z( z ), w( w )
	{
	}

public:
	Vec4 & operator=( const Vec4 & val )
	{
		x = val.x;
		y = val.y;
		z = val.z;
		w = val.w;

		return *this;
	}

public:
	value_type& operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 4 );

		return d[val];
	}

	value_type operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 4 );

		return d[val];
	}
};

template< typename T >
const XE::Vec4< T > XE::Vec4< T >::One = { 1, 1, 1, 1 };
template< typename T >
const XE::Vec4< T > XE::Vec4< T >::Zero = { 0, 0, 0, 0 };

using Vec4i = Vec4< XE::int32 >;
using Vec4f = Vec4< XE::float32 >;
using Vec4d = Vec4< XE::float64 >;

DECL_META_CLASS( XE_API, Vec4i );
DECL_META_CLASS( XE_API, Vec4f );
DECL_META_CLASS( XE_API, Vec4d );

END_XE_NAMESPACE

#endif // __VEC4_H__F3F6A44B_20F0_4913_A1F4_A89DE089D43D
