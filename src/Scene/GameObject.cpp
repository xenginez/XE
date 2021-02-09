#include "GameObject.h"

#include "Component.h"
#include "SceneComponent.h"
#include "BehaviorComponent.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>

BEG_META( XE::GameObject )
type->Property( "SceneComponent", &GameObject::_SceneComponent, IMetaProperty::NoDesign );
type->Property( "BehaviorComponents", &GameObject::_BehaviorComponents, IMetaProperty::NoDesign );
END_META()

XE::GameObject::GameObject()
	:_Type( GameObjectType::STATIC )
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

void XE::GameObject::SetType( GameObjectType val )
{
	_Type = val;
}

XE::SceneComponentPtr XE::GameObject::AddSceneComponent( IMetaClassPtr val, const SceneComponentPtr & parent )
{
	if( val->CanConvert( SceneComponent::GetMetaClassStatic() ) )
	{
		auto comp = val->ConstructPtr().Value< XE::SceneComponentPtr >();

		if( comp )
		{
			comp->_Handle = _HandleTable.Alloc();

			comp->_World = GetWorld();
			comp->_GameObject = XE_THIS( GameObject );

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

			XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( ThreadType::GAME, [comp]()
																						  {
																							  comp->Startup();
																						  } );
		}

		return comp;
	}

	return nullptr;
}

XE::BehaviorComponentPtr XE::GameObject::AddBehaviorComponent( IMetaClassPtr val )
{
	if( val->CanConvert( BehaviorComponent::GetMetaClassStatic() ) )
	{
		auto comp = val->ConstructPtr().Value< XE::BehaviorComponentPtr >();

		if( comp )
		{
			comp->_Handle = _HandleTable.Alloc();

			comp->_World = GetWorld();
			comp->_GameObject = XE_THIS( GameObject );

			XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( ThreadType::GAME, [comp]()
																						  {
																							  comp->Startup();
																						  } );

			_BehaviorComponents.push_back( comp );
		}

		return comp;
	}

	return nullptr;
}

XE::BehaviorComponentPtr XE::GameObject::FindBehaviorComponent( const String& val ) const
{
	for ( auto comp : _BehaviorComponents )
	{
		if ( comp->GetName() == val )
		{
			return comp;
		}
	}

	return nullptr;
}

XE::BehaviorComponentPtr XE::GameObject::FindBehaviorComponent( IMetaClassPtr val ) const
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

XE::BehaviorComponentPtr XE::GameObject::FindBehaviorComponent( ComponentHandle val ) const
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

	XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( ThreadType::GAME, [val]()
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

		XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( ThreadType::GAME, [val]()
																					  {
																						  val->Clearup();
																					  } );

		return true;
	}

	return false;
}

XE::SceneComponentPtr XE::GameObject::GetSceneComponent() const
{
	return _SceneComponent;
}

const XE::Array<XE::BehaviorComponentPtr> & XE::GameObject::GetBehaviorComponents() const
{
	return _BehaviorComponents;
}

void XE::GameObject::ProcessEvent( const EventPtr & val )
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
		_SceneComponent->_GameObject = XE_THIS( GameObject );
		_SceneComponent->_Transform.SetParent( &GetTransform() );

		_SceneComponent->Startup();
	}

	for( auto it : _BehaviorComponents )
	{
		it->_World = GetWorld();
		it->_GameObject = XE_THIS( GameObject );

		it->Startup();
	}
}

void XE::GameObject::Update( XE::float32 dt )
{
	if( GetEnable() == false )
	{
		return;
	}

	if( _SceneComponent )
	{
		_SceneComponent->Update( dt );
	}

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
	if( _SceneComponent )
	{
		_SceneComponent->Clearup();
	}

	_SceneComponent = nullptr;

	for( auto it : _BehaviorComponents )
	{
		it->Clearup();
	}

	_BehaviorComponents.clear();
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
