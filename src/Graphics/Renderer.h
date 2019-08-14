/*!
 * \file    Renderer.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERER_H__E2EF5FD6_6A10_4754_86CC_3EA007879A4F
#define __RENDERER_H__E2EF5FD6_6A10_4754_86CC_3EA007879A4F

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Renderer : public std::enable_shared_from_this< Renderer >
{
	OBJECT( Renderer )
	
public:
	Renderer();
	
	virtual ~Renderer();

public:
	void Startup();

	void Render( RenderContextPtr & context, CameraPtr & camera );

	void Clearup();

protected:
	virtual void OnStartup() = 0;

	virtual void OnRender( RenderContextPtr & context, CameraPtr & camera ) = 0;

	virtual void OnClearup() = 0;

private:
	RenderQueuePtr _Queue;
};

END_XE_NAMESPACE

#endif //__RENDERER_H__E2EF5FD6_6A10_4754_86CC_3EA007879A4F
