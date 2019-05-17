/*!
 * \file    Type.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-15
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__6580A518_948A_4162_A63F_E02DCC393EC9
#define __TYPE_H__6580A518_948A_4162_A63F_E02DCC393EC9

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR(Image);
DECL_PTR(RenderWindow);

DECL_HANDLE(RHI_API, Sampler);
DECL_HANDLE(RHI_API, IndexBuffer);
DECL_HANDLE(RHI_API, VertexBuffer);
DECL_HANDLE(RHI_API, ComputeBuffer);
DECL_HANDLE(RHI_API, ConstantBuffer);
DECL_HANDLE(RHI_API, DepthStencilBuffer);
DECL_HANDLE(RHI_API, HullShader);
DECL_HANDLE(RHI_API, PixelShader);
DECL_HANDLE(RHI_API, VertexShader);
DECL_HANDLE(RHI_API, DomainShader);
DECL_HANDLE(RHI_API, ComputeShader);
DECL_HANDLE(RHI_API, TessellationShader);
DECL_HANDLE(RHI_API, Texture);
DECL_HANDLE(RHI_API, Texture2D);
DECL_HANDLE(RHI_API, Texture3D);
DECL_HANDLE(RHI_API, TextureCube);
DECL_HANDLE(RHI_API, Texture2DArray);
DECL_HANDLE(RHI_API, Viewport);
DECL_HANDLE(RHI_API, RenderTarget);
DECL_HANDLE(RHI_API, RenderWindow);


enum class WindowFlag : XE::uint32
{
	GRAB				= 1 << 1,
	SHOW				= 1 << 2,
	MINIMIZE			= 1 << 3,
	FULLSRCEEN			= 1 << 4,
	FOREGROUND			= 1 << 5,
	SHOWCURSOR			= 1 << 6,
};
DECL_META_ENUM(RHI_API, WindowFlag);


END_XE_NAMESAPCE

#endif //__TYPE_H__6580A518_948A_4162_A63F_E02DCC393EC9
