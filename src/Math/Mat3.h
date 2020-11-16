/*!
 * \file   Mat3.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MAT3_H__C7739BBA_CC88_446C_9E5E_E8C2684E022E
#define __MAT3_H__C7739BBA_CC88_446C_9E5E_E8C2684E022E

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T > class alignas( 16 ) Mat3
{
public:
	using value_type = T;

public:
	static const Mat3 Zero;
	static const Mat3 Identity;

public:
	union
	{
		struct
		{
			value_type m00, m01, m02;
			value_type m10, m11, m12;
			value_type m20, m21, m22;
		};
		value_type d[9];
		value_type m[3][3];
	};

public:
	Mat3()
		:m00( 1 ), m01( 0 ), m02( 0 ), m10( 0 ), m11( 1 ), m12( 0 ), m20( 0 ), m21( 0 ), m22( 1 )
	{
	}

	Mat3( value_type * val )
	{
		std::memcpy( d, val, sizeof( value_type ) * 9 );
	}

	Mat3( const Quat & val )
	{
		XE::float32 x = val.x * 2.0f;
		XE::float32 y = val.y * 2.0f;
		XE::float32 z = val.z * 2.0f;
		XE::float32 xx = val.x * x;
		XE::float32 yy = val.y * y;
		XE::float32 zz = val.z * z;
		XE::float32 xy = val.x * y;
		XE::float32 xz = val.x * z;
		XE::float32 yz = val.y * z;
		XE::float32 wx = val.w * x;
		XE::float32 wy = val.w * y;
		XE::float32 wz = val.w * z;

		d[0] = 1.0f - ( yy + zz );
		d[1] = xy + wz;
		d[2] = xz - wy;

		d[3] = xy - wz;
		d[4] = 1.0f - ( xx + zz );
		d[5] = yz + wx;

		d[6] = xz + wy;
		d[7] = yz - wx;
		d[8] = 1.0f - ( xx + yy );
	}

	template< typename U > Mat3( const Mat3< U > & val )
		: m00( val.m00 ), m01( val.m01 ), m02( val.m02 ), m10( val.m10 ), m11( val.m11 ), m12( val.m12 ), m20( val.m20 ), m21( val.m21 ), m22( val.m22 )
	{

	}

	template< typename U > Mat3( const Mat4f< U > & val )
		: m00( val.m00 ), m01( val.m01 ), m02( val.m02 ), m10( val.m10 ), m11( val.m11 ), m12( val.m12 ), m20( val.m20 ), m21( val.m21 ), m22( val.m22 )
	{

	}

	Mat3( value_type m00, value_type m01, value_type m02, value_type m10, value_type m11, value_type m12, value_type m20, value_type m21, value_type m22 )
		:m00( m00 ), m01( m01 ), m02( m02 ), m10( m10 ), m11( m11 ), m12( m12 ), m20( m20 ), m21( m21 ), m22( m22 )
	{

	}

public:
	Mat3 & operator = ( const Mat3 & val )
	{
		m00 = val.m00; m01 = val.m01; m02 = val.m02;
		m10 = val.m10; m11 = val.m11; m12 = val.m12;
		m20 = val.m20; m21 = val.m21; m22 = val.m22;

		return *this;
	}

public:
	value_type * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < 3 );

		return m[val];
	}

	const value_type * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < 3 );

		return m[val];
	}

};

template< typename T > const XE::Mat3< T > XE::Mat3< T >::Zero = {
	0, 0, 0,
	0, 0, 0,
	0, 0 ,0 };
template< typename T > const XE::Mat3< T > XE::Mat3< T >::Identity = {
	1, 0, 0,
	0, 1, 0,
	0, 0, 1 };

using Mat3i = Mat3< XE::int32 >;
using Mat3f = Mat3< XE::float32 >;
using Mat3d = Mat3< XE::float64 >;

DECL_META_CLASS( XE_API, Mat3i );
DECL_META_CLASS( XE_API, Mat3f );
DECL_META_CLASS( XE_API, Mat3d );

END_XE_NAMESPACE

#endif // __MAT3_H__C7739BBA_CC88_446C_9E5E_E8C2684E022E
