/*!
 * \file   Mat4.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MAT4_H__37122410_1C8D_44A2_9830_6F4B075415DF
#define __MAT4_H__37122410_1C8D_44A2_9830_6F4B075415DF

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T > class alignas( 16 ) Mat4
{
public:
	using value_type = T;

public:
	static const Mat4 Zero;
	static const Mat4 Identity;

public:
	union
	{
		struct
		{
			value_type m00, m01, m02, m03;
			value_type m10, m11, m12, m13;
			value_type m20, m21, m22, m23;
			value_type m30, m31, m32, m33;
		};
		value_type d[16];
		value_type m[4][4];
	};

public:
	Mat4()
		: m00( 0.0f ), m01( 0.0f ), m02( 0.0f ), m03( 0.0f )
		, m10( 0.0f ), m11( 0.0f ), m12( 0.0f ), m13( 0.0f )
		, m20( 0.0f ), m21( 0.0f ), m22( 0.0f ), m23( 0.0f )
		, m30( 0.0f ), m31( 0.0f ), m32( 0.0f ), m33( 0.0f )
	{
	}

	Mat4( value_type * val )
	{
		std::memcpy( d, val, sizeof( value_type ) * 16 );
	}

	template< typename U > Mat4( const Mat3< U > & val )
		:m00( val.m00 ), m01( val.m01 ), m02( val.m02 ), m03( 0 )
		, m10( val.m10 ), m11( val.m11 ), m12( val.m12 ), m13( 0 )
		, m20( val.m20 ), m21( val.m21 ), m22( val.m22 ), m23( 0 )
		, m30( 0 ), m31( 0 ), m32( 0 ), m33( 1 )
	{
	}

	template< typename U > Mat4( const Mat4< U > & val )
		:m00( val.m00 ), m01( val.m01 ), m02( val.m02 ), m03( val.m03 )
		, m10( val.m10 ), m11( val.m11 ), m12( val.m12 ), m13( val.m13 )
		, m20( val.m20 ), m21( val.m21 ), m22( val.m22 ), m23( val.m23 )
		, m30( val.m30 ), m31( val.m31 ), m32( val.m32 ), m33( val.m33 )
	{
	}

	Mat4( value_type m00, value_type m01, value_type m02, value_type m03, value_type m10, value_type m11, value_type m12, value_type m13, value_type m20, value_type m21, value_type m22, value_type m23, value_type m30, value_type m31, value_type m32, value_type m33 )
		: m00( m00 ), m01( m01 ), m02( m02 ), m03( m03 )
		, m10( m10 ), m11( m11 ), m12( m12 ), m13( m13 )
		, m20( m20 ), m21( m21 ), m22( m22 ), m23( m23 )
		, m30( m30 ), m31( m31 ), m32( m32 ), m33( m33 )
	{
	}

public:
	template< typename U > Mat4 & operator = ( const Mat3< U > & val )
	{
		m00 = val.m00; m01 = val.m01; m02 = val.m02; m03 = 0;
		m10 = val.m10; m11 = val.m11; m12 = val.m12; m13 = 0;
		m20 = val.m20; m21 = val.m21; m22 = val.m22; m23 = 0;
		m30 = 0; m31 = 0; m32 = 0; m33 = 1;

		return *this;
	}

	template< typename U > Mat4 & operator = ( const Mat4< U > & val )
	{
		m00 = val.m00; m01 = val.m01; m02 = val.m02; m03 = val.m03;
		m10 = val.m10; m11 = val.m11; m12 = val.m12; m13 = val.m13;
		m20 = val.m20; m21 = val.m21; m22 = val.m22; m23 = val.m23;
		m30 = val.m30; m31 = val.m31; m32 = val.m32; m33 = val.m33;

		return *this;
	}

public:
	value_type * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

	const value_type * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

};

template< typename T > const XE::Mat4< T > XE::Mat4< T >::Zero = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0 };
template< typename T > const XE::Mat4< T > XE::Mat4< T >::Identity = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1 };

using Mat4i = Mat4< XE::int32 >;
using Mat4f = Mat4< XE::float32 >;
using Mat4d = Mat4< XE::float64 >;

DECL_META_CLASS( XE_API, Mat4i );
DECL_META_CLASS( XE_API, Mat4f );
DECL_META_CLASS( XE_API, Mat4d );

END_XE_NAMESPACE

#endif // __MAT4_H__37122410_1C8D_44A2_9830_6F4B075415DF
