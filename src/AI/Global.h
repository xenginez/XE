/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__B570A5F2_E5DF_4723_BB42_4616AC6080F8
#define __GLOBAL_H__B570A5F2_E5DF_4723_BB42_4616AC6080F8

#include <World/World.h>

#ifdef AI_EXPORT
#define AI_API DLL_EXPORT
#else
#define AI_API DLL_IMPORT
#define LIB_NAME "AI"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__B570A5F2_E5DF_4723_BB42_4616AC6080F8
