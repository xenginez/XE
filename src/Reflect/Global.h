/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__E6399CA9_7F1D_4C2F_B9A1_67FEA323F006
#define __GLOBAL_H__E6399CA9_7F1D_4C2F_B9A1_67FEA323F006

#include <GC/GC.h>

#ifdef REFLECT_EXPORT
#define REFLECT_API DLL_EXPORT
#else
#define REFLECT_API DLL_IMPORT
#define LIB_NAME "Reflect"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__E6399CA9_7F1D_4C2F_B9A1_67FEA323F006
