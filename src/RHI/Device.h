/*!
 * \file	Device.h
 *
 * \author	ZhengYuanQing
 * \date	2019/06/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DEVICE_H__C8946AB4_1220_4FEE_AB78_53C9D8C6A6A3
#define DEVICE_H__C8946AB4_1220_4FEE_AB78_53C9D8C6A6A3

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Device
{
	OBJECT( Device )

public:
	Device();

	virtual ~Device();

public:
	virtual void Startup() = 0;

	virtual void Clearup() = 0;

public:
	virtual DeviceType GetType() const = 0;

public:
	virtual WindowHandle CreateWindow( XE::uint64 native_handle ) = 0;

	virtual WindowHandle CreateWindow( const String & title, const Rect & rect ) = 0;

	virtual void DestroyWindow( const WindowHandle & handle ) = 0;

	virtual void ShowWindow( const WindowHandle & handle ) = 0;

	virtual void HideWindow( const WindowHandle & handle ) = 0;

	virtual void MinimizeWindow( const WindowHandle & handle ) = 0;

	virtual void MaximizeWindow( const WindowHandle & handle ) = 0;

	virtual void FullscreenWindow( const WindowHandle & handle ) = 0;

	virtual bool GetWindowGrab( const WindowHandle & handle ) = 0;

	virtual void SetWindowGrab( const WindowHandle & handle, bool grab ) = 0;

	virtual Rect GetWindowRect( const WindowHandle & handle ) = 0;

	virtual void SetWindowRect( const WindowHandle & handle, const Rect & rect ) = 0;

	virtual Vec2 GetWindowSize( const WindowHandle & handle ) = 0;

	virtual void SetWindowSize( const WindowHandle & handle, const Vec2 & size ) = 0;

	virtual Vec2 GetWindowPosition( const WindowHandle & handle ) = 0;

	virtual void SetWindowPosition( const WindowHandle & handle, const Vec2 & pos ) = 0;

	virtual String GetWindowIcon( const WindowHandle & handle ) = 0;

	virtual void SetWindowIcon( const WindowHandle & handle, const String & icon ) = 0;

	virtual String GetWindowTitle( const WindowHandle & handle ) = 0;

	virtual void SetWindowTitle( const WindowHandle & handle, const String & title ) = 0;

};

END_XE_NAMESPACE

#endif // DEVICE_H__C8946AB4_1220_4FEE_AB78_53C9D8C6A6A3
