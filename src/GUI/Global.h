/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__6A6AC972_C99D_4550_9FD3_66459F5AA0D0
#define __GLOBAL_H__6A6AC972_C99D_4550_9FD3_66459F5AA0D0

#include <Graphics/Graphics.h>

#ifdef GUI_EXPORT
#define GUI_API DLL_EXPORT
#else
#define GUI_API DLL_IMPORT
#define LIB_NAME "GUI"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__6A6AC972_C99D_4550_9FD3_66459F5AA0D0
