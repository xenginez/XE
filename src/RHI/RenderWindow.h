/*!
 * \file    RenderWindow.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-16
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERWINDOW_H__30A203B0_90D8_42E1_A032_520EC8A73A3D
#define __RENDERWINDOW_H__30A203B0_90D8_42E1_A032_520EC8A73A3D

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API RenderWindow : public XE::Object
{
	OBJECT(RenderWindow, Object)
	
public:
	RenderWindow();
	
	~RenderWindow() override = default;

public:
	void Grab();
	
	void Show();
	
	void Hide();
	
	void Minimize();
	
	void Maximize();
	
	void Fullsrceen();

	void Foreground();

	void ShowCursor();
	
	void HideCursor();
	
public:
	bool IsGrab();
	
	bool IsShow();
	
	bool IsHide();
	
	bool IsMinimize();
	
	bool IsMaximize();
	
	bool IsFullsrceen();
	
	bool IsForeground();
	
	bool IsShowCursor();
	
	bool IsHideCursor();

public:
	uint32 GetFlag() const;
	
	void SetFlag( uint32 val );
	
	const String& GetIcon() const;
	
	void SetIcon( const String& val );
	
	const String& GetCursor() const;
	
	void SetCursor( const String& val );
	
	const String& GetTitle() const;
	
	void SetTitle( const String& val );
	
	const Vec2& GetSize() const;
	
	void SetSize( const Vec2& val );
	
	const Vec2& GetPosition() const;
	
	void SetPosition( const Vec2& val );

public:
	RenderWindowHandle GetHandle() const;
	
	static RenderWindowPtr FromHandle( const RenderWindowHandle& val );
	
protected:
	virtual void Restore() = 0;
	
	virtual void FromNatvieHandle() = 0;
	
	void SetHandle( const RenderWindowHandle& val );

private:
	uint32 _Flag;
	String _Icon;
	String _Cursor;
	String _Title;
	Vec2 _Size;
	Vec2 _Position;
	RenderWindowHandle _Handle;
};

END_XE_NAMESAPCE

#endif //__RENDERWINDOW_H__30A203B0_90D8_42E1_A032_520EC8A73A3D
