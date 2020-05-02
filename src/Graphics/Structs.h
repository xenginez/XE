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

static constexpr XE::uint32 MAX_VIEW = 256;
static constexpr XE::uint32 MAX_VERTEX_LAYOUTS = 64;
static constexpr XE::uint32 MAX_INDEX_BUFFERS = 4096;
static constexpr XE::uint32 MAX_VERTEX_BUFFERS = 4096;
static constexpr XE::uint32 MAX_DYNAMIC_INDEX_BUFFERS = 4096;
static constexpr XE::uint32 MAX_DYNAMIC_VERTEX_BUFFERS = 4096;
static constexpr XE::uint32 MAX_SHADERS = 512;
static constexpr XE::uint32 MAX_TEXTURES = 4096;
static constexpr XE::uint32 MAX_TEXTURE_SAMPLERS = 16;
static constexpr XE::uint32 MAX_FRAME_BUFFERS = 128;
static constexpr XE::uint32 MAX_ATTACHMENTS = 8;
static constexpr XE::uint32 MAX_UNIFORMS = 512;
static constexpr XE::uint32 MAX_OCCLUSION = 256;
static constexpr XE::uint32 MAX_VERTEXS = 4;
static constexpr XE::uint32 MAX_DRAW_CALLS = 65535;
static constexpr XE::uint32 MAX_PROGRAMS = 512;


class View
{
public:
	XE::Color Color;
	XE::float32 Depth;
	XE::uint8 Stencil;
	XE::Rect Rect;
	XE::Rect Scissor;
	XE::Mat4 ViewMat;
	XE::Mat4 ProjMat;
	ViewMode Mode;
	FrameBufferHandle Handle;
};

class RenderBind
{
public:
	struct Binding
	{
		Binding()
		{

		}

		enum BindingType : XE::uint8
		{
			IMAGE,
			INDEXBUFFER,
			VERTEXBUFFER,
			TEXTURE,

			COUNT
		};

		XE::uint32 SamplerFlags;
		XE::uint16 Index;
		BindingType Type;
		XE::TextureFormat Format;
		XE::Access Access;
		XE::uint8 Mip;
	};
};

class RenderDraw
{
public:
	struct Vertexs
	{
		VertexBufferHandle buffer_handle;
		VertexLayoutHandle layout_handle;
	};

	std::array<Vertexs, MAX_VERTEXS> Vertexs;
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

union RenderItem
{
	RenderItem()
	{

	}

	~RenderItem()
	{

	}

	RenderDraw Draw;
	RenderCompute Compute;
};

class Frame
{
public:
	XE::uint64 RenderViewSize;
	std::array<View, MAX_VIEW> Views = {};

	XE::uint64 RenderOcclusionSize;
	std::array<XE::int32, MAX_OCCLUSION> Occlusion = {};

	XE::uint64 RenderBindSize;
	std::array<RenderBind, MAX_DRAW_CALLS> RenderBinds = {};

	XE::uint64 RenderItemSize;
	std::array<RenderItem, MAX_DRAW_CALLS> RenderItems = {};
	std::array<XE::uint64, MAX_DRAW_CALLS> RenderItemKeys = {};

	XE::uint64 RenderBlitSize;
	std::array<RenderBlit, MAX_DRAW_CALLS> RenderBlits = {};
	std::array<XE::uint64, MAX_DRAW_CALLS> RenderBlitKeys = {};

	XE::FreeHandleAlloctor<XE::View, MAX_VIEW> ViewHandleAlloc;
	XE::FreeHandleAlloctor<XE::ShaderHandle, MAX_SHADERS> ShaderHandleAlloc;
	XE::FreeHandleAlloctor<XE::ProgramHandle, MAX_PROGRAMS> ProgramHandleAlloc;
	XE::FreeHandleAlloctor<XE::TextureHandle, MAX_TEXTURES> TextureHandleAlloc;
	XE::FreeHandleAlloctor<XE::UniformHandle, MAX_UNIFORMS> UniformHandleAlloc;
	XE::FreeHandleAlloctor<XE::FrameBufferHandle, MAX_FRAME_BUFFERS> FrameBufferHandleAlloc;
	XE::FreeHandleAlloctor<XE::IndexBufferHandle, MAX_INDEX_BUFFERS>  IndexBufferHandleAlloc;
	XE::FreeHandleAlloctor<XE::VertexLayoutHandle, MAX_VERTEX_LAYOUTS> VertexLayoutHandleAlloc;
	XE::FreeHandleAlloctor<XE::VertexBufferHandle, MAX_VERTEX_BUFFERS> VertexBufferHandleAlloc;

	XE::Buffer PrevCmd;
	XE::Buffer PostCmd;
};

END_XE_NAMESPACE

#endif // STRUCTS_H__F731AAF0_BE7D_47A2_BCEC_5E0622CFE54D
