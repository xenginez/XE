#include "AIModule.h"

#include "Key.h"

USING_XE

BEG_META( AIModule )
type->Property( "Name", &AIModule::_Name );
type->Property( "Keys", &AIModule::_Keys );
END_META()

XE::AIModule::AIModule()
{

}

XE::AIModule::~AIModule()
{

}

const XE::String & AIModule::GetName() const
{
	return _Name;
}

void AIModule::SetName( const XE::String & val )
{
	_Name = val;
}

XE::Variant XE::AIModule::GetKey( const Key & val ) const
{
	auto it = _Keys.find( val.GetKey() );
	if( it != _Keys.end() )
	{
		return it->second;
	}
	return {};
}

void XE::AIModule::SetKey( const Key & key, const XE::Variant & val )
{
	_Keys[key.GetKey()] = val;
}
