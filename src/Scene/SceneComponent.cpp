#include "SceneComponent.h"

#include "World.h"
#include "GameObject.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>

BEG_META( XE::SceneComponent )
type->Property( "Children", &XE::SceneComponent::_Children, XE::IMetaProperty::NoDesign );
type->Property( "Transform", &XE::SceneComponent::_Transform );
END_META()

XE::SceneComponent::SceneComponent()
{

}

XE::SceneComponent::~SceneComponent()
{

}

XE::SceneComponentPtr XE::SceneComponent::GetRoot()
{
	if ( auto parent = GetParent() )
	{
		return parent->GetRoot();
	}

	return XE_THIS( XE::SceneComponent );
}

XE::SceneComponentPtr XE::SceneComponent::GetParent() const
{
	return _Parent.lock();
}

const XE::Array< XE::SceneComponentPtr > & XE::SceneComponent::GetChildren() const
{
	return _Children;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( const XE::String& val ) const
{
	for( auto child : _Children )
	{
		if( child->GetName() == val )
		{
			return child;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( XE::IMetaClassPtr val ) const
{
	for( auto child : _Children )
	{
		if( child->GetMetaClass()->CanConvert( val ) )
		{
			return child;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( XE::ComponentHandle val ) const
{
	for( auto child : _Children )
	{
		if( child->GetHandle() == val )
		{
			return child;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( const XE::String& val ) const
{
	if( auto child = FindChild( val ) )
	{
		return child;
	}

	for ( auto child : _Children )
	{
		if( auto ret = child->FindChildFromTree( val ) )
		{
			return ret;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( XE::IMetaClassPtr val ) const
{
	if( auto child = FindChild( val ) )
	{
		return child;
	}

	for( auto child : _Children )
	{
		if( auto ret = child->FindChildFromTree( val ) )
		{
			return ret;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( XE::ComponentHandle val ) const
{
	if( auto child = FindChild( val ) )
	{
		return child;
	}

	for( auto child : _Children )
	{
		if( auto ret = child->FindChildFromTree( val ) )
		{
			return ret;
		}
	}

	return nullptr;
}

void XE::SceneComponent::Startup()
{
	for( auto child : _Children )
	{
		child->_Parent = XE_THIS( XE::SceneComponent );

		child->_Transform.SetParent( &_Transform );
	}

	Super::Startup();

	for ( auto child : _Children )
	{
		child->Startup();
	}
}

void XE::SceneComponent::Update( XE::float32 dt )
{
	if( GetEnabled() == false )
	{
		return;
	}

	OnUpdate( dt );

	for ( auto child : _Children )
	{
		child->Update( dt );
	}
}

void XE::SceneComponent::LateUpdate( XE::float32 dt )
{
	if( GetEnabled() == false )
	{
		return;
	}

	OnLateUpdate( dt );

	for( auto child : _Children )
	{
		child->LateUpdate( dt );
	}
}

void XE::SceneComponent::Clearup()
{
	for ( auto child : _Children )
	{
		child->Clearup();
	}

	Super::Clearup();
}

XE::AABB XE::SceneComponent::GetBoundingBox()
{
	AABB boundbox = AABB();

	for( auto & child : _Children )
	{
		boundbox.Merge( child->GetBoundingBox() );
	}

	return boundbox;
}

XE::Transform & XE::SceneComponent::GetTransform()
{
	return _Transform;
}
