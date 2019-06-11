#include "WorldObject.h"

#include "GameObject.h"

USING_XE

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

const XE::String& XE::WorldObject::GetName() const
{
	return _Name;
}

void XE::WorldObject::SetName( const String& val )
{
	_Name = val;
}

XE::IFrameworkPtr XE::WorldObject::GetFramework() const
{
	return _Framework;
}

void XE::WorldObject::SetFramework( IFrameworkPtr val )
{
	_Framework = val;
}

XE::GameObjectPtr XE::WorldObject::AddGameObject()
{
	static XE::uint64 HandleTable = 0;

	GameObjectPtr p = XE::make_shared<GameObject>();

	p->_Name = "GameObject_" + StringUtils::Format( "%0", p->_Handle.GetValue() );
	p->_Handle = HandleTable++;
	p->_World = XE_THIS( WorldObject );
	p->SetFramework( GetFramework() );

	p->Startup();

	_AllGameObjects.push_back( p );
	_GameObjectMap.insert( std::make_pair( p->GetHandle().GetValue(), p ) );
	_GameObjectMap.insert( std::make_pair( reinterpret_cast<XE::uint64>( p->GetName().ToCString() ), p ) );

	return p;
}

XE::GameObjectPtr XE::WorldObject::FindGameObject( const String& val ) const
{
	auto it = _GameObjectMap.find( reinterpret_cast<XE::uint64>( val.ToCString() ) );
	if ( it != _GameObjectMap.end() )
	{
		return it->second;
	}
	return nullptr;
}

XE::GameObjectPtr XE::WorldObject::FindGameObject( GameObjectHandle val ) const
{
	auto it = _GameObjectMap.find( val.GetValue() );
	if (it != _GameObjectMap.end())
	{
		return it->second;
	}
	return nullptr;
}

const Array< GameObjectPtr >& XE::WorldObject::GetGameObjects() const
{
	return _AllGameObjects;
}

void XE::WorldObject::Startup()
{
	for ( auto obj : _AllGameObjects )
	{
		_GameObjectMap.insert( std::make_pair( reinterpret_cast<XE::uint64>( obj->GetName().ToCString() ), obj ) );
		_GameObjectMap.insert( std::make_pair( obj->GetHandle().GetValue(), obj ) );
		obj->_World = XE_THIS( WorldObject );
		obj->SetFramework( GetFramework() );
		obj->Startup();
	}
}

void XE::WorldObject::Update( XE::float32 dt )
{
	for ( XE::uint64 i = 0; i < _AllGameObjects.size(); ++i )
	{
		if ( _AllGameObjects[i] )
		{
			if ( _AllGameObjects[i]->GetDestroy() != false )
			{
				if ( _AllGameObjects[i]->GetEnabled() )
				{
					_AllGameObjects[i]->Update( dt );
				}
			}
			else
			{
				_GameObjectMap.erase( _AllGameObjects[i]->GetHandle().GetValue() );
				_GameObjectMap.erase( reinterpret_cast<XE::uint64>( _AllGameObjects[i]->GetName().ToCString() ) );
				_AllGameObjects[i]->Clearup();
				_AllGameObjects[i] = nullptr;
			}
		}
	}
}

void XE::WorldObject::Clearup()
{
	for ( auto obj : _AllGameObjects )
	{
		obj->Clearup();
	}

	_AllGameObjects.clear();
	_GameObjectMap.clear();
}
