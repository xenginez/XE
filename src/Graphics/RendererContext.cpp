#include "RendererContext.h"

#include <optional>

#include "Interface/IFramework.h"
#include "Interface/IThreadService.h"

#include "Encoder.h"

struct XE::RendererContext::Private
{
	std::mutex _FrameMutex;
	XE::RenderFrame * _SubmitFrame;
	XE::RenderFrame * _RenderFrame;
	std::array<XE::RenderFrame, 2> _Frames;

	XE::CapsInfo _Caps;
	XE::InitDesc _Init;

	std::array<View, GFX_MAX_VIEW> _Views;
	std::array<PShader, GFX_MAX_SHADERS> _Shaders;
	std::array<PTexture, GFX_MAX_TEXTURES> _Textures;
	std::array<PProgram, GFX_MAX_PROGRAMS> _Programs;
	std::array<PVertexLayout, GFX_MAX_VERTEX_LAYOUTS> _Layouts;
	std::array<POcclusionQuery, GFX_MAX_OCCLUSION> _Occlusions;
	std::array<PFrameBuffer, GFX_MAX_FRAME_BUFFERS> _FrameBuffers;
	std::array<PIndexBuffer, GFX_MAX_INDEX_BUFFERS> _IndexBuffers;
	std::array<PVertexBuffer, GFX_MAX_VERTEX_BUFFERS> _VertexBuffers;
	std::array<PVertexBuffer, GFX_MAX_VERTEX_BUFFERS> _VertexBuffers;
	std::array<PIndirectBuffer, GFX_MAX_DRAW_INDIRECT_BUFFERS> _IndirectBuffers;

	XE::ConcurrentHandleAllocator<XE::ViewHandle, GFX_MAX_VIEW> _ViewHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ShaderHandle, GFX_MAX_SHADERS> _ShaderHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ProgramHandle, GFX_MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::TextureHandle, GFX_MAX_TEXTURES> _TextureHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::VertexLayoutHandle, GFX_MAX_VERTEX_LAYOUTS> _LayoutHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::OcclusionQueryHandle, GFX_MAX_OCCLUSION> _OcclusionHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::FrameBufferHandle, GFX_MAX_FRAME_BUFFERS> _FrameBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::IndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  _IndexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::VertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> _VertexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::IndirectBufferHandle, GFX_MAX_DRAW_INDIRECT_BUFFERS> _IndirectBufferHandleAlloc;
};

XE::RendererContext::RendererContext()
	:_p( new Private )
{

}

XE::RendererContext::~RendererContext()
{
	delete _p;
}

void XE::RendererContext::Init( const InitDesc & val )
{
	_p->_Init = val;

	_p->_Caps.VendorId = val.vendorId;
	_p->_Caps.DeviceId = val.deviceId;

	_p->_SubmitFrame = &_p->_Frames[0];
	_p->_RenderFrame = &_p->_Frames[1];

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::RENDERER_INIT );
}

