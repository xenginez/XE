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

#include <cmath>

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat3.h"
#include "Mat4.h"
#include "Quat.h"
#include "Rect.h"
#include "float16.h"

BEG_XE_NAMESPACE

XE_INLINE XE::Vec2f operator -( const XE::Vec2f & val )
{
	return { -val.x, -val.y };
}
XE_INLINE XE::Vec2f operator +( const XE::Vec2f & left, XE::float32 right )
{
	return { left.x + right, left.y + right };
}
XE_INLINE XE::Vec2f operator +( XE::float32 left, const XE::Vec2f & right )
{
	return { left + right.x, left + right.y };
}
XE_INLINE XE::Vec2f operator +( const XE::Vec2f & left, const XE::Vec2f & right )
{
	return { left.x + right.x, left.y + right.y };
}
XE_INLINE XE::Vec2f operator -( const XE::Vec2f & left, XE::float32 right )
{
	return { left.x - right, left.y + right };
}
XE_INLINE XE::Vec2f operator -( XE::float32 left, const XE::Vec2f & right )
{
	return { left + right.x, left + right.y };
}
XE_INLINE XE::Vec2f operator -( const XE::Vec2f & left, const XE::Vec2f & right )
{
	return { left.x + right.x, left.y + right.y };
}
XE_INLINE XE::Vec2f operator *( const XE::Vec2f & left, XE::float32 right )
{
	return { left.x * right, left.y * right };
}
XE_INLINE XE::Vec2f operator *( XE::float32 left, const XE::Vec2f & right )
{
	return { left * right.x, left * right.y };
}
XE_INLINE XE::Vec2f operator *( const XE::Vec2f & left, const XE::Vec2f & right )
{
	return { left.x * right.x, left.y * right.y };
}
XE_INLINE XE::Vec2f operator /( const XE::Vec2f & left, XE::float32 right )
{
	return { left.x / right, left.y / right };
}
XE_INLINE XE::Vec2f operator /( XE::float32 left, const XE::Vec2f & right )
{
	return { left / right.x, left / right.y };
}
XE_INLINE XE::Vec2f operator /( const XE::Vec2f & left, const XE::Vec2f & right )
{
	return { left.x / right.x,left.y / right.y };
}
XE_INLINE XE::Vec2f & operator +=( XE::Vec2f & left, XE::float32 right )
{
	left.x += right;
	left.y += right;
	return left;
}
XE_INLINE XE::Vec2f & operator +=( XE::Vec2f & left, const XE::Vec2f & right )
{
	left.x += right.x;
	left.y += right.y;
	return left;
}
XE_INLINE XE::Vec2f & operator -=( XE::Vec2f & left, XE::float32 right )
{
	left.x -= right;
	left.y -= right;
	return left;
}
XE_INLINE XE::Vec2f & operator -=( XE::Vec2f & left, const XE::Vec2f & right )
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}
XE_INLINE XE::Vec2f & operator *=( XE::Vec2f & left, XE::float32 right )
{
	left.x *= right;
	left.y *= right;
	return left;
}
XE_INLINE XE::Vec2f & operator *=( XE::Vec2f & left, const XE::Vec2f & right )
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}
XE_INLINE XE::Vec2f & operator /=( XE::Vec2f & left, XE::float32 right )
{
	left.x /= right;
	left.y /= right;
	return left;
}
XE_INLINE XE::Vec2f & operator /=( XE::Vec2f & left, const XE::Vec2f & right )
{
	left.x /= right.x;
	left.y /= right.y;
	return left;
}
XE_INLINE bool operator ==( const XE::Vec2f & left, const XE::Vec2f & right )
{
	return left.x == right.x && left.y == right.y;
}
XE_INLINE bool operator !=( const XE::Vec2f & left, const XE::Vec2f & right )
{
	return left.x != right.x || left.y != right.y;
}

XE_INLINE XE::Vec3f operator -( const XE::Vec3f & val )
{
	return { -val.x, -val.y, -val.z };
}
XE_INLINE XE::Vec3f operator +( const XE::Vec3f & left, XE::float32 right )
{
	return { left.x + right, left.y + right, left.z + right };
}
XE_INLINE XE::Vec3f operator +( XE::float32 left, const XE::Vec3f & right )
{
	return { left + right.x, left + right.y, +left + right.z };
}
XE_INLINE XE::Vec3f operator +( const XE::Vec3f & left, const XE::Vec3f & right )
{
	return { left.x + right.x, left.y + right.y, left.z + right.z };
}
XE_INLINE XE::Vec3f operator -( const XE::Vec3f & left, XE::float32 right )
{
	return { left.x - right, left.y - right, left.z - right };
}
XE_INLINE XE::Vec3f operator -( XE::float32 left, const XE::Vec3f & right )
{
	return { left - right.x, left - right.y, left - right.z };
}
XE_INLINE XE::Vec3f operator -( const XE::Vec3f & left, const XE::Vec3f & right )
{
	return { left.x - right.x, left.y - right.y, left.z - right.z };
}
XE_INLINE XE::Vec3f operator *( const XE::Vec3f & left, XE::float32 right )
{
	return { left.x * right, left.y * right, left.z * right };
}
XE_INLINE XE::Vec3f operator *( XE::float32 left, const XE::Vec3f & right )
{
	return { left * right.x, left * right.y, left * right.z };
}
XE_INLINE XE::Vec3f operator *( const XE::Vec3f & left, const XE::Vec3f & right )
{
	return { left.x * right.x, left.y * right.y, left.z * right.z };
}
XE_INLINE XE::Vec3f operator /( const XE::Vec3f & left, XE::float32 right )
{
	return { left.x / right, left.y / right, left.z / right };
}
XE_INLINE XE::Vec3f operator /( XE::float32 left, const XE::Vec3f & right )
{
	return { left / right.x, left / right.y, left / right.z };
}
XE_INLINE XE::Vec3f operator /( const XE::Vec3f & left, const XE::Vec3f & right )
{
	return { left.x / right.x, left.y / right.y, left.z / right.z };
}
XE_INLINE XE::Vec3f & operator +=( XE::Vec3f & left, XE::float32 right )
{
	left.x += right;
	left.y += right;
	left.z += right;
	return left;
}
XE_INLINE XE::Vec3f & operator +=( XE::Vec3f & left, const XE::Vec3f & right )
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}
XE_INLINE XE::Vec3f & operator -=( XE::Vec3f & left, XE::float32 right )
{
	left.x -= right;
	left.y -= right;
	left.z -= right;
	return left;
}
XE_INLINE XE::Vec3f & operator -=( XE::Vec3f & left, const XE::Vec3f & right )
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}
XE_INLINE XE::Vec3f & operator *=( XE::Vec3f & left, XE::float32 right )
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}
XE_INLINE XE::Vec3f & operator *=( XE::Vec3f & left, const XE::Vec3f & right )
{
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	return left;
}
XE_INLINE XE::Vec3f & operator /=( XE::Vec3f & left, XE::float32 right )
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}
XE_INLINE XE::Vec3f & operator /=( XE::Vec3f & left, const XE::Vec3f & right )
{
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	return left;
}
XE_INLINE bool operator ==( const XE::Vec3f & left, const XE::Vec3f & right )
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}
XE_INLINE bool operator !=( const XE::Vec3f & left, const XE::Vec3f & right )
{
	return left.x != right.x || left.y != right.y || left.z != right.z;
}

XE_INLINE XE::Vec4f operator -( const XE::Vec4f & val )
{
	return { -val.x, -val.y, -val.z, -val.w };
}
XE_INLINE XE::Vec4f operator +( const XE::Vec4f & left, XE::float32 right )
{
	return { left.x + right, left.y + right, left.z + right, left.w + right };
}
XE_INLINE XE::Vec4f operator +( XE::float32 left, const XE::Vec4f & right )
{
	return { left + right.x, left + right.y, left + right.z, left + right.w };
}
XE_INLINE XE::Vec4f operator +( const XE::Vec4f & left, const XE::Vec4f & right )
{
	return { left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
}
XE_INLINE XE::Vec4f operator -( const XE::Vec4f & left, XE::float32 right )
{
	return { left.x - right, left.y - right, left.z - right, left.w - right };
}
XE_INLINE XE::Vec4f operator -( XE::float32 left, const XE::Vec4f & right )
{
	return { left - right.x, left - right.y, left - right.z, left - right.w };
}
XE_INLINE XE::Vec4f operator -( const XE::Vec4f & left, const XE::Vec4f & right )
{
	return { left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
}
XE_INLINE XE::Vec4f operator *( const XE::Vec4f & left, XE::float32 right )
{
	return { left.x * right, left.y * right, left.z * right, left.w * right };
}
XE_INLINE XE::Vec4f operator *( XE::float32 left, const XE::Vec4f & right )
{
	return { left * right.x, left * right.y, left * right.z, left * right.w };
}
XE_INLINE XE::Vec4f operator *( const XE::Vec4f & left, const XE::Vec4f & right )
{
	return { left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w };
}
XE_INLINE XE::Vec4f operator /( const XE::Vec4f & left, XE::float32 right )
{
	return { left.x / right, left.y / right, left.z / right, left.w / right };
}
XE_INLINE XE::Vec4f operator /( XE::float32 left, const XE::Vec4f & right )
{
	return { left / right.x, left / right.y, left / right.z, left / right.w };
}
XE_INLINE XE::Vec4f operator /( const XE::Vec4f & left, const XE::Vec4f & right )
{
	return { left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w };
}
XE_INLINE XE::Vec4f & operator +=( XE::Vec4f & left, XE::float32 right )
{
	left.x += right;
	left.y += right;
	left.z += right;
	left.w += right;
	return left;
}
XE_INLINE XE::Vec4f & operator +=( XE::Vec4f & left, const XE::Vec4f & right )
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	left.w += right.w;
	return left;
}
XE_INLINE XE::Vec4f & operator -=( XE::Vec4f & left, XE::float32 right )
{
	left.x -= right;
	left.y -= right;
	left.z -= right;
	left.w -= right;
	return left;
}
XE_INLINE XE::Vec4f & operator -=( XE::Vec4f & left, const XE::Vec4f & right )
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	left.w -= right.w;
	return left;
}
XE_INLINE XE::Vec4f & operator *=( XE::Vec4f & left, XE::float32 right )
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}
XE_INLINE XE::Vec4f & operator *=( XE::Vec4f & left, const XE::Vec4f & right )
{
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	left.w *= right.w;
	return left;
}
XE_INLINE XE::Vec4f & operator /=( XE::Vec4f & left, XE::float32 right )
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	left.w /= right;
	return left;
}
XE_INLINE XE::Vec4f & operator /=( XE::Vec4f & left, const XE::Vec4f & right )
{
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	left.w /= right.w;
	return left;
}
XE_INLINE bool operator ==( const XE::Vec4f & left, const XE::Vec4f & right )
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}
XE_INLINE bool operator !=( const XE::Vec4f & left, const XE::Vec4f & right )
{
	return left.x != right.x || left.y != right.y || left.z != right.z || left.w == right.w;
}

