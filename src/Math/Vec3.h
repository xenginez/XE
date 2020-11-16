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

template< typename T > class alignas( 16 ) Vec3
{
public:
	using value_type = T;

public:
	static const Vec3 One;
	static const Vec3 Zero;
	static const Vec3 Forward;
	static const Vec3 Backward;
	static const Vec3 Left;
	static const Vec3 Right;
	static const Vec3 Up;
	static const Vec3 Down;

public:
	union
	{
		struct { value_type x, y, z; };
		value_type d[3];
	};

public:
	Vec3()
		:x( 0 ), y( 0 ), z( 0 )
	{
	}

	Vec3( value_type val )
		: x( val ), y( val ), z( val )
	{

	}

	Vec3( value_type x, value_type y, value_type z )
		: x( x ), y( y ), z( z )
	{

	}

	template< typename U > Vec3( const Vec3< U > & val )
		: x( val.x ), y( val.y ), z( val.z )
	{

	}

public:
	Vec3 & operator=( value_type val )
	{
		x = val;
		y = val;
		z = val;

		return *this;
	}

	Vec3 & operator=( const Vec3 & val )
	{
		x = val.x;
		y = val.y;
		z = val.z;

		return *this;
	}

public:
	value_type & operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 3 );

		return d[val];
	}

	value_type operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 3 );

		return d[val];
	}
};

template< typename T >
const XE::Vec3< T > XE::Vec3< T >::One = { 1, 1, 1 };
template< typename T >
const XE::Vec3< T > XE::Vec3< T >::Zero = { 0, 0, 0 };
template< typename T >
const XE::Vec3< T > XE::Vec3< T >::Forward = { 0, 0, 1 };
template< typename T >
const XE::Vec3< T > XE::Vec3< T >::Backward = { 0, 0, -1 };
template< typename T >
const XE::Vec3< T > XE::Vec3< T >::Left = { -1, 0, 0 };
template< typename T >
const XE::Vec3< T > XE::Vec3< T >::Right = { 1, 0, 0 };
template< typename T >
const XE::Vec3< T > XE::Vec3< T >::Up = { 0, 1, 0 };
template< typename T >
const XE::Vec3< T > XE::Vec3< T >::Down = { 0, -1, 0 };

using Vec3i = Vec3<XE::int32>;
using Vec3f = Vec3<XE::float32>;
using Vec3d = Vec3<XE::float64>;

DECL_META_CLASS( XE_API, Vec3i );
DECL_META_CLASS( XE_API, Vec3f );
DECL_META_CLASS( XE_API, Vec3d );

END_XE_NAMESPACE

#endif // __VEC3_H__1E180C4F_2B1D_46E9_A0C6_F2CC0918BCE3
