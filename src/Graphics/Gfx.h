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

#include "Encoder.h"

BEG_XE_NAMESPACE

class XE_API Gfx : public XE::Singleton< Gfx >
{
private:
	struct Private;

public:
	Gfx();

	~Gfx();

public:
	XE::Caps GetCaps();

	XE::ContextType GetContextType();

	XE::Array<XE::ContextType> GetSupportedContext();

public:
	void Init( const XE::InitInfo & val );

	void Shutdown();

	void Reset( XE::uint32 width, XE::uint32 height, XE::Flags<XE::ResetFlag> flags = XE::ResetFlag::NONE, XE::TextureFormat format = XE::TextureFormat::COUNT );

public:
	XE::EncoderPtr Begin( bool forthread = false );

	void End( const XE::EncoderPtr & val );

	XE::uint32 Frame( bool capture = false );

public:
	void SetDebug( XE::Flags<XE::DebugFlag> flags = XE::DebugFlag::NONE );

	void DebugTextClear();

	void DebugTextPrint( XE::uint32 x, XE::uint32 y, const XE::Color & color, const std::string & text );

public:
	IndexBufferHandle CreateIndexBuffer( const XE::String & name, XE::memory_view mem, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	TransientIndexBufferHandle CreateTransientIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	void Destory( IndexBufferHandle handle );

	VertexLayoutHandle CreateVertexLayout( const XE::Array<VertexLayout> & layouts );

	void Destory( VertexLayoutHandle handle );

	VertexBufferHandle CreateVertexBuffer( const XE::String & name, XE::memory_view mem, const VertexLayout & layout, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	TransientVertexBufferHandle CreateTransientVertexBuffer( XE::memory_view mem, const VertexLayout & layout, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	void Destory( VertexBufferHandle handle );

	DynamicIndexBufferHandle CreateDynamicIndexBuffer( XE::uint64 size, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	DynamicIndexBufferHandle CreateDynamicIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	void Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::memory_view mem );

	void Destory( DynamicIndexBufferHandle handle );

	DynamicVertexBufferHandle CreateDynamicVertexBuffer( XE::uint64 size, const VertexLayout & layout, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	DynamicVertexBufferHandle CreateDynamicVertexBuffer( XE::memory_view mem, const VertexLayout & layout, XE::Flags< XE::BufferFlag > flags = XE::BufferFlag::NONE );

	void Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::memory_view mem );

	void Destory( DynamicVertexBufferHandle handle );

	IndirectBufferHandle CreateIndirectBuffer( XE::uint64 num );

	void Destory( IndirectBufferHandle handle );

	ShaderHandle CreateShader( const XE::String & name, XE::memory_view mem );

	void Destory( ShaderHandle handle );

	XE::Array<UniformHandle> GetShaderUniforms( ShaderHandle handle );

	ProgramHandle CreateProgram( ShaderHandle vs, ShaderHandle fs, ShaderHandle hs = ShaderHandle::Invalid, ShaderHandle ds = ShaderHandle::Invalid, ShaderHandle gs = ShaderHandle::Invalid, bool des_shader = false );

	ProgramHandle CreateProgram( ShaderHandle cs, bool des_shader = false );

	void Destory( ProgramHandle handle );

	TextureHandle CreateTexture( const XE::String & name, XE::memory_view mem, XE::Flags< XE::TextureFlag > flags,
								 SamplerWrap U, SamplerWrap V, SamplerWrap W,
								 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP,
								 uint8 skip = 0, std::optional< TextureInfo > info = std::nullopt );

	TextureHandle CreateTexture2D( const XE::String & name, XE::uint32 width, XE::uint32 height, bool hasmips, XE::uint16 layers, TextureFormat format,
								   XE::Flags< XE::TextureFlag > flags,
								   SamplerWrap U, SamplerWrap V, SamplerWrap W,
								   SamplerMode MIN, SamplerMode MAG, SamplerMode MIP,
								   std::optional< XE::memory_view > mem = std::nullopt );

	TextureHandle CreateTexture2D( const XE::String & name, XE::BackbufferRatio ratio, bool hasmips, XE::uint16 layers, TextureFormat format,
								   XE::Flags< XE::TextureFlag > flags,
								   SamplerWrap U, SamplerWrap V, SamplerWrap W,
								   SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

	TextureHandle CreateTexture3D( const XE::String & name, XE::uint32 width, XE::uint32 height, XE::uint32 depth, bool hasmips, TextureFormat format,
								   XE::Flags< XE::TextureFlag > flags,
								   SamplerWrap U, SamplerWrap V, SamplerWrap W,
								   SamplerMode MIN, SamplerMode MAG, SamplerMode MIP,
								   std::optional< XE::memory_view > mem = std::nullopt );

	TextureHandle CreateTextureCube( const XE::String & name, XE::uint32 size, bool hasmips, XE::uint16 layers, TextureFormat format,
								   XE::Flags< XE::TextureFlag > flags,
								   SamplerWrap U, SamplerWrap V, SamplerWrap W,
								   SamplerMode MIN, SamplerMode MAG, SamplerMode MIP,
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
										 SamplerWrap U, SamplerWrap V, SamplerWrap W,
										 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, XE::BackbufferRatio ratio,
										 TextureFormat format,
										 SamplerWrap U, SamplerWrap V, SamplerWrap W,
										 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, const XE::Array< TextureHandle > handles, bool des_texture = false );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, const XE::Array< Attachment > attachments, bool des_texture = false );

	FrameBufferHandle CreateFrameBuffer( const XE::String & name, WindowHandle window,
										 XE::uint32 width, XE::uint32 height,
										 TextureFormat color_format = TextureFormat::COUNT,
										 TextureFormat depth_format = TextureFormat::COUNT );

	TextureHandle GetTexture( FrameBufferHandle handle, XE::uint8 attachment = 0 );

	void Destory( FrameBufferHandle handle );

	UniformHandle CreateUniform( const XE::String & name, UniformType type, XE::uint16 num = 1 );

	const UniformInfo & GetUniformInfo( UniformHandle handle );

	void Destory( UniformHandle handle );

	OcclusionQueryHandle CreateOcclusionQuery();

	OcclusionQueryResult GetOcclusionQueryResult( OcclusionQueryHandle handle );

	std::optional<XE::uint32> GetOcclusionQueryValue( OcclusionQueryHandle handle );

	void Destory( OcclusionQueryHandle handle );

public:
	void SetViewName( ViewHandle handle, const XE::String & name );

	void SetViewRect( ViewHandle handle, const XE::Rect & rect );

	void SetViewScissor( ViewHandle handle, const XE::Rect & scissor );

	void SetViewClear( ViewHandle handle, 
					   std::optional<XE::Color> color = std::nullopt,
					   std::optional<XE::float32> depth = std::nullopt,
					   std::optional<XE::uint8> stencil = std::nullopt );

	void SetViewMode( ViewHandle handle, XE::ViewMode mode = ViewMode::Default );

	void SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame );

	void SetViewTransform( ViewHandle handle, const XE::Mat4 & transform );

	void SetViewOrder( ViewHandle handle, const XE::Array<ViewHandle> & remap );

	void ResetView( ViewHandle handle );
	/*
public:
	void SetMarker( const std::string & marker );

	void SetState( XE::Flags<XE::StateFlag> flags = XE::StateFlag::DEFAULT );

	void SetCondition( OcclusionQueryHandle handle, bool visible );

	void SetStencil( XE::Flags<XE::StencilFlag> front, XE::Flags<XE::StencilFlag> back = XE::StencilFlag::NONE );

	void SetScissor( const XE::Rect & scissor );

	void SetTransform( const XE::Mat4 & transform );

	void SetUniform( UniformHandle handle, const XE::Variant & value );

	void SetIndexBuffer( IndexBufferHandle handle );

	void SetIndexBuffer( IndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetIndexBuffer( DynamicIndexBufferHandle handle );

	void SetIndexBuffer( DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetIndexBuffer( TransientIndexBufferHandle handle );

	void SetIndexBuffer( TransientIndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetVertexBuffer( XE::uint8 steam, VertexBufferHandle handle );

	void SetVertexBuffer( XE::uint8 steam, VertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexBuffer( XE::uint8 steam, DynamicVertexBufferHandle handle );

	void SetVertexBuffer( XE::uint8 steam, DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexBuffer( XE::uint8 steam, TransientVertexBufferHandle handle );

	void SetVertexBuffer( XE::uint8 steam, TransientVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexCount( XE::uint32 num );

	void SetInstanceDataBuffer( VertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetInstanceDataBuffer( DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetInstanceDataBuffer( const XE::Array<InstanceDataBuffer> & buffers, XE::uint32 first, XE::uint32 num );

	void SetInstanceCount( XE::uint32 num );

	void SetTexture( XE::uint8 stage, UniformHandle sampler, TextureHandle handle,
					 SamplerWrap U, SamplerWrap V, SamplerWrap W,
					 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

public:
	void Touch( ViewHandle handle );

	void Submit( ViewHandle handle, ProgramHandle program, XE::uint32 depth = 0, bool preserve_state = false );

	void Submit( ViewHandle handle, ProgramHandle program, OcclusionQueryHandle query, XE::uint32 depth = 0, bool preserve_state = false );

	void Submit( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 depth = 0, bool preserve_state = false );

	void SetBuffer( XE::uint8 stage, IndexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, DynamicIndexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, VertexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, DynamicVertexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, IndirectBufferHandle handle, Access access );

	void SetImage( XE::uint8 stage, IndirectBufferHandle handle, XE::uint8 mip, Access access, TextureFormat format = TextureFormat::COUNT );

	void Dispatch( ViewHandle handle, ProgramHandle program, XE::uint32 numX = 1, XE::uint32 numY = 1, XE::uint32 numZ = 1 );

	void Dispatch( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num );

	void Discard();

	void Blit( ViewHandle handle,
			   TextureHandle dst, XE::uint32 dst_x, XE::uint32 dst_y,
			   TextureHandle src, XE::uint32 src_x, XE::uint32 src_y,
			   XE::uint32 width, XE::uint32 height );

	void Blit( ViewHandle handle,
			   TextureHandle dst, XE::uint8 dst_mip, XE::uint32 dst_x, XE::uint32 dst_y, XE::uint32 dst_z,
			   TextureHandle src, XE::uint8 src_mip, XE::uint32 src_x, XE::uint32 src_y, XE::uint32 src_z,
			   XE::uint32 width, XE::uint32 height, XE::uint32 depth );
*/
public:
	void RequestScreenShot( FrameBufferHandle handle, const std::filesystem::path & path );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // GFX_H__03DAE83A_A925_4FCA_8E63_633C5869DEB0
