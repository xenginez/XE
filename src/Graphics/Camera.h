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

class XE_API Camera : public XE::Object
{
	OBJECT( Camera, Object )

public:
	Camera();

	~Camera();

public:
	XE::float32 GetFOV() const;

	void SetFOV( XE::float32 val );

	XE::float32 GetFar() const;

	void SetFar( XE::float32 val );

	XE::float32 GetNear() const;

	void SetNear( XE::float32 val );

	XE::float32 GetDepth() const;

	void SetDepth( XE::float32 val );

	XE::float32 GetAspect() const;

	void SetAspect( XE::float32 val );

	const XE::Mat4 & GetTransform() const;

	void SetTransform( const XE::Mat4 & val );

	const XE::Mat4 & GetProjMatrix() const;

	void SetProjMatrix( const XE::Mat4 & val );

	const XE::Mat4 & GetViewMatrix() const;

	void SetViewMatrix( const XE::Mat4 & val );

	const Frustum & GetFrustum() const;

	void SetFrustum( const Frustum & val );

public:
	const Rect & GetViewport() const;

	void SetViewport( const Rect & val );

	const ViewHandle & GetViewHandle() const;

	void SetViewHandle( const ViewHandle & val );

private:
	XE::float32 _FOV;
	XE::float32 _Far;
	XE::float32 _Near;
	XE::float32 _Depth;
	XE::float32 _Aspect;
	XE::Mat4 _Transform;
	XE::Mat4 _ProjMatrix;
	XE::Mat4 _ViewMatrix;
	XE::Frustum _Frustum;
	XE::Rect _Viewport;
	XE::ViewHandle _ViewHandle;
};

END_XE_NAMESPACE

#endif // CAMERA_H__657DECFE_2C68_4602_9206_C058BA10F2C2
