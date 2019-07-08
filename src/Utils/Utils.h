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
#include "BASE64.h"
#include "Handle.h"
#include "Library.h"
#include "Platform.h"
#include "Profiler.h"

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

#ifdef DEBUG
#define PROFILER_TRACK(X) XE::ProfilerTrack _321_Profiler_Track__##X_456_(__FILE__, __LINE__, #X);
#else
#define PROFILER_TRACK(X)
#endif

#ifdef DEBUG
#define PROFILER_FUNCTION() XE::ProfilerTrack _321_Profiler_Function_456_(__FILE__, __LINE__, __FUNCTION__);
#else
#define PROFILER_FUNCTION()
#endif // DEBUG

#endif // __UTILS_H__8586A462_1BAB_4CB7_8176_591B37A1B021
