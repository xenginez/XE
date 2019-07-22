/*!
 * \file	Event.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef EVENT_H__1137B910_A3BE_4F6D_8873_46BF1A32A1D1
#define EVENT_H__1137B910_A3BE_4F6D_8873_46BF1A32A1D1

#include "Type.h"

BEG_XE_NAMESPACE

using WindowEventPair = XE::Pair<WindowHandle, XE::WindowEvent>;

DECL_EVENT( WINDOW, "window events", XE::Pair<WindowHandle, XE::WindowEvent> );
DECL_EVENT( KEY_UP, "keyboard button up", XE::uint32 );
DECL_EVENT( KEY_DOWN, "keyboard button down", XE::uint32 );
DECL_EVENT( MOUSE_UP, "mouse button up", XE::uint32 );
DECL_EVENT( MOUSE_DOWN, "mouse button down", XE::uint32 );
DECL_EVENT( MOUSE_WHEEL, "mouse wheel", XE::uint32 );

END_XE_NAMESPACE

#endif // EVENT_H__1137B910_A3BE_4F6D_8873_46BF1A32A1D1
