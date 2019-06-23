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
			XE::real m00, m01, m02, m03;
			XE::real m10, m11, m12, m13;
			XE::real m20, m21, m22, m23;
			XE::real m30, m31, m32, m33;
		};
		XE::real d[16];
		XE::real m[4][4];
	};

public:
	Mat4();

	Mat4( XE::real m00, XE::real m01, XE::real m02, XE::real m03, XE::real m10, XE::real m11, XE::real m12, XE::real m13, XE::real m20, XE::real m21, XE::real m22, XE::real m23, XE::real m30, XE::real m31, XE::real m32, XE::real m33 );

	Mat4( const Mat3& val );

	Mat4( const Mat4& val );

public:
	Mat4& operator = ( const Mat3& val );

	Mat4& operator = ( const Mat4& val );

public:
	XE::real * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

	const XE::real * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

};
DECL_META_CLASS( MATH_API, Mat4 );

END_XE_NAMESPACE

#endif // __MAT4_H__37122410_1C8D_44A2_9830_6F4B075415DF
