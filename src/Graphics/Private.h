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
	CREATE_INDIRECT_BUFFER,
	CREATE_OCCLUSION_QUERY,
	CREATE_DYNAMIC_INDEX_BUFFER,
	CREATE_DYNAMIC_VERTEX_BUFFER,

	READ_TEXTURE,
	UPDATE_TEXTURE,
	UPDATE_DYNAMIC_INDEX_BUFFER,
	UPDATE_DYNAMIC_VERTEX_BUFFER,

	END,

	DESTROY_SHADER,
	DESTROY_TEXTURE,
	DESTROY_PROGRAM,
	DESTROY_FRAMEBUFFER,
	DESTROY_INDEX_BUFFER,
	DESTROY_VERTEX_LAYOUT,
	DESTROY_VERTEX_BUFFER,
	DESTROY_INDIRECT_BUFFER,
	DESTROY_OCCLUSION_QUERY,
	DESTROY_DYNAMIC_INDEX_BUFFER,
	DESTROY_DYNAMIC_VERTEX_BUFFER,

	REQUEST_SCREEN_SHOT,
};

struct SortKey
{
	// SortKey Format
	//  view(2^8) draw(2^1) group(2^3) depth(2^32) program(2^20)
	// |----------------------------------------------------------------|
	// |               3               2               1               0|
	// |----------------------------------------------------------------|
	// |fedcba9876543210fedcba9876543210fedcba9876543210fedcba9876543210| Common
	// |vvvvvvvvdggg                                                    |
	// |       ^^  ^                                                    |
	// |       ||  |                                                    |
	// |  view-+|  +-group                                              |
	// |        +-draw                                                  |
	// |----------------------------------------------------------------| Draw - sort by depth
	// |           |ddddddddddddddddddddddddddddddddpppppppppppppppppppp|
	// |           |                               ^                   ^|
	// |           |                               |                   ||
	// |           |                         depth-+           program-+|
	// |           |                                                    |
	// |----------------------------------------------------------------| Draw - sort by program
	// |           |ppppppppppppppppppppdddddddddddddddddddddddddddddddd|
	// |           |                   ^                               ^|
	// |           |                   |                               ||
	// |           |                   +-program                 depth-+|
	// |           |                                                    |
	// |----------------------------------------------------------------| Compute
	// |           |ddddddddddddddddddddddddddddddddpppppppppppppppppppp|
	// |           |                               ^                   ^|
	// |           |                               |                   ||
	// |           |                               +-depth     program-+|
	// |           |                                                    |
	// |----------------------------------------------------------------| Blit
	// |           |                    dddddddddddddddddddddddddddddddd|
	// |           |                                                   ^|
	// |           |                                                   ||
	// |           |                               depth-+              |
	// |           |                                                    |
	// |----------------------------------------------------------------|
	//
public:
	static constexpr XE::uint64 VIEW_NUM_BITS = 8;
	static constexpr XE::uint64 DRAW_NUM_BITS = 1;
	static constexpr XE::uint64 GROUP_NUM_BITS = 3;
	static constexpr XE::uint64 DEPTH_NUM_BITS = 32;
	static constexpr XE::uint64 PROGRAM_NUM_BITS = 20;

