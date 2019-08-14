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

DECL_PTR( Resource );

DECL_PTR( Buffer );
DECL_PTR( FrameBuffer );
DECL_PTR( IndexBuffer );
DECL_PTR( VertexBuffer );
DECL_PTR( UniformBuffer );
DECL_PTR( ComputeBuffer );
DECL_PTR( ConstantBuffer );
DECL_PTR( IndirectBuffer );
DECL_PTR( InstanceBuffer );
DECL_PTR( DepthStencilBuffer );
DECL_PTR( DynamicIndexBuffer );
DECL_PTR( DynamicVertexBuffer );

DECL_PTR( Shader );
DECL_PTR( HullShader );
DECL_PTR( PixelShader );
DECL_PTR( VertexShader );
DECL_PTR( DomainShader );
DECL_PTR( ComputeShader );
DECL_PTR( GeometryShader );

DECL_PTR( BlendState );
DECL_PTR( PipelineState );
DECL_PTR( RasterizerState );
DECL_PTR( DepthStencilState );
DECL_PTR( ComputePipelineState );
DECL_PTR( GraphicsPipelineState );

DECL_PTR( Texture );
DECL_PTR( Texture2D );
DECL_PTR( Texture3D );
DECL_PTR( TextureCube );
DECL_PTR( Texture2DArray );

DECL_PTR( Query );
DECL_PTR( TimerQuery );
DECL_PTR( OcclusionQuery );

DECL_PTR( RenderTarget );
DECL_PTR( RenderWindow );
DECL_PTR( RenderTexture2D );

DECL_PTR( Image );
DECL_PTR( Sampler );
DECL_PTR( Viewport );
DECL_PTR( InputLayout );
DECL_PTR( CommandList );
DECL_PTR( RenderContext );
DECL_PTR( UnorderedAccess );


DECL_HANDLE( RHI_API, Resource );
DECL_HANDLE( RHI_API, CommandList );
DECL_HANDLE( RHI_API, PipelineState );


enum class FillType
{
	WIRTEFRAME,
	SOLID,
};
DECL_META_ENUM( RHI_API, FillType );

enum class CullType
{
	NONE,
	FRONT,
	BACK,
};
DECL_META_ENUM( RHI_API, CullType );

enum class TopologyType
{
	UNDEFINED,
	POINTLIST,
	LINELIST,
	LINESTRIP,
	TRIANGLELIST,
	TRIANGLESTRIP,
	LINELIST_ADJ,
	LINESTRIP_ADJ,
	TRIANGLELIST_ADJ,
	TRIANGLESTRIP_ADJ,
	CONTROL_POINT_PATCHLIST_1,
	CONTROL_POINT_PATCHLIST_2,
	CONTROL_POINT_PATCHLIST_3,
	CONTROL_POINT_PATCHLIST_4,
	CONTROL_POINT_PATCHLIST_5,
	CONTROL_POINT_PATCHLIST_6,
	CONTROL_POINT_PATCHLIST_7,
};
DECL_META_ENUM( RHI_API, TopologyType );

enum class AccessType
{
	NONE = 0,
	READ,
	WIRTE,
	READWIRTE,
};
DECL_META_ENUM( RHI_API, AccessType );

enum class CompareType
{
	LESS,
	LEQUAL,
	EQUAL,
	GEQUAL,
	GREATER,
	NOTEQUAL,
	NEVER,
	ALWAYS,
};
DECL_META_ENUM( RHI_API, CompareType );

enum class AttributeType
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
DECL_META_ENUM( RHI_API, AttributeType );

enum class RenderContextType
{
	SOFT,
	METAL,
	VULKAN,
	OPENGL,
	OPENGLES2,
	OPENGLES3,
	DIRECT3D11,
	DIRECT3D12,
};
DECL_META_ENUM( RHI_API, RenderContextType );

enum class UniformType
{
	VEC4,
	MAT3,
	MAT4,
	SAMPLER,
	TEXTURE,
};
DECL_META_ENUM( RHI_API, UniformType );

enum class TextureType
{
	TEXTURE2D,
	TEXTURE3D,
	TEXTURECUBE,
};
DECL_META_ENUM( RHI_API, TextureType );

enum class LayoutFormat
{
	INT8,
	INT16,
	INT32,
	INT64,
	UINT8,
	UINT16,
	UINT32,
	UINT64,
	FLOAT16,
	FLOAT32,
	FLOAT64,
	VEC2,
	VEC3,
	VEC4,
	QUAT,
	RECT,
	MAT3,
	MAT4,
	COLOR,

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
DECL_META_ENUM( RHI_API, LayoutFormat );

enum class TextureFormat
{
	///       RGBA16S
	///       ^   ^ ^
	///       |   | +-- [ ]Unorm
	///       |   |     [F]loat
	///       |   |     [S]norm
	///       |   |     [I]nt
	///       |   |     [U]int
	///       |   +---- Number of bits per component
	///       +-------- Components

