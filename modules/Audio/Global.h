/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/12
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__25EB817C_1917_4789_BC35_1B5A98C5BE44
#define GLOBAL_H__25EB817C_1917_4789_BC35_1B5A98C5BE44

#include <XE.h>

#ifdef AUDIO_EXPORT
#define AUDIO_API DLL_EXPORT
#else
#define AUDIO_API DLL_IMPORT
#endif // AUDIO_EXPORT

#define BEG_AUDIO_NAMESPACE namespace Audio {
#define END_AUDIO_NAMESPACE }

#endif // GLOBAL_H__25EB817C_1917_4789_BC35_1B5A98C5BE44
