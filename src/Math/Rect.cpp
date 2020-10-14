#include "Rect.h"

#include "Mathf.h"

BEG_META( XE::Rect )
END_META()

const XE::Rect XE::Rect::Zero = { 0, 0, 0, 0 };

XE::Rect::Rect()
	:x( 0 ), y( 0 ), width( 0 ), height( 0 )
{

}

XE::Rect::Rect( const Rect& val )
	: x( val.x ), y( val.y ), width( val.width ), height( val.height )
{

}

XE::Rect::Rect( const Vec2& center, const Vec2& size )
	: x( center.x - size.x * 0.5f ), y( center.y - size.y * 0.5f ), width( size.x ), height( size.y )
{

}

XE::Rect::Rect( XE::float32 x, XE::float32 y, XE::float32 w, XE::float32 h )
	: x( x ), y( y ), width( w ), height( h )
{

}

XE::Rect& XE::Rect::operator=( const Rect& val )
{
	x = val.x;
	y = val.y;
	width = val.width;
	height = val.height;
	return *this;
}

bool XE::Rect::operator==( const Rect& val ) const
{
	return x == val.x && y == val.y && width == val.width && height == val.height;
}

bool XE::Rect::operator!=( const Rect& val ) const
{
	return x != val.x || y != val.y || width != val.width || height != val.height;
}

XE::Vec2 XE::Rect::GetMin() const
{
	return { x, y };
}

XE::Vec2 XE::Rect::GetMax() const
{
	return{ x + width, y + height };
}

XE::Vec2 XE::Rect::GetSize() const
{
	return { width, height };
}

XE::Vec2 XE::Rect::GetCenter() const
{
	return { x + width * 0.5f, y + height * 0.5f };
}

bool XE::Rect::Contains( const Vec2& val ) const
{
	return ( val.x > x && val.x < ( x + width ) &&
			 val.y > y && val.y < ( y + height ) );
}

bool XE::Rect::Contains( const Rect & val ) const
{
	return ( val.x > x && val.width < width &&
			 val.y > y && val.height < height );
}

bool XE::Rect::Intersect( const Rect& val ) const
{
	XE::float32 minx = Mathf::Max( x, val.x );
	XE::float32 miny = Mathf::Max( y, val.y );
	XE::float32 maxx = Mathf::Min( x + width, val.x + val.width );
	XE::float32 maxy = Mathf::Min( y + height, val.y + val.height );

	return !( minx > maxx || miny > maxy );
}

bool XE::Rect::Intersect( const Vec2 & beg, const Vec2 & end ) const
{
	auto line_intersect = []( const Vec2 & beg1, const Vec2 & end1, const Vec2 & beg2, const Vec2 & end2 )
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

	if( line_intersect( beg, end, Vec2( x, y ), Vec2( x, y + height ) ) )
	{
		return true;
	}

	if( line_intersect( beg, end, Vec2( x, y + height ), Vec2( x + width, y + height ) ) )
	{
		return true;
	}

	if( line_intersect( beg, end, Vec2( x + width, y + height ), Vec2( x + width, y ) ) )
	{
		return true;
	}

	if( line_intersect( beg, end, Vec2( x + width, y ), Vec2( x, y ) ) )
	{
		return true;
	}

	return false;
}

void XE::Rect::Clip( const Rect& val )
{
	XE::float32 newLeft = Mathf::Max( x, val.x );
	XE::float32 newTop = Mathf::Max( y, val.y );

	XE::float32 newRight = Mathf::Min( x + width, val.x + val.width );
	XE::float32 newBottom = Mathf::Min( y + height, val.y + val.height );

	x = newLeft;
	y = newTop;
	width = newRight - newLeft;
	height = newBottom - newTop;
}

void XE::Rect::Encapsulate( const Rect& val )
{
	XE::float32 myRight = x + width;
	XE::float32 myBottom = y + height;
	XE::float32 otherRight = val.x + val.width;
	XE::float32 otherBottom = val.y + val.height;

	if ( val.x < x )
		x = val.x;

	if ( val.y < y )
		y = val.y;

	if ( otherRight > myRight )
		width = otherRight - x;
	else
		width = myRight - x;

	if ( otherBottom > myBottom )
		height = otherBottom - y;
	else
		height = myBottom - y;
}

void XE::Rect::Transform( const Mat4& val )
{
	Vec4 verts[4];
	verts[0] = Vec4( x, y, 0.0f, 1.0f );
	verts[1] = Vec4( x + width, y, 0.0f, 1.0f );
	verts[2] = Vec4( x, y + height, 0.0f, 1.0f );
	verts[3] = Vec4( x + width, y + height, 0.0f, 1.0f );

	for ( XE::uint32 i = 0; i < 4; i++ )
		verts[i] = val * verts[i];

	XE::float32 minX = std::numeric_limits<XE::float32>::max();
	XE::float32 maxX = std::numeric_limits<XE::float32>::min();
	XE::float32 minY = std::numeric_limits<XE::float32>::max();
	XE::float32 maxY = std::numeric_limits<XE::float32>::min();

	for ( XE::uint32 i = 0; i < 4; i++ )
	{
		if ( verts[i].x < minX )
			minX = verts[i].x;

		if ( verts[i].y < minY )
			minY = verts[i].y;

		if ( verts[i].x > maxX )
			maxX = verts[i].x;

		if ( verts[i].y > maxY )
			maxY = verts[i].y;
	}

	x = minX;
	y = minY;
	width = maxX - x;
	height = maxY - y;
}
