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

class XE_API alignas( 16 ) Mat3
{
public:
	static const Mat3 Zero;
	static const Mat3 Identity;

public:
	union
	{
		struct
		{
			XE::float32 m00, m01, m02;
			XE::float32 m10, m11, m12;
			XE::float32 m20, m21, m22;
		};
		XE::float32 d[9];
		XE::float32 m[3][3];
	};

public:
	Mat3();

	Mat3( XE::float32 m00, XE::float32 m01, XE::float32 m02, XE::float32 m10, XE::float32 m11, XE::float32 m12, XE::float32 m20, XE::float32 m21, XE::float32 m22 );

	Mat3( const Quat& val );

	Mat3( const Mat3& val );

	Mat3( const Mat4& val );

public:
	Mat3& operator = ( const Mat3& val );

public:
	XE::float32 * operator []( XE::uint64 val )
	{
		XE_ASSERT( val < 3 );
		return m[val];
	}

	const XE::float32 * operator []( XE::uint64 val ) const
	{
		XE_ASSERT( val < 3 );
		return m[val];
	}

};
DECL_META_CLASS( XE_API, Mat3 );

END_XE_NAMESPACE

#endif // __MAT3_H__C7739BBA_CC88_446C_9E5E_E8C2684E022E
