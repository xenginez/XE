#include "Layout.h"

#include "UserInterface.h"

USING_XE

BEG_META( Layout )
END_META()

Layout::Layout()
	:_TopMargin( 0 ), _LeftMargin( 0 ), _BottomMargin( 0 ), _RightMargin( 0 ), _WidgetSpacing( 0 ), _SizeConstraint( SizeConstraint::MINIMUM_SIZE )
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

SizeConstraint Layout::GetSizeConstraint() const
{
	return _SizeConstraint;
}

void Layout::SetSizeConstraint( SizeConstraint val )
{
	_SizeConstraint = val;
}

XE::uint8 Layout::GetStretch( XE::uint64 val ) const
{
	return _Children.at( val ).second;
}

void Layout::SetStretch( XE::uint64 index, XE::uint8 val )
{
	_Children.at( index ).second = val;
}

XE::Rect Layout::GetContentsRect() const
{
	const Rect & rect = GetGeometry();

	return Rect( rect.x + _LeftMargin, rect.y + _TopMargin, rect.width - _RightMargin, rect.height - _BottomMargin );
}

XE::uint64 Layout::ChildCount() const
{
	return _Children.size();
}

void Layout::AddChild( WidgetHandle val )
{
	GetWidget( val )->SetParentHandle( GetHandle() );

	_Children.push_back( { val, 0 } );
}

void Layout::RemoveChild( WidgetHandle val )
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

WidgetPtr Layout::GetChild( XE::uint64 val ) const
{
	return GetWidget( GetChildHandle( val ) );
}

WidgetHandle Layout::GetChildHandle( XE::uint64 val ) const
{
	return _Children.at( val ).first;
}

WidgetPtr Layout::GetWidget( WidgetHandle val ) const
{
	return GetUserInterface()->GetWidget( val );
}

void Layout::Render()
{
	OnRender();

	for( auto & pair : _Children )
	{
		GetWidget( pair.first )->Render();
	}
}

void Layout::OnRender()
{

}
