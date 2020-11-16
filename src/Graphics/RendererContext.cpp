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

	_p->_Caps.TransientIbSize = val.transientIbSize;
	_p->_Caps.TransientVbSize = val.transientVbSize;
	_p->_Caps.VendorId = val.vendorId;
	_p->_Caps.DeviceId = val.deviceId;

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

XE::IndexBufferHandle XE::RendererContext::CreateIndexBuffer( const XE::String & name, XE::MemoryView mem, XE::Flags< XE::BufferFlags > flags )
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

XE::TransientIndexBufferHandle XE::RendererContext::CreateTransientIndexBuffer( XE::MemoryView mem, XE::Flags< XE::BufferFlags > flags )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	auto handle = _p->_SubmitFrame->TransientIndexBufferHandleAlloc.Alloc();

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_TRANSIENT_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( mem );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

void XE::RendererContext::Destory( IndexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_INDEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

XE::VertexLayoutHandle XE::RendererContext::CreateVertexLayout( const XE::Array<VertexLayout> & layouts )
{
	auto handle = _p->_VertexLayoutHandleAlloc.Alloc();

	XE::MemoryView view( ( const char * )layouts.data(), layouts.size() * sizeof( VertexLayout ) );

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );
	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_VERTEX_LAYOUT );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( view ) );

	return handle;
}

void XE::RendererContext::Destory( VertexLayoutHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_VERTEX_LAYOUT );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

XE::VertexBufferHandle XE::RendererContext::CreateVertexBuffer( const XE::String & name, XE::MemoryView mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags )
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

XE::TransientVertexBufferHandle XE::RendererContext::CreateTransientVertexBuffer( XE::MemoryView mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags )
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

