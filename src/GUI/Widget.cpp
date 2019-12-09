#include "Widget.h"

USING_XE

BEG_META( Widget )
END_META()

XE::Widget::Widget()
	:_Enable( true ), _MinSize( XE::Vec2::Zero ), _MaxSize( std::numeric_limits<XE::real>::max() )
{

}

XE::Widget::~Widget()
{

}

bool Widget::GetEnable() const
{
	return _Enable;
}

void Widget::SetEnable( bool val )
{
	_Enable = val;
}

const XE::String & Widget::GetName() const
{
	return _Name;
}

void Widget::SetName( const XE::String & val )
{
	_Name = val;
}

WidgetHandle Widget::GetHandle() const
{
	return _Handle;
}

void Widget::SetHandle( WidgetHandle val )
{
	_Handle = val;
}

WidgetHandle Widget::GetParentHandle() const
{
	return _ParentHandle;
}

void Widget::SetParentHandle( WidgetHandle val )
{
	_ParentHandle = val;
}

const UserInterfacePtr & Widget::GetUserInterface() const
{
	return _UI;
}

void Widget::SetUserInterface( const UserInterfacePtr & val )
{
	_UI = val;
}

XE::Vec2 Widget::GetSize() const
{
	return { _Geometry.width, _Geometry.height };
}

void Widget::SetSize( const XE::Vec2 & val )
{
	auto rect = _Geometry;
	rect.width = val.x;
	rect.height = val.y;

	SetGeometry( rect );
}

XE::Vec2 Widget::GetPosition() const
{
	return { _Geometry.x, _Geometry.y };
}

void Widget::SetPosition( const XE::Vec2 & val )
{
	auto rect = _Geometry;
	rect.x = val.x;
	rect.y = val.y;

	SetGeometry( rect );
}

const XE::Vec2 & Widget::GetMinimumSize() const
{
	return _MinSize;
}

void Widget::SetMinimunSize( const XE::Vec2 & val )
{
	_MinSize = val;
}

const XE::Vec2 & Widget::GetMaximumSize() const
{
	return _MaxSize;
}

void Widget::SetMaximunSize( const XE::Vec2 & val )
{
	_MaxSize = val;
}

const XE::Rect & Widget::GetGeometry() const
{
	return _Geometry;
}

void Widget::SetGeometry( const XE::Rect & val )
{
	_Geometry = val;

	GeometryChanged( val );
}

void Widget::Render()
{

}

void Widget::OnRemove()
{

}

XE::Vec2 Widget::SizeHint() const
{
	return _MinSize;
}