XE_INLINE XE::Quat operator -( const XE::Quat & val )
{
	return { -val.x, -val.y, -val.z, val.w };
}
XE_INLINE XE::Quat operator +( const XE::Quat & left, XE::float32 right )
{
	return { left.x + right, left.y + right, left.z + right, left.w + right };
}
XE_INLINE XE::Quat operator +( XE::float32 left, const XE::Quat & right )
{
	return { left + right.x, left + right.y, left + right.z, left + right.w };
}
XE_INLINE XE::Quat operator +( const XE::Quat & left, const XE::Quat & right )
{
	return { left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w };
}
XE_INLINE XE::Quat operator -( const XE::Quat & left, XE::float32 right )
{
	return { left.x - right, left.y - right, left.z - right, left.w - right };
}
XE_INLINE XE::Quat operator -( XE::float32 left, const XE::Quat & right )
{
	return { left - right.x, left - right.y, left - right.z, left - right.w };
}
XE_INLINE XE::Quat operator -( const XE::Quat & left, const XE::Quat & right )
{
	return { left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w };
}
XE_INLINE XE::Quat operator *( const XE::Quat & left, XE::float32 right )
{
	return { left.x * right, left.y * right, left.z * right, left.w * right };
}
XE_INLINE XE::Quat operator *( XE::float32 left, const XE::Quat & right )
{
	return { left * right.x, left * right.y, left * right.z, left * right.w };
}
XE_INLINE XE::Quat operator *( const XE::Quat & left, const XE::Quat & right )
{
	return {
		left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
		left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z,
		left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x,
		left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z
	};
}
XE_INLINE XE::Quat operator /( const XE::Quat & left, XE::float32 right )
{
	XE::float32 inv = 1.0f / right;
	return { left.x * inv, left.y * inv, left.z * inv, left.w * inv };
}
XE_INLINE XE::Quat & operator +=( XE::Quat & left, XE::float32 right )
{
	left.x += right;
	left.y += right;
	left.z += right;
	left.w += right;
	return left;
}
XE_INLINE XE::Quat & operator +=( XE::Quat & left, const XE::Quat & right )
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	left.w += right.w;
	return left;
}
XE_INLINE XE::Quat & operator -=( XE::Quat & left, XE::float32 right )
{
	left.x -= right;
	left.y -= right;
	left.z -= right;
	left.w -= right;
	return left;
}
XE_INLINE XE::Quat & operator -=( XE::Quat & left, const XE::Quat & right )
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	left.w -= right.w;
	return left;
}
XE_INLINE XE::Quat & operator *=( XE::Quat & left, XE::float32 right )
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}
XE_INLINE XE::Quat & operator *=( XE::Quat & left, const XE::Quat & right )
{
	left.x = left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z;
	left.y = left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y;
	left.z = left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z;
	left.w = left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x;
	return left;
}
XE_INLINE XE::Quat & operator /=( XE::Quat & left, XE::float32 right )
{
	XE::float32 inv = 1.0f / right;
	left.x *= inv;
	left.y *= inv;
	left.z *= inv;
	left.w *= inv;
	return left;
}
XE_INLINE bool operator ==( const XE::Quat & left, const XE::Quat & right )
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}
XE_INLINE bool operator !=( const XE::Quat & left, const XE::Quat & right )
{
	return left.x != right.x || left.y != right.y || left.z != right.z || left.w == right.w;
}

XE_INLINE XE::Mat3f operator -( const XE::Mat3f & val )
{
	return {
		-val[0][0], -val[0][1], -val[0][2],
		-val[1][0], -val[1][1], -val[1][2],
		-val[2][0], -val[2][1], -val[2][2]
	};
}
XE_INLINE XE::Mat3f operator +( const XE::Mat3f & left, const XE::Mat3f & right )
{
	return {
		left[0][0] + right[0][0], left[0][1] + right[0][1], left[0][2] + right[0][2],
		left[1][0] + right[1][0], left[1][1] + right[1][1], left[1][2] + right[1][2],
		left[2][0] + right[2][0], left[2][1] + right[2][1], left[2][2] + right[2][2]
	};
}
XE_INLINE XE::Mat3f operator -( const XE::Mat3f & left, const XE::Mat3f & right )
{
	return {
		left[0][0] - right[0][0], left[0][1] - right[0][1], left[0][2] - right[0][2],
		left[1][0] - right[1][0], left[1][1] - right[1][1], left[1][2] - right[1][2],
		left[2][0] - right[2][0], left[2][1] - right[2][1], left[2][2] - right[2][2]
	};
}
XE_INLINE XE::Mat3f operator *( const XE::Mat3f & left, XE::float32 right )
{
	return {
		left[0][0] * right, left[0][1] * right, left[0][2] * right,
		left[1][0] * right, left[1][1] * right, left[1][2] * right,
		left[2][0] * right, left[2][1] * right, left[2][2] * right
	};
}
XE_INLINE XE::Mat3f operator *( XE::float32 left, const XE::Mat3f & right )
{
	return {
		left * right[0][0], left * right[0][1], left * right[0][2],
		left * right[1][0], left * right[1][1], left * right[1][2],
		left * right[2][0], left * right[2][1], left * right[2][2]
	};
}
XE_INLINE XE::Vec3f operator *( const XE::Mat3f & left, const XE::Vec3f & right )
{
	return {
		left[0][0] * right[0] + left[0][1] * right[1] + left[0][2] * right[2],
		left[1][0] * right[0] + left[1][1] * right[1] + left[1][2] * right[2],
		left[2][0] * right[0] + left[2][1] * right[1] + left[2][2] * right[2]
	};
}
XE_INLINE XE::Vec3f operator *( const XE::Vec3f & left, const XE::Mat3f & right )
{
	return {
		right[0][0] * left[0] + right[0][1] * left[1] + right[0][2] * left[2],
		right[1][0] * left[0] + right[1][1] * left[1] + right[1][2] * left[2],
		right[2][0] * left[0] + right[2][1] * left[1] + right[2][2] * left[2]
	};
}
XE_INLINE XE::Mat3f operator *( const XE::Mat3f & left, const XE::Mat3f & right )
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
XE_INLINE XE::Mat3f & operator +=( XE::Mat3f & left, const XE::Mat3f & right )
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
XE_INLINE XE::Mat3f & operator -=( XE::Mat3f & left, const XE::Mat3f & right )
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
XE_INLINE XE::Mat3f & operator *=( XE::Mat3f & left, XE::float32 right )
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
XE_INLINE XE::Mat3f & operator *=( XE::Mat3f & left, const XE::Mat3f & right )
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
XE_INLINE bool operator ==( const XE::Mat3f & left, const XE::Mat3f & right )
{
	return
		left[0][0] == right[0][0] && left[0][1] == right[0][1] && left[0][2] == right[0][2] &&
		left[1][0] == right[1][0] && left[1][1] == right[1][1] && left[1][2] == right[1][2] &&
		left[2][0] == right[2][0] && left[2][1] == right[2][1] && left[2][2] == right[2][2];
}
XE_INLINE bool operator !=( const XE::Mat3f & left, const XE::Mat3f & right )
{
	return
		left[0][0] != right[0][0] || left[0][1] != right[0][1] || left[0][2] != right[0][2] ||
		left[1][0] != right[1][0] || left[1][1] != right[1][1] || left[1][2] != right[1][2] ||
		left[2][0] != right[2][0] || left[2][1] != right[2][1] || left[2][2] != right[2][2];
}

