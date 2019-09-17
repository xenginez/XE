/*!
 * \file   Utils.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __UTILS_H__8586A462_1BAB_4CB7_8176_591B37A1B021
#define __UTILS_H__8586A462_1BAB_4CB7_8176_591B37A1B021

#include "LOD.h"
#include "Order.h"
#include "Layer.h"
#include "CRC32.h"
#include "Event.h"
#include "BASE64.h"
#include "Object.h"
#include "Message.h"
#include "Library.h"
#include "Platform.h"
#include "Handle.hpp"

#define DECL_HANDLE( _DLL_EXPORT, NAME ) class NAME; using NAME##Handle = XE::Handle< NAME >; DECL_META_CLASS( _DLL_EXPORT, NAME##Handle );

#define DECL_GROUP( _DLL_EXPORT, INDEX, NAME ) \
template<> class _DLL_EXPORT XE::OrderGroup< INDEX > \
{ \
public: \
    static constexpr XE::uint64 group_value = INDEX; \
}; \
typedef XE::OrderGroup< INDEX > NAME##Group;

#define DECL_ORDER(GROUP, NAME, DESC, PARAM) \
DLL_VAR_WEAK extern const XE::uint64 NAME = XE::Order::RegisterOrder< GROUP >( #NAME, DESC, XE::MetaID< PARAM >::Get() )

#define DECL_EVENT( NAME, DESC, PARAM ) DECL_ORDER( EventGroup, EVENT_##NAME, DESC, PARAM )
#define DECL_MESSAGE( NAME, DESC, PARAM ) DECL_ORDER( MessageGroup, MESSAGE_##NAME, DESC, PARAM )

BEG_XE_NAMESPACE

template<> class UTILS_API XE::OrderGroup< 1 >
{
public:
	static constexpr XE::uint64 group_value = 1;
};
typedef XE::OrderGroup< 1 > EventGroup;

template<> class UTILS_API XE::OrderGroup< 2 >
{
public:
	static constexpr XE::uint64 group_value = 2;
};
typedef XE::OrderGroup< 2 > MessageGroup;

END_XE_NAMESPACE

#endif // __UTILS_H__8586A462_1BAB_4CB7_8176_591B37A1B021
