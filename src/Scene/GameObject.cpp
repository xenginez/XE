#include "GameObject.h"

#include "Component.h"
#include "SceneComponent.h"
#include "BehaviorComponent.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>

BEG_META( XE::GameObject )
type->Property( "SceneComponent", &XE::GameObject::_SceneComponent, XE::IMetaProperty::NoDesign );
type->Property( "BehaviorComponents", &XE::GameObject::_BehaviorComponents, XE::IMetaProperty::NoDesign );
END_META()

XE::GameObject::GameObject()
	:_Type( XE::GameObjectType::STATIC )
{

}

XE::GameObject::~GameObject()
{

}

XE::AABB XE::GameObject::GetBoundingBox() const
{
	if( _SceneComponent )
	{
		return _SceneComponent->GetBoundingBox();
	}

	return {};
}

XE::GameObjectType XE::GameObject::GetType() const
{
	return _Type;
}

void XE::GameObject::SetType( XE::GameObjectType val )
{
	_Type = val;
}

XE::SceneComponentPtr XE::GameObject::AddSceneComponent( XE::IMetaClassPtr val, const XE::SceneComponentPtr & parent )
{
	if( val->CanConvert( XE::SceneComponent::GetMetaClassStatic() ) )
	{
		auto comp = val->ConstructPtr().Value< XE::SceneComponentPtr >();

		if( comp )
		{
			comp->_Handle = _HandleTable.Alloc();

			comp->_World = GetWorld();
			comp->_GameObject = XE_THIS( XE::GameObject );

			if( parent )
			{
				comp->_Parent = parent;
				comp->_Transform.SetParent( &parent->GetTransform() );
				parent->_Children.push_back( comp );
			}
			else
			{
				_SceneComponent = comp;
				comp->_Transform.SetParent( &GetTransform() );
			}

			XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IThreadService >()->PostTask( XE::ThreadType::GAME, [comp]()
																						  {
																							  comp->Startup();
																						  } );
		}

		return comp;
	}

	return nullptr;
}

XE::BehaviorComponentPtr XE::GameObject::AddBehaviorComponent( XE::IMetaClassPtr val )
{
	if( val->CanConvert( XE::BehaviorComponent::GetMetaClassStatic() ) )
	{
		auto comp = val->ConstructPtr().Value< XE::BehaviorComponentPtr >();

		if( comp )
		{
			comp->_Handle = _HandleTable.Alloc();

			comp->_World = GetWorld();
			comp->_GameObject = XE_THIS( XE::GameObject );

			XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IThreadService >()->PostTask( XE::ThreadType::GAME, [comp]()
																						  {
																							  comp->Startup();
																						  } );

			_BehaviorComponents.push_back( comp );
		}

		return comp;
	}

	return nullptr;
}

bool XE::GameObject::RemoveSceneComponent( const XE::SceneComponentPtr & val )
{
	if( auto parent = val->GetParent() )
	{
		auto it = std::find( parent->_Children.begin(), parent->_Children.end(), val );
		if( it != parent->_Children.end() )
		{
			parent->_Children.erase( it );
		}
	}
	else if( val == _SceneComponent )
	{
		_SceneComponent = nullptr;
	}
	else
	{
		return false;
	}

	XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IThreadService >()->PostTask( XE::ThreadType::GAME, [val]()
																						  {
																							  val->Clearup();
																						  } );
	return true;
}

bool XE::GameObject::RemoveBehaviorComponet( const XE::BehaviorComponentPtr & val )
{
	auto it = std::find( _BehaviorComponents.begin(), _BehaviorComponents.end(), val );
	if( it != _BehaviorComponents.end() )
	{
		_BehaviorComponents.erase( it );

		XE::IFramework::GetCurrentFramework()->GetServiceT< XE::IThreadService >()->PostTask( XE::ThreadType::GAME, [val]()
																							  {
																								  val->Clearup();
																							  } );

		return true;
	}

	return false;
}

XE::BehaviorComponentPtr XE::GameObject::FindBehaviorComponent( XE::IMetaClassPtr val ) const
{
	for( auto comp : _BehaviorComponents )
	{
		if( comp->GetMetaClass()->CanConvert( val ) )
		{
			return comp;
		}
	}

	return nullptr;
}

