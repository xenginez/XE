#include "AIModule.h"

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

XE::GameObjectPtr XE::AIModule::GetGameObject() const
{
	return _GameObject.lock();
}

void XE::AIModule::SetGameObject( const XE::GameObjectPtr & val )
{
	_GameObject = val;
}

XE::Variant XE::AIModule::GetKey( const XE::BlackboardKey & val ) const
{
	auto it = _Keys.find( val.GetKey() );
	if( it != _Keys.end() )
	{
		return it->second;
	}
	return {};
}

void XE::AIModule::SetKey( const XE::BlackboardKey & key, const XE::Variant & val )
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
