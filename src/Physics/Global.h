/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__988A05AF_624C_40F1_BE25_71295FF4361A
#define __GLOBAL_H__988A05AF_624C_40F1_BE25_71295FF4361A

#include <World/World.h>

#ifdef PHYSICS_EXPORT
#define PHYSICS_API DLL_EXPORT
#else
#define PHYSICS_API DLL_IMPORT
#define LIB_NAME "Physics"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__988A05AF_624C_40F1_BE25_71295FF4361A
