#include "World.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>



BEG_META( XE::World )
type->Property( "Name", &World::_Name );
type->Property( "Entities", &World::_Entities );
type->Property( "HandleTable", &World::_HandleTable, XE::IMetaProperty::NoDesign );
END_META()

XE::World::World()
{

}

XE::World::~World()
{

}

const XE::String & XE::World::GetName() const
{
	return _Name;
}

void XE::World::SetName( const String & val )
{
	_Name = val;
}

bool XE::World::AddEntity( const GameEntityPtr & val )
{
	auto it = std::find( _Entities.begin(), _Entities.end(), val );
	if( it != _Entities.end() )
	{
		return false;
	}

	val->_Handle = _HandleTable.Alloc();

	val->Startup();

	_Entities.push_back( val );

	return true;
}

bool XE::World::RemoveEntity( const XE::GameEntityPtr & val )
{
	auto it = std::find( _Entities.begin(), _Entities.end(), val );

	if( it != _Entities.end() )
	{
		_Entities.erase( it );

		val->Clearup();

		return true;
	}

	return false;
}

XE::GameEntityPtr XE::World::FindEntity( const String & val ) const
{
	for( const auto & obj : _Entities )
	{
		if( obj->GetName() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

XE::GameEntityPtr XE::World::FindEntity( GameEntityHandle val ) const
{
	for( const auto & obj : _Entities )
	{
		if( obj->GetHandle() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

const XE::Array< XE::GameEntityPtr > & XE::World::GetEntitys() const
{
	return _Entities;
}

void XE::World::Startup()
{
	for( auto entity : _Entities )
	{
		entity->Startup();
	}
}

void XE::World::Update( XE::float32 dt )
{
	for( auto & entity : _Entities )
	{
		if( entity )
		{
			if( entity->GetEnable() )
			{
				entity->Update( dt );
			}
		}
	}
}

void XE::World::Clearup()
{
	for( auto entity : _Entities )
	{
		entity->Clearup();
	}

	_Entities.clear();
}
