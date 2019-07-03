#include "RenderWindow.h"

#include "Device.h"

XE::RenderWindow::RenderWindow( DevicePtr val )
	:_Device( val )
{
	_Handle = Platform::ConstructWindow( _Title, static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ) );

	_Device->CreateSwapChain( _Handle );
}

XE::RenderWindow::~RenderWindow()
{
	_Device->DestroySwapChain( _Handle );

	Platform::DestroyWindow( _Handle.GetValue() );
}

void XE::RenderWindow::Show()
{
	_Show = true;
	_Fullscreen = false;

	Platform::ShowWindow( _Handle.GetValue() );
}

void XE::RenderWindow::Hide()
{
	_Show = false;
	_Fullscreen = false;

	Platform::HideWindow( _Handle.GetValue() );
}

void XE::RenderWindow::Focus()
{
	Platform::GrabWindow( _Handle.GetValue() );
}

void XE::RenderWindow::Minimize()
{
	_Show = false;
	_Fullscreen = false;

	Platform::MinimizeWindow( _Handle.GetValue() );
}

void XE::RenderWindow::Maximize()
{
	_Show = true;
	_Fullscreen = false;

	Platform::MaximizeWindow( _Handle.GetValue() );
}

void XE::RenderWindow::Fullscreen()
{
	_Fullscreen = true;

	Platform::FullscreenWindow( _Handle.GetValue() );
}

bool XE::RenderWindow::IsShow() const
{
	return _Show;
}

bool XE::RenderWindow::IsHide() const
{
	return !_Show;
}

bool XE::RenderWindow::IsFocus() const
{
	return Platform::GetWindowFocus( _Handle.GetValue() );
}

bool XE::RenderWindow::IsFullscreen() const
{
	return _Fullscreen;
}

XE::uint32 XE::RenderWindow::GetPosX() const
{
	return static_cast< XE::uint32 >( _Rect.x );
}

void XE::RenderWindow::SetPosX( XE::uint32 x )
{
	_Rect.x = static_cast< XE::real >( x );

	Platform::SetWindowRect( _Handle.GetValue(), static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ), false );
}

XE::uint32 XE::RenderWindow::GetPosY() const
{
	return static_cast< XE::uint32 >( _Rect.y );
}

void XE::RenderWindow::SetPosY( XE::uint32 y )
{
	_Rect.y = static_cast< XE::real >( y );

	Platform::SetWindowRect( _Handle.GetValue(), static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ), false );
}

XE::uint32 XE::RenderWindow::GetWidth() const
{
	return static_cast< XE::uint32 >( _Rect.width );
}

void XE::RenderWindow::SetWidth( XE::uint32 w )
{
	_Rect.width = static_cast< XE::real >( w );

	Platform::SetWindowRect( _Handle.GetValue(), static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ), false );
}

XE::uint32 XE::RenderWindow::GetHeight() const
{
	return static_cast< XE::uint32 >( _Rect.height );
}

void XE::RenderWindow::SetHeight( XE::uint32 h )
{
	_Rect.height = static_cast< XE::real >( h );

	Platform::SetWindowRect( _Handle.GetValue(), static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ), false );
}

XE::Vec2 XE::RenderWindow::GetSize() const
{
	return _Rect.GetSize();
}

void XE::RenderWindow::SetSize( const Vec2 & val )
{
	_Rect.width = val.x;
	_Rect.height = val.y;

	Platform::SetWindowRect( _Handle.GetValue(), static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ), false );
}

XE::Vec2 XE::RenderWindow::GetPosition() const
{
	return { _Rect.x, _Rect.y };
}

void XE::RenderWindow::SetPosition( const Vec2 & val )
{
	_Rect.x = val.x;
	_Rect.y = val.y;

	Platform::SetWindowRect( _Handle.GetValue(), static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ), false );
}

const XE::Rect & XE::RenderWindow::GetRect() const
{
	return _Rect;
}

void XE::RenderWindow::SetRect( const Rect & val )
{
	_Rect = val;

	Platform::SetWindowRect( _Handle.GetValue(), static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ), false );
}

const XE::String & XE::RenderWindow::GetTitle() const
{
	return _Title;
}

void XE::RenderWindow::SetTitle( const String & val )
{
	_Title = val;
	Platform::SetWindowTitle( _Handle.GetValue(), _Title );
}

XE::FrameBufferPtr XE::RenderWindow::GetBackFrameBuffer() const
{
	return _Device->GetBackFrameBuffer( _Handle );
}

XE::FrameBufferPtr XE::RenderWindow::GetFrontFrameBuffer() const
{
	return _Device->GetFrontFrameBuffer( _Handle );
}

XE::FrameBufferPtr XE::RenderWindow::GetCurrentFrameBuffer() const
{
	return _Device->GetCurrentFrameBuffer( _Handle );
}
