/*!
 * \file   Viewport.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/29
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VIEWPORT_H__4F451658_360B_46E4_AD0A_C06AA68683AA
#define __VIEWPORT_H__4F451658_360B_46E4_AD0A_C06AA68683AA

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Viewport
{
	OBJECT( Viewport )

public:
	Viewport();

	~Viewport();

public:
	XE::real GetX() const;

	void SetX( XE::real val );

	XE::real GetY() const;

	void SetY( XE::real val );

	XE::real GetWidth() const;

	void SetWidth( XE::real val );

	XE::real GetHeight() const;

	void SetHeight( XE::real val );

	const Rect & GetRect() const;

	void SetRect( const Rect & val );

public:
	XE::real GetMinDepth() const;

	void SetMinDepth( XE::real val );

	XE::real GetMaxDepth() const;

	void SetMaxDepth( XE::real val );

	const Vec2 & GetDepth() const;

	void SetDepth( const Vec2 & val );

public:
	RenderTargetPtr GetRenderTarget() const;

private:
	void SetRenderTarget( const RenderTargetPtr & val );

private:
	Rect _Rect;
	Vec2 _Depth;
	RenderTargetWPtr _RenderTarget;
};

END_XE_NAMESPACE

#endif // __VIEWPORT_H__4F451658_360B_46E4_AD0A_C06AA68683AA
