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

#include "Math/Math.h"
#include "Utils/Flags.hpp"
#include "Utils/Handle.hpp"
#include "Utils/Platform.h"

BEG_XE_NAMESPACE

struct RenderFrame;

DECL_PTR( Encoder );
DECL_PTR( RendererContext );

DECL_HANDLE( XE_API, View );
DECL_HANDLE( XE_API, Shader );
DECL_HANDLE( XE_API, Texture );
DECL_HANDLE( XE_API, Program );
DECL_HANDLE( XE_API, FrameBuffer );
DECL_HANDLE( XE_API, IndexBuffer );
DECL_HANDLE( XE_API, VertexBuffer );
DECL_HANDLE( XE_API, VertexLayout );
DECL_HANDLE( XE_API, IndirectBuffer );
DECL_HANDLE( XE_API, OcclusionQuery );
DECL_HANDLE( XE_API, DynamicIndexBuffer );
DECL_HANDLE( XE_API, DynamicVertexBuffer );

static constexpr XE::uint32 GFX_MAX_VIEW = 256;
static constexpr XE::uint32 GFX_MAX_VERTEXS = 4;
static constexpr XE::uint32 GFX_MAX_SHADERS = 512;
static constexpr XE::uint32 GFX_MAX_UNIFORMS = 64;
static constexpr XE::uint32 GFX_MAX_PROGRAMS = 512;
static constexpr XE::uint32 GFX_MAX_TEXTURES = 4096;
static constexpr XE::uint32 GFX_MAX_DESTORYS = 4096;
static constexpr XE::uint32 GFX_MAX_OCCLUSION = 256;
static constexpr XE::uint32 GFX_MAX_TRANSFORM = 256;
static constexpr XE::uint32 GFX_MAX_BLITITEMS = 1024;
static constexpr XE::uint32 GFX_MAX_DRAWCALLS = 16384;
static constexpr XE::uint32 GFX_MAX_ATTACHMENTS = 8;
static constexpr XE::uint32 GFX_MAX_BACK_BUFFERS = 4;
static constexpr XE::uint32 GFX_MAX_FRAME_BUFFERS = 128;
static constexpr XE::uint32 GFX_MAX_INDEX_BUFFERS = 4096;
static constexpr XE::uint32 GFX_MAX_VERTEX_BUFFERS = 4096;
static constexpr XE::uint32 GFX_MAX_VERTEX_LAYOUTS = 64;
static constexpr XE::uint32 GFX_MAX_TEXTURE_SAMPLERS = 16;
static constexpr XE::uint32 GFX_MAX_DRAW_INDIRECT_STRIDE = 32;
static constexpr XE::uint32 GFX_MAX_DRAW_INDIRECT_BUFFERS = 1024;
static constexpr XE::uint32 GFX_MAX_DYNAMIC_INDEX_BUFFERS = 1024;
static constexpr XE::uint32 GFX_MAX_DYNAMIC_VERTEX_BUFFERS = 1024;

enum class CapsFlag : XE::uint64
{
	NONE = 0X0000000000000000,
	ALPHA_TO_COVERAGE = 0x0000000000000001,
	BLEND_INDEPENDENT = 0x0000000000000002,
	COMPUTE = 0x0000000000000004,
	CONSERVATIVE_RASTER = 0x0000000000000008,
	DRAW_INDIRECT = 0x0000000000000010,
	FRAGMENT_DEPTH = 0x0000000000000020,
	FRAGMENT_ORDERING = 0x0000000000000040,
	GRAPHICS_DEBUGGER = 0x0000000000000080,
	HDR10 = 0x0000000000000100,
	HIDPI = 0x0000000000000200,
	IMAGE_RW = 0x0000000000000400,
	INDEX32 = 0x0000000000000800,
	INSTANCING = 0x0000000000001000,
	OCCLUSION_QUERY = 0x0000000000002000,
	RENDERER_MULTITHREADED = 0x0000000000004000,
	SWAP_CHAIN = 0x0000000000008000,
	TEXTURE_2D_ARRAY = 0x0000000000010000,
	TEXTURE_3D = 0x0000000000020000,
	TEXTURE_BLIT = 0x0000000000040000,
	TEXTURE_COMPARE_RESERVED = 0x0000000000080000,
	TEXTURE_COMPARE_LEQUAL = 0x0000000000100000,
	TEXTURE_CUBE_ARRAY = 0x0000000000200000,
	TEXTURE_DIRECT_ACCESS = 0x0000000000400000,
	TEXTURE_READ_BACK = 0x0000000000800000,
	VERTEX_ATTRIB_HALF = 0x0000000001000000,
	VERTEX_ATTRIB_UINT10 = 0x0000000002000000,
	VERTEX_ID = 0x0000000004000000,
	VIEWPORT_LAYER_ARRAY = 0x0000000008000000,
	TEXTURE_COMPARE_ALL = TEXTURE_COMPARE_RESERVED | TEXTURE_COMPARE_LEQUAL,
};
DECL_FLAGS( CapsFlag, CapsFlags );

