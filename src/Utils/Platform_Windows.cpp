#include "Platform.h"
#if PLATFORM_OS == OS_WINDOWS

#include <Windows.h>

USING_XE

std::function<bool( XE::uint64, XE::uint64, XE::uint64, XE::uint64 )> G_Callback;

LRESULT WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( G_Callback != nullptr )
	{
		if( !G_Callback( reinterpret_cast< XE::uint64 >( hWnd ), message, wParam, lParam ) )
		{
			G_Callback = nullptr;
		}

		return 0;
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

bool XE::Platform::RegisterWindowClass( const String & icon, std::function<bool( XE::uint64, XE::uint64, XE::uint64, XE::uint64 )> callback )
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof( wce );
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hInstance = GetModuleHandle( NULL );
	wce.hbrBackground = (HBRUSH )( COLOR_WINDOW + 1 );
	wce.hCursor = LoadCursor( NULL, IDC_ARROW );
	wce.hIcon = LoadIcon( wce.hInstance, icon.ToCString() );
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

XE::uint64 XE::Platform::ConstructWindow( const String & title, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h )
{
	HWND hwnd = ::CreateWindow( "XE", title.ToCString(), WS_OVERLAPPEDWINDOW, x, y, w, h, nullptr, nullptr, GetModuleHandle( NULL ), nullptr );

	if( hwnd )
	{
		::ShowWindow( hwnd, SW_SHOW );
		::UpdateWindow( hwnd );
	}

	return reinterpret_cast< XE::uint64 >( hwnd );
}

bool XE::Platform::DestroyWindow( XE::uint64 handle )
{
	return ::DestroyWindow( reinterpret_cast< HWND >( handle ) ) != 0;
}

bool Platform::GrabWindow( XE::uint64 handle )
{
	return BringWindowToTop( reinterpret_cast< HWND >( handle ) ) != 0;
}

bool XE::Platform::ShowWindow( XE::uint64 handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle ), SW_SHOW ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle ) ) != 0;
}

bool XE::Platform::HideWindow( XE::uint64 handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle ), SW_HIDE ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle ) ) != 0;
}

bool XE::Platform::MinimizeWindow( XE::uint64 handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle ), SW_MINIMIZE ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle ) ) != 0;
}

bool XE::Platform::MaximizeWindow( XE::uint64 handle )
{
	return ::ShowWindow( reinterpret_cast< HWND >( handle ), SW_MAXIMIZE ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle ) ) != 0;
}

bool XE::Platform::FullscreenWindow( XE::uint64 handle )
{
	RECT desk_rect;
	HWND desk_handle;
	desk_handle = GetDesktopWindow();
	GetWindowRect( desk_handle, &desk_rect );
	SetWindowLong( reinterpret_cast< HWND >( handle ), GWL_STYLE, WS_BORDER );

	return SetWindowPos( reinterpret_cast< HWND >( handle ), HWND_TOPMOST, 0, 0, desk_rect.right, desk_rect.bottom, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle ) ) != 0;
}

bool Platform::SetWindowRect( XE::uint64 handle, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h, bool topmost )
{
	return ::SetWindowPos( reinterpret_cast< HWND >( handle ), topmost ? HWND_TOPMOST : HWND_NOTOPMOST, x, y, w, h, SWP_NOZORDER ) != 0 &&
		::UpdateWindow( reinterpret_cast< HWND >( handle ) ) != 0;
}

#endif
