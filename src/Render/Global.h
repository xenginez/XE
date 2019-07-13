/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__A39D40FD_1112_4C76_B112_E283BE8AFE97
#define __GLOBAL_H__A39D40FD_1112_4C76_B112_E283BE8AFE97

#include <Graphics/Graphics.h>

#ifdef RENDER_EXPORT
#define RENDER_API DLL_EXPORT
#else
#define RENDER_API DLL_IMPORT
#define LIB_NAME "Render"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__A39D40FD_1112_4C76_B112_E283BE8AFE97