enum class PciIdFlag : XE::uint64
{
	NONE = 0X0000,
	AMD = 0X1002,
	INTEL = 0X8086,
	NVIDIA = 0X10DE,
	SOFTWARERASTERIZER = 0X0001,
};
DECL_FLAGS( PciIdFlag, PciIdFlags );

enum class ResetFlag : XE::uint64
{
	NONE = 0X00000000,
	MSAAX2 = 0X00000010,
	MSAAX4 = 0X00000020,
	MSAAX8 = 0X00000030,
	MSAAX16 = 0X00000040,
	MSAASHIFT = 4,
	MSAAMASK = 0X00000070,
	FULLSCREEN = 0X00000001,
	VSYNC = 0X00000080,
	MAXANISOTROPY = 0X00000100,
	CAPTURE = 0X00000200,
	FLUSHAFTERRENDER = 0X00002000,
	FLIPAFTERRENDER = 0X00004000,
	SRGBBACKBUFFER = 0X00008000,
	HDR10 = 0X00010000,
	HIDPI = 0X00020000,
	DEPTHCLAMP = 0X00040000,
	SUSPEND = 0X00080000,
	FULLSCREENSHIFT = 0,
	FULLSCREENMASK = 0X00000001,
	RESERVEDSHIFT = 31,
	RESERVEDMASK = 0X80000000,
};
DECL_FLAGS( ResetFlag, ResetFlags );

enum class StateFlag : XE::uint64
{
	NONE = 0x0000000000000000,
	WRITER = 0x0000000000000001,
	WRITEG = 0x0000000000000002,
	WRITEB = 0x0000000000000004,
	WRITEA = 0x0000000000000008,
	WRITEZ = 0x0000004000000000,
	WRITERGB = 0x0000000000000007,
	WRITEMASK = 0x000000400000000F,
	DEPTHTESTLESS = 0x0000000000000010,
	DEPTHTESTLEQUAL = 0x0000000000000020,
	DEPTHTESTEQUAL = 0x0000000000000030,
	DEPTHTESTGEQUAL = 0x0000000000000040,
	DEPTHTESTGREATER = 0x0000000000000050,
	DEPTHTESTNOTEQUAL = 0x0000000000000060,
	DEPTHTESTNEVER = 0x0000000000000070,
	DEPTHTESTALWAYS = 0x0000000000000080,
	DEPTHTESTSHIFT = 4,
	DEPTHTESTMASK = 0x00000000000000F0,
	BLENDZERO = 0x0000000000001000,
	BLENDONE = 0x0000000000002000,
	BLENDSRCCOLOR = 0x0000000000003000,
	BLENDINVSRCCOLOR = 0x0000000000004000,
	BLENDSRCALPHA = 0x0000000000005000,
	BLENDINVSRCALPHA = 0x0000000000006000,
	BLENDDSTALPHA = 0x0000000000007000,
	BLENDINVDSTALPHA = 0x0000000000008000,
	BLENDDSTCOLOR = 0x0000000000009000,
	BLENDINVDSTCOLOR = 0x000000000000A000,
	BLENDSRCALPHASAT = 0x000000000000B000,
	BLENDFACTOR = 0x000000000000C000,
	BLENDINVFACTOR = 0x000000000000D000,
	BLENDSHIFT = 12,
	BLENDMASK = 0x000000000FFFF000,
	BLENDEQUATIONADD = 0x0000000000000000,
	BLENDEQUATIONSUB = 0x0000000010000000,
	BLENDEQUATIONREVSUB = 0x0000000020000000,
	BLENDEQUATIONMIN = 0x0000000030000000,
	BLENDEQUATIONMAX = 0x0000000040000000,
	BLENDEQUATIONSHIFT = 28,
	BLENDEQUATIONMASK = 0x00000003F0000000,
	CULLCW = 0x0000001000000000,
	CULLCCW = 0x0000002000000000,
	CULLSHIFT = 36,
	CULLMASK = 0x0000003000000000,
	ALPHAREFSHIFT = 40,
	ALPHAREFMASK = 0x0000FF0000000000,
	PTTRISTRIP = 0x0001000000000000,
	PTLINES = 0x0002000000000000,
	PTLINESTRIP = 0x0003000000000000,
	PTPOINTS = 0x0004000000000000,
	PTSHIFT = 48,
	PTMASK = 0x0007000000000000,
	POINTSIZESHIFT = 52,
	POINTSIZEMASK = 0x00F0000000000000,
	MSAA = 0x0100000000000000,
	LINEAA = 0x0200000000000000,
	CONSERVATIVERASTER = 0x0400000000000000,
	BLENDINDEPENDENT = 0x0000000400000000,
	BLENDALPHATOCOVERAGE = 0x0000000800000000,
	DEFAULT = 0x010000500000001F,
	MASK = 0xFFFFFFFFFFFFFFFF,
	RESERVEDSHIFT = 61,
	RESERVEDMASK = 0xE000000000000000,
};
DECL_FLAGS( StateFlag, StateFlags );