void XE::RendererContext::Present()
{
	{
		std::unique_lock<std::mutex> lock( _p->_FrameMutex );

		std::swap( _p->_SubmitFrame, _p->_RenderFrame );
	}

	XE::IFramework::GetCurrentFramework()->GetThreadService()->PostTask( XE::ThreadType::RENDER, std::bind( &XE::RendererContext::Render, this ) );

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

XE::InitDesc & XE::RendererContext::GetInit()
{
	return _p->_Init;
}

void XE::RendererContext::Inc( XE::ViewHandle handle )
{
	_p->_Views[handle].Inc();
}

void XE::RendererContext::Inc( XE::ShaderHandle handle )
{
	_p->_Shaders[handle].Inc();
}

void XE::RendererContext::Inc( XE::ProgramHandle handle )
{
	_p->_Programs[handle].Inc();
}

void XE::RendererContext::Inc( XE::TextureHandle handle )
{
	_p->_Textures[handle].Inc();
}

void XE::RendererContext::Inc( XE::FrameBufferHandle handle )
{
	_p->_FrameBuffers[handle].Inc();
}

void XE::RendererContext::Inc( XE::IndexBufferHandle handle )
{
	_p->_IndexBuffers[handle].Inc();
}

void XE::RendererContext::Inc( XE::VertexLayoutHandle handle )
{
	_p->_Shaders[handle].Inc();
}

void XE::RendererContext::Inc( XE::VertexBufferHandle handle )
{
	_p->_VertexBuffers[handle].Inc();
}

void XE::RendererContext::Inc( XE::OcclusionQueryHandle handle )
{
	_p->_Occlusions[handle].Inc();
}

void XE::RendererContext::Inc( XE::IndirectBufferHandle handle )
{
	_p->_Shaders[handle].Inc();
}

void XE::RendererContext::Inc( XE::DynamicIndexBufferHandle handle )
{
	_p->_IndexBuffers[handle].Inc();
}

void XE::RendererContext::Inc( XE::DynamicVertexBufferHandle handle )
{
	_p->_VertexBuffers[handle].Inc();
}

void XE::RendererContext::Dec( XE::ViewHandle handle )
{
	if( _p->_Views[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::ShaderHandle handle )
{
	if( _p->_Shaders[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::ProgramHandle handle )
{
	if( _p->_Programs[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::TextureHandle handle )
{
	if( _p->_Textures[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::FrameBufferHandle handle )
{
	if( _p->_FrameBuffers[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::IndexBufferHandle handle )
{
	if( _p->_IndexBuffers[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::VertexLayoutHandle handle )
{
	if( _p->_Shaders[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::VertexBufferHandle handle )
{
	if( _p->_VertexBuffers[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::OcclusionQueryHandle handle )
{
	if( _p->_Occlusions[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::IndirectBufferHandle handle )
{
	if( _p->_Shaders[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::DynamicIndexBufferHandle handle )
{
	if( _p->_IndexBuffers[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

void XE::RendererContext::Dec( XE::DynamicVertexBufferHandle handle )
{
	if( _p->_VertexBuffers[handle].Dec() <= 0 )
	{
		Destory( handle );
	}
}

XE::ViewHandle XE::RendererContext::CreateView( const ViewDesc & val )
{
	auto handle = _p->_ViewHandleAlloc.Alloc();

	_p->_Views[handle].Reset();

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

XE::OcclusionQueryHandle XE::RendererContext::CreateOcclusionQuery()
{
	auto handle = _p->_OcclusionHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Occlusions[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_OCCLUSION_QUERY );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );

	return handle;
}

XE::ProgramHandle XE::RendererContext::CreateProgram( const XE::ProgramDesc & desc )
{
	auto handle = _p->_ProgramHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Programs[handle].Reset();

	_p->_Programs[handle];

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_PROGRAM );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::IndirectBufferHandle XE::RendererContext::CreateIndirectBuffer( const XE::BufferDesc & desc )
{
	auto handle = _p->_IndirectBufferHandleAlloc.Alloc().GetValue();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_IndirectBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::VertexLayoutHandle XE::RendererContext::CreateVertexLayout( const XE::VertexLayoutDesc & desc )
{
	auto handle = _p->_LayoutHandleAlloc.Alloc();

	_p->_Layouts[handle].Reset();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );
	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_LAYOUT );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::ShaderHandle XE::RendererContext::CreateShader( const XE::ShaderDesc & desc, XE::MemoryView data )
{
	auto handle = _p->_ShaderHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Shaders[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_SHADER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc.Name );
	_p->_SubmitFrame->PrevCmd.Wirte( desc.Type );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( data ) );

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTexture( const XE::TextureDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Textures[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::FrameBufferDesc & desc )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_FrameBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::FrameBufferFromWindowDesc & desc )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_FrameBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::FrameBufferFromTextureDesc & desc )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_FrameBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::FrameBufferFromAttachmentDesc & desc )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_FrameBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::IndexBufferHandle XE::RendererContext::CreateIndexBuffer( const XE::BufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_IndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_IndexBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::VertexBufferHandle XE::RendererContext::CreateVertexBuffer( const XE::VertexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_VertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_VertexBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( const XE::BufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_IndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_IndexBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle.GetValue();
}

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( const XE::VertexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_VertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_VertexBuffers[handle].Reset();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle.GetValue();
}

void XE::RendererContext::Destory( XE::ViewHandle handle )
{
	_p->_ViewHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::ShaderHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_SHADER , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_ShaderHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::ProgramHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_PROGRAM , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_ProgramHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::TextureHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_TEXTURE , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_TextureHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::FrameBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_FRAMEBUFFER , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_FrameBufferHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::IndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_INDEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_IndexBufferHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::VertexLayoutHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_VERTEX_LAYOUT , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_LayoutHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::VertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_VERTEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_VertexBufferHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::IndirectBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_DYNAMIC_VERTEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_IndirectBufferHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::OcclusionQueryHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_OCCLUSION_QUERY , handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_OcclusionHandleAlloc.Free( handle );
}

void XE::RendererContext::Destory( XE::DynamicIndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_DYNAMIC_INDEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_IndexBufferHandleAlloc.Free( handle.GetValue() );
}

void XE::RendererContext::Destory( XE::DynamicVertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->DestoryCmdMutex );
	DestoryHandle des = { DestoryHandle::DestoryType::DESTROY_DYNAMIC_VERTEX_BUFFER, handle };
	_p->_SubmitFrame->DestoryCmd.Wirte( des );

	_p->_VertexBufferHandleAlloc.Free( handle.GetValue() );
}

void XE::RendererContext::Update( const XE::UpdateTextureDesc & desc, XE::MemoryView Data )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );
}

void XE::RendererContext::Update( XE::DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( start );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

void XE::RendererContext::Update( XE::DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( start );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

XE::Array<XE::UniformDesc> XE::RendererContext::GetShaderUniforms( XE::ShaderHandle handle )
{
	return _p->_Shaders[handle].Uniforms;
}

void XE::RendererContext::ReadTexture( XE::TextureHandle handle, XE::uint8 * data, XE::uint8 mip )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::READ_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( data );
	_p->_SubmitFrame->PrevCmd.Wirte( mip );
}

XE::TextureHandle XE::RendererContext::GetTexture( XE::FrameBufferHandle handle, XE::uint8 attachment )
{
	if( _p->_FrameBuffers[handle].Window )
	{
		return TextureHandle::Invalid;
	}

	return _p->_FrameBuffers[handle].Textures[attachment];
}

std::optional<XE::uint32> XE::RendererContext::GetOcclusionQueryValue( XE::OcclusionQueryHandle handle )
{
	if( _p->_Occlusions[handle].Value == 0 )
	{
		return std::nullopt;
	}

	return _p->_Occlusions[handle].Value;
}

void XE::RendererContext::SetViewName( XE::ViewHandle handle, const XE::String & name )
{
	_p->_Views[handle].Name = name;
}

void XE::RendererContext::SetViewRect( XE::ViewHandle handle, const XE::Rectf & rect )
{
	_p->_Views[handle].ViewRect = rect;
}

void XE::RendererContext::SetViewScissor( XE::ViewHandle handle, const XE::Rectf & scissor )
{
	_p->_Views[handle].ViewScissor = scissor;
}

void XE::RendererContext::SetViewClear( const XE::ViewClearDesc & desc )
{
	_p->_Views[desc.Handle].ClearColor = desc.Color;
	_p->_Views[desc.Handle].ClearDepth = desc.Depth;
	_p->_Views[desc.Handle].ClearStencil = desc.Stencil;
	_p->_Views[desc.Handle].Flags = desc.Flags;
}

void XE::RendererContext::SetViewMode( XE::ViewHandle handle, XE::ViewMode mode )
{
	_p->_Views[handle].Mode = mode;
}

void XE::RendererContext::SetViewFrameBuffer( XE::ViewHandle handle, FrameBufferHandle frame )
{
	_p->_Views[handle].Handle = frame;
}

void XE::RendererContext::SetViewTransform( XE::ViewHandle handle, const XE::Mat4f & model, const XE::Mat4f & view, const XE::Mat4f & proj )
{
	_p->_Views[handle].ModelMat = model;
	_p->_Views[handle].ViewMat = view;
	_p->_Views[handle].ProjMat = proj;
}

void XE::RendererContext::ResetView( XE::ViewHandle handle, const XE::ViewDesc & desc )
{
	_p->_Views[handle].Name = desc.Name;
	_p->_Views[handle].ClearColor = desc.ClearColor;
	_p->_Views[handle].ClearDepth = desc.ClearDepth;
	_p->_Views[handle].ClearStencil = desc.ClearStencil;
	_p->_Views[handle].Flags = desc.Flags;
	_p->_Views[handle].ViewRect = desc.ViewRect;
	_p->_Views[handle].ViewScissor = desc.ViewScissor;
	_p->_Views[handle].ModelMat = desc.ModelMat;
	_p->_Views[handle].ViewMat = desc.ViewMat;
	_p->_Views[handle].ProjMat = desc.ProjMat;
	_p->_Views[handle].Mode = desc.Mode;
}

void XE::RendererContext::RequestScreenShot( XE::FrameBufferHandle handle, const XE::FileSystem::Path & path )
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
