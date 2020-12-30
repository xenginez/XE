/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__82C520ED_4A02_4AF9_B604_544FE9FC3C80
#define GLOBAL_H__82C520ED_4A02_4AF9_B604_544FE9FC3C80

#include <XE.h>

#ifdef ANIMATION_EXPORT
#define ANIMATION_API DLL_EXPORT
#else
#define ANIMATION_API DLL_IMPORT
#endif // AI_EXPORT

#define BEG_ANIMATION_NAMESPACE namespace Animation {
#define END_ANIMATION_NAMESPACE }

#endif // GLOBAL_H__82C520ED_4A02_4AF9_B604_544FE9FC3C80
