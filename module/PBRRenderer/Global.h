/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/12
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__4D34F9F4_221E_452D_A4BB_473F27FBDB36
#define GLOBAL_H__4D34F9F4_221E_452D_A4BB_473F27FBDB36

#include <Interface/Interface.h>

#ifdef PBRRENDERER_EXPORT
#define PBRRENDERER_API DLL_EXPORT
#else
#define PBRRENDERER_API DLL_IMPORT
#define LIB_NAME "PBRRenderer"
#include <Base/AutoLink.h>
#endif

#endif // GLOBAL_H__4D34F9F4_221E_452D_A4BB_473F27FBDB36
