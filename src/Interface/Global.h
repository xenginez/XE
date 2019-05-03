/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/23
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__21F78FED_A550_4FF5_9C6A_18EF55BC2565
#define __GLOBAL_H__21F78FED_A550_4FF5_9C6A_18EF55BC2565

#include <Math/Math.h>
#include <Utils/Utils.h>

#ifdef INTERFACE_EXPORT
#define INTERFACE_API DLL_EXPORT
#else
#define INTERFACE_API DLL_IMPORT
#define LIB_NAME "Interface"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__21F78FED_A550_4FF5_9C6A_18EF55BC2565
