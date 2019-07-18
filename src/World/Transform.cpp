#include "Transform.h"

USING_XE

BEG_META( Transform )
type->Property( "Parent", &Transform::_Parent, IMetaProperty::NoDesign | IMetaProperty::NoClone | IMetaProperty::NoSerialize );
type->Property( "WorldScale", &Transform::GetWorldScale, &Transform::SetWorldScale, IMetaProperty::NoDesign | IMetaProperty::NoClone | IMetaProperty::NoSerialize );
type->Property( "WorldPosition", &Transform::GetWorldPosition, &Transform::SetWorldPosition, IMetaProperty::NoDesign | IMetaProperty::NoClone | IMetaProperty::NoSerialize );
type->Property( "WorldRotation", &Transform::GetWorldRotation, &Transform::SetWorldRotation, IMetaProperty::NoDesign | IMetaProperty::NoClone | IMetaProperty::NoSerialize );
type->Property( "RelativeScale", &Transform::GetRelativeScale, &Transform::SetRelativeScale );
type->Property( "RelativePosition", &Transform::GetRelativePosition, &Transform::SetRelativePosition );
type->Property( "RelativeRotation", &Transform::GetRelativeRotation, &Transform::SetRelativeRotation );
END_META()

XE::Transform::Transform()
	:_WorldScale( Vec3::One ), _WorldPosition( Vec3::Zero ), _WorldRotation( Quat::Zero ), _RelativeScale( Vec3::One ), _RelativePosition( Vec3::Zero ), _RelativeRotation( Quat::Zero ), _Parent( nullptr ), _Dirty( false )
{

}

XE::Transform * XE::Transform::GetParent() const
{
	return _Parent;
}

void XE::Transform::SetParent( Transform * val )
{
	_Parent = val;
}

XE::Vec3 XE::Transform::GetWorldUp()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return Mathf::Rotate( _WorldRotation, Vec3::Up );
}

XE::Vec3 XE::Transform::GetWorldRight()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return Mathf::Rotate( _WorldRotation, Vec3::Right );
}

XE::Vec3 XE::Transform::GetWorldForward()
{
	if( _Dirty )
	{
		UpdateTransform();
	}

	return Mathf::Rotate( _WorldRotation, Vec3::Forward );
}

XE::Vec3 XE::Transform::GetRelativeUp() const
{
	return Mathf::Rotate( _RelativeRotation, Vec3::Up );
}

XE::Vec3 XE::Transform::GetRelativeRight() const
{
	return Mathf::Rotate( _RelativeRotation, Vec3::Right );
}

XE::Vec3 XE::Transform::GetRelativeForward() const
{
	return Mathf::Rotate( _RelativeRotation, Vec3::Forward );
}

const XE::Vec3& XE::Transform::GetWorldScale()
{
	if ( _Dirty )
	{
		UpdateTransform();
	}

	return _WorldScale;
}

void XE::Transform::SetWorldScale( const Vec3& val )
{
	_WorldScale = val;
	SetRelativeScale( _Parent ? val / _Parent->GetWorldScale() : val );
}

const XE::Vec3& XE::Transform::GetWorldPosition()
{
	if ( _Dirty )
	{
		UpdateTransform();
	}

	return _WorldPosition;
}

void XE::Transform::SetWorldPosition( const Vec3& val )
{
	_WorldPosition = val;
	SetRelativePosition( _Parent ? val - _Parent->GetWorldPosition() : val );
}

const XE::Quat& XE::Transform::GetWorldRotation()
{
	if ( _Dirty )
	{
		UpdateTransform();
	}

	return _WorldRotation;
}

void XE::Transform::SetWorldRotation( const Quat& val )
{
	_WorldRotation = val;
	SetRelativeRotation( _Parent ? Mathf::Inverse( _Parent->GetWorldRotation() ) * val : val );
}

const XE::Vec3& XE::Transform::GetRelativeScale() const
{
	return _RelativeScale;
}

void XE::Transform::SetRelativeScale( const Vec3& val )
{
	if( _RelativeScale != val )
	{
		_Dirty = true;

		_RelativeScale = val;
	}
}

const XE::Vec3& XE::Transform::GetRelativePosition() const
{
	return _RelativePosition;
}

void XE::Transform::SetRelativePosition( const Vec3& val )
{
	if( _RelativePosition != val )
	{
		_Dirty = true;

		_RelativePosition = val;
	}
}

const XE::Quat& XE::Transform::GetRelativeRotation() const
{
	return _RelativeRotation;
}

void XE::Transform::SetRelativeRotation( const Quat& val )
{
	if( _RelativeRotation != val )
	{
		_Dirty = true;

		_RelativeRotation = val;
	}
}

const XE::Mat4& XE::Transform::GetWorldTransform() const
{
	return _WorldTransform;
}

void XE::Transform::SetWorldTransform( const Mat4& val )
{
	_WorldTransform = val;

	Mathf::TRS( _WorldTransform, _WorldPosition, _WorldRotation, _WorldScale );
}

const XE::Mat4& XE::Transform::GetRelativeTransform() const
{
	return _RelativeTransform;
}

void XE::Transform::SetRelativeTransform( const Mat4& val )
{
	_RelativeTransform = val;

	Mathf::TRS( _RelativeTransform, _RelativePosition, _RelativeRotation, _RelativeScale );
}

void XE::Transform::UpdateTransform()
{
	if ( _Parent )
	{
		_WorldScale = _Parent->GetWorldScale() * _RelativeScale;
		_WorldPosition = _Parent->GetWorldPosition() + _RelativePosition;
		_WorldRotation = _Parent->GetWorldRotation() * _RelativeRotation;
	}
	else
	{
		_WorldScale = _RelativeScale;
		_WorldPosition = _RelativePosition;
		_WorldRotation = _RelativeRotation;
	}

	_WorldTransform = Mathf::TRS( _WorldPosition, _WorldRotation, _WorldScale );
	_RelativeTransform = Mathf::TRS( _RelativePosition, _RelativeRotation, _RelativeScale );

	_Dirty = false;
}