void XE::RendererContext::Destory( VertexBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_VERTEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( XE::uint64 size, XE::Flags< XE::BufferFlags > flags )
{
	auto handle = _p->_DynamicIndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( size );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

	return handle;
}

XE::DynamicIndexBufferHandle XE::RendererContext::CreateDynamicIndexBuffer( XE::MemoryView mem, XE::Flags< XE::BufferFlags > flags )
{
	auto handle = _p->_DynamicIndexBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_INDEX_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
	_p->_SubmitFrame->PrevCmd.Wirte( flags );

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
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_DYNAMIC_INDEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( XE::uint64 size, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags )
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

XE::DynamicVertexBufferHandle XE::RendererContext::CreateDynamicVertexBuffer( XE::MemoryView mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlags > flags )
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
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
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
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_DYNAMIC_VERTEX_BUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

XE::ShaderHandle XE::RendererContext::CreateShader( const XE::String & name, ShaderType type, XE::MemoryView mem )
{
	auto handle = _p->_ShaderHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_SHADER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( type );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );

	return handle;
}

void XE::RendererContext::Destory( ShaderHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_SHADER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
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
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_PROGRAM );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

XE::TextureHandle XE::RendererContext::CreateTexture2D( const XE::String & name, XE::uint32 width, XE::uint32 height, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlags > flags, XE::Flags< XE::SamplerFlags > sampler, std::optional< XE::MemoryView > mem )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_Textures[handle].Name = name;
	_p->_Textures[handle].StorageSize = 0;
	_p->_Textures[handle].Width = width;
	_p->_Textures[handle].Height = height;
	_p->_Textures[handle].Depth = 0;
	_p->_Textures[handle].NumLayers = std::max<XE::uint16>( layers, 1 );
	_p->_Textures[handle].NumMips = hasmips ? 1 + uint32_t( std::log2( float( std::max( width, height ) ) ) ) : 0;
	_p->_Textures[handle].BitsPerPixel = 0;
	_p->_Textures[handle].CubeMap = false;
	_p->_Textures[handle].Format = format;

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
	_p->_SubmitFrame->PrevCmd.Wirte( sampler );
	if( mem != std::nullopt )
	{
		_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( *mem ) );
	}
	else
	{
		_p->_SubmitFrame->PrevCmd.Wirte( XE::MemoryView() );
	}

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTexture2D( const XE::String & name, XE::BackbufferRatio ratio, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlags > flags, XE::Flags< XE::SamplerFlags > sampler )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	XE::uint32 width = _p->_Init.width;
	XE::uint32 height = _p->_Init.height;

	switch( ratio )
	{
	case BackbufferRatio::HALF:
		width /= 2;
		height /= 2;
		break;
	case BackbufferRatio::QUARTER:
		width /= 4;
		height /= 4;
		break;
	case BackbufferRatio::EIGHTH:
		width /= 8;
		height /= 8;
		break;
	case BackbufferRatio::SIXTEENTH:
		width /= 16;
		height /= 16;
		break;
	case BackbufferRatio::DOUBLE:
		width *= 2;
		height *= 2;
		break;
	default:
		break;
	}

	width = std::max<XE::uint32>( 1, width );
	height = std::max<XE::uint32>( 1, height );

	_p->_Textures[handle].Name = name;
	_p->_Textures[handle].StorageSize = 0;
	_p->_Textures[handle].Width = width;
	_p->_Textures[handle].Height = height;
	_p->_Textures[handle].Depth = 0;
	_p->_Textures[handle].NumLayers = std::max<XE::uint16>( layers, 1 );
	_p->_Textures[handle].NumMips = hasmips ? 1 + uint32_t( std::log2( float( std::max( width, height ) ) ) ) : 0;
	_p->_Textures[handle].BitsPerPixel = 0;
	_p->_Textures[handle].CubeMap = false;
	_p->_Textures[handle].Format = format;

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
	_p->_SubmitFrame->PrevCmd.Wirte( sampler );
	_p->_SubmitFrame->PrevCmd.Wirte( XE::MemoryView() );

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTexture3D( const XE::String & name, XE::uint32 width, XE::uint32 height, XE::uint32 depth, bool hasmips, TextureFormat format, XE::Flags< XE::TextureFlags > flags, XE::Flags< XE::SamplerFlags > sampler, std::optional< XE::MemoryView > mem )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	width = std::max<XE::uint32>( 1, width );
	height = std::max<XE::uint32>( 1, height );

	_p->_Textures[handle].Name = name;
	_p->_Textures[handle].StorageSize = 0;
	_p->_Textures[handle].Width = width;
	_p->_Textures[handle].Height = height;
	_p->_Textures[handle].Depth = depth;
	_p->_Textures[handle].NumLayers = 1;
	_p->_Textures[handle].NumMips = hasmips ? 1 + uint32_t( std::log2( float( std::max( width, std::max( height, depth ) ) ) ) ) : 0;
	_p->_Textures[handle].BitsPerPixel = 0;
	_p->_Textures[handle].CubeMap = false;
	_p->_Textures[handle].Format = format;

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
	_p->_SubmitFrame->PrevCmd.Wirte( sampler );
	if( mem != std::nullopt )
	{
		_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( *mem ) );
	}
	else
	{
		_p->_SubmitFrame->PrevCmd.Wirte( XE::MemoryView() );
	}

	return handle;
}

XE::TextureHandle XE::RendererContext::CreateTextureCube( const XE::String & name, XE::uint32 size, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlags > flags, XE::Flags< XE::SamplerFlags > sampler, std::optional< XE::MemoryView > mem )
{
	auto handle = _p->_TextureHandleAlloc.Alloc();

	_p->_Textures[handle].Name = name;
	_p->_Textures[handle].StorageSize = 0;
	_p->_Textures[handle].Width = size;
	_p->_Textures[handle].Height = size;
	_p->_Textures[handle].Depth = 0;
	_p->_Textures[handle].NumLayers = std::max<XE::uint16>( layers, 1 );
	_p->_Textures[handle].NumMips = hasmips ? 1 + uint32_t( std::log2( float( std::max( size, size ) ) ) ) : 0;
	_p->_Textures[handle].BitsPerPixel = 0;
	_p->_Textures[handle].CubeMap = true;
	_p->_Textures[handle].Format = format;

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
	_p->_SubmitFrame->PrevCmd.Wirte( sampler );
	if( mem != std::nullopt )
	{
		_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( *mem ) );
	}
	else
	{
		_p->_SubmitFrame->PrevCmd.Wirte( XE::MemoryView() );
	}

	return handle;
}

