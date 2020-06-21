#include "Item.h"



BEG_META( XE::Item )
type->Property( "Name", &Item::_Name );
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