	static constexpr XE::uint64 VIEW_MAX_VALUE = ( XE::uint64( 2 ) << ( VIEW_NUM_BITS - 1 ) ) - 1;
	static constexpr XE::uint64 DRAW_MAX_VALUE = ( XE::uint64( 2 ) << ( DRAW_NUM_BITS - 1 ) ) - 1;
	static constexpr XE::uint64 GROUP_MAX_VALUE = ( XE::uint64( 2 ) << ( GROUP_NUM_BITS - 1 ) ) - 1;
	static constexpr XE::uint64 DEPTH_MAX_VALUE = ( XE::uint64( 2 ) << ( DEPTH_NUM_BITS - 1 ) ) - 1;
	static constexpr XE::uint64 PROGRAM_MAX_VALUE = ( XE::uint64( 2 ) << ( PROGRAM_NUM_BITS - 1 ) ) - 1;

public:
	static bool EncodeDraw( XE::uint64 & key, XE::ViewHandle view, XE::RenderGroup group, XE::ProgramHandle program, XE::uint32 depth )
	{
		if( view > VIEW_MAX_VALUE || XE::uint64( group ) > GROUP_MAX_VALUE || program > PROGRAM_MAX_VALUE || depth > DEPTH_MAX_VALUE )
		{
			return false;
		}

		key = 0;

		key |= XE::uint64( view ) << ( 64 - VIEW_NUM_BITS );
		key |= XE::uint64( 1 ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS );
		key |= XE::uint64( group ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS );

		switch( group )
		{
		case XE::RenderGroup::GEOMETRY:
		case XE::RenderGroup::GEOMETRYLAST:
			key |= XE::uint64( program ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - PROGRAM_NUM_BITS );
			key |= XE::uint64( depth ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - PROGRAM_NUM_BITS - DEPTH_NUM_BITS );
			break;
		case XE::RenderGroup::ALPHATEST:
		case XE::RenderGroup::BACKGROUND:
		case XE::RenderGroup::TRANSPARENT:
		case XE::RenderGroup::OVERLAY:
			key |= XE::uint64( depth ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS );
			key |= XE::uint64( program ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS - PROGRAM_NUM_BITS );
			break;
		default:
			break;
		}

		return true;
	}

	static bool EncodeCompute( XE::uint64 & key, XE::ViewHandle view, XE::ProgramHandle program, XE::uint32 depth )
	{
		if( view > VIEW_MAX_VALUE || program > PROGRAM_MAX_VALUE || depth > DEPTH_MAX_VALUE )
		{
			return false;
		}

		key = 0;

		key |= XE::uint64( view ) << ( 64 - VIEW_NUM_BITS );
//		key |= XE::uint64( 0 ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS );
//		key |= XE::uint64( 0 ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS );
		key |= XE::uint64( depth ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS );
		key |= XE::uint64( program ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS - PROGRAM_NUM_BITS );

		return true;
	}

	static bool EncodeBlit( XE::uint64 & key, XE::ViewHandle view, XE::uint32 depth )
	{
		if( view > VIEW_MAX_VALUE || depth > DEPTH_MAX_VALUE )
		{
			return false;
		}

		key = 0;

		key |= XE::uint64( view ) << ( 64 - VIEW_NUM_BITS );
//		key |= XE::uint64( 0 ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS );
//		key |= XE::uint64( 0 ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS );
//		key |= XE::uint64( 0 ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - PROGRAM_NUM_BITS );
		key |= XE::uint64( depth ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - PROGRAM_NUM_BITS - DEPTH_NUM_BITS );

		return true;
	}

public:
	static bool DecodeDraw( XE::uint64 key, XE::ViewHandle & view, XE::RenderGroup & group, XE::ProgramHandle & program, XE::uint32 & depth )
	{
		if( ( key & ( XE::uint64( DRAW_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS ) ) ) != 1 )
		{
			return false;
		}

		view = key & ( XE::uint64( VIEW_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS ) );
		group = ( XE::RenderGroup )( key & ( XE::uint64( GROUP_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS ) ) );

		switch( group )
		{
		case XE::RenderGroup::GEOMETRY:
		case XE::RenderGroup::GEOMETRYLAST:
			program = key & ( XE::uint64( PROGRAM_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - PROGRAM_NUM_BITS ) );
			depth = key & ( XE::uint64( DEPTH_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - PROGRAM_NUM_BITS - DEPTH_NUM_BITS ) );
			break;
		case XE::RenderGroup::ALPHATEST:
		case XE::RenderGroup::BACKGROUND:
		case XE::RenderGroup::TRANSPARENT:
		case XE::RenderGroup::OVERLAY:
			depth = key & ( XE::uint64( DEPTH_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS ) );
			program = key & ( XE::uint64( PROGRAM_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS - PROGRAM_NUM_BITS ) );
			break;
		default:
			break;
		}

		return true;
	}

	static bool DecodeCompute( XE::uint64 key, XE::ViewHandle & view, XE::ProgramHandle & program, XE::uint32 & depth )
	{
		if( ( key & ( XE::uint64( DRAW_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS ) ) ) != 0 ||
			( key & ( XE::uint64( GROUP_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS ) ) ) != 0 )
		{
			return false;
		}

		view = key & ( XE::uint64( VIEW_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS ) );
		depth = key & ( XE::uint64( DEPTH_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS ) );
		program = key & ( XE::uint64( PROGRAM_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS - PROGRAM_NUM_BITS ) );

		return true;
	}

