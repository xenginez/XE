#include "Item.h"

USING_XE

BEG_META( Item )
type->Property( "Name", &Item::_Name );
type->Property( "Position", &Item::_Position, IMetaProperty::NoDesign );
END_META()

Item::Item()
{

}

Item::~Item()
{

}

const XE::String & Item::GetName() const
{
	return _Name;
}

void Item::SetName( const XE::String & val )
{
	_Name = val;
}

const XE::Vec2 & Item::GetPosition() const
{
	return _Position;
}

void Item::SetPosition( const XE::Vec2 & val )
{
	_Position = val;
}
