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

#include "Handle.hpp"

BEG_XE_NAMESPACE

DECL_HANDLE( XE_API, Event );

class XE_API Event
{
public:
	Event();

	Event( EventHandle handle, ObjectPtr sender, ObjectPtr recver, const Variant & parameter = Variant() );

	Event( const Event & val );

	Event & operator=( const Event & val );

public:
	bool accept;
	EventHandle handle;
	ObjectPtr sender;
	ObjectPtr recver;
	Variant parameter;
};

DECL_META_CLASS( XE_API, Event );

END_XE_NAMESPACE

#define DECL_EVENT( NAME, DESC, PARAM ) \
DLL_VAR_WEAK extern const XE::Handle<XE::Event> NAME = XE::Order::RegisterOrder< XE::EventGroup >( #NAME, DESC, XE::TypeID< PARAM >::Get() )

#endif // EVENT_H__297F9FF1_F984_41D3_8EFF_6E87D3E265B5
