/*!
 * \file   CameraComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/15
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CAMERACOMPONENT_H__80053273_5129_4AD0_901F_7E5A0E50DD44
#define __CAMERACOMPONENT_H__80053273_5129_4AD0_901F_7E5A0E50DD44

#include "Type.h"

BEG_XE_NAMESPACE

class RENDER_API CameraComponent : public XE::RenderComponent
{
	OBJECT( CameraComponent, RenderComponent )

public:
	CameraComponent();

	~CameraComponent();

public:
	ProjectionMode GetProjectionMode() const;

	void SetProjectionMode( ProjectionMode  val );

	float GetFOV() const;

	void SetFOV( float val );

	float GetNearClip() const;

	void SetNearClip( float val );

	float GetFarClip() const;

	void SetFarClip( float val );

	float GetOrthoSize() const;

	void SetOrthoSize( float val );

	Rect GetViewportRect() const;

	void SetViewportSize( const Rect& val );

	float GetAspectRatio() const;

	void SetAspectRatio( float aspect, bool locked = false );

public:
	float GetPPU() const;

	float GetZoomFactor() const;

	const Frustum& GetFrustum() const;

	const Frustum& GetClippingVolume() const;

	const Mat4& GetView() const;

	const Mat4& GetProjection() const;

	Mat4 GetViewProjection() const;

public:
	bool IsAspectLocked() const;

	bool IsFrustumLocked() const;

public:
	void LockFrustum( bool val );

public:
	Vec2 WorldToViewport( const Vec3& val ) const;

	Vec3 ViewportToWorld( const Vec2& val, float distance = 1000.0f ) const;

private:
	ProjectionMode _Mode = ProjectionMode::PERSPECTIVE;
	float _FOV = 60.0f;
	float _Near = 0.01f;
	float _Far = 10000.0f;
	float _OrthoSize = 5;
	Rect _Rect;
	Mat4 _View;
	Mat4 _Projection;
	Frustum _Frustum;
	bool _FrustumLocked = false;
	float _AspectRatio;
	Vec4 _AAData;
};

END_XE_NAMESAPCE

#endif // __CAMERACOMPONENT_H__80053273_5129_4AD0_901F_7E5A0E50DD44
