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

	XE::Array<XE::RendererContextType> GetSupportedContext();

public:
	void Init( const XE::InitInfo & val );

	void Shutdown();

public:
	XE::Encoder * Begin();

	void End( XE::Encoder * val );

	void Frame( bool capture = false );

	void Render();

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
	Private * _p;
};

END_XE_NAMESPACE

#endif // GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0
