/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/08
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__8368C858_9522_4982_8171_9B6DE389F766
#define GLOBAL_H__8368C858_9522_4982_8171_9B6DE389F766

#include <Reflect/Reflect.h>

#ifdef XSCRIPT_EXPORT
#define XSCRIPT_API DLL_EXPORT
#else
#define XSCRIPT_API DLL_IMPORT
#define LIB_NAME "XSCRIPT"
#include <Base/AutoLink.h>
#endif

#endif // GLOBAL_H__8368C858_9522_4982_8171_9B6DE389F766
