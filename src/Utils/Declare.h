/*!
 * \file   Declare.h
 *
 * \author ZhengYuanQing
 * \date   2020/10/06
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef DECLARE_H__4652FD34_ED41_4ED7_8178_1C4A9DEDD565
#define DECLARE_H__4652FD34_ED41_4ED7_8178_1C4A9DEDD565

#include "Utils/Event.h"
#include "Utils/Order.h"

BEG_XE_NAMESPACE

DECL_GROUP( XE_API, 1, Event );

DECL_EVENT( WINDOW, "window events", XE::WindowEvent );
DECL_EVENT( KEY_UP, "keyboard button up", XE::uint32 );
DECL_EVENT( KEY_DOWN, "keyboard button down", XE::uint32 );
DECL_EVENT( MOUSE_UP, "mouse button up", XE::uint32 );
DECL_EVENT( MOUSE_DOWN, "mouse button down", XE::uint32 );
DECL_EVENT( MOUSE_WHEEL, "mouse wheel", XE::uint32 );
DECL_EVENT( MOUSE_MOVE, "mouse move", XE::Vec2 );
DECL_EVENT( OPEN_WORLD, "open world", void );

END_XE_NAMESPACE

#endif // DECLARE_H__4652FD34_ED41_4ED7_8178_1C4A9DEDD565
