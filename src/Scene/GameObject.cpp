#include "GameObject.h"

#include "Component.h"
#include "SceneComponent.h"
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

const XE::AABB & XE::GameObject::GetBoundingBox() const
{
	return _SceneComponent->GetBoundingBox();
}

XE::SceneComponentPtr XE::GameObject::GetSceneComponent() const
{
	return _SceneComponent;
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
	XE::ComponentPtr comp = val->ConstructPtr().Value< XE::ComponentPtr >();
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

XE::Vec3 XE::GameObject::GetWorldUp()
{
	return _SceneComponent->GetWorldUp();
}

XE::Vec3 XE::GameObject::GetWorldRight()
{
	return _SceneComponent->GetWorldRight();
}

XE::Vec3 XE::GameObject::GetWorldForward()
{
	return _SceneComponent->GetWorldForward();
}

XE::Vec3 XE::GameObject::GetRelativeUp() const
{
	return _SceneComponent->GetRelativeUp();
}

XE::Vec3 XE::GameObject::GetRelativeRight() const
{
	return _SceneComponent->GetRelativeRight();
}

XE::Vec3 XE::GameObject::GetRelativeForward() const
{
	return _SceneComponent->GetRelativeForward();
}

const XE::Vec3 & XE::GameObject::GetWorldScale()
{
	return _SceneComponent->GetWorldScale();
}

void XE::GameObject::SetWorldScale( const Vec3 & val )
{
	_SceneComponent->SetWorldScale( val );
}

const XE::Vec3 & XE::GameObject::GetWorldPosition()
{
	return _SceneComponent->GetWorldPosition();
}

void XE::GameObject::SetWorldPosition( const Vec3 & val )
{
	_SceneComponent->SetWorldPosition( val );
}

const XE::Quat & XE::GameObject::GetWorldRotation()
{
	return _SceneComponent->GetWorldRotation();
}

void XE::GameObject::SetWorldRotation( const Quat & val )
{
	_SceneComponent->SetWorldRotation( val );
}

const XE::Vec3 & XE::GameObject::GetRelativeScale() const
{
	return _SceneComponent->GetRelativeScale();
}

void XE::GameObject::SetRelativeScale( const Vec3 & val )
{
	_SceneComponent->SetRelativeScale( val );
}

const XE::Vec3 & XE::GameObject::GetRelativePosition() const
{
	return _SceneComponent->GetRelativePosition();
}

void XE::GameObject::SetRelativePosition( const Vec3 & val )
{
	_SceneComponent->SetRelativePosition( val );
}

const XE::Quat & XE::GameObject::GetRelativeRotation() const
{
	return _SceneComponent->GetRelativeRotation();
}

void XE::GameObject::SetRelativeRotation( const Quat & val )
{
	_SceneComponent->SetRelativeRotation( val );
}

const Mat4 & XE::GameObject::GetWorldTransform() const
{
	return _SceneComponent->GetWorldTransform();
}

void XE::GameObject::SetWorldTransform( const Mat4 & val )
{
	_SceneComponent->SetWorldTransform( val );
}

const Mat4 & XE::GameObject::GetRelativeTransform() const
{
	return _SceneComponent->GetRelativeTransform();
}

void XE::GameObject::SetRelativeTransform( const Mat4 & val )
{
	_SceneComponent->SetRelativeTransform( val );
}

void XE::GameObject::ProcessEvent( EventPtr & val )
{
	for( auto & comp : _Components )
	{
		comp->ProcessEvent( val );

		if( val->accept )
		{
			break;
		}
	}
}
