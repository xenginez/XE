/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/26
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__91B28655_EE77_448D_8860_4F53F448E689
#define __GLOBAL_H__91B28655_EE77_448D_8860_4F53F448E689

#include <Interface/Interface.h>

#ifdef CORE_EXPORT
#define CORE_API DLL_EXPORT
#else
#define CORE_API DLL_IMPORT
#define LIB_NAME "Core"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__91B28655_EE77_448D_8860_4F53F448E689
