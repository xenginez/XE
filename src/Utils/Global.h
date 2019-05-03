/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__D14A57AE_76BC_4477_A7EE_B0A076CB33D2
#define __GLOBAL_H__D14A57AE_76BC_4477_A7EE_B0A076CB33D2

#include <Reflect/Reflect.h>

#ifdef UTILS_EXPORT
#define UTILS_API DLL_EXPORT
#else
#define UTILS_API DLL_IMPORT
#define LIB_NAME "Utils"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__D14A57AE_76BC_4477_A7EE_B0A076CB33D2
