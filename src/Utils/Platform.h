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

#include "Handle.h"

BEG_XE_NAMESPACE

class Window; using WindowHandle = XE::Handle< XE::Window >; DECL_META_CLASS( UTILS_API, WindowHandle );
class Process; using ProcessHandle = XE::Handle< XE::Process >; DECL_META_CLASS( UTILS_API, ProcessHandle );

class UTILS_API Platform
{
public:
	static Language GetDefaultLanguage();

public:
	static bool RegisterWindowClass( const String & icon, std::function<bool( WindowHandle, XE::WindowEvent )> callback );

	static void UnregisterWindowClass();

	static WindowHandle ConstructWindow( const String & title, XE::uint32 x, XE::uint32 y, XE::uint32 w, XE::uint32 h );

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

public:
	static bool ShowMouse();

	static bool HideMouse();

public:
	static ProcessHandle ConstructProcess( const std::filesystem::path & app, const std::string & cmd, bool inherit, XE::uint32 flag );

	static bool DestroyProcess( ProcessHandle handle, XE::uint32 code );

};

END_XE_NAMESPACE

#endif // __PLATFORM_H__BDD7C650_EC23_41CF_A4EA_7CDBFE3B0135
