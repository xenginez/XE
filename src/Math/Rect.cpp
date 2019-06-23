#include "Rect.h"

#include "Mathf.h"

USING_XE

BEG_META( Rect )
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

XE::Rect::Rect( XE::real x, XE::real y, XE::real w, XE::real h )
	: x( x ), y( y ), width( w ), height( h )
{

}

Rect& XE::Rect::operator=( const Rect& val )
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

Vec2 XE::Rect::GetMin() const
{
	return { x, y };
}

Vec2 XE::Rect::GetMax() const
{
	return{ x + width, y + height };
}

Vec2 XE::Rect::GetSize() const
{
	return { width, height };
}

Vec2 XE::Rect::GetCenter() const
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

bool XE::Rect::Intersects( const Rect& val ) const
{
	XE::real minx = Mathf::Max( x, val.x );
	XE::real miny = Mathf::Max( y, val.y );
	XE::real maxx = Mathf::Min( x + width, val.x + val.width );
	XE::real maxy = Mathf::Min( y + height, val.y + val.height );

	return !( minx > maxx || miny > maxy );
}

void XE::Rect::Clip( const Rect& val )
{
	XE::real newLeft = Mathf::Max( x, val.x );
	XE::real newTop = Mathf::Max( y, val.y );

	XE::real newRight = Mathf::Min( x + width, val.x + val.width );
	XE::real newBottom = Mathf::Min( y + height, val.y + val.height );

	x = newLeft;
	y = newTop;
	width = newRight - newLeft;
	height = newBottom - newTop;
}

void XE::Rect::Encapsulate( const Rect& val )
{
	XE::real myRight = x + width;
	XE::real myBottom = y + height;
	XE::real otherRight = val.x + val.width;
	XE::real otherBottom = val.y + val.height;

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

	XE::real minX = std::numeric_limits<XE::real>::max();
	XE::real maxX = std::numeric_limits<XE::real>::min();
	XE::real minY = std::numeric_limits<XE::real>::max();
	XE::real maxY = std::numeric_limits<XE::real>::min();

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
