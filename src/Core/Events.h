/*!
 * \file	Events.h
 *
 * \author	ZhengYuanQing
 * \date	2019/12/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef EVENTS_H__6525B5CD_865C_415D_B6CF_9959A8EDCA0F
#define EVENTS_H__6525B5CD_865C_415D_B6CF_9959A8EDCA0F

#include "Type.h"


DECL_EVENT( WINDOW, "window events", XE::WindowEventPair );

DECL_EVENT( KEY_UP, "keyboard button up", XE::uint32 );
DECL_EVENT( KEY_DOWN, "keyboard button down", XE::uint32 );
DECL_EVENT( MOUSE_UP, "mouse button up", XE::uint32 );
DECL_EVENT( MOUSE_DOWN, "mouse button down", XE::uint32 );
DECL_EVENT( MOUSE_WHEEL, "mouse wheel", XE::uint32 );
DECL_EVENT( MOUSE_MOVE, "mouse move", XE::Vec2 );

DECL_EVENT( OPEN_WORLD, "open world", XE::WorldPtr );

#endif // EVENTS_H__6525B5CD_865C_415D_B6CF_9959A8EDCA0F
