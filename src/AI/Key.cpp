#include "Key.h"

BEG_META( XE::Key )
type->Property( "Key", &Key::_Key );
END_META()

XE::Key::Key()
{

}

XE::Key::Key( const XE::Key & val )
	:_Key( val._Key )
{

}

XE::Key::Key( const XE::String & val )
	: _Key( val )
{

}

XE::Key::~Key()
{

}

const XE::String & XE::Key::GetKey() const
{
	return _Key;
}

void XE::Key::SetKey( const XE::String & val )
{
	_Key = val;
}

bool XE::Key::operator<( const XE::Key & val ) const
{
	return _Key < val._Key;
}

bool XE::Key::operator>( const XE::Key & val ) const
{
	return _Key > val._Key;
}

bool XE::Key::operator<=( const XE::Key & val ) const
{
	return _Key <= val._Key;
}

bool XE::Key::operator>=( const XE::Key & val ) const
{
	return _Key >= val._Key;
}

bool XE::Key::operator==( const XE::Key & val ) const
{
	return _Key == val._Key;
}

bool XE::Key::operator!=( const XE::Key & val ) const
{
	return _Key != val._Key;
}
