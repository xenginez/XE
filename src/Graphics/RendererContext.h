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
	void Init( const XE::InitDesc & val );

	void Present();

	void Shutdown();

private:
	void Render();

protected:
	virtual void OnRender( XE::RenderFrame * val ) = 0;

public:
	XE::Encoder * Begin();

	void End( XE::Encoder * val );

public:
	const XE::CapsInfo & GetCaps() const;

	const XE::InitDesc & GetInit() const;

public:
	void Inc( XE::ViewHandle handle );

	void Inc( XE::ShaderHandle handle );

	void Inc( XE::ProgramHandle handle );

	void Inc( XE::TextureHandle handle );

	void Inc( XE::FrameBufferHandle handle );

	void Inc( XE::IndexBufferHandle handle );

	void Inc( XE::VertexLayoutHandle handle );

	void Inc( XE::VertexBufferHandle handle );

	void Inc( XE::OcclusionQueryHandle handle );

	void Inc( XE::IndirectBufferHandle handle );

	void Inc( XE::DynamicIndexBufferHandle handle );

	void Inc( XE::DynamicVertexBufferHandle handle );

	void Dec( XE::ViewHandle handle );

	void Dec( XE::ShaderHandle handle );

	void Dec( XE::ProgramHandle handle );

	void Dec( XE::TextureHandle handle );

	void Dec( XE::FrameBufferHandle handle );

	void Dec( XE::IndexBufferHandle handle );

	void Dec( XE::VertexLayoutHandle handle );

	void Dec( XE::VertexBufferHandle handle );

	void Dec( XE::OcclusionQueryHandle handle );

	void Dec( XE::IndirectBufferHandle handle );

	void Dec( XE::DynamicIndexBufferHandle handle );

	void Dec( XE::DynamicVertexBufferHandle handle );

public:
	XE::ViewHandle Create( const XE::ViewDesc & desc );

	XE::ProgramHandle Create( const XE::ProgramDesc & desc );

	XE::FrameBufferHandle Create( const XE::FrameBufferDesc & desc );

	XE::VertexLayoutHandle Create( const XE::VertexLayoutDesc & desc );

	XE::OcclusionQueryHandle Create( const OcclusionQueryDesc & desc );

	XE::IndirectBufferHandle Create( const XE::IndirectBufferDesc & desc );

	XE::ShaderHandle Create( const XE::ShaderDesc & desc, XE::MemoryView data );

	XE::TextureHandle Create( const XE::TextureDesc & desc, XE::MemoryView data );

	XE::IndexBufferHandle Create( const XE::IndexBufferDesc & desc, XE::MemoryView data );

	XE::VertexBufferHandle Create( const XE::VertexBufferDesc & desc, XE::MemoryView data );

	XE::DynamicIndexBufferHandle Create( const XE::DynamicIndexBufferDesc & desc );

	XE::DynamicVertexBufferHandle Create( const XE::DynamicVertexBufferDesc & desc );

public:
	const XE::ViewDesc & GetDesc( XE::ViewHandle handle );

	const XE::ShaderDesc & GetDesc( XE::ShaderHandle handle );

	const XE::ProgramDesc & GetDesc( XE::ProgramHandle handle );

	const XE::TextureDesc & GetDesc( XE::TextureHandle handle );

	const XE::FrameBufferDesc & GetDesc( XE::FrameBufferHandle handle );

	const XE::IndexBufferDesc & GetDesc( XE::IndexBufferHandle handle );

	const XE::VertexLayoutDesc & GetDesc( XE::VertexLayoutHandle handle );

	const XE::VertexBufferDesc & GetDesc( XE::VertexBufferHandle handle );

	const XE::IndirectBufferDesc & GetDesc( XE::IndirectBufferHandle handle );

	const XE::OcclusionQueryDesc & GetDesc( XE::OcclusionQueryHandle handle );

	const XE::DynamicIndexBufferDesc & GetDesc( XE::DynamicIndexBufferHandle handle );

	const XE::DynamicVertexBufferDesc & GetDesc( XE::DynamicVertexBufferHandle handle );

public:
	void Destory( XE::ViewHandle handle );

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

public:
	void Update( const XE::UpdateTextureDesc & desc, XE::MemoryView data );

	void Update( XE::DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView data );

	void Update( XE::DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView data );

public:
	XE::Array<XE::UniformDesc> GetShaderUniforms( XE::ShaderHandle handle );

	void ReadTexture( XE::TextureHandle handle, XE::uint8 * data, XE::uint8 mip );

	XE::TextureHandle GetTexture( XE::FrameBufferHandle handle, XE::uint8 attachment );

	std::optional<XE::uint32> GetOcclusionQueryValue( XE::OcclusionQueryHandle handle );

public:
	void SetViewName( XE::ViewHandle handle, const XE::String & name );

	void SetViewRect( XE::ViewHandle handle, const XE::Rectf & rect );

	void SetViewScissor( XE::ViewHandle handle, const XE::Rectf & scissor );

	void SetViewClear( const XE::ClearDesc & desc );

	void SetViewMode( XE::ViewHandle handle, XE::ViewMode mode );

	void SetViewFrameBuffer( XE::ViewHandle handle, XE::FrameBufferHandle frame );

	void SetViewTransform( XE::ViewHandle handle, const XE::Mat4x4f & model, const XE::Mat4x4f & view, const XE::Mat4x4f & proj );

	void ResetView( XE::ViewHandle handle, const XE::ViewDesc & val );

public:
	void SetOcclusionQueryValue( XE::OcclusionQueryHandle handle, XE::uint32 value );

	void RequestScreenShot( XE::FrameBufferHandle handle, const std::string & userdata, ScreenShotCallbackType callback );

protected:
	XE::CapsInfo & Caps();

private:
	XE::MemoryView CopyToFrame( XE::MemoryView mem ) const;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5
