/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__98A93208_FE74_468C_A0B7_059AC2D5374C
#define __TYPE_H__98A93208_FE74_468C_A0B7_059AC2D5374C

#include "Global.h"

BEG_XE_NAMESPACE

class float16;
class Vec2;
class Vec3;
class Vec4;
class Quat;
class Mat3;
class Mat4;
class Rect;

class Color;
class FColor;

class Ray;
class OBB;
class AABB;
class Line;
class Plane;
class Sphere;
class Frustum;


enum class SideType
{
	NOOP,
	BOTH,
	POSITIVE,
	NEGATIVE,
};
DECL_META_ENUM( XE_API, SideType );

enum class AxisType : XE::uint8
{
	X = 1 << 0,
	Y = 1 << 1,
	Z = 1 << 2,
	XY = X | Y,
	XZ = X | Z,
	YZ = Y | Z,
	XYZ = X | Y | Z,
};
DECL_META_ENUM( XE_API, AxisType );

enum class RotationType
{
	XYZ,
	XZY,
	YXZ,
	YZX,
	ZXY,
	ZYX
};
DECL_META_ENUM( XE_API, RotationType );

template< typename _Ty > class MakeRect;
template< typename _Ty > class MakeAABB;

END_XE_NAMESPACE

#endif // __TYPE_H__98A93208_FE74_468C_A0B7_059AC2D5374C
