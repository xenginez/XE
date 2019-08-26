#include "Camera.h"

#include "Renderer.h"

USING_XE

BEG_META( Camera )
END_META()

XE::Camera::Camera()
	:_Active( true ), _Type( CameraType::ORTHOGRAPHIC ), _FOV( 60.0f ), _Far( 1000.0f ), _Near( 0.1f ), _Depth( 0 ), _Aspect( 1.333f )
{

}

XE::Camera::~Camera()
{

}

bool XE::Camera::GetActive() const
{
	return _Active;
}

void XE::Camera::SetActive( bool val )
{
	_Active = val;
}

XE::CameraType XE::Camera::GetType() const
{
	return _Type;
}

void XE::Camera::SetType( XE::CameraType val )
{
	_Type = val;
}

XE::float32 XE::Camera::GetFOV() const
{
	return _FOV;
}

void XE::Camera::SetFOV( XE::float32 val )
{
	_FOV = val;
}

XE::float32 XE::Camera::GetFar() const
{
	return _Far;
}

void XE::Camera::SetFar( XE::float32 val )
{
	_Far = val;
}

XE::float32 XE::Camera::GetNear() const
{
	return _Near;
}

void XE::Camera::SetNear( XE::float32 val )
{
	_Near = val;
}

XE::float32 XE::Camera::GetDepth() const
{
	return _Depth;
}

void XE::Camera::SetDepth( XE::float32 val )
{
	_Depth = val;
}

XE::float32 XE::Camera::GetAspect() const
{
	return _Aspect;
}

void XE::Camera::SetAspect( XE::float32 val )
{
	_Aspect = val;
}

const XE::Mat4 & XE::Camera::GetTransform() const
{
	return _Transform;
}

void XE::Camera::SetTransform( const Mat4 & val )
{
	_Transform = val;
}

const XE::Mat4 & XE::Camera::GetProjMatrix() const
{
	return _ProjMatrix;
}

void XE::Camera::SetProjMatrix( const Mat4 & val )
{
	_ProjMatrix = val;
}

const XE::Mat4 & XE::Camera::GetViewMatrix() const
{
	return _ViewMatrix;
}

void XE::Camera::SetViewMatrix( const Mat4 & val )
{
	_ViewMatrix = val;
}

const XE::Frustum & XE::Camera::GetFrustum() const
{
	return _Frustum;
}

void XE::Camera::SetFrustum( const Frustum & val )
{
	_Frustum = val;
}

const XE::ViewportPtr & XE::Camera::GetViewport() const
{
	return _Viewport;
}

void XE::Camera::SetViewport( const ViewportPtr & val )
{
	_Viewport = val;
}
