/*!
 * \file	Global.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/12
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GLOBAL_H__C2229150_8ADE_496B_8DDE_B063758111E4
#define GLOBAL_H__C2229150_8ADE_496B_8DDE_B063758111E4

#include <Core/Core.h>

#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <windows.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#ifdef D3DRHI_EXPORT
#define D3DRHI_API DLL_EXPORT
#else
#define D3DRHI_API DLL_IMPORT
#define LIB_NAME "D3DRHI"
#include <Base/AutoLink.h>
#endif

#endif // GLOBAL_H__C2229150_8ADE_496B_8DDE_B063758111E4
