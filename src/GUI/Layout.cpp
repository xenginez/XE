#include "Layout.h"

#include "UserInterface.h"


XE::Layout::Layout()
	:_TopMargin( 0 ), _LeftMargin( 0 ), _BottomMargin( 0 ), _RightMargin( 0 ), _WidgetSpacing( 0 ), _SizeConstraint( SizeConstraint::MINIMUM_SIZE )
{
}

XE::Layout::~Layout()
{
}

XE::real XE::Layout::GetLeftMargin() const
{
	return _LeftMargin;
}

void XE::Layout::SetLeftMargin( XE::real val )
{
	_LeftMargin = val;
}

XE::real XE::Layout::GetTopMargin() const
{
	return _TopMargin;
}

void XE::Layout::SetTopMargin( XE::real val )
{
	_TopMargin = val;
}

XE::real XE::Layout::GetBottomMargin() const
{
	return _BottomMargin;
}

void XE::Layout::SetBottomMargin( XE::real val )
{
	_BottomMargin = val;
}

XE::real XE::Layout::GetRightMargin() const
{
	return _RightMargin;
}

void XE::Layout::SetRightMargin( XE::real val )
{
	_RightMargin = val;
}

XE::real XE::Layout::GetWidgetSpacing() const
{
	return _WidgetSpacing;
}

void XE::Layout::SetWidgetSpacing( XE::real val )
{
	_WidgetSpacing = val;
}

XE::SizeConstraint XE::Layout::GetSizeConstraint() const
{
	return _SizeConstraint;
}

void XE::Layout::SetSizeConstraint( XE::SizeConstraint val )
{
	_SizeConstraint = val;
}

XE::uint8 XE::Layout::GetStretch( XE::uint64 val ) const
{
	return _Children.at( val ).second;
}

void XE::Layout::SetStretch( XE::uint64 index, XE::uint8 val )
{
	_Children.at( index ).second = val;
}

XE::Rect XE::Layout::GetContentsRect() const
{
	const Rect & rect = GetGeometry();

	return Rect( rect.x + _LeftMargin, rect.y + _TopMargin, rect.width - _RightMargin, rect.height - _BottomMargin );
}

XE::uint64 XE::Layout::ChildCount() const
{
	return _Children.size();
}

void XE::Layout::AddChild( WidgetHandle val )
{
	GetWidget( val )->SetParentHandle( GetHandle() );

	_Children.push_back( { val, 0 } );
}

void XE::Layout::RemoveChild( WidgetHandle val )
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

XE::WidgetPtr XE::Layout::GetChild( XE::uint64 val ) const
{
	return GetWidget( GetChildHandle( val ) );
}

XE::WidgetHandle XE::Layout::GetChildHandle( XE::uint64 val ) const
{
	return _Children.at( val ).first;
}

XE::WidgetPtr XE::Layout::GetWidget( XE::WidgetHandle val ) const
{
	return GetUserInterface()->GetWidget( val );
}

void XE::Layout::Render()
{
	OnRender();

	for( auto & pair : _Children )
	{
		GetWidget( pair.first )->Render();
	}
}

void XE::Layout::OnRender()
{

}
