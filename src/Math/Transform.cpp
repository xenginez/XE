#include "Transform.h"

#include "Mathf.h"

BEG_META( XE::Transform )
type->Property( "Up", &XE::Transform::GetUp );
type->Property( "Down", &XE::Transform::GetDown );
type->Property( "Left", &XE::Transform::GetLeft );
type->Property( "Right", &XE::Transform::GetRight );
type->Property( "Forward", &XE::Transform::GetForward );
type->Property( "Backward", &XE::Transform::GetBackward );
type->Property( "Parent", &XE::Transform::GetParent, &XE::Transform::SetParent );
type->Property( "WorldPosition", &XE::Transform::GetWorldPosition, &XE::Transform::SetWorldPosition );
type->Property( "WorldRotation", &XE::Transform::GetWorldRotation, &XE::Transform::SetWorldRotation );
type->Property( "WorldScale", &XE::Transform::GetWorldScale, &XE::Transform::SetWorldScale );
type->Property( "WorldTransform", &XE::Transform::GetWorldTransform, &XE::Transform::SetWorldTransform );
type->Property( "RelativePosition", &XE::Transform::GetRelativePosition, &XE::Transform::SetRelativePosition );
type->Property( "RelativeRotation", &XE::Transform::GetRelativeRotation, &XE::Transform::SetRelativeRotation );
type->Property( "RelativeScale", &XE::Transform::GetRelativeScale, &XE::Transform::SetRelativeScale );
type->Property( "RelativeTransform", &XE::Transform::GetRelativeTransform, &XE::Transform::SetRelativeTransform );
END_META()

XE::Transform const XE::Transform::Identity = XE::Transform();

XE::Transform::Transform( Transform * parent /*= nullptr */ )
	: _Position( XE::Vec3f::Zero )
	, _Rotation( XE::Quat::Identity )
	, _Scale( XE::Vec3f::One )
	, _Transform( XE::Mat4x4f::Identity )
	, _Parent( parent )
{

}

XE::Transform::Transform( const XE::Mat4x4f & val, Transform * parent /*= nullptr */ )
	: _Transform( val )
	, _Parent( parent )
{
	XE::Mathf::TRS( _Transform, _Position, _Rotation, _Scale );
}

XE::Transform::Transform( const XE::Vec3f & position, const XE::Quat & rotation, const XE::Vec3f & scale, Transform * parent /*= nullptr */ )
	: _Position( position )
	, _Rotation( rotation )
	, _Scale( scale )
	, _Parent( parent )
{
	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

XE::Transform::Transform( const Transform & val, Transform * parent /*= nullptr */ )
	: _Position( val._Position )
	, _Rotation( val._Rotation )
	, _Scale( val._Scale )
	, _Transform( val._Transform )
	, _Parent( parent )
{

}

XE::Transform::~Transform()
{

}

XE::Transform * XE::Transform::GetParent() const
{
	return _Parent;
}

void XE::Transform::SetParent( XE::Transform * parent )
{
	_Parent = parent;
}

XE::Vec3f XE::Transform::GetUp() const
{
	return Mathf::Rotate( GetWorldRotation(), Vec3f::Up );
}

XE::Vec3f XE::Transform::GetDown() const
{
	return Mathf::Rotate( GetWorldRotation(), -Vec3f::Up );
}

XE::Vec3f XE::Transform::GetLeft() const
{
	return Mathf::Rotate( GetWorldRotation(), -Vec3f::Right );
}

XE::Vec3f XE::Transform::GetRight() const
{
	return Mathf::Rotate( GetWorldRotation(), Vec3f::Right );
}

XE::Vec3f XE::Transform::GetForward() const
{
	return Mathf::Rotate( GetWorldRotation(), Vec3f::Forward );
}

XE::Vec3f XE::Transform::GetBackward() const
{
	return Mathf::Rotate( GetWorldRotation(), -Vec3f::Forward );
}

void XE::Transform::Translate( const XE::Vec3f & val )
{
	_Position += val;

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

void XE::Transform::Rotate( const XE::Quat & val )
{
	_Rotation *= val;

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

void XE::Transform::Scale( const XE::Vec3f & val )
{
	_Scale *= val;

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

XE::Vec3d XE::Transform::GetWorldPosition() const
{
	return _Parent ? _Parent->GetWorldPosition() + XE::Vec3d( _Position ) : XE::Vec3d( _Position );
}

void XE::Transform::SetWorldPosition( const XE::Vec3d & val )
{
	_Position = val - ( _Parent ? _Parent->GetWorldPosition() : XE::Vec3d::Zero );

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

XE::Quat XE::Transform::GetWorldRotation() const
{
	return _Parent ? _Parent->GetWorldRotation() * _Rotation : _Rotation;
}

void XE::Transform::SetWorldRotation( const XE::Quat & val )
{
	_Rotation = val * ( _Parent ? XE::Mathf::Inverse( _Parent->GetWorldRotation() ) : XE::Quat::Identity );

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

XE::Vec3d XE::Transform::GetWorldScale() const
{
	return _Parent ? _Parent->GetWorldScale() * XE::Vec3d( _Scale ) : XE::Vec3d( _Scale );
}

void XE::Transform::SetWorldScale( const XE::Vec3d & val )
{
	_Scale = val / ( _Parent ? _Parent->GetWorldScale() : XE::Vec3d::One );

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

XE::Mat4x4d XE::Transform::GetWorldTransform() const
{
	return _Parent ? _Parent->GetWorldTransform() * XE::Mat4x4d( _Transform ) : XE::Mat4x4d( _Transform );
}

void XE::Transform::SetWorldTransform( const XE::Mat4x4d & val )
{
	_Transform = val * ( _Parent ? _Parent->GetWorldTransform() * XE::Mathf::Inverse( _Transform ) : XE::Mat4x4d::Identity );

	XE::Mathf::TRS( _Transform, _Position, _Rotation, _Scale );
}

const XE::Vec3f & XE::Transform::GetRelativePosition() const
{
	return _Position;
}

void XE::Transform::SetRelativePosition( const XE::Vec3f & val )
{
	_Position = val;

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

const XE::Quat & XE::Transform::GetRelativeRotation() const
{
	return _Rotation;
}

void XE::Transform::SetRelativeRotation( const XE::Quat & val )
{
	_Rotation = val;

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

const XE::Vec3f & XE::Transform::GetRelativeScale() const
{
	return _Scale;
}

void XE::Transform::SetRelativeScale( const XE::Vec3f & val )
{
	_Scale = val;

	_Transform = XE::Mathf::TRS( _Position, _Rotation, _Scale );
}

const XE::Mat4x4f & XE::Transform::GetRelativeTransform() const
{
	return _Transform;
}

void XE::Transform::SetRelativeTransform( const XE::Mat4x4f & val )
{
	_Transform = val;

	XE::Mathf::TRS( _Transform, _Position, _Rotation, _Scale );
}

XE::Transform XE::operator*( const Transform & left, const Transform & right )
{
	return { left.GetWorldTransform() * right.GetWorldTransform() };
}