	static bool DecodeBlit( XE::uint64 key, XE::ViewHandle & view, XE::uint32 & depth )
	{
		if( ( key & ( XE::uint64( DRAW_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS ) ) ) != 0 ||
			( key & ( XE::uint64( GROUP_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS ) ) ) != 0 ||
			( key & ( XE::uint64( PROGRAM_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - PROGRAM_NUM_BITS ) ) ) != 0 )
		{
			return false;
		}

		view = key & ( XE::uint64( VIEW_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS ) );
		depth = key & ( XE::uint64( DEPTH_MAX_VALUE ) << ( 64 - VIEW_NUM_BITS - DRAW_NUM_BITS - GROUP_NUM_BITS - DEPTH_NUM_BITS ) );

		return true;
	}
};

struct GfxRefCount
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

struct PShader : public GfxRefCount
{
	XE::uint32 HashIn;
	XE::uint32 HashOut;
	XE::ShaderDesc Desc;
	XE::Array< UniformDesc > Uniforms;
};

struct PTexture : public GfxRefCount
{
	XE::TextureDesc Desc;
	XE::uint32 StorageSize = 0;
	XE::uint8 BitsPerPixel = 0;
	TextureFormat Format = TextureFormat::RGBA8;
};

struct PProgram : public GfxRefCount
{
	XE::ProgramDesc Desc;
};

struct PUniform
{
	XE::String Name;
	XE::uint32 Size;
	union
	{
		XE::int32 i;
		XE::uint32 u;
		XE::float32 f;
		const char * p;
	};
	XE::UniformType Type;
};

struct PFrameBuffer : public GfxRefCount
{
	XE::FrameBufferDesc Desc;
};

struct PIndexBuffer : public GfxRefCount
{
	XE::uint64 Handle;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
	XE::IndexBufferDesc Desc;
};

struct PVertexLayout : public GfxRefCount
{
	XE::VertexLayoutDesc Desc;
};

struct PVertexBuffer : public GfxRefCount
{
	XE::uint64 Handle;
	XE::uint32 StartVertex;
	XE::uint32 NumVertices;
	XE::VertexBufferDesc Desc;
};

struct PIndirectBuffer : public GfxRefCount
{
	XE::uint64 Handle;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
	XE::IndirectBufferDesc Desc;
};

struct POcclusionQuery : public GfxRefCount
{
	XE::OcclusionQueryDesc Desc;
	std::optional<XE::uint32> Value;
};

struct PDynamicIndexBuffer : public GfxRefCount
{
	XE::uint64 Handle;
	XE::uint32 StartIndex;
	XE::uint32 NumIndices;
	XE::DynamicIndexBufferDesc Desc;
};

struct PDynamicVertexBuffer : public GfxRefCount
{
	XE::uint64 Handle;
	XE::uint32 StartVertex;
	XE::uint32 NumVertices;
	XE::DynamicVertexBufferDesc Desc;
};


struct PView : public GfxRefCount
{
	XE::String Name;
	XE::Color ClearColor;
	XE::float32 ClearDepth = 0.0f;
	XE::uint8 ClearStencil = 1;
	XE::Flags<ClearFlags> Flags = ClearFlags::NONE;
	XE::Rectf ViewRect;
	XE::Rectf ViewScissor;
	XE::Mat4x4f ModelMat;
	XE::Mat4x4f ViewMat;
	XE::Mat4x4f ProjMat;
	ViewMode Mode = XE::ViewMode::DEFAULT;
	FrameBufferHandle Handle;
	XE::ViewDesc Desc;
};


struct RenderBlit
{
	void Reset();

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
	XE::ViewHandle Handle;
	XE::TextureHandle Src;
	XE::TextureHandle Dst;
};

struct RenderBind
{
	void Reset();

	enum BindType : XE::uint8
	{
		NONE,
		IMAGE,
		TEXTURE,
		INDEXBUFFER,
		VERTEXBUFFER,
		DYNAMICINDEXBUFFER,
		DYNAMICVERTEXBUFFER,
	};

