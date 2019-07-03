/*!
 * \file	RenderWindow.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/03
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERWINDOW_H__5C73A47E_1E26_4EE2_81AA_1336FFAC2843
#define RENDERWINDOW_H__5C73A47E_1E26_4EE2_81AA_1336FFAC2843

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API RenderWindow : public std::enable_shared_from_this< RenderWindow >, public XE::NonCopyable
{
public:
	RenderWindow( DevicePtr val );

	~RenderWindow();

public:
	void Show();

	void Hide();

	void Focus();

	void Minimize();

	void Maximize();

	void Fullscreen();

public:
	bool IsShow() const;

	bool IsHide() const;

	bool IsFocus() const;

	bool IsMinimized() const;

	bool IsMaximized() const;

	bool IsFullscreen() const;

public:
	XE::uint32 GetPosX() const;

	void SetPosX( XE::uint32 x );

	XE::uint32 GetPosY() const;

	void SetPosY( XE::uint32 y );

	XE::uint32 GetWidth() const;

	void SetWidth( XE::uint32 w );

	XE::uint32 GetHeight() const;

	void SetHeight( XE::uint32 h );

	Vec2 GetSize() const;

	void SetSize( const Vec2 & val );

	Vec2 GetPosition() const;

	void SetPosition( const Vec2 & val );

	const Rect & GetRect() const;

	void SetRect( const Rect & val );

	const String & GetTitle() const;

	void SetTitle( const String & val );

public:
	FrameBufferPtr GetBackFrameBuffer() const;

	FrameBufferPtr GetFrontFrameBuffer() const;

	FrameBufferPtr GetCurrentFrameBuffer() const;

private:
	bool _Show = true;
	bool _Fullscreen = false;

	Rect _Rect = { 0, 0, 800, 600 };
	String _Title = "XE";

	DevicePtr _Device;
	RenderWindowHandle _Handle;
};

END_XE_NAMESPACE

#endif // RENDERWINDOW_H__5C73A47E_1E26_4EE2_81AA_1336FFAC2843
