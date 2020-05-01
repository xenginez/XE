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
static constexpr XE::uint32 MAX_OCCLUSION_QUERIES = 256;
static constexpr XE::uint32 MAX_VERTEXS = 4;
static constexpr XE::uint32 MAX_DRAW_CALLS = 65535;


class View
{
public:
	XE::Color color;
	XE::float32 depth;
	XE::uint8 stencil;
	XE::Rect rect;
	XE::Rect scissor;
	XE::Mat4 view;
	XE::Mat4 proj;
	ViewMode mode;
	FrameBufferHandle handle;
};

class RenderBind
{
	struct Binding
	{
		enum BindingType : XE::uint8
		{
			Image,
			IndexBuffer,
			VertexBuffer,
			Texture,

			Count
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
	struct Vertexs
	{
		VertexBufferHandle buffer_handle;
		VertexLayoutHandle layout_handle;
	};

	Vertexs vertexs[MAX_VERTEXS];
	XE::Flags<XE::StateFlag> StateFlags;
	XE::Flags <XE::StencilFlag> StencilFlags;
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

	XE::IndexBufferHandle    IndexBuffer;
	XE::VertexBufferHandle   InstanceDataBuffer;
	XE::IndirectBufferHandle IndirectBuffer;
	XE::OcclusionQueryHandle OcclusionQuery;
};

class RenderCompute
{
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
	RenderDraw draw;
	RenderCompute compute;
};

class Frame
{
	std::array<View, MAX_VIEW> Views;
	XE::FreeHandleAlloctor<XE::View, MAX_VIEW> ViewHandleAlloc;


};


END_XE_NAMESPACE

#endif // STRUCTS_H__F731AAF0_BE7D_47A2_BCEC_5E0622CFE54D
