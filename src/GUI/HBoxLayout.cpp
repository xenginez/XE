#include "HBoxLayout.h"


XE::HBoxLayout::HBoxLayout()
	:_OnGeometryChanged( std::bind( &HBoxLayout::OnGeometryChanged, this, std::placeholders::_1 ) )
{
	XE::Connect( &GeometryChanged, &_OnGeometryChanged );
}

XE::HBoxLayout::~HBoxLayout()
{

}

void XE::HBoxLayout::OnGeometryChanged( const XE::Rect & val )
{
	if( ChildCount() == 0 )
	{
		return;
	}

	auto c_rect = GetContentsRect();

	for( int i = 0; i < ChildCount(); ++i )
	{

	}

	for( int i = 0; i < ChildCount(); ++i )
	{
		GetChild( i )->SetGeometry( {} );
	}
}
