#include "Viewport.h"

USING_XE

BEG_META(Viewport)
END_META()

XE::Viewport::Viewport()
{

}

XE::Viewport::~Viewport()
{

}

XE::real XE::Viewport::GetX() const
{
	return _Rect.x;
}

void XE::Viewport::SetX( XE::real val )
{
	_Rect.x = val;
}

XE::real XE::Viewport::GetY() const
{
	return _Rect.y;
}

void XE::Viewport::SetY( XE::real val )
{
	_Rect.y = val;
}

XE::real XE::Viewport::GetWidth() const
{
	return _Rect.width;
}

void XE::Viewport::SetWidth( XE::real val )
{
	_Rect.width = val;
}

XE::real XE::Viewport::GetHeight() const
{
	return _Rect.height;
}

void XE::Viewport::SetHeight( XE::real val )
{
	_Rect.height = val;
}

const XE::Rect &XE::Viewport::GetRect() const
{
	return _Rect;
}

void XE::Viewport::SetRect( const Rect & val )
{
	_Rect = val;
}

XE::real XE::Viewport::GetMinDepth() const
{
	return _Depth.x;
}

void XE::Viewport::SetMinDepth( XE::real val )
{
	_Depth.x = val;
}

XE::real XE::Viewport::GetMaxDepth() const
{
	return _Depth.y;
}

void XE::Viewport::SetMaxDepth( XE::real val )
{
	_Depth.y = val;
}

const XE::Vec2 & XE::Viewport::GetDepth() const
{
	return _Depth;
}

void XE::Viewport::SetDepth( const Vec2 & val )
{
	_Depth = val;
}
