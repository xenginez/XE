#include "Mat4.h"

#include "Mathf.h"

BEG_META( XE::Mat4 )
type->Property( "m00", &Mat4::m00 );
type->Property( "m01", &Mat4::m01 );
type->Property( "m02", &Mat4::m02 );
type->Property( "m03", &Mat4::m03 );
type->Property( "m10", &Mat4::m10 );
type->Property( "m11", &Mat4::m11 );
type->Property( "m12", &Mat4::m12 );
type->Property( "m13", &Mat4::m13 );
type->Property( "m20", &Mat4::m20 );
type->Property( "m21", &Mat4::m21 );
type->Property( "m22", &Mat4::m22 );
type->Property( "m23", &Mat4::m23 );
type->Property( "m30", &Mat4::m30 );
type->Property( "m31", &Mat4::m31 );
type->Property( "m32", &Mat4::m32 );
type->Property( "m33", &Mat4::m33 );
END_META()

const XE::Mat4 XE::Mat4::Zero = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

const XE::Mat4 XE::Mat4::Identity = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

XE::Mat4::Mat4()
	: m00( 0.0f ), m01( 0.0f ), m02( 0.0f ), m03( 0.0f )
	, m10( 0.0f ), m11( 0.0f ), m12( 0.0f ), m13( 0.0f )
	, m20( 0.0f ), m21( 0.0f ), m22( 0.0f ), m23( 0.0f )
	, m30( 0.0f ), m31( 0.0f ), m32( 0.0f ), m33( 0.0f )
{
}

XE::Mat4::Mat4( XE::float32 m00, XE::float32 m01, XE::float32 m02, XE::float32 m03, XE::float32 m10, XE::float32 m11, XE::float32 m12, XE::float32 m13, XE::float32 m20, XE::float32 m21, XE::float32 m22, XE::float32 m23, XE::float32 m30, XE::float32 m31, XE::float32 m32, XE::float32 m33 )
	:m00( m00 ), m01( m01 ), m02( m02 ), m03( m03 )
	, m10( m10 ), m11( m11 ), m12( m12 ), m13( m13 )
	, m20( m20 ), m21( m21 ), m22( m22 ), m23( m23 )
	, m30( m30 ), m31( m31 ), m32( m32 ), m33( m33 )
{

}

XE::Mat4::Mat4( const Mat3& val )
	:m00( val.m00 ), m01( val.m01 ), m02( val.m02 ), m03( 0 )
	, m10( val.m10 ), m11( val.m11 ), m12( val.m12 ), m13( 0 )
	, m20( val.m20 ), m21( val.m21 ), m22( val.m22 ), m23( 0 )
	, m30( 0 ), m31( 0 ), m32( 0 ), m33( 1 )
{

}

XE::Mat4::Mat4( const Mat4& val )
	:m00( val.m00 ), m01( val.m01 ), m02( val.m02 ), m03( val.m03 )
	, m10( val.m10 ), m11( val.m11 ), m12( val.m12 ), m13( val.m13 )
	, m20( val.m20 ), m21( val.m21 ), m22( val.m22 ), m23( val.m23 )
	, m30( val.m30 ), m31( val.m31 ), m32( val.m32 ), m33( val.m33 )
{

}

XE::Mat4& XE::Mat4::operator=( const Mat3& val )
{
	m00 = val.m00; m01 = val.m01; m02 = val.m02; m03 = 0;
	m10 = val.m10; m11 = val.m11; m12 = val.m12; m13 = 0;
	m20 = val.m20; m21 = val.m21; m22 = val.m22; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;

	return *this;
}

XE::Mat4& XE::Mat4::operator=( const Mat4& val )
{
	m00 = val.m00; m01 = val.m01; m02 = val.m02; m03 = val.m03;
	m10 = val.m10; m11 = val.m11; m12 = val.m12; m13 = val.m13;
	m20 = val.m20; m21 = val.m21; m22 = val.m22; m23 = val.m23;
	m30 = val.m30; m31 = val.m31; m32 = val.m32; m33 = val.m33;

	return *this;
}
