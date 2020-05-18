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

#include "Type.h"

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
	virtual void OnStartup() = 0;

	virtual void OnRender( XE::Frame* val ) = 0;

	virtual void OnClearup() = 0;

public:
	void Reset( XE::uint32 width, XE::uint32 height, XE::Flags<XE::ResetFlag> flags, XE::TextureFormat format );

public:
	XE::Encoder * Begin();

	void End( XE::Encoder * val );

public:
	const XE::CapsInfo & GetCaps() const;

	const XE::InitInfo & GetInit() const;

public:
	IndexBufferHandle CreateIndexBuffer( const XE::String & name, XE::memory_view mem, XE::Flags< XE::BufferFlag > flags );

	TransientIndexBufferHandle CreateTransientIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags );

	void Destory( IndexBufferHandle handle );

	VertexLayoutHandle CreateVertexLayout( const XE::Array<VertexLayout> & layouts );

	void Destory( VertexLayoutHandle handle );

	VertexBufferHandle CreateVertexBuffer( const XE::String & name, XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags );

	TransientVertexBufferHandle CreateTransientVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags );

	void Destory( VertexBufferHandle handle );

	DynamicIndexBufferHandle CreateDynamicIndexBuffer( XE::uint64 size, XE::Flags< XE::BufferFlag > flags);

	DynamicIndexBufferHandle CreateDynamicIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags );

	void Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::memory_view mem );

	void Destory( DynamicIndexBufferHandle handle );

	DynamicVertexBufferHandle CreateDynamicVertexBuffer( XE::uint64 size, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags );

	DynamicVertexBufferHandle CreateDynamicVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags );

	void Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::memory_view mem );

	void Destory( DynamicVertexBufferHandle handle );

	IndirectBufferHandle CreateIndirectBuffer( XE::uint64 num );

	void Destory( IndirectBufferHandle handle );

	ShaderHandle CreateShader( const XE::String & name, XE::memory_view mem );

	void Destory( ShaderHandle handle );

	XE::Array<UniformHandle> GetShaderUniforms( ShaderHandle handle );

	ProgramHandle CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader );

	ProgramHandle CreateProgram( ShaderHandle cs, bool des_shader);

	void Destory( ProgramHandle handle );

	TextureHandle CreateTexture2D( const XE::String & name, XE::uint32 width, XE::uint32 height, bool hasmips, XE::uint16 layers, TextureFormat format,
								   XE::Flags< XE::TextureFlag > flags,
								   SamplerWrap U, SamplerWrap V, SamplerWrap W,
								   SamplerMode MIN, SamplerMode MAG, SamplerMode MIP,
								   std::optional< XE::memory_view > mem  );

	TextureHandle CreateTexture2D( const XE::String & name, XE::BackbufferRatio ratio, bool hasmips, XE::uint16 layers, TextureFormat format,
								   XE::Flags< XE::TextureFlag > flags,
								   SamplerWrap U, SamplerWrap V, SamplerWrap W,
								   SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

	TextureHandle CreateTexture3D( const XE::String & name, XE::uint32 width, XE::uint32 height, XE::uint32 depth, bool hasmips, TextureFormat format,
								   XE::Flags< XE::TextureFlag > flags,
								   SamplerWrap U, SamplerWrap V, SamplerWrap W,
								   SamplerMode MIN, SamplerMode MAG, SamplerMode MIP,
								   std::optional< XE::memory_view > mem  );

	TextureHandle CreateTextureCube( const XE::String & name, XE::uint32 size, bool hasmips, XE::uint16 layers, TextureFormat format,
									 XE::Flags< XE::TextureFlag > flags,
									 SamplerWrap U, SamplerWrap V, SamplerWrap W,
									 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP,
									 std::optional< XE::memory_view > mem  );

	void UpdateTexture2D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip,
						  XE::uint32 x, XE::uint32 y,
						  XE::uint32 width, XE::uint32 height,
						  XE::memory_view mem, XE::uint32 pitch  );

	void UpdateTexture3D( TextureHandle handle, XE::uint8 mip,
						  XE::uint32 x, XE::uint32 y, XE::uint32 z,
						  XE::uint32 width, XE::uint32 height, XE::uint32 depth,
						  XE::memory_view mem );

	void UpdateTextureCube( TextureHandle handle, XE::uint16 layer, XE::uint8 side, XE::uint8 mip,
							XE::uint32 x, XE::uint32 y, XE::uint32 z,
							XE::uint32 width, XE::uint32 height, XE::uint32 depth,
							XE::memory_view mem );

	XE::uint32 ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip  );

	XE::uint8 * GetDirectAccess( TextureHandle handle );

	void Destory( TextureHandle handle );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, XE::uint32 width, XE::uint32 height,
										 TextureFormat format,
										 SamplerWrap U, SamplerWrap V, SamplerWrap W,
										 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, XE::BackbufferRatio ratio,
										 TextureFormat format,
										 SamplerWrap U, SamplerWrap V, SamplerWrap W,
										 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, const XE::Array< TextureHandle > handles, bool des_texture );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, const XE::Array< Attachment > attachments, bool des_texture  );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, WindowHandle window,
										 XE::uint32 width, XE::uint32 height,
										 TextureFormat color_format,
										 TextureFormat depth_format );

	TextureHandle GetTexture( FrameBufferHandle handle, XE::uint8 attachment );

	void Destory( FrameBufferHandle handle );

	UniformHandle CreateUniform( const XE::String & name, UniformType type, XE::uint16 num  );

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

	void SetViewClear( ViewHandle handle,
					   std::optional<XE::Color> color,
					   std::optional<XE::float32> depth,
					   std::optional<XE::uint8> stencil );

	void SetViewMode( ViewHandle handle, XE::ViewMode mode );

	void SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame );

	void SetViewTransform( ViewHandle handle, const XE::Mat4 & view, const XE::Mat4 & proj );

	void ResetView( ViewHandle handle );

	void Destory( ViewHandle handle );

public:
	void DebugTextPrint( XE::uint32 x, XE::uint32 y, const XE::Color & color, const std::string & text );

public:
	void RequestScreenShot( FrameBufferHandle handle, const std::filesystem::path & path );

protected:
	void ResizeTexture( TextureHandle handle, XE::uint32 layers, XE::uint32 mips, XE::uint32 width, XE::uint32 height );

private:
	XE::memory_view CopyToFrame( XE::memory_view mem ) const;

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // RENDERERCONTEXT_H__759BB776_4331_4BA8_AAB0_8AA62934A3A5
