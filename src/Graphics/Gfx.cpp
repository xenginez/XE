#include "Gfx.h"

#include "RendererContextNull.h"
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
	ret.push_back( XE::RendererContextType::NIL );

	return ret;
}

void XE::Gfx::Init( const XE::InitInfo & val )
{
	auto type = val.type;

	if( type == RendererContextType::NONE )
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
	case XE::RendererContextType::GLES3:
	case XE::RendererContextType::OPENGL:
		_p->_Context = XE::CreateRendererContextGL();
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
	case XE::RendererContextType::NIL:
		_p->_Context = XE::CreateRendererContextNull();
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

XE::IndexBufferHandle XE::Gfx::CreateIndexBuffer( const BufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateIndexBuffer( desc, data );
}

XE::TransientIndexBufferHandle XE::Gfx::CreateTransientIndexBuffer( const BufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTransientIndexBuffer( desc, data );
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

XE::VertexLayoutHandle XE::Gfx::CreateVertexLayout( const VertexLayoutDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateVertexLayout( val );
}

XE::VertexBufferHandle XE::Gfx::CreateVertexBuffer( const VertexBufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateVertexBuffer( desc, data );
}

XE::TransientVertexBufferHandle XE::Gfx::CreateTransientVertexBuffer( const VertexBufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTransientVertexBuffer( desc, data );
}

void XE::Gfx::Update( DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Update( handle, start, mem );
}

void XE::Gfx::Update( DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Update( handle, start, mem );
}

XE::DynamicIndexBufferHandle XE::Gfx::CreateDynamicIndexBuffer( const BufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateDynamicIndexBuffer( desc, data );
}

XE::DynamicVertexBufferHandle XE::Gfx::CreateDynamicVertexBuffer( const VertexBufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateDynamicVertexBuffer( desc, data );
}

XE::IndirectBufferHandle XE::Gfx::CreateIndirectBuffer( XE::uint64 num )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateIndirectBuffer( num );
}

XE::ShaderHandle XE::Gfx::CreateShader( const ShaderDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateShader( val );
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

XE::TextureHandle XE::Gfx::CreateTexture( const TextureDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateTexture( desc, data );
}

void XE::Gfx::Update( const UpdateTextureDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->Update( desc, data );
}

void XE::Gfx::ReadTexture( TextureHandle handle, XE::uint8 * data, XE::uint8 mip /*= 0 */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->ReadTexture( handle, data, mip );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const FrameBufferDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( val );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const FrameBufferFromWindowDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( val );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const FrameBufferFromTextureDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( val );
}

XE::FrameBufferHandle XE::Gfx::CreateFrameBuffer( const FrameBufferFromAttachmentDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateFrameBuffer( val );
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

XE::OcclusionQueryHandle XE::Gfx::CreateOcclusionQuery()
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateOcclusionQuery();
}

std::optional<XE::uint32> XE::Gfx::GetOcclusionQueryValue( OcclusionQueryHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetOcclusionQueryValue( handle );
}

XE::ViewHandle XE::Gfx::CreateView( const XE::ViewDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->CreateView( val );
}

void XE::Gfx::SetViewName( ViewHandle handle, const XE::String & name )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewName( handle, name );
}

void XE::Gfx::SetViewRect( ViewHandle handle, const XE::Rectf & rect )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewRect( handle, rect );
}

void XE::Gfx::SetViewScissor( ViewHandle handle, const XE::Rectf & scissor )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewScissor( handle, scissor );
}

void XE::Gfx::SetViewClear( const ViewClearDesc & val )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewClear( val );
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

void XE::Gfx::SetViewTransform( ViewHandle handle, const XE::Mat4f & model, const XE::Mat4f & view, const XE::Mat4f & proj )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewTransform( handle, model, view, proj );
}

void XE::Gfx::RequestScreenShot( FrameBufferHandle handle, const XE::FileSystem::Path & path )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->RequestScreenShot( handle, path );
}
