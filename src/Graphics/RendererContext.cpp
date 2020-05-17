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

	std::array<View, GFX_MAX_VIEW> _Views = {};

	XE::ConcurrentHandleAllocator<XE::ViewHandle, GFX_MAX_VIEW> _ViewHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ShaderHandle, GFX_MAX_SHADERS> _ShaderHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::ProgramHandle, GFX_MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::TextureHandle, GFX_MAX_TEXTURES> _TextureHandleAlloc;
	XE::ConcurrentHandleAllocator<XE::UniformHandle, GFX_MAX_UNIFORMS> _UniformHandleAlloc;
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
	
	Render( _p->_RenderFrame );
}

const XE::CapsInfo & XE::RendererContext::GetCaps() const
{
	return _p->_Caps;
}

const XE::InitInfo & XE::RendererContext::GetInitInfo() const
{
	return _p->_Init;
}

void XE::RendererContext::Destory( IndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_INDEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( VertexLayoutHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_VERTEX_LAYOUT );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( VertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_VERTEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( DynamicIndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( DynamicVertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( IndirectBufferHandle handle )
{
	// TODO: 
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_INDEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( ShaderHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_SHADER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( ProgramHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_PROGRAM );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( TextureHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_TEXTURE );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( FrameBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_FRAMEBUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( UniformHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_UNIFORM );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( OcclusionQueryHandle handle )
{
	// TODO: 
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_INDEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

void XE::RendererContext::Destory( ViewHandle handle )
{
	_p->_ViewHandleAlloc.Free( handle );
}

XE::IndexBufferHandle XE::RendererContext::CreateIndexBuffer( const XE::String & name, XE::memory_view mem, XE::Flags< XE::BufferFlag > flags )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	auto handle = _p->_IndexBufferHandleAlloc.Alloc();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

XE::TransientIndexBufferHandle XE::RendererContext::CreateTransientIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	auto handle = _p->_SubmitFrame->TransientIndexBufferHandleAlloc.Alloc();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TRANSIENT_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( mem );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );
	 
	return handle;
}

XE::VertexLayoutHandle XE::RendererContext::CreateVertexLayout( const XE::Array<VertexLayout> & layouts )
{
	auto handle = _p->_VertexLayoutHandleAlloc.Alloc();

	XE::memory_view view( ( const char * )layouts.data(), layouts.size() * sizeof( VertexLayout ) );

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );
	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_LAYOUT );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( view ) );

	return handle;
}

XE::VertexBufferHandle XE::RendererContext::CreateVertexBuffer( const XE::String & name, XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	auto handle = _p->_VertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
	_p->_SubmitFrame->PrevCmd.Wirte( layout );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

XE::TransientVertexBufferHandle XE::RendererContext::CreateTransientVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	auto handle = _p->_SubmitFrame->TransientVertexBufferHandleAlloc.Alloc();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TRANSIENT_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
	_p->_SubmitFrame->PrevCmd.Wirte( layout );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( XE::uint64 size, XE::Flags< XE::BufferFlag > flags )
{
	auto handle = _p->_DynamicIndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( size );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags )
{
	auto handle = _p->_DynamicIndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

void XE::RendererContext::Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::memory_view mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( start );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

void XE::RendererContext::Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::memory_view mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( start );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( XE::uint64 size, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	auto handle = _p->_DynamicVertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( size );
	_p->_SubmitFrame->PrevCmd.Wirte( layout );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags )
{
	auto handle = _p->_DynamicVertexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
	_p->_SubmitFrame->PrevCmd.Wirte( layout );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

XE::IndirectBufferHandle XE::RendererContext::CreateIndirectBuffer( XE::uint64 num )
{
	// TODO: 
	return {};
}

XE::ShaderHandle XE::RendererContext::CreateShader( const XE::String & name, XE::memory_view mem )
{
	auto handle = _p->_ShaderHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_SHADER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );

	return handle;
}

XE::Array<XE::UniformHandle> XE::RendererContext::GetShaderUniforms( ShaderHandle handle )
{
	// TODO: 
	return {};
}

XE::ProgramHandle XE::RendererContext::CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader )
{
	auto handle = _p->_ProgramHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

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

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_PROGRAM );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( cs );

	if( des_shader )
	{
		Destory( cs );
	}

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTexture2D( const XE::String & name, XE::uint32 width, XE::uint32 height, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_2D );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( hasmips );
	_p->_SubmitFrame->PrevCmd.Wirte( layers );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );
	_p->_SubmitFrame->PrevCmd.Wirte( U );
	_p->_SubmitFrame->PrevCmd.Wirte( V );
	_p->_SubmitFrame->PrevCmd.Wirte( W );
	_p->_SubmitFrame->PrevCmd.Wirte( MIN );
	_p->_SubmitFrame->PrevCmd.Wirte( MAG );
	_p->_SubmitFrame->PrevCmd.Wirte( MIP );
	if( mem != std::nullopt )
	{
		_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( *mem ) );
	}
	else
	{
		_p->_SubmitFrame->PrevCmd.Wirte( XE::memory_view() );
	}

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTexture2D( const XE::String & name, XE::BackbufferRatio ratio, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_2D );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( ratio );
	_p->_SubmitFrame->PrevCmd.Wirte( hasmips );
	_p->_SubmitFrame->PrevCmd.Wirte( layers );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );
	_p->_SubmitFrame->PrevCmd.Wirte( U );
	_p->_SubmitFrame->PrevCmd.Wirte( V );
	_p->_SubmitFrame->PrevCmd.Wirte( W );
	_p->_SubmitFrame->PrevCmd.Wirte( MIN );
	_p->_SubmitFrame->PrevCmd.Wirte( MAG );
	_p->_SubmitFrame->PrevCmd.Wirte( MIP );

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTexture3D( const XE::String & name, XE::uint32 width, XE::uint32 height, XE::uint32 depth, bool hasmips, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_3D );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( depth );
	_p->_SubmitFrame->PrevCmd.Wirte( hasmips );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );
	_p->_SubmitFrame->PrevCmd.Wirte( U );
	_p->_SubmitFrame->PrevCmd.Wirte( V );
	_p->_SubmitFrame->PrevCmd.Wirte( W );
	_p->_SubmitFrame->PrevCmd.Wirte( MIN );
	_p->_SubmitFrame->PrevCmd.Wirte( MAG );
	_p->_SubmitFrame->PrevCmd.Wirte( MIP );
	if( mem != std::nullopt )
	{
		_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( *mem ) );
	}
	else
	{
		_p->_SubmitFrame->PrevCmd.Wirte( XE::memory_view() );
	}

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTextureCube( const XE::String & name, XE::uint32 size, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_CUBE );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( size );
	_p->_SubmitFrame->PrevCmd.Wirte( hasmips );
	_p->_SubmitFrame->PrevCmd.Wirte( layers );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );
	_p->_SubmitFrame->PrevCmd.Wirte( U );
	_p->_SubmitFrame->PrevCmd.Wirte( V );
	_p->_SubmitFrame->PrevCmd.Wirte( W );
	_p->_SubmitFrame->PrevCmd.Wirte( MIN );
	_p->_SubmitFrame->PrevCmd.Wirte( MAG );
	_p->_SubmitFrame->PrevCmd.Wirte( MIP );
	if( mem != std::nullopt )
	{
		_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( *mem ) );
	}
	else
	{
		_p->_SubmitFrame->PrevCmd.Wirte( XE::memory_view() );
	}

	return handle;
}

