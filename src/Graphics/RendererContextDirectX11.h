/*!
 * \file	RendererContextDirectX11.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTDIRECTX11_H__0BC8ECE7_63A4_479F_9079_39840765BAB4
#define RENDERERCONTEXTDIRECTX11_H__0BC8ECE7_63A4_479F_9079_39840765BAB4

#include "RendererContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & (OS_WINDOWS)

class RendererContextDirectX11 : public XE::RendererContext
{
private:
    struct Private;

    using Super = XE::RendererContext;

public:
	RendererContextDirectX11();

	~RendererContextDirectX11() override;

protected:
	void OnRender( XE::Frame* val ) override;

private:
	void RenderItems( XE::Frame * val );

	void RenderBlits( XE::Frame * val );

	void ExecCommand( XE::Buffer & buffer );

private:
	void Blit( const RenderBlit & blit );

	void Draw( const RenderDraw & draw, const RenderBind & bind );

	void Compute( const RenderCompute & compute, const RenderBind & bind );

private:
	void EXEC_RENDERER_INIT();
	void EXEC_RENDERER_SHUTDOWN();
	void EXEC_CREATE_VERTEX_LAYOUT();
	void EXEC_CREATE_INDEX_BUFFER();
	void EXEC_CREATE_VERTEX_BUFFER();
	void EXEC_CREATE_DYNAMIC_INDEX_BUFFER();
	void EXEC_UPDATE_DYNAMIC_INDEX_BUFFER();
	void EXEC_CREATE_DYNAMIC_VERTEX_BUFFER();
	void EXEC_UPDATE_DYNAMIC_VERTEX_BUFFER();
	void EXEC_CREATE_TRANSIENT_INDEX_BUFFER();
	void EXEC_CREATE_TRANSIENT_VERTEX_BUFFER();
	void EXEC_CREATE_SHADER();
	void EXEC_CREATE_PROGRAM();
	void EXEC_CREATE_TEXTURE();
	void EXEC_UPDATE_TEXTURE();
	void EXEC_RESIZE_TEXTURE();
	void EXEC_CREATE_FRAME_BUFFER();
	void EXEC_CREATE_UNIFORM();
	void EXEC_CREATE_OCCLUSION_QUERY();
	void EXEC_END();
	void EXEC_DESTROY_VERTEX_LAYOUT();
	void EXEC_DESTROY_INDEX_BUFFER();
	void EXEC_DESTROY_VERTEX_BUFFER();
	void EXEC_DESTROY_DYNAMIC_INDEX_BUFFER();
	void EXEC_DESTROY_DYNAMIC_VERTEX_BUFFER();
	void EXEC_DESTROY_SHADER();
	void EXEC_DESTROY_PROGRAM();
	void EXEC_DESTROY_TEXTURE();
	void EXEC_DESTROY_FRAMEBUFFER();
	void EXEC_DESTROY_UNIFORM();
	void EXEC_READ_TEXTURE();
	void EXEC_DESTROY_OCCLUSION_QUERY();
	void EXEC_REQUEST_SCREEN_SHOT();

private:
    Private * _p;
};

#endif

XE::RendererContext * CreateRendererContextDirectX11();

END_XE_NAMESPACE

#endif // RENDERERCONTEXTDIRECTX11_H__0BC8ECE7_63A4_479F_9079_39840765BAB4
