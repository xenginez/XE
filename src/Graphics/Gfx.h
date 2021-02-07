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
	XE::RefHandle < XE::ViewHandle > Create( const XE::ViewDesc & desc );

	XE::RefHandle < XE::ProgramHandle > Create( const XE::ProgramDesc & desc );

	XE::RefHandle < XE::FrameBufferHandle > Create( const XE::FrameBufferDesc & desc );

	XE::RefHandle < XE::VertexLayoutHandle > Create( const XE::VertexLayoutDesc & desc );

	XE::RefHandle < XE::OcclusionQueryHandle > Create( const OcclusionQueryDesc & desc );

	XE::RefHandle < XE::IndirectBufferHandle > Create( const XE::IndirectBufferDesc & desc );

	XE::RefHandle < XE::ShaderHandle > Create( const XE::ShaderDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::TextureHandle > Create( const XE::TextureDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::IndexBufferHandle > Create( const XE::IndexBufferDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::VertexBufferHandle > Create( const XE::VertexBufferDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::DynamicIndexBufferHandle > Create( const XE::DynamicIndexBufferDesc & desc, XE::MemoryView data );

	XE::RefHandle < XE::DynamicVertexBufferHandle > Create( const XE::DynamicVertexBufferDesc & desc, XE::MemoryView data );

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

	void SetViewClear( const XE::ViewClearDesc & desc );

	void SetViewMode( XE::ViewHandle handle, XE::ViewMode mode );

	void SetViewFrameBuffer( XE::ViewHandle handle, XE::FrameBufferHandle frame );

	void SetViewTransform( XE::ViewHandle handle, const XE::Mat4x4f & model, const XE::Mat4x4f & view, const XE::Mat4x4f & proj );

	void ResetView( XE::ViewHandle handle, const XE::ViewDesc & desc );

public:
	void RequestScreenShot( XE::FrameBufferHandle handle, const std::filesystem::path & path );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0