enum class ClearFlag : XE::uint64
{
	NONE = 0X0000,
	COLOR = 0X0001,
	DEPTH = 0X0002,
	STENCIL = 0X0004,
	DISCARDCOLOR0 = 0X0008,
	DISCARDCOLOR1 = 0X0010,
	DISCARDCOLOR2 = 0X0020,
	DISCARDCOLOR3 = 0X0040,
	DISCARDCOLOR4 = 0X0080,
	DISCARDCOLOR5 = 0X0100,
	DISCARDCOLOR6 = 0X0200,
	DISCARDCOLOR7 = 0X0400,
	DISCARDDEPTH = 0X0800,
	DISCARDSTENCIL = 0X1000,
	COLOR_USE_PALETTE = 0X8000,
	DISCARDCOLORMASK = 0X07F8,
	DISCARDMASK = 0X1FF8,
};
DECL_FLAGS( ClearFlag, ClearFlags );

enum class BufferFlag : XE::uint64
{
	NONE = 0X0000,
	COMPUTEFORMAT8X1 = 0X0001,
	COMPUTEFORMAT8X2 = 0X0002,
	COMPUTEFORMAT8X4 = 0X0003,
	COMPUTEFORMAT16X1 = 0X0004,
	COMPUTEFORMAT16X2 = 0X0005,
	COMPUTEFORMAT16X4 = 0X0006,
	COMPUTEFORMAT32X1 = 0X0007,
	COMPUTEFORMAT32X2 = 0X0008,
	COMPUTEFORMAT32X4 = 0X0009,
	COMPUTEFORMATSHIFT = 0,
	COMPUTEFORMATMASK = 0X000F,
	COMPUTETYPEINT = 0X0010,
	COMPUTETYPEUINT = 0X0020,
	COMPUTETYPEFLOAT = 0X0030,
	COMPUTETYPESHIFT = 4,
	COMPUTETYPEMASK = 0X0030,
	COMPUTEREAD = 0X0100,
	COMPUTEWRITE = 0X0200,
	DRAWINDIRECT = 0X0400,
	ALLOWRESIZE = 0X0800,
	INDEX32 = 0X1000,
	COMPUTEREADWRITE = 0X0300,
};
DECL_FLAGS( BufferFlag, BufferFlags );

