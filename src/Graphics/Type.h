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

DECL_PTR( Encoder );
DECL_PTR( RenderContext );

DECL_HANDLE( XE_API, View );
DECL_HANDLE( XE_API, Shader );
DECL_HANDLE( XE_API, Texture );
DECL_HANDLE( XE_API, Uniform );
DECL_HANDLE( XE_API, Program );
DECL_HANDLE( XE_API, FrameBuffer );
DECL_HANDLE( XE_API, IndexBuffer );
DECL_HANDLE( XE_API, VertexBuffer );
DECL_HANDLE( XE_API, VertexLayout );
DECL_HANDLE( XE_API, IndirectBuffer );
DECL_HANDLE( XE_API, OcclusionQuery );
DECL_HANDLE( XE_API, DynamicIndexBuffer );
DECL_HANDLE( XE_API, DynamicVertexBuffer );
DECL_HANDLE( XE_API, TransientIndexBuffer );
DECL_HANDLE( XE_API, TransientVertexBuffer );

enum class ResetFlag
{
	NONE = 0,
	FULLSCREEN = 1 << 0,
	VSYNC = 1 << 1,
	MAXANISOTROPY = 1 << 2,
	CAPTURE = 1 << 3,
	FLUSH_AFTER_RENDER = 1 << 4,
	FLIP_AFTER_RENDER = 1 << 5,
	SRGB_BACKBUFFER = 1 << 6,
	HDR10 = 1 << 7,
	HIDPI = 1 << 8,
	DEPTH_CLAMP = 1 << 9,
	SUSPEND = 1 << 10,
};

enum class DebugFlag
{
	NONE = 0,
	WIREFRAME = 1 << 0,
	IFH = 1 << 1,
	STATS = 1 << 2,
	TEXT = 1 << 3,
	PROFILER = 1 << 4,
};

enum class BufferFlag
{
	NONE,
	COMPUTE_READ = 1 << 0,
	COMPUTE_WRITE = 1 << 1,
	DRAW_INDIRECT = 1 << 2,
	ALLOW_RESIZE = 1 << 3,
	INDEX32 = 1 << 4,
	COMPUTE_READ_WRITE = COMPUTE_READ | COMPUTE_WRITE,
};

enum class TextureFlag
{
	NONE = 0,
	MSAA_SAMPLE = 1 << 0,
	RT = 1 << 1,
	COMPUTE_WRITE = 1 << 2,
	SRGB = 1 << 3,
	BLIT_DST = 1 << 4,
	READ_BACK = 1 << 5,
	RT_MSAA_X2 = 1 << 6,
	RT_MSAA_X4 = 1 << 7,
	RT_MSAA_X8 = 1 << 8,
	RT_MSAA_X16 = 1 << 9,
	RT_WRITE_ONLY = 1 << 10,
};

