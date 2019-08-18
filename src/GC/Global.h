/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/02/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__BDB8E907_2027_44BC_81D5_6216D2D7107B
#define __GLOBAL_H__BDB8E907_2027_44BC_81D5_6216D2D7107B

#include <Base/Base.h>

#ifdef GC_EXPORT
#define GC_API DLL_EXPORT
#else
#define GC_API DLL_IMPORT
#define LIB_NAME "GC"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__BDB8E907_2027_44BC_81D5_6216D2D7107B
