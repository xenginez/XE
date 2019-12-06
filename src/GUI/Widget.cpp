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

const WidgetPtr & Widget::GetParent() const
{
	return _Parent;
}

void Widget::SetParent( const WidgetPtr & val )
{
	_Parent = val;
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

const XE::Rect & Widget::GetBoundingRect() const
{
	return _BoundingRect;
}

void Widget::SetBoundingRect( const XE::Rect & val )
{
	_BoundingRect = val;
}

void Widget::Update()
{

}

void Widget::Render()
{

}