enum class StateFlag : XE::uint64
{
	WRITE_R = 0,
	WRITE_G = 1 << 0,
	WRITE_B = 1 << 1,
	WRITE_A = 1 << 2,
	WRITE_Z = 1 << 3,
	WIRTE_RGB = WRITE_R | WRITE_G | WRITE_B,
	DEPTH_TEST_LESS = 1 << 4,
	DEPTH_TEST_LEQUAL = 1 << 5,
	DEPTH_TEST_EQUAL = 1 << 6,
	DEPTH_TEST_GEQUAL = 1 << 7,
	DEPTH_TEST_GREATER = 1 << 8,
	DEPTH_TEST_NOTEQUAL = 1 << 9,
	DEPTH_TEST_NEVER = 1 << 10,
	DEPTH_TEST_ALWAYS = 1 << 11,
	BLEND_ZERO = 1 << 12,
	BLEND_ONE = 1 << 13,
	BLEND_SRC_COLOR = 1 << 14,
	BLEND_INV_SRC_COLOR = 1 << 15,
	BLEND_SRC_ALPHA = 1 << 16,
	BLEND_INV_SRC_ALPHA = 1 << 17,
	BLEND_DST_ALPHA = 1 << 18,
	BLEND_INV_DST_ALPHA = 1 << 19,
	BLEND_DST_COLOR = 1 << 20,
	BLEND_INV_DST_COLOR = 1 << 21,
	BLEND_SRC_ALPHA_SAT = 1 << 22,
	BLEND_FACTOR = 1 << 23,
	BLEND_INV_FACTOR = 1 << 24,
	BLEND_EQUATION_ADD = 1 << 25,
	BLEND_EQUATION_SUB = 1 << 26,
	BLEND_EQUATION_REVSUB = 1 << 27,
	BLEND_EQUATION_MIN = 1 << 28,
	BLEND_EQUATION_MAX = 1 << 29,
	CULL_CW = 1 << 30,
	CULL_CCW = 1 << 31,
	PT_TRISTRIP = 1 << 32,
	PT_LINES = 1 << 33,
	PT_LINESTRIP = 1 << 34,
	PT_POINTS = 1 << 35,
	MSAA = 1 << 36,
	LINEAA = 1 << 37,
	CONSERVATIVE_RASTER = 1 << 38,
	NONE = 1 << 39,
	BLEND_INDEPENDENT = 1 << 40,
	BLEND_ALPHA_TO_COVERAGE = 1 << 41,
	DEFAULT = WIRTE_RGB | WRITE_A | WRITE_Z | DEPTH_TEST_LESS | CULL_CW | MSAA,
};

enum class StencilFlag : XE::uint32
{
	NONE = 0,
	TEST_LESS = 1 << 0,
	TEST_LEQUAL = 1 << 1,
	TEST_EQUAL = 1 << 2,
	TEST_GEQUAL = 1 << 3,
	TEST_GREATER = 1 << 4,
	TEST_NOTEQUAL = 1 << 5,
	TEST_NEVER = 1 << 6,
	TEST_ALWAYS = 1 << 7,
	OP_FAIL_S_ZERO = 1 << 8,
	OP_FAIL_S_KEEP = 1 << 9,
	OP_FAIL_S_REPLACE = 1 << 10,
	OP_FAIL_S_INCR = 1 << 11,
	OP_FAIL_S_INCRSAT = 1 << 12,
	OP_FAIL_S_DECR = 1 << 13,
	OP_FAIL_S_DECRSAT = 1 << 14,
	OP_FAIL_S_INVERT = 1 << 15,
	OP_FAIL_Z_ZERO = 1 << 16,
	OP_FAIL_Z_KEEP = 1 << 17,
	OP_FAIL_Z_REPLACE = 1 << 18,
	OP_FAIL_Z_INCR = 1 << 19,
	OP_FAIL_Z_INCRSAT = 1 << 20,
	OP_FAIL_Z_DECR = 1 << 21,
	OP_FAIL_Z_DECRSAT = 1 << 22,
	OP_FAIL_Z_INVERT = 1 << 23,
	OP_PASS_Z_ZERO = 1 << 24,
	OP_PASS_Z_KEEP = 1 << 25,
	OP_PASS_Z_REPLACE = 1 << 26,
	OP_PASS_Z_INCR = 1 << 27,
	OP_PASS_Z_INCRSAT = 1 << 28,
	OP_PASS_Z_DECR = 1 << 29,
	OP_PASS_Z_DECRSAT = 1 << 30,
	OP_PASS_Z_INVERT = 1 << 31,
};

enum class PCIType
{
	NONE,
	AMD,
	INTEL,
	NVIDIA,
	SOFTWARE,
};

enum class Fatal
{
	DebugCheck,
	InvalidShader,
	UnableToInitialize,
	UnableToCreateTexture,
	DeviceLost,

	Count
};

enum class Access
{
	READ,      //!< Read
	WRITE,     //!< Write
	READWRITE, //!< Read and write

	COUNT
};

enum class ContextType
{
	NOOP,         //!< No rendering.
	METAL,        //!< Metal
	VULKAN,       //!< Vulkan
	DIRECT3D12,   //!< Direct3D 12.0
};

enum class Attribute
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