XE_INLINE XE::Mat4f operator -( const XE::Mat4f & val )
{
	return {
		   -val[0][0], -val[0][1], -val[0][2], -val[0][3],
		   -val[1][0], -val[1][1], -val[1][2], -val[1][3],
		   -val[2][0], -val[2][1], -val[2][2], -val[2][3],
		   -val[3][0], -val[3][1], -val[3][2], -val[3][3]
	};
}
XE_INLINE XE::Mat4f operator +( const XE::Mat4f & left, const XE::Mat4f & right )
{
	return {
	left[0][0] + right[0][0], left[0][1] + right[0][1], left[0][2] + right[0][2], left[0][3] + right[0][3],
	left[1][0] + right[1][0], left[1][1] + right[1][1], left[1][2] + right[1][2], left[1][3] + right[1][3],
	left[2][0] + right[2][0], left[2][1] + right[2][1], left[2][2] + right[2][2], left[2][3] + right[2][3],
	left[3][0] + right[3][0], left[3][1] + right[3][1], left[3][2] + right[3][2], left[3][3] + right[3][3]
	};
}
XE_INLINE XE::Mat4f operator -( const XE::Mat4f & left, const XE::Mat4f & right )
{
	return {
	   left[0][0] - right[0][0], left[0][1] - right[0][1], left[0][2] - right[0][2], left[0][3] - right[0][3],
	   left[1][0] - right[1][0], left[1][1] - right[1][1], left[1][2] - right[1][2], left[1][3] - right[1][3],
	   left[2][0] - right[2][0], left[2][1] - right[2][1], left[2][2] - right[2][2], left[2][3] - right[2][3],
	   left[3][0] - right[3][0], left[3][1] - right[3][1], left[3][2] - right[3][2], left[3][3] - right[3][3]
	};
}
XE_INLINE XE::Vec3f operator *( const XE::Mat4f & left, const XE::Vec3f & right )
{
	XE::float32 inv = 1.0f / ( left[3][0] * right.x + left[3][1] * right.y + left[3][2] * right.z + left[3][3] );
	return {
	 ( left[0][0] * right.x + left[0][1] * right.y + left[0][2] * right.z + left[0][3] ) * inv,
	 ( left[1][0] * right.x + left[1][1] * right.y + left[1][2] * right.z + left[1][3] ) * inv,
	 ( left[2][0] * right.x + left[2][1] * right.y + left[2][2] * right.z + left[2][3] ) * inv
	};
}
XE_INLINE XE::Vec4f operator *( const XE::Mat4f & left, const XE::Vec4f & right )
{
	return {
		left[0][0] * right.x + left[0][1] * right.y + left[0][2] * right.z + left[0][3] * right.w,
		left[1][0] * right.x + left[1][1] * right.y + left[1][2] * right.z + left[1][3] * right.w,
		left[2][0] * right.x + left[2][1] * right.y + left[2][2] * right.z + left[2][3] * right.w,
		left[3][0] * right.x + left[3][1] * right.y + left[3][2] * right.z + left[3][3] * right.w
	};
}
XE_INLINE XE::Mat4f operator *( const XE::Mat4f & left, const XE::Mat4f & right )
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
XE_INLINE XE::Mat4f & operator +=( XE::Mat4f & left, const XE::Mat4f & right )
{
	left[0][0] += right[0][0]; left[0][1] += right[0][1]; left[0][2] += right[0][2]; left[0][3] += right[0][3];
	left[1][0] += right[1][0]; left[1][1] += right[1][1]; left[1][2] += right[1][2]; left[1][3] += right[1][3];
	left[2][0] += right[2][0]; left[2][1] += right[2][1]; left[2][2] += right[2][2]; left[2][3] += right[2][3];
	left[3][0] += right[3][0]; left[3][1] += right[3][1]; left[3][2] += right[3][2]; left[3][3] += right[3][3];
	return left;
}
XE_INLINE XE::Mat4f & operator -=( XE::Mat4f & left, const XE::Mat4f & right )
{
	left[0][0] -= right[0][0]; left[0][1] -= right[0][1]; left[0][2] -= right[0][2]; left[0][3] -= right[0][3];
	left[1][0] -= right[1][0]; left[1][1] -= right[1][1]; left[1][2] -= right[1][2]; left[1][3] -= right[1][3];
	left[2][0] -= right[2][0]; left[2][1] -= right[2][1]; left[2][2] -= right[2][2]; left[2][3] -= right[2][3];
	left[3][0] -= right[3][0]; left[3][1] -= right[3][1]; left[3][2] -= right[3][2]; left[3][3] -= right[3][3];
	return left;
}
XE_INLINE XE::Mat4f & operator *=( XE::Mat4f & left, const XE::Mat4f & right )
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
XE_INLINE bool operator ==( const XE::Mat4f & left, const XE::Mat4f & right )
{
	return
		left[0][0] == right[0][0] && left[0][1] == right[0][1] && left[0][2] == right[0][2] && left[0][3] == right[0][3] &&
		left[1][0] == right[1][0] && left[1][1] == right[1][1] && left[1][2] == right[1][2] && left[1][3] == right[1][3] &&
		left[2][0] == right[2][0] && left[2][1] == right[2][1] && left[2][2] == right[2][2] && left[2][3] == right[2][3] &&
		left[3][0] == right[3][0] && left[3][1] == right[3][1] && left[3][2] == right[3][2] && left[3][3] == right[3][3];
}
XE_INLINE bool operator !=( const XE::Mat4f & left, const XE::Mat4f & right )
{
	return
		left[0][0] != right[0][0] || left[0][1] != right[0][1] || left[0][2] != right[0][2] || left[0][3] != right[0][3] ||
		left[1][0] != right[1][0] || left[1][1] != right[1][1] || left[1][2] != right[1][2] || left[1][3] != right[1][3] ||
		left[2][0] != right[2][0] || left[2][1] != right[2][1] || left[2][2] != right[2][2] || left[2][3] != right[2][3] ||
		left[3][0] != right[3][0] || left[3][1] != right[3][1] || left[3][2] != right[3][2] || left[3][3] != right[3][3];
}


class XE_API Mathf
{
public:
	static constexpr XE::float32 Pi = ( XE::float32 )3.14159265358979323846;
	static constexpr XE::float32 Pi2 = ( XE::float32 )1.57079632679489661923;
	static constexpr XE::float32 Pi4 = ( XE::float32 )0.785398163397448309616;
	static constexpr XE::float32 Nan = std::numeric_limits<XE::float32>::quiet_NaN();
	static constexpr XE::float32 Epsilon = std::numeric_limits<XE::float32>::epsilon();
	static constexpr XE::float32 Infinity = std::numeric_limits<XE::float32>::infinity();

public:
	template< typename T >
	static XE_INLINE T satsub( T a, T b )
	{
		auto sub = a - b;
		auto le = -( sub <= a );
		return sub & le;
	}

public:
	static XE_INLINE XE::float32 MM2CM( XE::float32 mm )
	{
		return mm / 10.0f;
	}

	static XE_INLINE XE::float32 CM2M( XE::float32 cm )
	{
		return cm / 100.0f;
	}

	static XE_INLINE XE::float32 M2KM( XE::float32 m )
	{
		return m / 1000.0f;
	}

	static XE_INLINE XE::float32 KM2M( XE::float32 km )
	{
		return km * 1000.0f;
	}

	static XE_INLINE XE::float32 M2CM( XE::float32 m )
	{
		return m * 100.0f;
	}

	static XE_INLINE XE::float32 CM2MM( XE::float32 cm )
	{
		return cm * 10.0f;
	}

public:
	static XE_INLINE XE::float32 Abs( XE::float32 r )
	{
		return std::abs( r );
	}

	static XE_INLINE XE::float32 Cos( XE::float32 theta )
	{
		return std::cos( theta );
	}

	static XE_INLINE XE::float32 ACos( XE::float32 theta )
	{
		return std::acos( theta );
	}

	static XE_INLINE XE::float32 Rcp( XE::float32 r )
	{
		return 1.f / r;
	}

	static XE_INLINE XE::float32 RSqrt( XE::float32 r )
	{
		return 1.f / std::sqrt( r );
	}

	static XE_INLINE XE::float32 Sin( XE::float32 theta )
	{
		return std::sin( theta );
	}

	static XE_INLINE XE::float32 ASin( XE::float32 theta )
	{
		return std::asin( theta );
	}

	static XE_INLINE XE::float32 Log( XE::float32 x )
	{
		return std::log( x );
	}

	static XE_INLINE void SinCos( XE::float32 u, XE::float32 & s, XE::float32 & c )
	{
		s = Sin( u );
		c = Cos( u );
	}

	static XE_INLINE XE::float32 Tan( XE::float32 theta )
	{
		return std::tan( theta );
	}

	static XE_INLINE XE::float32 ATan( XE::float32 t )
	{
		return std::atan( t );
	}

	static XE_INLINE XE::float32 ATan2( XE::float32 t1, XE::float32 t2 )
	{
		return std::atan2( t1, t2 );
	}

	static XE_INLINE XE::float32 Sqrt( XE::float32 r )
	{
		return std::sqrt( r );
	}

