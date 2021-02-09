#include "GameEntity.h"

#include "World.h"
#include "GameZone.h"

BEG_META( XE::GameEntity )
type->Property( "Name", &XE::GameEntity::_Name );
type->Property( "Enable", &XE::GameEntity::_Enable );
type->Property( "Handle", &XE::GameEntity::_Handle, XE::IMetaProperty::NoDesign );
type->Property( "Zone", &XE::GameEntity::_Zone, XE::IMetaProperty::NoDesign );
END_META()

XE::WorldPtr XE::GameEntity::GetWorld() const
{
	return _World.lock();
}

XE::GameEntity::GameEntity()
	:_Enable( true )
{

}

XE::GameEntity::~GameEntity()
{

}

void XE::GameEntity::Startup()
{

}

void XE::GameEntity::Update( XE::float32 dt )
{

}

void XE::GameEntity::Clearup()
{
	if( _Zone )
	{
		GetGameZonePtr()->RemoveEntity( GetHandle() );
		_Zone = XE::GameEntityHandle::Invalid;
	}
}

bool XE::GameEntity::GetEnable() const
{
	return _Enable;
}

void XE::GameEntity::SetEnable( bool val )
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

const XE::String & XE::GameEntity::GetName() const
{
	return _Name;
}

void XE::GameEntity::SetName( const String & val )
{
	_Name = val;
}

XE::GameEntityHandle XE::GameEntity::GetGameZone() const
{
	return _Zone;
}

void XE::GameEntity::SetGameZone( const XE::GameEntityHandle & val )
{
	if( _Zone )
	{
		GetGameZonePtr()->RemoveEntity( GetHandle() );
	}

	_Zone = val;

	if( val )
	{
		GetGameZonePtr()->InsertEntity( GetHandle() );
	}
}

XE::Transform & XE::GameEntity::GetTransform()
{
	return _Transform;
}

XE::GameEntityHandle XE::GameEntity::GetHandle() const
{
	return _Handle;
}

XE::GameZonePtr XE::GameEntity::GetGameZonePtr() const
{
	return DP_CAST<XE::GameZone>( GetWorld()->FindEntity( _Zone ) );
}
