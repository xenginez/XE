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
DECL_PTR( Fence );
DECL_PTR( Context );
DECL_PTR( Sampler );
DECL_PTR( Viewport );
DECL_PTR( SwapChain );
DECL_PTR( InputLayout );
DECL_PTR( CommandList );
DECL_PTR( UnorderedAccess );


DECL_HANDLE( RHI_API, Fence );
DECL_HANDLE( RHI_API, Query );
DECL_HANDLE( RHI_API, Sampler );
DECL_HANDLE( RHI_API, Viewport );
DECL_HANDLE( RHI_API, Resource );
DECL_HANDLE( RHI_API, SwapChain );
DECL_HANDLE( RHI_API, InputLayout );
DECL_HANDLE( RHI_API, FrameBuffer );
DECL_HANDLE( RHI_API, RenderTarget );
DECL_HANDLE( RHI_API, PipelineState );


DECL_ALLOCATOR_FRAME( FrameBuffer );


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

enum class DeviceType
{
	SOFT,
	WEBGL,
	METAL,
	VULKAN,
	OPENGL,
	OPENGLES3,
	DIRECT3D12,
};
DECL_META_ENUM( RHI_API, DeviceType );

enum class UniformType
{
	VEC4,
	MAT3,
	MAT4,
	Sampler,
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
	ZERO,						/// 0, 0, 0, 0
	ONE,						/// 1, 1, 1, 1
	SRC_COLOR,					/// Rs, Gs, Bs, As
	INV_SRC_COLOR,				/// 1-Rs, 1-Gs, 1-Bs, 1-As
	SRC_ALPHA,					/// As, As, As, As
	INV_SRC_ALPHA,				/// 1-As, 1-As, 1-As, 1-As
	DST_ALPHA,					/// Ad, Ad, Ad, Ad
	INV_DST_ALPHA,				/// 1-Ad, 1-Ad, 1-Ad ,1-Ad
	DST_COLOR,					/// Rd, Gd, Bd, Ad
	INV_DST_COLOR,				/// 1-Rd, 1-Gd, 1-Bd, 1-Ad
	SRC_ALPHA_SAT,				/// f, f, f, 1; f = min(As, 1-Ad)
	FACTOR,						/// Blend factor
	INV_FACTOR,					/// 1-Blend factor
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


enum ClearType
{
	CLAER_COLOR = 1 << 1,
	CLAER_DEPTH = 1 << 2,
	CLAER_STENCIL = 1 << 3,
};

enum LayerType
{
	RENDER_QUEUE_BACKGROUND = 0,
	RENDER_QUEUE_SKIES_EARLY = 5,
	RENDER_QUEUE_WORLD_GEOMETRY_1 = 25,
	RENDER_QUEUE_MAIN = 50,
	RENDER_QUEUE_WORLD_GEOMETRY_2 = 75,
	RENDER_QUEUE_SKIES_LATE = 95,
	RENDER_QUEUE_OVERLAY = 100,
};

END_XE_NAMESPACE

#endif //__TYPE_H__6580A518_948A_4162_A63F_E02DCC393EC9
