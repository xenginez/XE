#include "Widget.h"

BEG_META( XE::Widget )
END_META()

XE::Widget::Widget()
	:_Enable( true ), _MinSize( XE::Vec2f::Zero ), _MaxSize( std::numeric_limits<XE::float32>::max() )
{

}

XE::Widget::~Widget()
{

}

bool XE::Widget::GetEnable() const
{
	return _Enable;
}

void XE::Widget::SetEnable( bool val )
{
	_Enable = val;
}

const XE::String & XE::Widget::GetName() const
{
	return _Name;
}

void XE::Widget::SetName( const XE::String & val )
{
	_Name = val;
}

XE::WidgetHandle XE::Widget::GetHandle() const
{
	return _Handle;
}

void XE::Widget::SetHandle( XE::WidgetHandle val )
{
	_Handle = val;
}

XE::WidgetHandle XE::Widget::GetParentHandle() const
{
	return _ParentHandle;
}

void XE::Widget::SetParentHandle( XE::WidgetHandle val )
{
	_ParentHandle = val;
}

const XE::UserInterfacePtr & XE::Widget::GetUserInterface() const
{
	return _UI;
}

void XE::Widget::SetUserInterface( const XE::UserInterfacePtr & val )
{
	_UI = val;
}

XE::Vec2f XE::Widget::GetSize() const
{
	return { _Geometry.width, _Geometry.height };
}

void XE::Widget::SetSize( const XE::Vec2f & val )
{
	auto rect = _Geometry;
	rect.width = val.x;
	rect.height = val.y;

	SetGeometry( rect );
}

XE::Vec2f XE::Widget::GetPosition() const
{
	return { _Geometry.x, _Geometry.y };
}

void XE::Widget::SetPosition( const XE::Vec2f & val )
{
	auto rect = _Geometry;
	rect.x = val.x;
	rect.y = val.y;

	SetGeometry( rect );
}

const XE::Vec2f & XE::Widget::GetMinimumSize() const
{
	return _MinSize;
}

void XE::Widget::SetMinimunSize( const XE::Vec2f & val )
{
	_MinSize = val;
}

const XE::Vec2f & XE::Widget::GetMaximumSize() const
{
	return _MaxSize;
}

void XE::Widget::SetMaximunSize( const XE::Vec2f & val )
{
	_MaxSize = val;
}

const XE::Rectf & XE::Widget::GetGeometry() const
{
	return _Geometry;
}

void XE::Widget::SetGeometry( const XE::Rectf & val )
{
	_Geometry = val;

	GeometryChanged( val );
}

void XE::Widget::Render()
{

}

void XE::Widget::OnRemove()
{

}

XE::Vec2f XE::Widget::SizeHint() const
{
	return _MinSize;
}
