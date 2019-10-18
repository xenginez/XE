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
	_p->_MainWindow->Show();

	Gfx::setViewRect( 0, 0, 0, 800, 600 );
	Gfx::setViewFrameBuffer( 0, _p->_MainWindow->GetFrameBufferHandle() );
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
