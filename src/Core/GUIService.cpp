#include "GUIService.h"

USING_XE

BEG_META( GUIService )
END_META()

struct XE::GUIService::Private
{
	RenderWindowPtr _MainWindow;
};

XE::GUIService::GUIService()
	:_p( new Private )
{

}

XE::GUIService::~GUIService()
{
	delete _p;
}

void XE::GUIService::Prepare()
{
	_p->_MainWindow = XE::make_shared<RenderWindow>();


	if( GetFramework()->GetConfigService()->GetBool( "GUI/Window/Fullscreen", false ) )
	{
		_p->_MainWindow->Fullscreen();
	}
	else
	{
		XE::float32 width = GetFramework()->GetConfigService()->GetFloat32( "GUI/Window/Width", 1024 );
		XE::float32 height = GetFramework()->GetConfigService()->GetFloat32( "GUI/Window/Height", 768 );
		_p->_MainWindow->SetSize( { width, height } );

		XE::uint32 desktop_w, desktop_h;
		Platform::GetDesktopSize( desktop_w, desktop_h );

		_p->_MainWindow->SetPosition( { desktop_w / 2 - width / 2, desktop_h / 2 - height / 2 } );

		_p->_MainWindow->Show();
	}

	XE::uint16 r_width = GetFramework()->GetConfigService()->GetUInt16( "Render/Resolution/Width", 1024 );
	XE::uint16 r_height = GetFramework()->GetConfigService()->GetUInt16( "Render/Resolution/Height", 768 );
	Gfx::setViewFrameBuffer( 0, _p->_MainWindow->GetFrameBufferHandle() );
	Gfx::setViewRect( 0, 0, 0, r_width, r_height );
	Gfx::setViewClear( 0, ClearFlags::COLOR_DEPTH, 0x603060ff, 1.0f, 0 );
}

bool XE::GUIService::Startup()
{
	return true;
}

void XE::GUIService::Update()
{

}

void XE::GUIService::Clearup()
{
	_p->_MainWindow->Close();
}
