#include "Widget.h"

BEG_META( GUI::Widget )
END_META()

GUI::Widget::Widget()
	:_Enable( true ), _MinSize( XE::Vec2i::Zero ), _MaxSize( std::numeric_limits<XE::float32>::max() )
{

}

GUI::Widget::~Widget()
{

}

bool GUI::Widget::GetEnable() const
{
	return _Enable;
}

void GUI::Widget::SetEnable( bool val )
{
	_Enable = val;
}

const XE::String & GUI::Widget::GetName() const
{
	return _Name;
}

void GUI::Widget::SetName( const XE::String & val )
{
	_Name = val;
}

GUI::WidgetHandle GUI::Widget::GetHandle() const
{
	return _Handle;
}

void GUI::Widget::SetHandle( GUI::WidgetHandle val )
{
	_Handle = val;
}

GUI::WidgetHandle GUI::Widget::GetParentHandle() const
{
	return _ParentHandle;
}

void GUI::Widget::SetParentHandle( GUI::WidgetHandle val )
{
	_ParentHandle = val;
}

const GUI::UserInterfacePtr & GUI::Widget::GetUserInterface() const
{
	return _UI;
}

void GUI::Widget::SetUserInterface( const GUI::UserInterfacePtr & val )
{
	_UI = val;
}

XE::Vec2i GUI::Widget::GetSize() const
{
	return { _Geometry.width, _Geometry.height };
}

void GUI::Widget::SetSize( const XE::Vec2i & val )
{
	auto rect = _Geometry;
	rect.width = val.x;
	rect.height = val.y;

	SetGeometry( rect );
}

XE::Vec2i GUI::Widget::GetPosition() const
{
	return { _Geometry.x, _Geometry.y };
}

void GUI::Widget::SetPosition( const XE::Vec2i & val )
{
	auto rect = _Geometry;
	rect.x = val.x;
	rect.y = val.y;

	SetGeometry( rect );
}

const XE::Vec2i & GUI::Widget::GetMinimumSize() const
{
	return _MinSize;
}

void GUI::Widget::SetMinimunSize( const XE::Vec2i & val )
{
	_MinSize = val;
}

const XE::Vec2i & GUI::Widget::GetMaximumSize() const
{
	return _MaxSize;
}

void GUI::Widget::SetMaximunSize( const XE::Vec2i & val )
{
	_MaxSize = val;
}

const XE::Recti & GUI::Widget::GetGeometry() const
{
	return _Geometry;
}

void GUI::Widget::SetGeometry( const XE::Recti & val )
{
	_Geometry = val;

	GeometryChanged( val );
}

void GUI::Widget::Render()
{

}

void GUI::Widget::OnRemove()
{

}

XE::Vec2i GUI::Widget::SizeHint() const
{
	return _MinSize;
}
