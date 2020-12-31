#include "GameObject.h"

#include "Component.h"
#include "SceneComponent.h"
#include "BehaviorComponent.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>

BEG_META( XE::GameObject )
type->Property( "RootSceneComponent", &GameObject::_RootSceneComponent, IMetaProperty::NoDesign );
type->Property( "BehaviorComponents", &GameObject::_BehaviorComponents, IMetaProperty::NoDesign );
END_META()

XE::GameObject::GameObject()
	:_Type( GameObjectType::STATIC )
{
	_RootSceneComponent = XE::MakeShared<XE::SceneComponent>();
	_RootSceneComponent->SetName( "Root" );
}

XE::GameObject::~GameObject()
{

}

const XE::AABB & XE::GameObject::GetBoundingBox() const
{
	return _RootSceneComponent->GetBoundingBox();
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
			comp->_GameObject = XE_THIS( GameObject );
			comp->_Handle = _HandleTable.Alloc();

			comp->_Parent = parent;
			parent->_Children.push_back( comp );

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
			comp->_GameObject = XE_THIS( GameObject );
			comp->_Handle = _HandleTable.Alloc();

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

			XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( ThreadType::GAME, [val]()
																						  {
																							  val->Clearup();
																						  } );

			return true;
		}
	}

	return false;
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

XE::SceneComponentPtr XE::GameObject::GetRootSceneComponent() const
{
	return _RootSceneComponent;
}

const XE::Array<XE::BehaviorComponentPtr> & XE::GameObject::GetBehaviorComponents() const
{
	return _BehaviorComponents;
}

XE::Vec3f XE::GameObject::GetWorldUp()
{
	return _RootSceneComponent->GetWorldUp();
}

XE::Vec3f XE::GameObject::GetWorldRight()
{
	return _RootSceneComponent->GetWorldRight();
}

XE::Vec3f XE::GameObject::GetWorldForward()
{
	return _RootSceneComponent->GetWorldForward();
}

XE::Vec3f XE::GameObject::GetRelativeUp() const
{
	return _RootSceneComponent->GetRelativeUp();
}

XE::Vec3f XE::GameObject::GetRelativeRight() const
{
	return _RootSceneComponent->GetRelativeRight();
}

XE::Vec3f XE::GameObject::GetRelativeForward() const
{
	return _RootSceneComponent->GetRelativeForward();
}

const XE::Vec3f & XE::GameObject::GetWorldScale()
{
	return _RootSceneComponent->GetWorldScale();
}

void XE::GameObject::SetWorldScale( const Vec3f & val )
{
	_RootSceneComponent->SetWorldScale( val );
}

const XE::Vec3f & XE::GameObject::GetWorldPosition()
{
	return _RootSceneComponent->GetWorldPosition();
}

void XE::GameObject::SetWorldPosition( const Vec3f & val )
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

const XE::Vec3f & XE::GameObject::GetRelativeScale() const
{
	return _RootSceneComponent->GetRelativeScale();
}

void XE::GameObject::SetRelativeScale( const Vec3f & val )
{
	_RootSceneComponent->SetRelativeScale( val );
}

const XE::Vec3f & XE::GameObject::GetRelativePosition() const
{
	return _RootSceneComponent->GetRelativePosition();
}

void XE::GameObject::SetRelativePosition( const Vec3f & val )
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

const XE::Mat4x4f & XE::GameObject::GetWorldTransform() const
{
	return _RootSceneComponent->GetWorldTransform();
}

void XE::GameObject::SetWorldTransform( const Mat4x4f & val )
{
	_RootSceneComponent->SetWorldTransform( val );
}

const XE::Mat4x4f & XE::GameObject::GetRelativeTransform() const
{
	return _RootSceneComponent->GetRelativeTransform();
}

void XE::GameObject::SetRelativeTransform( const Mat4x4f & val )
{
	_RootSceneComponent->SetRelativeTransform( val );
}

void XE::GameObject::ProcessEvent( const EventPtr & val )
{
	_RootSceneComponent->ProcessEvent( val );

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
	_RootSceneComponent->_GameObject = XE_THIS( GameObject );

	_RootSceneComponent->Startup();

	for( auto it : _BehaviorComponents )
	{
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
		it->Clearup();
	}

	_BehaviorComponents.clear();
}

void XE::GameObject::OnEnable()
{
	_RootSceneComponent->SetEnabled( GetEnable() );

	for( auto & coms : _BehaviorComponents )
	{
		coms->SetEnabled( GetEnable() );
	}
}

void XE::GameObject::OnDisable()
{
	_RootSceneComponent->SetEnabled( GetEnable() );

	for( auto & coms : _BehaviorComponents )
	{
		coms->SetEnabled( GetEnable() );
	}
}
