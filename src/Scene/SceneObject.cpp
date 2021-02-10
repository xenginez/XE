#include "SceneObject.h"

#include "World.h"
#include "GameZoneObject.h"

BEG_META( XE::SceneObject )
type->Property( "Name", &XE::SceneObject::_Name );
type->Property( "Enable", &XE::SceneObject::_Enable );
type->Property( "Handle", &XE::SceneObject::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "Zone", &XE::SceneObject::_Zone, XE::IMetaProperty::NoDesign );
END_META()

XE::WorldPtr XE::SceneObject::GetWorld() const
{
	return _World.lock();
}

XE::SceneObject::SceneObject()
	:_Enable( true )
{

}

XE::SceneObject::~SceneObject()
{

}

void XE::SceneObject::Startup()
{

}

void XE::SceneObject::Update( XE::float32 dt )
{

}

void XE::SceneObject::Clearup()
{
	if( _Zone )
	{
		GetGameZoneObjectPtr()->RemoveEntity( GetHandle() );
		_Zone = XE::SceneObjectHandle::Invalid;
	}
}

bool XE::SceneObject::GetEnable() const
{
	return _Enable;
}

void XE::SceneObject::SetEnable( bool val )
{
	if( _Enable != val )
	{
		_Enable = val;

		if( _Enable )
		{
			OnEnable();
		}
		else
		{
			OnDisable();
		}
	}
}

const XE::String & XE::SceneObject::GetName() const
{
	return _Name;
}

void XE::SceneObject::SetName( const String & val )
{
	_Name = val;
}

XE::SceneObjectHandle XE::SceneObject::GetGameZone() const
{
	return _Zone;
}

void XE::SceneObject::SetGameZone( const XE::SceneObjectHandle & val )
{
	if( _Zone )
	{
		GetGameZoneObjectPtr()->RemoveEntity( GetHandle() );
	}

	_Zone = val;

	if( val )
	{
		GetGameZoneObjectPtr()->InsertEntity( GetHandle() );
	}
}

XE::Transform & XE::SceneObject::GetTransform()
{
	return _Transform;
}

XE::SceneObjectHandle XE::SceneObject::GetHandle() const
{
	return _Handle;
}

XE::GameZoneObjectPtr XE::SceneObject::GetGameZoneObjectPtr() const
{
	return DP_CAST< XE::GameZoneObject >( GetWorld()->FindObject( _Zone ) );
}