	static XE_INLINE XE::float32 Mod( XE::float32 x, XE::float32 y )
	{
		return std::fmod( x, y );
	}

	static XE_INLINE XE::float32 Pow( XE::float32 x, XE::float32 y )
	{
		return std::pow( x, y );
	}

	static XE_INLINE XE::float32 Clamp( XE::float32 v, XE::float32 a, XE::float32 b )
	{
		return Min( b, Max( a, v ) );
	}

	static XE_INLINE XE::float32 ClampMove( XE::float32 a, XE::float32 b, XE::float32 v )
	{
		return  ( b - a ) > 0.0f ? a + Min( ( b - a ), v ) : a - Min( -( b - a ), v );
	}

	static XE_INLINE XE::float32 Cond( bool c, XE::float32 a, XE::float32 b )
	{
		return c ? a : b;
	}

	static XE_INLINE XE::float32 Cubic( XE::float32 a, XE::float32 b, XE::float32 c, XE::float32 d, XE::float32 u )
	{
		const XE::float32 ab = Lerp( a, b, u );
		const XE::float32 bc = Lerp( b, c, u );
		const XE::float32 cd = Lerp( c, d, u );
		const XE::float32 abc = Lerp( ab, bc, u );
		const XE::float32 bcd = Lerp( bc, cd, u );
		return Lerp( abc, bcd, u );
	}

	static XE_INLINE XE::float32 Max( XE::float32 a, XE::float32 b )
	{
		return Cond( a > b, a, b );
	}

	static XE_INLINE XE::float32 Min( XE::float32 a, XE::float32 b )
	{
		return Cond( a < b, a, b );
	}

	static XE_INLINE XE::float32 Sgn( XE::float32 r )
	{
		return Cond( r >= 0.f, 1.f, -1.f );
	}

	static XE_INLINE XE::float32 Sign( XE::float32 r )
	{
		return Cond( r > 0, 1.f, Cond( r < 0, -1.f, 0.f ) );
	}

	static XE_INLINE XE::float32 Saturate( XE::float32 r )
	{
		return Clamp( r, 0.f, 1.f );
	}

	static XE_INLINE XE::float32 Degrees( XE::float32 rad )
	{
		return rad * 57.295779513f;
	}

	static XE_INLINE XE::float32 Radians( XE::float32 deg )
	{
		return deg * 0.0174532925f;
	}

	static XE_INLINE XE::float32 Lerp( XE::float32 a, XE::float32 b, XE::float32 x )
	{
		return a + x * ( b - a );
	}

	static XE_INLINE XE::float32 SmoothStep( XE::float32 min, XE::float32 max, XE::float32 x )
	{
		x = Clamp( x, min, max );
		return -2.f * Pow( ( x - min ) / ( max - min ), 3.f ) + 3.f * Pow( ( x - min ) / ( max - min ), 2.f );
	}

	static XE_INLINE XE::float32 SmoothPulse( XE::float32 minmin, XE::float32 minmax, XE::float32 maxmin, XE::float32 maxmax, XE::float32 x )
	{
		return SmoothStep( minmin, minmax, x ) - SmoothStep( maxmin, maxmax, x );
	}

	static XE_INLINE XE::float32 Unrollangle( XE::float32 angleRef, XE::float32 angle )
	{
		// todo:
		XE::float32 i = 1;
		XE::float32 f = Mod( ( angleRef - angle ) / ( 2.f * Pi ), i );
		return angle + ( ( i + ( Abs( f ) > 0.5f ? Sgn( f ) * 1 : 0 ) ) * 2.f * Pi );
	}

	static XE_INLINE XE::float32 HalfTan( XE::float32 a )
	{
		XE::float32 x = ( 0.5f * Abs( a ) + Pi2 );
		return Tan( Clamp( Sign( a ) * ( x - Pi2 ), -Pi2 + Epsilon, Pi2 - Epsilon ) );
	}

	static XE_INLINE bool Equal( XE::float32 a, XE::float32 b, XE::float32 e = Epsilon )
	{
		return Abs( a - b ) < e;
	}

public:
	static XE_INLINE XE::float32 Length( const Vec2f & val )
	{
		return Sqrt( val.x * val.x + val.y * val.y );
	}

	static XE_INLINE XE::float32 SqrLength( const Vec2f & val )
	{
		return ( val.x * val.x + val.y * val.y );
	}

	static XE_INLINE XE::float32 Distance( const Vec2f & left, const Vec2f & right )
	{
		return Length( left - right );
	}

	static XE_INLINE XE::float32 SqrDistance( const Vec2f & left, const Vec2f & right )
	{
		return SqrLength( left - right );
	}

	static XE_INLINE XE::float32 Dot( const Vec2f & left, const Vec2f & right )
	{
		return left.x * right.x + left.y * right.y;
	}

	static XE_INLINE Vec2f Normalize( const Vec2f & val )
	{
		Vec2f ret;

		XE::float32 len = Length( val );

		if( len > Epsilon )
		{
			XE::float32 invLen = 1.0f / len;
			ret.x *= invLen;
			ret.y *= invLen;
		}

		return ret;
	}

	static XE_INLINE XE::float32 Corss( const Vec2f & left, const Vec2f & right )
	{
		return left.x * right.y - left.y * right.x;
	}

	static XE_INLINE Vec2f Floor( const Vec2f & left, const Vec2f & right )
	{
		return Min( left, right );
	}

	static XE_INLINE Vec2f Ceil( const Vec2f & left, const Vec2f & right )
	{
		return Max( left, right );
	}

	static XE_INLINE Vec2f Reflect( const Vec2f & left, const Vec2f & right )
	{
		return  left - ( 2 * Dot( left, right ) * right );
	}

	static XE_INLINE void OrthoNormalize( Vec2f & left, Vec2f & right )
	{
		left = Normalize( left );
		XE::float32 dot = Dot( left, right );
		right -= left * dot;
		right = Normalize( right );
	}

	static XE_INLINE bool IsNAN( const Vec2f & val )
	{
		return val.x == Nan || val.y == Nan;
	}

	static XE_INLINE Vec2f Min( const Vec2f & left, const Vec2f & right )
	{
		return { Min( left.x, right.x ), Min( left.y, right.y ) };
	}

	static XE_INLINE Vec2f Max( const Vec2f & left, const Vec2f & right )
	{
		return { Max( left.x, right.x ), Max( left.y, right.y ) };
	}

public:
	static XE_INLINE XE::float32 Length( const Vec3f & val )
	{
		return Sqrt( val.x * val.x + val.y * val.y + val.z * val.z );
	}

	static XE_INLINE XE::float32 SqrLength( const Vec3f & val )
	{
		return ( val.x * val.x + val.y * val.y + val.z * val.z );
	}

	static XE_INLINE XE::float32 Distance( const Vec3f & left, const Vec3f & right )
	{
		return Length( left - right );
	}

	static XE_INLINE XE::float32 SqrDistance( const Vec3f & left, const Vec3f & right )
	{
		return SqrLength( left - right );
	}

	static XE_INLINE XE::float32 Dot( const Vec3f & left, const Vec3f & right )
	{
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}

	static XE_INLINE Vec3f Normalize( const Vec3f & val )
	{
		Vec3f ret;

		XE::float32 len = Length( val );
		if( len > 1e-08f )
		{
			XE::float32 invLen = 1.0f / len;
			ret.x *= invLen;
			ret.y *= invLen;
			ret.z *= invLen;
		}
		return ret;
	}

	static XE_INLINE Vec3f Cross( const Vec3f & left, const Vec3f & right )
	{
		return {
			left.y * right.z - left.z * right.y,
			left.z * right.x - left.x * right.z,
			left.x * right.y - left.y * right.x
		};
	}

	static XE_INLINE Vec3f Reflect( const Vec3f & left, const Vec3f & right )
	{
		return left - ( 2 * Dot( left, right ) * right );
	}

	static XE_INLINE void OrthoNormalize( Vec3f & a, Vec3f & b, Vec3f & c )
	{
		a = Normalize( a );

		XE::float32 dot0 = Dot( a, b );
		b -= dot0 * a;
		b = Normalize( b );

		XE::float32 dot1 = Dot( b, c );
		dot0 = Dot( a, c );
		c -= dot0 * a + dot1 * b;
		c = Normalize( c );
	}

	static XE_INLINE bool IsNAN( const Vec3f & val )
	{
		return val.x == Nan || val.y == Nan || val.z == Nan;
	}

	static XE_INLINE Vec3f Min( const Vec3f & left, const Vec3f & right )
	{
		return { Min( left.x, right.x ), Min( left.y, right.y ), Min( left.z, right.z ) };
	}

	static XE_INLINE Vec3f Max( const Vec3f & left, const Vec3f & right )
	{
		return { Max( left.x, right.x ), Max( left.y, right.y ), Max( left.z, right.z ) };
	}