XE::BehaviorComponentPtr XE::GameObject::FindBehaviorComponent( const XE::String & val ) const
{
	for( auto comp : _BehaviorComponents )
	{
		if( comp->GetName() == val )
		{
			return comp;
		}
	}

	return nullptr;
}

XE::BehaviorComponentPtr XE::GameObject::FindBehaviorComponent( XE::ComponentHandle val ) const
{
	for( auto comp : _BehaviorComponents )
	{
		if( comp->GetHandle() == val )
		{
			return comp;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::GameObject::FindSceneComponent( XE::IMetaClassPtr val ) const
{
	if( _SceneComponent )
	{
		if( _SceneComponent->GetMetaClass()->CanConvert( val ) )
		{
			return _SceneComponent;
		}
		else
		{
			return _SceneComponent->FindChild( val );
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::GameObject::FindSceneComponent( const XE::String & val ) const
{
	if( _SceneComponent )
	{
		if( _SceneComponent->GetName() == val )
		{
			return _SceneComponent;
		}
		else
		{
			return _SceneComponent->FindChild( val );
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::GameObject::FindSceneComponent( XE::ComponentHandle val ) const
{
	if( _SceneComponent )
	{
		if( _SceneComponent->GetHandle() == val )
		{
			return _SceneComponent;
		}
		else
		{
			return _SceneComponent->FindChild( val );
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::GameObject::GetRootSceneComponents() const
{
	return _SceneComponent;
}

const XE::Array< XE::BehaviorComponentPtr > & XE::GameObject::GetBehaviorComponents() const
{
	return _BehaviorComponents;
}

void XE::GameObject::ProcessEvent( const XE::EventPtr & val )
{
	if( _SceneComponent )
	{
		_SceneComponent->ProcessEvent( val );
	}

	if( val->accept )
	{
		return;
	}

	for( auto & comp : _BehaviorComponents )
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
	if( _SceneComponent )
	{
		_SceneComponent->_World = GetWorld();
		_SceneComponent->_GameObject = XE_THIS( XE::GameObject );
		_SceneComponent->_Transform.SetParent( &GetTransform() );

		_SceneComponent->Startup();
	}

	for( auto it : _BehaviorComponents )
	{
		it->_World = GetWorld();
		it->_GameObject = XE_THIS( XE::GameObject );

		it->Startup();
	}
}

void XE::GameObject::Update( XE::float32 dt )
{
	if( GetEnable() == false )
	{
		return;
	}

	for( XE::uint64 i = 0; i < _BehaviorComponents.size(); i++ )
	{
		if( _BehaviorComponents[i] )
		{
			_BehaviorComponents[i]->Update( dt );
		}
	}

	if( _SceneComponent )
	{
		_SceneComponent->Update( dt );
	}
}

void XE::GameObject::LateUpdate( XE::float32 dt )
{
	if( GetEnable() == false )
	{
		return;
	}

	for( XE::uint64 i = 0; i < _BehaviorComponents.size(); i++ )
	{
		if( _BehaviorComponents[i] )
		{
			_BehaviorComponents[i]->LateUpdate( dt );
		}
	}

	if( _SceneComponent )
	{
		_SceneComponent->LateUpdate( dt );
	}
}

void XE::GameObject::Clearup()
{
	for( auto it : _BehaviorComponents )
	{
		it->Clearup();
	}

	_BehaviorComponents.clear();

	if( _SceneComponent )
	{
		_SceneComponent->Clearup();
		_SceneComponent = nullptr;
	}
}

void XE::GameObject::OnEnable()
{
	if( _SceneComponent )
	{
		_SceneComponent->SetEnabled( GetEnable() );
	}

	for( auto & coms : _BehaviorComponents )
	{
		coms->SetEnabled( GetEnable() );
	}
}

void XE::GameObject::OnDisable()
{
	if( _SceneComponent )
	{
		_SceneComponent->SetEnabled( GetEnable() );
	}

	for( auto & comp : _BehaviorComponents )
	{
		comp->SetEnabled( GetEnable() );
	}
}
