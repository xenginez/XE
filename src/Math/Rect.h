/*!
 * \file   Rect.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RECT_H__CFAED4A1_7564_4C31_AC1F_E7BD88EE9157
#define __RECT_H__CFAED4A1_7564_4C31_AC1F_E7BD88EE9157

#include "Vec2.h"
#include "Mat4.h"

BEG_XE_NAMESPACE

template< typename T > class XE_API alignas( 16 ) Rect
{
public:
	using value_type = T;

public:
	static const Rect Zero;

public:
	value_type x;
	value_type y;
	value_type width;
	value_type height;

public:
	Rect()
		:x( 0 ), y( 0 ), width( 0 ), height( 0 )
	{

	}

	template< typename U > Rect( const Rect< U > & val )
		: x( val.x ), y( val.y ), width( val.width ), height( val.height )
	{

	}

	Rect( value_type x, value_type y, value_type w, value_type h )
		: x( x ), y( y ), width( w ), height( h )
	{

	}

	template< typename U > Rect( const Vec2< U > & center, const Vec2< U > & size )
		: x( center.x - size.x * 0.5f ), y( center.y - size.y * 0.5f ), width( size.x ), height( size.y )
	{

	}

public:
	template< typename U > Rect & operator=( const Rect< U > & val )
	{
		x = val.x;
		y = val.y;
		width = val.width;
		height = val.height;
		return *this;
	}

	template< typename U > bool operator ==( const Rect< U > & val ) const
	{
		return x == val.x && y == val.y && width == val.width && height == val.height;
	}

	template< typename U > bool operator !=( const Rect< U > & val ) const
	{
		return x != val.x || y != val.y || width != val.width || height != val.height;
	}

public:
	Vec2< value_type > GetMin() const
	{
		return { x, y };
	}

	Vec2< value_type > GetMax() const
	{
		return{ x + width, y + height };
	}

	Vec2< value_type > GetSize() const
	{
		return { width, height };
	}

	Vec2< value_type > GetCenter() const
	{
		return { x + width * 0.5f, y + height * 0.5f };
	}

public:
	bool Contains( const Vec2< value_type > & val ) const
	{
		return ( val.x > x && val.x < ( x + width ) &&
				 val.y > y && val.y < ( y + height ) );
	}

	bool Contains( const Rect< value_type > & val ) const
	{
		return ( val.x > x && val.width < width &&
				 val.y > y && val.height < height );
	}

public:
	bool Intersect( const Rect< value_type > & val ) const
	{
		XE::float32 minx = std::max( x, val.x );
		XE::float32 miny = std::max( y, val.y );
		XE::float32 maxx = std::min( x + width, val.x + val.width );
		XE::float32 maxy = std::min( y + height, val.y + val.height );

		return !( minx > maxx || miny > maxy );
	}

	bool Intersect( const Vec2< value_type > & beg, const Vec2< value_type > & end )const
	{
		auto line_intersect = []( const Vec2f & beg1, const Vec2f & end1, const Vec2f & beg2, const Vec2f & end2 )
		{
			float32 x1 = beg1.x;
			float32 y1 = beg1.y;
			float32 x2 = end1.x;
			float32 y2 = end1.y;
			float32 x3 = beg2.x;
			float32 y3 = beg2.y;
			float32 x4 = end2.x;
			float32 y4 = end2.y;

			if( ( ( x1 * y3 + x2 * y1 + x3 * y2 - x1 * y2 - x2 * y3 - x3 * y1 ) * ( x1 * y4 + x2 * y1 + x4 * y2 - x1 * y2 - x2 * y4 - x4 * y1 ) ) > 0 )
			{
				return false;
			}

			if( ( ( x3 * y1 + x4 * y3 + x1 * y4 - x3 * y4 - x4 * y1 - x1 * y3 ) * ( x3 * y2 + x4 * y3 + x2 * y4 - x3 * y4 - x4 * y2 - x2 * y3 ) ) > 0 )
			{
				return false;
			}

			return true;
		};

		if( line_intersect( beg, end, Vec2f( x, y ), Vec2f( x, y + height ) ) )
		{
			return true;
		}

		if( line_intersect( beg, end, Vec2f( x, y + height ), Vec2f( x + width, y + height ) ) )
		{
			return true;
		}

		if( line_intersect( beg, end, Vec2f( x + width, y + height ), Vec2f( x + width, y ) ) )
		{
			return true;
		}

		if( line_intersect( beg, end, Vec2f( x + width, y ), Vec2f( x, y ) ) )
		{
			return true;
		}

		return false;
	}

public:
	void Clip( const Rect< value_type > & val )
	{
		XE::float32 newLeft = std::max( x, val.x );
		XE::float32 newTop = std::max( y, val.y );

		XE::float32 newRight = std::min( x + width, val.x + val.width );
		XE::float32 newBottom = std::min( y + height, val.y + val.height );

		x = newLeft;
		y = newTop;
		width = newRight - newLeft;
		height = newBottom - newTop;
	}

	void Encapsulate( const Rect< value_type > & val )
	{
		XE::float32 myRight = x + width;
		XE::float32 myBottom = y + height;
		XE::float32 otherRight = val.x + val.width;
		XE::float32 otherBottom = val.y + val.height;

		if( val.x < x )
			x = val.x;

		if( val.y < y )
			y = val.y;

		if( otherRight > myRight )
			width = otherRight - x;
		else
			width = myRight - x;

		if( otherBottom > myBottom )
			height = otherBottom - y;
		else
			height = myBottom - y;
	}

public:
	void Transform( const Mat4< value_type > & val )
	{
		Vec4f verts[4];
		verts[0] = Vec4f( x, y, 0.0f, 1.0f );
		verts[1] = Vec4f( x + width, y, 0.0f, 1.0f );
		verts[2] = Vec4f( x, y + height, 0.0f, 1.0f );
		verts[3] = Vec4f( x + width, y + height, 0.0f, 1.0f );

		for( XE::uint32 i = 0; i < 4; i++ )
			verts[i] = val * verts[i];

		XE::float32 minX = std::numeric_limits<XE::float32>::max();
		XE::float32 maxX = std::numeric_limits<XE::float32>::min();
		XE::float32 minY = std::numeric_limits<XE::float32>::max();
		XE::float32 maxY = std::numeric_limits<XE::float32>::min();

		for( XE::uint32 i = 0; i < 4; i++ )
		{
			if( verts[i].x < minX )
				minX = verts[i].x;

			if( verts[i].y < minY )
				minY = verts[i].y;

			if( verts[i].x > maxX )
				maxX = verts[i].x;

			if( verts[i].y > maxY )
				maxY = verts[i].y;
		}

		x = minX;
		y = minY;
		width = maxX - x;
		height = maxY - y;
	}

};

template< typename T > const XE::Rect< T > XE::Rect< T >::Zero = { 0, 0, 0, 0 };

using Recti = Rect< XE::int32 >;
using Rectf = Rect< XE::float32 >;
using Rectd = Rect< XE::float64 >;

DECL_META_CLASS( XE_API, Recti );
DECL_META_CLASS( XE_API, Rectf );
DECL_META_CLASS( XE_API, Rectd );

END_XE_NAMESPACE

#endif // __RECT_H__CFAED4A1_7564_4C31_AC1F_E7BD88EE9157
