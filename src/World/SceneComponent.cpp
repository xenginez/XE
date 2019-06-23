#include "SceneComponent.h"

#include "GameObject.h"

USING_XE

BEG_META( SceneComponent )
type->Property( "Transform", &SceneComponent::_Transform );
type->Property( "Parent", &SceneComponent::_ParentHandle, IMetaProperty::NoDesign );
type->Property( "Children", &SceneComponent::_ChildrenHandle, IMetaProperty::NoDesign );
END_META()

XE::SceneComponent::SceneComponent()
{

}

XE::SceneComponent::~SceneComponent()
{

}

XE::Transform * XE::SceneComponent::GetTransform()
{
	return &_Transform;
}

XE::SceneComponentPtr XE::SceneComponent::GetRoot()
{
	if ( auto parent = GetParent() )
	{
		return parent->GetRoot();
	}

	return XE_THIS( SceneComponent );
}

XE::SceneComponentPtr XE::SceneComponent::GetParent() const
{
	return GetGameObject()->FindComponentT<SceneComponent>( _ParentHandle );
}

XE::Array< XE::SceneComponentPtr > XE::SceneComponent::GetChildren() const
{
	XE::Array< XE::SceneComponentPtr > ret;

	for ( auto h : _ChildrenHandle )
	{
		if ( auto c = GetGameObject()->FindComponentT<SceneComponent>( h ) )
		{
			ret.push_back( c );
		}
	}

	return ret;
}

void XE::SceneComponent::AttachToParent( SceneComponentPtr val )
{
	if ( _ParentHandle == val->GetHandle() )
	{
		return;
	}

	if ( auto parent = GetGameObject()->FindComponentT<SceneComponent>( _ParentHandle ) )
	{
		for ( auto it = parent->_ChildrenHandle.begin(); it != parent->_ChildrenHandle.end(); ++it )
		{
			if ( ( *it ) == GetHandle() )
			{
				parent->_ChildrenHandle.erase( it );
				break;
			}
		}
	}

	if ( val == nullptr )
	{
		_ParentHandle = ComponentHandle::invalid;
		return;
	}

	_ParentHandle = val->GetHandle();

	if ( auto parent = GetGameObject()->FindComponentT<SceneComponent>( _ParentHandle ) )
	{
		parent->_ChildrenHandle.push_back( GetHandle() );
	}
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( const String& val ) const
{
	auto children = GetChildren();
	for ( auto child : children )
	{
		if ( child->GetName() == val )
		{
			return child;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( IMetaClassPtr val ) const
{
	auto children = GetChildren();
	for ( auto child : children )
	{
		if ( child->GetMetaClass()->CanConvert( val ) )
		{
			return child;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( ComponentHandle val ) const
{
	auto children = GetChildren();
	for ( auto child : children )
	{
		if ( child->GetHandle() == val )
		{
			return child;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( const String& val ) const
{
	auto children = GetChildren();
	for ( auto child : children )
	{
		if ( child->GetName() == val )
		{
			return child;
		}

		if ( auto ret = child->FindChildFromTree( val ) )
		{
			return ret;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( IMetaClassPtr val ) const
{
	auto children = GetChildren();
	for ( auto child : children )
	{
		if ( child->GetMetaClass()->CanConvert( val ) )
		{
			return child;
		}

		if ( auto ret = child->FindChildFromTree( val ) )
		{
			return ret;
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( ComponentHandle val ) const
{
	auto children = GetChildren();
	for ( auto child : children )
	{
		if ( child->GetHandle() == val )
		{
			return child;
		}

		if ( auto ret = child->FindChildFromTree( val ) )
		{
			return ret;
		}
	}

	return nullptr;
}

void XE::SceneComponent::Startup()
{
	_Transform.SetParent( _ParentHandle != ComponentHandle::invalid ? GetParent()->GetTransform() : nullptr );

	OnStartup();

	auto children = GetChildren();
	for ( auto child : children )
	{
		child->Startup();
	}
}

void XE::SceneComponent::Update( XE::real dt )
{
	if ( _Enabled == false || _Update == false )
	{
		return;
	}

	OnUpdate( dt );

	auto children = GetChildren();
	for ( auto child : children )
	{
		child->Update( dt );
	}
}

void XE::SceneComponent::Clearup()
{
	auto children = GetChildren();
	for ( auto child : children )
	{
		child->Clearup();
	}

	OnClearup();
}