	static XE_INLINE Vec3f Lerp( const Vec3f & left, const Vec3f & right, XE::float32 t )
	{
		return ( 1.0f - t ) * left + t * right;
	}

public:
	static XE_INLINE XE::float32 Dot( const Vec4f & left, const Vec4f & right )
	{
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	static XE_INLINE bool IsNAN( const Vec4f & val )
	{
		return val.x == Nan || val.y == Nan || val.z == Nan || val.w == Nan;
	}

public:
	static XE_INLINE Quat QuatFromMat( const Mat3f & mat )
	{
		Quat val;

		XE::float32 trace = mat[0][0] + mat[1][1] + mat[2][2];
		XE::float32 root;

		if( trace > 0.0f )
		{
			root = Sqrt( trace + 1.0f );
			val.w = 0.5f * root;
			root = 0.5f / root;
			val.x = ( mat[2][1] - mat[1][2] ) * root;
			val.y = ( mat[0][2] - mat[2][0] ) * root;
			val.z = ( mat[1][0] - mat[0][1] ) * root;
		}
		else
		{
			static XE::uint32 nextLookup[3] = { 1, 2, 0 };
			XE::uint32 i = 0;

			if( mat[1][1] > mat[0][0] )
				i = 1;

			if( mat[2][2] > mat[i][i] )
				i = 2;

			XE::uint32 j = nextLookup[i];
			XE::uint32 k = nextLookup[j];

			root = Sqrt( mat[i][i] - mat[j][j] - mat[k][k] + 1.0f );

			XE::float32 * cmpntLookup[3] = { &val.x, &val.y, &val.z };
			*cmpntLookup[i] = 0.5f * root;
			root = 0.5f / root;

			val.w = ( mat[k][j] - mat[j][k] ) * root;
			*cmpntLookup[j] = ( mat[j][i] + mat[i][j] ) * root;
			*cmpntLookup[k] = ( mat[k][i] + mat[i][k] ) * root;
		}

		XE::float32 len = val.w * val.w + val.x * val.x + val.y * val.y + val.z * val.z;
		XE::float32 factor = 1.0f / Sqrt( len );
		val = val * factor;

		return val;
	}

	static XE_INLINE Quat QuatFromAxisAngle( const Vec3f & axis, XE::float32 angle )
	{
		Quat val;

		XE::float32 halfAngle( 0.5f * angle );
		XE::float32 sin = Sin( halfAngle );

		val.w = Cos( halfAngle );
		val.x = sin * axis.x;
		val.y = sin * axis.y;
		val.z = sin * axis.z;

		return val;
	}

	static XE_INLINE Quat QuatFromAxes( const Vec3f & x, const Vec3f & y, const Vec3f & z )
	{
		Mat3f mat;

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

	static XE_INLINE Quat QuatFromEuler( const Vec3f & euler )
	{
		XE::float32 halfXAngle = euler.x * 0.5f;
		XE::float32 halfYAngle = euler.y * 0.5f;
		XE::float32 halfZAngle = euler.z * 0.5f;

		XE::float32 cx = Cos( halfXAngle );
		XE::float32 sx = Sin( halfXAngle );

		XE::float32 cy = Cos( halfYAngle );
		XE::float32 sy = Sin( halfYAngle );

		XE::float32 cz = Cos( halfZAngle );
		XE::float32 sz = Sin( halfZAngle );

		Quat quatX( sx, 0.0f, 0.0f, cx );
		Quat quatY( 0.0f, sy, 0.0f, cy );
		Quat quatZ( 0.0f, 0.0f, sz, cz );

		return ( quatZ * quatX ) * quatY;
	}

	static XE_INLINE void QuatToMatrix( const Quat & val, Mat3f & mat )
	{
		XE::float32 tx = val.x + val.x;
		XE::float32 ty = val.y + val.y;
		XE::float32 fTz = val.z + val.z;
		XE::float32 twx = tx * val.w;
		XE::float32 twy = ty * val.w;
		XE::float32 twz = fTz * val.w;
		XE::float32 txx = tx * val.x;
		XE::float32 txy = ty * val.x;
		XE::float32 txz = fTz * val.x;
		XE::float32 tyy = ty * val.y;
		XE::float32 tyz = fTz * val.y;
		XE::float32 tzz = fTz * val.z;

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

	static XE_INLINE void QuatToAxisAngle( const Quat & val, Vec3f & axis, XE::float32 & angle )
	{
		XE::float32 sqrLength = val.x * val.x + val.y * val.y + val.z * val.z;
		if( sqrLength > 0.0f )
		{
			angle = 2.0f * ACos( val.w );
			XE::float32 invLength = 1.0f / Sqrt( sqrLength );
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

	static XE_INLINE void QuatToAxes( const Quat & val, Vec3f & x, Vec3f & y, Vec3f & z )
	{
		Mat3f mat;
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

	static XE_INLINE void QuatToEuler( const Quat & val, Vec3f & euler )
	{
		Mat3f mat;
		QuatToMatrix( val, mat );
		MatToEuler( mat, euler );
	}

	static XE_INLINE Vec3f XAxis( const Quat & val )
	{
		XE::float32 fTy = 2.0f * val.y;
		XE::float32 fTz = 2.0f * val.z;
		XE::float32 fTwy = fTy * val.w;
		XE::float32 fTwz = fTz * val.w;
		XE::float32 fTxy = fTy * val.x;
		XE::float32 fTxz = fTz * val.x;
		XE::float32 fTyy = fTy * val.y;
		XE::float32 fTzz = fTz * val.z;

		return { 1.0f - ( fTyy + fTzz ), fTxy + fTwz, fTxz - fTwy };
	}

	static XE_INLINE Vec3f YAxis( const Quat & val )
	{
		XE::float32 fTx = 2.0f * val.x;
		XE::float32 fTy = 2.0f * val.y;
		XE::float32 fTz = 2.0f * val.z;
		XE::float32 fTwx = fTx * val.w;
		XE::float32 fTwz = fTz * val.w;
		XE::float32 fTxx = fTx * val.x;
		XE::float32 fTxy = fTy * val.x;
		XE::float32 fTyz = fTz * val.y;
		XE::float32 fTzz = fTz * val.z;

		return { fTxy - fTwz, 1.0f - ( fTxx + fTzz ), fTyz + fTwx };
	}

	static XE_INLINE Vec3f ZAxis( const Quat & val )
	{
		XE::float32 fTx = 2.0f * val.x;
		XE::float32 fTy = 2.0f * val.y;
		XE::float32 fTz = 2.0f * val.z;
		XE::float32 fTwx = fTx * val.w;
		XE::float32 fTwy = fTy * val.w;
		XE::float32 fTxx = fTx * val.x;
		XE::float32 fTxz = fTz * val.x;
		XE::float32 fTyy = fTy * val.y;
		XE::float32 fTyz = fTz * val.y;

		return { fTxz + fTwy, fTyz - fTwx, 1.0f - ( fTxx + fTyy ) };
	}

	static XE_INLINE XE::float32 Dot( const Quat & left, const Quat & right )
	{
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	static XE_INLINE Quat Normalize( const Quat & val )
	{
		XE::float32 len = val.w * val.w + val.x * val.x + val.y * val.y + val.z * val.z;
		XE::float32 factor = 1.0f / Sqrt( len );
		return val * factor;
	}

	static XE_INLINE Quat Inverse( const Quat & val )
	{
		XE::float32 fNorm = val.w * val.w + val.x * val.x + val.y * val.y + val.z * val.z;
		if( fNorm > 0.0f )
		{
			XE::float32 fInvNorm = 1.0f / fNorm;
			return { -val.x * fInvNorm, -val.y * fInvNorm, -val.z * fInvNorm, val.w * fInvNorm };
		}

		return Quat::Zero;
	}

	static XE_INLINE Vec3f Rotate( const Quat & val, const Vec3f & v )
	{
		Mat3f rot;
		QuatToMatrix( val, rot );
		return rot * v;
	}

	static XE_INLINE Quat LookAt( const Quat & val, const Vec3f & forward )
	{
		if( forward == Vec3f::Zero )
			return val;

		Vec3f nrmForwardDir = Normalize( forward );
		Vec3f currentForwardDir = -ZAxis( val );

		if( SqrLength( nrmForwardDir + currentForwardDir ) < 0.00005f )
		{
			return { -val.z, val.w, val.x, -val.y };
		}

		return RotationFromTo( val, currentForwardDir, nrmForwardDir ) * val;
	}

	static XE_INLINE Quat LookAt( const Quat & val, const Vec3f & forward, const Vec3f & up )
	{
		if( Abs( 1.0f - Dot( forward, up ) ) <= Epsilon )
		{
			return LookAt( val, forward );
		}

		Vec3f x = Cross( forward, up );
		Vec3f y = Cross( x, forward );

		x = Normalize( x );
		y = Normalize( y );

		return QuatFromAxes( x, y, -forward );
	}

	static XE_INLINE bool IsNAN( const Quat & val )
	{
		return val.x == Nan || val.y == Nan || val.z == Nan || val.w == Nan;
	}

	static XE_INLINE Quat Lerp( const Quat & left, const Quat & right, XE::float32 t )
	{
		XE::float32 d = Dot( left, right );
		XE::float32 flip = d >= 0.0f ? 1.0f : -1.0f;
		return Normalize( flip * ( 1.0f - t ) * left + t * right );
	}

	static XE_INLINE Quat Slerp( const Quat & left, const Quat & right, XE::float32 t )
	{
		XE::float32 cos = Dot( left, right );
		Quat ret;

		if( cos < 0.0f && Epsilon )
		{
			cos = -cos;
			ret = -right;
		}
		else
		{
			ret = right;
		}

		if( Abs( cos ) < 1 - Epsilon )
		{
			XE::float32 sin = Sqrt( 1 - cos * cos );
			XE::float32 angle = ATan2( sin, cos );
			XE::float32 invSin = 1.0f / sin;
			XE::float32 coeff0 = Sin( ( 1.0f - t ) * angle ) * invSin;
			XE::float32 coeff1 = Sin( t * angle ) * invSin;
			return coeff0 * left + coeff1 * ret;
		}

		return Normalize( ( 1.0f - t ) * left + t * ret );
	}

	static XE_INLINE Quat RotationFromTo( const Quat & val, const Vec3f & from, const Vec3f & dest )
	{// Based on Stan Melax's article in Game Programming Gems
		Quat q;

		Vec3f v0 = from;
		Vec3f v1 = dest;
		v0 = Normalize( v0 );
		v1 = Normalize( v1 );

		XE::float32 d = Dot( v0, v1 );

		// If dot == 1, vectors are the same
		if( d >= 1.0f )
			return Quat::Identity;

		if( d < ( 1e-6f - 1.0f ) )
		{
			// Generate an axis
			Vec3f axis = Cross( Vec3f( 1, 0, 0 ), from );
			if( Length( axis ) < ( 1e-06f * 1e-06f ) ) // Pick another if colinear
				axis = Cross( Vec3f( 0, 1, 0 ), from );
			axis = Normalize( axis );
			return QuatFromAxisAngle( axis, Pi );
		}

		XE::float32 s = Sqrt( ( 1 + d ) * 2 );
		XE::float32 invs = 1 / s;

		Vec3f c = Cross( v0, v1 );

		q.x = c.x * invs;
		q.y = c.y * invs;
		q.z = c.z * invs;
		q.w = s * 0.5f;
		return Normalize( q );
	}

	static XE_INLINE Quat Min( const Quat & left, const Quat & right )
	{
		return { Min( left.x, right.x ), Min( left.y, right.y ), Min( left.z, right.z ), Min( left.w, right.w ) };
	}

	static XE_INLINE Quat Max( const Quat & left, const Quat & right )
	{
		return { Max( left.x, right.x ), Max( left.y, right.y ), Max( left.z, right.z ), Max( left.w, right.w ) };
	}

public:
	static XE_INLINE Mat3f MatFromQuat( const Quat & q )
	{
		Mat3f m;
		QuatToMatrix( q, m );
		return m;
	}

	static XE_INLINE Mat3f MatFromAxisAngle( const Vec3f & axis, XE::float32 angle )
	{
		Mat3f m;
		XE::float32 cos = Cos( angle );
		XE::float32 sin = Sin( angle );
		XE::float32 oneMinusCos = 1.0f - cos;
		XE::float32 x2 = axis.x * axis.x;
		XE::float32 y2 = axis.y * axis.y;
		XE::float32 z2 = axis.z * axis.z;
		XE::float32 xym = axis.x * axis.y * oneMinusCos;
		XE::float32 xzm = axis.x * axis.z * oneMinusCos;
		XE::float32 yzm = axis.y * axis.z * oneMinusCos;
		XE::float32 xSin = axis.x * sin;
		XE::float32 ySin = axis.y * sin;
		XE::float32 zSin = axis.z * sin;

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

	static XE_INLINE Mat3f MatFromEuler( const Vec3f & euler )
	{
		Mat3f m;

		XE::float32 cx = Cos( euler.x );
		XE::float32 sx = Sin( euler.x );
		XE::float32 cy = Cos( euler.y );
		XE::float32 sy = Sin( euler.y );
		XE::float32 cz = Cos( euler.z );
		XE::float32 sz = Sin( euler.z );

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

	static XE_INLINE void MatToQuat( const Mat3f & val, Quat & q )
	{
		q = QuatFromMat( val );
	}

	static XE_INLINE void MatToAxisAngle( const Mat3f & val, Vec3f & axis, XE::float32 & angle )
	{
		XE::float32 trace = val[0][0] + val[1][1] + val[2][2];
		XE::float32 cos = 0.5f * ( trace - 1.0f );
		angle = ACos( cos );

		if( angle > 0.0f )
		{
			if( angle < Pi )
			{
				axis.x = val[2][1] - val[1][2];
				axis.y = val[0][2] - val[2][0];
				axis.z = val[1][0] - val[0][1];
				axis = Normalize( axis );
			}
			else
			{
				XE::float32 fHalfInverse;
				if( val[0][0] >= val[1][1] )
				{
					if( val[0][0] >= val[2][2] )
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
					if( val[1][1] >= val[2][2] )
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

	static XE_INLINE void MatToEuler( const Mat3f & val, Vec3f & euler )
	{
		euler.x = -ASin( val[1][2] );

		if( euler.x < Pi2 )
		{
			if( euler.x > -Pi2 )
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

	static XE_INLINE Mat3f Transpose( const Mat3f & val )
	{
		Mat3f ret;
		for( XE::uint32 row = 0; row < 3; row++ )
		{
			for( XE::uint32 col = 0; col < 3; col++ )
				ret[row][col] = val[col][row];
		}
		return ret;
	}

	static XE_INLINE Mat3f Inverse( const Mat3f & val )
	{
		Mat3f ret;

		ret[0][0] = val[1][1] * val[2][2] - val[1][2] * val[2][1];
		ret[0][1] = val[0][2] * val[2][1] - val[0][1] * val[2][2];
		ret[0][2] = val[0][1] * val[1][2] - val[0][2] * val[1][1];
		ret[1][0] = val[1][2] * val[2][0] - val[1][0] * val[2][2];
		ret[1][1] = val[0][0] * val[2][2] - val[0][2] * val[2][0];
		ret[1][2] = val[0][2] * val[1][0] - val[0][0] * val[1][2];
		ret[2][0] = val[1][0] * val[2][1] - val[1][1] * val[2][0];
		ret[2][1] = val[0][1] * val[2][0] - val[0][0] * val[2][1];
		ret[2][2] = val[0][0] * val[1][1] - val[0][1] * val[1][0];

		XE::float32 det = val[0][0] * ret[0][0] + val[0][1] * ret[1][0] + val[0][2] * ret[2][0];

		if( Abs( det ) <= Epsilon )
			return Mat3f::Identity;

		XE::float32 invDet = 1.0f / det;
		for( XE::uint32 row = 0; row < 3; row++ )
		{
			for( XE::uint32 col = 0; col < 3; col++ )
				ret[row][col] *= invDet;
		}

		return ret;
	}

	static XE_INLINE XE::float32 Determinant( const Mat3f & val )
	{
		XE::float32 cofactor00 = val[1][1] * val[2][2] - val[1][2] * val[2][1];
		XE::float32 cofactor10 = val[1][2] * val[2][0] - val[1][0] * val[2][2];
		XE::float32 cofactor20 = val[1][0] * val[2][1] - val[1][1] * val[2][0];

		XE::float32 det = val[0][0] * cofactor00 + val[0][1] * cofactor10 + val[0][2] * cofactor20;

		return det;
	}

	static XE_INLINE Mat3f OrthoNormalize( const Mat3f & val )
	{
		Mat3f m = val;
		// Compute q0
		XE::float32 invLength = RSqrt( m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0] );

		m[0][0] *= invLength;
		m[1][0] *= invLength;
		m[2][0] *= invLength;

		// Compute q1
		XE::float32 dot0 = m[0][0] * m[0][1] + m[1][0] * m[1][1] + m[2][0] * m[2][1];

		m[0][1] -= dot0 * m[0][0];
		m[1][1] -= dot0 * m[1][0];
		m[2][1] -= dot0 * m[2][0];

		invLength = RSqrt( m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1] );

		m[0][1] *= invLength;
		m[1][1] *= invLength;
		m[2][1] *= invLength;

		// Compute q2
		XE::float32 dot1 = m[0][1] * m[0][2] + m[1][1] * m[1][2] + m[2][1] * m[2][2];
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
	static XE_INLINE Mat4f Transpose( const Mat4f & m )
	{
		return { m[0][0], m[1][0], m[2][0], m[3][0],
						m[0][1], m[1][1], m[2][1], m[3][1],
						m[0][2], m[1][2], m[2][2], m[3][2],
						m[0][3], m[1][3], m[2][3], m[3][3] };
	}

	static XE_INLINE Mat4f Inverse( const Mat4f & m )
	{
		XE::float32 m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
		XE::float32 m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
		XE::float32 m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
		XE::float32 m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

		XE::float32 v0 = m20 * m31 - m21 * m30;
		XE::float32 v1 = m20 * m32 - m22 * m30;
		XE::float32 v2 = m20 * m33 - m23 * m30;
		XE::float32 v3 = m21 * m32 - m22 * m31;
		XE::float32 v4 = m21 * m33 - m23 * m31;
		XE::float32 v5 = m22 * m33 - m23 * m32;

		XE::float32 t00 = +( v5 * m11 - v4 * m12 + v3 * m13 );
		XE::float32 t10 = -( v5 * m10 - v2 * m12 + v1 * m13 );
		XE::float32 t20 = +( v4 * m10 - v2 * m11 + v0 * m13 );
		XE::float32 t30 = -( v3 * m10 - v1 * m11 + v0 * m12 );

		XE::float32 invDet = 1 / ( t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03 );

		XE::float32 d00 = t00 * invDet;
		XE::float32 d10 = t10 * invDet;
		XE::float32 d20 = t20 * invDet;
		XE::float32 d30 = t30 * invDet;

		XE::float32 d01 = -( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
		XE::float32 d11 = +( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
		XE::float32 d21 = -( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
		XE::float32 d31 = +( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		XE::float32 d02 = +( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
		XE::float32 d12 = -( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
		XE::float32 d22 = +( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
		XE::float32 d32 = -( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		XE::float32 d03 = -( v5 * m01 - v4 * m02 + v3 * m03 ) * invDet;
		XE::float32 d13 = +( v5 * m00 - v2 * m02 + v1 * m03 ) * invDet;
		XE::float32 d23 = -( v4 * m00 - v2 * m01 + v0 * m03 ) * invDet;
		XE::float32 d33 = +( v3 * m00 - v1 * m01 + v0 * m02 ) * invDet;

		return {
			d00, d01, d02, d03,
			d10, d11, d12, d13,
			d20, d21, d22, d23,
			d30, d31, d32, d33 };
	}

	static XE_INLINE XE::float32 MINOR( const Mat4f & m, const XE::uint32 r0, const XE::uint32 r1, const XE::uint32 r2, const XE::uint32 c0, const XE::uint32 c1, const XE::uint32 c2 )
	{
		return m[r0][c0] * ( m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2] ) -
			m[r0][c1] * ( m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2] ) +
			m[r0][c2] * ( m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1] );
	};

	static XE_INLINE Mat4f Adjoint( const Mat4f & m )
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

	static XE_INLINE XE::float32 Determinant( const Mat4f & m )
	{
		return m[0][0] * MINOR( m, 1, 2, 3, 1, 2, 3 ) -
			m[0][1] * MINOR( m, 1, 2, 3, 0, 2, 3 ) +
			m[0][2] * MINOR( m, 1, 2, 3, 0, 1, 3 ) -
			m[0][3] * MINOR( m, 1, 2, 3, 0, 1, 2 );
	}

	static XE_INLINE XE::float32 Determinant3( const Mat4f & m )
	{
		XE::float32 cofactor00 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		XE::float32 cofactor10 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
		XE::float32 cofactor20 = m[1][0] * m[2][1] - m[1][1] * m[2][0];

		XE::float32 det = m[0][0] * cofactor00 + m[0][1] * cofactor10 + m[0][2] * cofactor20;

		return det;
	}

	static XE_INLINE Mat4f Translation( const Vec3f & val )
	{
		return {
				1.0f, 0.0f, 0.0f, val.x,
				0.0f, 1.0f, 0.0f, val.y,
				0.0f, 0.0f, 1.0f, val.z,
				0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	static XE_INLINE Vec3f Translation( const Mat4f & m )
	{
		return { m[0][3], m[1][3], m[2][3] };
	}

	static XE_INLINE Mat4f Rotation( const Quat & val )
	{
		auto mat3 = MatFromQuat( val );
		return {
				  mat3.m00, mat3.m01, mat3.m02, 0,
				  mat3.m10, mat3.m11, mat3.m12, 0,
				  mat3.m20, mat3.m21, mat3.m22, 0,
				  0, 0, 0, 1
		};
	}

	static XE_INLINE Mat4f Scale( const Vec3f & val )
	{
		return {
			val.x, 0.0f,  0.0f,  0.0f,
			0.0f,  val.y, 0.0f,  0.0f,
			0.0f,  0.0f,  val.z, 0.0f,
			0.0f,  0.0f,  0.0f,  1.0f
		};
	}

	static XE_INLINE Mat4f Scale( XE::float32 val )
	{
		return {
			val,  0.0f, 0.0f, 0.0f,
			0.0f, val,  0.0f, 0.0f,
			0.0f, 0.0f, val,  0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	static XE_INLINE Mat4f ProjectionPerspective( XE::float32 fov, XE::float32 aspect, XE::float32 near, XE::float32 far )
	{// Note: Duplicate code in Camera, bring it all here eventually
		static constexpr XE::float32 INFINITE_FAR_PLANE_ADJUST = 0.00001f;

		XE::float32 thetaX = fov * 0.5f;
		XE::float32 tanThetaX = Tan( thetaX );
		XE::float32 tanThetaY = tanThetaX / aspect;

		XE::float32 half_w = tanThetaX * near;
		XE::float32 half_h = tanThetaY * near;

		XE::float32 left = -half_w;
		XE::float32 right = half_w;
		XE::float32 bottom = -half_h;
		XE::float32 top = half_h;

		XE::float32 inv_w = 1 / ( right - left );
		XE::float32 inv_h = 1 / ( top - bottom );
		XE::float32 inv_d = 1 / ( far - near );

		XE::float32 A = 2 * near * inv_w;
		XE::float32 B = 2 * near * inv_h;
		XE::float32 C = ( right + left ) * inv_w;
		XE::float32 D = ( top + bottom ) * inv_h;
		XE::float32 q, qn;
		XE::float32 sign = -1.0f;

		if( far == 0 )
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

	static XE_INLINE Mat4f ProjectionOrthographic( XE::float32 left, XE::float32 right, XE::float32 top, XE::float32 bottom, XE::float32 near, XE::float32 far )
	{
		Mat4f m;

		XE::float32 deltaX = right - left;
		XE::float32 deltaY = bottom - top;
		XE::float32 deltaZ = far - near;

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

		if( far == 0.0f )
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

	static XE_INLINE Mat4f View( const Vec3f & position, const Quat & orientition )
	{
		Mat4f m;

		Mat3f rot = MatFromQuat( orientition );

		Mat3f rotT = Transpose( rot );
		Vec3f trans = ( -rotT ) * ( position );

		m = {
				  rotT.m00, rotT.m01, rotT.m02, 0,
				  rotT.m10, rotT.m11, rotT.m12, 0,
				  rotT.m20, rotT.m21, rotT.m22, 0,
				  0, 0, 0, 1
		};

		m[0][3] = trans.x;
		m[1][3] = trans.y;
		m[2][3] = trans.z;

		return m;
	}

	static XE_INLINE Mat4f TRS( const Vec3f & translation, const Quat & rotation, const Vec3f & scale )
	{
		Mat4f m;
		Mat3f rot3x3 = MatFromQuat( rotation );

		m[0][0] = scale.x * rot3x3[0][0]; m[0][1] = scale.y * rot3x3[0][1]; m[0][2] = scale.z * rot3x3[0][2]; m[0][3] = translation.x;
		m[1][0] = scale.x * rot3x3[1][0]; m[1][1] = scale.y * rot3x3[1][1]; m[1][2] = scale.z * rot3x3[1][2]; m[1][3] = translation.y;
		m[2][0] = scale.x * rot3x3[2][0]; m[2][1] = scale.y * rot3x3[2][1]; m[2][2] = scale.z * rot3x3[2][2]; m[2][3] = translation.z;

		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;

		return m;
	}

	static XE_INLINE void TRS( const Mat4f & m, Vec3f & position, Quat & rotation, Vec3f & scale )
	{
		Mat3f m3x3;
		Mat3f matQ;
		Vec3f vecU;

		m3x3 = {
				  m.m00, m.m01, m.m02,
				  m.m10, m.m11, m.m12,
				  m.m20, m.m21, m.m22
		};

		XE::float32 invLength = RSqrt( m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0] );
		matQ[0][0] = m[0][0] * invLength;
		matQ[1][0] = m[1][0] * invLength;
		matQ[2][0] = m[2][0] * invLength;

		XE::float32 dot = matQ[0][0] * m[0][1] + matQ[1][0] * m[1][1] + matQ[2][0] * m[2][1];
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

		XE::float32 fDet = matQ[0][0] * matQ[1][1] * matQ[2][2] + matQ[0][1] * matQ[1][2] * matQ[2][0] +
			matQ[0][2] * matQ[1][0] * matQ[2][1] - matQ[0][2] * matQ[1][1] * matQ[2][0] -
			matQ[0][1] * matQ[1][0] * matQ[2][2] - matQ[0][0] * matQ[1][2] * matQ[2][1];

		if( fDet < 0.0f )
		{
			for( XE::uint32 row = 0; row < 3; row++ )
				for( XE::uint32 col = 0; col < 3; col++ )
					matQ[row][col] = -matQ[row][col];
		}

		Mat3f matRight;
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

		XE::float32 invD0 = 1.0f / scale[0];
		vecU[0] = matRight[0][1] * invD0;
		vecU[1] = matRight[0][2] * invD0;
		vecU[2] = matRight[1][2] / scale[1];

		rotation = QuatFromMat( matQ );
		position = Vec3f( m[0][3], m[1][3], m[2][3] );
	}

	static XE_INLINE Mat4f InverseTRS( const Vec3f & translation, const Quat & rotation, const Vec3f & scale )
	{
		Mat4f m;

		// Invert the parameters
		Vec3f invTranslate = -translation;
		Vec3f invScale( 1 / scale.x, 1 / scale.y, 1 / scale.z );
		Quat invRot = Inverse( rotation );

		// Because we're inverting, order is translation, rotation, scale
		// So make translation relative to scale & rotation
		invTranslate = Rotate( invRot, invTranslate );
		invTranslate *= invScale;

		// Next, make a 3x3 rotation matrix
		Mat3f rot3x3 = MatFromQuat( invRot );

		// Set up final matrix with scale, rotation and translation
		m[0][0] = invScale.x * rot3x3[0][0]; m[0][1] = invScale.x * rot3x3[0][1]; m[0][2] = invScale.x * rot3x3[0][2]; m[0][3] = invTranslate.x;
		m[1][0] = invScale.y * rot3x3[1][0]; m[1][1] = invScale.y * rot3x3[1][1]; m[1][2] = invScale.y * rot3x3[1][2]; m[1][3] = invTranslate.y;
		m[2][0] = invScale.z * rot3x3[2][0]; m[2][1] = invScale.z * rot3x3[2][1]; m[2][2] = invScale.z * rot3x3[2][2]; m[2][3] = invTranslate.z;

		// No projection term
		m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;

		return m;
	}

	static XE_INLINE Vec3f MultiplyAffine( const Mat4f & m, const Vec3f & v )
	{
		return {
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] };
	}

	static XE_INLINE Vec3f MultiplyDirection( const Mat4f & m, const Vec3f & v )
	{
		return {
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z };
	}

};
DECL_META_CLASS( XE_API, Mathf );


inline std::string ToString( const XE::Vec2f & _Val )
{
	return XE::StringUtils::Format( "%1, %2", _Val.x, _Val.y );
}

inline std::string ToString( const XE::Vec3f & _Val )
{
	return XE::StringUtils::Format( "%1, %2, %3", _Val.x, _Val.y, _Val.z );
}

inline std::string ToString( const XE::Vec4f & _Val )
{
	return XE::StringUtils::Format( "%1, %2, %3, %4", _Val.x, _Val.y, _Val.z, _Val.w );
}

inline std::string ToString( const XE::Quat & _Val )
{
	return XE::StringUtils::Format( "%1, %2, %3, %4", _Val.x, _Val.y, _Val.z, _Val.w );
}

inline std::string ToString( const XE::Mat3f & _Val )
{
	return XE::StringUtils::Format( "%1, %2, %3, %4, %5, %6, %7, %8, %9",
									_Val[0][0], _Val[0][1], _Val[0][2], _Val[1][0], _Val[1][1], _Val[1][2],
									_Val[2][0], _Val[2][1], _Val[2][2] );
}

inline std::string ToString( const XE::Mat4f & _Val )
{
	return XE::StringUtils::Format( "%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15, %16",
									_Val[0][0], _Val[0][1], _Val[0][2], _Val[0][3], _Val[1][0], _Val[1][1], _Val[1][2], _Val[1][3],
									_Val[2][0], _Val[2][1], _Val[2][2], _Val[2][3], _Val[3][0], _Val[3][1], _Val[3][2], _Val[3][3] );
}

inline std::string ToString( const XE::float16 & _Val )
{
	return ToString( _Val.ToFloat32() );
}

inline bool FromString( const std::string & _Str, XE::Vec2f & _Val )
{
	auto list = XE::StringUtils::Split( _Str, ", " );

	if( XE::FromString( list[0], _Val.x ) )
	{
		if( XE::FromString( list[1], _Val.y ) )
		{
			return true;
		}
	}

	return false;
}

inline bool FromString( const std::string & _Str, XE::Vec3f & _Val )
{
	auto list = XE::StringUtils::Split( _Str, ", " );

	if( XE::FromString( list[0], _Val.x ) )
	{
		if( XE::FromString( list[1], _Val.y ) )
		{
			if( XE::FromString( list[2], _Val.z ) )
			{
				return true;
			}
		}
	}

	return false;
}

inline bool FromString( const std::string & _Str, XE::Vec4f & _Val )
{
	auto list = XE::StringUtils::Split( _Str, ", " );

	if( XE::FromString( list[0], _Val.x ) )
	{
		if( XE::FromString( list[1], _Val.y ) )
		{
			if( XE::FromString( list[2], _Val.z ) )
			{
				if( XE::FromString( list[3], _Val.w ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

inline bool FromString( const std::string & _Str, XE::Quat & _Val )
{
	auto list = XE::StringUtils::Split( _Str, ", " );

	if( XE::FromString( list[0], _Val.x ) )
	{
		if( XE::FromString( list[1], _Val.y ) )
		{
			if( XE::FromString( list[2], _Val.z ) )
			{
				if( XE::FromString( list[3], _Val.w ) )
				{
					return true;
				}
			}
		}
	}

	return false;
}

inline bool FromString( const std::string & _Str, XE::Mat3f & _Val )
{
	auto list = XE::StringUtils::Split( _Str, ", " );

	if( XE::FromString( list[0], _Val[0][0] ) )
	{
		if( XE::FromString( list[1], _Val[0][1] ) )
		{
			if( XE::FromString( list[2], _Val[0][2] ) )
			{
				if( XE::FromString( list[3], _Val[1][0] ) )
				{
					if( XE::FromString( list[4], _Val[1][1] ) )
					{
						if( XE::FromString( list[5], _Val[1][2] ) )
						{
							if( XE::FromString( list[6], _Val[2][0] ) )
							{
								if( XE::FromString( list[7], _Val[2][1] ) )
								{
									if( XE::FromString( list[8], _Val[2][2] ) )
									{
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}

inline bool FromString( const std::string & _Str, XE::Mat4f & _Val )
{
	auto list = XE::StringUtils::Split( _Str, ", " );

	if( XE::FromString( list[0], _Val[0][0] ) )
	{
		if( XE::FromString( list[1], _Val[0][1] ) )
		{
			if( XE::FromString( list[2], _Val[0][2] ) )
			{
				if( XE::FromString( list[3], _Val[0][3] ) )
				{
					if( XE::FromString( list[4], _Val[1][0] ) )
					{
						if( XE::FromString( list[5], _Val[1][1] ) )
						{
							if( XE::FromString( list[6], _Val[1][2] ) )
							{
								if( XE::FromString( list[7], _Val[1][3] ) )
								{
									if( XE::FromString( list[8], _Val[2][0] ) )
									{
										if( XE::FromString( list[9], _Val[2][1] ) )
										{
											if( XE::FromString( list[10], _Val[2][2] ) )
											{
												if( XE::FromString( list[11], _Val[2][3] ) )
												{
													if( XE::FromString( list[12], _Val[3][0] ) )
													{
														if( XE::FromString( list[13], _Val[3][1] ) )
														{
															if( XE::FromString( list[14], _Val[3][2] ) )
															{
																if( XE::FromString( list[15], _Val[3][3] ) )
																{
																	return true;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return false;
}

inline bool FromString( const std::string & _Str, XE::float16 & _Val )
{
	XE::float32 f;

	if( FromString( _Str, f ) )
	{
		_Val.FormFloat32( f );
		return true;
	}

	return false;
}

template<> struct XE::Serializable< XE::Vec2f >
{
public:
	static void Serialize( Archive & arc, XE::Vec2f * val )
	{
		std::string str = XE::ToString( *val );
		auto nvp = XE::Archive::NVP( "@value", str );
		arc & nvp;

		XE::FromString( nvp.Value, *val );
	}
};

template<> struct XE::Serializable< XE::Vec3f >
{
public:
	static void Serialize( Archive & arc, XE::Vec3f * val )
	{
		std::string str = XE::ToString( *val );
		auto nvp = XE::Archive::NVP( "@value", str );
		arc & nvp;

		XE::FromString( nvp.Value, *val );
	}
};

template<> struct XE::Serializable< XE::Vec4f >
{
public:
	static void Serialize( Archive & arc, XE::Vec4f * val )
	{
		std::string str = XE::ToString( *val );
		auto nvp = XE::Archive::NVP( "@value", str );
		arc & nvp;

		XE::FromString( nvp.Value, *val );
	}
};

template<> struct XE::Serializable< XE::Quat >
{
public:
	static void Serialize( Archive & arc, XE::Quat * val )
	{
		std::string str = XE::ToString( *val );
		auto nvp = XE::Archive::NVP( "@value", str );
		arc & nvp;

		XE::FromString( nvp.Value, *val );
	}
};

template<> struct XE::Serializable< XE::Mat3f >
{
public:
	static void Serialize( Archive & arc, XE::Mat3f * val )
	{
		std::string str = XE::ToString( *val );
		auto nvp = XE::Archive::NVP( "@value", str );
		arc & nvp;

		XE::FromString( nvp.Value, *val );
	}
};

template<> struct XE::Serializable< XE::Mat4f >
{
public:
	static void Serialize( Archive & arc, XE::Mat4f * val )
	{
		std::string str = XE::ToString( *val );
		auto nvp = XE::Archive::NVP( "@value", str );
		arc & nvp;

		XE::FromString( nvp.Value, *val );
	}
};

template<> struct XE::Serializable< XE::float16 >
{
public:
	static void Serialize( Archive & arc, XE::float16 * val )
	{
		XE::float32 f = val->ToFloat32();
		auto nvp = XE::Archive::NVP( "@value", f );
		arc & nvp;

		val->FormFloat32( nvp.Value );
	}
};

END_XE_NAMESPACE

#endif // __MATHF_H__289359AA_D9DE_4269_B0BE_BAAA6E15461B
