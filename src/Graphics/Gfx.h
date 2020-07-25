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
	void DebugTextPrint( XE::uint32 x, XE::uint32 y, const XE::Color & color, const std::string & text );

public:
	IndexBufferHandle CreateIndexBuffer( const XE::String & name, XE::memory_view mem, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	TransientIndexBufferHandle CreateTransientIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	void Destory( IndexBufferHandle handle );

	VertexLayoutHandle CreateVertexLayout( const XE::Array<VertexLayout> & layouts );

	void Destory( VertexLayoutHandle handle );

	VertexBufferHandle CreateVertexBuffer( const XE::String & name, XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	TransientVertexBufferHandle CreateTransientVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	void Destory( VertexBufferHandle handle );

	DynamicIndexBufferHandle CreateDynamicIndexBuffer( XE::uint64 size, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	DynamicIndexBufferHandle CreateDynamicIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	void Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::memory_view mem );

	void Destory( DynamicIndexBufferHandle handle );

	DynamicVertexBufferHandle CreateDynamicVertexBuffer( XE::uint64 size, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	DynamicVertexBufferHandle CreateDynamicVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags = XE::BufferFlags::NONE );

	void Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::memory_view mem );

	void Destory( DynamicVertexBufferHandle handle );

	IndirectBufferHandle CreateIndirectBuffer( XE::uint64 num );

	void Destory( IndirectBufferHandle handle );

	ShaderHandle CreateShader( const XE::String & name, ShaderType type, XE::memory_view mem );

	void Destory( ShaderHandle handle );

	XE::Array<UniformHandle> GetShaderUniforms( ShaderHandle handle );

	ProgramHandle CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader = false );

	ProgramHandle CreateProgram( ShaderHandle cs, bool des_shader = false );

	void Destory( ProgramHandle handle );

	TextureHandle CreateTexture2D( const XE::String & name, XE::uint32 width, XE::uint32 height, bool hasmips, XE::uint16 layers, TextureFormat format,
								   XE::Flags< XE::TextureFlags > flags,
								   XE::Flags< XE::SamplerFlags > samplers,
								   std::optional< XE::memory_view > mem = std::nullopt );

	TextureHandle CreateTexture2D( const XE::String & name, XE::BackbufferRatio ratio, bool hasmips, XE::uint16 layers, TextureFormat format,
								   XE::Flags< XE::TextureFlags > flags,
								   XE::Flags< XE::SamplerFlags > samplers );

	TextureHandle CreateTexture3D( const XE::String & name, XE::uint32 width, XE::uint32 height, XE::uint32 depth, bool hasmips, TextureFormat format,
								   XE::Flags< XE::TextureFlags > flags,
								   XE::Flags< XE::SamplerFlags > samplers,
								   std::optional< XE::memory_view > mem = std::nullopt );

	TextureHandle CreateTextureCube( const XE::String & name, XE::uint32 size, bool hasmips, XE::uint16 layers, TextureFormat format,
									 XE::Flags< XE::TextureFlags > flags,
									 XE::Flags< XE::SamplerFlags > samplers,
								   std::optional< XE::memory_view > mem = std::nullopt );

	void UpdateTexture2D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip, 
						  XE::uint32 x, XE::uint32 y,
						  XE::uint32 width, XE::uint32 height,
						  XE::memory_view mem, XE::uint32 pitch = 0 );

	void UpdateTexture3D( TextureHandle handle, XE::uint8 mip,
						  XE::uint32 x, XE::uint32 y, XE::uint32 z,
						  XE::uint32 width, XE::uint32 height, XE::uint32 depth,
						  XE::memory_view mem );

	void UpdateTextureCube( TextureHandle handle, XE::uint16 layer, XE::uint8 side, XE::uint8 mip,
						  XE::uint32 x, XE::uint32 y, XE::uint32 z,
						  XE::uint32 width, XE::uint32 height, XE::uint32 depth,
						  XE::memory_view mem );

	XE::uint32 ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip = 0 );

	XE::uint8 * GetDirectAccess( TextureHandle handle );

	void Destory( TextureHandle handle );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, XE::uint32 width, XE::uint32 height,
										 TextureFormat format,
										 XE::Flags< XE::SamplerFlags > samplers );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, XE::BackbufferRatio ratio,
										 TextureFormat format,
										 XE::Flags< XE::SamplerFlags > samplers );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, const XE::Array< TextureHandle > handles, bool des_texture = false );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, const XE::Array< Attachment > attachments, bool des_texture = false );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, WindowHandle window,
										 XE::uint32 width, XE::uint32 height,
										 TextureFormat color_format = TextureFormat::COUNT,
										 TextureFormat depth_format = TextureFormat::COUNT );

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

	void SetViewClear( ViewHandle handle, 
					   std::optional<XE::Color> color = std::nullopt,
					   std::optional<XE::float32> depth = std::nullopt,
					   std::optional<XE::uint8> stencil = std::nullopt );

	void SetViewMode( ViewHandle handle, XE::ViewMode mode = ViewMode::DEFAULT );

	void SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame );

	void SetViewTransform( ViewHandle handle, const XE::Mat4 & view, const XE::Mat4 & proj );

	void ResetView( ViewHandle handle );
	
	void Destory( ViewHandle handle );

public:
	void RequestScreenShot( FrameBufferHandle handle, const std::filesystem::path & path );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0
