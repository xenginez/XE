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

XE::Rect::Rect( const Vec2& min, const Vec2& max )
	: x( min.x ), y( min.y ), width( max.x - min.x ), height( max.y - min.y )
{

}

XE::Rect::Rect( float x, float y, float w, float h )
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

bool XE::Rect::contains( const Vec2& val ) const
{
	if ( val.x >= x && val.x <= ( x + width ) )
	{
		if ( val.y >= y && val.y <= ( y + height ) )
		{
			return true;
		}
	}

	return false;
}

bool XE::Rect::overlaps( const Rect& val ) const
{
	float otherRight = val.x + val.width;
	float myRight = x + width;

	float otherBottom = val.y + val.height;
	float myBottom = y + height;

	if ( x < otherRight && myRight > val.x && y < otherBottom && myBottom > val.y )
	{
		return true;
	}

	return false;
}

void XE::Rect::clip( const Rect& val )
{
	float newLeft = Mathf::Max( x, val.x );
	float newTop = Mathf::Max( y, val.y );

	float newRight = Mathf::Min( x + width, val.x + val.width );
	float newBottom = Mathf::Min( y + height, val.y + val.height );

	x = newLeft;
	y = newTop;
	width = newRight - newLeft;
	height = newBottom - newTop;
}

void XE::Rect::encapsulate( const Rect& val )
{
	float myRight = x + width;
	float myBottom = y + height;
	float otherRight = val.x + val.width;
	float otherBottom = val.y + val.height;

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

	for ( uint32 i = 0; i < 4; i++ )
		verts[i] = val * verts[i];

	float minX = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::min();

	for ( uint32 i = 0; i < 4; i++ )
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
