/*!
 * \file   Type.h
 *
 * \author ZhengYuanQing
 * \date   2019/1/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
#define __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848

#include "Global.h"

BEG_XE_NAMESPACE

DECL_PTR( Mesh );
DECL_PTR( Light );
DECL_PTR( Camera );
DECL_PTR( Renderer );
DECL_PTR( Skeleton );
DECL_PTR( RenderPass );
DECL_PTR( Renderable );
DECL_PTR( RenderWindow );
DECL_PTR( RenderMaterial );

enum class StateWrite : XE::uint64
{
	R = 0x0000000000000001,
	G = 0x0000000000000002,
	B = 0x0000000000000004,
	A = 0x0000000000000008,
	Z = 0x0000004000000000,
	RGB = R | G | B,
};
DECL_META_ENUM( XE_API, StateWrite );

enum class StateDepthTest : XE::uint64
{
	LESS = 0x0000000000000010,
	LEQUAL = 0x0000000000000020,
	EQUAL = 0x0000000000000030,
	GEQUAL = 0x0000000000000040,
	GREATER = 0x0000000000000050,
	NOTEQUAL = 0x0000000000000060,
	NEVER = 0x0000000000000070,
	ALWAYS = 0x0000000000000080,
};
DECL_META_ENUM( XE_API, StateDepthTest );

enum class StateBlendFunc : XE::uint64
{
	ZERO = 0x0000000000001000,
	ONE = 0x0000000000002000,
	SRC_COLOR = 0x0000000000003000,
	INV_SRC_COLOR = 0x0000000000004000,
	SRC_ALPHA = 0x0000000000005000,
	INV_SRC_ALPHA = 0x0000000000006000,
	DST_ALPHA = 0x0000000000007000,
	INV_DST_ALPHA = 0x0000000000008000,
	DST_COLOR = 0x0000000000009000,
	INV_DST_COLOR = 0x000000000000a000,
	SRC_ALPHA_SAT = 0x000000000000b000,
	FACTOR = 0x000000000000c000,
	INV_FACTOR = 0x000000000000d000,
};
DECL_META_ENUM( XE_API, StateBlendFunc );

enum class StateBlendEquation : XE::uint64
{
	ADD = 0x0000000000000000,
	SUB = 0x0000000010000000,
	REVSUB = 0x0000000020000000,
	MIN = 0x0000000030000000,
	MAX = 0x0000000040000000,
};
DECL_META_ENUM( XE_API, StateBlendEquation );

enum class StateCull : XE::uint64
{
	CW = 0x0000001000000000,
	CCW = 0x0000002000000000,
};
DECL_META_ENUM( XE_API, StateCull );

enum class StateTopologyType : XE::uint64
{
	TRISTRIP = 0x0001000000000000,
	LINES = 0x0002000000000000,
	LINESTRIP = 0x0003000000000000,
	POINTS = 0x0004000000000000,
};
DECL_META_ENUM( XE_API, StateTopologyType );

enum class StateMSAA : XE::uint64
{
	MSAA = 0x0100000000000000,
	LINEAA = 0x0200000000000000,
	CONSERVATIVE_RASTER = 0x0400000000000000,
	NONE = 0x0000000000000000,
	BLEND_INDEPENDENT = 0x0000000400000000,
	BLEND_ALPHA_TO_COVERAGE = 0x0000000800000000,
};
DECL_META_ENUM( XE_API, StateMSAA );

enum class StencilFlags : XE::uint64
{
	NONE = 0x00000000,
	TEST_LESS = 0x00010000,
	TEST_LEQUAL = 0x00020000,
	TEST_EQUAL = 0x00030000,
	TEST_GEQUAL = 0x00040000,
	TEST_GREATER = 0x00050000,
	TEST_NOTEQUAL = 0x00060000,
	TEST_NEVER = 0x00070000,
	TEST_ALWAYS = 0x00080000,
	FAIL_S_ZERO = 0x00000000,
	FAIL_S_KEEP = 0x00100000,
	FAIL_S_REPLACE = 0x00200000,
	FAIL_S_INCR = 0x00300000,
	FAIL_S_INCRSAT = 0x00400000,
	FAIL_S_DECR = 0x00500000,
	FAIL_S_DECRSAT = 0x00600000,
	FAIL_S_INVERT = 0x00700000,
	FAIL_Z_ZERO = 0x00000000,
	FAIL_Z_KEEP = 0x01000000,
	FAIL_Z_REPLACE = 0x02000000,
	FAIL_Z_INCR = 0x03000000,
	FAIL_Z_INCRSAT = 0x04000000,
	FAIL_Z_DECR = 0x05000000,
	FAIL_Z_DECRSAT = 0x06000000,
	FAIL_Z_INVERT = 0x07000000,
	PASS_Z_ZERO = 0x00000000,
	PASS_Z_KEEP = 0x10000000,
	PASS_Z_REPLACE = 0x20000000,
	PASS_Z_INCR = 0x30000000,
	PASS_Z_INCRSAT = 0x40000000,
	PASS_Z_DECR = 0x50000000,
	PASS_Z_DECRSAT = 0x60000000,
	PASS_Z_INVERT = 0x70000000,
};
DECL_META_ENUM( XE_API, StencilFlags );

enum class ClearFlags : XE::uint64
{
	NONE = 0x0000,
	COLOR = 0x0001,
	DEPTH = 0x0002,
	STENCIL = 0x0004,
	COLOR_DEPTH = COLOR | DEPTH,
	DEPTH_STENCIL = DEPTH | STENCIL,
	COLOR_STENCIL = COLOR | STENCIL,
	COLOR_DEPTH_STENCIL = COLOR | DEPTH | STENCIL,
	DISCARD_COLOR_0 = 0x0008,
	DISCARD_COLOR_1 = 0x0010,
	DISCARD_COLOR_2 = 0x0020,
	DISCARD_COLOR_3 = 0x0040,
	DISCARD_COLOR_4 = 0x0080,
	DISCARD_COLOR_5 = 0x0100,
	DISCARD_COLOR_6 = 0x0200,
	DISCARD_COLOR_7 = 0x0400,
	DISCARD_DEPTH = 0x0800,
	DISCARD_STENCIL = 0x1000,
};
DECL_META_ENUM( XE_API, ClearFlags );

enum class DebugFlags : XE::uint64
{
	NONE = 0x00000000,
	WIREFRAME = 0x00000001,
	IFH = 0x00000002,
	STATS = 0x00000004,
	TEXT = 0x00000008,
	PROFILER = 0x00000010,
};
DECL_META_ENUM( XE_API, DebugFlags );

enum class ComputeFormat : XE::uint64
{
	I8X1 = 0x0001 | 0x0010,
	I8X2 = 0x0002 | 0x0010,
	I8X4 = 0x0003 | 0x0010,
	I16X1 = 0x0004 | 0x0010,
	I16X2 = 0x0005 | 0x0010,
	I16X4 = 0x0006 | 0x0010,
	I32X1 = 0x0007 | 0x0010,
	I32X2 = 0x0008 | 0x0010,
	I32X4 = 0x0009 | 0x0010,
	U8X1 = 0x0001 | 0x0020,
	U8X2 = 0x0002 | 0x0020,
	U8X4 = 0x0003 | 0x0020,
	U16X1 = 0x0004 | 0x0020,
	U16X2 = 0x0005 | 0x0020,
	U16X4 = 0x0006 | 0x0020,
	U32X1 = 0x0007 | 0x0020,
	U32X2 = 0x0008 | 0x0020,
	U32X4 = 0x0009 | 0x0020,
	F8X1 = 0x0001 | 0x0030,
	F8X2 = 0x0002 | 0x0030,
	F8X4 = 0x0003 | 0x0030,
	F16X1 = 0x0004 | 0x0030,
	F16X2 = 0x0005 | 0x0030,
	F16X4 = 0x0006 | 0x0030,
	F32X1 = 0x0007 | 0x0030,
	F32X2 = 0x0008 | 0x0030,
	F32X4 = 0x0009 | 0x0030,
};
DECL_META_ENUM( XE_API, ComputeFormat );

enum class BufferUsage : XE::uint64
{
	NONE = 0x0000,
	COMPUTE_READ = 0x0100,
	COMPUTE_WRITE = 0x0200,
	DRAW_INDIRECT = 0x0400,
	ALLOW_RESIZE = 0x0800,
	INDEX32 = 0x1000,
	COMPUTE_READ_WRITE = COMPUTE_READ | COMPUTE_WRITE,
};
DECL_META_ENUM( XE_API, BufferUsage );

enum class TextureUsage : XE::uint64
{
	NONE = 0x0000000000000000,
	MSAA_SAMPLE = 0x0000000800000000,
	RT = 0x0000001000000000,
	COMPUTE_WRITE = 0x0000100000000000,
	SRGB = 0x0000200000000000,
	BLIT_DST = 0x0000400000000000,
	READ_BACK = 0x0000800000000000,
};
DECL_META_ENUM( XE_API, TextureUsage );

enum class RenderTargetMSAA : XE::uint64
{
	X2 = 0x0000002000000000,
	X4 = 0x0000003000000000,
	X8 = 0x0000004000000000,
	X16 = 0x0000005000000000,
	WRITE_ONLY = 0x0000008000000000,
};
DECL_META_ENUM( XE_API, RenderTargetMSAA );

enum class SamlerFlags : XE::uint64
{
	U_MIRROR = 0x00000001,
	U_CLAMP = 0x00000002,
	U_BORDER = 0x00000003,
	V_MIRROR = 0x00000004,
	V_CLAMP = 0x00000008,
	V_BORDER = 0x0000000c,
	W_MIRROR = 0x00000010,
	W_CLAMP = 0x00000020,
	W_BORDER = 0x00000030,
	MIN_POINT = 0x00000040,
	MIN_ANISOTROPIC = 0x00000080,
	MAG_POINT = 0x00000100,
	MAG_ANISOTROPIC = 0x00000200,
	MIP_POINT = 0x00000400,
	POINT = MIN_POINT | MAG_POINT | MIP_POINT,
	UVW_MIRROR = U_MIRROR | V_MIRROR | W_MIRROR,
	UVW_CLAMP = U_CLAMP | V_CLAMP | W_CLAMP,
	UVW_BORDER = U_BORDER | V_BORDER | W_BORDER,
	LESS = 0x00010000,
	LEQUAL = 0x00020000,
	EQUAL = 0x00030000,
	GEQUAL = 0x00040000,
	GREATER = 0x00050000,
	NOTEQUAL = 0x00060000,
	NEVER = 0x00070000,
	ALWAYS = 0x00080000,
};
DECL_META_ENUM( XE_API, SamlerFlags );

enum class ResetFlags : XE::uint64
{
	MSAAX2 = 0x00000010,
	MSAAX4 = 0x00000020,
	MSAAX8 = 0x00000030,
	MSAAX16 = 0x00000040,

	NONE = 0x00000000,
	FULLSCREEN = 0x00000001,
	VSYNC = 0x00000080,
	MAXANISOTROPY = 0x00000100,
	CAPTURE = 0x00000200,
	FLUSH_AFTER_RENDER = 0x00002000,
	FLIP_AFTER_RENDER = 0x00004000,
	SRGB_BACKBUFFER = 0x00008000,
	HDR10 = 0x00010000,
	HIDPI = 0x00020000,
	DEPTH_CLAMP = 0x00040000,
	SUSPEND = 0x00080000,
};
DECL_META_ENUM( XE_API, ResetFlags );

enum class CapsFlags : XE::uint64
{
	ALPHA_TO_COVERAGE = 0x0000000000000001,
	BLEND_INDEPENDENT = 0x0000000000000002,
	COMPUTE = 0x0000000000000004,
	CONSERVATIVE_RASTER = 0x0000000000000008,
	DRAW_INDIRECT = 0x0000000000000010,
	FRAGMENT_DEPTH = 0x0000000000000020,
	FRAGMENT_ORDERING = 0x0000000000000040,
	FRAMEBUFFER_RW = 0x0000000000000080,
	GRAPHICS_DEBUGGER = 0x0000000000000100,
	RESERVED = 0x0000000000000200,
	HDR10 = 0x0000000000000400,
	HIDPI = 0x0000000000000800,
	INDEX32 = 0x0000000000001000,
	INSTANCING = 0x0000000000002000,
	OCCLUSION_QUERY = 0x0000000000004000,
	RENDERER_MULTITHREADED = 0x0000000000008000,
	SWAP_CHAIN = 0x0000000000010000,
	TEXTURE_2D_ARRAY = 0x0000000000020000,
	TEXTURE_3D = 0x0000000000040000,
	TEXTURE_BLIT = 0x0000000000080000,
	TEXTURE_COMPARE_RESERVED = 0x0000000000100000,
	TEXTURE_COMPARE_LEQUAL = 0x0000000000200000,
	TEXTURE_CUBE_ARRAY = 0x0000000000400000,
	TEXTURE_DIRECT_ACCESS = 0x0000000000800000,
	TEXTURE_READ_BACK = 0x0000000001000000,
	VERTEX_ATTRIB_HALF = 0x0000000002000000,
	VERTEX_ATTRIB_UINT10 = 0x0000000004000000,
	VERTEX_ID = 0x0000000008000000,
	TEXTURE_COMPARE_ALL = TEXTURE_COMPARE_RESERVED | TEXTURE_COMPARE_LEQUAL,
};
DECL_META_ENUM( XE_API, CapsFlags );

enum class CapsFormat : XE::uint64
{
	TEXTURE_NONE = 0x0000,
	TEXTURE_2D = 0x0001,
	TEXTURE_2D_SRGB = 0x0002,
	TEXTURE_2D_EMULATED = 0x0004,
	TEXTURE_3D = 0x0008,
	TEXTURE_3D_SRGB = 0x0010,
	TEXTURE_3D_EMULATED = 0x0020,
	TEXTURE_CUBE = 0x0040,
	TEXTURE_CUBE_SRGB = 0x0080,
	TEXTURE_CUBE_EMULATED = 0x0100,
	TEXTURE_VERTEX = 0x0200,
	TEXTURE_IMAGE = 0x0400,
	TEXTURE_FRAMEBUFFER = 0x0800,
	TEXTURE_FRAMEBUFFER_MSAA = 0x1000,
	TEXTURE_MSAA = 0x2000,
	TEXTURE_MIP_AUTOGEN = 0x4000,
};
DECL_META_ENUM( XE_API, CapsFormat );

enum class PCIType : XE::int64
{
	NONE = 0x0000,
	SOFTWARE = 0x0001,
	AMD = 0x1002,
	INTEL = 0x8086,
	NVIDIA = 0x10de,
};
DECL_META_ENUM( XE_API, PCIType );

enum class CubeMap : XE::uint8
{
	POSITIVE_X = 0x00,
	NEGATIVE_X = 0x01,
	POSITIVE_Y = 0x02,
	NEGATIVE_Y = 0x03,
	POSITIVE_Z = 0x04,
	NEGATIVE_Z = 0x05,
};
DECL_META_ENUM( XE_API, CubeMap );

enum class Fatal
{
	DEBUG_CHECK,
	INVALID_SHADER,
	UNABLE_TO_INITIALIZE,
	UNABLE_TO_CREATE_TEXTURE,
	DEVICE_LOST,
};
DECL_META_ENUM( XE_API, Fatal );

enum class RendererType
{
	NOOP,
	DIRECT3D9,
	DIRECT3D11,
	DIRECT3D12,
	GNM,
	METAL,
	NVN,
	OPENGLES,
	OPENGL,
	VULKAN,
};
DECL_META_ENUM( XE_API, RendererType );

enum class Access
{
	READ,
	WRITE,
	READ_WRITE,
};
DECL_META_ENUM( XE_API, Access );

enum class Attrib : XE::uint16
{
	POSITION,
	NORMAL,
	TANGENT,
	BITANGENT,
	COLOR0,
	COLOR1,
	COLOR2,
	COLOR3,
	INDICES,
	WEIGHT,
	TEXCOORD0,
	TEXCOORD1,
	TEXCOORD2,
	TEXCOORD3,
	TEXCOORD4,
	TEXCOORD5,
	TEXCOORD6,
	TEXCOORD7,
};
DECL_META_ENUM( XE_API, Attrib );

enum class AttribType : XE::uint16
{
	UINT8,
	UINT10,
	INT16,
	HALF,
	FLOAT,
};
DECL_META_ENUM( XE_API, AttribType );

enum class TextureFormat
{
	BC1,
	BC2,
	BC3,
	BC4,
	BC5,
	BC6H,
	BC7,
	ETC1,
	ETC2,
	ETC2A,
	ETC2A1,
	PTC12,
	PTC14,
	PTC12A,
	PTC14A,
	PTC22,
	PTC24,
	ATC,
	ATCE,
	ATCI,
	ASTC4X4,
	ASTC5X5,
	ASTC6X6,
	ASTC8X5,
	ASTC8X6,
	ASTC10X5,

	UNKNOWN,

	R1,
	A8,
	R8,
	R8I,
	R8U,
	R8S,
	R16,
	R16I,
	R16U,
	R16F,
	R16S,
	R32I,
	R32U,
	R32F,
	RG8,
	RG8I,
	RG8U,
	RG8S,
	RG16,
	RG16I,
	RG16U,
	RG16F,
	RG16S,
	RG32I,
	RG32U,
	RG32F,
	RGB8,
	RGB8I,
	RGB8U,
	RGB8S,
	RGB9E5F,
	BGRA8,
	RGBA8,
	RGBA8I,
	RGBA8U,
	RGBA8S,
	RGBA16,
	RGBA16I,
	RGBA16U,
	RGBA16F,
	RGBA16S,
	RGBA32I,
	RGBA32U,
	RGBA32F,
	R5G6B5,
	RGBA4,
	RGB5A1,
	RGB10A2,
	RG11B10F,

	UNKNOWNDEPTH,

	D16,
	D24,
	D24S8,
	D32,
	D16F,
	D24F,
	D32F,
	D0S8,
};
DECL_META_ENUM( XE_API, TextureFormat );

enum class UniformType
{
	SAMPLER,
	END,

	VEC4,
	MAT3,
	MAT4,
};
DECL_META_ENUM( XE_API, UniformType );

enum class BackbufferRatio
{
	EQUAL,
	HALF,
	QUARTER,
	EIGHTH,
	SIXTEENTH,
	DOUBLE,
};
DECL_META_ENUM( XE_API, BackbufferRatio );

enum class OcclusionQueryResult
{
	INVISIBLE,
	VISIBLE,
	NORESULT,
};
DECL_META_ENUM( XE_API, OcclusionQueryResult );

enum class Topology
{
	TRILIST,
	TRISTRIP,
	LINELIST,
	LINESTRIP,
	POINTLIST,
};
DECL_META_ENUM( XE_API, Topology );

enum class TopologyConvert
{
	TRILIST_FLIP_WINDING,
	TRISTRIP_FLIP_WINDING,
	TRILIST_TO_LINELIST,
	TRISTRIP_TO_TRILIST,
	LINESTRIP_TO_LINELIST,
};
DECL_META_ENUM( XE_API, TopologyConvert );

enum class TopologySort
{
	DIRECTIONFRONT_TO_BACKMIN,
	DIRECTIONFRONT_TO_BACKAVG,
	DIRECTIONFRONT_TO_BACKMAX,
	DIRECTIONBACK_TO_FRONTMIN,
	DIRECTIONBACK_TO_FRONTAVG,
	DIRECTIONBACK_TO_FRONTMAX,
	DISTANCEFRONT_TO_BACKMIN,
	DISTANCEFRONT_TO_BACKAVG,
	DISTANCEFRONT_TO_BACKMAX,
	DISTANCEBACK_TO_FRONTMIN,
	DISTANCEBACK_TO_FRONTAVG,
	DISTANCEBACK_TO_FRONTMAX,
};
DECL_META_ENUM( XE_API, TopologySort );

enum class ViewMode
{
	DEFAULT,
	SEQUENTIAL,
	DEPTHASCENDING,
	DEPTHDESCENDING,
};
DECL_META_ENUM( XE_API, ViewMode );


XE::uint64 StateDefault();

XE::uint64 StateAlphaRef( XE::uint64 val );

XE::uint64 StatePointSize( XE::uint64 val );

XE::uint64 StateStencilFuncRef( XE::uint64 val );

XE::uint64 StateStencilFuncRMask( XE::uint64 val );

XE::uint64 SamplerBorderColor( XE::uint64 val );

XE::uint64 BlendFunctionSeparate( StateBlendFunc srcRGB, StateBlendFunc dstRGB, StateBlendFunc srcA, StateBlendFunc dstA );

XE::uint64 BlendEquationSeparate( StateBlendEquation rgb, StateBlendEquation a );

XE::uint64 BlendAdditive();

XE::uint64 BlendAlpha();

XE::uint64 BlendDarken();

XE::uint64 BlendLighten();

XE::uint64 BlendMultiply();

XE::uint64 BlendNormal();

XE::uint64 BlendScreen();

XE::uint64 BlendLinearBurn();

XE::uint64 BlendFuncRT1( StateBlendFunc src, StateBlendFunc dst );

XE::uint64 BlendFuncRT2( StateBlendFunc src, StateBlendFunc dst );

XE::uint64 BlendFuncRT3( StateBlendFunc src, StateBlendFunc dst );

XE::uint64 BlendFuncRT1E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation );

XE::uint64 BlendFuncRT2E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation );

XE::uint64 BlendFuncRT3E( StateBlendFunc src, StateBlendFunc dst, StateBlendEquation equation );


DECL_HANDLE( XE_API, View );
DECL_HANDLE( XE_API, DynamicIndexBuffer );
DECL_HANDLE( XE_API, DynamicVertexBuffer );
DECL_HANDLE( XE_API, FrameBuffer );
DECL_HANDLE( XE_API, IndexBuffer );
DECL_HANDLE( XE_API, IndirectBuffer );
DECL_HANDLE( XE_API, OcclusionQuery );
DECL_HANDLE( XE_API, Program );
DECL_HANDLE( XE_API, Shader );
DECL_HANDLE( XE_API, Texture );
DECL_HANDLE( XE_API, Uniform );
DECL_HANDLE( XE_API, VertexBuffer );
DECL_HANDLE( XE_API, VertexLayout );


END_XE_NAMESPACE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
