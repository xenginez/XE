/*!
 * \file	RendererContext.h
 *
 * \author	ZhengYuanQing
 * \date	2020/04/05
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5
#define RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5

#include <optional>

#include "Type.h"
#include "Private.h"

BEG_XE_NAMESPACE

class RendererContext
{
private:
	struct Private;

public:
	RendererContext();

	virtual ~RendererContext();

public:
	void Init( const InitInfo & val );

	void Frame( bool capture );

	void Render();

	void Shutdown();

protected:
	virtual void OnRender( XE::Frame * val ) = 0;

public:
	XE::Encoder * Begin();

	void End( XE::Encoder * val );

public:
	XE::CapsInfo & GetCaps();

	XE::InitInfo & GetInit();

public:
	XE::OcclusionQueryHandle CreateOcclusionQuery();

	XE::ShaderHandle CreateShader( const XE::ShaderDesc & val );

	XE::ProgramHandle CreateProgram( XE::ShaderHandle cs, bool des_shader );

	XE::ProgramHandle CreateProgram( XE::ShaderHandle vs, XE::ShaderHandle fs, bool des_shader );

	XE::UniformHandle CreateUniform( const XE::String & name, XE::UniformType type, XE::uint16 num );

	XE::IndirectBufferHandle CreateIndirectBuffer( XE::uint64 num );

	XE::VertexLayoutHandle CreateVertexLayout( const XE::VertexLayoutDesc & val );

	XE::TextureHandle CreateTexture( const XE::TextureDesc & desc, XE::MemoryView data );

	XE::IndexBufferHandle CreateIndexBuffer( const XE::BufferDesc & desc, XE::MemoryView data );

	XE::VertexBufferHandle CreateVertexBuffer( const XE::VertexBufferDesc & desc, XE::MemoryView data );

	XE::DynamicIndexBufferHandle CreateDynamicIndexBuffer( const XE::BufferDesc & desc, XE::MemoryView data );

	XE::DynamicVertexBufferHandle CreateDynamicVertexBuffer( const XE::VertexBufferDesc & desc, XE::MemoryView data );

	XE::TransientIndexBufferHandle CreateTransientIndexBuffer( const XE::BufferDesc & desc, XE::MemoryView data );

	XE::TransientVertexBufferHandle CreateTransientVertexBuffer( const XE::VertexBufferDesc & desc, XE::MemoryView data );

	XE::FrameBufferHandle CreateFrameBuffer( const XE::FrameBufferDesc & val );

	XE::FrameBufferHandle CreateFrameBuffer( const XE::FrameBufferFromWindowDesc & val );

	XE::FrameBufferHandle CreateFrameBuffer( const XE::FrameBufferFromTextureDesc & val );

	XE::FrameBufferHandle CreateFrameBuffer( const XE::FrameBufferFromAttachmentDesc & val );

public:
	void Update( const XE::UpdateTextureDesc & desc, XE::MemoryView data );

	void Update( XE::DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView data );

	void Update( XE::DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView data );

public:
	void ReadTexture( XE::TextureHandle handle, XE::uint8 * data, XE::uint8 mip );

	XE::TextureHandle GetTexture( XE::FrameBufferHandle handle, XE::uint8 attachment );

	const XE::Uniform & GetUniformInfo( XE::UniformHandle handle );

	XE::Array<UniformHandle> GetShaderUniforms( XE::ShaderHandle handle );

	std::optional<XE::uint32> GetOcclusionQueryValue( XE::OcclusionQueryHandle handle );

public:
	void Destory( XE::ShaderHandle handle );

	void Destory( XE::ProgramHandle handle );

	void Destory( XE::TextureHandle handle );

	void Destory( XE::UniformHandle handle );

	void Destory( XE::FrameBufferHandle handle );

	void Destory( XE::IndexBufferHandle handle );

	void Destory( XE::VertexLayoutHandle handle );

	void Destory( XE::VertexBufferHandle handle );

	void Destory( XE::IndirectBufferHandle handle );

	void Destory( XE::OcclusionQueryHandle handle );

	void Destory( XE::DynamicIndexBufferHandle handle );

	void Destory( XE::DynamicVertexBufferHandle handle );

	void Destory( XE::TransientIndexBufferHandle handle );

	void Destory( XE::TransientVertexBufferHandle handle );

public:
	XE::ViewHandle CreateView( const XE::ViewDesc & val );

	void SetViewName( XE::ViewHandle handle, const XE::String & name );

	void SetViewRect( XE::ViewHandle handle, const XE::Rectf & rect );

	void SetViewScissor( XE::ViewHandle handle, const XE::Rectf & scissor );

	void SetViewClear( const XE::ViewClearDesc & val );

	void SetViewMode( XE::ViewHandle handle, XE::ViewMode mode );

	void SetViewFrameBuffer( XE::ViewHandle handle, XE::FrameBufferHandle frame );

	void SetViewTransform( XE::ViewHandle handle, const XE::Mat4f & model, const XE::Mat4f & view, const XE::Mat4f & proj );

	void ResetView( XE::ViewHandle handle, const XE::ViewDesc & val );

	void Destory( XE::ViewHandle handle );

public:
	void RequestScreenShot( XE::FrameBufferHandle handle, const XE::FileSystem::Path & path );

private:
	XE::MemoryView CopyToFrame( XE::MemoryView mem ) const;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5
