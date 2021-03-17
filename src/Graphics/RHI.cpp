#include "RHI.h"

#include "GraphicsContextNull.h"
#include "GraphicsContextD3D12.h"
#include "GraphicsContextMetal.h"
#include "GraphicsContextHTML5.h"
#include "GraphicsContextVulkan.h"
#include "GraphicsContextSoftware.h"

struct XE::RHI::Private
{
	GraphicsContext * _Context = nullptr;
};

XE::RHI::RHI()
	:_p( new Private )
{

}

XE::RHI::~RHI()
{
	delete _p;
}

const XE::CapsInfo & XE::RHI::GetCaps()
{
	return _p->_Context->GetCaps();
}

XE::List< XE::GraphicsContextType > XE::RHI::GetSupportedContext()
{
	XE::List< XE::GraphicsContextType > ret;

#if PLATFORM_OS & (OS_WINDOWS)
	ret.push_back( XE::GraphicsContextType::D3D12 );
	ret.push_back( XE::GraphicsContextType::VULKAN );
#elif PLATFORM_OS & (OS_HTML5)
	ret.push_back( XE::GraphicsContextType::HTML5 );
#elif PLATFORM_OS & (OS_XBOX)
	ret.push_back( XE::GraphicsContextType::D3D12 );
#elif PLATFORM_OS & (OS_MAC)
	ret.push_back( XE::GraphicsContextType::METAL );
#elif PLATFORM_OS & (OS_IOS)
	ret.push_back( XE::GraphicsContextType::METAL );
#elif PLATFORM_OS & (OS_ANDROID)
	ret.push_back( XE::GraphicsContextType::VULKAN );
#elif PLATFORM_OS & (OS_LINUX)
	ret.push_back( XE::GraphicsContextType::VULKAN );
#endif

	ret.push_back( XE::GraphicsContextType::SOFTWARE );
	ret.push_back( XE::GraphicsContextType::NIL );

	return ret;
}

void XE::RHI::Init( const XE::InitDesc & val )
{
	auto type = val.Type;
	auto contexts = GetSupportedContext();

	while( _p->_Context == nullptr )
	{
		switch( type )
		{
		case XE::GraphicsContextType::METAL:
			_p->_Context = XE::CreateRendererContextMetal();
			break;
		case XE::GraphicsContextType::D3D12:
			_p->_Context = XE::CreateRendererContextD3D12();
			break;
		case XE::GraphicsContextType::HTML5:
			_p->_Context = XE::CreateRendererContextHTML5();
			break;
		case XE::GraphicsContextType::VULKAN:
			_p->_Context = XE::CreateRendererContextVulkan();
			break;
		case XE::GraphicsContextType::SOFTWARE:
			_p->_Context = XE::CreateRendererContextSoftware();
			break;
		case XE::GraphicsContextType::NIL:
			_p->_Context = XE::CreateRendererContextNull();
			break;
		default:
			break;
		}

		if( _p->_Context == nullptr )
		{
			type = contexts.front();
			contexts.pop_front();
		}
	}

	XE_ASSERT( _p->_Context == nullptr );

	_p->_Context->Init( val );
}

void XE::RHI::Shutdown()
{
	if( _p->_Context )
	{
		_p->_Context->Shutdown();

		delete _p->_Context;

		_p->_Context = nullptr;
	}
}

XE::Encoder * XE::RHI::Begin()
{
	return _p->_Context->Begin();
}

void XE::RHI::End( XE::Encoder * val )
{
	_p->_Context->End( val );
}

void XE::RHI::Present()
{
	_p->_Context->Present();
}

