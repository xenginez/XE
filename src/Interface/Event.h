/*!
 * \file	Event.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/03
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef EVENT_H__297F9FF1_F984_41D3_8EFF_6E87D3E265B5
#define EVENT_H__297F9FF1_F984_41D3_8EFF_6E87D3E265B5

#include "Utils/Order.h"
#include "Utils/Handle.hpp"

#include "Type.h"

BEG_XE_NAMESPACE

DECL_HANDLE( XE_API, Event );

class XE_API Event
{
public:
	Event();

	Event( XE::EventHandle handle, XE::ObjectPtr sender, XE::ObjectPtr recver, const XE::Variant & parameter = XE::Variant() );

	Event( const Event & val );

	Event & operator=( const Event & val );

public:
	bool accept;
	XE::EventHandle handle;
	XE::ObjectPtr sender;
	XE::ObjectPtr recver;
	XE::Variant parameter;
};

DECL_META_CLASS( XE_API, Event );

END_XE_NAMESPACE

#define DECL_EVENT( NAME, DESC, ... ) \
DLL_VAR_WEAK extern const XE::Handle<XE::Event> EVENT_##NAME = XE::HandleCast< XE::Event >( XE::Order::RegisterOrder< XE::EventGroup >( #NAME, DESC, XE_TypeID< __VA_ARGS__ >::Get() ) )


DECL_EVENT( WINDOW, "window events", XE::WindowEvent );
DECL_EVENT( KEY_UP, "keyboard button up", XE::uint32 );
DECL_EVENT( KEY_DOWN, "keyboard button down", XE::uint32 );
DECL_EVENT( MOUSE_UP, "mouse button up", XE::uint32 );
DECL_EVENT( MOUSE_DOWN, "mouse button down", XE::uint32 );
DECL_EVENT( MOUSE_WHEEL, "mouse wheel", XE::uint32 );
DECL_EVENT( MOUSE_MOVE, "mouse move", XE::Pair<XE::uint32, XE::uint32> );


#endif // EVENT_H__297F9FF1_F984_41D3_8EFF_6E87D3E265B5
