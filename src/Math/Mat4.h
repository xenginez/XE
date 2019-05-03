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
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float d[16];
		float m[4][4];
	};

public:
	Mat4();

	Mat4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33 );

	Mat4( const Mat3& val );

	Mat4( const Mat4& val );

public:
	Mat4& operator = ( const Mat3& val );

	Mat4& operator = ( const Mat4& val );

public:
	float * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

	const float * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < 4 );
		return m[val];
	}

};
DECL_META_CLASS( MATH_API, Mat4 );

END_XE_NAMESAPCE

#endif // __MAT4_H__37122410_1C8D_44A2_9830_6F4B075415DF