	struct Binding
	{
		BindType Type;
		XE::uint8 Mip;
		XE::uint64 Handle;
		XE::Access Access;
		XE::uint32 SamplerFlags;
		XE::TextureFormat Format;
	};

	std::array<Binding, GFX_MAX_TEXTURE_SAMPLERS> Binds;
};

struct RenderDraw
{
	void Reset();

	bool IsDynamicIndices = false;
	PIndexBuffer Indices = {};
	std::array<PUniform, GFX_MAX_UNIFORMS> Uniforms = {};
	std::array<bool, GFX_MAX_VERTEXS> IsDynamicVertices = {};
	std::array<PVertexBuffer, GFX_MAX_VERTEXS> Vertices = {};

	XE::Color Rgba = XE::Color::Black;

	XE::uint32 StartMatrix = 0;
	XE::uint16 NumMatrices = 0;

	XE::uint32 InstanceDataOffset = 0;
	XE::uint32 NumInstances = 0;

	XE::uint16 StartIndirect = 0;
	XE::uint16 NumIndirect = 0;

	XE::Rectf Scissor = XE::Rectf::Zero;
	XE::uint8 SubmitFlags = 0;
	XE::uint8 StreamMask = 0;

	XE::ProgramHandle Program;

	bool IsDynamicInstanceDataBuffer = false;
	XE::VertexBufferHandle InstanceDataBuffer;

	XE::IndirectBufferHandle IndirectBuffer;

	XE::OcclusionQueryHandle OcclusionQuery;

	XE::Flags<XE::StateFlags> StateFlags = XE::StateFlags::NONE;
	XE::Flags<XE::StencilFlags> FrontStencilFlags = XE::StencilFlags::NONE;
	XE::Flags<XE::StencilFlags> BackStencilFlags = XE::StencilFlags::NONE;
};

struct RenderCompute
{
	void Reset();

	XE::uint32 StartMatrix = 0;
	XE::uint32 NumMatrices = 0;

	XE::uint32 StartIndirect = 0;
	XE::uint32 NumIndirect = 0;

	XE::uint32 NumX = 0;
	XE::uint32 NumY = 0;
	XE::uint32 NumZ = 0;

	XE::ProgramHandle Program;

	XE::IndirectBufferHandle IndirectBuffer;

	std::array<XE::PUniform, GFX_MAX_UNIFORMS> Uniforms = {};
};

struct RenderItem
{
	XE::uint8 Data[std::max( sizeof( RenderDraw ), sizeof( RenderCompute ) )];
};

struct RenderFrame
{
public:
	void Reset();

public:
	XE::Buffer PrevCmd;
	std::mutex PrevCmdMutex;

	std::atomic<XE::uint32> UniformsSize = 0;
	std::array<XE::PUniform, GFX_MAX_UNIFORMS> Uniforms = {};

	std::atomic<XE::uint32> TransformsSize = 0;
	std::array<XE::Mat4x4f, GFX_MAX_TRANSFORM> Transforms = {};

	std::atomic<XE::uint32> RenderOcclusionSize = 0;
	std::array<XE::int32, GFX_MAX_OCCLUSION> Occlusions = {};

	std::atomic<XE::uint32> RenderItemSize = 0;
	std::array<XE::uint64, GFX_MAX_DRAWCALLS> RenderItemKeys = {};
	std::array<XE::RenderItem, GFX_MAX_DRAWCALLS> RenderItems = {};
	std::array<XE::RenderBind, GFX_MAX_DRAWCALLS> RenderBinds = {};

	std::atomic<XE::uint32> BlitItemSize = 0;
	std::array<XE::uint32, GFX_MAX_BLITITEMS> BlitItemKeys = {};
	std::array<XE::RenderBlit, GFX_MAX_BLITITEMS> BlitItems = {};

	XE::Buffer PostCmd;
	std::mutex PostCmdMutex;

	XE::Buffer TransientBuffers;
	std::mutex TransientBufferMutex;
};

END_XE_NAMESPACE

#endif // PRIVATE_H__D0889097_46CE_4E49_B998_1260127343E7
