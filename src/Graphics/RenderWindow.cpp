#include "RenderWindow.h"

#include "GFX.h"
#include "RenderPass.h"
#include "FrameBuffer.h"

USING_XE

BEGIN_META(RenderWindow)
END_META()

XE::RenderWindow::RenderWindow()
{
	PrepareSurface();
}

XE::RenderWindow::RenderWindow( const String &title, XE::uint32 flags /*= 0*/ )
		:Window(title, 0, 0, 1024, 768, flags)
{
	PrepareSurface();
}

XE::RenderWindow::~RenderWindow()
{
	DestorySurface();
}

XE::FrameBufferPtr XE::RenderWindow::GetSurface() const
{
	return _Surface;
}

XE::ViewHandle XE::RenderWindow::GetPresentPass() const
{
	RenderPass pass("present_to_window_pass");
	pass.Bind(_Surface);
	pass.Clear();
	
	return pass.GetHandle();
}

void XE::RenderWindow::PrepareSurface()
{
	_Surface = XE::make_shared < FrameBuffer >(reinterpret_cast<void *>( GetHandle()), GetWidth(), GetHeight());
}

void XE::RenderWindow::DestorySurface()
{
	if( _Surface )
	{
		_Surface = nullptr;
		
		GFX::Flush();
	}
}

void XE::RenderWindow::OnResize()
{
	PrepareSurface();
}