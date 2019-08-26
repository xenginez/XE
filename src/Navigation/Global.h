/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__77E2A866_AA34_4D76_8807_A2F0EEAE8A57
#define __GLOBAL_H__77E2A866_AA34_4D76_8807_A2F0EEAE8A57

#include <Math/Math.h>

#ifdef NAVIGATION_EXPORT
#define NAVIGATION_API DLL_EXPORT
#else
#define NAVIGATION_API DLL_IMPORT
#define LIB_NAME "Navigation"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__77E2A866_AA34_4D76_8807_A2F0EEAE8A57