enum class TextureFlag : XE::uint64
{
	NONE = 0X0000000000000000,
	MSAASAMPLE = 0X0000000800000000,
	RT = 0X0000001000000000,
	COMPUTEWRITE = 0X0000100000000000,
	SRGB = 0X0000200000000000,
	BLITDST = 0X0000400000000000,
	READBACK = 0X0000800000000000,
	RTMSAAX2 = 0X0000002000000000,
	RTMSAAX4 = 0X0000003000000000,
	RTMSAAX8 = 0X0000004000000000,
	RTMSAAX16 = 0X0000005000000000,
	RTMSAASHIFT = 36,
	RTMSAAMASK = 0X0000007000000000,
	RTWRITEONLY = 0X0000008000000000,
	RTSHIFT = 36,
	RTMASK = 0X000000F000000000,
};
DECL_FLAGS( TextureFlag, TextureFlags );

enum class SamplerFlag : XE::uint64
{
	NONE = 0X00000000,
	UMIRROR = 0X00000001,
	UCLAMP = 0X00000002,
	UBORDER = 0X00000003,
	USHIFT = 0,
	UMASK = 0X00000003,
	VMIRROR = 0X00000004,
	VCLAMP = 0X00000008,
	VBORDER = 0X0000000C,
	VSHIFT = 2,
	VMASK = 0X0000000C,
	WMIRROR = 0X00000010,
	WCLAMP = 0X00000020,
	WBORDER = 0X00000030,
	WSHIFT = 4,
	WMASK = 0X00000030,
	MINPOINT = 0X00000040,
	MINANISOTROPIC = 0X00000080,
	MINSHIFT = 6,
	MINMASK = 0X000000C0,
	MAGPOINT = 0X00000100,
	MAGANISOTROPIC = 0X00000200,
	MAGSHIFT = 8,
	MAGMASK = 0X00000300,
	MIPPOINT = 0X00000400,
	MIPSHIFT = 10,
	MIPMASK = 0X00000400,
	COMPARELESS = 0X00010000,
	COMPARELEQUAL = 0X00020000,
	COMPAREEQUAL = 0X00030000,
	COMPAREGEQUAL = 0X00040000,
	COMPAREGREATER = 0X00050000,
	COMPARENOTEQUAL = 0X00060000,
	COMPARENEVER = 0X00070000,
	COMPAREALWAYS = 0X00080000,
	COMPARESHIFT = 16,
	COMPAREMASK = 0X000F0000,
	BORDERCOLORSHIFT = 24,
	BORDERCOLORMASK = 0X0F000000,
	RESERVEDSHIFT = 28,
	RESERVEDMASK = 0XF0000000,
	SAMPLESTENCIL = 0X00100000,
	POINT = 0X00000540,
	UVWMIRROR = 0X00000015,
	UVWCLAMP = 0X0000002A,
	UVWBORDER = 0X0000003F,
	BITSMASK = 0X000F07FF,

	INTERNALDEFAULT = 0X10000000,
	INTERNALSHARED = 0x20000000,
};
DECL_FLAGS( SamplerFlag, SamplerFlags );

enum class StencilFlag : XE::uint64
{
	NONE = 0X00000000,
	FUNCREFSHIFT = 0,
	FUNCREFMASK = 0X000000FF,
	FUNCRMASKSHIFT = 8,
	FUNCRMASKMASK = 0X0000FF00,
	MASK = 0XFFFFFFFF,
	DEFAULT = 0X00000000,

	TESTLESS = 0X00010000,
	TESTLEQUAL = 0X00020000,
	TESTEQUAL = 0X00030000,
	TESTGEQUAL = 0X00040000,
	TESTGREATER = 0X00050000,
	TESTNOTEQUAL = 0X00060000,
	TESTNEVER = 0X00070000,
	TESTALWAYS = 0X00080000,
	TESTSHIFT = 16,
	TESTMASK = 0X000F0000,
	OPFAILSZERO = 0X00000000,
	OPFAILSKEEP = 0X00100000,
	OPFAILSREPLACE = 0X00200000,
	OPFAILSINCR = 0X00300000,
	OPFAILSINCRSAT = 0X00400000,
	OPFAILSDECR = 0X00500000,
	OPFAILSDECRSAT = 0X00600000,
	OPFAILSINVERT = 0X00700000,
	OPFAILSSHIFT = 20,
	OPFAILSMASK = 0X00F00000,
	OPFAILZZERO = 0X00000000,
	OPFAILZKEEP = 0X01000000,
	OPFAILZREPLACE = 0X02000000,
	OPFAILZINCR = 0X03000000,
	OPFAILZINCRSAT = 0X04000000,
	OPFAILZDECR = 0X05000000,
	OPFAILZDECRSAT = 0X06000000,
	OPFAILZINVERT = 0X07000000,
	OPFAILZSHIFT = 24,
	OPFAILZMASK = 0X0F000000,
	OPPASSZZERO = 0X00000000,
	OPPASSZKEEP = 0X10000000,
	OPPASSZREPLACE = 0X20000000,
	OPPASSZINCR = 0X30000000,
	OPPASSZINCRSAT = 0X40000000,
	OPPASSZDECR = 0X50000000,
	OPPASSZDECRSAT = 0X60000000,
	OPPASSZINVERT = 0X70000000,
	OPPASSZSHIFT = 28,
	OPPASSZMASK = 0XF0000000,
};
DECL_FLAGS( StencilFlag, StencilFlags );

