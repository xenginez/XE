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
	void OnRender( XE::RenderFrame * val ) override;

private:
	void BlitCall( XE::RenderFrame * frame, XE::RenderBlit * item );

	void DrawCall( XE::RenderFrame * frame, XE::RenderDraw * item, XE::RenderBind * bind );

	void ComputeCall( XE::RenderFrame * frame, XE::RenderCompute * item, XE::RenderBind * bind );

	void ExecCommand( XE::RenderFrame * frame, XE::Buffer * buffer );

private:
	void Init( XE::RenderFrame * frame );

	void Shutdown( XE::RenderFrame * frame );

private:
	void CreateProgram( XE::RenderFrame * frame );

	void CreateFrameBuffer( XE::RenderFrame * frame );

	void CreateVertexLayout( XE::RenderFrame * frame );

	void CreateOcclusionQuery( XE::RenderFrame * frame );

	void CreateIndirectBuffer( XE::RenderFrame * frame );

	void CreateShader( XE::RenderFrame * frame );

	void CreateTexture( XE::RenderFrame * frame );

	void CreateIndexBuffer( XE::RenderFrame * frame );

	void CreateVertexBuffer( XE::RenderFrame * frame );

	void CreateDynamicIndexBuffer( XE::RenderFrame * frame );

	void CreateDynamicVertexBuffer( XE::RenderFrame * frame );

public:
	void ReadTexture( XE::RenderFrame * frame );

	void UpdateTexture( XE::RenderFrame * frame );

	void RequestScreenShot( XE::RenderFrame * frame );

	void UpdateDynamicIndexBuffer( XE::RenderFrame * frame );

	void UpdateDynamicVertexBuffer( XE::RenderFrame * frame );

public:
	void DestoryShader( XE::RenderFrame * frame );

	void DestoryProgram( XE::RenderFrame * frame );

	void DestoryTexture( XE::RenderFrame * frame );

	void DestoryFrameBuffer( XE::RenderFrame * frame );

	void DestoryIndexBuffer( XE::RenderFrame * frame );

	void DestoryVertexLayout( XE::RenderFrame * frame );

	void DestoryVertexBuffer( XE::RenderFrame * frame );

	void DestoryIndirectBuffer( XE::RenderFrame * frame );

	void DestoryOcclusionQuery( XE::RenderFrame * frame );

	void DestoryDynamicIndexBuffer( XE::RenderFrame * frame );

	void DestoryDynamicVertexBuffer( XE::RenderFrame * frame );

private:
    Private * _p;
};

XE_INLINE XE::RendererContext * CreateRendererContextDirectX11()
{
	return new XE::RendererContextDirectX11();
}

#else

XE_INLINE XE::RendererContext * XE::CreateRendererContextDirectX11()
{
	return nullptr;
}

#endif

END_XE_NAMESPACE

#endif // RENDERERCONTEXTDIRECTX11_H__0BC8ECE7_63A4_479F_9079_39840765BAB4
