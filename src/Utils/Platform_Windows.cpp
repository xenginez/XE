#include "Platform.h"
#if PLATFORM_OS == OS_WINDOWS

#include <Windows.h>

USING_XE

IMPLEMENT_META( WindowHandle );

std::function<bool( WindowHandle, XE::WindowEvent )> G_Callback;

LRESULT WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( G_Callback != nullptr )
	{
		switch( message )
		{
		case WM_CREATE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::CREATE ); break;
		case WM_DESTROY:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::DESTROY ); break;
		case WM_MOVE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MOVE ); break;
		case WM_SIZE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SIZE ); break;
		case WM_ACTIVATE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::ACTIVATE ); break;
		case WM_SETFOCUS:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SETFOCUS ); break;
		case WM_KILLFOCUS:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::KILLFOCUS ); break;
		case WM_ENABLE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::ENABLE ); break;
		case WM_PAINT:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::PAINT ); break;
		case WM_CLOSE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::CLOSE ); break;
		case WM_QUERYENDSESSION:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::QUERYENDSESSION ); break;
		case WM_QUIT:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::QUIT ); break;
		case WM_SHOWWINDOW:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SHOWWINDOW ); break;
		case WM_ACTIVATEAPP:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::ACTIVATEAPP ); break;
		case WM_SETCURSOR:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SETCURSOR ); break;
		case WM_MOUSEACTIVATE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MOUSEACTIVATE ); break;
		case WM_GETMINMAXINFO:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::GETMINMAXINFO ); break;
		case WM_NEXTDLGCTL:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::NEXTDLGCTL ); break;
		case WM_COMPACTING:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::COMPACTING ); break;
		case WM_WINDOWPOSCHANGING:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::WINDOWPOSCHANGING ); break;
		case WM_WINDOWPOSCHANGED:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::WINDOWPOSCHANGED ); break;
		case WM_DISPLAYCHANGE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::DISPLAYCHANGE ); break;
		case WM_GETICON:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::GETICON ); break;
		case WM_SETICON:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SETICON ); break;
		case WM_KEYDOWN:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::KEYDOWN ); break;
		case WM_KEYUP:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::KEYUP ); break;
		case WM_CHAR:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::CHAR ); break;
		case WM_DEADCHAR:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::DEADCHAR ); break;
		case WM_SYSKEYDOWN:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SYSKEYDOWN ); break;
		case WM_SYSKEYUP:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SYSKEYUP ); break;
		case WM_SYSCHAR:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SYSCHAR ); break;
		case WM_SYSDEADCHAR:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SYSDEADCHAR ); break;
		case WM_MOUSEMOVE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MOUSEMOVE ); break;
		case WM_LBUTTONDOWN:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::LBUTTONDOWN ); break;
		case WM_LBUTTONUP:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::LBUTTONUP ); break;
		case WM_LBUTTONDBLCLK:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::LBUTTONDBLCLK ); break;
		case WM_RBUTTONDOWN:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::RBUTTONDOWN ); break;
		case WM_RBUTTONUP:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::RBUTTONUP ); break;
		case WM_RBUTTONDBLCLK:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::RBUTTONDBLCLK ); break;
		case WM_MBUTTONDOWN:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MBUTTONDOWN ); break;
		case WM_MBUTTONUP:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MBUTTONUP ); break;
		case WM_MBUTTONDBLCLK:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MBUTTONDBLCLK ); break;
		case WM_MOUSEWHEEL:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MOUSEWHEEL ); break;
		case WM_SIZING:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::SIZING ); break;
		case WM_CAPTURECHANGED:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::CAPTURECHANGED ); break;
		case WM_MOVING:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::MOVING ); break;
		case WM_POWERBROADCAST:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::POWERBROADCAST ); break;
		case WM_DEVICECHANGE:G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), XE::WindowEvent::DEVICECHANGE ); break;
		default:
			break;
		}
	}

	return DefWindowProc( hWnd, message, wParam, lParam );
}

