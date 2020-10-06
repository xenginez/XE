#include "AIModule.h"

#include "Key.h"

BEG_META( XE::AIModule )
type->Property( "Name", &AIModule::_Name );
type->Property( "Keys", &AIModule::_Keys );
END_META()

XE::AIModule::AIModule()
{

}

XE::AIModule::~AIModule()
{

}

const XE::String & XE::AIModule::GetName() const
{
	return _Name;
}

void XE::AIModule::SetName( const XE::String & val )
{
	_Name = val;
}

XE::Variant XE::AIModule::GetKey( const XE::Key & val ) const
{
	auto it = _Keys.find( val.GetKey() );
	if( it != _Keys.end() )
	{
		return it->second;
	}
	return {};
}

void XE::AIModule::SetKey( const XE::Key & key, const XE::Variant & val )
{
	_Keys[key.GetKey()] = val;
}

const XE::Map<XE::String, XE::Variant> & XE::AIModule::GetKeys() const
{
	return _Keys;
}

void XE::AIModule::SetKeys( const XE::Map<XE::String, XE::Variant> & val )
{
	_Keys = val;
}
