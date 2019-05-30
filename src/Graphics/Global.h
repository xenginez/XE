/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__A39D40FD_1112_4C77_B112_E283BE8AFE97
#define __GLOBAL_H__A39D40FD_1112_4C77_B112_E283BE8AFE97

#include <Interface/Interface.h>

#ifdef GRAPHICS_EXPORT
#define GRAPHICS_API DLL_EXPORT
#else
#define GRAPHICS_API DLL_IMPORT
#define LIB_NAME "Graphics"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__A39D40FD_1112_4C77_B112_E283BE8AFE97