enum class AttributeType
{
	Uint8,  //!< Uint8
	Uint10, //!< Uint10, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_UINT10`.
	Int16,  //!< Int16
	Half,   //!< Half, availability depends on: `BGFX_CAPS_VERTEX_ATTRIB_HALF`.
	Float,  //!< Float

	Count
};

enum class UniformType
{
	SAMPLER, //!< Sampler.
	END,     //!< Reserved, do not use.

	VEC4,    //!< 4 floats vector.
	MAT3,    //!< 3x3 matrix.
	MAT4,    //!< 4x4 matrix.

	COUNT
};

enum class BackbufferRatio
{
	EQUAL,     //!< Equal to backbuffer.
	HALF,      //!< One half size of backbuffer.
	QUARTER,   //!< One quarter size of backbuffer.
	EIGHTH,    //!< One eighth size of backbuffer.
	SIXTEENTH, //!< One sixteenth size of backbuffer.
	DOUBLE,    //!< Double size of backbuffer.

	COUNT
};

enum class OcclusionQueryResult
{
	INVISIBLE, //!< Query failed test.
	VISIBLE,   //!< Query passed test.
	NORESULT,  //!< Query result is not available yet.

	Count
};

enum class Topology
{
	TRILIST,   //!< Triangle list.
	TRISTRIP,  //!< Triangle strip.
	LINELIST,  //!< Line list.
	LINESTRIP, //!< Line strip.
	POINTLIST, //!< Point list.

	COUNT
};

enum class TopologySort
{
	DirectionFrontToBackMin, //!<
	DirectionFrontToBackAvg, //!<
	DirectionFrontToBackMax, //!<
	DirectionBackToFrontMin, //!<
	DirectionBackToFrontAvg, //!<
	DirectionBackToFrontMax, //!<
	DistanceFrontToBackMin,  //!<
	DistanceFrontToBackAvg,  //!<
	DistanceFrontToBackMax,  //!<
	DistanceBackToFrontMin,  //!<
	DistanceBackToFrontAvg,  //!<
	DistanceBackToFrontMax,  //!<

	Count
};

enum class ViewMode
{
	Default,         //!< Default sort order.
	Sequential,      //!< Sort in the same order in which submit calls were called.
	DepthAscending,  //!< Sort draw call depth in ascending order.
	DepthDescending, //!< Sort draw call depth in descending order.

	Count
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

	UNKNOWN_DEPTH, // Depth formats below.

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

enum class CubeMap
{
	POSITIVE_X,
	NEGATIVE_X,
	POSITIVE_Y,
	NEGATIVE_Y,
	POSITIVE_Z,
	NEGATIVE_Z,
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

enum class CommandType : XE::uint8
{
	RENDERER_INIT,
	RENDERER_SHUTDOWN_BEGIN,
	CREATE_VERTEX_LAYOUT,
	CREATE_INDEX_BUFFER,
	CREATE_VERTEX_BUFFER,
	CREATE_DYNAMIC_INDEX_BUFFER,
	UPDATE_DYNAMIC_INDEX_BUFFER,
	CREATE_DYNAMIC_VERTEX_BUFFER,
	UPDATE_DYNAMIC_VERTEX_BUFFER,
	CREATE_SHADER,
	CREATE_PROGRAM,
	CREATE_TEXTURE,
	UPDATE_TEXTURE,
	RESIZE_TEXTURE,
	CREATE_FRAME_BUFFER,
	CREATE_UNIFORM,
	UPDATE_VIEW_NAME,
	INVALIDATE_OCCLUSION_QUERY,
	SET_NAME,
	END,
	RENDERER_SHUTDOWN_END,
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
	REQUEST_SCREEN_SHOT,
};

struct XE_API Caps
{
	ContextType contextType = ContextType::NOOP;

	uint64_t supported = 0;

	PCIType vendorId = PCIType::NONE;
	uint16_t deviceId = 0;        
	bool     homogeneousDepth = false;
	bool     originBottomLeft = false;
	uint8_t  numGPUs = 0;         

	struct
	{
		PCIType vendorId = PCIType::NONE;
		uint16_t deviceId = 0;
	} gpu[4]; //!< Enumerated GPUs.

