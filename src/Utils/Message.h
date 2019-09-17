/*!
 * \file	Message.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MESSAGE_H__973F55B0_8973_4D6E_AAE6_16EF56B2FCC6
#define MESSAGE_H__973F55B0_8973_4D6E_AAE6_16EF56B2FCC6

#include "Type.h"

BEG_XE_NAMESPACE

class UTILS_API Message
{
public:
	Message();

	Message( XE::uint64 id, ObjectPtr sender = nullptr, const Variant & parameter = Variant() );

	Message( const Message & val );

public:
	bool accept;
	XE::uint64 id;
	ObjectPtr sender;
	Variant parameter;
};
DECL_META_CLASS( UTILS_API, Message );

END_XE_NAMESPACE

#endif // MESSAGE_H__973F55B0_8973_4D6E_AAE6_16EF56B2FCC6
