#include "Mat3.h"

#include "Mathf.h"

BEG_META( XE::Mat3 )
type->Property( "m00", &Mat3::m00 );
type->Property( "m01", &Mat3::m01 );
type->Property( "m02", &Mat3::m02 );
type->Property( "m10", &Mat3::m10 );
type->Property( "m11", &Mat3::m11 );
type->Property( "m12", &Mat3::m12 );
type->Property( "m20", &Mat3::m20 );
type->Property( "m21", &Mat3::m21 );
type->Property( "m22", &Mat3::m22 );
END_META()


const XE::Mat3 XE::Mat3::Zero = { 0, 0, 0, 0, 0, 0, 0, 0 ,0 };
const XE::Mat3 XE::Mat3::Identity = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

XE::Mat3::Mat3()
	:m00( 1 ), m01( 0 ), m02( 0 ), m10( 0 ), m11( 1 ), m12( 0 ), m20( 0 ), m21( 0 ), m22( 1 )
{
}

XE::Mat3::Mat3( XE::real m00, XE::real m01, XE::real m02, XE::real m10, XE::real m11, XE::real m12, XE::real m20, XE::real m21, XE::real m22 )
	:m00( m00 ), m01( m01 ), m02( m02 ), m10( m10 ), m11( m11 ), m12( m12 ), m20( m20 ), m21( m21 ), m22( m22 )
{

}

XE::Mat3::Mat3( const Quat& val )
{
	XE::real x = val.x * 2.0f;
	XE::real y = val.y * 2.0f;
	XE::real z = val.z * 2.0f;
	XE::real xx = val.x * x;
	XE::real yy = val.y * y;
	XE::real zz = val.z * z;
	XE::real xy = val.x * y;
	XE::real xz = val.x * z;
	XE::real yz = val.y * z;
	XE::real wx = val.w * x;
	XE::real wy = val.w * y;
	XE::real wz = val.w * z;

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

XE::Mat3::Mat3( const Mat3& val )
	: m00( val.m00 ), m01( val.m01 ), m02( val.m02 ), m10( val.m10 ), m11( val.m11 ), m12( val.m12 ), m20( val.m20 ), m21( val.m21 ), m22( val.m22 )
{

}

XE::Mat3::Mat3( const Mat4& val )
{
	m[0][0] = val[0][0];
	m[0][1] = val[0][1];
	m[0][2] = val[0][2];
	m[1][0] = val[1][0];
	m[1][1] = val[1][1];
	m[1][2] = val[1][2];
	m[2][0] = val[2][0];
	m[2][1] = val[2][1];
	m[2][2] = val[2][2];
}

XE::Mat3& XE::Mat3::operator=( const Mat3& val )
{
	m00 = val.m00; m01 = val.m01; m02 = val.m02;
	m10 = val.m10; m11 = val.m11; m12 = val.m12;
	m20 = val.m20; m21 = val.m21; m22 = val.m22;

	return *this;
}
