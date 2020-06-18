#include "SceneComponent.h"

#include "GameObject.h"

#include <Interface/IFramework.h>
#include <Interface/IThreadService.h>


BEG_META( XE::SceneComponent )
type->Property( "Children", &SceneComponent::_Children, IMetaProperty::NoDesign );
type->Property( "WorldTransform", &SceneComponent::_WorldTransform, IMetaProperty::NoDesign );
type->Property( "RelativeTransform", &SceneComponent::_RelativeTransform, IMetaProperty::NoDesign );
END_META()

XE::SceneComponent::SceneComponent()
	:_Dirty( false )
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
	return _Parent.lock();
}

const XE::Array< XE::SceneComponentPtr > & XE::SceneComponent::GetChildren() const
{
	return _Children;
}

XE::SceneComponentPtr XE::SceneComponent::FindChild( const String& val ) const
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

XE::SceneComponentPtr XE::SceneComponent::FindChild( IMetaClassPtr val ) const
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

XE::SceneComponentPtr XE::SceneComponent::FindChild( ComponentHandle val ) const
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

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( const String& val ) const
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

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( IMetaClassPtr val ) const
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

XE::SceneComponentPtr XE::SceneComponent::FindChildFromTree( ComponentHandle val ) const
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
	}

	Super::Startup();

	for ( auto child : _Children )
	{
		child->Startup();
	}
}

void XE::SceneComponent::Update( XE::float32 dt )
{
	if( _Enabled == false || _Update == false )
	{
		return;
	}

	OnUpdate( dt );

	for ( auto child : _Children )
	{
		child->Update( dt );
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

const XE::AABB & XE::SceneComponent::GetBoundingBox()
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
	if( auto parent = _Parent.lock() )
	{
		_WorldScale = parent->GetWorldScale() * _RelativeScale;
		_WorldPosition = parent->GetWorldPosition() + _RelativePosition;
		_WorldRotation = parent->GetWorldRotation() * _RelativeRotation;
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

	for( auto & child : _Children )
	{
		boundbox.Merge( child->GetBoundingBox() );
	}

	_BoundingBox = boundbox;

	_Dirty = false;
}
