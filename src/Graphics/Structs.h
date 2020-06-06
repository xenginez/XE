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

enum class ClearFlag
{
	NONE = 0,
	COLOR = 1,
	DEPTH = 2,
	STENCIL = 4,
};

enum class CommandType : XE::uint8
{
	RENDERER_INIT,
	RENDERER_SHUTDOWN,
	CREATE_VERTEX_LAYOUT,
	CREATE_INDEX_BUFFER,
	CREATE_VERTEX_BUFFER,
	CREATE_DYNAMIC_INDEX_BUFFER,
	UPDATE_DYNAMIC_INDEX_BUFFER,
	CREATE_DYNAMIC_VERTEX_BUFFER,
	UPDATE_DYNAMIC_VERTEX_BUFFER,
	CREATE_TRANSIENT_INDEX_BUFFER,
	CREATE_TRANSIENT_VERTEX_BUFFER,
	CREATE_SHADER,
	CREATE_PROGRAM,
	CREATE_TEXTURE,
	UPDATE_TEXTURE,
	RESIZE_TEXTURE,
	CREATE_FRAME_BUFFER,
	CREATE_UNIFORM,
	CREATE_OCCLUSION_QUERY,
	END,
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
	DESTROY_OCCLUSION_QUERY,
	REQUEST_SCREEN_SHOT,
};

// SortKey FORMAT
// 64bit:
//   00000000    00000000  000000000000000000000000 000000000000000000000000
//		|           |                 |                        |
//  view(2^8)  group(2^8)       program(2^24)              depth(2^24)
class SortKey
{
public:
	static constexpr XE::uint64 VIEW_LEFT_SHIFT = ( 64 - 8 );
	static constexpr XE::uint64 GROUP_LEFT_SHIFT = ( VIEW_LEFT_SHIFT - 8 );
	static constexpr XE::uint64 PROGRAM_LEFT_SHIFT = ( GROUP_LEFT_SHIFT - 24 );
	static constexpr XE::uint64 DEPTH_LEFT_SHIFT = 0;

	static constexpr XE::uint64 MAX_VIEW = 255;
	static constexpr XE::uint64 MAX_GROUP = 255;
	static constexpr XE::uint64 MAX_PROGRAM = 16777215;
	static constexpr XE::uint64 MAX_DEPTH = 16777215;

public:
	SortKey();

	SortKey( XE::uint64 val );

	SortKey( const SortKey & val );

public:
	bool operator <( const SortKey& val ) const;

	bool operator >( const SortKey& val ) const;

	bool operator <=( const SortKey& val ) const;

	bool operator >=( const SortKey& val ) const;

	bool operator ==( const SortKey& val ) const;

	bool operator !=( const SortKey& val ) const;

public:
	XE::uint8 GetView() const;

	void SetView( XE::uint8 val );

	XE::uint8 GetGroup() const;

	void SetGroup( XE::uint8 val );

	XE::uint32 GetProgram() const;

	void SetProgram( XE::uint32 val );

	XE::uint32 GetDepth() const;

	void SetDepth( XE::uint32 val );

	XE::uint64 GetKey() const;

	void SetKey( XE::uint64 val );

private:
	XE::uint64 _Key;
};


class RefCount
{
public:
	virtual ~RefCount() = default;

public:
	XE::uint32 Inc();

	XE::uint32 Dec();

public:
	std::atomic_uint32_t Count = 0;
};

class Shader : public RefCount
{
public:
	XE::String Name;
	XE::uint32 HashIn;
	XE::uint32 HashOut;
	XE::Array< UniformHandle > Uniforms;
};

class Texture : public RefCount
{
public:
	XE::String Name;
	XE::uint32 StorageSize = 0;
	XE::uint16 Width = 0;
	XE::uint16 Height = 0;
	XE::uint16 Depth = 0;
	XE::uint16 NumLayers = 0;
	XE::uint8 NumMips = 0;
	XE::uint8 BitsPerPixel = 0;
	bool CubeMap = false;
	TextureFormat Format = TextureFormat::COUNT;
};

class Uniform : public RefCount
{
public:
	XE::String Name;
	XE::uint16 Num = 0;
	UniformType Type = UniformType::COUNT;
};

class Program : public RefCount
{
public:
	ShaderHandle VS;
	ShaderHandle FS;
	ShaderHandle CS;
};

class FrameBuffer : public RefCount
{
public:
	XE::String Name;
	WindowHandle Window;
	TextureHandle Textures[GFX_MAX_ATTACHMENTS];
};


class IndexBuffer
{
public:
	enum HandleType
	{
		INDEX,
		DYNAMIC,
		TRANSIENT,
	};

public:
	HandleType Type;
	XE::uint64 Handle;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
};

class VertexBuffer
{
public:
	enum HandleType
	{
		VERTEX,
		DYNAMIC,
		TRANSIENT,
	};

public:
	HandleType Type;
	XE::uint64 Handle;
	XE::uint32 StartVertex;
	XE::uint32 NumVertices;
	VertexLayoutHandle LayoutHandle;
};

