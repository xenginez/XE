/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__12933BCF_36C7_45E2_9F4F_72FE139EE196
#define __GLOBAL_H__12933BCF_36C7_45E2_9F4F_72FE139EE196

#include <Graphics/Graphics.h>

#ifdef ANIMATION_EXPORT
#define ANIMATION_API DLL_EXPORT
#else
#define ANIMATION_API DLL_IMPORT
#define LIB_NAME "Animation"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__12933BCF_36C7_45E2_9F4F_72FE139EE196
