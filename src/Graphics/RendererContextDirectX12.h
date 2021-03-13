/*!
 * \file	RendererContextDirectX12.h
 *
 * \author	ZhengYuanQing
 * \date	2020/04/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTDIRECTX12_H__F749BA89_7295_4D11_8DD4_664658D8DE3B
#define RENDERERCONTEXTDIRECTX12_H__F749BA89_7295_4D11_8DD4_664658D8DE3B

#include "RendererContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & ( OS_WINDOWS | OS_XBOX )

class RendererContextDirectX12 : public XE::RendererContext
{
public:
	RendererContextDirectX12();

	~RendererContextDirectX12() override;

protected:
	void OnRender( XE::RenderFrame* val ) override;

private:
	void ExecCommands( XE::Buffer & buffer );

private:
	void Init();

	void Shutdown();

private:
	void CreateShader( XE::ShaderHandle handle, XE::MemoryView data );

	void CreateProgram( XE::ProgramHandle handle );

	void CreateTexture(XE::TextureHandle handle, XE::MemoryView data );

	void CreateFrameBuffer( XE::FrameBufferHandle handle );

	void CreateIndexBuffer( XE::IndexBufferHandle handle, XE::MemoryView data );

	void CreateVertexLayout( XE::VertexLayoutHandle handle );

	void CreateVertexBuffer( XE::VertexBufferHandle handle, XE::MemoryView data );

	void CreateIndirectBuffer( XE::IndirectBufferHandle handle );

	void CreateOcclusionQuery( XE::OcclusionQueryHandle handle );

	void CreateDynamicIndexBuffer( XE::DynamicIndexBufferHandle handle );

	void CreateDynamicVertexBuffer( XE::DynamicVertexBufferHandle handle );

private:
	void ReadTexture( XE::TextureHandle handle, XE::uint8 * data, XE::uint8 mip );

	void UpdateTexture( const XE::UpdateTextureDesc & desc, XE::MemoryView data );

	void UpdateDynamicIndexBuffer( XE::DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem );

	void UpdateDynamicVertexBuffer( XE::DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem );

private:
	void DestroyShader( XE::ShaderHandle handle );

	void DestroyTexture( XE::TextureHandle handle );

	void DestroyProgram( XE::ProgramHandle handle );

	void DestroyFrameBuffer( XE::FrameBufferHandle handle );

	void DestroyIndexBuffer( XE::IndexBufferHandle handle );

	void DestroyVertexLayout( XE::VertexLayoutHandle handle );

	void DestroyVertexBuffer( XE::VertexBufferHandle handle );

	void DestroyIndirectBuffer( XE::IndirectBufferHandle handle );

	void DestroyOcclusionQuery( XE::OcclusionQueryHandle handle );

	void DestroyDynamicIndexBuffer( XE::DynamicIndexBufferHandle handle );

	void DestroyDynamicVertexBuffer( XE::DynamicVertexBufferHandle handle );

private:
	void RequestScreenShot( XE::FrameBufferHandle handle, const std::string & userdata, ScreenShotCallbackType callback );
};

XE_INLINE XE::RendererContext * CreateRendererContextDirectX12()
{
	return new XE::RendererContextDirectX12();
}

#else

XE_INLINE XE::RendererContext * CreateRendererContextDirectX12()
{
	return nullptr;
}

#endif

END_XE_NAMESPACE

#endif // RENDERERCONTEXTDIRECTX12_H__F749BA89_7295_4D11_8DD4_664658D8DE3B