enum class CubeMapFlag : XE::uint64
{
	NONE = 0X00000000,
	POSITIVEX = 0X00000000,
	NEGATIVEX = 0X00000001,
	POSITIVEY = 0X00000002,
	NEGATIVEY = 0X00000003,
	POSITIVEZ = 0X00000004,
	NEGATIVEZ = 0X00000005,
};
DECL_FLAGS( CubeMapFlag, CubeMapFlags );

enum class ResolveFlag : XE::uint64
{
	NONE = 0X00000000,
	AUTOGENMIPS = 0X00000001,
};
DECL_FLAGS( ResolveFlag, ResolveFlags );

enum class CapsFormatFlag : XE::uint64
{
	NONE = 0X0000,
	TEXTURE_2D = 0x00000001,
	TEXTURE_2D_SRGB = 0x00000002,
	TEXTURE_2D_EMULATED = 0x00000004,
	TEXTURE_3D = 0x00000008,
	TEXTURE_3D_SRGB = 0x00000010,
	TEXTURE_3D_EMULATED = 0x00000020,
	TEXTURE_CUBE = 0x00000040,
	TEXTURE_CUBE_SRGB = 0x00000080,
	TEXTURE_CUBE_EMULATED = 0x00000100,
	TEXTURE_VERTEX = 0x00000200,
	TEXTURE_IMAGE_READ = 0x00000400,
	TEXTURE_IMAGE_WRITE = 0x00000800,
	TEXTURE_FRAMEBUFFER = 0x00001000,
	TEXTURE_FRAMEBUFFER_MSAA = 0x00002000,
	TEXTURE_MSAA = 0x00004000,
	TEXTURE_MIP_AUTOGEN = 0x00008000,
};
DECL_FLAGS( CapsFormatFlag, CapsFormatFlags );

enum class AccessType
{
	READ,      //!< Read
	WRITE,     //!< Write
	READWRITE, //!< Read and write

	COUNT
};

enum class RendererContextType
{
	NONE,         // No rendering.
	NIL,          // Null
	HTML5,		  // HTML5
	D3D12,        // D3D 12
	METAL,        // Metal
	VULKAN,       // Vulkan
	SOFTWARE,	  // Software
};

enum class EncodingType
{
	UNORM,
	INT,
	UINT,
	FLOAT,
	SNORM,

	COUNT
};

enum class AttributeType
{
	UINT8,
	UINT10,
	INT16,
	HALF,
	FLOAT,

	COUNT
};

enum class AttributeName
{
	POSITION,  //!< a_position
	NORMAL,    //!< a_normal
	TANGENT,   //!< a_tangent
	BITANGENT, //!< a_bitangent
	COLOR0,    //!< a_color0
	COLOR1,    //!< a_color1
	COLOR2,    //!< a_color2
	COLOR3,    //!< a_color3
	INDICES,   //!< a_indices
	WEIGHT,    //!< a_weight
	TEXCOORD0, //!< a_texcoord0
	TEXCOORD1, //!< a_texcoord1
	TEXCOORD2, //!< a_texcoord2
	TEXCOORD3, //!< a_texcoord3
	TEXCOORD4, //!< a_texcoord4
	TEXCOORD5, //!< a_texcoord5
	TEXCOORD6, //!< a_texcoord6
	TEXCOORD7, //!< a_texcoord7

	COUNT
};

