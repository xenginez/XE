#include "Layout.h"

USING_XE

BEG_META( Layout )
END_META()

Layout::Layout()
	:_TopMargin( 0 ), _LeftMargin( 0 ), _BottomMargin( 0 ), _RightMargin( 0 ), _WidgetSpacing( 0 )
{
}

Layout::~Layout()
{
}

XE::real Layout::GetLeftMargin() const
{
	return _LeftMargin;
}

void Layout::SetLeftMargin( XE::real val )
{
	_LeftMargin = val;
}

XE::real Layout::GetTopMargin() const
{
	return _TopMargin;
}

void Layout::SetTopMargin( XE::real val )
{
	_TopMargin = val;
}

XE::real Layout::GetBottomMargin() const
{
	return _BottomMargin;
}

void Layout::SetBottomMargin( XE::real val )
{
	_BottomMargin = val;
}

XE::real Layout::GetRightMargin() const
{
	return _RightMargin;
}

void Layout::SetRightMargin( XE::real val )
{
	_RightMargin = val;
}

XE::real Layout::GetWidgetSpacing() const
{
	return _WidgetSpacing;
}

void Layout::SetWidgetSpacing( XE::real val )
{
	_WidgetSpacing = val;
}

XE::Rect Layout::GetContentsRect() const
{
	const Rect & rect = GetGeometry();

	return Rect( rect.x + _LeftMargin, rect.y + _TopMargin, rect.width - _RightMargin, rect.height - _BottomMargin );
}

XE::uint64 Layout::Count() const
{
	return _Widgets.size();
}

void Layout::AddWidget( const WidgetPtr & val )
{
	val->SetParent( XE_THIS( Widget ) );

	_Widgets.push_back( val );
}

void Layout::RemoveWidget( const WidgetPtr & val )
{
	for( auto it = _Widgets.begin(); it != _Widgets.end(); ++it )
	{
		if( *it == val )
		{
			( *it )->SetParent( nullptr );

			_Widgets.erase( it );

			break;
		}
	}
}

const XE::Array<WidgetPtr> & Layout::GetWidgets() const
{
	return _Widgets;
}

const WidgetPtr & Layout::GetWidget( XE::uint64 val ) const
{
	return _Widgets.at( val );
}

void Layout::Update()
{
	OnUpdate();

	for( auto & widget : _Widgets )
	{
		widget->Update();
	}
}

void Layout::Render()
{
	OnRender();

	for( auto & widget : _Widgets )
	{
		widget->Render();
	}
}

void Layout::OnUpdate()
{

}

void Layout::OnRender()
{

}
