#include "Camera.h"

#include "Renderer.h"

USING_XE

XE::Camera::Camera()
{

}

XE::Camera::~Camera()
{

}

void XE::Camera::Startup()
{
	_Renderer->Startup();
}

void XE::Camera::Clearup()
{
	_Renderer->Clearup();

	_Viewport = nullptr;
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

const XE::RendererPtr & XE::Camera::GetRenderer() const
{
	return _Renderer;
}

void XE::Camera::SetRenderer( const RendererPtr & val )
{
	_Renderer = val;
}
