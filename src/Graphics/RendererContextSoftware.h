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
	void OnRender( XE::RenderFrame * val ) override;

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
	void Destory( XE::ShaderHandle handle );

	void Destory( XE::ProgramHandle handle );

	void Destory( XE::TextureHandle handle );

	void Destory( XE::FrameBufferHandle handle );

	void Destory( XE::IndexBufferHandle handle );

	void Destory( XE::VertexLayoutHandle handle );

	void Destory( XE::VertexBufferHandle handle );

	void Destory( XE::IndirectBufferHandle handle );

	void Destory( XE::OcclusionQueryHandle handle );

	void Destory( XE::DynamicIndexBufferHandle handle );

	void Destory( XE::DynamicVertexBufferHandle handle );

};

XE_INLINE XE::RendererContext * CreateRendererContextSoftware()
{
	return new XE::RendererContextSoftware();
}

END_XE_NAMESPACE

#endif // RENDERERCONTEXTSOFTWARE_H__3145856F_D79A_440A_90B3_558891CD1D3A
