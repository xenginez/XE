#include "HBoxLayout.h"

USING_XE

BEG_META( HBoxLayout )
END_META()

HBoxLayout::HBoxLayout()
	:_OnGeometryChanged( std::bind( &HBoxLayout::OnGeometryChanged, this, std::placeholders::_1 ) )
{
	GeometryChanged.connect( _OnGeometryChanged );
}

HBoxLayout::~HBoxLayout()
{

}

void HBoxLayout::OnGeometryChanged( const XE::Rect & val )
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