XE::RefHandle< XE::ViewHandle > XE::RHI::CreateView( const XE::ViewDesc & desc )
{
	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::ProgramHandle > XE::RHI::CreateProgram( const XE::ProgramDesc & desc )
{
	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::FrameBufferHandle > XE::RHI::CreateFrameBuffer( const XE::FrameBufferDesc & desc )
{
	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::VertexLayoutHandle > XE::RHI::CreateVertexLayout( const XE::VertexLayoutDesc & desc )
{
	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::OcclusionQueryHandle > XE::RHI::CreateOcclusionQuery( const OcclusionQueryDesc & desc )
{
	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::ShaderHandle > XE::RHI::CreateShader( const XE::ShaderDesc & desc, XE::MemoryView data )
{
	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::TextureHandle > XE::RHI::CreateTexture( const XE::TextureDesc & desc, XE::MemoryView data )
{
	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::IndexBufferHandle > XE::RHI::CreateIndexBuffer( const XE::IndexBufferDesc & desc, XE::MemoryView data )
{
	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::VertexBufferHandle > XE::RHI::CreateVertexBuffer( const XE::VertexBufferDesc & desc, XE::MemoryView data )
{
	return { _p->_Context->Create( desc, data ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::DynamicIndexBufferHandle > XE::RHI::CreateDynamicIndexBuffer( const XE::IndexBufferDesc & desc )
{
	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

XE::RefHandle< XE::DynamicVertexBufferHandle > XE::RHI::CreateDynamicVertexBuffer( const XE::VertexBufferDesc & desc )
{
	return { _p->_Context->Create( desc ), [this]( auto val ) { _p->_Context->Inc( val ); }, [this]( auto val ) { _p->_Context->Dec( val ); } };
}

const XE::ViewDesc & XE::RHI::GetDesc( XE::ViewHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::ShaderDesc & XE::RHI::GetDesc( XE::ShaderHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::ProgramDesc & XE::RHI::GetDesc( XE::ProgramHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::TextureDesc & XE::RHI::GetDesc( XE::TextureHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::FrameBufferDesc & XE::RHI::GetDesc( XE::FrameBufferHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::IndexBufferDesc & XE::RHI::GetDesc( XE::IndexBufferHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::VertexLayoutDesc & XE::RHI::GetDesc( XE::VertexLayoutHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::VertexBufferDesc & XE::RHI::GetDesc( XE::VertexBufferHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::OcclusionQueryDesc & XE::RHI::GetDesc( XE::OcclusionQueryHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::IndexBufferDesc & XE::RHI::GetDesc( XE::DynamicIndexBufferHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

const XE::VertexBufferDesc & XE::RHI::GetDesc( XE::DynamicVertexBufferHandle handle )
{
	return _p->_Context->GetDesc( handle );
}

void XE::RHI::UpdateTexture( const XE::UpdateTextureDesc & desc, XE::MemoryView data )
{
	return _p->_Context->Update( desc, data );
}

void XE::RHI::UpdateDynamicIndexBuffer( XE::DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	_p->_Context->Update( handle, start, mem );
}

void XE::RHI::UpdateDynamicVertexBuffer( XE::DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	_p->_Context->Update( handle, start, mem );
}

XE::Array< XE::UniformDesc > XE::RHI::GetShaderUniforms( XE::ShaderHandle handle )
{
	return _p->_Context->GetShaderUniforms( handle );
}

void XE::RHI::ReadTexture( XE::TextureHandle handle, XE::uint8 * data, XE::uint8 mip /*= 0 */ )
{
	return _p->_Context->ReadTexture( handle, data, mip );
}

XE::TextureHandle XE::RHI::GetTexture( XE::FrameBufferHandle handle, XE::uint8 attachment /*= 0 */ )
{
	return _p->_Context->GetTexture( handle, attachment );
}

std::optional< XE::uint32 > XE::RHI::GetOcclusionQueryValue( XE::OcclusionQueryHandle handle )
{
	return _p->_Context->GetOcclusionQueryValue( handle );
}

void XE::RHI::SetViewName( XE::ViewHandle handle, const XE::String & name )
{
	_p->_Context->SetViewName( handle, name );
}

void XE::RHI::SetViewRect( XE::ViewHandle handle, const XE::Rectf & rect )
{
	_p->_Context->SetViewRect( handle, rect );
}

void XE::RHI::SetViewScissor( XE::ViewHandle handle, const XE::Rectf & scissor )
{
	_p->_Context->SetViewScissor( handle, scissor );
}

void XE::RHI::SetViewClear( const XE::ClearDesc & desc )
{
	_p->_Context->SetViewClear( desc );
}

void XE::RHI::SetViewMode( XE::ViewHandle handle, XE::ViewMode mode /*= ViewMode::Default */ )
{
	_p->_Context->SetViewMode( handle, mode );
}

void XE::RHI::SetViewFrameBuffer( XE::ViewHandle handle, FrameBufferHandle frame )
{
	_p->_Context->SetViewFrameBuffer( handle, frame );
}

void XE::RHI::SetViewTransform( XE::ViewHandle handle, const XE::Mat4x4f & model, const XE::Mat4x4f & view, const XE::Mat4x4f & proj )
{
	_p->_Context->SetViewTransform( handle, model, view, proj );
}

void XE::RHI::ResetView( XE::ViewHandle handle, const XE::ViewDesc & desc )
{
	_p->_Context->ResetView( handle, desc );
}

void XE::RHI::RequestScreenShot( XE::FrameBufferHandle handle, const std::string & userdata, ScreenShotCallbackType callback )
{
	_p->_Context->RequestScreenShot( handle, userdata, callback );
}
