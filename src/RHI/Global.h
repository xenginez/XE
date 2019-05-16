/*!
 * \file    Global.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-15
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__F78664F6_0EEA_470D_912E_4609A870224B
#define __GLOBAL_H__F78664F6_0EEA_470D_912E_4609A870224B

#include <Interface/Interface.h>

#ifdef RHI_EXPORT
#define RHI_API DLL_EXPORT
#else
#define RHI_API DLL_IMPORT
#define LIB_NAME "RHI"
#include <Base/AutoLink.h>
#endif

#endif //__GLOBAL_H__F78664F6_0EEA_470D_912E_4609A870224B
