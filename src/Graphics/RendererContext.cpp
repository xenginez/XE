#include "RendererContext.h"

#include <optional>

#include "Encoder.h"

struct XE::RendererContext::Private
{
	std::mutex _FrameMutex;
	XE::Frame * _SubmitFrame;
	XE::Frame * _RenderFrame;
	std::array<XE::Frame, 2> _Frames;

	XE::CapsInfo _Caps;
	XE::InitInfo _Init;

	std::array<View, GFX_MAX_VIEW> _Views;
	std::array<Shader, GFX_MAX_SHADERS> _Shaders;
	std::array<Texture, GFX_MAX_TEXTURES> _Textures;
	std::array<Uniform, GFX_MAX_UNIFORMS> _Uniforms;
	std::array<Program, GFX_MAX_PROGRAMS> _Programs;
	std::array<FrameBuffer, GFX_MAX_FRAME_BUFFERS> _FrameBuffers;
	std::array<std::optional<XE::uint32>, GFX_MAX_OCCLUSION> _Occlusions;

	XE::ConcurrentHandleAllocator<XE::ViewHandle, GFX_MAX_VIEW> _ViewHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ShaderHandle, GFX_MAX_SHADERS> _ShaderHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ProgramHandle, GFX_MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::TextureHandle, GFX_MAX_TEXTURES> _TextureHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::UniformHandle, GFX_MAX_UNIFORMS> _UniformHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::OcclusionQueryHandle, GFX_MAX_OCCLUSION> _OcclusionHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::FrameBufferHandle, GFX_MAX_FRAME_BUFFERS> _FrameBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::IndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  _IndexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::VertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> _VertexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::VertexLayoutHandle, GFX_MAX_VERTEX_LAYOUTS> _VertexLayoutHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::DynamicIndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  _DynamicIndexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::DynamicVertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> _DynamicVertexBufferHandleAlloc;
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

	_p->_Caps.VendorId = val.vendorId;
	_p->_Caps.DeviceId = val.deviceId;
	_p->_Caps.TransientIbSize = val.transientIbSize;
	_p->_Caps.TransientVbSize = val.transientVbSize;

	_p->_SubmitFrame = &_p->_Frames[0];
	_p->_RenderFrame = &_p->_Frames[1];

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::RENDERER_INIT );
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

	OnRender( _p->_RenderFrame );
}

void XE::RendererContext::Shutdown()
{
	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::RENDERER_SHUTDOWN );
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

XE::CapsInfo & XE::RendererContext::GetCaps()
{
	return _p->_Caps;
}

XE::InitInfo & XE::RendererContext::GetInit()
{
	return _p->_Init;
}

