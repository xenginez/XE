#include "SpacerItem.h"

BEG_META( GUI::SpacerItem )
END_META()

GUI::SpacerItem::SpacerItem()
	:_Orientation( Orientation::HORIZONTAL ), _SizePolicy( SizePolicy::EXPANDING )
{

}

GUI::SpacerItem::~SpacerItem()
{

}

GUI::SizePolicy GUI::SpacerItem::GetSizePolicy() const
{
	return _SizePolicy;
}

void GUI::SpacerItem::SetSizePolicy( GUI::SizePolicy val )
{
	_SizePolicy = val;
}

GUI::Orientation GUI::SpacerItem::GetOrientation() const
{
	return _Orientation;
}

void GUI::SpacerItem::SetOrientation( GUI::Orientation val )
{
	_Orientation = val;
}

const XE::Vec2i & GUI::SpacerItem::GetSizeHint() const
{
	return _SizeHint;
}

void GUI::SpacerItem::SetSizeHint( const XE::Vec2i & val )
{
	_SizeHint = val;
}

XE::Vec2i GUI::SpacerItem::SizeHint() const
{
	if (_SizePolicy == GUI::SizePolicy::FIXED)
	{
		return _SizeHint;
	}

	return GetMaximumSize();
}
