#include "RendererContext.h"

#include "Structs.h"
#include "Encoder.h"

struct XE::RendererContext::Private
{
	std::mutex _FrameMutex;
	XE::Frame * _SubmitFrame;
	XE::Frame * _RenderFrame;
	std::array<XE::Frame, 2> _Frames;

	XE::CapsInfo _Caps;
	XE::InitInfo _Init;

	std::array<View, GFX_MAX_VIEW> Views = {};

	XE::ConcurrentHandleAlloctor<XE::View, GFX_MAX_VIEW> _ViewHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::ShaderHandle, GFX_MAX_SHADERS> _ShaderHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::ProgramHandle, GFX_MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::TextureHandle, GFX_MAX_TEXTURES> _TextureHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::UniformHandle, GFX_MAX_UNIFORMS> _UniformHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::FrameBufferHandle, GFX_MAX_FRAME_BUFFERS> _FrameBufferHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::IndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  _IndexBufferHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::VertexLayoutHandle, GFX_MAX_VERTEX_LAYOUTS> _VertexLayoutHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::VertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> _VertexBufferHandleAlloc;
};

XE::RendererContext::RendererContext()
	:_p( new Private )
{

}

XE::RendererContext::~RendererContext()
{
	delete _p;
}

void XE::RendererContext::Init( const InitInfo & val )
{
	_p->_Init = val;

	_p->_Caps.TransientIbSize = val.transientIbSize;
	_p->_Caps.TransientVbSize = val.transientVbSize;
	_p->_Caps.VendorId = val.vendorId;
	_p->_Caps.DeviceId = val.deviceId;

	_p->_SubmitFrame = &_p->_Frames[0];
	_p->_RenderFrame = &_p->_Frames[1];
}

void XE::RendererContext::Shutdown()
{

}

void XE::RendererContext::Reset( XE::uint32 width, XE::uint32 height, XE::Flags<XE::ResetFlag> flags, XE::TextureFormat format )
{

}

XE::Encoder * XE::RendererContext::Begin()
{
	thread_local Encoder encoder;

	encoder.Discard();

	encoder.SetFrame( _p->_SubmitFrame );

	return &encoder;
}

void XE::RendererContext::End( XE::Encoder * val )
{
	val->Discard();

	val->SetFrame( nullptr );
}

void XE::RendererContext::Frame( bool capture )
{
	{
		std::unique_lock<std::mutex> lock( _p->_FrameMutex );

		std::swap( _p->_SubmitFrame, _p->_RenderFrame );
	}

	_p->_SubmitFrame->Reset();
}

void XE::RendererContext::Render()
{
	std::unique_lock<std::mutex> lock( _p->_FrameMutex );
	// TODO: render anytings
}

const XE::CapsInfo & XE::RendererContext::GetCaps() const
{
	return _p->_Caps;
}

const XE::InitInfo & XE::RendererContext::GetInitInfo() const
{
	return _p->_Init;
}

XE::IndexBufferHandle XE::RendererContext::CreateIndexBuffer( const XE::String & name, XE::memory_view mem, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

XE::TransientIndexBufferHandle XE::RendererContext::CreateTransientIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

void XE::RendererContext::Destory( IndexBufferHandle handle )
{

}

void XE::RendererContext::Destory( VertexLayoutHandle handle )
{

}

void XE::RendererContext::Destory( VertexBufferHandle handle )
{

}

void XE::RendererContext::Destory( DynamicIndexBufferHandle handle )
{

}

void XE::RendererContext::Destory( DynamicVertexBufferHandle handle )
{

}

void XE::RendererContext::Destory( IndirectBufferHandle handle )
{

}

void XE::RendererContext::Destory( ShaderHandle handle )
{

}

void XE::RendererContext::Destory( ProgramHandle handle )
{

}

void XE::RendererContext::Destory( TextureHandle handle )
{

}

void XE::RendererContext::Destory( FrameBufferHandle handle )
{

}

void XE::RendererContext::Destory( UniformHandle handle )
{

}

void XE::RendererContext::Destory( OcclusionQueryHandle handle )
{

}

void XE::RendererContext::Destory( ViewHandle handle )
{

}

XE::VertexLayoutHandle XE::RendererContext::CreateVertexLayout( const XE::Array<VertexLayout> & layouts )
{
	return {};
}

XE::VertexBufferHandle XE::RendererContext::CreateVertexBuffer( const XE::String & name, XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

XE::TransientVertexBufferHandle XE::RendererContext::CreateTransientVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( XE::uint64 size, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

void XE::RendererContext::Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::memory_view mem )
{

}

void XE::RendererContext::Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::memory_view mem )
{

}

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( XE::uint64 size, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	return {};
}

XE::IndirectBufferHandle XE::RendererContext::CreateIndirectBuffer( XE::uint64 num )
{
	return {};
}

XE::ShaderHandle XE::RendererContext::CreateShader( const XE::String & name, XE::memory_view mem )
{
	return {};
}

XE::Array<XE::UniformHandle> XE::RendererContext::GetShaderUniforms( ShaderHandle handle )
{
	return {};
}

XE::ProgramHandle XE::RendererContext::CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader )
{
	return {};
}