void XE::RendererContext::UpdateTexture2D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 width, XE::uint32 height, XE::memory_view mem, XE::uint32 pitch )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_2D );
	_p->_SubmitFrame->PrevCmd.Wirte( layer );
	_p->_SubmitFrame->PrevCmd.Wirte( mip );
	_p->_SubmitFrame->PrevCmd.Wirte( x );
	_p->_SubmitFrame->PrevCmd.Wirte( y );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
	_p->_SubmitFrame->PrevCmd.Wirte( pitch );
}

void XE::RendererContext::UpdateTexture3D( TextureHandle handle, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::memory_view mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_2D );
	_p->_SubmitFrame->PrevCmd.Wirte( mip );
	_p->_SubmitFrame->PrevCmd.Wirte( x );
	_p->_SubmitFrame->PrevCmd.Wirte( y );
	_p->_SubmitFrame->PrevCmd.Wirte( z );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( depth );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

void XE::RendererContext::UpdateTextureCube( TextureHandle handle, XE::uint16 layer, XE::uint8 side, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::memory_view mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_CUBE );
	_p->_SubmitFrame->PrevCmd.Wirte( layer );
	_p->_SubmitFrame->PrevCmd.Wirte( side );
	_p->_SubmitFrame->PrevCmd.Wirte( mip );
	_p->_SubmitFrame->PrevCmd.Wirte( x );
	_p->_SubmitFrame->PrevCmd.Wirte( y );
	_p->_SubmitFrame->PrevCmd.Wirte( z );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( depth );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

XE::uint32 XE::RendererContext::ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip )
{
	// TODO: 
	return {};
}

