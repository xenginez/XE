#include "RenderWindow.h"

USING_XE

BEGIN_META(RenderWindow)
END_META()

XE::RenderWindow::RenderWindow()
		:_Flag(0)
{
	
}

void XE::RenderWindow::Grab()
{
	if( !IsGrab())
	{
		_Flag |= uint32(WindowFlag::GRAB);
		Restore();
	}
}

void XE::RenderWindow::Show()
{
	if( !IsShow())
	{
		_Flag |= uint32(WindowFlag::SHOW);
		Restore();
	}
}

void XE::RenderWindow::Hide()
{
	if( !IsHide())
	{
		_Flag &= ~uint32(WindowFlag::SHOW);
		Restore();
	}
}

void XE::RenderWindow::Minimize()
{
	if( !IsMinimize())
	{
		_Flag |= uint32(WindowFlag::MINIMIZE);
		Restore();
	}
}

void XE::RenderWindow::Maximize()
{
	if( !IsMaximize())
	{
		_Flag &= ~uint32(WindowFlag::MINIMIZE);
		Restore();
	}
}

void XE::RenderWindow::Fullsrceen()
{
	if( !IsFullsrceen())
	{
		_Flag |= uint32(WindowFlag::FULLSRCEEN);
		Restore();
	}
}

void XE::RenderWindow::Foreground()
{
	if( !IsForeground())
	{
		_Flag |= uint32(WindowFlag::FOREGROUND);
		Restore();
	}
}

void XE::RenderWindow::ShowCursor()
{
	if( !IsShowCursor())
	{
		_Flag |= uint32(WindowFlag::SHOWCURSOR);
		Restore();
	}
}

void XE::RenderWindow::HideCursor()
{
	if( !IsGrab())
	{
		_Flag &= ~uint32(WindowFlag::SHOWCURSOR);
		Restore();
	}
}

bool XE::RenderWindow::IsGrab()
{
	return _Flag & uint32(WindowFlag::GRAB);
}

bool XE::RenderWindow::IsShow()
{
	return _Flag & uint32(WindowFlag::SHOW);
}

bool XE::RenderWindow::IsHide()
{
	return !( _Flag & uint32(WindowFlag::SHOW));
}

bool XE::RenderWindow::IsMinimize()
{
	return _Flag & uint32(WindowFlag::MINIMIZE);
}

bool XE::RenderWindow::IsMaximize()
{
	return !( _Flag & uint32(WindowFlag::MINIMIZE));
}

bool XE::RenderWindow::IsFullsrceen()
{
	return _Flag & uint32(WindowFlag::FULLSRCEEN);
}

bool XE::RenderWindow::IsForeground()
{
	return _Flag & uint32(WindowFlag::FOREGROUND);
}

bool XE::RenderWindow::IsShowCursor()
{
	return _Flag & uint32(WindowFlag::SHOWCURSOR);
}

bool XE::RenderWindow::IsHideCursor()
{
	return !( _Flag & uint32(WindowFlag::SHOWCURSOR));
}

XE::uint32 XE::RenderWindow::GetFlag() const
{
	return _Flag;
}

void XE::RenderWindow::SetFlag( XE::uint32 val )
{
	_Flag = val;
}

const XE::String &XE::RenderWindow::GetIcon() const
{
	return _Icon;
}

void XE::RenderWindow::SetIcon( const XE::String &val )
{
	_Icon = val;
}

const XE::String &XE::RenderWindow::GetCursor() const
{
	return _Cursor;
}

void XE::RenderWindow::SetCursor( const XE::String &val )
{
	_Cursor = val;
}

const XE::String &XE::RenderWindow::GetTitle() const
{
	return _Title;
}

void XE::RenderWindow::SetTitle( const XE::String &val )
{
	_Title = val;
}

const XE::Vec2 &XE::RenderWindow::GetSize() const
{
	return _Size;
}

void XE::RenderWindow::SetSize( const XE::Vec2 &val )
{
	_Size = val;
}

const XE::Vec2 &XE::RenderWindow::GetPosition() const
{
	return _Position;
}

void XE::RenderWindow::SetPosition( const XE::Vec2 &val )
{
	_Position = val;
}

XE::RenderWindowHandle XE::RenderWindow::GetHandle() const
{
	return _Handle;
}

void XE::RenderWindow::SetHandle( const XE::RenderWindowHandle &val )
{
	_Handle = val;
}

XE::RenderWindowPtr XE::RenderWindow::FromHandle( const XE::RenderWindowHandle &val )
{
	auto p = XE::make_shared < RenderWindow >();
	
	p->_Handle = val;
	
	p->FromNatvieHandle();
	
	return p;
}
