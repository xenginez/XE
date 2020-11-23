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

	std::array<PView, GFX_MAX_VIEW> _Views;
	std::array<PShader, GFX_MAX_SHADERS> _Shaders;
	std::array<PTexture, GFX_MAX_TEXTURES> _Textures;
	std::array<PProgram, GFX_MAX_PROGRAMS> _Programs;
	std::array<POcclusionQuery, GFX_MAX_OCCLUSION> _Occlusions;
	std::array<PFrameBuffer, GFX_MAX_FRAME_BUFFERS> _FrameBuffers;
	std::array<PIndexBuffer, GFX_MAX_INDEX_BUFFERS> _IndexBuffers;
	std::array<PVertexLayout, GFX_MAX_VERTEX_LAYOUTS> _VertexLayouts;
	std::array<PVertexBuffer, GFX_MAX_VERTEX_BUFFERS> _VertexBuffers;
	std::array<PIndirectBuffer, GFX_MAX_DRAW_INDIRECT_BUFFERS> _IndirectBuffers;
	std::array<PDynamicIndexBuffer, GFX_MAX_INDEX_BUFFERS> _DynamicIndexBuffers;
	std::array<PDynamicVertexBuffer, GFX_MAX_VERTEX_BUFFERS> _DynamicVertexBuffers;

	XE::ConcurrentHandleAllocator<XE::ViewHandle, GFX_MAX_VIEW> _ViewHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ShaderHandle, GFX_MAX_SHADERS> _ShaderHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ProgramHandle, GFX_MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::TextureHandle, GFX_MAX_TEXTURES> _TextureHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::OcclusionQueryHandle, GFX_MAX_OCCLUSION> _OcclusionHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::FrameBufferHandle, GFX_MAX_FRAME_BUFFERS> _FrameBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::IndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  _IndexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::VertexLayoutHandle, GFX_MAX_VERTEX_LAYOUTS> _VertexLayoutHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::VertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> _VertexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::IndirectBufferHandle, GFX_MAX_DRAW_INDIRECT_BUFFERS> _IndirectBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::DynamicIndexBufferHandle, GFX_MAX_DYNAMIC_INDEX_BUFFERS>  _DynamicIndexBufferHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::DynamicVertexBufferHandle, GFX_MAX_DYNAMIC_VERTEX_BUFFERS> _DynamicVertexBufferHandleAlloc;
};

XE::RendererContext::RendererContext()
	:_p( new Private )
{

}

XE::RendererContext::~RendererContext()
{
	delete _p;
}

void XE::RendererContext::Init( const InitDesc & desc )
{
	_p->_Init = desc;

	_p->_Caps.VendorId = desc.vendorId;
	_p->_Caps.DeviceId = desc.deviceId;

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

XE::ViewHandle XE::RendererContext::Create( const ViewDesc & desc )
{
	auto handle = _p->_ViewHandleAlloc.Alloc();

	_p->_Views[handle].Reset();

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
	_p->_Views[handle].Handle = desc.FrameBuffer;
	_p->_Views[handle].Desc = desc;

	return handle;
}

XE::ProgramHandle XE::RendererContext::Create( const XE::ProgramDesc & desc )
{
	auto handle = _p->_ProgramHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Programs[handle].Reset();

	_p->_Programs[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_PROGRAM );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::Create( const XE::FrameBufferDesc & desc )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_FrameBuffers[handle].Reset();

	_p->_FrameBuffers[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::VertexLayoutHandle XE::RendererContext::Create( const XE::VertexLayoutDesc & desc )
{
	auto handle = _p->_VertexLayoutHandleAlloc.Alloc();

	_p->_VertexLayouts[handle].Reset();

	_p->_VertexLayouts[handle].Desc = desc;

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );
	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_LAYOUT );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::OcclusionQueryHandle XE::RendererContext::Create( const OcclusionQueryDesc & desc )
{
	auto handle = _p->_OcclusionHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Occlusions[handle].Reset();

	_p->_Occlusions[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_OCCLUSION_QUERY );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );

	return handle;
}

XE::IndirectBufferHandle XE::RendererContext::Create( const XE::IndirectBufferDesc & desc )
{
	auto handle = _p->_IndirectBufferHandleAlloc.Alloc().GetValue();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_IndirectBuffers[handle].Reset();

	_p->_IndirectBuffers[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );

	return handle;
}

XE::ShaderHandle XE::RendererContext::Create( const XE::ShaderDesc & desc, XE::MemoryView data )
{
	auto handle = _p->_ShaderHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Shaders[handle].Reset();

	_p->_Shaders[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_SHADER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc.Name );
	_p->_SubmitFrame->PrevCmd.Wirte( desc.Type );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( data ) );

	return handle;
}

