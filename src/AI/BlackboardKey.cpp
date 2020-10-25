#include "BlackboardKey.h"

BEG_META( XE::BlackboardKey )
type->Property( "Key", &BlackboardKey::_Key );
END_META()

XE::BlackboardKey::BlackboardKey()
{

}

XE::BlackboardKey::BlackboardKey( const XE::BlackboardKey & val )
	:_Key( val._Key )
{

}

XE::BlackboardKey::BlackboardKey( const XE::String & val )
	: _Key( val )
{

}

XE::BlackboardKey::~BlackboardKey()
{

}

const XE::String & XE::BlackboardKey::GetKey() const
{
	return _Key;
}

void XE::BlackboardKey::SetKey( const XE::String & val )
{
	_Key = val;
}

bool XE::BlackboardKey::operator<( const XE::BlackboardKey & val ) const
{
	return _Key < val._Key;
}

bool XE::BlackboardKey::operator>( const XE::BlackboardKey & val ) const
{
	return _Key > val._Key;
}

bool XE::BlackboardKey::operator<=( const XE::BlackboardKey & val ) const
{
	return _Key <= val._Key;
}

bool XE::BlackboardKey::operator>=( const XE::BlackboardKey & val ) const
{
	return _Key >= val._Key;
}

bool XE::BlackboardKey::operator==( const XE::BlackboardKey & val ) const
{
	return _Key == val._Key;
}

bool XE::BlackboardKey::operator!=( const XE::BlackboardKey & val ) const
{
	return _Key != val._Key;
}