XE::ProgramHandle XE::RendererContext::CreateProgram( ShaderHandle cs, bool des_shader )
{
	return {};
}

XE::TextureHandle XE::RendererContext::CreateTexture2D( const XE::String & name, XE::uint32 width, XE::uint32 height, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem )
{
	return {};
}

XE::TextureHandle XE::RendererContext::CreateTexture2D( const XE::String & name, XE::BackbufferRatio ratio, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	return {};
}

XE::TextureHandle XE::RendererContext::CreateTexture3D( const XE::String & name, XE::uint32 width, XE::uint32 height, XE::uint32 depth, bool hasmips, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem )
{
	return {};
}

XE::TextureHandle XE::RendererContext::CreateTextureCube( const XE::String & name, XE::uint32 size, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem )
{
	return {};
}

void XE::RendererContext::UpdateTexture2D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 width, XE::uint32 height, XE::memory_view mem, XE::uint32 pitch )
{

}

void XE::RendererContext::UpdateTexture3D( TextureHandle handle, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::memory_view mem )
{

}

void XE::RendererContext::UpdateTextureCube( TextureHandle handle, XE::uint16 layer, XE::uint8 side, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::memory_view mem )
{

}

XE::uint32 XE::RendererContext::ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip )
{
	return {};
}

XE::uint8 * XE::RendererContext::GetDirectAccess( TextureHandle handle )
{
	return {};
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, XE::uint32 width, XE::uint32 height, TextureFormat format, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	return {};
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, XE::BackbufferRatio ratio, TextureFormat format, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	return {};
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, const XE::Array< TextureHandle > handles, bool des_texture )
{
	return {};
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, const XE::Array< Attachment > attachments, bool des_texture )
{
	return {};
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, WindowHandle window, XE::uint32 width, XE::uint32 height, TextureFormat color_format, TextureFormat depth_format )
{
	return {};
}

XE::TextureHandle XE::RendererContext::GetTexture( FrameBufferHandle handle, XE::uint8 attachment )
{
	return {};
}

XE::UniformHandle XE::RendererContext::CreateUniform( const XE::String & name, UniformType type, XE::uint16 num )
{
	return {};
}

const XE::UniformInfo & XE::RendererContext::GetUniformInfo( UniformHandle handle )
{
	return {};
}

XE::OcclusionQueryHandle XE::RendererContext::CreateOcclusionQuery()
{
	return {};
}

XE::OcclusionQueryResult XE::RendererContext::GetOcclusionQueryResult( OcclusionQueryHandle handle )
{
	return {};
}

std::optional<XE::uint32> XE::RendererContext::GetOcclusionQueryValue( OcclusionQueryHandle handle )
{
	return {};
}

XE::ViewHandle XE::RendererContext::CreateView()
{
	return {};
}

void XE::RendererContext::SetViewName( ViewHandle handle, const XE::String & name )
{

}

void XE::RendererContext::SetViewRect( ViewHandle handle, const XE::Rect & rect )
{

}

void XE::RendererContext::SetViewScissor( ViewHandle handle, const XE::Rect & scissor )
{

}

void XE::RendererContext::SetViewClear( ViewHandle handle, std::optional<XE::Color> color, std::optional<XE::float32> depth, std::optional<XE::uint8> stencil )
{

}

void XE::RendererContext::SetViewMode( ViewHandle handle, XE::ViewMode mode )
{

}

void XE::RendererContext::SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame )
{

}

void XE::RendererContext::SetViewTransform( ViewHandle handle, const XE::Mat4 & transform )
{

}

void XE::RendererContext::SetViewOrder( ViewHandle handle, const XE::Array<ViewHandle> & remap )
{

}

void XE::RendererContext::ResetView( ViewHandle handle )
{

}

void XE::RendererContext::DebugTextPrint( XE::uint32 x, XE::uint32 y, const XE::Color & color, const std::string & text )
{

}

void XE::RendererContext::RequestScreenShot( FrameBufferHandle handle, const std::filesystem::path & path )
{

}
