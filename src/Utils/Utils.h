/*!
 * \file	Utils.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef UTILS_H__836D437C_196C_4DE7_8062_D8A3F6CEC7D3
#define UTILS_H__836D437C_196C_4DE7_8062_D8A3F6CEC7D3

#include "LOD.h"
#include "CRC32.h"
#include "Event.h"
#include "Layer.h"
#include "Order.h"
#include "BASE64.h"
#include "Object.h"
#include "Prefab.h"
#include "Library.h"
#include "Platform.h"
#include "Handle.hpp"


#define DECL_HANDLE( _DLL_EXPORT, NAME ) class NAME; using NAME##Handle = XE::Handle< NAME >; DECL_META_CLASS( _DLL_EXPORT, NAME##Handle );

#define DECL_GROUP( _DLL_EXPORT, INDEX, NAME ) \
template<> class _DLL_EXPORT XE::OrderGroup< INDEX > \
{ \
public: \
    static constexpr XE::uint8 group_value = INDEX; \
}; \
namespace XE{ using NAME##Group = XE::OrderGroup< INDEX >; }

#define DECL_EVENT( NAME, DESC, PARAM ) \
DLL_VAR_WEAK extern const XE::Handle<XE::Event> NAME = XE::Order::RegisterOrder< XE::EventGroup >( #NAME, DESC, XE::MetaID< PARAM >::Get() )


DECL_GROUP( XE_API, 1, Event );

#endif // UTILS_H__836D437C_196C_4DE7_8062_D8A3F6CEC7D3
