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
		struct { float x, y, z, w; };
		float d[4];
	};

public:
	Quat();

	Quat( const Quat& val );

	Quat( float x, float y, float z, float w );

public:
	Quat& operator=( const Quat& val );

public:
	float& operator[]( XE::uint64 val )
	{
		return d[val];
	}

	float operator[]( XE::uint64 val ) const
	{
		return d[val];
	}

};
DECL_META_CLASS( MATH_API, Quat );

END_XE_NAMESAPCE

#endif // __QUAT_H__4B922B3C_9B10_4EEB_91DF_1D1BCE288FDE
