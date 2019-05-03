#include "Transform.h"

USING_XE

BEGIN_META( Transform )
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

XE::Vec3 XE::Transform::GetWorldUp() const
{
	return Mathf::Rotate( _WorldRotation, Vec3::Up );
}

XE::Vec3 XE::Transform::GetWorldRight() const
{
	return Mathf::Rotate( _WorldRotation, Vec3::Right );
}

XE::Vec3 XE::Transform::GetWorldForward() const
{
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
		UpdateTransformCache();
	}

	return _WorldScale;
}

void XE::Transform::SetWorldScale( const Vec3& val )
{
	_WorldScale = val;
	_RelativeScale = _Parent ? val / _Parent->GetWorldScale() : val;
}

const XE::Vec3& XE::Transform::GetWorldPosition()
{
	if ( _Dirty )
	{
		UpdateTransformCache();
	}

	return _WorldPosition;
}

void XE::Transform::SetWorldPosition( const Vec3& val )
{
	_WorldPosition = val;
	_RelativePosition = _Parent ? val - _Parent->GetWorldPosition() : val;
}

const XE::Quat& XE::Transform::GetWorldRotation()
{
	if ( _Dirty )
	{
		UpdateTransformCache();
	}

	return _WorldRotation;
}

void XE::Transform::SetWorldRotation( const Quat& val )
{
	_WorldRotation = val;
	_RelativeRotation = _Parent ? Mathf::Inverse( _Parent->GetWorldRotation() ) * val : val;
}

const XE::Vec3& XE::Transform::GetRelativeScale() const
{
	return _RelativeScale;
}

void XE::Transform::SetRelativeScale( const Vec3& val )
{
	_RelativeScale = val;

	_Dirty = true;
}

const XE::Vec3& XE::Transform::GetRelativePosition() const
{
	return _RelativePosition;
}

void XE::Transform::SetRelativePosition( const Vec3& val )
{
	_RelativePosition = val;

	_Dirty = true;
}

const XE::Quat& XE::Transform::GetRelativeRotation() const
{
	return _RelativeRotation;
}

void XE::Transform::SetRelativeRotation( const Quat& val )
{
	_RelativeRotation = val;

	_Dirty = true;
}

void XE::Transform::UpdateTransformCache()
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

	_TransformCache[0] = Mathf::Translation( _WorldPosition ) * Mathf::Rotation( _WorldRotation ) * Mathf::Scale( _WorldScale );

	_Dirty = false;
}

const XE::Mat4& XE::Transform::GetTransformCache( XE::uint64 val ) const
{
	return _TransformCache[0];
}
