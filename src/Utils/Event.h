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

#include "Type.h"

BEG_XE_NAMESPACE

class UTILS_API Event
{
public:
	Event();

	Event( XE::uint64 id, ObjectPtr sender, ObjectPtr recver, const Variant & parameter = Variant() );

	Event( const Event & val );

public:
	bool accept;
	XE::uint64 id;
	ObjectPtr sender;
	ObjectPtr recver;
	Variant parameter;
};
DECL_META_CLASS( UTILS_API, Event );

END_XE_NAMESPACE

#endif // EVENT_H__297F9FF1_F984_41D3_8EFF_6E87D3E265B5
