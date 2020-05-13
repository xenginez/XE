#include "Gfx.h"

#include "RendererContextGLES2.h"
#include "RendererContextGLES3.h"
#include "RendererContextMetal.h"
#include "RendererContextOpenGL.h"
#include "RendererContextVulkan.h"
#include "RendererContextSoftware.h"
#include "RendererContextDirectX11.h"
#include "RendererContextDirectX12.h"

struct XE::Gfx::Private
{
	RendererContext * _Context = nullptr;
};

XE::Gfx::Gfx()
	:_p( new Private )
{

}

XE::Gfx::~Gfx()
{
	delete _p;
}

const XE::CapsInfo & XE::Gfx::GetCaps()
{
	return _p->_Context->GetCaps();
}

XE::Array<XE::RendererContextType> XE::Gfx::GetSupportedContext()
{
	XE::Array<XE::RendererContextType> ret;

#if PLATFORM_OS & (OS_WINDOWS)
	ret.push_back( XE::RendererContextType::DIRECT3D12 );
	ret.push_back( XE::RendererContextType::DIRECT3D11 );
	ret.push_back( XE::RendererContextType::VULKAN );
	ret.push_back( XE::RendererContextType::OPENGL );
#elif PLATFORM_OS & (OS_XBOXONE)
	ret.push_back( XE::RendererContextType::DIRECT3D12 );
#elif PLATFORM_OS & (OS_MAC)
	ret.push_back( XE::RendererContextType::METAL );
	ret.push_back( XE::RendererContextType::OPENGL );
#elif PLATFORM_OS & (OS_IOS)
	ret.push_back( XE::RendererContextType::METAL );
	ret.push_back( XE::RendererContextType::GLES2 );
#elif PLATFORM_OS & (OS_ANDROID)
	ret.push_back( XE::RendererContextType::VULKAN );
	ret.push_back( XE::RendererContextType::GLES3 );
	ret.push_back( XE::RendererContextType::GLES2 );
#elif PLATFORM_OS & (OS_LINUX)
	ret.push_back( XE::RendererContextType::VULKAN );
	ret.push_back( XE::RendererContextType::OPENGL );
#endif

	ret.push_back( XE::RendererContextType::SOFTWARE );

	return ret;
}

void XE::Gfx::Init( const XE::InitInfo & val )
{
	auto type = val.type;

	if( type == RendererContextType::NOOP )
	{
		type = GetSupportedContext().front();
	}

	switch( type )
	{
	case XE::RendererContextType::METAL:
		_p->_Context = XE::CreateRendererContextMetal();
		break;
	case XE::RendererContextType::VULKAN:
		_p->_Context = XE::CreateRendererContextVulkan();
		break;
	case XE::RendererContextType::GLES2:
		_p->_Context = XE::CreateRendererContextGLES2();
		break;
	case XE::RendererContextType::GLES3:
		_p->_Context = XE::CreateRendererContextGLES3();
		break;
	case XE::RendererContextType::OPENGL:
		_p->_Context = XE::CreateRendererContextOpenGL();
		break;
	case XE::RendererContextType::DIRECT3D11:
		_p->_Context = XE::CreateRendererContextDirectX11();
		break;
	case XE::RendererContextType::DIRECT3D12:
		_p->_Context = XE::CreateRendererContextDirectX12();
		break;
	case XE::RendererContextType::SOFTWARE:
		_p->_Context = XE::CreateRendererContextSoftware();
		break;
	default:
		break;
	}

	XE_ASSERT( _p->_Context == nullptr );

	_p->_Context->Init( val );
}

void XE::Gfx::Shutdown()
{
	if( _p->_Context )
	{
		_p->_Context->Shutdown();

		delete _p->_Context;

		_p->_Context = nullptr;
	}
}

void XE::Gfx::Reset( XE::uint32 width, XE::uint32 height, XE::Flags<XE::ResetFlag> flags /*= XE::ResetFlag::NONE*/, XE::TextureFormat format /*= XE::TextureFormat::COUNT */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Reset( width, height, flags, format );
}

XE::Encoder * XE::Gfx::Begin()
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->Begin();
}

void XE::Gfx::End( XE::Encoder * val )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->End( val );
}

void XE::Gfx::Frame( bool capture /*= false */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Frame( capture );
}

void XE::Gfx::Render()
{
	_p->_Context->Render();
}

