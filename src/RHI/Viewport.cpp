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

XE::float32 XE::Viewport::GetX() const
{
	return _Rect.x;
}

void XE::Viewport::SetX( XE::float32 val )
{
	_Rect.x = val;
}

XE::float32 XE::Viewport::GetY() const
{
	return _Rect.y;
}

void XE::Viewport::SetY( XE::float32 val )
{
	_Rect.y = val;
}

XE::float32 XE::Viewport::GetWidth() const
{
	return _Rect.width;
}

void XE::Viewport::SetWidth( XE::float32 val )
{
	_Rect.width = val;
}

XE::float32 XE::Viewport::GetHeight() const
{
	return _Rect.height;
}

void XE::Viewport::SetHeight( XE::float32 val )
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

XE::float32 XE::Viewport::GetMinDepth() const
{
	return _Depth.x;
}

void XE::Viewport::SetMinDepth( XE::float32 val )
{
	_Depth.x = val;
}

XE::float32 XE::Viewport::GetMaxDepth() const
{
	return _Depth.y;
}

void XE::Viewport::SetMaxDepth( XE::float32 val )
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

XE::RenderTargetPtr XE::Viewport::GetRenderTarget() const
{
	return _RenderTarget.lock();
}
