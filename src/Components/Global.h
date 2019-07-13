/*!
 * \file   Global.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GLOBAL_H__4C22FF7D_B3D1_4890_9778_7D8F6AB64B92
#define __GLOBAL_H__4C22FF7D_B3D1_4890_9778_7D8F6AB64B92

#include <AI/AI.h>
#include <GUI/GUI.h>
#include <Audio/Audio.h>
#include <Physics/Physics.h>
#include <Graphics/Graphics.h>
#include <Navigation/Navigation.h>

#ifdef COMPONENTS_EXPORT
#define COMPONENTS_API DLL_EXPORT
#else
#define COMPONENTS_API DLL_IMPORT
#define LIB_NAME "Components"
#include <Base/AutoLink.h>
#endif

#endif // __GLOBAL_H__4C22FF7D_B3D1_4890_9778_7D8F6AB64B92
