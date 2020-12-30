#include "BlackboardKey.h"

BEG_META( AI::BlackboardKey )
type->Property( "Key", &AI::BlackboardKey::GetKey, &AI::BlackboardKey::SetKey );
END_META()

AI::BlackboardKey::BlackboardKey()
{

}

AI::BlackboardKey::BlackboardKey( const AI::BlackboardKey & val )
	:_Key( val._Key )
{

}

AI::BlackboardKey::BlackboardKey( const XE::String & val )
	: _Key( val )
{

}

AI::BlackboardKey::~BlackboardKey()
{

}

const XE::String & AI::BlackboardKey::GetKey() const
{
	return _Key;
}

void AI::BlackboardKey::SetKey( const XE::String & val )
{
	_Key = val;
}

bool AI::BlackboardKey::operator<( const AI::BlackboardKey & val ) const
{
	return _Key < val._Key;
}

bool AI::BlackboardKey::operator>( const AI::BlackboardKey & val ) const
{
	return _Key > val._Key;
}

bool AI::BlackboardKey::operator<=( const AI::BlackboardKey & val ) const
{
	return _Key <= val._Key;
}

bool AI::BlackboardKey::operator>=( const AI::BlackboardKey & val ) const
{
	return _Key >= val._Key;
}

bool AI::BlackboardKey::operator==( const AI::BlackboardKey & val ) const
{
	return _Key == val._Key;
}

bool AI::BlackboardKey::operator!=( const AI::BlackboardKey & val ) const
{
	return _Key != val._Key;
}
