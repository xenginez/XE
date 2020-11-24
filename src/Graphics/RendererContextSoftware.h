#ifndef RENDERERCONTEXTSOFTWARE_H__3145856F_D79A_440A_90B3_558891CD1D3A
#define RENDERERCONTEXTSOFTWARE_H__3145856F_D79A_440A_90B3_558891CD1D3A

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextSoftware : public XE::RendererContext
{
public:
	RendererContextSoftware();

	~RendererContextSoftware();

protected:
	void OnRender( XE::RenderFrame * frame ) override;

private:
	void Init( XE::RenderFrame * frame );

	void Shutdown( XE::RenderFrame * frame );

	void BlitCall( const XE::RenderBlit * item );

	void DrawCall( const XE::RenderDraw * item, const XE::RenderBind * bind );

	void ComputeCall( const XE::RenderCompute * item, const XE::RenderBind * bind );

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

};

XE_INLINE XE::RendererContext * CreateRendererContextSoftware()
{
	return new XE::RendererContextSoftware();
}

END_XE_NAMESPACE

#endif // RENDERERCONTEXTSOFTWARE_H__3145856F_D79A_440A_90B3_558891CD1D3A
