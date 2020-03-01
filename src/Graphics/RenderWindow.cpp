#include "RenderWindow.h"

#include "Gfx.h"

USING_XE

BEG_META( RenderWindow )
END_META()

XE::RenderWindow::RenderWindow()
	:_Size( 1024, 768 ), _Position( 0, 0 ), _Title( "" ), _Show( false ), _Minimize( false ), _Maximize( false ), _MouseLock( false ), _Fullscreen( false ), _Dirty( true )
{

}

XE::RenderWindow::~RenderWindow()
{

}

void XE::RenderWindow::Show()
{
	_Show = true;
	_Minimize = false;
	_Maximize = false;
	_Fullscreen = false;

	UpdateWindow();
}

void XE::RenderWindow::Hide()
{
	_Show = false;

	UpdateWindow();
}

void XE::RenderWindow::Minimize()
{
	_Show = true;
	_Minimize = true;
	_Maximize = false;
	_Fullscreen = false;

	UpdateWindow();
}

void XE::RenderWindow::Maximize()
{
	_Show = true;
	_Maximize = true;
	_Minimize = false;
	_Fullscreen = false;

	UpdateWindow();
}

void XE::RenderWindow::Fullscreen()
{
	_Show = true;
	_Maximize = false;
	_Minimize = false;
	_Fullscreen = true;

	UpdateWindow();
}

void XE::RenderWindow::Close()
{
	if( _WindowHandle )
	{
		Platform::DestroyWindow( _WindowHandle );
		_WindowHandle = WindowHandle::Invalid;
	}

	_Show = false;
	_Minimize = false;
	_Maximize = false;
	_Fullscreen = false;
}

void XE::RenderWindow::MouseLock()
{
	XE_ASSERT( _WindowHandle );

	_MouseLock = true;

	Platform::HideMouse();
}

void XE::RenderWindow::MouseUnlock()
{
	XE_ASSERT( _WindowHandle );

	_MouseLock = false;

	Platform::ShowMouse();
}

bool XE::RenderWindow::IsShow()
{
	return _Show;
}

bool XE::RenderWindow::IsNormal()
{
	return _Show && !_Minimize && !_Maximize && !_Fullscreen;
}

bool XE::RenderWindow::IsMinimized()
{
	return _Minimize;
}

bool XE::RenderWindow::IsMaximized()
{
	return _Maximize;
}

bool XE::RenderWindow::IsFullscreen()
{
	return _Fullscreen;
}

bool XE::RenderWindow::IsMouseLock()
{
	return _MouseLock;
}

const XE::String & XE::RenderWindow::GetTitle() const
{
	return _Title;
}

void XE::RenderWindow::SetTitle( const XE::String & val )
{
	_Title = val;
}

const XE::Vec2 & XE::RenderWindow::GetSize() const
{
	return _Size;
}

void XE::RenderWindow::SetSize( const XE::Vec2 & val )
{
	_Size = val;
	_Dirty = true;
}

const XE::Vec2 & XE::RenderWindow::GetPosition() const
{
	return _Position;
}

void XE::RenderWindow::SetPosition( const XE::Vec2 & val )
{
	_Position = val;
	_Dirty = true;
}

XE::WindowHandle XE::RenderWindow::GetWindowHandle() const
{
	return _WindowHandle;
}

void XE::RenderWindow::SetWindowHandle( XE::WindowHandle val )
{
	Close();

	_WindowHandle = val;

	Show();
}

void XE::RenderWindow::UpdateWindow()
{
	if( !_WindowHandle )
	{
		_WindowHandle = Platform::CreateWindow( _Title, _Position.x, _Position.y, _Size.x, _Size.y );
	}

	if( !_Show )
	{
		Platform::HideWindow( _WindowHandle );
	}
	else
	{
		if( _Dirty )
		{
			Platform::SetWindowTitle( _WindowHandle, _Title );
			Platform::SetWindowRect( _WindowHandle, _Position.x, _Position.y, _Size.x, _Size.y, false );
			_Dirty = false;
		}

		if( _Fullscreen )
		{
			Platform::FullscreenWindow( _WindowHandle );
		}
		else if( _Minimize )
		{
			Platform::MinimizeWindow( _WindowHandle );
		}
		else if( _Maximize )
		{
			Platform::MaximizeWindow( _WindowHandle );
		}
		else
		{
			Platform::ShowWindow( _WindowHandle );
		}
	}
}
