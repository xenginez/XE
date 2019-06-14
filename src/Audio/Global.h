/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__0DFC6107_240B_453A_970F_16275816320F
#define __GLOBAL_H__0DFC6107_240B_453A_970F_16275816320F

#include <Interface/Interface.h>

#ifdef AUDIO_EXPORT
#define AUDIO_API DLL_EXPORT
#else
#define AUDIO_API DLL_IMPORT
#define LIB_NAME "Audio"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__0DFC6107_240B_453A_970F_16275816320F