void XE::Gfx::DebugTextPrint( XE::uint32 x, XE::uint32 y, const XE::Color & color, const std::string & text )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->DebugTextPrint( x, y, color, text );
}

XE::IndexBufferHandle XE::Gfx::CreateIndexBuffer( const XE::String & name, XE::memory_view mem, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateIndexBuffer( name, mem, flags );
}

XE::TransientIndexBufferHandle XE::Gfx::CreateTransientIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTransientIndexBuffer( mem, flags );
}

void XE::Gfx::Destory( IndexBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( VertexLayoutHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( VertexBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( DynamicIndexBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( DynamicVertexBufferHandle handle )
{

}

void XE::Gfx::Destory( IndirectBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( ShaderHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( ProgramHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( TextureHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( FrameBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( UniformHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( OcclusionQueryHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

void XE::Gfx::Destory( ViewHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Destory( handle );
}

XE::VertexLayoutHandle XE::Gfx::CreateVertexLayout( const XE::Array<VertexLayout> & layouts )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateVertexLayout( layouts );
}

XE::VertexBufferHandle XE::Gfx::CreateVertexBuffer( const XE::String & name, XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateVertexBuffer( name, mem, layout, flags );
}

XE::TransientVertexBufferHandle XE::Gfx::CreateTransientVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTransientVertexBuffer( mem, layout, flags );
}

XE::DynamicIndexBufferHandle XE::Gfx::CreateDynamicIndexBuffer( XE::uint64 size, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateDynamicIndexBuffer( size, flags );
}

XE::DynamicIndexBufferHandle XE::Gfx::CreateDynamicIndexBuffer( XE::memory_view mem, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateDynamicIndexBuffer( mem, flags );
}

void XE::Gfx::Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::memory_view mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Update( handle, start, mem );
}

void XE::Gfx::Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::memory_view mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Update( handle, start, mem );
}

XE::DynamicVertexBufferHandle XE::Gfx::CreateDynamicVertexBuffer( XE::uint64 size, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateDynamicVertexBuffer( size, layout, flags );
}

XE::DynamicVertexBufferHandle XE::Gfx::CreateDynamicVertexBuffer( XE::memory_view mem, VertexLayoutHandle layout, XE::Flags< XE::BufferFlag > flags /*= XE::BufferFlag::NONE */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateDynamicVertexBuffer( mem, layout, flags );
}

XE::IndirectBufferHandle XE::Gfx::CreateIndirectBuffer( XE::uint64 num )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateIndirectBuffer( num );
}

XE::ShaderHandle XE::Gfx::CreateShader( const XE::String & name, XE::memory_view mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateShader( name, mem );
}

XE::Array<XE::UniformHandle> XE::Gfx::GetShaderUniforms( ShaderHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetShaderUniforms( handle );
}

XE::ProgramHandle XE::Gfx::CreateProgram( ShaderHandle vs, ShaderHandle fs, bool des_shader /*= false */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateProgram( vs, fs, des_shader );
}

XE::ProgramHandle XE::Gfx::CreateProgram( ShaderHandle cs, bool des_shader /*= false */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateProgram( cs, des_shader );
}

XE::TextureHandle XE::Gfx::CreateTexture2D( const XE::String & name, XE::uint32 width, XE::uint32 height, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem /*= std::nullopt */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTexture2D( name, width, height, hasmips, layers, format, flags, U, V, W, MIN, MAG, MIP, mem );
}

XE::TextureHandle XE::Gfx::CreateTexture2D( const XE::String & name, XE::BackbufferRatio ratio, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTexture2D( name, ratio, hasmips, layers, format, flags, U, V, W, MIN, MAG, MIP );
}

XE::TextureHandle XE::Gfx::CreateTexture3D( const XE::String & name, XE::uint32 width, XE::uint32 height, XE::uint32 depth, bool hasmips, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem /*= std::nullopt */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTexture3D( name, width, height, depth, hasmips, format, flags, U, V, W, MIN, MAG, MIP, mem );
}

XE::TextureHandle XE::Gfx::CreateTextureCube( const XE::String & name, XE::uint32 size, bool hasmips, XE::uint16 layers, TextureFormat format, XE::Flags< XE::TextureFlag > flags, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP, std::optional< XE::memory_view > mem /*= std::nullopt */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTextureCube( name, size, hasmips, layers, format, flags, U, V, W, MIN, MAG, MIP, mem );
}

void XE::Gfx::UpdateTexture2D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 width, XE::uint32 height, XE::memory_view mem, XE::uint32 pitch /*= 0 */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->UpdateTexture2D( handle, layer, mip, x, y, width, height, mem, pitch );
}

void XE::Gfx::UpdateTexture3D( TextureHandle handle, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::memory_view mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->UpdateTexture3D( handle, mip, x, y, z, width, height, depth, mem );
}

void XE::Gfx::UpdateTextureCube( TextureHandle handle, XE::uint16 layer, XE::uint8 side, XE::uint8 mip, XE::uint32 x, XE::uint32 y, XE::uint32 z, XE::uint32 width, XE::uint32 height, XE::uint32 depth, XE::memory_view mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->UpdateTextureCube( handle, layer, side, mip, x, y, z, width, height, depth, mem );
}

XE::uint32 XE::Gfx::ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip /*= 0 */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->ReadTexture( handle, data, mip );
}

XE::uint8 * XE::Gfx::GetDirectAccess( TextureHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDirectAccess( handle );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const XE::String & name, XE::uint32 width, XE::uint32 height, TextureFormat format, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( name, width, height, format, U, V, W, MIN, MAG, MIP );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const XE::String & name, XE::BackbufferRatio ratio, TextureFormat format, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer(name, ratio, format, U, V, W, MIN, MAG, MIP );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const XE::String & name, const XE::Array< TextureHandle > handles, bool des_texture /*= false */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( name, handles, des_texture );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const XE::String & name, const XE::Array< Attachment > attachments, bool des_texture /*= false */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( name, attachments, des_texture );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const XE::String & name, WindowHandle window, XE::uint32 width, XE::uint32 height, TextureFormat color_format /*= TextureFormat::COUNT*/, TextureFormat depth_format /*= TextureFormat::COUNT */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( name, window, width, height, color_format, depth_format );
}

XE::TextureHandle XE::Gfx::GetTexture( FrameBufferHandle handle, XE::uint8 attachment /*= 0 */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetTexture( handle, attachment );
}

XE::UniformHandle XE::Gfx::CreateUniform( const XE::String & name, UniformType type, XE::uint16 num /*= 1 */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateUniform( name, type, num );
}

const XE::UniformInfo & XE::Gfx::GetUniformInfo( UniformHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetUniformInfo( handle );
}

XE::OcclusionQueryHandle XE::Gfx::CreateOcclusionQuery()
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateOcclusionQuery();
}

XE::OcclusionQueryResult XE::Gfx::GetOcclusionQueryResult( OcclusionQueryHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetOcclusionQueryResult( handle );
}

std::optional<XE::uint32> XE::Gfx::GetOcclusionQueryValue( OcclusionQueryHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetOcclusionQueryValue( handle );
}

XE::ViewHandle XE::Gfx::CreateView()
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateView();
}

void XE::Gfx::SetViewName( ViewHandle handle, const XE::String & name )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewName( handle, name );
}

void XE::Gfx::SetViewRect( ViewHandle handle, const XE::Rect & rect )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewRect( handle, rect );
}

void XE::Gfx::SetViewScissor( ViewHandle handle, const XE::Rect & scissor )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewScissor( handle, scissor );
}

void XE::Gfx::SetViewClear( ViewHandle handle, std::optional<XE::Color> color /*= std::nullopt*/, std::optional<XE::float32> depth /*= std::nullopt*/, std::optional<XE::uint8> stencil /*= std::nullopt */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewClear( handle, color, depth, stencil );
}

void XE::Gfx::SetViewMode( ViewHandle handle, XE::ViewMode mode /*= ViewMode::Default */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewMode( handle, mode );
}

void XE::Gfx::SetViewFrameBuffer( ViewHandle handle, FrameBufferHandle frame )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewFrameBuffer( handle, frame );
}

void XE::Gfx::SetViewTransform( ViewHandle handle, const XE::Mat4 & view, const XE::Mat4 & proj )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewTransform( handle, view, proj );
}

void XE::Gfx::ResetView( ViewHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->ResetView( handle );
}

void XE::Gfx::RequestScreenShot( FrameBufferHandle handle, const std::filesystem::path & path )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->RequestScreenShot( handle, path );
}
