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

	void Reset( XE::uint32 width, XE::uint32 height, XE::Flags<XE::ResetFlags> flags = XE::ResetFlags::NONE, XE::TextureFormat format = XE::TextureFormat::COUNT );

public:
	XE::Encoder * Begin();

	void End( XE::Encoder * val );

	void Frame( bool capture = false );

	void Render();

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

	ProgramHandle CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader = false );

	ProgramHandle CreateProgram( ShaderHandle cs, bool des_shader = false );

	void Destory( ProgramHandle handle );

	TextureHandle CreateTexture( const TextureDesc & val );

	void UpdateTexture( const UpdateTextureDesc & val );

	XE::uint32 ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip = 0 );

	void Destory( TextureHandle handle );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferDesc & val );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferFromWindowDesc & val );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferFromTextureDesc & val );

	FrameBufferHandle CreateFrameBuffer( const FrameBufferFromAttachmentDesc & val );

	TextureHandle GetTexture( FrameBufferHandle handle, XE::uint8 attachment = 0 );

	void Destory( FrameBufferHandle handle );

	UniformHandle CreateUniform( const XE::String & name, UniformType type, XE::uint16 num = 1 );

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

	void SetViewMode( ViewHandle handle, XE::ViewMode mode = ViewMode::DEFAULT );

	void SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame );

	void SetViewTransform( ViewHandle handle, const XE::Mat4f & view, const XE::Mat4f & proj );

	void ResetView( ViewHandle handle );
	
	void Destory( ViewHandle handle );

public:
	void RequestScreenShot( FrameBufferHandle handle, const XE::FileSystem::Path & path );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0