void XE::RendererContext::UpdateTexture2D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 width, XE::uint32 height, XE::MemoryView mem, XE::uint32 pitch )
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

void XE::RendererContext::UpdateTexture3D( TextureHandle handle, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::MemoryView mem )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::UPDATE_TEXTURE );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( TextureType::TEXTURE_3D );
	_p->_SubmitFrame->PrevCmd.Wirte( mip );
	_p->_SubmitFrame->PrevCmd.Wirte( x );
	_p->_SubmitFrame->PrevCmd.Wirte( y );
	_p->_SubmitFrame->PrevCmd.Wirte( z );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( depth );
	_p->_SubmitFrame->PrevCmd.Wirte( CopyToFrame( mem ) );
}

void XE::RendererContext::UpdateTextureCube( TextureHandle handle, XE::uint16 layer, XE::uint8 side, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::MemoryView mem )
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

void XE::RendererContext::Destory( TextureHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_TEXTURE );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, XE::uint32 width, XE::uint32 height, TextureFormat format, XE::Flags< XE::SamplerFlags > sampler )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( width );
	_p->_SubmitFrame->PrevCmd.Wirte( height );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( sampler );

	return handle;
}

XE::FrameBufferHandle XE::RendererContext::CreateFrameBuffer( const XE::String & name, XE::BackbufferRatio ratio, TextureFormat format, XE::Flags< XE::SamplerFlags > sampler )
{
	auto handle = _p->_FrameBufferHandleAlloc.Alloc();

	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PrevCmdMutex );

	_p->_SubmitFrame->PrevCmd.Wirte( CommandType::CREATE_FRAME_BUFFER );
	_p->_SubmitFrame->PrevCmd.Wirte( handle );
	_p->_SubmitFrame->PrevCmd.Wirte( name );
	_p->_SubmitFrame->PrevCmd.Wirte( ratio );
	_p->_SubmitFrame->PrevCmd.Wirte( format );
	_p->_SubmitFrame->PrevCmd.Wirte( sampler );

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

	if( des_texture )
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

	XE::MemoryView view( ( const char * )attachments.data(), attachments.size() );

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
	if( _p->_FrameBuffers[handle].Window )
	{
		return TextureHandle::Invalid;
	}

	return _p->_FrameBuffers[handle].Textures[attachment];
}

void XE::RendererContext::Destory( FrameBufferHandle handle )
{
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_FRAMEBUFFER );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
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
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_UNIFORM );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
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
	std::unique_lock<std::mutex> lock( _p->_SubmitFrame->PostCmdMutex );
	_p->_SubmitFrame->PostCmd.Wirte( CommandType::DESTROY_OCCLUSION_QUERY );
	_p->_SubmitFrame->PostCmd.Wirte( handle );
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
	if (color != std::nullopt)
	{
		_p->_Views[handle].ClearColor = *color;
		_p->_Views[handle].Flag |= ClearFlags::COLOR;
	}

	if (depth != std::nullopt)
	{
		_p->_Views[handle].ClearColor = *depth;
		_p->_Views[handle].Flag |= ClearFlags::DEPTH;
	}

	if (stencil != std::nullopt)
	{
		_p->_Views[handle].ClearStencil = *stencil;
		_p->_Views[handle].Flag |= ClearFlags::STENCIL;
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

void XE::RendererContext::SetViewTransform( ViewHandle handle, const XE::Mat4f & view, const XE::Mat4f & proj )
{
	_p->_Views[handle].ViewMat = view;
	_p->_Views[handle].ProjMat = proj;
}

void XE::RendererContext::ResetView( ViewHandle handle )
{
	_p->_Views[handle] = {};
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

	auto pos = _p->_SubmitFrame->TransientBuffers.WirtePos();
	_p->_SubmitFrame->TransientBuffers.Wirte( mem );

	return XE::MemoryView( ( const char * )pos, mem.size() );
}

void XE::RendererContext::ResizeTexture( TextureHandle handle, XE::uint32 layers, XE::uint32 mips, XE::uint32 width, XE::uint32 height )
{

}
