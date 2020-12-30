/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__4F2B270B_0E58_4279_AD64_600028073BB7
#define GLOBAL_H__4F2B270B_0E58_4279_AD64_600028073BB7

#include <XE.h>

#ifdef AI_EXPORT
#define AI_API DLL_EXPORT
#else
#define AI_API DLL_IMPORT
#endif // AI_EXPORT

#define BEG_AI_NAMESPACE namespace AI {
#define END_AI_NAMESPACE }

#endif // GLOBAL_H__4F2B270B_0E58_4279_AD64_600028073BB7
