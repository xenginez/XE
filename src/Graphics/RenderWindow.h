/*!
 * \file	RenderWindow.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERWINDOW_H__3BD26354_B4C2_4E7C_88DF_1F719BFB8397
#define RENDERWINDOW_H__3BD26354_B4C2_4E7C_88DF_1F719BFB8397

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API RenderWindow : public XE::Object
{
	OBJECT( RenderWindow, Object )

public:
	RenderWindow();

	~RenderWindow() override;

public:
	void Show();

	void Hide();

	void Minimize();

	void Maximize();

	void Fullscreen();

	void Close();

public:
	void MouseLock();

	void MouseUnlock();

public:
	bool IsShow();

	bool IsNormal();

	bool IsMinimized();

	bool IsMaximized();

	bool IsFullscreen();

	bool IsMouseLock();

public:
	const XE::String & GetTitle() const;

	void SetTitle( const XE::String & val );

	const XE::Vec2 & GetSize() const;

	void SetSize( const XE::Vec2 & val );

	const XE::Vec2 & GetPosition() const;

	void SetPosition( const XE::Vec2 & val );

public:
	XE::WindowHandle GetWindowHandle() const;

	void SetWindowHandle( XE::WindowHandle val );

private:
	void UpdateWindow();

private:
	XE::Vec2 _Size;
	XE::String _Title;
	XE::Vec2 _Position;
	bool _Show;
	bool _Minimize;
	bool _Maximize;
	bool _MouseLock;
	bool _Fullscreen;
	
	bool _Dirty;

	WindowHandle _WindowHandle;
};

END_XE_NAMESPACE

#endif // RENDERWINDOW_H__3BD26354_B4C2_4E7C_88DF_1F719BFB8397
