#include "RenderService.h"

USING_XE

BEG_META( RenderService )
END_META()

struct XE::RenderService::Private
{
	RenderWindowPtr _MainWindow;

	Array<LightPtr> _Lights;
	Array<XE::CameraPtr> _Cameras;
	Array<XE::RenderablePtr> _Renderables;
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
	_p->_MainWindow = XE::MakeShared<RenderWindow>();


	if( GetFramework()->GetConfigService()->GetBool( "Window/Fullscreen", false ) )
	{
		_p->_MainWindow->Fullscreen();
	}
	else
	{
		XE::float32 width = GetFramework()->GetConfigService()->GetFloat32( "Window/Width", 1024 );
		XE::float32 height = GetFramework()->GetConfigService()->GetFloat32( "Window/Height", 768 );
		_p->_MainWindow->SetSize( { width, height } );

		XE::uint32 desktop_w, desktop_h;
		Platform::GetDesktopSize( desktop_w, desktop_h );

		_p->_MainWindow->SetPosition( { desktop_w / 2 - width / 2, desktop_h / 2 - height / 2 } );

		_p->_MainWindow->Show();
	}
}

bool XE::RenderService::Startup()
{
	GfxDesc desc = { 0 };

	desc.window_handle = _p->_MainWindow->GetWindowHandle();
	desc.window_width = _p->_MainWindow->GetSize().x;
	desc.window_height = _p->_MainWindow->GetSize().y;

	Gfx::Setup( &desc );

	return true;
}

void XE::RenderService::Update()
{
	for (auto & camera : _p->_Cameras)
	{

	}

	Gfx::Commit();

	Gfx::Present();
}

void XE::RenderService::Clearup()
{
	_p->_Lights.clear();
	_p->_Cameras.clear();
	_p->_Renderables.clear();

	Gfx::ShutDown();
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
