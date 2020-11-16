/*!
 * \file   Vec2.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8
#define __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8

#include "Type.h"

BEG_XE_NAMESPACE

template< typename T > class alignas( 16 ) Vec2
{
public:
	using value_type = T;

public:
	static const Vec2< T > One;
	static const Vec2< T > Zero;

public:
	union
	{
		value_type d[2];
		struct { value_type x, y; };
	};

public:
	Vec2()
		:x( 0 ), y( 0 )
	{

	}

	Vec2( value_type val )
		: x( val ), y( val )
	{

	}

	Vec2( value_type x, value_type y )
		: x( x ), y( y )
	{

	}

	template< typename U > Vec2( const Vec2< U > & val )
		: x( val.x ), y( val.y )
	{

	}

public:
	Vec2 & operator=( value_type val )
	{
		x = val;
		y = val;
		return *this;
	}

	Vec2 & operator=( const Vec2 & val )
	{
		x = val.x;
		y = val.y;
		return *this;
	}

public:
	value_type & operator[]( XE::uint64 val )
	{
		XE_ASSERT( val < 2 );

		return d[val];
	}

	value_type operator[]( XE::uint64 val ) const
	{
		XE_ASSERT( val < 2 );

		return d[val];
	}
};

template< typename T >
const XE::Vec2<T> XE::Vec2<T>::One = { 1 , 1 };
template< typename T >
const XE::Vec2<T> XE::Vec2<T>::Zero = { 0 , 0 };

using Vec2i = Vec2<XE::int32>;
using Vec2f = Vec2<XE::float32>;
using Vec2d = Vec2<XE::float64>;

DECL_META_CLASS( XE_API, Vec2i );
DECL_META_CLASS( XE_API, Vec2f );
DECL_META_CLASS( XE_API, Vec2d );

END_XE_NAMESPACE

#endif // __VEC2_H__9268065A_1161_405E_9963_4C59BF7615D8
