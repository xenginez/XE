#include "RenderService.h"

#include <Graphics/Graphics.h>

#include <bgfx/bgfx.h>

USING_XE

BEG_META( RenderService )
END_META()

struct XE::RenderService::Private
{
	SkyBoxPtr _Sky;
	Array<LightPtr> _Lights;
	Array<XE::CameraPtr> _Cameras;
	Array<XE::RenderablePtr> _Renderables;
	WindowHandle _WindowHandle;
	FrameBufferHandle _FBHandle;
};

XE::RenderService::RenderService()
	:_p( new Private )
{

}

XE::RenderService::~RenderService()
{
	delete _p;
}

void XE::RenderService::Prepare()
{
	bgfx::Init _init;
	
	_init.type = bgfx::RendererType::Enum::Direct3D11;
	_init.vendorId = BGFX_PCI_ID_NONE;
	_init.resolution.width = 1024;
	_init.resolution.height = 768;
	_init.resolution.reset = BGFX_RESET_VSYNC;
	
	bgfx::init( _init );

	Gfx::setDebug( BGFX_DEBUG_NONE );

	_p->_WindowHandle = Platform::CreateWindow( "XE", 0, 0, 1024, 768 );

	_p->_FBHandle = Gfx::createFrameBuffer( _p->_WindowHandle, 1024, 768, TextureFormat::RGBA8, TextureFormat::D24S8 );

	Gfx::setViewRect( 0, 0, 0, 1024, 768 );
	Gfx::setViewFrameBuffer( 0, _p->_FBHandle );
	Gfx::setViewClear( 0, ClearFlags::COLOR_DEPTH, 0x603060ff, 1.0f, 0 );
}

bool XE::RenderService::Startup()
{
	Gfx::touch( 0 );

	return false;
}

void XE::RenderService::Update()
{
// 	Gfx::setViewRect( 0, 0, 0, 1024, 768 );
// 	Gfx::setViewFrameBuffer( 0, _p->_FBHandle );
// 	Gfx::setViewClear( 0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0 );


	for( auto & renderable : _p->_Renderables )
	{
		renderable->Render();
	}
	
	Gfx::frame();
}

void XE::RenderService::Clearup()
{
	_p->_Lights.clear();
	_p->_Cameras.clear();
	_p->_Renderables.clear();

	Gfx::destroy( _p->_FBHandle );

	Platform::DestroyWindow( _p->_WindowHandle );

	bgfx::shutdown();
}

void XE::RenderService::RegisterLight( const LightPtr & val )
{
	auto it = std::find( _p->_Lights.begin(), _p->_Lights.end(), val );
	if( it != _p->_Lights.end() )
	{
		_p->_Lights.push_back( val );
	}
}

void XE::RenderService::UnregisterLight( const LightPtr & val )
{
	auto it = std::find( _p->_Lights.begin(), _p->_Lights.end(), val );
	if( it != _p->_Lights.end() )
	{
		_p->_Lights.erase( it );
	}
}

void XE::RenderService::RegisterCamera( const CameraPtr & val )
{
	auto it = std::find( _p->_Cameras.begin(), _p->_Cameras.end(), val );
	if( it != _p->_Cameras.end() )
	{
		_p->_Cameras.push_back( val );
	}
}

void XE::RenderService::UnregisterCamera( const CameraPtr & val )
{
	auto it = std::find( _p->_Cameras.begin(), _p->_Cameras.end(), val );
	if( it != _p->_Cameras.end() )
	{
		_p->_Cameras.erase( it );
	}
}

void XE::RenderService::RegisterRenderable( const RenderablePtr & val )
{
	auto it = std::find( _p->_Renderables.begin(), _p->_Renderables.end(), val );
	if( it != _p->_Renderables.end() )
	{
		_p->_Renderables.push_back( val );
	}
}

void XE::RenderService::UnregisterRenderable( const RenderablePtr & val )
{
	auto it = std::find( _p->_Renderables.begin(), _p->_Renderables.end(), val );
	if( it != _p->_Renderables.end() )
	{
		_p->_Renderables.erase( it );
	}
}

const XE::Array<XE::LightPtr> & XE::RenderService::GetLights() const
{
	return _p->_Lights;
}

const XE::Array<XE::CameraPtr> & XE::RenderService::GetCameras() const
{
	return _p->_Cameras;
}

const XE::Array<XE::RenderablePtr> & XE::RenderService::GetRenderables() const
{
	return _p->_Renderables;
}