enum class UniformType
{
	INT,
	UINT,
	FLOAT,
	VEC2f,
	VEC3f,
	VEC4f,
	MAT3f,
	MAT4f,
	SAMPLER,
};

enum class TopologyType
{
	TRILIST,
	TRISTRIP,
	LINELIST,
	LINESTRIP,
	POINTLIST,

	COUNT
};

enum class TopologySort
{
	DIRECTIONFRONTTOBACKMIN,
	DIRECTIONFRONTTOBACKAVG,
	DIRECTIONFRONTTOBACKMAX,
	DIRECTIONBACKTOFRONTMIN,
	DIRECTIONBACKTOFRONTAVG,
	DIRECTIONBACKTOFRONTMAX,
	DISTANCEFRONTTOBACKMIN,
	DISTANCEFRONTTOBACKAVG,
	DISTANCEFRONTTOBACKMAX,
	DISTANCEBACKTOFRONTMIN,
	DISTANCEBACKTOFRONTAVG,
	DISTANCEBACKTOFRONTMAX,

	COUNT
};

enum class ViewMode
{
	DEFAULT,
	SEQUENTIAL,
	DEPTHASCENDING,
	DEPTHDESCENDING,

	COUNT
};

enum class TextureType
{
	TEXTURE_2D,
	TEXTURE_3D,
	TEXTURE_CUBE,
};

enum class TextureFormat
{
	BC1,          //!< DXT1 R5G6B5A1
	BC2,          //!< DXT3 R5G6B5A4
	BC3,          //!< DXT5 R5G6B5A8
	BC4,          //!< LATC1/ATI1 R8
	BC5,          //!< LATC2/ATI2 RG8
	BC6H,         //!< BC6H RGB16F
	BC7,          //!< BC7 RGB 4-7 bits per color channel, 0-8 bits alpha
	ETC1,         //!< ETC1 RGB8
	ETC2,         //!< ETC2 RGB8
	ETC2A,        //!< ETC2 RGBA8
	ETC2A1,       //!< ETC2 RGB8A1
	PTC12,        //!< PVRTC1 RGB 2BPP
	PTC14,        //!< PVRTC1 RGB 4BPP
	PTC12A,       //!< PVRTC1 RGBA 2BPP
	PTC14A,       //!< PVRTC1 RGBA 4BPP
	PTC22,        //!< PVRTC2 RGBA 2BPP
	PTC24,        //!< PVRTC2 RGBA 4BPP
	ATC,          //!< ATC RGB 4BPP
	ATCE,         //!< ATCE RGBA 8 BPP explicit alpha
	ATCI,         //!< ATCI RGBA 8 BPP interpolated alpha
	ASTC4x4,      //!< ASTC 4x4 8.0 BPP
	ASTC5x5,      //!< ASTC 5x5 5.12 BPP
	ASTC6x6,      //!< ASTC 6x6 3.56 BPP
	ASTC8x5,      //!< ASTC 8x5 3.20 BPP
	ASTC8x6,      //!< ASTC 8x6 2.67 BPP
	ASTC10x5,     //!< ASTC 10x5 2.56 BPP

	UNKNOWN,      // Compressed formats above.

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

	UNKNOWNDEPTH, // Depth formats below.

	D16,
	D24,
	D24S8,
	D32,
	D16F,
	D24F,
	D32F,
	D0S8,

	COUNT
};

enum class ComputeFormat
{
	INT8X1,
	INT8X2,
	INT8X4,
	INT16X1,
	INT16X2,
	INT16X4,
	INT32X1,
	INT32X2,
	INT32X4,
	UINT8X1,
	UINT8X2,
	UINT8X4,
	UINT16X1,
	UINT16X2,
	UINT16X4,
	UINT32X1,
	UINT32X2,
	UINT32X4,
	FLOAT8X1,
	FLOAT8X2,
	FLOAT8X4,
	FLOAT16X1,
	FLOAT16X2,
	FLOAT16X4,
	FLOAT32X1,
	FLOAT32X2,
	FLOAT32X4,
};

enum class BufferMode
{
	COMPUTE_READ,
	COMPUTE_WRITE,
	DRAW_INDIRECT,
	ALLOW_RESIZE,
	INDEX32,
};

