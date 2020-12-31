/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/31
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__709E2A87_5049_45A9_81BD_6FA0F188C25B
#define GLOBAL_H__709E2A87_5049_45A9_81BD_6FA0F188C25B

#include <XE.h>

#ifdef AL_EXPORT
#define AL_API DLL_EXPORT
#else
#define AL_API DLL_IMPORT
#endif // AL_EXPORT

#define BEG_AL_NAMESPACE namespace PhysX {
#define END_AL_NAMESPACE }

#endif // GLOBAL_H__709E2A87_5049_45A9_81BD_6FA0F188C25B
