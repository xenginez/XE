#include "World.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>

#include "GameZoneObject.h"

BEG_META( XE::World )
type->Property( "Name", &World::_Name );
type->Property( "Entities", &World::_Objects );
type->Property( "Transform", &World::_Transform );
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

bool XE::World::AddObject( const SceneObjectPtr & val )
{
	auto it = std::find( _Objects.begin(), _Objects.end(), val );
	if( it != _Objects.end() )
	{
		return false;
	}

	val->_Handle = _HandleTable.Alloc();

	val->_World = XE_THIS( World );

	val->_Transform.SetParent( &_Transform );

	val->Startup();

	_Objects.push_back( val );

	return true;
}

bool XE::World::RemoveObject( const XE::SceneObjectPtr & val )
{
	auto it = std::find( _Objects.begin(), _Objects.end(), val );

	if( it != _Objects.end() )
	{
		_Objects.erase( it );

		val->Clearup();

		return true;
	}

	return false;
}

XE::SceneObjectPtr XE::World::FindObject( const String & val ) const
{
	for( const auto & obj : _Objects )
	{
		if( obj->GetName() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

XE::SceneObjectPtr XE::World::FindObject( SceneObjectHandle val ) const
{
	for( const auto & obj : _Objects )
	{
		if( obj->GetHandle() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

const XE::Array< XE::SceneObjectPtr > & XE::World::GetObjects() const
{
	return _Objects;
}

void XE::World::Startup()
{
	for( auto entity : _Objects )
	{
		entity->_World = XE_THIS( World );

		entity->_Transform.SetParent( &_Transform );

		entity->Startup();
	}
}

void XE::World::Update( XE::float32 dt )
{
	for( auto & entity : _Objects )
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
	for( auto entity : _Objects )
	{
		entity->Clearup();
	}

	_Objects.clear();
}

XE::Transform & XE::World::GetTransform()
{
	return _Transform;
}
