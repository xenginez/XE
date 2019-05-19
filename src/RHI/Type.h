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
DECL_PTR(Renderer);

DECL_HANDLE(RHI_API, Window);

DECL_HANDLE(RHI_API, Sampler);
DECL_HANDLE(RHI_API, Uniform);
DECL_HANDLE(RHI_API, FrameBuffer);
DECL_HANDLE(RHI_API, IndexBuffer);
DECL_HANDLE(RHI_API, VertexBuffer);
DECL_HANDLE(RHI_API, ComputeBuffer);
DECL_HANDLE(RHI_API, ConstantBuffer);
DECL_HANDLE(RHI_API, DepthStencilBuffer);
DECL_HANDLE(RHI_API, DynamicIndexBuffer);
DECL_HANDLE(RHI_API, DynamicVertexBuffer);

DECL_HANDLE(RHI_API, Program);
DECL_HANDLE(RHI_API, HullShader);
DECL_HANDLE(RHI_API, PixelShader);
DECL_HANDLE(RHI_API, VertexShader);
DECL_HANDLE(RHI_API, DomainShader);
DECL_HANDLE(RHI_API, ComputeShader);
DECL_HANDLE(RHI_API, TessellationShader);

DECL_HANDLE(RHI_API, Texture);

DECL_HANDLE(RHI_API, Viewport);


enum class RendererType
{
	SOFT,
	METAL,
	VULKAN,
	WEBGL1,
	WEBGL2,
	OPENGL2,
	OPENGL3,
	OPENGL_ES2,
	OPENGL_ES3,
	DIRECT3D_9,
	DIRECT3D_11,
	DIRECT3D_12,
};
DECL_META_ENUM(RHI_API, RendererType);

enum class TextureType
{
	TEXTURE2D,
	TEXTURE3D,
	TEXTURECUBE,
};

enum class TextureFormat
{

};

END_XE_NAMESAPCE

#endif //__TYPE_H__6580A518_948A_4162_A63F_E02DCC393EC9
