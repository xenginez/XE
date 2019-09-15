/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__5D7B2936_AD8D_4517_BAA1_1707F1D0B9D4
#define GLOBAL_H__5D7B2936_AD8D_4517_BAA1_1707F1D0B9D4

#include <Math/Math.h>

#ifdef PSI_EXPORT
#define PSI_API DLL_EXPORT
#else
#define PSI_API DLL_IMPORT
#define LIB_NAME "PSI"
#include <Base/AutoLink.h>
#endif

#endif // GLOBAL_H__5D7B2936_AD8D_4517_BAA1_1707F1D0B9D4