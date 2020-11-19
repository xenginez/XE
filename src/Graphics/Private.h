/*!
 * \file	Private.h
 *
 * \author	ZhengYuanQing
 * \date	2020/07/25
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PRIVATE_H__D0889097_46CE_4E49_B998_1260127343E7
#define PRIVATE_H__D0889097_46CE_4E49_B998_1260127343E7

#include <mutex>

#include "Utils/Buffer.h"
#include "Utils/Platform.h"

#include "Type.h"

BEG_XE_NAMESPACE

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
	READ_TEXTURE,
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

	SortKey & operator=( const SortKey & val );

public:
	bool operator <( const SortKey & val ) const;

	bool operator >( const SortKey & val ) const;

	bool operator <=( const SortKey & val ) const;

	bool operator >=( const SortKey & val ) const;

	bool operator ==( const SortKey & val ) const;

	bool operator !=( const SortKey & val ) const;

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
	Shader();

	Shader( const Shader & val );

	Shader & operator=( const Shader & val );

public:
	XE::String Name;
	XE::uint32 HashIn;
	XE::uint32 HashOut;
	XE::Array< UniformHandle > Uniforms;
};

class Texture : public RefCount
{
public:
	Texture();

	Texture( const Texture & val );

	Texture & operator=( const Texture & val );

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
	Uniform();

	Uniform( const Uniform & val );

	Uniform & operator=( const Uniform & val );

public:
	XE::String Name;
	XE::uint16 Num = 0;
	UniformType Type = UniformType::COUNT;
};

class Program : public RefCount
{
public:
	Program();

	Program( const Program & val );

	Program & operator=( const Program & val );

public:
	ShaderHandle VS;
	ShaderHandle FS;
	ShaderHandle CS;
};

class FrameBuffer : public RefCount
{
public:
	FrameBuffer();

	FrameBuffer( const FrameBuffer & val );

	FrameBuffer & operator=( const FrameBuffer & val );

public:
	XE::String Name;
	WindowHandle Window;
	TextureHandle Textures[GFX_MAX_ATTACHMENTS];
};

class IndexBuffer : public RefCount
{
public:
	enum HandleType
	{
		INDEX,
		DYNAMIC,
		TRANSIENT,
	};

public:
	IndexBuffer();

	IndexBuffer( const IndexBuffer & val );

	IndexBuffer & operator=( const IndexBuffer & val );

public:
	HandleType Type;
	XE::uint64 Handle;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
};

class VertexBuffer : public RefCount
{
public:
	enum HandleType
	{
		VERTEX,
		DYNAMIC,
		TRANSIENT,
	};

public:
	VertexBuffer();

	VertexBuffer( const VertexBuffer & val );

	VertexBuffer & operator=( const VertexBuffer & val );

public:
	HandleType Type;
	XE::uint64 Handle;
	XE::uint32 StartVertex;
	XE::uint32 NumVertices;
	VertexLayoutHandle LayoutHandle;
};

class UniformBuffer : public RefCount
{
public:
	UniformBuffer();

	UniformBuffer( const UniformBuffer & val );

	UniformBuffer & operator=( const UniformBuffer & val );

};

class InstanceDataBuffer : public RefCount
{
public:
	InstanceDataBuffer();

	InstanceDataBuffer( const InstanceDataBuffer & val );

	InstanceDataBuffer & operator=( const InstanceDataBuffer & val );

public:
	XE::MemoryView data;
	uint32_t offset = 0;
	uint32_t num = 0;
	uint16_t stride = 0;
	VertexBufferHandle handle;
};

class TransientIndexBuffer : public RefCount
{
public:
	TransientIndexBuffer();

	TransientIndexBuffer( const TransientIndexBuffer & val );

	TransientIndexBuffer & operator=( const TransientIndexBuffer & val );

public:
	XE::MemoryView data;
	uint32_t startIndex = 0;
	IndexBufferHandle handle;
};

class TransientVertexBuffer : public RefCount
{
public:
	TransientVertexBuffer();

	TransientVertexBuffer( const TransientVertexBuffer & val );

	TransientVertexBuffer & operator=( const TransientVertexBuffer & val );

public:
	XE::MemoryView data;
	uint32_t startVertex = 0;
	uint16_t stride = 0;
	VertexBufferHandle handle;
	VertexLayoutHandle layoutHandle;
};

class PredefinedUniform
{
public:
	enum Type
	{
		VIEWRECT,
		VIEWTEXEL,
		VIEW,
		INVVIEW,
		PROJ,
		INVPROJ,
		VIEWPROJ,
		INVVIEWPROJ,
		MODEL,
		MODELVIEW,
		MODELVIEWPROJ,
		ALPHAREF,
		COUNT
	};

public:
	PredefinedUniform();

	PredefinedUniform( const PredefinedUniform & val );

	PredefinedUniform & operator=( const PredefinedUniform & val );

public:
	Type _Type;
	uint32_t _Loc;
	uint16_t _Count;
};

class View : public RefCount
{
public:
	View();

	View( const View & val );

	View & operator=( const View & val );

public:
	XE::String Name;
	XE::Color ClearColor;
	XE::float32 ClearDepth = 0.0f;
	XE::uint8 ClearStencil = 1;
	XE::Flags<ClearFlags> Flags = ClearFlags::NONE;
	XE::Rectf ViewRect;
	XE::Rectf ViewScissor;
	XE::Mat4f ModelMat;
	XE::Mat4f ViewMat;
	XE::Mat4f ProjMat;
	ViewMode Mode = XE::ViewMode::DEFAULT;
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

public:
	RenderBind();

	RenderBind( const RenderBind & val );

	RenderBind & operator=( const RenderBind & val );

public:
	std::array<Binding, GFX_MAX_TEXTURE_SAMPLERS> Binds;
};

class RenderDraw
{
public:
	RenderDraw();

	RenderDraw( const RenderDraw & val );

	RenderDraw & operator=( const RenderDraw & val );

public:
	IndexBuffer Indices;
	VertexBuffer Vertices[GFX_MAX_VERTEXS];

	XE::Color Rgba = XE::Color::Black;

	XE::uint32 UniformBegin = 0;
	XE::uint32 UniformEnd = 0;

	XE::uint32 StartMatrix = 0;
	XE::uint16 NumMatrices = 0;

	XE::uint32 InstanceDataOffset = 0;
	XE::uint32 NumInstances = 0;

	XE::uint16 StartIndirect = 0;
	XE::uint16 NumIndirect = 0;

	XE::Rectf Scissor = XE::Rectf::Zero;
	XE::uint8 SubmitFlags = 0;
	XE::uint8 StreamMask = 0;

	XE::VertexBufferHandle InstanceDataBuffer;
	XE::DynamicVertexBufferHandle DynamicInstanceDataBuffer;

	XE::IndirectBufferHandle IndirectBuffer;

	XE::OcclusionQueryHandle OcclusionQuery;

	XE::Flags<XE::StateFlags> StateFlags = XE::StateFlags::NONE;
	XE::Flags<XE::StencilFlags> FrontStencilFlags = XE::StencilFlags::NONE;
	XE::Flags<XE::StencilFlags> BackStencilFlags = XE::StencilFlags::NONE;
};

class RenderBlit
{
public:
	RenderBlit();

	RenderBlit( const RenderBlit & val );

	RenderBlit & operator=( const RenderBlit & val );

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
	RenderCompute();

	RenderCompute( const RenderCompute & val );

	RenderCompute & operator=( const RenderCompute & val );

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

	RenderItem( const RenderItem & val );

	RenderItem & operator=( const RenderItem & val );

	~RenderItem();

public:
	ItemType Type;
	union
	{
		RenderDraw Draw;
		RenderCompute Compute;
	};
};

class DestoryHandle
{
public:
	enum DestoryType
	{
		DESTROY_SHADER,
		DESTROY_TEXTURE,
		DESTROY_UNIFORM,
		DESTROY_PROGRAM,
		DESTROY_FRAMEBUFFER,
		DESTROY_INDEX_BUFFER,
		DESTROY_VERTEX_BUFFER,
		DESTROY_VERTEX_LAYOUT,
		DESTROY_OCCLUSION_QUERY,
		DESTROY_DYNAMIC_INDEX_BUFFER,
		DESTROY_DYNAMIC_VERTEX_BUFFER,
		DESTROY_TRANSIENT_INDEX_BUFFER,
		DESTROY_TRANSIENT_VERTEX_BUFFER,
	};

	DestoryType Type;
	union
	{
		XE::ShaderHandle					_ShaderHandle;
		XE::TextureHandle					_TextureHandle;
		XE::UniformHandle					_UniformHandle;
		XE::ProgramHandle					_ProgramHandle;
		XE::FrameBufferHandle				_FrameBufferHandle;
		XE::IndexBufferHandle				_IndexBufferHandle;
		XE::VertexBufferHandle				_VertexBufferHandle;
		XE::VertexLayoutHandle				_VertexLayoutHandle;
		XE::OcclusionQueryHandle			_OcclusionQueryHandle;
		XE::DynamicIndexBufferHandle		_DynamicIndexBufferHandle;
		XE::DynamicVertexBufferHandle		_DynamicVertexBufferHandle;
		XE::TransientIndexBufferHandle		_TransientIndexBufferHandle;
		XE::TransientVertexBufferHandle		_TransientVertexBufferHandle;
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
	std::array<XE::Mat4f, GFX_MAX_TRANSFORM> Transforms = {};

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

	XE::Buffer DestoryCmd;
	std::mutex DestoryCmdMutex;

	XE::Buffer UniformBuffers;
	std::mutex UniformBufferMutex;

	XE::Buffer TransientBuffers;
	std::mutex TransientBufferMutex;
};

END_XE_NAMESPACE

#endif // PRIVATE_H__D0889097_46CE_4E49_B998_1260127343E7
