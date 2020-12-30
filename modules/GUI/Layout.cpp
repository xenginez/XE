#include "Layout.h"

#include "UserInterface.h"

BEG_META( GUI::Layout )
END_META()

GUI::Layout::Layout()
	:_TopMargin( 0 ), _LeftMargin( 0 ), _BottomMargin( 0 ), _RightMargin( 0 ), _WidgetSpacing( 0 ), _SizeConstraint( SizeConstraint::MINIMUM_SIZE )
	,_OnGeometryChanged( std::bind( &Layout::OnGeometryChanged, this, std::placeholders::_1 ) )
{
	XE::Connect( &GeometryChanged, &_OnGeometryChanged );
}

GUI::Layout::~Layout()
{
}

XE::uint32 GUI::Layout::GetLeftMargin() const
{
	return _LeftMargin;
}

void GUI::Layout::SetLeftMargin( XE::uint32 val )
{
	_LeftMargin = val;
}

XE::uint32 GUI::Layout::GetTopMargin() const
{
	return _TopMargin;
}

void GUI::Layout::SetTopMargin( XE::uint32 val )
{
	_TopMargin = val;
}

XE::uint32 GUI::Layout::GetBottomMargin() const
{
	return _BottomMargin;
}

void GUI::Layout::SetBottomMargin( XE::uint32 val )
{
	_BottomMargin = val;
}

XE::uint32 GUI::Layout::GetRightMargin() const
{
	return _RightMargin;
}

void GUI::Layout::SetRightMargin( XE::uint32 val )
{
	_RightMargin = val;
}

XE::uint32 GUI::Layout::GetWidgetSpacing() const
{
	return _WidgetSpacing;
}

void GUI::Layout::SetWidgetSpacing( XE::uint32 val )
{
	_WidgetSpacing = val;
}

GUI::SizeConstraint GUI::Layout::GetSizeConstraint() const
{
	return _SizeConstraint;
}

void GUI::Layout::SetSizeConstraint( GUI::SizeConstraint val )
{
	_SizeConstraint = val;
}

XE::uint8 GUI::Layout::GetStretch( XE::uint64 val ) const
{
	return _Children.at( val ).second;
}

void GUI::Layout::SetStretch( XE::uint64 index, XE::uint8 val )
{
	_Children.at( index ).second = val;
}

XE::Rectf GUI::Layout::GetContentsRect() const
{
	const XE::Rectf & rect = GetGeometry();

	return XE::Rectf( rect.x + _LeftMargin, rect.y + _TopMargin, rect.width - _RightMargin, rect.height - _BottomMargin );
}

XE::uint64 GUI::Layout::ChildCount() const
{
	return _Children.size();
}

void GUI::Layout::AddChild( WidgetHandle val )
{
	GetWidget( val )->SetParentHandle( GetHandle() );

	_Children.push_back( { val, 0 } );
}

void GUI::Layout::RemoveChild( WidgetHandle val )
{
	for( auto it = _Children.begin(); it != _Children.end(); ++it )
	{
		if( it->first == val )
		{
			GetWidget( it->first )->SetParentHandle( WidgetHandle::Invalid );

			_Children.erase( it );

			break;
		}
	}
}

GUI::WidgetPtr GUI::Layout::GetChild( XE::uint64 val ) const
{
	return GetWidget( GetChildHandle( val ) );
}

GUI::WidgetHandle GUI::Layout::GetChildHandle( XE::uint64 val ) const
{
	return _Children.at( val ).first;
}

GUI::WidgetPtr GUI::Layout::GetWidget( GUI::WidgetHandle val ) const
{
	return GetUserInterface()->GetWidget( val );
}

void GUI::Layout::Render()
{
	for( auto & pair : _Children )
	{
		GetWidget( pair.first )->Render();
	}
}