XE::uint8 * XE::RendererContext::GetDirectAccess( TextureHandle handle )
{
	// TODO: 
	return {};
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, XE::uint32 width, XE::uint32 height, TextureFormat format, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( U );
	_p->_SubmitFrame->PrevCmd.Wirte( V );
	_p->_SubmitFrame->PrevCmd.Wirte( W );
	_p->_SubmitFrame->PrevCmd.Wirte( MIN );
	_p->_SubmitFrame->PrevCmd.Wirte( MAG );
	_p->_SubmitFrame->PrevCmd.Wirte( MIP );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, XE::BackbufferRatio ratio, TextureFormat format, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( ratio );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( U );
	_p->_SubmitFrame->PrevCmd.Wirte( V );
	_p->_SubmitFrame->PrevCmd.Wirte( W );
	_p->_SubmitFrame->PrevCmd.Wirte( MIN );
	_p->_SubmitFrame->PrevCmd.Wirte( MAG );
	_p->_SubmitFrame->PrevCmd.Wirte( MIP );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, const XE::Array< TextureHandle > handles, bool des_texture )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( handles );

	if (des_texture)
	{
		for( auto tex : handles )
		{
			Destory( tex );
		}
	}

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, const XE::Array< Attachment > attachments, bool des_texture )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	XE::memory_view view( ( const char * )attachments.data(), attachments.size() );

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( view ) );

	if( des_texture )
	{
		for( const auto & tex : attachments )
		{
			Destory( tex.handle );
		}
	}

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, WindowHandle window, XE::uint32 width, XE::uint32 height, TextureFormat color_format, TextureFormat depth_format )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( color_format );
	_p->_SubmitFrame->PrevCmd.Wirte( depth_format );

	return handle;
}

XE::TextureHandle XE::RendererContext::GetTexture( FrameBufferHandle handle, XE::uint8 attachment )
{
	// TODO: 
	return {};
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
	// TODO: 
	return {};
}

XE::OcclusionQueryHandle XE::RendererContext::CreateOcclusionQuery()
{
	// TODO: 
	return {};
}

XE::OcclusionQueryResult XE::RendererContext::GetOcclusionQueryResult( OcclusionQueryHandle handle )
{
	// TODO: 
	return {};
}

std::optional<XE::uint32> XE::RendererContext::GetOcclusionQueryValue( OcclusionQueryHandle handle )
{
	// TODO: 
	return {};
}

XE::ViewHandle XE::RendererContext::CreateView()
{
	return _p->_ViewHandleAlloc.Alloc();
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

void XE::RendererContext::SetViewClear( ViewHandle handle, std::optional<XE::Color> color, std::optional<XE::float32> depth, std::optional<XE::uint8> stencil )
{
	// TODO: 
	if (color != std::nullopt)
	{
		_p->_Views[handle].ClearColor = *color;
		_p->_Views[handle].Flag |= ClearFlag::COLOR;
	}

	if (depth != std::nullopt)
	{
		_p->_Views[handle].ClearColor = *depth;
		_p->_Views[handle].Flag |= ClearFlag::DEPTH;
	}

	if (stencil != std::nullopt)
	{
		_p->_Views[handle].ClearStencil = *stencil;
		_p->_Views[handle].Flag |= ClearFlag::STENCIL;
	}
}

void XE::RendererContext::SetViewMode( ViewHandle handle, XE::ViewMode mode )
{
	_p->_Views[handle].Mode = mode;
}

void XE::RendererContext::SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame )
{
	_p->_Views[handle].Handle = frame;
}

void XE::RendererContext::SetViewTransform( ViewHandle handle, const XE::Mat4 & view, const XE::Mat4 & proj )
{
	_p->_Views[handle].ViewMat = view;
	_p->_Views[handle].ProjMat = proj;
}

void XE::RendererContext::ResetView( ViewHandle handle )
{
	_p->_Views[handle] = {};
}

void XE::RendererContext::DebugTextPrint( XE::uint32 x, XE::uint32 y, const XE::Color & color, const std::string & text )
{

}

void XE::RendererContext::RequestScreenShot( FrameBufferHandle handle, const std::filesystem::path & path )
{

}

XE::memory_view XE::RendererContext::CopyToFrame( XE::memory_view mem ) const
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->TransientBufferMutex );

	auto pos = _p->_SubmitFrame->TransientBuffer.WirtePos();
	_p->_SubmitFrame->TransientBuffer.Wirte( mem );

	return XE::memory_view( ( const char * )pos, mem.size() );
}
