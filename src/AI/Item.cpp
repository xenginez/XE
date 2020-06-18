#include "Item.h"



BEG_META( XE::Item )
type->Property( "Name", &Item::_Name );
type->Property( "Position", &Item::_Position, IMetaProperty::NoDesign );
END_META()

XE::Item::Item()
{

}

XE::Item::~Item()
{

}

const XE::String & XE::Item::GetName() const
{
	return _Name;
}

void XE::Item::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Vec2 & XE::Item::GetPosition() const
{
	return _Position;
}

void XE::Item::SetPosition( const XE::Vec2 & val )
{
	_Position = val;
}
