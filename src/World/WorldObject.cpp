#include "WorldObject.h"

#include "GameObject.h"

USING_XE

XE::uint64 XE::WorldObject::_HandleTable = 0;

BEG_META( WorldObject )
type->Property( "Name", &WorldObject::_Name );
type->Property( "GameObjects", &WorldObject::_AllGameObjects );
END_META()

XE::WorldObject::WorldObject()
{

}

XE::WorldObject::~WorldObject()
{

}

const XE::String & XE::WorldObject::GetName() const
{
	return _Name;
}

void XE::WorldObject::SetName( const String & val )
{
	_Name = val;
}

bool XE::WorldObject::AddGameObject( const GameObjectPtr & val )
{
	for( const auto & obj : _AllGameObjects )
	{
		if( obj == val )
		{
			return false;
		}
	}

	val->_Handle = _HandleTable++;
	val->_World = XE_THIS( WorldObject );

	val->Startup();

	_AllGameObjects.push_back( val );

	return true;
}

XE::GameObjectPtr XE::WorldObject::FindGameObject( const String & val ) const
{
	for( const auto & obj : _AllGameObjects )
	{
		if( obj->GetName() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

XE::GameObjectPtr XE::WorldObject::FindGameObject( GameObjectHandle val ) const
{
	for( const auto & obj : _AllGameObjects )
	{
		if( obj->GetHandle() == val )
		{
			return obj;
		}
	}

	return nullptr;
}

const XE::Array< GameObjectPtr > & XE::WorldObject::GetGameObjects() const
{
	return _AllGameObjects;
}

XE::GameObjectPtr XE::WorldObject::Intersect( const Array<GameObjectPtr> exclude, const Ray & val ) const
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

XE::GameObjectPtr XE::WorldObject::Intersect( const Array<GameObjectPtr> exclude, const AABB & val ) const
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

XE::GameObjectPtr XE::WorldObject::Intersect( const Array<GameObjectPtr> exclude, const Line & val ) const
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

XE::GameObjectPtr XE::WorldObject::Intersect( const Array<GameObjectPtr> exclude, const Plane & val ) const
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

XE::GameObjectPtr XE::WorldObject::Intersect( const Array<GameObjectPtr> exclude, const Sphere & val ) const
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

XE::GameObjectPtr XE::WorldObject::Intersect( const Array<GameObjectPtr> exclude, const Frustum & val ) const
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

XE::Array<XE::GameObjectPtr> XE::WorldObject::Intersects( const Ray & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::WorldObject::Intersects( const AABB & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::WorldObject::Intersects( const Line & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::WorldObject::Intersects( const Plane & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::WorldObject::Intersects( const Sphere & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

XE::Array<XE::GameObjectPtr> XE::WorldObject::Intersects( const Frustum & val ) const
{
	XE::Array<XE::GameObjectPtr> static_objects = _StaticTree.Intersects( val );

	XE::Array<XE::GameObjectPtr> dynmic_objects = _DynmicTree.Intersects( val );

	static_objects.insert( static_objects.end(), dynmic_objects.begin(), dynmic_objects.end() );

	return std::move( static_objects );
}

void XE::WorldObject::Startup()
{
	FArray<GameObjectPtr> static_objs;
	FArray<GameObjectPtr> dynmic_objs;

	for( auto obj : _AllGameObjects )
	{
		obj->_World = XE_THIS( WorldObject );
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

void XE::WorldObject::Update( XE::float32 dt )
{
	FArray<GameObjectPtr> dynmic_objs;

	for( XE::uint64 i = 0; i < _AllGameObjects.size(); ++i )
	{
		if( _AllGameObjects[i] )
		{
			if( _AllGameObjects[i]->GetDestroy() != false )
			{
				if( _AllGameObjects[i]->GetEnabled() )
				{
					_AllGameObjects[i]->Update( dt );
					if( _AllGameObjects[i]->GetType() == GameObjectType::DYNAMIC )
					{
						dynmic_objs.push_back( _AllGameObjects[i] );
					}
				}
			}
			else
			{
				_AllGameObjects[i]->Clearup();
				_AllGameObjects[i] = nullptr;
			}
		}
	}

	_DynmicTree.Rebuild( dynmic_objs.begin(), dynmic_objs.end() );
}

void XE::WorldObject::Clearup()
{
	for( auto obj : _AllGameObjects )
	{
		obj->Clearup();
	}

	_AllGameObjects.clear();
}
