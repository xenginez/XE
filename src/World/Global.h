/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__23E217B7_CA9F_4286_9EB1_347706B49152
#define __GLOBAL_H__23E217B7_CA9F_4286_9EB1_347706B49152

#include <Math/Math.h>

#ifdef WORLD_EXPORT
#define WORLD_API DLL_EXPORT
#else
#define WORLD_API DLL_IMPORT
#define LIB_NAME "World"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__23E217B7_CA9F_4286_9EB1_347706B49152
