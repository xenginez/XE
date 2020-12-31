/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/31
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__B67EB6FB_F4A4_4A0C_9990_97CE5746639F
#define GLOBAL_H__B67EB6FB_F4A4_4A0C_9990_97CE5746639F

#include <XE.h>

#ifdef PHYSX_EXPORT
#define PHYSX_API DLL_EXPORT
#else
#define PHYSX_API DLL_IMPORT
#endif // PHYSX_EXPORT

#define BEG_PHYSX_NAMESPACE namespace PhysX {
#define END_PHYSX_NAMESPACE }

#endif // GLOBAL_H__B67EB6FB_F4A4_4A0C_9990_97CE5746639F
