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
#elif PLATFORM_OS & (OS_XBOX)
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

void XE::Gfx::Init( const XE::InitDesc & val )
{
	auto type = val.type;
	auto contexts = GetSupportedContext();

	while( _p->_Context == nullptr )
	{
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

		if( type == RendererContextType::NONE && !contexts.empty() )
		{
			type = contexts.front();
			contexts.erase( contexts.begin() );
		}
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

void XE::Gfx::Present()
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Present();
}

XE::RefHandle< XE::ViewHandle > XE::Gfx::Create( const XE::ViewDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::ProgramHandle > XE::Gfx::Create( const XE::ProgramDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::FrameBufferHandle > XE::Gfx::Create( const XE::FrameBufferDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::VertexLayoutHandle > XE::Gfx::Create( const XE::VertexLayoutDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::OcclusionQueryHandle > XE::Gfx::Create( const OcclusionQueryDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::IndirectBufferHandle > XE::Gfx::Create( const XE::IndirectBufferDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::ShaderHandle > XE::Gfx::Create( const XE::ShaderDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::TextureHandle > XE::Gfx::Create( const XE::TextureDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::IndexBufferHandle > XE::Gfx::Create( const XE::IndexBufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::VertexBufferHandle > XE::Gfx::Create( const XE::VertexBufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::DynamicIndexBufferHandle > XE::Gfx::Create( const XE::DynamicIndexBufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::DynamicVertexBufferHandle > XE::Gfx::Create( const XE::DynamicVertexBufferDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

const XE::ViewDesc & XE::Gfx::GetDesc( XE::ViewHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::ShaderDesc & XE::Gfx::GetDesc( XE::ShaderHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::ProgramDesc & XE::Gfx::GetDesc( XE::ProgramHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::TextureDesc & XE::Gfx::GetDesc( XE::TextureHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::FrameBufferDesc & XE::Gfx::GetDesc( XE::FrameBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::IndexBufferDesc & XE::Gfx::GetDesc( XE::IndexBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::VertexLayoutDesc & XE::Gfx::GetDesc( XE::VertexLayoutHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::VertexBufferDesc & XE::Gfx::GetDesc( XE::VertexBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::IndirectBufferDesc & XE::Gfx::GetDesc( XE::IndirectBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::OcclusionQueryDesc & XE::Gfx::GetDesc( XE::OcclusionQueryHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::DynamicIndexBufferDesc & XE::Gfx::GetDesc( XE::DynamicIndexBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

const XE::DynamicVertexBufferDesc & XE::Gfx::GetDesc( XE::DynamicVertexBufferHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetDesc( handle );
}

void XE::Gfx::Update( const XE::UpdateTextureDesc & desc, XE::MemoryView data )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->Update( desc, data );
}

void XE::Gfx::Update( XE::DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Update( handle, start, mem );
}

void XE::Gfx::Update( XE::DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->Update( handle, start, mem );
}

XE::Array<XE::UniformDesc> XE::Gfx::GetShaderUniforms( XE::ShaderHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetShaderUniforms( handle );
}

void XE::Gfx::ReadTexture( XE::TextureHandle handle, XE::uint8 * data, XE::uint8 mip /*= 0 */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->ReadTexture( handle, data, mip );
}

XE::TextureHandle XE::Gfx::GetTexture( XE::FrameBufferHandle handle, XE::uint8 attachment /*= 0 */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetTexture( handle, attachment );
}

std::optional<XE::uint32> XE::Gfx::GetOcclusionQueryValue( XE::OcclusionQueryHandle handle )
{
	XE_ASSERT( _p->_Context != nullptr );

	return _p->_Context->GetOcclusionQueryValue( handle );
}

void XE::Gfx::SetViewName( XE::ViewHandle handle, const XE::String & name )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewName( handle, name );
}

void XE::Gfx::SetViewRect( XE::ViewHandle handle, const XE::Rectf & rect )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewRect( handle, rect );
}

void XE::Gfx::SetViewScissor( XE::ViewHandle handle, const XE::Rectf & scissor )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewScissor( handle, scissor );
}

void XE::Gfx::SetViewClear( const XE::ViewClearDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewClear( desc );
}

void XE::Gfx::SetViewMode( XE::ViewHandle handle, XE::ViewMode mode /*= ViewMode::Default */ )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewMode( handle, mode );
}

void XE::Gfx::SetViewFrameBuffer( XE::ViewHandle handle, FrameBufferHandle frame )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewFrameBuffer( handle, frame );
}

void XE::Gfx::SetViewTransform( XE::ViewHandle handle, const XE::Mat4f & model, const XE::Mat4f & view, const XE::Mat4f & proj )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->SetViewTransform( handle, model, view, proj );
}

void XE::Gfx::ResetView( XE::ViewHandle handle, const XE::ViewDesc & desc )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->ResetView( handle, desc );
}

void XE::Gfx::RequestScreenShot( XE::FrameBufferHandle handle, const XE::FileSystem::Path & path )
{
	XE_ASSERT( _p->_Context != nullptr );

	_p->_Context->RequestScreenShot( handle, path );
}
