#include "World.h"

#include "GameObject.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>

USING_XE

BEG_META( World )
type->Property( "Name", &World::_Name );
type->Property( "GameObjects", &World::_GameObjects );
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

bool XE::World::AddGameObject( const GameObjectPtr & val )
{
	auto it = std::find( _GameObjects.begin(), _GameObjects.end(), val );
	if( it != _GameObjects.end() )
	{
		return false;
	}

	val->_Handle = _HandleTable.Alloc();

	XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( ThreadType::GAME, [ val ]()
		{
			val->Startup();
		} );

	_GameObjects.push_back( val );

	return true;
}

bool World::RemoveGameObject( const GameObjectPtr & val )
{
	auto it = std::find( _GameObjects.begin(), _GameObjects.end(), val );

	if( it != _GameObjects.end() )
	{
		_GameObjects.erase( it );

		XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( ThreadType::GAME, [ val ]()
			{
				val->Clearup();
			} );

		return true;
	}

	return false;
}

XE::GameObjectPtr XE::World::FindGameObject( const String & val ) const
{
	for( const auto & obj : _GameObjects )
	{
		if( obj->GetName() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

XE::GameObjectPtr XE::World::FindGameObject( GameObjectHandle val ) const
{
	for( const auto & obj : _GameObjects )
	{
		if( obj->GetHandle() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

const XE::Array< GameObjectPtr > & XE::World::GetGameObjects() const
{
	return _GameObjects;
}

XE::GameObjectPtr XE::World::Intersect( const Array<GameObjectPtr> exclude, const Ray & val ) const
{
	if( GameObjectPtr obj = _StaticTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	if( GameObjectPtr obj = _DynmicTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	return nullptr;
}

XE::GameObjectPtr XE::World::Intersect( const Array<GameObjectPtr> exclude, const AABB & val ) const
{
	if( GameObjectPtr obj = _StaticTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	if( GameObjectPtr obj = _DynmicTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	return nullptr;
}

XE::GameObjectPtr XE::World::Intersect( const Array<GameObjectPtr> exclude, const Line & val ) const
{
	if( GameObjectPtr obj = _StaticTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	if( GameObjectPtr obj = _DynmicTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	return nullptr;
}

XE::GameObjectPtr XE::World::Intersect( const Array<GameObjectPtr> exclude, const Plane & val ) const
{
	if( GameObjectPtr obj = _StaticTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	if( GameObjectPtr obj = _DynmicTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	return nullptr;
}

XE::GameObjectPtr XE::World::Intersect( const Array<GameObjectPtr> exclude, const Sphere & val ) const
{
	if( GameObjectPtr obj = _StaticTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	if( GameObjectPtr obj = _DynmicTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	return nullptr;
}

XE::GameObjectPtr XE::World::Intersect( const Array<GameObjectPtr> exclude, const Frustum & val ) const
{
	if( GameObjectPtr obj = _StaticTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	if( GameObjectPtr obj = _DynmicTree.Intersect( val, exclude ) )
	{
		return obj;
	}
	return nullptr;
}

XE::Array<XE::GameObjectPtr> XE::World::Intersects( const Ray & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::World::Intersects( const AABB & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::World::Intersects( const Line & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::World::Intersects( const Plane & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::World::Intersects( const Sphere & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::World::Intersects( const Frustum & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

void XE::World::Startup()
{
	Array<GameObjectPtr> static_objs;
	Array<GameObjectPtr> dynmic_objs;

	for( auto obj : _GameObjects )
	{
		obj->Startup();

		if( obj->GetType() == GameObjectType::STATIC )
		{
			static_objs.push_back( obj );
		}
		else
		{
			dynmic_objs.push_back( obj );
		}
	}

	_StaticTree.Rebuild( static_objs.begin(), static_objs.end() );
	_DynmicTree.Rebuild( dynmic_objs.begin(), dynmic_objs.end() );
}

void XE::World::Update( XE::float32 dt )
{
	Array<GameObjectPtr> dynmic_objs;

	for( XE::uint64 i = 0; i < _GameObjects.size(); ++i )
	{
		if( _GameObjects[i] )
		{
			if( _GameObjects[i]->GetEnabled() )
			{
				_GameObjects[i]->Update( dt );

				if( _GameObjects[i]->GetType() == GameObjectType::DYNAMIC )
				{
					dynmic_objs.push_back( _GameObjects[i] );
				}
			}
		}
	}

	_DynmicTree.Rebuild( dynmic_objs.begin(), dynmic_objs.end() );
}

void XE::World::Clearup()
{
	for( auto obj : _GameObjects )
	{
		obj->Clearup();
	}

	_GameObjects.clear();
}
