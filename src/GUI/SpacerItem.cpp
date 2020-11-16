#include "SpacerItem.h"

BEG_META( XE::SpacerItem )
END_META()

XE::SpacerItem::SpacerItem()
	:_Orientation( Orientation::HORIZONTAL ), _SizePolicy( SizePolicy::EXPANDING )
{

}

XE::SpacerItem::~SpacerItem()
{

}

XE::SizePolicy XE::SpacerItem::GetSizePolicy() const
{
	return _SizePolicy;
}

void XE::SpacerItem::SetSizePolicy( XE::SizePolicy val )
{
	_SizePolicy = val;
}

XE::Orientation XE::SpacerItem::GetOrientation() const
{
	return _Orientation;
}

void XE::SpacerItem::SetOrientation( XE::Orientation val )
{
	_Orientation = val;
}

const XE::Vec2f & XE::SpacerItem::GetSizeHint() const
{
	return _SizeHint;
}

void XE::SpacerItem::SetSizeHint( const XE::Vec2f & val )
{
	_SizeHint = val;
}

XE::Vec2f XE::SpacerItem::SizeHint() const
{
	if (_SizePolicy == XE::SizePolicy::FIXED)
	{
		return _SizeHint;
	}

	return GetMaximumSize();
}