XE::IndexBufferHandle XE::RendererContext::CreateIndexBuffer( const BufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_IndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::TransientIndexBufferHandle XE::RendererContext::CreateTransientIndexBuffer( const BufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_SubmitFrame->TransientIndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TRANSIENT_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

void XE::RendererContext::Destory( IndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_INDEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::VertexLayoutHandle XE::RendererContext::CreateVertexLayout( const VertexLayoutDesc & val )
{
	auto handle = _p->_VertexLayoutHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );
	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_LAYOUT );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( val );

	return handle;
}

void XE::RendererContext::Destory( VertexLayoutHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_VERTEX_LAYOUT , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::VertexBufferHandle XE::RendererContext::CreateVertexBuffer( const VertexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_VertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::TransientVertexBufferHandle XE::RendererContext::CreateTransientVertexBuffer( const VertexBufferDesc & desc, XE::MemoryView Data )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	auto handle = _p->_SubmitFrame->TransientVertexBufferHandleAlloc.Alloc();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TRANSIENT_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

void XE::RendererContext::Destory( VertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_VERTEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( const BufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_DynamicIndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

void XE::RendererContext::Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( start );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

void XE::RendererContext::Destory( DynamicIndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_DYNAMIC_INDEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( const VertexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_DynamicVertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

void XE::RendererContext::Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( start );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

void XE::RendererContext::Destory( DynamicVertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_DYNAMIC_VERTEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::IndirectBufferHandle XE::RendererContext::CreateIndirectBuffer( XE::uint64 num )
{
	IndirectBufferHandle handle = _p->_VertexBufferHandleAlloc.Alloc().GetValue();


	uint32_t size = num * GFX_MAX_DRAW_INDIRECT_STRIDE;
	uint16_t flags = GFX_MAX_DRAW_INDIRECT_BUFFERS;

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( size );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

void XE::RendererContext::Destory( IndirectBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_DYNAMIC_VERTEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::ShaderHandle XE::RendererContext::CreateShader( const ShaderDesc & val )
{
	auto handle = _p->_ShaderHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_SHADER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( val.Name );
	_p->_SubmitFrame->PrevCmd.Wirte( val.Type );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( val.Data ) );

	return handle;
}

void XE::RendererContext::Destory( ShaderHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_SHADER , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::Array<XE::UniformHandle> XE::RendererContext::GetShaderUniforms( ShaderHandle handle )
{
	return _p->_Shaders[handle].Uniforms;
}

XE::ProgramHandle XE::RendererContext::CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader )
{
	auto handle = _p->_ProgramHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Programs[handle].VS = vs;
	_p->_Programs[handle].FS = fs;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_PROGRAM );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( vs );
	_p->_SubmitFrame->PrevCmd.Wirte( fs );

	if( des_shader )
	{
		Destory( vs );
		Destory( fs );
	}

	return handle;
}

XE::ProgramHandle XE::RendererContext::CreateProgram( ShaderHandle cs, bool des_shader )
{
	auto handle = _p->_ProgramHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Programs[handle].CS = cs;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_PROGRAM );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( cs );

	if( des_shader )
	{
		Destory( cs );
	}

	return handle;
}

void XE::RendererContext::Destory( ProgramHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_PROGRAM , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::TextureHandle XE::RendererContext::CreateTexture( const TextureDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

void XE::RendererContext::Update( const UpdateTextureDesc & desc, XE::MemoryView Data )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );
}

void XE::RendererContext::ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::READ_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( data );
	_p->_SubmitFrame->PrevCmd.Wirte( mip );
}

void XE::RendererContext::Destory( TextureHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_TEXTURE , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const FrameBufferDesc & val )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( val );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const FrameBufferFromWindowDesc & val )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( val );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const FrameBufferFromTextureDesc & val )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( val );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const FrameBufferFromAttachmentDesc & val )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( val );

	return handle;
}

XE::TextureHandle XE::RendererContext::GetTexture( FrameBufferHandle handle, XE::uint8 attachment )
{
	if( _p->_FrameBuffers[handle].Window )
	{
		return TextureHandle::Invalid;
	}

	return _p->_FrameBuffers[handle].Textures[attachment];
}

void XE::RendererContext::Destory( FrameBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_FRAMEBUFFER , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::UniformHandle XE::RendererContext::CreateUniform( const XE::String & name, UniformType type, XE::uint16 num )
{
	auto handle = _p->_UniformHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_UNIFORM );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( type );
	_p->_SubmitFrame->PrevCmd.Wirte( num );

	return handle;
}

const XE::Uniform & XE::RendererContext::GetUniformInfo( UniformHandle handle )
{
	return _p->_Uniforms[handle];
}

void XE::RendererContext::Destory( UniformHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_UNIFORM , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::OcclusionQueryHandle XE::RendererContext::CreateOcclusionQuery()
{
	auto handle = _p->_OcclusionHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_OCCLUSION_QUERY );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );

	return handle;
}

std::optional<XE::uint32> XE::RendererContext::GetOcclusionQueryValue( OcclusionQueryHandle handle )
{
	if( _p->_Occlusions[handle] == 0 )
	{
		return std::nullopt;
	}

	return _p->_Occlusions[handle];
}

void XE::RendererContext::Destory( OcclusionQueryHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_OCCLUSION_QUERY , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

void XE::RendererContext::Destory( XE::TransientIndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_TRANSIENT_INDEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

void XE::RendererContext::Destory( XE::TransientVertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_TRANSIENT_VERTEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );
}

XE::ViewHandle XE::RendererContext::CreateView( const ViewDesc & val )
{
	auto handle = _p->_ViewHandleAlloc.Alloc();

	_p->_Views[handle].Name = val.Name;
	_p->_Views[handle].ClearColor = val.ClearColor;
	_p->_Views[handle].ClearDepth = val.ClearDepth;
	_p->_Views[handle].ClearStencil = val.ClearStencil;
	_p->_Views[handle].Flags = val.Flags;
	_p->_Views[handle].ViewRect = val.ViewRect;
	_p->_Views[handle].ViewScissor = val.ViewScissor;
	_p->_Views[handle].ModelMat = val.ModelMat;
	_p->_Views[handle].ViewMat = val.ViewMat;
	_p->_Views[handle].ProjMat = val.ProjMat;
	_p->_Views[handle].Mode = val.Mode;
	_p->_Views[handle].Handle = val.FrameBuffer;

	return handle;
}

void XE::RendererContext::SetViewName( ViewHandle handle, const XE::String & name )
{
	_p->_Views[handle].Name = name;
}

void XE::RendererContext::SetViewRect( ViewHandle handle, const XE::Rect & rect )
{
	_p->_Views[handle].ViewRect = rect;
}

void XE::RendererContext::SetViewScissor( ViewHandle handle, const XE::Rect & scissor )
{
	_p->_Views[handle].ViewScissor = scissor;
}

void XE::RendererContext::SetViewClear( const ViewClearDesc & val )
{
	_p->_Views[val.Handle].ClearColor = val.Color;
	_p->_Views[val.Handle].ClearDepth = val.Depth;
	_p->_Views[val.Handle].ClearStencil = val.Stencil;
	_p->_Views[val.Handle].Flags = val.Flags;
}

void XE::RendererContext::SetViewMode( ViewHandle handle, XE::ViewMode mode )
{
	_p->_Views[handle].Mode = mode;
}

void XE::RendererContext::SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame )
{
	_p->_Views[handle].Handle = frame;
}

void XE::RendererContext::SetViewTransform( ViewHandle handle, const XE::Mat4f & model, const XE::Mat4f & view, const XE::Mat4f & proj )
{
	_p->_Views[handle].ModelMat = model;
	_p->_Views[handle].ViewMat = view;
	_p->_Views[handle].ProjMat = proj;
}

void XE::RendererContext::ResetView( ViewHandle handle, const ViewDesc & val )
{
	_p->_Views[handle].Name = val.Name;
	_p->_Views[handle].ClearColor = val.ClearColor;
	_p->_Views[handle].ClearDepth = val.ClearDepth;
	_p->_Views[handle].ClearStencil = val.ClearStencil;
	_p->_Views[handle].Flags = val.Flags;
	_p->_Views[handle].ViewRect = val.ViewRect;
	_p->_Views[handle].ViewScissor = val.ViewScissor;
	_p->_Views[handle].ModelMat = val.ModelMat;
	_p->_Views[handle].ViewMat = val.ViewMat;
	_p->_Views[handle].ProjMat = val.ProjMat;
	_p->_Views[handle].Mode = val.Mode;
}

void XE::RendererContext::Destory( ViewHandle handle )
{
	_p->_ViewHandleAlloc.Free( handle );
}

void XE::RendererContext::RequestScreenShot( FrameBufferHandle handle, const XE::FileSystem::Path & path )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );

	_p->_SubmitFrame->PostCmd.Wirte( CommandType::REQUEST_SCREEN_SHOT );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
	_p->_SubmitFrame->PostCmd.Wirte( path.u8string() );
}

XE::MemoryView XE::RendererContext::CopyToFrame( XE::MemoryView mem ) const
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->TransientBufferMutex );

	auto pos = _p->_SubmitFrame->TransientBuffers.View().data() + _p->_SubmitFrame->TransientBuffers.WirtePos();

	_p->_SubmitFrame->TransientBuffers.Wirte( mem.data(), mem.size() );

	return XE::MemoryView( pos, mem.size() );
}
