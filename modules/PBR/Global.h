/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2019/10/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__786B5DBE_FE97_4D6A_831D_1BA397624BD0
#define GLOBAL_H__786B5DBE_FE97_4D6A_831D_1BA397624BD0

#include <XE.h>

#ifdef PBR_EXPORT
#define PBR_API DLL_EXPORT
#else
#define PBR_API DLL_IMPORT
#endif // PBR_EXPORT

#define BEG_PBR_NAMESPACE namespace PBR {
#define END_PBR_NAMESPACE }

#endif // GLOBAL_H__786B5DBE_FE97_4D6A_831D_1BA397624BD0
