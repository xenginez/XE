#include "GameObject.h"

#include "WorldObject.h"

#include "Component.h"
#include "SceneComponent.h"
#include "RenderComponent.h"
#include "BehaviorComponent.h"

USING_XE

BEG_META( GameObject )
type->Property( "Name", &GameObject::_Name );
type->Property( "Handle", &GameObject::_Handle, IMetaProperty::NoDesign | IMetaProperty::NoClone );
type->Property( "Enabled", &GameObject::_Enabled );
type->Property( "Components", &GameObject::_Components, IMetaProperty::NoDesign );
END_META()

XE::GameObject::GameObject()
	:_Enabled( true ), _Destroy( false ), _Type( GameObjectType::STATIC )
{

}

XE::GameObject::~GameObject()
{

}

const XE::String& XE::GameObject::GetName() const
{
	return _Name;
}

XE::GameObjectHandle XE::GameObject::GetHandle() const
{
	return _Handle;
}

XE::Transform * XE::GameObject::GetTransform()
{
	return _SceneComponent->GetTransform();
}

XE::SceneComponentPtr XE::GameObject::GetSceneComponent() const
{
	return _SceneComponent;
}

XE::WorldObjectPtr XE::GameObject::GetWorld() const
{
	return _World.lock();
}

XE::IFrameworkPtr XE::GameObject::GetFramework() const
{
	return _Framework;
}

void XE::GameObject::SetFramework( IFrameworkPtr val )
{
	_Framework = val;
}

bool XE::GameObject::GetEnabled() const
{
	return _Enabled;
}

void XE::GameObject::SetEnabled( bool val )
{
	_Enabled = val;
}

bool XE::GameObject::GetDestroy() const
{
	return _Destroy;
}

void XE::GameObject::SetDestroy( bool val )
{
	_Destroy = val;
}

XE::GameObjectType XE::GameObject::GetType() const
{
	return _Type;
}

void XE::GameObject::SetType( GameObjectType val )
{
	_Type = val;
}

XE::ComponentPtr XE::GameObject::AddComponent( IMetaClassPtr val )
{
	XE::ComponentPtr comp = SP_CAST< Component >( val->ConstructPtr() );
	if ( comp )
	{
		comp->_GameObject = XE_THIS( GameObject );
		comp->_Handle = _Components.size();
		_Components.push_back( comp );
		comp->Startup();
	}
	return comp;
}

XE::ComponentPtr XE::GameObject::FindComponent( const String& val ) const
{
	for ( auto comp : _Components )
	{
		if ( comp->GetName() == val )
		{
			return comp;
		}
	}

	return nullptr;
}

XE::ComponentPtr XE::GameObject::FindComponent( IMetaClassPtr val ) const
{
	for ( auto comp : _Components )
	{
		if ( comp->GetMetaClass()->CanConvert( val ) )
		{
			return comp;
		}
	}

	return nullptr;
}

XE::ComponentPtr XE::GameObject::FindComponent( ComponentHandle val ) const
{
	XE_ASSERT( val.GetValue() < _Components.size() );

	return _Components[val.GetValue()];
}

const std::vector< ComponentPtr >& XE::GameObject::GetAllComponents() const
{
	return _Components;
}

void XE::GameObject::Startup()
{
	_SceneComponent = FindComponentT<SceneComponent>();

	OnStartup();

	for ( auto it : _Components )
	{
		it->_GameObject = XE_THIS( GameObject );

		it->Startup();
	}
}

void XE::GameObject::Update( XE::float32 dt )
{
	if ( _Enabled == false )
	{
		return;
	}

	OnUpdate( dt );

	for ( XE::uint64 i = 0; i < _Components.size(); i++ )
	{
		if ( _Components[i] )
		{
			if ( _Components[i]->GetDestroy() == false )
			{
				if ( _Components[i]->GetUpdate() )
				{
					_Components[i]->Update( dt );
				}
			}
			else
			{
				_Components[i]->Clearup();
				_Components[i] = nullptr;
			}
		}
	}
}

void XE::GameObject::Clearup()
{
	_SceneComponent = nullptr;

	for ( auto it : _Components )
	{
		if ( it )
		{
			it->Clearup();
		}
	}

	OnClearup();
}

void XE::GameObject::OnStartup()
{

}

void XE::GameObject::OnUpdate( XE::float32 dt )
{

}

void XE::GameObject::OnClearup()
{

}
