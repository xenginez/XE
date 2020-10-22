/*!
 * \file   Platform.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135
#define __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135

#include "Event.h"

BEG_XE_NAMESPACE

DECL_HANDLE( XE_API, Window );
DECL_HANDLE( XE_API, Process );

class XE_API Platform
{
public:
	static Language GetDefaultLanguage();

public:
	static WindowHandle CreateWindow( const String & title, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h );

	static bool DestroyWindow( WindowHandle handle );

	static bool GrabWindow( WindowHandle handle );

	static bool ShowWindow( WindowHandle handle );

	static bool HideWindow( WindowHandle handle );

	static bool MinimizeWindow( WindowHandle handle );

	static bool MaximizeWindow( WindowHandle handle );

	static bool FullscreenWindow( WindowHandle handle );

	static bool GetWindowFocus( WindowHandle handle );

	static bool SetWindowTitle( WindowHandle handle, const String & title );

	static bool SetWindowRect( WindowHandle handle, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h, bool topmost );

	static bool GetDesktopSize( XE::uint32 & w, XE::uint32 & h );

public:
	static bool ShowMouse();

	static bool HideMouse();

public:
	static ProcessHandle CreateProcess( const XE::FileSystem::Path & app, const std::string & cmd, bool inherit, XE::uint32 flag );

	static bool DestroyProcess( ProcessHandle handle, XE::uint32 code );

};

END_XE_NAMESPACE

DECL_EVENT( WINDOW, "window events", XE::WindowEvent );
DECL_EVENT( KEY_UP, "keyboard button up", XE::uint32 );
DECL_EVENT( KEY_DOWN, "keyboard button down", XE::uint32 );
DECL_EVENT( MOUSE_UP, "mouse button up", XE::uint32 );
DECL_EVENT( MOUSE_DOWN, "mouse button down", XE::uint32 );
DECL_EVENT( MOUSE_WHEEL, "mouse wheel", XE::uint32 );
DECL_EVENT( MOUSE_MOVE, "mouse move", XE::Pair<XE::uint32, XE::uint32> );

#endif // __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135
