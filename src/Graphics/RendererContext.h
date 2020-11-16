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
	IndexBufferHandle CreateIndexBuffer( const BufferDesc & val );

	TransientIndexBufferHandle CreateTransientIndexBuffer( const BufferDesc & val );

	void Destory( IndexBufferHandle handle );

	VertexLayoutHandle CreateVertexLayout( const VertexLayoutDesc & val );

	void Destory( VertexLayoutHandle handle );

	VertexBufferHandle CreateVertexBuffer( const VertexBufferDesc & val );

	TransientVertexBufferHandle CreateTransientVertexBuffer( const VertexBufferDesc & val );

	void Destory( VertexBufferHandle handle );

	DynamicIndexBufferHandle CreateDynamicIndexBuffer( const BufferDesc & val );

	void Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem );

	void Destory( DynamicIndexBufferHandle handle );

	DynamicVertexBufferHandle CreateDynamicVertexBuffer( const VertexBufferDesc & val );

	void Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem );

	void Destory( DynamicVertexBufferHandle handle );

	IndirectBufferHandle CreateIndirectBuffer( XE::uint64 num );

	void Destory( IndirectBufferHandle handle );

	ShaderHandle CreateShader( const ShaderDesc & val );

	void Destory( ShaderHandle handle );

	XE::Array<UniformHandle> GetShaderUniforms( ShaderHandle handle );

	ProgramHandle CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader );

	ProgramHandle CreateProgram( ShaderHandle cs, bool des_shader );

	void Destory( ProgramHandle handle );

	TextureHandle CreateTexture( const TextureDesc & val );

	void UpdateTexture( const UpdateTextureDesc & val );

	XE::uint32 ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip );

	void Destory( TextureHandle handle );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferDesc & val );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferFromWindowDesc & val );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferFromTextureDesc & val );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferFromAttachmentDesc & val );

	TextureHandle GetTexture( FrameBufferHandle handle, XE::uint8 attachment );

	void Destory( FrameBufferHandle handle );

	UniformHandle CreateUniform( const XE::String & name, UniformType type, XE::uint16 num );

	const Uniform & GetUniformInfo( UniformHandle handle );

	void Destory( UniformHandle handle );

	OcclusionQueryHandle CreateOcclusionQuery();

	std::optional<XE::uint32> GetOcclusionQueryValue( OcclusionQueryHandle handle );

	void Destory( OcclusionQueryHandle handle );

public:
	ViewHandle CreateView();

	void SetViewName( ViewHandle handle, const XE::String & name );

	void SetViewRect( ViewHandle handle, const XE::Rect & rect );

	void SetViewScissor( ViewHandle handle, const XE::Rect & scissor );

	void SetViewClear( const ViewClearDesc & val );

	void SetViewMode( ViewHandle handle, XE::ViewMode mode );

	void SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame );

	void SetViewTransform( ViewHandle handle, const XE::Mat4f & view, const XE::Mat4f & proj );

	void ResetView( ViewHandle handle );

	void Destory( ViewHandle handle );

public:
	void RequestScreenShot( FrameBufferHandle handle, const XE::FileSystem::Path & path );

protected:
	void ResizeTexture( TextureHandle handle, XE::uint32 layers, XE::uint32 mips, XE::uint32 width, XE::uint32 height );

private:
	XE::MemoryView CopyToFrame( XE::MemoryView mem ) const;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5
