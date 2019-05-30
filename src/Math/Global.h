/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__C4E5B4C5_7BA4_4D64_8216_F334705DEE66
#define __GLOBAL_H__C4E5B4C5_7BA4_4D64_8216_F334705DEE66

#include <Utils/Utils.h>

#ifdef MATH_EXPORT
#define MATH_API DLL_EXPORT
#else
#define MATH_API DLL_IMPORT
#define LIB_NAME "Math"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__C4E5B4C5_7BA4_4D64_8216_F334705DEE66
