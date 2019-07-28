/*!
 * \file	Camera.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CAMERA_H__657DECFE_2C68_4602_9206_C058BA10F2C2
#define CAMERA_H__657DECFE_2C68_4602_9206_C058BA10F2C2

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Camera : public XE::Object
{
	OBJECT( Camera, Object )

public:
	Camera();

	~Camera();

public:
	void Startup();

	void Clearup();

public:
	XE::CameraType GetType() const;

	void SetType( XE::CameraType val );

	XE::float32 GetFOV() const;

	void SetFOV( XE::float32 val );

	XE::float32 GetFar() const;

	void SetFar( XE::float32 val );

	XE::float32 GetNear() const;

	void SetNear( XE::float32 val );

	XE::float32 GetAspect() const;

	void SetAspect( XE::float32 val );

	const Mat4 & GetTransform() const;

	void SetTransform( const Mat4 & val );

	const Mat4 & GetProjMatrix() const;

	void SetProjMatrix( const Mat4 & val );

	const Mat4 & GetViewMatrix() const;

	void SetViewMatrix( const Mat4 & val );

	const Frustum & GetFrustum() const;

	void SetFrustum( const Frustum & val );

public:
	const ViewportPtr & GetViewport() const;

	void SetViewport( const ViewportPtr & val );

	const RendererPtr & GetRenderer() const;

	void SetRenderer( const RendererPtr & val );

private:
	CameraType _Type;
	XE::float32 _FOV;
	XE::float32 _Far;
	XE::float32 _Near;
	XE::float32 _Aspect;
	Mat4 _Transform;
	Mat4 _ProjMatrix;
	Mat4 _ViewMatrix;
	Frustum _Frustum;

	ViewportPtr _Viewport;
	RendererPtr _Renderer;
};

END_XE_NAMESPACE

#endif // CAMERA_H__657DECFE_2C68_4602_9206_C058BA10F2C2
