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

class MATH_API Mat3
{
public:
	static const Mat3 Zero;
	static const Mat3 Identity;

public:
	union
	{
		struct
		{
			float m00, m01, m02;
			float m10, m11, m12;
			float m20, m21, m22;
		};
		float d[9];
		float m[3][3];
	};

public:
	Mat3();

	Mat3( float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22 );

	Mat3( const Quat& val );

	Mat3( const Mat3& val );

	Mat3( const Mat4& val );

public:
	Mat3& operator = ( const Mat3& val );

public:
	float * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < 3 );
		return m[val];
	}

	const float * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < 3 );
		return m[val];
	}

};
DECL_META_CLASS( MATH_API, Mat3 );

END_XE_NAMESAPCE

#endif // __MAT3_H__C7739BBA_CC88_446C_9E5E_E8C2684E022E