XE::Language XE::Platform::GetDefaultLanguage()
{
	LANGID id = GetSystemDefaultLangID();

	switch( id )
	{
	case 0x0401:
	case 0x0801:
	case 0x0c01:
	case 0x1001:
	case 0x1401:
	case 0x1801:
	case 0x1c01:
	case 0x2001:
	case 0x2401:
	case 0x2801:
	case 0x2c01:
	case 0x3001:
	case 0x3401:
	case 0x3801:
	case 0x3c01:
	case 0x4001:
		return XE::Language::ARABIC;
	case 0x0402:
		return XE::Language::BULGARIAN;
	case 0x0403:
		return XE::Language::CATALAN;
	case 0x0804:
		return XE::Language::CHINESESIMPLIFIED;
	case 0x0404:
	case 0x0c04:
	case 0x1004:
		return XE::Language::CHINESETRADITIONAL;
	case 0x0405:
		return XE::Language::CZECH;
	case 0x0406:
		return XE::Language::DANISH;
	case 0x0407:
	case 0x0807:
	case 0x0c07:
	case 0x1007:
	case 0x1407:
		return XE::Language::GERMAN;
	case 0x0408:
		return XE::Language::GREEK;
	case 0x0409:
	case 0x0809:
	case 0x0c09:
	case 0x1009:
	case 0x1409:
	case 0x1809:
	case 0x1c09:
	case 0x2009:
	case 0x2409:
	case 0x2809:
	case 0x2c09:
		return XE::Language::ENGLISH;
	case 0x040a:
		return XE::Language::SPANISH;
	case 0x080a:
	case 0x0c0a:
	case 0x100a:
	case 0x140a:
	case 0x180a:
	case 0x1c0a:
	case 0x200a:
	case 0x240a:
	case 0x280a:
	case 0x2c0a:
	case 0x300a:
	case 0x340a:
	case 0x380a:
	case 0x3c0a:
	case 0x400a:
	case 0x440a:
	case 0x480a:
	case 0x4c0a:
	case 0x500a:
		return XE::Language::SPANISH;
	case 0x040b:
	case 0x040c:
	case 0x080c:
	case 0x0c0c:
	case 0x100c:
	case 0x140c:
		return XE::Language::FINNISH;
	case 0x040d:
		return XE::Language::HEBREW;
	case 0x040e:
		return XE::Language::HUNGARIAN;
	case 0x040f:
		return XE::Language::ICELANDIC;
	case 0x0410:
	case 0x0810:
		return XE::Language::ITALIAN;
	case 0x0411:
		return XE::Language::JAPANESE;
	case 0x0412:
	case 0x0812:
		return XE::Language::KOREAN;
	case 0x0413:
	case 0x0813:
		return XE::Language::DUTCH;
	case 0x0414:
	case 0x0814:
		return XE::Language::NORWEGIAN;
	case 0x0415:
		return XE::Language::POLISH;
	case 0x0416:
	case 0x0816:
		return XE::Language::PORTUGUESE;
	case 0x0418:
		return XE::Language::ROMANIAN;
	case 0x0419:
		return XE::Language::RUSSIAN;
	case 0x041b:
		return XE::Language::SLOVAK;
	case 0x041d:
	case 0x081d:
		return XE::Language::SWEDISH;
	case 0x041e:
		return XE::Language::THAI;
	case 0x041f:
		return XE::Language::TURKISH;
	case 0x0421:
		return XE::Language::INDONESIAN;
	case 0x0422:
		return XE::Language::UKRAINIAN;
	case 0x0423:
		return XE::Language::BELARUSIAN;
	case 0x0424:
		return XE::Language::SLOVENIAN;
	case 0x0425:
		return XE::Language::ESTONIAN;
	case 0x0426:
		return XE::Language::LATVIAN;
	case 0x0427:
		return XE::Language::LITHUANIAN;
	case 0x042a:
		return XE::Language::VIETNAMESE;
	case 0x042d:
		return XE::Language::BASQUE;
	case 0x0436:
		return XE::Language::AFRIKAANS;
	default:
		return XE::Language::UNKNOWN;
		break;
	}
}

