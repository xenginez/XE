#include "SpacerItem.h"

USING_XE

BEG_META( SpacerItem )
END_META()

SpacerItem::SpacerItem()
	:_Orientation( Orientation::HORIZONTAL ), _SizePolicy( SizePolicy::EXPANDING )
{

}

SpacerItem::~SpacerItem()
{

}

SizePolicy SpacerItem::GetSizePolicy() const
{
	return _SizePolicy;
}

void SpacerItem::SetSizePolicy( SizePolicy val )
{
	_SizePolicy = val;
}

Orientation SpacerItem::GetOrientation() const
{
	return _Orientation;
}

void SpacerItem::SetOrientation( Orientation val )
{
	_Orientation = val;
}

const XE::Vec2 & SpacerItem::GetSizeHint() const
{
	return _SizeHint;
}

void SpacerItem::SetSizeHint( const XE::Vec2 & val )
{
	_SizeHint = val;
}

XE::Vec2 SpacerItem::SizeHint() const
{
	if (_SizePolicy == SizePolicy::FIXED)
	{
		return _SizeHint;
	}

	return GetMaximumSize();
}