class InstanceDataBuffer
{
public:
	XE::memory_view data;
	uint32_t offset = 0;
	uint32_t num = 0;
	uint16_t stride = 0;
	VertexBufferHandle handle;
};

class TransientIndexBuffer
{
public:
	XE::memory_view data;
	uint32_t startIndex = 0;
	IndexBufferHandle handle;
};

class TransientVertexBuffer
{
public:
	XE::memory_view data;
	uint32_t startVertex = 0;
	uint16_t stride = 0;
	VertexBufferHandle handle;
	VertexLayoutHandle layoutHandle;
};


class View
{
public:
	XE::String Name;
	XE::Color ClearColor;
	XE::float32 ClearDepth = 0.0f;
	XE::uint8 ClearStencil = 1;
	XE::Flags<ClearFlag> Flag = ClearFlag::NONE;
	XE::Rect ViewRect;
	XE::Rect ViewScissor;
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

	struct Binding
	{
		XE::uint32 SamplerFlags;
		XE::uint64 Handle;
		BindType Type;
		XE::TextureFormat Format;
		XE::Access Access;
		XE::uint8 Mip;
	};
	
	std::array<Binding, GFX_MAX_TEXTURE_SAMPLERS> Binds;
};

class RenderDraw
{
public:
	IndexBuffer Indices;
	VertexBuffer Vertices[GFX_MAX_VERTEXS];

	XE::Color Rgba;

	XE::uint32 UniformBegin;
	XE::uint32 UniformEnd;

	XE::uint32 StartMatrix;
	XE::uint16 NumMatrices;

	XE::uint32 InstanceDataOffset;
	XE::uint32 NumInstances;

	XE::uint16 StartIndirect;
	XE::uint16 NumIndirect;

	XE::Rect Scissor;
	XE::uint8 SubmitFlags;
	XE::uint8 StreamMask;

	XE::VertexBufferHandle InstanceDataBuffer;
	XE::DynamicVertexBufferHandle DynamicInstanceDataBuffer;

	XE::IndirectBufferHandle IndirectBuffer;

	XE::OcclusionQueryHandle OcclusionQuery;

	XE::Flags<XE::StateFlag> StateFlags = XE::StateFlag::NONE;
	XE::Flags <XE::StencilFlag> FrontStencilFlags = XE::StencilFlag::NONE;
	XE::Flags <XE::StencilFlag> BackStencilFlags = XE::StencilFlag::NONE;
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
	ViewHandle Handle;
	TextureHandle Src;
	TextureHandle Dst;
};

class RenderCompute
{
public:
	XE::uint32 UniformBegin = 0;
	XE::uint32 UniformEnd = 0;

	XE::uint32 StartMatrix = 0;
	XE::uint16 NumMatrices = 0;

	XE::uint16 StartIndirect = 0;
	XE::uint16 NumIndirect = 0;

	XE::uint32 NumX = 0;
	XE::uint32 NumY = 0;
	XE::uint32 NumZ = 0;

	XE::IndirectBufferHandle IndirectBuffer;
};

class RenderItem
{
public:
	enum class ItemType
	{
		DRAW,
		COMPUTE,
	};

public:
	RenderItem();

	RenderItem( RenderItem && val );

	RenderItem & operator=( RenderItem && val );

	~RenderItem();

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
	std::mutex PrevCmdMutex;

	std::atomic<XE::uint64> TransformsSize = 0;
	std::array<XE::Mat4, GFX_MAX_TRANSFORM> Transforms = {};

	std::atomic<XE::uint64> RenderOcclusionSize = 0;
	std::array<XE::int32, GFX_MAX_OCCLUSION> Occlusions = {};

	std::atomic<XE::uint64> RenderItemSize = 0;
	std::array<RenderItem, GFX_MAX_DRAW_CALLS> RenderItems = {};
	std::array<RenderBind, GFX_MAX_DRAW_CALLS> RenderBinds = {};
	std::array<XE::uint64, GFX_MAX_DRAW_CALLS> RenderItemKeys = {};

	std::atomic<XE::uint32> RenderBlitSize = 0;
	std::array<RenderBlit, GFX_MAX_DRAW_CALLS> RenderBlits = {};
	std::array<XE::uint32, GFX_MAX_DRAW_CALLS> RenderBlitKeys = {};

	std::array<TransientIndexBuffer, GFX_MAX_INDEX_BUFFERS> TransientIndexBufferView;
	XE::ConcurrentHandleAllocator<XE::TransientIndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  TransientIndexBufferHandleAlloc;

	std::array<TransientVertexBuffer, GFX_MAX_VERTEX_BUFFERS> TransientVertexBufferView;
	XE::ConcurrentHandleAllocator<XE::TransientVertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> TransientVertexBufferHandleAlloc;

	XE::Buffer PostCmd;
	std::mutex PostCmdMutex;

	XE::Buffer UniformBuffer;
	std::mutex UniformBufferMutex;

	XE::Buffer TransientBuffer;
	std::mutex TransientBufferMutex;
};

END_XE_NAMESPACE

#endif // STRUCTS_H__F731AAF0_BE7D_47A2_BCEC_5E0622CFE54D
