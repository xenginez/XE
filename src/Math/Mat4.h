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

class MATH_API Mat4
{
public:
	static const Mat4 Zero;
	static const Mat4 Identity;

public:
	union
	{
		struct
		{
			XE::float32 m00, m01, m02, m03;
			XE::float32 m10, m11, m12, m13;
			XE::float32 m20, m21, m22, m23;
			XE::float32 m30, m31, m32, m33;
		};
		XE::float32 d[16];
		XE::float32 m[4][4];
	};

public:
	Mat4();

	Mat4( XE::float32 m00, XE::float32 m01, XE::float32 m02, XE::float32 m03, XE::float32 m10, XE::float32 m11, XE::float32 m12, XE::float32 m13, XE::float32 m20, XE::float32 m21, XE::float32 m22, XE::float32 m23, XE::float32 m30, XE::float32 m31, XE::float32 m32, XE::float32 m33 );

	Mat4( const Mat3& val );

	Mat4( const Mat4& val );

public:
	Mat4& operator = ( const Mat3& val );

	Mat4& operator = ( const Mat4& val );

public:
	XE::float32 * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

	const XE::float32 * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

};
DECL_META_CLASS( MATH_API, Mat4 );

END_XE_NAMESAPCE

#endif // __MAT4_H__37122410_1C8D_44A2_9830_6F4B075415DF