enum class SamplerWrap
{
	MIRROR,
	CLAMP,
	BORDER,
};

enum class SamplerMode
{
	POINT,
	ANISOTROPIC,
};

enum class SamplerCompare
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

enum class ShaderType
{
	VS,
	FS,
	CS,
};

enum class RenderGroup : XE::uint8
{
	GEOMETRY = 0,			// opaque geometry uses this group.
	BACKGROUND = 1,			// this render group is rendered before any others.
	ALPHATEST = 2,			// alpha tested geometry uses this group.
	GEOMETRYLAST = 3,		// last render group that is considered "opaque".
	TRANSPARENT = 4,		// this render queue is rendered after Geometry and AlphaTest, in back-to-front order.
	OVERLAY = 5,			// this render group is meant for overlay effects.
};

struct XE_API CapsInfo
{
public:
	RendererContextType ContextType = RendererContextType::NONE;

	XE::CapsFlags Supported;
	XE::CapsFormatFlags SupportFormat[( XE::uint64 )XE::TextureFormat::COUNT];

	PciIdFlag VendorId = PciIdFlag::NONE;
	XE::uint16 DeviceId = 0;
	bool     HomogeneousDepth = false;
	bool     OriginBottomLeft = false;
	XE::uint8  NumGPUs = 0;

	struct
	{
		PciIdFlag VendorId = PciIdFlag::NONE;
		uint16_t DeviceId = 0;
	} Gpu[4];

	struct  
	{
		XE::uint32 MaxDrawCalls;            //!< Maximum number of draw calls.
		XE::uint32 MaxBlits;                //!< Maximum number of blit calls.
		XE::uint32 MaxTextureSize;          //!< Maximum texture size.
		XE::uint32 MaxTextureLayers;        //!< Maximum texture layers.
		XE::uint32 MaxViews;                //!< Maximum number of views.
		XE::uint32 MaxFrameBuffers;         //!< Maximum number of frame buffer handles.
		XE::uint32 MaxFBAttachments;        //!< Maximum number of frame buffer attachments.
		XE::uint32 MaxPrograms;             //!< Maximum number of program handles.
		XE::uint32 MaxShaders;              //!< Maximum number of shader handles.
		XE::uint32 MaxTextures;             //!< Maximum number of texture handles.
		XE::uint32 MaxTextureSamplers;      //!< Maximum number of texture samplers.
		XE::uint32 MaxComputeBindings;      //!< Maximum number of compute bindings.
		XE::uint32 MaxVertexLayouts;        //!< Maximum number of vertex format layouts.
		XE::uint32 MaxVertexStreams;        //!< Maximum number of vertex streams.
		XE::uint32 MaxIndexBuffers;         //!< Maximum number of index buffer handles.
		XE::uint32 MaxVertexBuffers;        //!< Maximum number of vertex buffer handles.
		XE::uint32 MaxDynamicIndexBuffers;  //!< Maximum number of dynamic index buffer handles.
		XE::uint32 MaxDynamicVertexBuffers; //!< Maximum number of dynamic vertex buffer handles.
		XE::uint32 MaxUniforms;             //!< Maximum number of uniform handles.
		XE::uint32 MaxOcclusionQueries;     //!< Maximum number of occlusion query handles.
		XE::uint32 MaxEncoders;             //!< Maximum number of encoder threads.
		XE::uint32 TransientVbSize;         //!< Maximum transient vertex buffer size.
		XE::uint32 TransientIbSize;         //!< Maximum transient index buffer size.
	} Limits;
};

struct XE_API Attachment
{
public:
	TextureHandle Handle;
	XE::uint16 Mip = 0;
	XE::uint16 Layer = 0;
	bool AutoGenMips = false;
	XE::uint8 Resolve = 0;
	XE::AccessType Access = XE::AccessType::COUNT;
};

struct XE_API InitDesc
{
public:
	RendererContextType Type = RendererContextType::NONE;

	PciIdFlag VendorId = PciIdFlag::NONE;
	XE::uint16 DeviceId = 0;

	WindowHandle Window;

	XE::uint32 Width = 0;
	XE::uint32 Height = 0;
	TextureFormat Format = TextureFormat::RGBA8;
	XE::Flags<ResetFlag> Reset;
	XE::uint8  NumBackBuffers = 0;
	XE::uint8  MaxFrameLatency = 0;
};

