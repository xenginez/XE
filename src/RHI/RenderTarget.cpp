#include "RenderTarget.h"

#include "SwapChain.h"

USING_XE

BEG_META( RenderTarget )
END_META()

XE::RenderTarget::RenderTarget()
{

}

XE::RenderTarget::~RenderTarget()
{

}

bool XE::RenderTarget::GetWriteRed() const
{
	return _WriteRed;
}

void XE::RenderTarget::SetWriteRed( bool WriteRed )
{
	_WriteRed = WriteRed;
}

bool XE::RenderTarget::GetWriteGreen() const
{
	return _WriteGreen;
}

XE::RenderTargetHandle XE::RenderTarget::Handle() const
{
	return _Handle;
}

void XE::RenderTarget::SetWriteGreen( bool val )
{
	_WriteGreen = val;
}

bool XE::RenderTarget::GetWriteBlue() const
{
	return _WriteBlue;
}

void XE::RenderTarget::SetWriteBlue( bool val )
{
	_WriteBlue = val;
}

bool XE::RenderTarget::GetWriteAlpha() const
{
	return _WriteAlpha;
}

void XE::RenderTarget::SetWriteAlpha( bool val )
{
	_WriteAlpha = val;
}

bool XE::RenderTarget::GetBlendEnabled() const
{
	return _BlendEnabled;
}

void XE::RenderTarget::SetBlendEnabled( bool val )
{
	_BlendEnabled = val;
}

XE::BlendFactor XE::RenderTarget::GetSrcRgbFunc() const
{
	return _SrcRgbFunc;
}

void XE::RenderTarget::SetSrcRgbFunc( const XE::BlendFactor & val )
{
	_SrcRgbFunc = val;
}

XE::BlendFactor XE::RenderTarget::GetSrcAlphaFunc() const
{
	return _SrcAlphaFunc;
}

void XE::RenderTarget::SetSrcAlphaFunc( const XE::BlendFactor & val )
{
	_SrcAlphaFunc = val;
}

XE::BlendFactor XE::RenderTarget::GetDstRgbFunc() const
{
	return _DstRgbFunc;
}

void XE::RenderTarget::SetDstRgbFunc( const XE::BlendFactor & val )
{
	_DstRgbFunc = val;
}

XE::BlendFactor XE::RenderTarget::GetDstAlphaFunc() const
{
	return _DstAlphaFunc;
}

void XE::RenderTarget::SetDstAlphaFunc( const XE::BlendFactor & val )
{
	_DstAlphaFunc = val;
}

XE::BlendOperation XE::RenderTarget::GetRgbBlendOp() const
{
	return _RgbBlendOp;
}

void XE::RenderTarget::SetRgbBlendOp( const BlendOperation & val )
{
	_RgbBlendOp = val;
}

XE::BlendOperation XE::RenderTarget::GetAlphaBlendOp() const
{
	return _AlphaBlendOp;
}

void XE::RenderTarget::SetAlphaBlendOp( const BlendOperation & val )
{
	_AlphaBlendOp = val;
}

BEG_META( RenderWindow )
END_META()

XE::RenderWindow::RenderWindow()
{
	_Handle = Platform::ConstructWindow( _Title, static_cast< XE::uint32 >( _Rect.x ), static_cast< XE::uint32 >( _Rect.y ), static_cast< XE::uint32 >( _Rect.width ), static_cast< XE::uint32 >( _Rect.height ) );
}

XE::RenderWindow::~RenderWindow()
{
	_SwapChain = nullptr;

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

XE::SwapChainPtr XE::RenderWindow::GetSwapChain() const
{
	return _SwapChain;
}

BEG_META( RenderTexture2D )
END_META()

XE::RenderTexture2D::RenderTexture2D()
{

}

XE::RenderTexture2D::~RenderTexture2D()
{

}
