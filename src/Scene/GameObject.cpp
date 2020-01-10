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
	_RootSceneComponent = XE::MakeShared<XE::SceneComponent>();
	_RootSceneComponent->SetName( "Root" );
	_Components.push_back( _RootSceneComponent );
}

XE::GameObject::~GameObject()
{

}

XE::GameObjectHandle XE::GameObject::GetHandle() const
{
	return _Handle;
}

const XE::AABB & XE::GameObject::GetBoundingBox() const
{
	return _RootSceneComponent->GetBoundingBox();
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

const XE::String & XE::GameObject::GetName() const
{
	return _Name;
}

void XE::GameObject::SetName( const XE::String & val )
{
	_Name = val;
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

		if( auto beh = DP_CAST<XE::BehaviorComponent>( comp ) )
		{
			_BehaviorComponents.push_back( beh );
		}
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

const XE::Array< ComponentPtr >& XE::GameObject::GetComponents() const
{
	return _Components;
}

bool GameObject::RemoveComponet( const ComponentPtr & val )
{
	auto it = std::find( _Components.begin(), _Components.end(), val );
	if( it != _Components.end() )
	{
		val->SetDestroy( true );

		return true;
	}

	return false;
}

XE::SceneComponentPtr XE::GameObject::GetRootSceneComponent() const
{
	return _RootSceneComponent;
}

XE::Array<SceneComponentPtr> GameObject::GetSceneComponets() const
{
	XE::Array<SceneComponentPtr> ret;

	if( GetRootSceneComponent() )
	{
		ret.push_back( GetRootSceneComponent() );

		for( XE::uint64 i = 0;; )
		{
			auto children = ret[i]->GetChildren();

			ret.insert( ret.end(), children.begin(), children.end() );
		}
	}

	return ret;
}

XE::Array<BehaviorComponentPtr> GameObject::GetBehaviorComponents() const
{
	return _BehaviorComponents;
}

XE::Vec3 XE::GameObject::GetWorldUp()
{
	return _RootSceneComponent->GetWorldUp();
}

XE::Vec3 XE::GameObject::GetWorldRight()
{
	return _RootSceneComponent->GetWorldRight();
}

XE::Vec3 XE::GameObject::GetWorldForward()
{
	return _RootSceneComponent->GetWorldForward();
}

XE::Vec3 XE::GameObject::GetRelativeUp() const
{
	return _RootSceneComponent->GetRelativeUp();
}

XE::Vec3 XE::GameObject::GetRelativeRight() const
{
	return _RootSceneComponent->GetRelativeRight();
}

XE::Vec3 XE::GameObject::GetRelativeForward() const
{
	return _RootSceneComponent->GetRelativeForward();
}

const XE::Vec3 & XE::GameObject::GetWorldScale()
{
	return _RootSceneComponent->GetWorldScale();
}

void XE::GameObject::SetWorldScale( const Vec3 & val )
{
	_RootSceneComponent->SetWorldScale( val );
}

const XE::Vec3 & XE::GameObject::GetWorldPosition()
{
	return _RootSceneComponent->GetWorldPosition();
}

void XE::GameObject::SetWorldPosition( const Vec3 & val )
{
	_RootSceneComponent->SetWorldPosition( val );
}

const XE::Quat & XE::GameObject::GetWorldRotation()
{
	return _RootSceneComponent->GetWorldRotation();
}

void XE::GameObject::SetWorldRotation( const Quat & val )
{
	_RootSceneComponent->SetWorldRotation( val );
}

const XE::Vec3 & XE::GameObject::GetRelativeScale() const
{
	return _RootSceneComponent->GetRelativeScale();
}

void XE::GameObject::SetRelativeScale( const Vec3 & val )
{
	_RootSceneComponent->SetRelativeScale( val );
}

const XE::Vec3 & XE::GameObject::GetRelativePosition() const
{
	return _RootSceneComponent->GetRelativePosition();
}

void XE::GameObject::SetRelativePosition( const Vec3 & val )
{
	_RootSceneComponent->SetRelativePosition( val );
}

const XE::Quat & XE::GameObject::GetRelativeRotation() const
{
	return _RootSceneComponent->GetRelativeRotation();
}

void XE::GameObject::SetRelativeRotation( const Quat & val )
{
	_RootSceneComponent->SetRelativeRotation( val );
}

const Mat4 & XE::GameObject::GetWorldTransform() const
{
	return _RootSceneComponent->GetWorldTransform();
}

void XE::GameObject::SetWorldTransform( const Mat4 & val )
{
	_RootSceneComponent->SetWorldTransform( val );
}

const Mat4 & XE::GameObject::GetRelativeTransform() const
{
	return _RootSceneComponent->GetRelativeTransform();
}

void XE::GameObject::SetRelativeTransform( const Mat4 & val )
{
	_RootSceneComponent->SetRelativeTransform( val );
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

void XE::GameObject::Startup()
{
	_RootSceneComponent = SP_CAST<XE::SceneComponent>( _Components[0] );

	for( auto it : _Components )
	{
		it->_GameObject = XE_THIS( GameObject );

		it->Startup();
	}
}

void XE::GameObject::Update( XE::float32 dt )
{
	for( XE::uint64 i = 0; i < _Components.size(); i++ )
	{
		if( _Components[i] )
		{
			if( _Components[i]->GetDestroy() == true )
			{
				if( auto beh = DP_CAST<XE::BehaviorComponent>( _Components[i] ) )
				{
					_BehaviorComponents.erase( std::find( _BehaviorComponents.begin(), _BehaviorComponents.end(), beh ) );

					_Components[i]->Clearup();

					_Components[i] = nullptr;
				}
				else if( auto scene = DP_CAST<XE::SceneComponent>( _Components[i] ) )
				{
					RemoveSceneComponent( scene );

					scene->Clearup();
				}
			}
		}
	}

	if( _Enabled == false )
	{
		return;
	}

	_RootSceneComponent->Update( dt );

	for( XE::uint64 i = 0; i < _BehaviorComponents.size(); i++ )
	{
		if( _BehaviorComponents[i] )
		{
			if( _BehaviorComponents[i]->GetUpdate() )
			{
				_BehaviorComponents[i]->Update( dt );
			}
		}
	}
}

void XE::GameObject::Clearup()
{
	_RootSceneComponent->Clearup();

	_RootSceneComponent = nullptr;

	for( auto it : _BehaviorComponents )
	{
		if( it )
		{
			it->Clearup();
		}
	}

	_BehaviorComponents.clear();

	_Components.clear();
}

void GameObject::RemoveSceneComponent( const XE::SceneComponentPtr & val )
{
	const auto & children = val->GetChildren();

	for( const auto & child : children )
	{
		RemoveSceneComponent( child );
	}

	_Components[val->GetHandle().GetValue()] = nullptr;
}
