/*!
 * \file	Gfx.h
 *
 * \author	ZhengYuanQing
 * \date	2020/04/04
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0
#define GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0

#include <optional>

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Gfx : public XE::Singleton< Gfx >
{
	SINGLETON( Gfx )

private:
	struct Private;

private:
	Gfx();

	~Gfx();

public:
	const XE::CapsInfo & GetCaps();

	XE::List<XE::RendererContextType> GetSupportedContext();

public:
	void Init( const XE::InitDesc & val );

	void Shutdown();

public:
	XE::Encoder * Begin();

	void End( XE::Encoder * val );

	void Present();

public:
	XE::RefHandle < XE::ViewHandle > CreateView( const XE::ViewDesc & desc );

	XE::RefHandle < XE::ProgramHandle > CreateProgram( const XE::ProgramDesc & desc );

	XE::RefHandle < XE::FrameBufferHandle > CreateFrameBuffer( const XE::FrameBufferDesc & desc );

	XE::RefHandle < XE::VertexLayoutHandle > CreateVertexLayout( const XE::VertexLayoutDesc & desc );

	XE::RefHandle < XE::OcclusionQueryHandle > CreateOcclusionQuery( const OcclusionQueryDesc & desc );

	XE::RefHandle < XE::ShaderHandle > CreateShader( const XE::ShaderDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::TextureHandle > CreateTexture( const XE::TextureDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::IndexBufferHandle > CreateIndexBuffer( const XE::IndexBufferDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::VertexBufferHandle > CreateVertexBuffer( const XE::VertexBufferDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::DynamicIndexBufferHandle > CreateDynamicIndexBuffer( const XE::IndexBufferDesc & desc );

	XE::RefHandle < XE::DynamicVertexBufferHandle > CreateDynamicVertexBuffer( const XE::VertexBufferDesc & desc );

public:
	const XE::ViewDesc & GetDesc( XE::ViewHandle handle );

	const XE::ShaderDesc & GetDesc( XE::ShaderHandle handle );

	const XE::ProgramDesc & GetDesc( XE::ProgramHandle handle );

	const XE::TextureDesc & GetDesc( XE::TextureHandle handle );

	const XE::FrameBufferDesc & GetDesc( XE::FrameBufferHandle handle );

	const XE::IndexBufferDesc & GetDesc( XE::IndexBufferHandle handle );

	const XE::VertexLayoutDesc & GetDesc( XE::VertexLayoutHandle handle );

	const XE::VertexBufferDesc & GetDesc( XE::VertexBufferHandle handle );

	const XE::OcclusionQueryDesc & GetDesc( XE::OcclusionQueryHandle handle );

	const XE::IndexBufferDesc & GetDesc( XE::DynamicIndexBufferHandle handle );

	const XE::VertexBufferDesc & GetDesc( XE::DynamicVertexBufferHandle handle );

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

	void ResetView( XE::ViewHandle handle, const XE::ViewDesc & desc );

public:
	void RequestScreenShot( XE::FrameBufferHandle handle, const std::string & userdata, ScreenShotCallbackType callback );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0
