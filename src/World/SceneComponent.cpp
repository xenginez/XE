#include "SceneComponent.h"

#include "GameObject.h"

USING_XE

BEG_META( SceneComponent )
type->Property( "Parent", &SceneComponent::_ParentHandle, IMetaProperty::NoDesign );
type->Property( "Children", &SceneComponent::_ChildrenHandle, IMetaProperty::NoDesign );
type->Property( "WorldScale", &SceneComponent::GetWorldScale, &SceneComponent::SetWorldScale, IMetaProperty::NoDesign | IMetaProperty::NoClone | IMetaProperty::NoSerialize );
type->Property( "WorldPosition", &SceneComponent::GetWorldPosition, &SceneComponent::SetWorldPosition, IMetaProperty::NoDesign | IMetaProperty::NoClone | IMetaProperty::NoSerialize );
type->Property( "WorldRotation", &SceneComponent::GetWorldRotation, &SceneComponent::SetWorldRotation, IMetaProperty::NoDesign | IMetaProperty::NoClone | IMetaProperty::NoSerialize );
type->Property( "RelativeScale", &SceneComponent::GetRelativeScale, &SceneComponent::SetRelativeScale );
type->Property( "RelativePosition", &SceneComponent::GetRelativePosition, &SceneComponent::SetRelativePosition );
type->Property( "RelativeRotation", &SceneComponent::GetRelativeRotation, &SceneComponent::SetRelativeRotation );
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
		_ParentHandle = ComponentHandle::Invalid;
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
	for( auto handle : _ChildrenHandle )
	{
		if( auto child = GetGameObject()->FindComponentT<SceneComponent>( handle ) )
		{
			if( child->GetName() == val )
			{
				return child;
			}
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( IMetaClassPtr val ) const
{
	for( auto handle : _ChildrenHandle )
	{
		if( auto child = GetGameObject()->FindComponentT<SceneComponent>( handle ) )
		{
			if( child->GetMetaClass()->CanConvert( val ) )
			{
				return child;
			}
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( ComponentHandle val ) const
{
	for( auto handle : _ChildrenHandle )
	{
		if( handle == val )
		{
			return GetGameObject()->FindComponentT<SceneComponent>( handle );
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( const String& val ) const
{
	if( auto child = FindChild( val ) )
	{
		return child;
	}

	for ( auto handle : _ChildrenHandle )
	{
		if( auto child = GetGameObject()->FindComponentT<SceneComponent>( handle ) )
		{
			if( auto ret = child->FindChildFromTree( val ) )
			{
				return ret;
			}
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( IMetaClassPtr val ) const
{
	if( auto child = FindChild( val ) )
	{
		return child;
	}

	for( auto handle : _ChildrenHandle )
	{
		if( auto child = GetGameObject()->FindComponentT<SceneComponent>( handle ) )
		{
			if( auto ret = child->FindChildFromTree( val ) )
			{
				return ret;
			}
		}
	}

	return nullptr;
}

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( ComponentHandle val ) const
{
	if( auto child = FindChild( val ) )
	{
		return child;
	}

	for( auto handle : _ChildrenHandle )
	{
		if( auto child = GetGameObject()->FindComponentT<SceneComponent>( handle ) )
		{
			if( auto ret = child->FindChildFromTree( val ) )
			{
				return ret;
			}
		}
	}

	return nullptr;
}

void XE::SceneComponent::Startup()
{
	Super::Startup();

	auto children = GetChildren();
	for ( auto child : children )
	{
		child->Startup();
	}
}

void XE::SceneComponent::Update( XE::real dt )
{
	if( _Enabled == false || _Update == false )
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

	Super::Clearup();
}

const AABB & XE::SceneComponent::GetBoundingBox()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return _BoundingBox;
}

XE::Vec3 XE::SceneComponent::GetWorldUp()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return Mathf::Rotate( _WorldRotation, Vec3::Up );
}

XE::Vec3 XE::SceneComponent::GetWorldRight()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return Mathf::Rotate( _WorldRotation, Vec3::Right );
}

XE::Vec3 XE::SceneComponent::GetWorldForward()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return Mathf::Rotate( _WorldRotation, Vec3::Forward );
}

XE::Vec3 XE::SceneComponent::GetRelativeUp() const
{
	return Mathf::Rotate( _RelativeRotation, Vec3::Up );
}

XE::Vec3 XE::SceneComponent::GetRelativeRight() const
{
	return Mathf::Rotate( _RelativeRotation, Vec3::Right );
}

XE::Vec3 XE::SceneComponent::GetRelativeForward() const
{
	return Mathf::Rotate( _RelativeRotation, Vec3::Forward );
}

const XE::Vec3 & XE::SceneComponent::GetWorldScale()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return _WorldScale;
}

void XE::SceneComponent::SetWorldScale( const Vec3 & val )
{
	_WorldScale = val;
	SetRelativeScale( GetParent() ? val / GetParent()->GetWorldScale() : val );
}

const XE::Vec3 & XE::SceneComponent::GetWorldPosition()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return _WorldPosition;
}

void XE::SceneComponent::SetWorldPosition( const Vec3 & val )
{
	_WorldPosition = val;
	SetRelativePosition( GetParent() ? val - GetParent()->GetWorldPosition() : val );
}

const XE::Quat & XE::SceneComponent::GetWorldRotation()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return _WorldRotation;
}

void XE::SceneComponent::SetWorldRotation( const Quat & val )
{
	_WorldRotation = val;
	SetRelativeRotation( GetParent() ? Mathf::Inverse( GetParent()->GetWorldRotation() ) * val : val );
}

const XE::Vec3 & XE::SceneComponent::GetRelativeScale() const
{
	return _RelativeScale;
}

void XE::SceneComponent::SetRelativeScale( const Vec3 & val )
{
	if( _RelativeScale != val )
	{
		_Dirty = true;

		_RelativeScale = val;
	}
}

const XE::Vec3 & XE::SceneComponent::GetRelativePosition() const
{
	return _RelativePosition;
}

void XE::SceneComponent::SetRelativePosition( const Vec3 & val )
{
	if( _RelativePosition != val )
	{
		_Dirty = true;

		_RelativePosition = val;
	}
}

const XE::Quat & XE::SceneComponent::GetRelativeRotation() const
{
	return _RelativeRotation;
}

void XE::SceneComponent::SetRelativeRotation( const Quat & val )
{
	if( _RelativeRotation != val )
	{
		_Dirty = true;

		_RelativeRotation = val;
	}
}

const XE::Mat4 & XE::SceneComponent::GetWorldTransform() const
{
	return _WorldTransform;
}

void XE::SceneComponent::SetWorldTransform( const Mat4 & val )
{
	_WorldTransform = val;

	Mathf::TRS( _WorldTransform, _WorldPosition, _WorldRotation, _WorldScale );
}

const XE::Mat4 & XE::SceneComponent::GetRelativeTransform() const
{
	return _RelativeTransform;
}

void XE::SceneComponent::SetRelativeTransform( const Mat4 & val )
{
	_RelativeTransform = val;

	Mathf::TRS( _RelativeTransform, _RelativePosition, _RelativeRotation, _RelativeScale );
}

void XE::SceneComponent::UpdateTransform()
{
	if( GetParent() )
	{
		_WorldScale = GetParent()->GetWorldScale() * _RelativeScale;
		_WorldPosition = GetParent()->GetWorldPosition() + _RelativePosition;
		_WorldRotation = GetParent()->GetWorldRotation() * _RelativeRotation;
	}
	else
	{
		_WorldScale = _RelativeScale;
		_WorldPosition = _RelativePosition;
		_WorldRotation = _RelativeRotation;
	}

	_WorldTransform = Mathf::TRS( _WorldPosition, _WorldRotation, _WorldScale );
	_RelativeTransform = Mathf::TRS( _RelativePosition, _RelativeRotation, _RelativeScale );

	AABB boundbox = AABB();

	for( auto & handle : _ChildrenHandle )
	{
		if( auto child = GetGameObject()->FindComponentT<SceneComponent>( handle ) )
		{
			boundbox.Merge( child->GetBoundingBox() );
		}
	}

	_BoundingBox = boundbox;

	_Dirty = false;
}