bool XE::Platform::RegisterWindowClass( const String & icon, std::function<bool( WindowHandle, XE::WindowEvent )> callback )
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof( wce );
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hInstance = GetModuleHandle( NULL );
	wce.hbrBackground = (HBRUSH )( COLOR_WINDOW + 1 );
	wce.hCursor = LoadCursor( NULL, IDC_ARROW );
	wce.hIcon = LoadIcon( wce.hInstance, icon.ToCString() );
	wce.hIconSm = LoadIcon( wce.hInstance, icon.ToCString() );
	wce.lpfnWndProc = WndProc;
	wce.lpszClassName = "XE";
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW;

	if( RegisterClassEx( &wce ) != 0 )
	{
		G_Callback = callback;
		return true;
	}

	return false;
}

void XE::Platform::UnregisterWindowClass()
{
	G_Callback = nullptr;
}

WindowHandle XE::Platform::ConstructWindow( const String & title, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h )
{
	HWND hwnd = ::CreateWindow( "XE", title.ToCString(), WS_OVERLAPPEDWINDOW, x, y, w, h, nullptr, nullptr, GetModuleHandle( NULL ), nullptr );

	if( hwnd )
	{
		::ShowWindow( hwnd, SW_SHOW );
		::UpdateWindow( hwnd );
	}

	return reinterpret_cast< XE::uint64 >( hwnd );
}

bool XE::Platform::DestroyWindow( WindowHandle handle )
{
	return ::DestroyWindow( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool Platform::GrabWindow( WindowHandle handle )
{
	return BringWindowToTop( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool XE::Platform::ShowWindow( WindowHandle handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle.GetValue() ), SW_SHOW ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool XE::Platform::HideWindow( WindowHandle handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle.GetValue() ), SW_HIDE ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool XE::Platform::MinimizeWindow( WindowHandle handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle.GetValue() ), SW_MINIMIZE ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool XE::Platform::MaximizeWindow( WindowHandle handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle.GetValue() ), SW_MAXIMIZE ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool XE::Platform::FullscreenWindow( WindowHandle handle )
{
	RECT desk_rect;
	HWND desk_handle;
	desk_handle = GetDesktopWindow();
	GetWindowRect( desk_handle, &desk_rect );
	SetWindowLong( reinterpret_cast< HWND >( handle.GetValue() ), GWL_STYLE, WS_BORDER );

	return SetWindowPos( reinterpret_cast< HWND >( handle.GetValue() ), HWND_TOPMOST, 0, 0, desk_rect.right, desk_rect.bottom, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool Platform::GetWindowFocus( WindowHandle handle )
{
	return GetFocus() == reinterpret_cast< HWND >( handle.GetValue() );
}

bool XE::Platform::SetWindowTitle( WindowHandle handle, const String & title )
{
	return SetWindowText( reinterpret_cast< HWND >( handle.GetValue() ), title.ToCString() );
}

bool XE::Platform::SetWindowRect( WindowHandle handle, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h, bool topmost )
{
	return ::SetWindowPos( reinterpret_cast< HWND >( handle.GetValue() ), topmost ? HWND_TOPMOST : HWND_NOTOPMOST, x, y, w, h, SWP_NOZORDER ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle.GetValue() ) ) != 0;
}

bool XE::Platform::ShowMouse()
{
	while( ShowCursor( true ) >= 0 );
	return true;
}

bool XE::Platform::HideMouse()
{
	while( ShowCursor( false ) < 0 );
	return true;
}

XE::ProcessHandle XE::Platform::ConstructProcess( const std::filesystem::path & app, const std::string & cmd, bool inherit, XE::uint32 flag )
{
	STARTUPINFO startup = {};
	PROCESS_INFORMATION * info = new PROCESS_INFORMATION();

	if( ::CreateProcess( app.string().c_str(), const_cast< char * >( cmd.c_str() ), nullptr, nullptr, inherit, flag, nullptr, nullptr, &startup, info ) )
	{
		return reinterpret_cast< XE::uint64 >( info );
	}

	return ProcessHandle::Invalid;
}

bool XE::Platform::DestroyProcess( ProcessHandle handle, XE::uint32 code )
{
	if( handle != ProcessHandle::Invalid )
	{
		PROCESS_INFORMATION * info = reinterpret_cast< PROCESS_INFORMATION * >( handle.GetValue() );
		if( info != nullptr )
		{
			::TerminateProcess( info->hProcess, code );
			::CloseHandle( info->hThread );
			return ::CloseHandle( info->hProcess );
		}
	}

	return false;
}

#endif
