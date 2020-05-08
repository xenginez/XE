/*!
 * \file	Structs.h
 *
 * \author	ZhengYuanQing
 * \date	2020/04/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef STRUCTS_H__F731AAF0_BE7D_47A2_BCEC_5E0622CFE54D
#define STRUCTS_H__F731AAF0_BE7D_47A2_BCEC_5E0622CFE54D

#include "Type.h"

BEG_XE_NAMESPACE

enum class CommandType : XE::uint8
{
	RENDERER_INIT,
	RENDERER_SHUTDOWN_BEGIN,
	CREATE_VERTEX_LAYOUT,
	CREATE_INDEX_BUFFER,
	CREATE_VERTEX_BUFFER,
	CREATE_DYNAMIC_INDEX_BUFFER,
	UPDATE_DYNAMIC_INDEX_BUFFER,
	CREATE_DYNAMIC_VERTEX_BUFFER,
	UPDATE_DYNAMIC_VERTEX_BUFFER,
	CREATE_SHADER,
	CREATE_PROGRAM,
	CREATE_TEXTURE,
	UPDATE_TEXTURE,
	RESIZE_TEXTURE,
	CREATE_FRAME_BUFFER,
	CREATE_UNIFORM,
	UPDATE_VIEW_NAME,
	INVALIDATE_OCCLUSION_QUERY,
	SET_NAME,
	END,
	RENDERER_SHUTDOWN_END,
	DESTROY_VERTEX_LAYOUT,
	DESTROY_INDEX_BUFFER,
	DESTROY_VERTEX_BUFFER,
	DESTROY_DYNAMIC_INDEX_BUFFER,
	DESTROY_DYNAMIC_VERTEX_BUFFER,
	DESTROY_SHADER,
	DESTROY_PROGRAM,
	DESTROY_TEXTURE,
	DESTROY_FRAMEBUFFER,
	DESTROY_UNIFORM,
	READ_TEXTURE,
	REQUEST_SCREEN_SHOT,
};

class View
{
public:
	XE::Color Color;
	XE::float32 Depth = 0.0f;
	XE::uint8 Stencil;
	XE::Rect Rect;
	XE::Rect Scissor;
	XE::Mat4 ViewMat;
	XE::Mat4 ProjMat;
	ViewMode Mode = XE::ViewMode::Default;
	FrameBufferHandle Handle;
};

class RenderBind
{
public:
	enum BindType : XE::uint8
	{
		IMAGE,
		INDEXBUFFER,
		VERTEXBUFFER,
		TEXTURE,

		COUNT
	};

	BindType Type;
	XE::uint32 SamplerFlags;
	XE::uint16 Index;
	XE::TextureFormat Format;
	XE::Access Access;
	XE::uint8 Mip;
};

class RenderDraw
{
public:
	struct
	{
		VertexBufferHandle buffer_handle;
		VertexLayoutHandle layout_handle;
	} Vertexs[GFX_MAX_VERTEXS];

	XE::Flags<XE::StateFlag> StateFlags = XE::StateFlag::NONE;
	XE::Flags <XE::StencilFlag> StencilFlags = XE::StencilFlag::NONE;
	XE::Color Rgba;
	XE::uint32 UniformBegin;
	XE::uint32 UniformEnd;
	XE::uint32 StartMatrix;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
	XE::uint32 NumVertices;
	XE::uint32 InstanceDataOffset;
	XE::uint32 NumInstances;
	XE::uint16 InstanceDataStride;
	XE::uint16 StartIndirect;
	XE::uint16 NumIndirect;
	XE::uint16 NumMatrices;
	XE::uint16 Scissor;
	XE::uint8 SubmitFlags;
	XE::uint8 StreamMask;
	XE::uint8 UniformIdx;

	XE::IndexBufferHandle IndexBuffer;
	XE::VertexBufferHandle InstanceDataBuffer;
	XE::IndirectBufferHandle IndirectBuffer;
	XE::OcclusionQueryHandle OcclusionQuery;
};

class RenderBlit
{
public:
	XE::uint32 SrcX = 0;
	XE::uint32 SrcY = 0;
	XE::uint32 SrcZ = 0;
	XE::uint32 DstX = 0;
	XE::uint32 DstY = 0;
	XE::uint32 DstZ = 0;
	XE::uint32 Width = 0;
	XE::uint32 Height = 0;
	XE::uint32 Depth = 0;
	XE::uint32 SrcMip = 0;
	XE::uint32 DstMip = 0;
	TextureHandle Src;
	TextureHandle Dst;
};

class RenderCompute
{
public:
	XE::uint32 UniformBegin = 0;
	XE::uint32 UniformEnd = 0;
	XE::uint32 StartMatrix = 0;
	XE::IndirectBufferHandle IndirectBuffer;

	XE::uint32 NumX = 0;
	XE::uint32 NumY = 0;
	XE::uint32 NumZ = 0;
	XE::uint16 StartIndirect = 0;
	XE::uint16 NumIndirect = 0;
	XE::uint16 NumMatrices = 0;
	XE::uint8  SubmitFlags = 0;
	XE::uint8  UniformIdx = 0;
};

class RenderItem
{
public:
	enum class ItemType
	{
		RENDERDRAW,
		RENDERCOMPUTE,
	};

public:
	RenderItem()
	{

	}

	~RenderItem()
	{

	}

public:
	ItemType Type;
	union
	{
		RenderDraw Draw;
		RenderCompute Compute;
	};
};

class Frame
{
public:
	void Reset();

public:
	XE::Buffer PrevCmd;

	XE::uint64 RenderOcclusionSize = 0;
	std::array<XE::int32, GFX_MAX_OCCLUSION> Occlusion = {};

	XE::uint64 RenderBindSize = 0;
	std::array<RenderBind, GFX_MAX_DRAW_CALLS> RenderBinds = {};

	XE::uint64 RenderItemSize = 0;
	std::array<RenderItem, GFX_MAX_DRAW_CALLS> RenderItems = {};
	std::array<XE::uint64, GFX_MAX_DRAW_CALLS> RenderItemKeys = {};

	XE::uint64 RenderBlitSize = 0;
	std::array<RenderBlit, GFX_MAX_DRAW_CALLS> RenderBlits = {};
	std::array<XE::uint64, GFX_MAX_DRAW_CALLS> RenderBlitKeys = {};

	XE::Buffer PostCmd;
};

END_XE_NAMESPACE

#endif // STRUCTS_H__F731AAF0_BE7D_47A2_BCEC_5E0622CFE54D