	uint32_t maxDrawCalls;            //!< Maximum number of draw calls.
	uint32_t maxBlits;                //!< Maximum number of blit calls.
	uint32_t maxTextureSize;          //!< Maximum texture size.
	uint32_t maxTextureLayers;        //!< Maximum texture layers.
	uint32_t maxViews;                //!< Maximum number of views.
	uint32_t maxFrameBuffers;         //!< Maximum number of frame buffer handles.
	uint32_t maxFBAttachments;        //!< Maximum number of frame buffer attachments.
	uint32_t maxPrograms;             //!< Maximum number of program handles.
	uint32_t maxShaders;              //!< Maximum number of shader handles.
	uint32_t maxTextures;             //!< Maximum number of texture handles.
	uint32_t maxTextureSamplers;      //!< Maximum number of texture samplers.
	uint32_t maxComputeBindings;      //!< Maximum number of compute bindings.
	uint32_t maxVertexLayouts;        //!< Maximum number of vertex format layouts.
	uint32_t maxVertexStreams;        //!< Maximum number of vertex streams.
	uint32_t maxIndexBuffers;         //!< Maximum number of index buffer handles.
	uint32_t maxVertexBuffers;        //!< Maximum number of vertex buffer handles.
	uint32_t maxDynamicIndexBuffers;  //!< Maximum number of dynamic index buffer handles.
	uint32_t maxDynamicVertexBuffers; //!< Maximum number of dynamic vertex buffer handles.
	uint32_t maxUniforms;             //!< Maximum number of uniform handles.
	uint32_t maxOcclusionQueries;     //!< Maximum number of occlusion query handles.
	uint32_t maxEncoders;             //!< Maximum number of encoder threads.
	uint32_t transientVbSize;         //!< Maximum transient vertex buffer size.
	uint32_t transientIbSize;         //!< Maximum transient index buffer size.

	uint16_t formats[( XE::uint64 )TextureFormat::COUNT];
};

struct XE_API TransientIndexBuffer
{
	uint8_t * data = nullptr;
	uint32_t size = 0;
	uint32_t startIndex = 0;
	IndexBufferHandle handle;
};

struct XE_API TransientVertexBuffer
{
	uint8_t * data = nullptr;
	uint32_t size = 0;
	uint32_t startVertex = 0;
	uint16_t stride = 0;
	VertexBufferHandle handle;
	VertexLayoutHandle layoutHandle;
};

struct XE_API InstanceDataBuffer
{
	uint8_t * data = nullptr;
	uint32_t size = 0;
	uint32_t offset = 0;
	uint32_t num = 0;
	uint16_t stride = 0;
	VertexBufferHandle handle;
};

struct XE_API TextureInfo
{
	TextureFormat format = TextureFormat::COUNT;
	uint32_t storageSize = 0;
	uint16_t width = 0;
	uint16_t height = 0;
	uint16_t depth = 0;
	uint16_t numLayers = 0;
	uint8_t numMips = 0;
	uint8_t bitsPerPixel = 0;
	bool cubeMap = false;
};

struct XE_API UniformInfo
{
	std::string name;
	UniformType type = UniformType::COUNT;
	uint16_t num = 0;
};

struct XE_API Attachment
{
	Access access = Access::COUNT;
	TextureHandle handle;
	uint16_t mip = 0;
	uint16_t layer = 0;
	bool auto_gen_mips = false;
};

struct XE_API InitInfo
{
	ContextType type = ContextType::NOOP;

	PCIType vendorId = PCIType::NONE;
	uint16_t deviceId = 0;

	bool debug = false;
	bool profile = false;

	WindowHandle window;

	TextureFormat format = TextureFormat::COUNT;
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t reset = 0;
	uint8_t  numBackBuffers = 0;
	uint8_t  maxFrameLatency = 0;

	uint16_t maxEncoders = 0;
	uint32_t transientVbSize = 0;
	uint32_t transientIbSize = 0;
};

struct XE_API VertexLayout
{
	Attribute Attr;
	AttributeType Type;
};


END_XE_NAMESPACE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
