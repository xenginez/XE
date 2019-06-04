/*!
 * \file   Quat.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __QUAT_H__4B922B3C_9B10_4EEB_91DF_1D1BCE288FDE
#define __QUAT_H__4B922B3C_9B10_4EEB_91DF_1D1BCE288FDE

#include "Type.h"

BEG_XE_NAMESPACE

class MATH_API Quat
{
public:
	static const Quat Zero;
	static const Quat Identity;

public:
	union
	{
		struct { XE::float32 x, y, z, w; };
		XE::float32 d[4];
	};

public:
	Quat();

	Quat( const Quat& val );

	Quat( XE::float32 x, XE::float32 y, XE::float32 z, XE::float32 w );

public:
	Quat& operator=( const Quat& val );

public:
	XE::float32& operator[]( XE::uint64 val )
	{
		return d[val];
	}

	XE::float32 operator[]( XE::uint64 val ) const
	{
		return d[val];
	}

};
DECL_META_CLASS( MATH_API, Quat );

END_XE_NAMESPACE

#endif // __QUAT_H__4B922B3C_9B10_4EEB_91DF_1D1BCE288FDE