	BC1,          /// DXT1
	BC2,          /// DXT3
	BC3,          /// DXT5
	BC4,          /// LATC1/ATI1
	BC5,          /// LATC2/ATI2
	BC6H,         /// BC6H
	BC7,          /// BC7
	ETC1,         /// ETC1 RGB8
	ETC2,         /// ETC2 RGB8
	ETC2A,        /// ETC2 RGBA8
	ETC2A1,       /// ETC2 RGB8A1
	PTC12,        /// PVRTC1 RGB 2BPP
	PTC14,        /// PVRTC1 RGB 4BPP
	PTC12A,       /// PVRTC1 RGBA 2BPP
	PTC14A,       /// PVRTC1 RGBA 4BPP
	PTC22,        /// PVRTC2 RGBA 2BPP
	PTC24,        /// PVRTC2 RGBA 4BPP
	ATC,          /// ATC RGB 4BPP
	ATCE,         /// ATCE RGBA 8 BPP explicit alpha
	ATCI,         /// ATCI RGBA 8 BPP interpolated alpha
	ASTC4x4,      /// ASTC 4x4 8.0 BPP
	ASTC5x5,      /// ASTC 5x5 5.12 BPP
	ASTC6x6,      /// ASTC 6x6 3.56 BPP
	ASTC8x5,      /// ASTC 8x5 3.20 BPP
	ASTC8x6,      /// ASTC 8x6 2.67 BPP
	ASTC10x5,     /// ASTC 10x5 2.56 BPP

	UNKNOWN,      /// Compressed formats above.

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

	UNKNOWN_DEPTH, /// Depth formats below.

	D16,
	D24,
	D24S8,
	D32,
	D16F,
	D24F,
	D32F,
	D0S8,
};
DECL_META_ENUM( RHI_API, TextureFormat );

enum class SamplerFilter
{
	POINT,
	LINEAR,
	ANISOTROPIC,
	COMPARISON_POINT,
	COMPARISON_LINEAR,
	COMPARISON_ANISOTROPIC,
	MINIMUM_POINT,
	MINIMUM_LINEAR,
	MINIMUM_ANISOTROPIC,
	MAXIMUM_POINT,
	MAXIMUM_LINEAR,
	MAXIMUM_ANISOTROPIC,
	NUM_FILTERS,
};
DECL_META_ENUM( RHI_API, SamplerFilter );

enum class SamplerAddressType
{
	MIRROR,
	CLAMP,
	BORDER,
};
DECL_META_ENUM( RHI_API, SamplerAddressType );

enum class BlendFactor
{
	ZERO,
	ONE,
	SRC_COLOR,
	INV_SRC_COLOR,
	SRC_ALPHA,
	INV_SRC_ALPHA,
	DST_ALPHA,
	INV_DST_ALPHA,
	DST_COLOR,
	INV_DST_COLOR,
	SRC_ALPHA_SAT,
	FACTOR,
	INV_FACTOR,
};
DECL_META_ENUM( RHI_API, BlendFactor );

enum class BlendOperation
{
	ADD,
	SUB,
	REVSUB,
	MIN,
	MAX,
};
DECL_META_ENUM( RHI_API, BlendOperation );

enum class StencilOperation
{
	ZERO,
	KEEP,
	REPLACE,
	INCR,
	INCRSAT,
	DECR,
	DECRSAT,
	INVERT,
};
DECL_META_ENUM( RHI_API, StencilOperation );


enum class ClearType
{
	CLAER_DEPTH,
	CLAER_STENCIL,
	CLAER_DEPTH_STENCIL,
};

enum class TileCopyType
{
	NONE,
	NO_HAZARD,
	LINEAR_TO_SWIZZLED,
	SWIZZLED_TO_LINEAR,
};

enum class BarrierFlag
{
	NONE,
	BEG_ONLY,
	END_ONLY
};

enum class ResourceState
{
	COMMON = 0,
	VERTEX_AND_CONSTANT_BUFFER = 0x1,
	INDEX_BUFFER = 0x2,
	RENDER_TARGET = 0x4,
	UNORDERED_ACCESS = 0x8,
	DEPTH_WRITE = 0x10,
	DEPTH_READ = 0x20,
	NON_PIXEL_SHADER_RESOURCE = 0x40,
	PIXEL_SHADER_RESOURCE = 0x80,
	STREAM_OUT = 0x100,
	INDIRECT_ARGUMENT = 0x200,
	COPY_DEST = 0x400,
	COPY_SOURCE = 0x800,
	RESOLVE_DEST = 0x1000,
	RESOLVE_SOURCE = 0x2000,
	RAYTRACING_ACCELERATION_STRUCTURE = 0x400000,
	GENERIC_READ = ( ( ( ( ( 0x1 | 0x2 ) | 0x40 ) | 0x80 ) | 0x200 ) | 0x800 ),
	PRESENT = 0,
	PREDICATION = 0x200,
	VIDEO_DECODE_READ = 0x10000,
	VIDEO_DECODE_WRITE = 0x20000,
	VIDEO_PROCESS_READ = 0x40000,
	VIDEO_PROCESS_WRITE = 0x80000,
	VIDEO_ENCODE_READ = 0x200000,
	VIDEO_ENCODE_WRITE = 0x800000
};

enum class StripCutValue
{
	DISABLED ,
	FFFF,
	FFFFFFFF,
};

END_XE_NAMESPACE

#endif //__TYPE_H__6580A518_948A_4162_A63F_E02DCC393EC9
