/*!
 * \file    RenderWindow.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-01
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERWINDOW_H__F05A60F4_E60E_45AF_BDEF_39C4D9D086BE
#define __RENDERWINDOW_H__F05A60F4_E60E_45AF_BDEF_39C4D9D086BE

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderWindow : XE::Window
{
	OBJECT(RenderWindow, Window)

public:
	RenderWindow();
	
	RenderWindow( const String &title, XE::uint32 flags = 0 );
	
	~RenderWindow();

public:
	FrameBufferPtr GetSurface() const;
	
	ViewHandle GetPresentPass() const;

protected:
	virtual void PrepareSurface();
	
	virtual void DestorySurface();

protected:
	virtual void OnResize();

private:
	FrameBufferPtr _Surface;
};

END_XE_NAMESAPCE

#endif // __RENDERWINDOW_H__F05A60F4_E60E_45AF_BDEF_39C4D9D086BE