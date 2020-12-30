#include "HBoxLayout.h"

BEG_META( GUI::HBoxLayout )
END_META()

GUI::HBoxLayout::HBoxLayout()
{
}

GUI::HBoxLayout::~HBoxLayout()
{

}

void GUI::HBoxLayout::OnGeometryChanged( const XE::Recti & val )
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
