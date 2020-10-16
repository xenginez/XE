#include "HBoxLayout.h"

BEG_META( HBoxLayout )
END_META()

XE::HBoxLayout::HBoxLayout()
{
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