XE::TextureHandle XE::RendererContext::Create( const XE::TextureDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Textures[handle].Reset();

	_p->_Textures[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::IndexBufferHandle XE::RendererContext::Create( const XE::IndexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_IndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_IndexBuffers[handle].Reset();

	_p->_IndexBuffers[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::VertexBufferHandle XE::RendererContext::Create( const XE::VertexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_VertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_VertexBuffers[handle].Reset();

	_p->_VertexBuffers[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::DynamicIndexBufferHandle XE::RendererContext::Create( const XE::DynamicIndexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_DynamicIndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_DynamicIndexBuffers[handle].Reset();

	_p->_DynamicIndexBuffers[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

XE::DynamicVertexBufferHandle XE::RendererContext::Create( const XE::DynamicVertexBufferDesc & desc, XE::MemoryView Data )
{
	auto handle = _p->_DynamicVertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_DynamicVertexBuffers[handle].Reset();

	_p->_DynamicVertexBuffers[handle].Desc = desc;

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( desc );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( Data ) );

	return handle;
}

const XE::ViewDesc & XE::RendererContext::GetDesc( XE::ViewHandle handle )
{
	return _p->_Views[handle].Desc;
}

const XE::ShaderDesc & XE::RendererContext::GetDesc( XE::ShaderHandle handle )
{
	return _p->_Shaders[handle].Desc;
}

const XE::ProgramDesc & XE::RendererContext::GetDesc( XE::ProgramHandle handle )
{
	return _p->_Programs[handle].Desc;
}

const XE::TextureDesc & XE::RendererContext::GetDesc( XE::TextureHandle handle )
{
	return _p->_Textures[handle].Desc;
}

const XE::FrameBufferDesc & XE::RendererContext::GetDesc( XE::FrameBufferHandle handle )
{
	return _p->_FrameBuffers[handle].Desc;
}

const XE::IndexBufferDesc & XE::RendererContext::GetDesc( XE::IndexBufferHandle handle )
{
	return _p->_IndexBuffers[handle].Desc;
}

const XE::VertexLayoutDesc & XE::RendererContext::GetDesc( XE::VertexLayoutHandle handle )
{
	return _p->_VertexLayouts[handle].Desc;
}

const XE::VertexBufferDesc & XE::RendererContext::GetDesc( XE::VertexBufferHandle handle )
{
	return _p->_VertexBuffers[handle].Desc;
}

const XE::IndirectBufferDesc & XE::RendererContext::GetDesc( XE::IndirectBufferHandle handle )
{
	return _p->_IndirectBuffers[handle].Desc;
}

const XE::OcclusionQueryDesc & XE::RendererContext::GetDesc( XE::OcclusionQueryHandle handle )
{
	return _p->_Occlusions[handle].Desc;
}

const XE::DynamicIndexBufferDesc & XE::RendererContext::GetDesc( XE::DynamicIndexBufferHandle handle )
{
	return _p->_DynamicIndexBuffers[handle].Desc;
}

const XE::DynamicVertexBufferDesc & XE::RendererContext::GetDesc( XE::DynamicVertexBufferHandle handle )
{
	return _p->_DynamicVertexBuffers[handle].Desc;
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

	_p->_VertexLayoutHandleAlloc.Free( handle );
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
	if( _p->_FrameBuffers[handle].Desc.Window )
	{
		return TextureHandle::Invalid;
	}

	return _p->_FrameBuffers[handle].Desc.Attachments[attachment].handle;
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