struct XE_API ViewDesc
{
	XE::String Name;
	XE::Color ClearColor = XE::Color::Black;
	XE::float32 ClearDepth = 0.0f;
	XE::uint8 ClearStencil = 1;
	XE::Flags<ClearFlag> Flags = ClearFlag::NONE;
	XE::Rectf ViewRect;
	XE::Rectf ViewScissor;
	XE::Mat4x4f ModelMat;
	XE::Mat4x4f ViewMat;
	XE::Mat4x4f ProjMat;
	ViewMode Mode = XE::ViewMode::DEFAULT;
	XE::FrameBufferHandle FrameBuffer;
};

struct XE_API ShaderDesc
{
	XE::String Name;
	ShaderType Type;
};

struct XE_API BufferDesc
{
	XE::String Name;
	XE::uint64 Size = 0;
	XE::Flags< XE::BufferFlag > Flags = XE::BufferFlag::NONE;
};

struct XE_API UniformDesc
{
public:
	XE::String Name;
	XE::uint16 Num;
	UniformType Type;
};

struct XE_API TextureDesc
{
	XE::String Name;
	TextureType Type;
	XE::uint32 Width = 0;
	XE::uint32 Height = 0;
	XE::uint32 Depth = 0;
	bool HasMaps = false;
	XE::uint16 NumMips = 0;
	XE::uint16 NumLayers = 0;
	TextureFormat Format = TextureFormat::RGBA8;
	XE::Flags< XE::TextureFlag > Flags = XE::TextureFlag::NONE;
	XE::Flags< XE::SamplerFlag > Samplers = XE::SamplerFlag::NONE;
};

struct XE_API ProgramDesc
{
	XE::ShaderHandle VS;
	XE::ShaderHandle FS;
	XE::ShaderHandle CS;
};

struct XE_API FrameBufferDesc
{
	XE::String Name;
	XE::uint32 Width = 0;
	XE::uint32 Height = 0;
	XE::WindowHandle Window;
	XE::uint32 AttachmentCount = 0;
	XE::Attachment Attachments[GFX_MAX_ATTACHMENTS];
	XE::TextureFormat ColorFormat = XE::TextureFormat::RGBA8;
	XE::TextureFormat DepthFormat = XE::TextureFormat::D24S8;
	XE::Flags< XE::SamplerFlag > Samplers = XE::SamplerFlag::NONE;
};

struct XE_API IndexBufferDesc : public BufferDesc
{

};

struct XE_API VertexLayoutDesc
{
	AttributeName Attr[GFX_MAX_VERTEX_LAYOUTS];
	AttributeType Type[GFX_MAX_VERTEX_LAYOUTS];
};

struct XE_API VertexBufferDesc : public XE::BufferDesc
{
	XE::VertexLayoutHandle Layout;
};

struct XE_API UpdateTextureDesc
{
	TextureHandle Handle;
	XE::uint16 Layer = 0;
	XE::uint8 Side = 0;
	XE::uint8 Mip = 0;
	XE::int32 X = 0;
	XE::int32 Y = 0;
	XE::int32 Z = 0;
	XE::int32 Width = 0;
	XE::int32 Height = 0;
	XE::int32 Depth = 0;
};

struct XE_API IndirectBufferDesc : public BufferDesc
{

};

struct XE_API OcclusionQueryDesc
{

};

struct XE_API DynamicIndexBufferDesc : public IndexBufferDesc
{

};

struct XE_API DynamicVertexBufferDesc : public XE::VertexBufferDesc
{

};

struct XE_API ClearDesc
{
	ViewHandle Handle;
	XE::uint8 Stencil = 1;
	XE::float32 Depth = 0.0f;
	XE::Color Color = XE::Color::Black;
	XE::ClearFlags Flags = XE::MakeFlags( XE::ClearFlag::COLOR, XE::ClearFlag::DEPTH, XE::ClearFlag::STENCIL );
};


typedef void( *ScreenShotCallbackType )( const char * userdata, XE::uint32 width, XE::uint32 height, XE::uint32 pitch, const XE::uint8 * data, XE::uint64 size, bool filpy );

END_XE_NAMESPACE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
