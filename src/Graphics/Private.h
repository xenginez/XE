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
#include <optional>

#include "Utils/Buffer.h"
#include "Utils/Platform.h"

#include "Type.h"

BEG_XE_NAMESPACE

enum class CommandType : XE::uint8
{
	RENDERER_INIT,
	RENDERER_SHUTDOWN,

	CREATE_SHADER,
	CREATE_PROGRAM,
	CREATE_TEXTURE,
	CREATE_FRAME_BUFFER,
	CREATE_INDEX_BUFFER,
	CREATE_VERTEX_LAYOUT,
	CREATE_VERTEX_BUFFER,
	CREATE_OCCLUSION_QUERY,
	CREATE_DYNAMIC_INDEX_BUFFER,
	CREATE_DYNAMIC_VERTEX_BUFFER,

	UPDATE_TEXTURE,
	UPDATE_DYNAMIC_INDEX_BUFFER,
	UPDATE_DYNAMIC_VERTEX_BUFFER,

	END,

	READ_TEXTURE,
	REQUEST_SCREEN_SHOT,
};

class SortKey
{
	// SortKey FORMAT
	// 64bit:
	//   00000000    00000000  000000000000000000000000 000000000000000000000000
	//		|           |                 |                        |
	//  view(2^8)  group(2^8)       program(2^24)              depth(2^24)
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


class GfxRefCount
{
public:
	virtual ~GfxRefCount() = default;

public:
	XE::uint32 Inc();

	XE::uint32 Dec();

	void Reset();

private:
	std::atomic<XE::uint32> _Count = 0;
};

class PShader : public GfxRefCount
{
public:
	PShader();

	PShader( const PShader & val );

	PShader & operator=( const PShader & val );

public:
	XE::uint32 HashIn;
	XE::uint32 HashOut;
	XE::ShaderDesc Desc;
	XE::Array< UniformDesc > Uniforms;
};

class PTexture : public GfxRefCount
{
public:
	PTexture();

	PTexture( const PTexture & val );

	PTexture & operator=( const PTexture & val );

public:
	XE::TextureDesc Desc;
	XE::uint32 StorageSize = 0;
	XE::uint8 BitsPerPixel = 0;
	TextureFormat Format = TextureFormat::RGBA8;
};

class PProgram : public GfxRefCount
{
public:
	PProgram();

	PProgram( const PProgram & val );

	PProgram & operator=( const PProgram & val );

public:
	XE::ProgramDesc Desc;
};

class PFrameBuffer : public GfxRefCount
{
public:
	PFrameBuffer();

	PFrameBuffer( const PFrameBuffer & val );

	PFrameBuffer & operator=( const PFrameBuffer & val );

public:
	XE::FrameBufferDesc Desc;
};

class PIndexBuffer : public GfxRefCount
{
public:
	enum HandleType
	{
		INDEX,
		DYNAMIC,
		TRANSIENT,
	};

public:
	PIndexBuffer();

	PIndexBuffer( const PIndexBuffer & val );

	PIndexBuffer & operator=( const PIndexBuffer & val );

public:
	HandleType Type;
	XE::uint64 Handle;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
	union
	{
		XE::IndexBufferDesc Desc;
		XE::DynamicIndexBufferDesc DDesc;
	};
};

class PVertexLayout : public GfxRefCount
{
public:
	PVertexLayout();

	PVertexLayout( const PVertexLayout & val );

	PVertexLayout & operator=( const PVertexLayout & val );

public:
	XE::VertexLayoutDesc Desc;
};

class PVertexBuffer : public GfxRefCount
{
public:
	enum HandleType
	{
		VERTEX,
		DYNAMIC,
		TRANSIENT,
	};

public:
	PVertexBuffer();

	PVertexBuffer( const PVertexBuffer & val );

	PVertexBuffer & operator=( const PVertexBuffer & val );

public:
	HandleType Type;
	XE::uint64 Handle;
	XE::uint32 StartVertex;
	XE::uint32 NumVertices;
	VertexLayoutHandle LayoutHandle;
	union
	{
		XE::VertexBufferDesc Desc;
		XE::DynamicVertexBufferDesc DDesc;
	};
};

class PIndirectBuffer : public GfxRefCount
{
public:
	PIndirectBuffer();

	PIndirectBuffer( const PIndirectBuffer & val );

	PIndirectBuffer & operator=( const PIndirectBuffer & val );

public:
	XE::uint64 Handle;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
	XE::IndirectBufferDesc Desc;
};

class POcclusionQuery : public GfxRefCount
{
public:
	std::optional<XE::uint32> Value;
	XE::OcclusionQueryDesc Desc;
};


class PView : public GfxRefCount
{
public:
	PView();

	PView( const PView & val );

	PView & operator=( const PView & val );

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
	XE::ViewDesc Desc;
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
	PIndexBuffer Indices;
	PVertexBuffer Vertices[GFX_MAX_VERTEXS];

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

class RenderFrame
{
public:
	void Reset();

public:
	XE::Buffer PrevCmd;
	std::mutex PrevCmdMutex;

	std::atomic<XE::uint64> RenderOcclusionSize = 0;
	std::array<XE::int32, GFX_MAX_OCCLUSION> Occlusions = {};

	std::atomic<XE::uint64> RenderItemSize = 0;
	std::array<RenderItem, GFX_MAX_DRAW_CALLS> RenderItems = {};
	std::array<RenderBind, GFX_MAX_DRAW_CALLS> RenderBinds = {};
	std::array<XE::uint64, GFX_MAX_DRAW_CALLS> RenderItemKeys = {};

	std::atomic<XE::uint32> RenderBlitSize = 0;
	std::array<RenderBlit, GFX_MAX_BLITITEMS> RenderBlits = {};
	std::array<XE::uint32, GFX_MAX_BLITITEMS> RenderBlitKeys = {};

	XE::Buffer PostCmd;
	std::mutex PostCmdMutex;

	XE::Buffer DestoryCmd;
	std::mutex DestoryCmdMutex;

	XE::Buffer TransientBuffers;
	std::mutex TransientBufferMutex;
};

END_XE_NAMESPACE

#endif // PRIVATE_H__D0889097_46CE_4E49_B998_1260127343E7
