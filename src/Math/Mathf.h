/*!
 * \file   Mathf.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MATHF_H__289359AA_D9DE_4269_B0BE_BAAA6E15461B
#define __MATHF_H__289359AA_D9DE_4269_B0BE_BAAA6E15461B

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Quat.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Rect.h"
#include "SIMD.h"

XE::Vec2 operator -( const XE::Vec2 & val );
XE::Vec2 operator +( const XE::Vec2 & left, float right );
XE::Vec2 operator +( float left, const XE::Vec2 & right );
XE::Vec2 operator +( const XE::Vec2 & left, const XE::Vec2 & right );
XE::Vec2 operator -( const XE::Vec2 & left, float right );
XE::Vec2 operator -( float left, const XE::Vec2 & right );
XE::Vec2 operator -( const XE::Vec2 & left, const XE::Vec2 & right );
XE::Vec2 operator *( const XE::Vec2 & left, float right );
XE::Vec2 operator *( float left, const XE::Vec2 & right );
XE::Vec2 operator *( const XE::Vec2 & left, const XE::Vec2 & right );
XE::Vec2 operator /( const XE::Vec2 & left, float right );
XE::Vec2 operator /( float left, const XE::Vec2 & right );
XE::Vec2 operator /( const XE::Vec2 & left, const XE::Vec2 & right );
XE::Vec2 & operator +=( XE::Vec2 & left, float right );
XE::Vec2 & operator +=( XE::Vec2 & left, const XE::Vec2 & right );
XE::Vec2 & operator -=( XE::Vec2 & left, float right );
XE::Vec2 & operator -=( XE::Vec2 & left, const XE::Vec2 & right );
XE::Vec2 & operator *=( XE::Vec2 & left, float right );
XE::Vec2 & operator *=( XE::Vec2 & left, const XE::Vec2 & right );
XE::Vec2 & operator /=( XE::Vec2 & left, float right );
XE::Vec2 & operator /=( XE::Vec2 & left, const XE::Vec2 & right );
bool operator ==( const XE::Vec2 & left, const XE::Vec2 & right );
bool operator !=( const XE::Vec2 & left, const XE::Vec2 & right );

XE::Vec3 operator -( const XE::Vec3 & val );
XE::Vec3 operator +( const XE::Vec3 & left, float right );
XE::Vec3 operator +( float left, const XE::Vec3 & right );
XE::Vec3 operator +( const XE::Vec3 & left, const XE::Vec3 & right );
XE::Vec3 operator -( const XE::Vec3 & left, float right );
XE::Vec3 operator -( float left, const XE::Vec3 & right );
XE::Vec3 operator -( const XE::Vec3 & left, const XE::Vec3 & right );
XE::Vec3 operator *( const XE::Vec3 & left, float right );
XE::Vec3 operator *( float left, const XE::Vec3 & right );
XE::Vec3 operator *( const XE::Vec3 & left, const XE::Vec3 & right );
XE::Vec3 operator /( const XE::Vec3 & left, float right );
XE::Vec3 operator /( float left, const XE::Vec3 & right );
XE::Vec3 operator /( const XE::Vec3 & left, const XE::Vec3 & right );
XE::Vec3 & operator +=( XE::Vec3 & left, float right );
XE::Vec3 & operator +=( XE::Vec3 & left, const XE::Vec3 & right );
XE::Vec3 & operator -=( XE::Vec3 & left, float right );
XE::Vec3 & operator -=( XE::Vec3 & left, const XE::Vec3 & right );
XE::Vec3 & operator *=( XE::Vec3 & left, float right );
XE::Vec3 & operator *=( XE::Vec3 & left, const XE::Vec3 & right );
XE::Vec3 & operator /=( XE::Vec3 & left, float right );
XE::Vec3 & operator /=( XE::Vec3 & left, const XE::Vec3 & right );
bool operator ==( const XE::Vec3 & left, const XE::Vec3 & right );
bool operator !=( const XE::Vec3 & left, const XE::Vec3 & right );

XE::Vec4 operator -( const XE::Vec4 & val );
XE::Vec4 operator +( const XE::Vec4 & left, float right );
XE::Vec4 operator +( float left, const XE::Vec4 & right );
XE::Vec4 operator +( const XE::Vec4 & left, const XE::Vec4 & right );
XE::Vec4 operator -( const XE::Vec4 & left, float right );
XE::Vec4 operator -( float left, const XE::Vec4 & right );
XE::Vec4 operator -( const XE::Vec4 & left, const XE::Vec4 & right );
XE::Vec4 operator *( const XE::Vec4 & left, float right );
XE::Vec4 operator *( float left, const XE::Vec4 & right );
XE::Vec4 operator *( const XE::Vec4 & left, const XE::Vec4 & right );
XE::Vec4 operator /( const XE::Vec4 & left, float right );
XE::Vec4 operator /( float left, const XE::Vec4 & right );
XE::Vec4 operator /( const XE::Vec4 & left, const XE::Vec4 & right );
XE::Vec4 & operator +=( XE::Vec4 & left, float right );
XE::Vec4 & operator +=( XE::Vec4 & left, const XE::Vec4 & right );
XE::Vec4 & operator -=( XE::Vec4 & left, float right );
XE::Vec4 & operator -=( XE::Vec4 & left, const XE::Vec4 & right );
XE::Vec4 & operator *=( XE::Vec4 & left, float right );
XE::Vec4 & operator *=( XE::Vec4 & left, const XE::Vec4 & right );
XE::Vec4 & operator /=( XE::Vec4 & left, float right );
XE::Vec4 & operator /=( XE::Vec4 & left, const XE::Vec4 & right );
bool operator ==( const XE::Vec4 & left, const XE::Vec4 & right );
bool operator !=( const XE::Vec4 & left, const XE::Vec4 & right );

XE::Quat operator -( const XE::Quat & val );
XE::Quat operator +( const XE::Quat & left, float right );
XE::Quat operator +( float left, const XE::Quat & right );
XE::Quat operator +( const XE::Quat & left, const XE::Quat & right );
XE::Quat operator -( const XE::Quat & left, float right );
XE::Quat operator -( float left, const XE::Quat & right );
XE::Quat operator -( const XE::Quat & left, const XE::Quat & right );
XE::Quat operator *( const XE::Quat & left, float right );
XE::Quat operator *( float left, const XE::Quat & right );
XE::Quat operator *( const XE::Quat & left, const XE::Quat & right );
XE::Quat operator /( const XE::Quat & left, float right );
XE::Quat & operator +=( XE::Quat & left, const XE::Quat & right );
XE::Quat & operator -=( XE::Quat & left, const XE::Quat & right );
XE::Quat & operator *=( XE::Quat & left, float right );
XE::Quat & operator *=( XE::Quat & left, const XE::Quat & right );
XE::Quat & operator /=( XE::Quat & left, float right );
bool operator ==( const XE::Quat & left, const XE::Quat & right );
bool operator !=( const XE::Quat & left, const XE::Quat & right );

XE::Mat3 operator -( const XE::Mat3 & val );
XE::Mat3 operator +( const XE::Mat3 & left, const XE::Mat3 & right );
XE::Mat3 operator -( const XE::Mat3 & left, const XE::Mat3 & right );
XE::Mat3 operator *( const XE::Mat3 & left, float right );
XE::Mat3 operator *( float left, const XE::Mat3 & right );
XE::Vec3 operator *( const XE::Mat3 & left, const XE::Vec3& right );
XE::Vec3 operator *( const XE::Vec3& left, const XE::Mat3 & right );
XE::Mat3 operator *( const XE::Mat3 & left, const XE::Mat3 & right );
XE::Mat3 & operator +=( XE::Mat3 & left, const XE::Mat3 & right );
XE::Mat3 & operator -=( XE::Mat3 & left, const XE::Mat3 & right );
XE::Mat3 & operator *=( XE::Mat3 & left, float right );
XE::Mat3 & operator *=( XE::Mat3 & left, const XE::Mat3 & right );
bool operator ==( const XE::Mat3 & left, const XE::Mat3 & right );
bool operator !=( const XE::Mat3 & left, const XE::Mat3 & right );

XE::Mat4 operator -( const XE::Mat4 & val );
XE::Mat4 operator +( const XE::Mat4 & left, const XE::Mat4 & right );
XE::Mat4 operator -( const XE::Mat4 & left, const XE::Mat4 & right );
XE::Vec3 operator *( const XE::Mat4 & left, const XE::Vec3& right );
XE::Vec4 operator *( const XE::Mat4 & left, const XE::Vec4& right );
XE::Mat4 operator *( const XE::Mat4 & left, const XE::Mat4 & right );
XE::Mat4 & operator +=( XE::Mat4 & left, const XE::Mat4 & right );
XE::Mat4 & operator -=( XE::Mat4 & left, const XE::Mat4 & right );
XE::Mat4 & operator *=( XE::Mat4 & left, const XE::Mat4 & right );
bool operator ==( const XE::Mat4 & left, const XE::Mat4 & right );
bool operator !=( const XE::Mat4 & left, const XE::Mat4 & right );

BEG_XE_NAMESPACE

class MATH_API Mathf
{
public:
	static const float Pi;
	static const float Pi2;
	static const float Pi4;
	static const float Nan;
	static const float Epsilon;
	static const float Infinity;

public:
	static inline float Abs( float r )
	{
		return std::abs( r );
	}

	static inline float Cos( float theta )
	{
		return std::cos( theta );
	}

	static inline float ACos( float theta )
	{
		return std::acos( theta );
	}

	static inline float Rcp( float r )
	{
		return 1.f / r;
	}

	static inline float RSqrt( float r )
	{
		return 1.f / std::sqrt( r );
	}

	static inline float Sin( float theta )
	{
		return std::sin( theta );
	}

	static inline float ASin( float theta )
	{
		return std::asin( theta );
	}

	static inline float Log( float x )
	{
		return std::logf( x );
	}

	static inline void SinCos( float u, float& s, float& c )
	{
		s = Sin( u );
		c = Cos( u );
	}

	static inline float Tan( float theta )
	{
		return std::tan( theta );
	}

	static inline float ATan( float t )
	{
		return std::atan( t );
	}

	static inline float ATan2( float t1, float t2 )
	{
		return std::atan2( t1, t2 );
	}

	static inline float Sqrt( float r )
	{
		return std::sqrt( r );
	}

	static inline float Mod( float x, float y )
	{
		return std::fmod( x, y );
	}

	static inline float Pow( float x, float y )
	{
		return std::pow( x, y );
	}

	static inline float Clamp( float v, float a, float b )
	{
		return Min( b, Max( a, v ) );
	}

	static inline float ClampMove( float a, float b, float v )
	{
		return  ( b - a ) > 0.0f ? a + Min( ( b - a ), v ) : a - Min( -( b - a ), v );
	}

	static inline float Cond( bool c, float a, float b )
	{
		return c ? a : b;
	}

	static inline float Cubic( float a, float b, float c, float d, float u )
	{
		const float ab = Lerp( a, b, u );
		const float bc = Lerp( b, c, u );
		const float cd = Lerp( c, d, u );
		const float abc = Lerp( ab, bc, u );
		const float bcd = Lerp( bc, cd, u );
		return Lerp( abc, bcd, u );
	}

	static inline float Max( float a, float b )
	{
		return Cond( a > b, a, b );
	}

	static inline float Min( float a, float b )
	{
		return Cond( a < b, a, b );
	}

	static inline float Sgn( float r )
	{
		return Cond( r >= 0.f, 1.f, -1.f );
	}

	static inline float Sign( float r )
	{
		return Cond( r > 0, 1.f, Cond( r < 0, -1.f, 0.f ) );
	}

	static inline float Saturate( float r )
	{
		return Clamp( r, 0.f, 1.f );
	}

	static inline float Degrees( float rad )
	{
		return rad * 57.295779513f;
	}

	static inline float Radians( float deg )
	{
		return deg * 0.0174532925f;
	}

	static inline float Lerp( float a, float b, float x )
	{
		return a + x * ( b - a );
	}

	static inline float SmoothStep( float min, float max, float x )
	{
		x = Clamp( x, min, max );
		return -2.f * Pow( ( x - min ) / ( max - min ), 3.f ) + 3.f * Pow( ( x - min ) / ( max - min ), 2.f );
	}

	static inline float SmoothPulse( float minmin, float minmax, float maxmin, float maxmax, float x )
	{
		return SmoothStep( minmin, minmax, x ) - SmoothStep( maxmin, maxmax, x );
	}

	static inline float Unrollangle( float angleRef, float angle )
	{
		// todo:
		float i = 1;
		float f = Mod( ( angleRef - angle ) / ( 2.f * Pi ), i );
		return angle + ( ( i + ( Abs( f ) > 0.5f ? Sgn( f ) * 1 : 0 ) ) * 2.f * Pi );
	}

	static inline float HalfTan( float a )
	{
		float x = ( 0.5f * Abs( a ) + Pi2 );
		return Tan( Clamp( Sign( a )*( x - Pi2 ), -Pi2 + Epsilon, Pi2 - Epsilon ) );
	}

	static inline bool Equal( float a, float b, float e = Epsilon )
	{
		return Abs( a - b ) < e;
	}

public:
	static inline float Length( const Vec2& val )
	{
		return Sqrt( val.x * val.x + val.y * val.y );
	}

	static inline float SqrLength( const Vec2& val )
	{
		return ( val.x * val.x + val.y * val.y );
	}

	static inline float Distance( const Vec2& left, const Vec2& right )
	{
		return Length( left - right );
	}

	static inline float SqrDistance( const Vec2& left, const Vec2& right )
	{
		return SqrLength( left - right );
	}

	static inline float Dot( const Vec2& left, const Vec2& right )
	{
		return left.x * right.x + left.y * right.y;
	}

	static inline Vec2 Normalize( const Vec2& val )
	{
		Vec2 ret;

		float len = Length( val );

		if ( len > Epsilon )
		{
			float invLen = 1.0f / len;
			ret.x *= invLen;
			ret.y *= invLen;
		}

		return ret;
	}

	static inline float Corss( const Vec2& left, const Vec2& right )
	{
		return left.x * right.y - left.y * right.x;
	}

	static inline Vec2 Floor( const Vec2& left, const Vec2& right )
	{
		return Min( left, right );
	}

	static inline Vec2 Ceil( const Vec2& left, const Vec2& right )
	{
		return Max( left, right );
	}

	static inline Vec2 Reflect( const Vec2& left, const Vec2& right )
	{
		return  left - ( 2 * Dot( left, right ) * right );
	}

	static inline void OrthoNormalize( Vec2& left, Vec2& right )
	{
		left = Normalize( left );
		float dot = Dot( left, right );
		right -= left * dot;
		right = Normalize( right );
	}

	static inline bool IsNAN( const Vec2& val )
	{
		return val.x == Nan || val.y == Nan;
	}

	static inline Vec2 Min( const Vec2& left, const Vec2& right )
	{
		return { Min( left.x, right.x ), Min( left.y, right.y ) };
	}

	static inline Vec2 Max( const Vec2& left, const Vec2& right )
	{
		return { Max( left.x, right.x ), Max( left.y, right.y ) };
	}

public:
	static inline float Length( const Vec3& val )
	{
		return Sqrt( val.x * val.x + val.y * val.y + val.z * val.z );
	}

	static inline float SqrLength( const Vec3& val )
	{
		return ( val.x * val.x + val.y * val.y + val.z * val.z );
	}

	static inline float Distance( const Vec3& left, const Vec3& right )
	{
		return Length( left - right );
	}

	static inline float SqrDistance( const Vec3& left, const Vec3& right )
	{
		return SqrLength( left - right );
	}

	static inline float Dot( const Vec3& left, const Vec3& right )
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	static inline Vec3 Normalize( const Vec3& val )
	{
		Vec3 ret;

		float len = Length( val );
		if ( len > 1e-08f )
		{
			float invLen = 1.0f / len;
			ret.x *= invLen;
			ret.y *= invLen;
			ret.z *= invLen;
		}
		return ret;
	}

	static inline Vec3 Cross( const Vec3& left, const Vec3& right )
	{
		return {
			left.y * right.z - left.z * right.y,
			left.z * right.x - left.x * right.z,
			left.x * right.y - left.y * right.x
		};
	}

	static inline Vec3 Reflect( const Vec3& left, const Vec3& right )
	{
		return left - ( 2 * Dot( left, right ) * right );
	}

	static inline void OrthoNormalize( Vec3& a, Vec3& b, Vec3& c )
	{
		a = Normalize( a );

		float dot0 = Dot( a, b );
		b -= dot0 * a;
		b = Normalize( b );

		float dot1 = Dot( b, c );
		dot0 = Dot( a, c );
		c -= dot0 * a + dot1 * b;
		c = Normalize( c );
	}

	static inline bool IsNAN( const Vec3& val )
	{
		return val.x == Nan || val.y == Nan || val.z == Nan;
	}

	static inline Vec3 Min( const Vec3& left, const Vec3& right )
	{
		return { Min( left.x, right.x ), Min( left.y, right.y ), Min( left.z, right.z ) };
	}

	static inline Vec3 Max( const Vec3& left, const Vec3& right )
	{
		return { Max( left.x, right.x ), Max( left.y, right.y ), Max( left.z, right.z ) };
	}

	static inline Vec3 Lerp( const Vec3& left, const Vec3& right, float t )
	{
		return ( 1.0f - t ) * left + t * right;
	}

public:
	static inline float Dot( const Vec4& left, const Vec4& right )
	{
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	static inline bool IsNAN( const Vec4& val )
	{
		return val.x == Nan || val.y == Nan || val.z == Nan || val.w == Nan;
	}

public:
	static inline Quat QuatFromMat( const Mat3& mat )
	{
		Quat val;

		float trace = mat[0][0] + mat[1][1] + mat[2][2];
		float root;

		if ( trace > 0.0f )
		{
			root = Sqrt( trace + 1.0f );
			val.w = 0.5f*root;
			root = 0.5f / root;
			val.x = ( mat[2][1] - mat[1][2] )*root;
			val.y = ( mat[0][2] - mat[2][0] )*root;
			val.z = ( mat[1][0] - mat[0][1] )*root;
		}
		else
		{
			static uint32 nextLookup[3] = { 1, 2, 0 };
			uint32 i = 0;

			if ( mat[1][1] > mat[0][0] )
				i = 1;

			if ( mat[2][2] > mat[i][i] )
				i = 2;

			uint32 j = nextLookup[i];
			uint32 k = nextLookup[j];

			root = Sqrt( mat[i][i] - mat[j][j] - mat[k][k] + 1.0f );

			float* cmpntLookup[3] = { &val.x, &val.y, &val.z };
			*cmpntLookup[i] = 0.5f*root;
			root = 0.5f / root;

			val.w = ( mat[k][j] - mat[j][k] )*root;
			*cmpntLookup[j] = ( mat[j][i] + mat[i][j] )*root;
			*cmpntLookup[k] = ( mat[k][i] + mat[i][k] )*root;
		}

		float len = val.w * val.w + val.x * val.x + val.y * val.y + val.z * val.z;
		float factor = 1.0f / Sqrt( len );
		val = val * factor;

		return val;
	}

	static inline Quat QuatFromAxisAngle( const Vec3& axis, float angle )
	{
		Quat val;

		float halfAngle( 0.5f * angle );
		float sin = Sin( halfAngle );

		val.w = Cos( halfAngle );
		val.x = sin * axis.x;
		val.y = sin * axis.y;
		val.z = sin * axis.z;

		return val;
	}

	static inline Quat QuatFromAxes( const Vec3& x, const Vec3& y, const Vec3& z )
	{
		Mat3 mat;

		mat[0][0] = x.x;
		mat[1][0] = x.y;
		mat[2][0] = x.z;

		mat[0][1] = y.x;
		mat[1][1] = y.y;
		mat[2][1] = y.z;

		mat[0][2] = z.x;
		mat[1][2] = z.y;
		mat[2][2] = z.z;

		return QuatFromMat( mat );
	}

	static inline Quat QuatFromEuler( const Vec3& euler )
	{
		float halfXAngle = euler.x * 0.5f;
		float halfYAngle = euler.y * 0.5f;
		float halfZAngle = euler.z * 0.5f;

		float cx = Cos( halfXAngle );
		float sx = Sin( halfXAngle );

		float cy = Cos( halfYAngle );
		float sy = Sin( halfYAngle );

		float cz = Cos( halfZAngle );
		float sz = Sin( halfZAngle );

		Quat quatX( sx, 0.0f, 0.0f, cx );
		Quat quatY( 0.0f, sy, 0.0f, cy );
		Quat quatZ( 0.0f, 0.0f, sz, cz );

		return ( quatZ * quatX ) * quatY;
	}

	static inline void QuatToMatrix( const Quat& val, Mat3& mat )
	{
		float tx = val.x + val.x;
		float ty = val.y + val.y;
		float fTz = val.z + val.z;
		float twx = tx * val.w;
		float twy = ty * val.w;
		float twz = fTz * val.w;
		float txx = tx * val.x;
		float txy = ty * val.x;
		float txz = fTz * val.x;
		float tyy = ty * val.y;
		float tyz = fTz * val.y;
		float tzz = fTz * val.z;

		mat[0][0] = 1.0f - ( tyy + tzz );
		mat[0][1] = txy - twz;
		mat[0][2] = txz + twy;
		mat[1][0] = txy + twz;
		mat[1][1] = 1.0f - ( txx + tzz );
		mat[1][2] = tyz - twx;
		mat[2][0] = txz - twy;
		mat[2][1] = tyz + twx;
		mat[2][2] = 1.0f - ( txx + tyy );
	}

	static inline void QuatToAxisAngle( const Quat& val, Vec3& axis, float& angle )
	{
		float sqrLength = val.x * val.x + val.y * val.y + val.z * val.z;
		if ( sqrLength > 0.0f )
		{
			angle = 2.0f * ACos( val.w );
			float invLength = 1.0f / Sqrt( sqrLength );
			axis.x = val.x * invLength;
			axis.y = val.y * invLength;
			axis.z = val.z * invLength;
		}
		else
		{
			angle = 0.0f;
			axis.x = 1.0f;
			axis.y = 0.0f;
			axis.z = 0.0f;
		}
	}

	static inline void QuatToAxes( const Quat& val, Vec3& x, Vec3& y, Vec3& z )
	{
		Mat3 mat;
		QuatToMatrix( val, mat );

		x.x = mat[0][0];
		x.y = mat[1][0];
		x.z = mat[2][0];

		y.x = mat[0][1];
		y.y = mat[1][1];
		y.z = mat[2][1];

		z.x = mat[0][2];
		z.y = mat[1][2];
		z.z = mat[2][2];
	}

	static inline void QuatToEuler( const Quat& val, Vec3& euler )
	{
		Mat3 mat;
		QuatToMatrix( val, mat );
		MatToEuler( mat, euler );
	}

	static inline Vec3 XAxis( const Quat& val )
	{
		float fTy = 2.0f*val.y;
		float fTz = 2.0f*val.z;
		float fTwy = fTy * val.w;
		float fTwz = fTz * val.w;
		float fTxy = fTy * val.x;
		float fTxz = fTz * val.x;
		float fTyy = fTy * val.y;
		float fTzz = fTz * val.z;

		return { 1.0f - ( fTyy + fTzz ), fTxy + fTwz, fTxz - fTwy };
	}

	static inline Vec3 YAxis( const Quat& val )
	{
		float fTx = 2.0f * val.x;
		float fTy = 2.0f * val.y;
		float fTz = 2.0f * val.z;
		float fTwx = fTx * val.w;
		float fTwz = fTz * val.w;
		float fTxx = fTx * val.x;
		float fTxy = fTy * val.x;
		float fTyz = fTz * val.y;
		float fTzz = fTz * val.z;

		return { fTxy - fTwz, 1.0f - ( fTxx + fTzz ), fTyz + fTwx };
	}

	static inline Vec3 ZAxis( const Quat& val )
	{
		float fTx = 2.0f * val.x;
		float fTy = 2.0f * val.y;
		float fTz = 2.0f * val.z;
		float fTwx = fTx * val.w;
		float fTwy = fTy * val.w;
		float fTxx = fTx * val.x;
		float fTxz = fTz * val.x;
		float fTyy = fTy * val.y;
		float fTyz = fTz * val.y;

		return { fTxz + fTwy, fTyz - fTwx, 1.0f - ( fTxx + fTyy ) };
	}

	static inline float Dot( const Quat& left, const Quat& right )
	{
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	static inline Quat Normalize( const Quat& val )
	{
		float len = val.w * val.w + val.x * val.x + val.y * val.y + val.z * val.z;
		float factor = 1.0f / Sqrt( len );
		return val * factor;
	}

	static inline Quat Inverse( const Quat& val )
	{
		float fNorm = val.w * val.w + val.x * val.x + val.y * val.y + val.z * val.z;
		if ( fNorm > 0.0f )
		{
			float fInvNorm = 1.0f / fNorm;
			return { -val.x * fInvNorm, -val.y * fInvNorm, -val.z * fInvNorm, val.w * fInvNorm };
		}

		return Quat::Zero;
	}

	static inline Vec3 Rotate( const Quat& val, const Vec3& v )
	{
		Mat3 rot;
		QuatToMatrix( val, rot );
		return rot * v;
	}

	static inline Quat LookAt( const Quat& val, const Vec3& forward )
	{
		if ( forward == Vec3::Zero )
			return val;

		Vec3 nrmForwardDir = Normalize( forward );
		Vec3 currentForwardDir = -ZAxis( val );

		if ( SqrLength( nrmForwardDir + currentForwardDir ) < 0.00005f )
		{
			return { -val.z, val.w, val.x, -val.y };
		}

		return RotationFromTo( val, currentForwardDir, nrmForwardDir ) * val;
	}

	static inline Quat LookAt( const Quat& val, const Vec3& forward, const Vec3& up )
	{
		if ( Abs( 1.0f - Dot( forward, up ) ) <= Epsilon )
		{
			return LookAt( val, forward );
		}

		Vec3 x = Cross( forward, up );
		Vec3 y = Cross( x, forward );

		x = Normalize( x );
		y = Normalize( y );

		return QuatFromAxes( x, y, -forward );
	}

	static inline bool IsNAN( const Quat& val )
	{
		return val.x == Nan || val.y == Nan || val.z == Nan || val.w == Nan;
	}

	static inline Quat Lerp( const Quat& left, const Quat& right, float t )
	{
		float d = Dot( left, right );
		float flip = d >= 0.0f ? 1.0f : -1.0f;
		return Normalize( flip * ( 1.0f - t ) * left + t * right );
	}

	static inline Quat Slerp( const Quat& left, const Quat& right, float t )
	{
		float cos = Dot( left, right );
		Quat ret;

		if ( cos < 0.0f && Epsilon )
		{
			cos = -cos;
			ret = -right;
		}
		else
		{
			ret = right;
		}

		if ( Abs( cos ) < 1 - Epsilon )
		{
			float sin = Sqrt( 1 - cos * cos );
			float angle = ATan2( sin, cos );
			float invSin = 1.0f / sin;
			float coeff0 = Sin( ( 1.0f - t ) * angle ) * invSin;
			float coeff1 = Sin( t * angle ) * invSin;
			return coeff0 * left + coeff1 * ret;
		}

		return Normalize( ( 1.0f - t ) * left + t * ret );
	}

	static inline Quat RotationFromTo( const Quat& val, const Vec3& from, const Vec3& dest )
	{// Based on Stan Melax's article in Game Programming Gems
		Quat q;

		Vec3 v0 = from;
		Vec3 v1 = dest;
		v0 = Normalize( v0 );
		v1 = Normalize( v1 );

		float d = Dot( v0, v1 );

		// If dot == 1, vectors are the same
		if ( d >= 1.0f )
			return Quat::Identity;

		if ( d < ( 1e-6f - 1.0f ) )
		{
			// Generate an axis
			Vec3 axis = Cross( Vec3( 1, 0, 0 ), from );
			if ( Length( axis ) < ( 1e-06f * 1e-06f ) ) // Pick another if colinear
				axis = Cross( Vec3( 0, 1, 0 ), from );
			axis = Normalize( axis );
			return QuatFromAxisAngle( axis, Pi );
		}

		float s = Sqrt( ( 1 + d ) * 2 );
		float invs = 1 / s;

		Vec3 c = Cross( v0, v1 );

		q.x = c.x * invs;
		q.y = c.y * invs;
		q.z = c.z * invs;
		q.w = s * 0.5f;
		return Normalize( q );
	}

	static inline Quat Min( const Quat& left, const Quat& right )
	{
		return { Min( left.x, right.x ), Min( left.y, right.y ), Min( left.z, right.z ), Min( left.w, right.w ) };
	}

	static inline Quat Max( const Quat& left, const Quat& right )
	{
		return { Max( left.x, right.x ), Max( left.y, right.y ), Max( left.z, right.z ), Max( left.w, right.w ) };
	}

public:
	static inline Mat3 MatFromQuat( const Quat& q )
	{
		Mat3 m;
		QuatToMatrix( q, m );
		return m;
	}

	static inline Mat3 MatFromAxisAngle( const Vec3& axis, float angle )
	{
		Mat3 m;
		float cos = Cos( angle );
		float sin = Sin( angle );
		float oneMinusCos = 1.0f - cos;
		float x2 = axis.x*axis.x;
		float y2 = axis.y*axis.y;
		float z2 = axis.z*axis.z;
		float xym = axis.x*axis.y*oneMinusCos;
		float xzm = axis.x*axis.z*oneMinusCos;
		float yzm = axis.y*axis.z*oneMinusCos;
		float xSin = axis.x*sin;
		float ySin = axis.y*sin;
		float zSin = axis.z*sin;

		m[0][0] = x2 * oneMinusCos + cos;
		m[0][1] = xym - zSin;
		m[0][2] = xzm + ySin;
		m[1][0] = xym + zSin;
		m[1][1] = y2 * oneMinusCos + cos;
		m[1][2] = yzm - xSin;
		m[2][0] = xzm - ySin;
		m[2][1] = yzm + xSin;
		m[2][2] = z2 * oneMinusCos + cos;

		return m;
	}

	static inline Mat3 MatFromEuler( const Vec3& euler )
	{
		Mat3 m;

		float cx = Cos( euler.x );
		float sx = Sin( euler.x );
		float cy = Cos( euler.y );
		float sy = Sin( euler.y );
		float cz = Cos( euler.z );
		float sz = Sin( euler.z );

		m[0][0] = cy * cz + sx * sy * sz;
		m[0][1] = cz * sx * sy - cy * sz;
		m[0][2] = cx * sy;

		m[1][0] = cx * sz;
		m[1][1] = cx * cz;
		m[1][2] = -sx;

		m[2][0] = -cz * sy + cy * sx * sz;
		m[2][1] = cy * cz * sx + sy * sz;
		m[2][2] = cx * cy;

		return m;
	}

	static inline void MatToQuat( const Mat3& val, Quat& q )
	{
		q = QuatFromMat( val );
	}

	static inline void MatToAxisAngle( const Mat3& val, Vec3& axis, float& angle )
	{
		float trace = val[0][0] + val[1][1] + val[2][2];
		float cos = 0.5f*( trace - 1.0f );
		angle = ACos( cos );

		if ( angle > 0.0f )
		{
			if ( angle < Pi )
			{
				axis.x = val[2][1] - val[1][2];
				axis.y = val[0][2] - val[2][0];
				axis.z = val[1][0] - val[0][1];
				axis = Normalize( axis );
			}
			else
			{
				float fHalfInverse;
				if ( val[0][0] >= val[1][1] )
				{
					if ( val[0][0] >= val[2][2] )
					{
						axis.x = 0.5f * Sqrt( val[0][0] - val[1][1] - val[2][2] + 1.0f );
						fHalfInverse = 0.5f / axis.x;
						axis.y = fHalfInverse * val[0][1];
						axis.z = fHalfInverse * val[0][2];
					}
					else
					{
						axis.z = 0.5f * Sqrt( val[2][2] - val[0][0] - val[1][1] + 1.0f );
						fHalfInverse = 0.5f / axis.z;
						axis.x = fHalfInverse * val[0][2];
						axis.y = fHalfInverse * val[1][2];
					}
				}
				else
				{
					if ( val[1][1] >= val[2][2] )
					{
						axis.y = 0.5f * Sqrt( val[1][1] - val[0][0] - val[2][2] + 1.0f );
						fHalfInverse = 0.5f / axis.y;
						axis.x = fHalfInverse * val[0][1];
						axis.z = fHalfInverse * val[1][2];
					}
					else
					{
						axis.z = 0.5f * Sqrt( val[2][2] - val[0][0] - val[1][1] + 1.0f );
						fHalfInverse = 0.5f / axis.z;
						axis.x = fHalfInverse * val[0][2];
						axis.y = fHalfInverse * val[1][2];
					}
				}
			}
		}
		else
		{
			axis.x = 1.0f;
			axis.y = 0.0f;
			axis.z = 0.0f;
		}
	}

	static inline void MatToEuler( const Mat3& val, Vec3& euler )
	{
		euler.x = -ASin( val[1][2] );

		if ( euler.x < Pi2 )
		{
			if ( euler.x > -Pi2 )
			{
				euler.y = ATan2( val[0][2], val[2][2] );
				euler.z = ATan2( val[1][0], val[1][1] );
			}
			else
			{
				euler.x = -Pi2;
				euler.y = ATan2( -val[0][1], val[0][0] );
				euler.z = 0.0f;
			}
		}

		euler.x = Pi2;
		euler.y = ATan2( val[0][1], val[0][0] );
		euler.z = 0.0f;
	}

	static inline Mat3 Transpose( const Mat3 & val )
	{
		Mat3 ret;
		for ( uint32 row = 0; row < 3; row++ )
		{
			for ( uint32 col = 0; col < 3; col++ )
				ret[row][col] = val[col][row];
		}
		return ret;
	}

	static inline Mat3 Inverse( const Mat3 & val )
	{
		Mat3 ret;

		ret[0][0] = val[1][1] * val[2][2] - val[1][2] * val[2][1];
		ret[0][1] = val[0][2] * val[2][1] - val[0][1] * val[2][2];
		ret[0][2] = val[0][1] * val[1][2] - val[0][2] * val[1][1];
		ret[1][0] = val[1][2] * val[2][0] - val[1][0] * val[2][2];
		ret[1][1] = val[0][0] * val[2][2] - val[0][2] * val[2][0];
		ret[1][2] = val[0][2] * val[1][0] - val[0][0] * val[1][2];
		ret[2][0] = val[1][0] * val[2][1] - val[1][1] * val[2][0];
		ret[2][1] = val[0][1] * val[2][0] - val[0][0] * val[2][1];
		ret[2][2] = val[0][0] * val[1][1] - val[0][1] * val[1][0];

		float det = val[0][0] * ret[0][0] + val[0][1] * ret[1][0] + val[0][2] * ret[2][0];

		if ( Abs( det ) <= Epsilon )
			return Mat3::Identity;

		float invDet = 1.0f / det;
		for ( uint32 row = 0; row < 3; row++ )
		{
			for ( uint32 col = 0; col < 3; col++ )
				ret[row][col] *= invDet;
		}

		return ret;
	}

	static inline float Determinant( const Mat3 & val )
	{
		float cofactor00 = val[1][1] * val[2][2] - val[1][2] * val[2][1];
		float cofactor10 = val[1][2] * val[2][0] - val[1][0] * val[2][2];
		float cofactor20 = val[1][0] * val[2][1] - val[1][1] * val[2][0];

		float det = val[0][0] * cofactor00 + val[0][1] * cofactor10 + val[0][2] * cofactor20;

		return det;
	}

	static inline Mat3 OrthoNormalize( const Mat3 & val )
	{
		Mat3 m = val;
		// Compute q0
		float invLength = RSqrt( m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0] );

		m[0][0] *= invLength;
		m[1][0] *= invLength;
		m[2][0] *= invLength;

		// Compute q1
		float dot0 = m[0][0] * m[0][1] + m[1][0] * m[1][1] + m[2][0] * m[2][1];

		m[0][1] -= dot0 * m[0][0];
		m[1][1] -= dot0 * m[1][0];
		m[2][1] -= dot0 * m[2][0];

		invLength = RSqrt( m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1] );

		m[0][1] *= invLength;
		m[1][1] *= invLength;
		m[2][1] *= invLength;

		// Compute q2
		float dot1 = m[0][1] * m[0][2] + m[1][1] * m[1][2] + m[2][1] * m[2][2];
		dot0 = m[0][0] * m[0][2] + m[1][0] * m[1][2] + m[2][0] * m[2][2];

		m[0][2] -= dot0 * m[0][0] + dot1 * m[0][1];
		m[1][2] -= dot0 * m[1][0] + dot1 * m[1][1];
		m[2][2] -= dot0 * m[2][0] + dot1 * m[2][1];

		invLength = RSqrt( m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2] );

		m[0][2] *= invLength;
		m[1][2] *= invLength;
		m[2][2] *= invLength;

		return m;
	}

public:
	static inline Mat4 Transpose( const Mat4 & m )
	{
		return { m[0][0], m[1][0], m[2][0], m[3][0],
						m[0][1], m[1][1], m[2][1], m[3][1],
						m[0][2], m[1][2], m[2][2], m[3][2],
						m[0][3], m[1][3], m[2][3], m[3][3] };
	}

	static inline Mat4 Inverse( const Mat4 & m )
	{
		float m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
		float m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
		float m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
		float m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

		float v0 = m20 * m31 - m21 * m30;
		float v1 = m20 * m32 - m22 * m30;
		float v2 = m20 * m33 - m23 * m30;
		float v3 = m21 * m32 - m22 * m31;
		float v4 = m21 * m33 - m23 * m31;
		float v5 = m22 * m33 - m23 * m32;

		float t00 = +( v5 * m11 - v4 * m12 + v3 * m13 );
		float t10 = -( v5 * m10 - v2 * m12 + v1 * m13 );
		float t20 = +( v4 * m10 - v2 * m11 + v0 * m13 );
		float t30 = -( v3 * m10 - v1 * m11 + v0 * m12 );

		float invDet = 1 / ( t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03 );

		float d00 = t00 * invDet;
		float d10 = t10 * invDet;
		float d20 = t20 * invDet;
		float d30 = t30 * invDet;

		float d01 = -( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
		float d11 = +( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
		float d21 = -( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
		float d31 = +( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		float d02 = +( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
		float d12 = -( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
		float d22 = +( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
		float d32 = -( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		float d03 = -( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
		float d13 = +( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
		float d23 = -( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
		float d33 = +( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

		return {
			d00, d01, d02, d03,
			d10, d11, d12, d13,
			d20, d21, d22, d23,
			d30, d31, d32, d33 };
	}

	static inline float MINOR( const Mat4& m, const uint32 r0, const uint32 r1, const uint32 r2, const uint32 c0, const uint32 c1, const uint32 c2 )
	{
		return m[r0][c0] * ( m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2] ) -
			m[r0][c1] * ( m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2] ) +
			m[r0][c2] * ( m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1] );
	};

	static inline Mat4 Adjoint( const Mat4 & m )
	{
		return {
			MINOR( m, 1, 2, 3, 1, 2, 3 ),
			-MINOR( m, 0, 2, 3, 1, 2, 3 ),
			MINOR( m, 0, 1, 3, 1, 2, 3 ),
			-MINOR( m, 0, 1, 2, 1, 2, 3 ),

			-MINOR( m, 1, 2, 3, 0, 2, 3 ),
			MINOR( m, 0, 2, 3, 0, 2, 3 ),
			-MINOR( m, 0, 1, 3, 0, 2, 3 ),
			MINOR( m, 0, 1, 2, 0, 2, 3 ),

			MINOR( m, 1, 2, 3, 0, 1, 3 ),
			-MINOR( m, 0, 2, 3, 0, 1, 3 ),
			MINOR( m, 0, 1, 3, 0, 1, 3 ),
			-MINOR( m, 0, 1, 2, 0, 1, 3 ),

			-MINOR( m, 1, 2, 3, 0, 1, 2 ),
			MINOR( m, 0, 2, 3, 0, 1, 2 ),
			-MINOR( m, 0, 1, 3, 0, 1, 2 ),
			MINOR( m, 0, 1, 2, 0, 1, 2 )
		};
	}

	static inline float Determinant( const Mat4 & m )
	{
		return m[0][0] * MINOR( m, 1, 2, 3, 1, 2, 3 ) -
			m[0][1] * MINOR( m, 1, 2, 3, 0, 2, 3 ) +
			m[0][2] * MINOR( m, 1, 2, 3, 0, 1, 3 ) -
			m[0][3] * MINOR( m, 1, 2, 3, 0, 1, 2 );
	}

	static inline float Determinant3( const Mat4 & m )
	{
		float cofactor00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		float cofactor10 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
		float cofactor20 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

		float det = m[0][0] * cofactor00 + m[0][1] * cofactor10 + m[0][2] * cofactor20;

		return det;
	}

	static inline Mat4 Translation( const Vec3 & val )
	{
		return {
				1.0f, 0.0f, 0.0f, val.x,
				0.0f, 1.0f, 0.0f, val.y,
				0.0f, 0.0f, 1.0f, val.z,
				0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	static inline Vec3 Translation( const Mat4& m )
	{
		return { m[0][3], m[1][3], m[2][3] };
	}

	static inline Mat4 Rotation( const Quat & val )
	{
		return { MatFromQuat( val ) };
	}

	static inline Mat4 Scale( const Vec3 & val )
	{
		return {
			val.x, 0.0f,  0.0f,  0.0f,
			0.0f,  val.y, 0.0f,  0.0f,
			0.0f,  0.0f,  val.z, 0.0f,
			0.0f,  0.0f,  0.0f,  1.0f
		};
	}

	static inline Mat4 Scale( float val )
	{
		return {
			val,  0.0f, 0.0f, 0.0f,
			0.0f, val,  0.0f, 0.0f,
			0.0f, 0.0f, val,  0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	static inline Mat4 ProjectionPerspective( float fov, float aspect, float near, float far )
	{// Note: Duplicate code in Camera, bring it all here eventually
		static constexpr float INFINITE_FAR_PLANE_ADJUST = 0.00001f;

		float thetaX = fov * 0.5f;
		float tanThetaX = Tan( thetaX );
		float tanThetaY = tanThetaX / aspect;

		float half_w = tanThetaX * near;
		float half_h = tanThetaY * near;

		float left = -half_w;
		float right = half_w;
		float bottom = -half_h;
		float top = half_h;

		float inv_w = 1 / ( right - left );
		float inv_h = 1 / ( top - bottom );
		float inv_d = 1 / ( far - near );

		float A = 2 * near * inv_w;
		float B = 2 * near * inv_h;
		float C = ( right + left ) * inv_w;
		float D = ( top + bottom ) * inv_h;
		float q, qn;
		float sign = -1.0f;

		if ( far == 0 )
		{
			// Infinite far plane
			q = INFINITE_FAR_PLANE_ADJUST - 1;
			qn = near * ( INFINITE_FAR_PLANE_ADJUST - 2 );
		}
		else
		{
			q = sign * ( far + near ) * inv_d;
			qn = -2.0f * ( far * near ) * inv_d;
		}

		return {
		A,		0.0f,	C,		0.0f,
		0.0f,	B,		D,		0.0f,
		0.0f,	0.0f,	q,		qn,
		0.0f,	0.0f,	sign,	0.0f
		};
	}

	static inline Mat4 ProjectionOrthographic( float left, float right, float top, float bottom, float near, float far )
	{
		Mat4 m;

		float deltaX = right - left;
		float deltaY = bottom - top;
		float deltaZ = far - near;

		m[0][0] = 2.0F / deltaX;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;
		m[0][3] = -( right + left ) / deltaX;

		m[1][0] = 0.0f;
		m[1][1] = -2.0F / deltaY;
		m[1][2] = 0.0f;
		m[1][3] = ( top + bottom ) / deltaY;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;

		if ( far == 0.0f )
		{
			m[2][2] = 1.0f;
			m[2][3] = 0.0f;
		}
		else
		{
			m[2][2] = -2.0F / deltaZ;
			m[2][3] = -( far + near ) / deltaZ;
		}

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;

		return m;
	}

	static inline Mat4 View( const Vec3& position, const Quat & orientition )
	{
		Mat4 m;

		Mat3 rot = MatFromQuat( orientition );

		Mat3 rotT = Transpose( rot );
		Vec3 trans = ( -rotT ) * ( position );

		m = rotT;
		m[0][3] = trans.x;
		m[1][3] = trans.y;
		m[2][3] = trans.z;

		return m;
	}

	static inline Mat4 TRS( const Vec3 & translation, const Quat& rotation, const Vec3& scale )
	{
		Mat4 m;
		Mat3 rot3x3 = MatFromQuat( rotation );

		m[0][0] = scale.x * rot3x3[0][0]; m[0][1] = scale.y * rot3x3[0][1]; m[0][2] = scale.z * rot3x3[0][2]; m[0][3] = translation.x;
		m[1][0] = scale.x * rot3x3[1][0]; m[1][1] = scale.y * rot3x3[1][1]; m[1][2] = scale.z * rot3x3[1][2]; m[1][3] = translation.y;
		m[2][0] = scale.x * rot3x3[2][0]; m[2][1] = scale.y * rot3x3[2][1]; m[2][2] = scale.z * rot3x3[2][2]; m[2][3] = translation.z;

		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;

		return m;
	}

	static inline void TRS( const Mat4& m, Vec3 & position, Quat& rotation, Vec3& scale )
	{
		Mat3 m3x3( m );

		Mat3 matQ;
		Vec3 vecU;

		float invLength = RSqrt( m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0] );
		matQ[0][0] = m[0][0] * invLength;
		matQ[1][0] = m[1][0] * invLength;
		matQ[2][0] = m[2][0] * invLength;

		float dot = matQ[0][0] * m[0][1] + matQ[1][0] * m[1][1] + matQ[2][0] * m[2][1];
		matQ[0][1] = m[0][1] - dot * matQ[0][0];
		matQ[1][1] = m[1][1] - dot * matQ[1][0];
		matQ[2][1] = m[2][1] - dot * matQ[2][0];

		invLength = RSqrt( matQ[0][1] * matQ[0][1] + matQ[1][1] * matQ[1][1] + matQ[2][1] * matQ[2][1] );
		matQ[0][1] *= invLength;
		matQ[1][1] *= invLength;
		matQ[2][1] *= invLength;

		dot = matQ[0][0] * m[0][2] + matQ[1][0] * m[1][2] + matQ[2][0] * m[2][2];
		matQ[0][2] = m[0][2] - dot * matQ[0][0];
		matQ[1][2] = m[1][2] - dot * matQ[1][0];
		matQ[2][2] = m[2][2] - dot * matQ[2][0];

		dot = matQ[0][1] * m[0][2] + matQ[1][1] * m[1][2] + matQ[2][1] * m[2][2];
		matQ[0][2] -= dot * matQ[0][1];
		matQ[1][2] -= dot * matQ[1][1];
		matQ[2][2] -= dot * matQ[2][1];

		invLength = RSqrt( matQ[0][2] * matQ[0][2] + matQ[1][2] * matQ[1][2] + matQ[2][2] * matQ[2][2] );
		matQ[0][2] *= invLength;
		matQ[1][2] *= invLength;
		matQ[2][2] *= invLength;

		float fDet = matQ[0][0] * matQ[1][1] * matQ[2][2] + matQ[0][1] * matQ[1][2] * matQ[2][0] +
			matQ[0][2] * matQ[1][0] * matQ[2][1] - matQ[0][2] * matQ[1][1] * matQ[2][0] -
			matQ[0][1] * matQ[1][0] * matQ[2][2] - matQ[0][0] * matQ[1][2] * matQ[2][1];

		if ( fDet < 0.0f )
		{
			for ( uint32 row = 0; row < 3; row++ )
				for ( uint32 col = 0; col < 3; col++ )
					matQ[row][col] = -matQ[row][col];
		}

		Mat3 matRight;
		matRight[0][0] = matQ[0][0] * m[0][0] + matQ[1][0] * m[1][0] +
			matQ[2][0] * m[2][0];
		matRight[0][1] = matQ[0][0] * m[0][1] + matQ[1][0] * m[1][1] +
			matQ[2][0] * m[2][1];
		matRight[1][1] = matQ[0][1] * m[0][1] + matQ[1][1] * m[1][1] +
			matQ[2][1] * m[2][1];
		matRight[0][2] = matQ[0][0] * m[0][2] + matQ[1][0] * m[1][2] +
			matQ[2][0] * m[2][2];
		matRight[1][2] = matQ[0][1] * m[0][2] + matQ[1][1] * m[1][2] +
			matQ[2][1] * m[2][2];
		matRight[2][2] = matQ[0][2] * m[0][2] + matQ[1][2] * m[1][2] +
			matQ[2][2] * m[2][2];

		scale[0] = matRight[0][0];
		scale[1] = matRight[1][1];
		scale[2] = matRight[2][2];

		float invD0 = 1.0f / scale[0];
		vecU[0] = matRight[0][1] * invD0;
		vecU[1] = matRight[0][2] * invD0;
		vecU[2] = matRight[1][2] / scale[1];

		rotation = QuatFromMat( matQ );
		position = Vec3( m[0][3], m[1][3], m[2][3] );
	}

	static inline Mat4 InverseTRS( const Vec3 & translation, const Quat& rotation, const Vec3& scale )
	{
		Mat4 m;

		// Invert the parameters
		Vec3 invTranslate = -translation;
		Vec3 invScale( 1 / scale.x, 1 / scale.y, 1 / scale.z );
		Quat invRot = Inverse( rotation );

		// Because we're inverting, order is translation, rotation, scale
		// So make translation relative to scale & rotation
		invTranslate = Rotate( invRot, invTranslate );
		invTranslate *= invScale;

		// Next, make a 3x3 rotation matrix
		Mat3 rot3x3 = MatFromQuat( invRot );

		// Set up final matrix with scale, rotation and translation
		m[0][0] = invScale.x * rot3x3[0][0]; m[0][1] = invScale.x * rot3x3[0][1]; m[0][2] = invScale.x * rot3x3[0][2]; m[0][3] = invTranslate.x;
		m[1][0] = invScale.y * rot3x3[1][0]; m[1][1] = invScale.y * rot3x3[1][1]; m[1][2] = invScale.y * rot3x3[1][2]; m[1][3] = invTranslate.y;
		m[2][0] = invScale.z * rot3x3[2][0]; m[2][1] = invScale.z * rot3x3[2][1]; m[2][2] = invScale.z * rot3x3[2][2]; m[2][3] = invTranslate.z;

		// No projection term
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;

		return m;
	}

	static inline Vec3 MultiplyAffine( const Mat4& m, const Vec3 & v )
	{
		return {
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] };
	}

	static inline Vec3 MultiplyDirection( const Mat4& m, const Vec3 & v )
	{
		return {
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z };
	}

};
DECL_META_CLASS( MATH_API, Mathf );

END_XE_NAMESAPCE


inline XE::Vec2 operator -( const XE::Vec2 & val )
{
	return { -val.x, -val.y };
}
inline XE::Vec2 operator +( const XE::Vec2 & left, float right )
{
	return { left.x + right, left.y + right };
}
inline XE::Vec2 operator +( float left, const XE::Vec2 & right )
{
	return { left + right.x, left + right.y };
}
inline XE::Vec2 operator +( const XE::Vec2 & left, const XE::Vec2 & right )
{
	return { left.x + right.x, left.y + right.y };
}
inline XE::Vec2 operator -( const XE::Vec2 & left, float right )
{
	return { left.x - right, left.y + right };
}
inline XE::Vec2 operator -( float left, const XE::Vec2 & right )
{
	return { left + right.x, left + right.y };
}
inline XE::Vec2 operator -( const XE::Vec2 & left, const XE::Vec2 & right )
{
	return { left.x + right.x, left.y + right.y };
}
inline XE::Vec2 operator *( const XE::Vec2 & left, float right )
{
	return { left.x * right, left.y * right };
}
inline XE::Vec2 operator *( float left, const XE::Vec2 & right )
{
	return { left * right.x, left * right.y };
}
inline XE::Vec2 operator *( const XE::Vec2 & left, const XE::Vec2 & right )
{
	return { left.x * right.x, left.y * right.y };
}
inline XE::Vec2 operator /( const XE::Vec2 & left, float right )
{
	return { left.x / right, left.y / right };
}
inline XE::Vec2 operator /( float left, const XE::Vec2 & right )
{
	return { left / right.x, left / right.y };
}
inline XE::Vec2 operator /( const XE::Vec2 & left, const XE::Vec2 & right )
{
	return { left.x / right.x,left.y / right.y };
}
inline XE::Vec2 & operator +=( XE::Vec2 & left, float right )
{
	left.x += right;
	left.y += right;
	return left;
}
inline XE::Vec2 & operator +=( XE::Vec2 & left, const XE::Vec2 & right )
{
	left.x += right.x;
	left.y += right.y;
	return left;
}
inline XE::Vec2 & operator -=( XE::Vec2 & left, float right )
{
	left.x -= right;
	left.y -= right;
	return left;
}
inline XE::Vec2 & operator -=( XE::Vec2 & left, const XE::Vec2 & right )
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}
inline XE::Vec2 & operator *=( XE::Vec2 & left, float right )
{
	left.x *= right;
	left.y *= right;
	return left;
}
inline XE::Vec2 & operator *=( XE::Vec2 & left, const XE::Vec2 & right )
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}
inline XE::Vec2 & operator /=( XE::Vec2 & left, float right )
{
	left.x /= right;
	left.y /= right;
	return left;
}
inline XE::Vec2 & operator /=( XE::Vec2 & left, const XE::Vec2 & right )
{
	left.x /= right.x;
	left.y /= right.y;
	return left;
}
inline bool operator ==( const XE::Vec2 & left, const XE::Vec2 & right )
{
	return left.x == right.x && left.y == right.y;
}
inline bool operator !=( const XE::Vec2 & left, const XE::Vec2 & right )
{
	return left.x != right.x || left.y != right.y;
}

inline XE::Vec3 operator -( const XE::Vec3 & val )
{
	return { -val.x, -val.y, -val.z };
}
inline XE::Vec3 operator +( const XE::Vec3 & left, float right )
{
	return { left.x + right, left.y + right, left.z + right };
}
inline XE::Vec3 operator +( float left, const XE::Vec3 & right )
{
	return { left + right.x, left + right.y, +left + right.z };
}
inline XE::Vec3 operator +( const XE::Vec3 & left, const XE::Vec3 & right )
{
	return { left.x + right.x, left.y + right.y, left.z + right.z };
}
inline XE::Vec3 operator -( const XE::Vec3 & left, float right )
{
	return { left.x - right, left.y - right, left.z - right };
}
inline XE::Vec3 operator -( float left, const XE::Vec3 & right )
{
	return { left - right.x, left - right.y, left - right.z };
}
inline XE::Vec3 operator -( const XE::Vec3 & left, const XE::Vec3 & right )
{
	return { left.x - right.x, left.y - right.y, left.z - right.z };
}
inline XE::Vec3 operator *( const XE::Vec3 & left, float right )
{
	return { left.x * right, left.y * right, left.z * right };
}
inline XE::Vec3 operator *( float left, const XE::Vec3 & right )
{
	return { left * right.x, left * right.y, left * right.z };
}
inline XE::Vec3 operator *( const XE::Vec3 & left, const XE::Vec3 & right )
{
	return { left.x * right.x, left.y * right.y, left.z * right.z };
}
inline XE::Vec3 operator /( const XE::Vec3 & left, float right )
{
	return { left.x / right, left.y / right, left.z / right };
}
inline XE::Vec3 operator /( float left, const XE::Vec3 & right )
{
	return { left / right.x, left / right.y, left / right.z };
}
inline XE::Vec3 operator /( const XE::Vec3 & left, const XE::Vec3 & right )
{
	return { left.x / right.x, left.y / right.y, left.z / right.z };
}
inline XE::Vec3 & operator +=( XE::Vec3 & left, float right )
{
	left.x += right;
	left.y += right;
	left.z += right;
	return left;
}
inline XE::Vec3 & operator +=( XE::Vec3 & left, const XE::Vec3 & right )
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}
inline XE::Vec3 & operator -=( XE::Vec3 & left, float right )
{
	left.x -= right;
	left.y -= right;
	left.z -= right;
	return left;
}
inline XE::Vec3 & operator -=( XE::Vec3 & left, const XE::Vec3 & right )
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}
inline XE::Vec3 & operator *=( XE::Vec3 & left, float right )
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}
inline XE::Vec3 & operator *=( XE::Vec3 & left, const XE::Vec3 & right )
{
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	return left;
}
inline XE::Vec3 & operator /=( XE::Vec3 & left, float right )
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}
inline XE::Vec3 & operator /=( XE::Vec3 & left, const XE::Vec3 & right )
{
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	return left;
}
inline bool operator ==( const XE::Vec3 & left, const XE::Vec3 & right )
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}
inline bool operator !=( const XE::Vec3 & left, const XE::Vec3 & right )
{
	return left.x != right.x || left.y != right.y || left.z != right.z;
}

inline XE::Vec4 operator -( const XE::Vec4 & val )
{
	return { -val.x, -val.y, -val.z, -val.w };
}
inline XE::Vec4 operator +( const XE::Vec4 & left, float right )
{
	return { left.x + right, left.y + right, left.z + right, left.w + right };
}
inline XE::Vec4 operator +( float left, const XE::Vec4 & right )
{
	return { left + right.x, left + right.y, left + right.z, left + right.w };
}
inline XE::Vec4 operator +( const XE::Vec4 & left, const XE::Vec4 & right )
{
	return { left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
}
inline XE::Vec4 operator -( const XE::Vec4 & left, float right )
{
	return { left.x - right, left.y - right, left.z - right, left.w - right };
}
inline XE::Vec4 operator -( float left, const XE::Vec4 & right )
{
	return { left - right.x, left - right.y, left - right.z, left - right.w };
}
inline XE::Vec4 operator -( const XE::Vec4 & left, const XE::Vec4 & right )
{
	return { left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
}
inline XE::Vec4 operator *( const XE::Vec4 & left, float right )
{
	return { left.x * right, left.y * right, left.z * right, left.w * right };
}
inline XE::Vec4 operator *( float left, const XE::Vec4 & right )
{
	return { left * right.x, left * right.y, left * right.z, left * right.w };
}
inline XE::Vec4 operator *( const XE::Vec4 & left, const XE::Vec4 & right )
{
	return { left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w };
}
inline XE::Vec4 operator /( const XE::Vec4 & left, float right )
{
	return { left.x / right, left.y / right, left.z / right, left.w / right };
}
inline XE::Vec4 operator /( float left, const XE::Vec4 & right )
{
	return { left / right.x, left / right.y, left / right.z, left / right.w };
}
inline XE::Vec4 operator /( const XE::Vec4 & left, const XE::Vec4 & right )
{
	return { left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w };
}
inline XE::Vec4 & operator +=( XE::Vec4 & left, float right )
{
	left.x += right;
	left.y += right;
	left.z += right;
	left.w += right;
	return left;
}
inline XE::Vec4 & operator +=( XE::Vec4 & left, const XE::Vec4 & right )
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	left.w += right.w;
	return left;
}
inline XE::Vec4 & operator -=( XE::Vec4 & left, float right )
{
	left.x -= right;
	left.y -= right;
	left.z -= right;
	left.w -= right;
	return left;
}
inline XE::Vec4 & operator -=( XE::Vec4 & left, const XE::Vec4 & right )
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	left.w -= right.w;
	return left;
}
inline XE::Vec4 & operator *=( XE::Vec4 & left, float right )
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}
inline XE::Vec4 & operator *=( XE::Vec4 & left, const XE::Vec4 & right )
{
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	left.w *= right.w;
	return left;
}
inline XE::Vec4 & operator /=( XE::Vec4 & left, float right )
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	left.w /= right;
	return left;
}
inline XE::Vec4 & operator /=( XE::Vec4 & left, const XE::Vec4 & right )
{
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	left.w /= right.w;
	return left;
}
inline bool operator ==( const XE::Vec4 & left, const XE::Vec4 & right )
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}
inline bool operator !=( const XE::Vec4 & left, const XE::Vec4 & right )
{
	return left.x != right.x || left.y != right.y || left.z != right.z || left.w == right.w;
}

inline XE::Quat operator -( const XE::Quat & val )
{
	return { -val.x, -val.y, -val.z, val.w };
}
inline XE::Quat operator +( const XE::Quat & left, float right )
{
	return { left.x + right, left.y + right, left.z + right, left.w + right };
}
inline XE::Quat operator +( float left, const XE::Quat & right )
{
	return { left + right.x, left + right.y, left + right.z, left + right.w };
}
inline XE::Quat operator +( const XE::Quat & left, const XE::Quat & right )
{
	return { left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
}
inline XE::Quat operator -( const XE::Quat & left, float right )
{
	return { left.x - right, left.y - right, left.z - right, left.w - right };
}
inline XE::Quat operator -( float left, const XE::Quat & right )
{
	return { left - right.x, left - right.y, left - right.z, left - right.w };
}
inline XE::Quat operator -( const XE::Quat & left, const XE::Quat & right )
{
	return { left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
}
inline XE::Quat operator *( const XE::Quat & left, float right )
{
	return { left.x * right, left.y * right, left.z * right, left.w * right };
}
inline XE::Quat operator *( float left, const XE::Quat & right )
{
	return { left * right.x, left * right.y, left * right.z, left * right.w };
}
inline XE::Quat operator *( const XE::Quat & left, const XE::Quat & right )
{
	return {
		left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
		left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z,
		left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x,
		left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z
	};
}
inline XE::Quat operator /( const XE::Quat & left, float right )
{
	float inv = 1.0f / right;
	return { left.x * inv, left.y * inv, left.z * inv, left.w * inv };
}
inline XE::Quat & operator +=( XE::Quat & left, float right )
{
	left.x += right;
	left.y += right;
	left.z += right;
	left.w += right;
	return left;
}
inline XE::Quat & operator +=( XE::Quat & left, const XE::Quat & right )
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	left.w += right.w;
	return left;
}
inline XE::Quat & operator -=( XE::Quat & left, float right )
{
	left.x -= right;
	left.y -= right;
	left.z -= right;
	left.w -= right;
	return left;
}
inline XE::Quat & operator -=( XE::Quat & left, const XE::Quat & right )
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	left.w -= right.w;
	return left;
}
inline XE::Quat & operator *=( XE::Quat & left, float right )
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}
inline XE::Quat & operator *=( XE::Quat & left, const XE::Quat & right )
{
	left.x = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
	left.y = left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y;
	left.z = left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z;
	left.w = left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x;
	return left;
}
inline XE::Quat & operator /=( XE::Quat & left, float right )
{
	float inv = 1.0f / right;
	left.x *= inv;
	left.y *= inv;
	left.z *= inv;
	left.w *= inv;
	return left;
}
inline bool operator ==( const XE::Quat & left, const XE::Quat & right )
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}
inline bool operator !=( const XE::Quat & left, const XE::Quat & right )
{
	return left.x != right.x || left.y != right.y || left.z != right.z || left.w == right.w;
}

inline XE::Mat3 operator -( const XE::Mat3 & val )
{
	return {
		-val[0][0], -val[0][1], -val[0][2],
		-val[1][0], -val[1][1], -val[1][2],
		-val[2][0], -val[2][1], -val[2][2]
	};
}
inline XE::Mat3 operator +( const XE::Mat3 & left, const XE::Mat3 & right )
{
	return {
		left[0][0] + right[0][0], left[0][1] + right[0][1], left[0][2] + right[0][2],
		left[1][0] + right[1][0], left[1][1] + right[1][1], left[1][2] + right[1][2],
		left[2][0] + right[2][0], left[2][1] + right[2][1], left[2][2] + right[2][2]
	};
}
inline XE::Mat3 operator -( const XE::Mat3 & left, const XE::Mat3 & right )
{
	return {
		left[0][0] - right[0][0], left[0][1] - right[0][1], left[0][2] - right[0][2],
		left[1][0] - right[1][0], left[1][1] - right[1][1], left[1][2] - right[1][2],
		left[2][0] - right[2][0], left[2][1] - right[2][1], left[2][2] - right[2][2]
	};
}
inline XE::Mat3 operator *( const XE::Mat3 & left, float right )
{
	return {
		left[0][0] * right, left[0][1] * right, left[0][2] * right,
		left[1][0] * right, left[1][1] * right, left[1][2] * right,
		left[2][0] * right, left[2][1] * right, left[2][2] * right
	};
}
inline XE::Mat3 operator *( float left, const XE::Mat3 & right )
{
	return {
		left * right[0][0], left * right[0][1], left *right[0][2],
		left * right[1][0], left * right[1][1], left *right[1][2],
		left * right[2][0], left * right[2][1], left *right[2][2]
	};
}
inline XE::Vec3 operator *( const XE::Mat3 & left, const XE::Vec3& right )
{
	return {
		left[0][0] * right[0] + left[0][1] * right[1] + left[0][2] * right[2],
		left[1][0] * right[0] + left[1][1] * right[1] + left[1][2] * right[2],
		left[2][0] * right[0] + left[2][1] * right[1] + left[2][2] * right[2]
	};
}
inline XE::Vec3 operator *( const XE::Vec3& left, const XE::Mat3 & right )
{
	return {
		right[0][0] * left[0] + right[0][1] * left[1] + right[0][2] * left[2],
		right[1][0] * left[0] + right[1][1] * left[1] + right[1][2] * left[2],
		right[2][0] * left[0] + right[2][1] * left[1] + right[2][2] * left[2]
	};
}
inline XE::Mat3 operator *( const XE::Mat3 & left, const XE::Mat3 & right )
{
	return {
		left[0][0] * right[0][0] + left[0][1] * right[1][0] + left[0][2] * right[2][0],
		left[0][0] * right[0][1] + left[0][1] * right[1][1] + left[0][2] * right[2][1],
		left[0][0] * right[0][2] + left[0][1] * right[1][2] + left[0][2] * right[2][2],
		left[1][0] * right[0][0] + left[1][1] * right[1][0] + left[1][2] * right[2][0],
		left[1][0] * right[0][1] + left[1][1] * right[1][1] + left[1][2] * right[2][1],
		left[1][0] * right[0][2] + left[1][1] * right[1][2] + left[1][2] * right[2][2],
		left[2][0] * right[0][0] + left[2][1] * right[1][0] + left[2][2] * right[2][0],
		left[2][0] * right[0][1] + left[2][1] * right[1][1] + left[2][2] * right[2][1],
		left[2][0] * right[0][2] + left[2][1] * right[1][2] + left[2][2] * right[2][2]
	};
}
inline XE::Mat3 & operator +=( XE::Mat3 & left, const XE::Mat3 & right )
{
	left[0][0] += right[0][0];
	left[0][1] += right[0][1];
	left[0][2] += right[0][2];
	left[1][0] += right[1][0];
	left[1][1] += right[1][1];
	left[1][2] += right[1][2];
	left[2][0] += right[2][0];
	left[2][1] += right[2][1];
	left[2][2] += right[2][2];
	return left;
}
inline XE::Mat3 & operator -=( XE::Mat3 & left, const XE::Mat3 & right )
{
	left[0][0] -= right[0][0];
	left[0][1] -= right[0][1];
	left[0][2] -= right[0][2];
	left[1][0] -= right[1][0];
	left[1][1] -= right[1][1];
	left[1][2] -= right[1][2];
	left[2][0] -= right[2][0];
	left[2][1] -= right[2][1];
	left[2][2] -= right[2][2];
	return left;
}
inline XE::Mat3 & operator *=( XE::Mat3 & left, float right )
{
	left[0][0] *= right;
	left[0][1] *= right;
	left[0][2] *= right;
	left[1][0] *= right;
	left[1][1] *= right;
	left[1][2] *= right;
	left[2][0] *= right;
	left[2][1] *= right;
	left[2][2] *= right;
	return left;
}
inline XE::Mat3 & operator *=( XE::Mat3 & left, const XE::Mat3 & right )
{
	left[0][0] *= right[0][0] + left[0][1] * right[1][0] + left[0][2] * right[2][0];
	left[0][0] *= right[0][1] + left[0][1] * right[1][1] + left[0][2] * right[2][1];
	left[0][0] *= right[0][2] + left[0][1] * right[1][2] + left[0][2] * right[2][2];
	left[1][0] *= right[0][0] + left[1][1] * right[1][0] + left[1][2] * right[2][0];
	left[1][0] *= right[0][1] + left[1][1] * right[1][1] + left[1][2] * right[2][1];
	left[1][0] *= right[0][2] + left[1][1] * right[1][2] + left[1][2] * right[2][2];
	left[2][0] *= right[0][0] + left[2][1] * right[1][0] + left[2][2] * right[2][0];
	left[2][0] *= right[0][1] + left[2][1] * right[1][1] + left[2][2] * right[2][1];
	left[2][0] *= right[0][2] + left[2][1] * right[1][2] + left[2][2] * right[2][2];
	return left;
}
inline bool operator ==( const XE::Mat3 & left, const XE::Mat3 & right )
{
	return
		left[0][0] == right[0][0] && left[0][1] == right[0][1] && left[0][2] == right[0][2] &&
		left[1][0] == right[1][0] && left[1][1] == right[1][1] && left[1][2] == right[1][2] &&
		left[2][0] == right[2][0] && left[2][1] == right[2][1] && left[2][2] == right[2][2];
}
inline bool operator !=( const XE::Mat3 & left, const XE::Mat3 & right )
{
	return
		left[0][0] != right[0][0] || left[0][1] != right[0][1] || left[0][2] != right[0][2] ||
		left[1][0] != right[1][0] || left[1][1] != right[1][1] || left[1][2] != right[1][2] ||
		left[2][0] != right[2][0] || left[2][1] != right[2][1] || left[2][2] != right[2][2];
}

inline XE::Mat4 operator -( const XE::Mat4 & val )
{
	return {
		   -val[0][0], -val[0][1], -val[0][2], -val[0][3],
		   -val[1][0], -val[1][1], -val[1][2], -val[1][3],
		   -val[2][0], -val[2][1], -val[2][2], -val[2][3],
		   -val[3][0], -val[3][1], -val[3][2], -val[3][3]
	};
}
inline XE::Mat4 operator +( const XE::Mat4 & left, const XE::Mat4 & right )
{
	return {
	left[0][0] + right[0][0], left[0][1] + right[0][1], left[0][2] + right[0][2], left[0][3] + right[0][3],
	left[1][0] + right[1][0], left[1][1] + right[1][1], left[1][2] + right[1][2], left[1][3] + right[1][3],
	left[2][0] + right[2][0], left[2][1] + right[2][1], left[2][2] + right[2][2], left[2][3] + right[2][3],
	left[3][0] + right[3][0], left[3][1] + right[3][1], left[3][2] + right[3][2], left[3][3] + right[3][3]
	};
}
inline XE::Mat4 operator -( const XE::Mat4 & left, const XE::Mat4 & right )
{
	return {
	   left[0][0] - right[0][0], left[0][1] - right[0][1], left[0][2] - right[0][2], left[0][3] - right[0][3],
	   left[1][0] - right[1][0], left[1][1] - right[1][1], left[1][2] - right[1][2], left[1][3] - right[1][3],
	   left[2][0] - right[2][0], left[2][1] - right[2][1], left[2][2] - right[2][2], left[2][3] - right[2][3],
	   left[3][0] - right[3][0], left[3][1] - right[3][1], left[3][2] - right[3][2], left[3][3] - right[3][3]
	};
}
inline XE::Vec3 operator *( const XE::Mat4 & left, const XE::Vec3& right )
{
	float inv = 1.0f / ( left[3][0] * right.x + left[3][1] * right.y + left[3][2] * right.z + left[3][3] );
	return {
	 ( left[0][0] * right.x + left[0][1] * right.y + left[0][2] * right.z + left[0][3] ) * inv,
	 ( left[1][0] * right.x + left[1][1] * right.y + left[1][2] * right.z + left[1][3] ) * inv,
	 ( left[2][0] * right.x + left[2][1] * right.y + left[2][2] * right.z + left[2][3] ) * inv
	};
}
inline XE::Vec4 operator *( const XE::Mat4 & left, const XE::Vec4& right )
{
	return {
		left[0][0] * right.x + left[0][1] * right.y + left[0][2] * right.z + left[0][3] * right.w,
		left[1][0] * right.x + left[1][1] * right.y + left[1][2] * right.z + left[1][3] * right.w,
		left[2][0] * right.x + left[2][1] * right.y + left[2][2] * right.z + left[2][3] * right.w,
		left[3][0] * right.x + left[3][1] * right.y + left[3][2] * right.z + left[3][3] * right.w
	};
}
inline XE::Mat4 operator *( const XE::Mat4 & left, const XE::Mat4 & right )
{
	return {
	left[0][0] * right[0][0] + left[0][1] * right[1][0] + left[0][2] * right[2][0] + left[0][3] * right[3][0],
	left[0][0] * right[0][1] + left[0][1] * right[1][1] + left[0][2] * right[2][1] + left[0][3] * right[3][1],
	left[0][0] * right[0][2] + left[0][1] * right[1][2] + left[0][2] * right[2][2] + left[0][3] * right[3][2],
	left[0][0] * right[0][3] + left[0][1] * right[1][3] + left[0][2] * right[2][3] + left[0][3] * right[3][3],
	left[1][0] * right[0][0] + left[1][1] * right[1][0] + left[1][2] * right[2][0] + left[1][3] * right[3][0],
	left[1][0] * right[0][1] + left[1][1] * right[1][1] + left[1][2] * right[2][1] + left[1][3] * right[3][1],
	left[1][0] * right[0][2] + left[1][1] * right[1][2] + left[1][2] * right[2][2] + left[1][3] * right[3][2],
	left[1][0] * right[0][3] + left[1][1] * right[1][3] + left[1][2] * right[2][3] + left[1][3] * right[3][3],
	left[2][0] * right[0][0] + left[2][1] * right[1][0] + left[2][2] * right[2][0] + left[2][3] * right[3][0],
	left[2][0] * right[0][1] + left[2][1] * right[1][1] + left[2][2] * right[2][1] + left[2][3] * right[3][1],
	left[2][0] * right[0][2] + left[2][1] * right[1][2] + left[2][2] * right[2][2] + left[2][3] * right[3][2],
	left[2][0] * right[0][3] + left[2][1] * right[1][3] + left[2][2] * right[2][3] + left[2][3] * right[3][3],
	left[3][0] * right[0][0] + left[3][1] * right[1][0] + left[3][2] * right[2][0] + left[3][3] * right[3][0],
	left[3][0] * right[0][1] + left[3][1] * right[1][1] + left[3][2] * right[2][1] + left[3][3] * right[3][1],
	left[3][0] * right[0][2] + left[3][1] * right[1][2] + left[3][2] * right[2][2] + left[3][3] * right[3][2],
	left[3][0] * right[0][3] + left[3][1] * right[1][3] + left[3][2] * right[2][3] + left[3][3] * right[3][3]
	};
}
inline XE::Mat4 & operator +=( XE::Mat4 & left, const XE::Mat4 & right )
{
	left[0][0] += right[0][0]; left[0][1] += right[0][1]; left[0][2] += right[0][2]; left[0][3] += right[0][3];
	left[1][0] += right[1][0]; left[1][1] += right[1][1]; left[1][2] += right[1][2]; left[1][3] += right[1][3];
	left[2][0] += right[2][0]; left[2][1] += right[2][1]; left[2][2] += right[2][2]; left[2][3] += right[2][3];
	left[3][0] += right[3][0]; left[3][1] += right[3][1]; left[3][2] += right[3][2]; left[3][3] += right[3][3];
	return left;
}
inline XE::Mat4 & operator -=( XE::Mat4 & left, const XE::Mat4 & right )
{
	left[0][0] -= right[0][0]; left[0][1] -= right[0][1]; left[0][2] -= right[0][2]; left[0][3] -= right[0][3];
	left[1][0] -= right[1][0]; left[1][1] -= right[1][1]; left[1][2] -= right[1][2]; left[1][3] -= right[1][3];
	left[2][0] -= right[2][0]; left[2][1] -= right[2][1]; left[2][2] -= right[2][2]; left[2][3] -= right[2][3];
	left[3][0] -= right[3][0]; left[3][1] -= right[3][1]; left[3][2] -= right[3][2]; left[3][3] -= right[3][3];
	return left;
}
inline XE::Mat4 & operator *=( XE::Mat4 & left, const XE::Mat4 & right )
{
	left[0][0] = left[0][0] * right[0][0] + left[0][1] * right[1][0] + left[0][2] * right[2][0] + left[0][3] * right[3][0];
	left[0][1] = left[0][0] * right[0][1] + left[0][1] * right[1][1] + left[0][2] * right[2][1] + left[0][3] * right[3][1];
	left[0][2] = left[0][0] * right[0][2] + left[0][1] * right[1][2] + left[0][2] * right[2][2] + left[0][3] * right[3][2];
	left[0][3] = left[0][0] * right[0][3] + left[0][1] * right[1][3] + left[0][2] * right[2][3] + left[0][3] * right[3][3];
	left[1][0] = left[1][0] * right[0][0] + left[1][1] * right[1][0] + left[1][2] * right[2][0] + left[1][3] * right[3][0];
	left[1][1] = left[1][0] * right[0][1] + left[1][1] * right[1][1] + left[1][2] * right[2][1] + left[1][3] * right[3][1];
	left[1][2] = left[1][0] * right[0][2] + left[1][1] * right[1][2] + left[1][2] * right[2][2] + left[1][3] * right[3][2];
	left[1][3] = left[1][0] * right[0][3] + left[1][1] * right[1][3] + left[1][2] * right[2][3] + left[1][3] * right[3][3];
	left[2][0] = left[2][0] * right[0][0] + left[2][1] * right[1][0] + left[2][2] * right[2][0] + left[2][3] * right[3][0];
	left[2][1] = left[2][0] * right[0][1] + left[2][1] * right[1][1] + left[2][2] * right[2][1] + left[2][3] * right[3][1];
	left[2][2] = left[2][0] * right[0][2] + left[2][1] * right[1][2] + left[2][2] * right[2][2] + left[2][3] * right[3][2];
	left[2][3] = left[2][0] * right[0][3] + left[2][1] * right[1][3] + left[2][2] * right[2][3] + left[2][3] * right[3][3];
	left[3][0] = left[3][0] * right[0][0] + left[3][1] * right[1][0] + left[3][2] * right[2][0] + left[3][3] * right[3][0];
	left[3][1] = left[3][0] * right[0][1] + left[3][1] * right[1][1] + left[3][2] * right[2][1] + left[3][3] * right[3][1];
	left[3][2] = left[3][0] * right[0][2] + left[3][1] * right[1][2] + left[3][2] * right[2][2] + left[3][3] * right[3][2];
	left[3][3] = left[3][0] * right[0][3] + left[3][1] * right[1][3] + left[3][2] * right[2][3] + left[3][3] * right[3][3];
	return left;
}
inline bool operator ==( const XE::Mat4 & left, const XE::Mat4 & right )
{
	return
		left[0][0] == right[0][0] && left[0][1] == right[0][1] && left[0][2] == right[0][2] && left[0][3] == right[0][3] &&
		left[1][0] == right[1][0] && left[1][1] == right[1][1] && left[1][2] == right[1][2] && left[1][3] == right[1][3] &&
		left[2][0] == right[2][0] && left[2][1] == right[2][1] && left[2][2] == right[2][2] && left[2][3] == right[2][3] &&
		left[3][0] == right[3][0] && left[3][1] == right[3][1] && left[3][2] == right[3][2] && left[3][3] == right[3][3];
}
inline bool operator !=( const XE::Mat4 & left, const XE::Mat4 & right )
{
	return
		left[0][0] != right[0][0] || left[0][1] != right[0][1] || left[0][2] != right[0][2] || left[0][3] != right[0][3] ||
		left[1][0] != right[1][0] || left[1][1] != right[1][1] || left[1][2] != right[1][2] || left[1][3] != right[1][3] ||
		left[2][0] != right[2][0] || left[2][1] != right[2][1] || left[2][2] != right[2][2] || left[2][3] != right[2][3] ||
		left[3][0] != right[3][0] || left[3][1] != right[3][1] || left[3][2] != right[3][2] || left[3][3] != right[3][3];
}

#endif // __MATHF_H__289359AA_D9DE_4269_B0BE_BAAA6E15461B
