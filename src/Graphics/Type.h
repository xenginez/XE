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
DECL_PTR( Texture );
DECL_PTR( Skeleton );
DECL_PTR( Renderer );
DECL_PTR( Renderable );
DECL_PTR( RenderShader );
DECL_PTR( RenderWindow );
DECL_PTR( RenderMaterial );

DECL_HANDLE( XE_API, Buffer );
DECL_HANDLE( XE_API, Image );
DECL_HANDLE( XE_API, Shader );
DECL_HANDLE( XE_API, Pipeline );
DECL_HANDLE( XE_API, Pass );
DECL_HANDLE( XE_API, Context );

/*
	various compile-time constants

	FIXME: it may make sense to convert some of those into defines so
	that the user code can override them.
*/
static constexpr XE::uint32 INVALID_SLOT_INDEX = 0;
static constexpr XE::uint32 NUM_SHADER_STAGES = 2;
static constexpr XE::uint32 NUM_INFLIGHT_FRAMES = 2;
static constexpr XE::uint32 MAX_COLOR_ATTACHMENTS = 4;
static constexpr XE::uint32 MAX_SHADERSTAGE_BUFFERS = 8;
static constexpr XE::uint32 MAX_SHADERSTAGE_IMAGES = 12;
static constexpr XE::uint32 MAX_SHADERSTAGE_UBS = 4;
static constexpr XE::uint32 MAX_UB_MEMBERS = 16;
static constexpr XE::uint32 MAX_VERTEX_ATTRIBUTES = 16;      /* NOTE: actual max vertex attrs can be less on GLES2, see Limits! */
static constexpr XE::uint32 MAX_MIPMAPS = 16;
static constexpr XE::uint32 MAX_TEXTUREARRAY_LAYERS = 128;
static constexpr XE::float32 DEFAULT_CLEAR_RED = 0.5f;
static constexpr XE::float32 DEFAULT_CLEAR_GREEN = 0.5f;
static constexpr XE::float32 DEFAULT_CLEAR_BLUE = 0.5f;
static constexpr XE::float32 DEFAULT_CLEAR_ALPHA = 1.0f;
static constexpr XE::float32 DEFAULT_CLEAR_DEPTH = 1.0f;
static constexpr XE::float32 DEFAULT_CLEAR_STENCIL = 0;

/*
	Backend

	The active 3D-API backend, use the function query_backend()
	to get the currently active backend.

	For returned value corresponds with the compile-time define to select
	a backend, with the only exception of SOKOL_GLES3: this may
	return BACKEND_GLES2 if the backend has to fallback to GLES2 mode
	because GLES3 isn't supported.
*/
enum Backend
{
	BACKEND_GLCORE33,
	BACKEND_GLES2,
	BACKEND_GLES3,
	BACKEND_D3D11,
	BACKEND_D3D12,
	BACKEND_VULKAN,
	BACKEND_METAL_IOS,
	BACKEND_METAL_MACOS,
	BACKEND_METAL_SIMULATOR,
	BACKEND_DUMMY,
};

/*
	PixelFormat

	sokol_gfx.h basically uses the same pixel formats as WebGPU, since these
	are supported on most newer GPUs. GLES2 and WebGL has a much smaller
	subset of available pixel formats. Call query_pixelformat() to check
	at runtime if a pixel format supports the desired features.

	A pixelformat name consist of three parts:

		- components (R, RG, RGB or RGBA)
		- bit width per component (8, 16 or 32)
		- component data type:
			- unsigned normalized (no postfix)
			- signed normalized (SN postfix)
			- unsigned integer (UI postfix)
			- signed integer (SI postfix)
			- float (F postfix)

	Not all pixel formats can be used for everything, call query_pixelformat()
	to inspect the capabilities of a given pixelformat. The function returns
	an PixelFormatInfo struct with the following bool members:

		- sample: the pixelformat can be sampled as texture at least with
				  nearest filtering
		- filter: the pixelformat can be samples as texture with linear
				  filtering
		- render: the pixelformat can be used for render targets
		- blend:  blending is supported when using the pixelformat for
				  render targets
		- msaa:   multisample-antialiasing is supported when using the
				  pixelformat for render targets
		- depth:  the pixelformat can be used for depth-stencil attachments

	When targeting GLES2/WebGL, the only safe formats to use
	as texture are PIXELFORMAT_R8 and PIXELFORMAT_RGBA8. For rendering
	in GLES2/WebGL, only PIXELFORMAT_RGBA8 is safe. All other formats
	must be checked via query_pixelformats().

	The default pixel format for texture images is PIXELFORMAT_RGBA8.

	The default pixel format for render target images is platform-dependent:
		- for Metal and D3D11 it is PIXELFORMAT_BGRA8
		- for GL backends it is PIXELFORMAT_RGBA8

	This is mainly because of the default framebuffer which is setup outside
	of sokol_gfx.h. On some backends, using BGRA for the default frame buffer
	allows more efficient frame flips. For your own offscreen-render-targets,
	use whatever renderable pixel format is convenient for you.
*/
enum PixelFormat
{
	_PIXELFORMAT_DEFAULT,    /* value 0 reserved for default-init */
	PIXELFORMAT_NONE,

	PIXELFORMAT_R8,
	PIXELFORMAT_R8SN,
	PIXELFORMAT_R8UI,
	PIXELFORMAT_R8SI,

	PIXELFORMAT_R16,
	PIXELFORMAT_R16SN,
	PIXELFORMAT_R16UI,
	PIXELFORMAT_R16SI,
	PIXELFORMAT_R16F,
	PIXELFORMAT_RG8,
	PIXELFORMAT_RG8SN,
	PIXELFORMAT_RG8UI,
	PIXELFORMAT_RG8SI,

	PIXELFORMAT_R32UI,
	PIXELFORMAT_R32SI,
	PIXELFORMAT_R32F,
	PIXELFORMAT_RG16,
	PIXELFORMAT_RG16SN,
	PIXELFORMAT_RG16UI,
	PIXELFORMAT_RG16SI,
	PIXELFORMAT_RG16F,
	PIXELFORMAT_RGBA8,
	PIXELFORMAT_RGBA8SN,
	PIXELFORMAT_RGBA8UI,
	PIXELFORMAT_RGBA8SI,
	PIXELFORMAT_BGRA8,
	PIXELFORMAT_RGB10A2,
	PIXELFORMAT_RG11B10F,

	PIXELFORMAT_RG32UI,
	PIXELFORMAT_RG32SI,
	PIXELFORMAT_RG32F,
	PIXELFORMAT_RGBA16,
	PIXELFORMAT_RGBA16SN,
	PIXELFORMAT_RGBA16UI,
	PIXELFORMAT_RGBA16SI,
	PIXELFORMAT_RGBA16F,

	PIXELFORMAT_RGBA32UI,
	PIXELFORMAT_RGBA32SI,
	PIXELFORMAT_RGBA32F,

	PIXELFORMAT_DEPTH,
	PIXELFORMAT_DEPTH_STENCIL,

	PIXELFORMAT_BC1_RGBA,
	PIXELFORMAT_BC2_RGBA,
	PIXELFORMAT_BC3_RGBA,
	PIXELFORMAT_BC4_R,
	PIXELFORMAT_BC4_RSN,
	PIXELFORMAT_BC5_RG,
	PIXELFORMAT_BC5_RGSN,
	PIXELFORMAT_BC6H_RGBF,
	PIXELFORMAT_BC6H_RGBUF,
	PIXELFORMAT_BC7_RGBA,
	PIXELFORMAT_PVRTC_RGB_2BPP,
	PIXELFORMAT_PVRTC_RGB_4BPP,
	PIXELFORMAT_PVRTC_RGBA_2BPP,
	PIXELFORMAT_PVRTC_RGBA_4BPP,
	PIXELFORMAT_ETC2_RGB8,
	PIXELFORMAT_ETC2_RGB8A1,
	PIXELFORMAT_ETC2_RGBA8,
	PIXELFORMAT_ETC2_RG11,
	PIXELFORMAT_ETC2_RG11SN,

	_PIXELFORMAT_NUM,
	_PIXELFORMAT_FORCE_U32 = 0x7FFFFFFF
};

/*
	ResourceState

	The current state of a resource in its resource pool.
	Resources start in the INITIAL state, which means the
	pool slot is unoccupied and can be allocated. When a resource is
	created, first an id is allocated, and the resource pool slot
	is set to state ALLOC. After allocation, the resource is
	initialized, which may result in the VALID or FAILED state. The
	reason why allocation and initialization are separate is because
	some resource types (e.g. buffers and images) might be asynchronously
	initialized by the user application. If a resource which is not
	in the VALID state is attempted to be used for rendering, rendering
	operations will silently be dropped.

	The special INVALID state is returned in query_xxx_state() if no
	resource object exists for the provided resource id.
*/
enum ResourceState
{
	RESOURCESTATE_INITIAL,
	RESOURCESTATE_ALLOC,
	RESOURCESTATE_VALID,
	RESOURCESTATE_FAILED,
	RESOURCESTATE_INVALID,
	_RESOURCESTATE_FORCE_U32 = 0x7FFFFFFF
};

/*
	Usage

	A resource usage hint describing the update strategy of
	buffers and images. This is used in the BufferDesc.usage
	and ImageDesc.usage members when creating buffers
	and images:

	USAGE_IMMUTABLE:     the resource will never be updated with
							new data, instead the content of the
							resource must be provided on creation
	USAGE_DYNAMIC:       the resource will be updated infrequently
							with new data (this could range from "once
							after creation", to "quite often but not
							every frame")
	USAGE_STREAM:        the resource will be updated each frame
							with new content

	The rendering backends use this hint to prevent that the
	CPU needs to wait for the GPU when attempting to update
	a resource that might be currently accessed by the GPU.

	Resource content is updated with the function update_buffer() for
	buffer objects, and update_image() for image objects. Only
	one update is allowed per frame and resource object. The
	application must update all data required for rendering (this
	means that the update data can be smaller than the resource size,
	if only a part of the overall resource size is used for rendering,
	you only need to make sure that the data that *is* used is valid).

	The default usage is USAGE_IMMUTABLE.
*/
enum Usage
{
	_USAGE_DEFAULT,      /* value 0 reserved for default-init */
	USAGE_IMMUTABLE,
	USAGE_DYNAMIC,
	USAGE_STREAM,
	_USAGE_NUM,
	_USAGE_FORCE_U32 = 0x7FFFFFFF
};

/*
	BufferType

	This indicates whether a buffer contains vertex- or index-data,
	used in the BufferDesc.type member when creating a buffer.

	The default value is BUFFERTYPE_VERTEXBUFFER.
*/
enum BufferType
{
	_BUFFERTYPE_DEFAULT,         /* value 0 reserved for default-init */
	BUFFERTYPE_VERTEXBUFFER,
	BUFFERTYPE_INDEXBUFFER,
	_BUFFERTYPE_NUM,
	_BUFFERTYPE_FORCE_U32 = 0x7FFFFFFF
};

/*
	IndexType

	Indicates whether indexed rendering (fetching vertex-indices from an
	index buffer) is used, and if yes, the index data type (16- or 32-bits).
	This is used in the PipelineDesc.index_type member when creating a
	pipeline object.

	The default index type is INDEXTYPE_NONE.
*/
enum IndexType
{
	_INDEXTYPE_DEFAULT,   /* value 0 reserved for default-init */
	INDEXTYPE_NONE,
	INDEXTYPE_UINT16,
	INDEXTYPE_UINT32,
	_INDEXTYPE_NUM,
	_INDEXTYPE_FORCE_U32 = 0x7FFFFFFF
};

/*
	ImageType

	Indicates the basic type of an image object (2D-texture, cubemap,
	3D-texture or 2D-array-texture). 3D- and array-textures are not supported
	on the GLES2/WebGL backend (use query_features().imagetype_3d and
	query_features().imagetype_array to check for support). The image type
	is used in the ImageDesc.type member when creating an image.

	The default image type when creating an image is IMAGETYPE_2D.
*/
enum ImageType
{
	_IMAGETYPE_DEFAULT,  /* value 0 reserved for default-init */
	IMAGETYPE_2D,
	IMAGETYPE_CUBE,
	IMAGETYPE_3D,
	IMAGETYPE_ARRAY,
	_IMAGETYPE_NUM,
	_IMAGETYPE_FORCE_U32 = 0x7FFFFFFF
};

/*
	CubeFace

	The cubemap faces. Use these as indices in the ImageDesc.content
	array.
*/
enum CubeFace
{
	CUBEFACE_POS_X,
	CUBEFACE_NEG_X,
	CUBEFACE_POS_Y,
	CUBEFACE_NEG_Y,
	CUBEFACE_POS_Z,
	CUBEFACE_NEG_Z,
	CUBEFACE_NUM,
	_CUBEFACE_FORCE_U32 = 0x7FFFFFFF
};

/*
	ShaderStage

	There are 2 shader stages: vertex- and fragment-shader-stage.
	Each shader stage consists of:

	- one slot for a shader function (provided as source- or byte-code)
	- MAX_SHADERSTAGE_UBS slots for uniform blocks
	- MAX_SHADERSTAGE_IMAGES slots for images used as textures by
	  the shader function
*/
enum ShaderStage
{
	SHADERSTAGE_VS,
	SHADERSTAGE_FS,
	_SHADERSTAGE_FORCE_U32 = 0x7FFFFFFF
};

/*
	PrimitiveType

	This is the common subset of 3D primitive types supported across all 3D
	APIs. This is used in the PipelineDesc.primitive_type member when
	creating a pipeline object.

	The default primitive type is PRIMITIVETYPE_TRIANGLES.
*/
enum PrimitiveType
{
	_PRIMITIVETYPE_DEFAULT,  /* value 0 reserved for default-init */
	PRIMITIVETYPE_POINTS,
	PRIMITIVETYPE_LINES,
	PRIMITIVETYPE_LINE_STRIP,
	PRIMITIVETYPE_TRIANGLES,
	PRIMITIVETYPE_TRIANGLE_STRIP,
	_PRIMITIVETYPE_NUM,
	_PRIMITIVETYPE_FORCE_U32 = 0x7FFFFFFF
};

/*
	Filter

	The filtering mode when sampling a texture image. This is
	used in the ImageDesc.min_filter and ImageDesc.mag_filter
	members when creating an image object.

	The default filter mode is FILTER_NEAREST.
*/
enum Filter
{
	_FILTER_DEFAULT, /* value 0 reserved for default-init */
	FILTER_NEAREST,
	FILTER_LINEAR,
	FILTER_NEAREST_MIPMAP_NEAREST,
	FILTER_NEAREST_MIPMAP_LINEAR,
	FILTER_LINEAR_MIPMAP_NEAREST,
	FILTER_LINEAR_MIPMAP_LINEAR,
	_FILTER_NUM,
	_FILTER_FORCE_U32 = 0x7FFFFFFF
};

/*
	Wrap

	The texture coordinates wrapping mode when sampling a texture
	image. This is used in the ImageDesc.wrap_u, .wrap_v
	and .wrap_w members when creating an image.

	The default wrap mode is WRAP_REPEAT.

	NOTE: WRAP_CLAMP_TO_BORDER is not supported on all backends
	and platforms. To check for support, call query_features()
	and check the "clamp_to_border" boolean in the returned
	Features struct.

	Platforms which don't support WRAP_CLAMP_TO_BORDER will silently fall back
	to WRAP_CLAMP_TO_EDGE without a validation error.

	Platforms which support clamp-to-border are:

		- all desktop GL platforms
		- Metal on macOS
		- D3D11

	Platforms which do not support clamp-to-border:

		- GLES2/3 and WebGL/WebGL2
		- Metal on iOS
*/
enum Wrap
{
	_WRAP_DEFAULT,   /* value 0 reserved for default-init */
	WRAP_REPEAT,
	WRAP_CLAMP_TO_EDGE,
	WRAP_CLAMP_TO_BORDER,
	WRAP_MIRRORED_REPEAT,
	_WRAP_NUM,
	_WRAP_FORCE_U32 = 0x7FFFFFFF
};

/*
	BorderColor

	The border color to use when sampling a texture, and the UV wrap
	mode is WRAP_CLAMP_TO_BORDER.

	The default border color is BORDERCOLOR_OPAQUE_BLACK
*/
enum BorderColor
{
	_BORDERCOLOR_DEFAULT,    /* value 0 reserved for default-init */
	BORDERCOLOR_TRANSPARENT_BLACK,
	BORDERCOLOR_OPAQUE_BLACK,
	BORDERCOLOR_OPAQUE_WHITE,
	_BORDERCOLOR_NUM,
	_BORDERCOLOR_FORCE_U32 = 0x7FFFFFFF
};

/*
	VertexFormat

	The data type of a vertex component. This is used to describe
	the layout of vertex data when creating a pipeline object.
*/
enum VertexFormat
{
	VERTEXFORMAT_INVALID,
	VERTEXFORMAT_FLOAT,
	VERTEXFORMAT_FLOAT2,
	VERTEXFORMAT_FLOAT3,
	VERTEXFORMAT_FLOAT4,
	VERTEXFORMAT_BYTE4,
	VERTEXFORMAT_BYTE4N,
	VERTEXFORMAT_UBYTE4,
	VERTEXFORMAT_UBYTE4N,
	VERTEXFORMAT_SHORT2,
	VERTEXFORMAT_SHORT2N,
	VERTEXFORMAT_USHORT2N,
	VERTEXFORMAT_SHORT4,
	VERTEXFORMAT_SHORT4N,
	VERTEXFORMAT_USHORT4N,
	VERTEXFORMAT_UINT10_N2,
	_VERTEXFORMAT_NUM,
	_VERTEXFORMAT_FORCE_U32 = 0x7FFFFFFF
};

/*
	VertexStep

	Defines whether the input pointer of a vertex input stream is advanced
	'per vertex' or 'per instance'. The default step-func is
	VERTEXSTEP_PER_VERTEX. VERTEXSTEP_PER_INSTANCE is used with
	instanced-rendering.

	The vertex-step is part of the vertex-layout definition
	when creating pipeline objects.
*/
enum VertexStep
{
	_VERTEXSTEP_DEFAULT,     /* value 0 reserved for default-init */
	VERTEXSTEP_PER_VERTEX,
	VERTEXSTEP_PER_INSTANCE,
	_VERTEXSTEP_NUM,
	_VERTEXSTEP_FORCE_U32 = 0x7FFFFFFF
};

/*
	UniformType

	The data type of a uniform block member. This is used to
	describe the internal layout of uniform blocks when creating
	a shader object.
*/
enum UniformType
{
	UNIFORMTYPE_INVALID,
	UNIFORMTYPE_FLOAT,
	UNIFORMTYPE_FLOAT2,
	UNIFORMTYPE_FLOAT3,
	UNIFORMTYPE_FLOAT4,
	UNIFORMTYPE_MAT4,
	_UNIFORMTYPE_NUM,
	_UNIFORMTYPE_FORCE_U32 = 0x7FFFFFFF
};

/*
	CullMode

	The face-culling mode, this is used in the
	PipelineDesc.rasterizer.cull_mode member when creating a
	pipeline object.

	The default cull mode is CULLMODE_NONE
*/
enum CullMode
{
	_CULLMODE_DEFAULT,   /* value 0 reserved for default-init */
	CULLMODE_NONE,
	CULLMODE_FRONT,
	CULLMODE_BACK,
	_CULLMODE_NUM,
	_CULLMODE_FORCE_U32 = 0x7FFFFFFF
};

/*
	FaceWinding

	The vertex-winding rule that determines a front-facing primitive. This
	is used in the member PipelineDesc.rasterizer.face_winding
	when creating a pipeline object.

	The default winding is FACEWINDING_CW (clockwise)
*/
enum FaceWinding
{
	_FACEWINDING_DEFAULT,    /* value 0 reserved for default-init */
	FACEWINDING_CCW,
	FACEWINDING_CW,
	_FACEWINDING_NUM,
	_FACEWINDING_FORCE_U32 = 0x7FFFFFFF
};

/*
	CompareFunc

	The compare-function for depth- and stencil-ref tests.
	This is used when creating pipeline objects in the members:

	PipelineDesc
		.depth_stencil
			.depth_compare_func
			.stencil_front.compare_func
			.stencil_back.compare_func

	The default compare func for depth- and stencil-tests is
	COMPAREFUNC_ALWAYS.
*/
enum CompareFunc
{
	_COMPAREFUNC_DEFAULT,    /* value 0 reserved for default-init */
	COMPAREFUNC_NEVER,
	COMPAREFUNC_LESS,
	COMPAREFUNC_EQUAL,
	COMPAREFUNC_LESS_EQUAL,
	COMPAREFUNC_GREATER,
	COMPAREFUNC_NOT_EQUAL,
	COMPAREFUNC_GREATER_EQUAL,
	COMPAREFUNC_ALWAYS,
	_COMPAREFUNC_NUM,
	_COMPAREFUNC_FORCE_U32 = 0x7FFFFFFF
};

/*
	StencilOp

	The operation performed on a currently stored stencil-value when a
	comparison test passes or fails. This is used when creating a pipeline
	object in the members:

	PipelineDesc
		.depth_stencil
			.stencil_front
				.fail_op
				.depth_fail_op
				.pass_op
			.stencil_back
				.fail_op
				.depth_fail_op
				.pass_op

	The default value is STENCILOP_KEEP.
*/
enum StencilOp
{
	_STENCILOP_DEFAULT,      /* value 0 reserved for default-init */
	STENCILOP_KEEP,
	STENCILOP_ZERO,
	STENCILOP_REPLACE,
	STENCILOP_INCR_CLAMP,
	STENCILOP_DECR_CLAMP,
	STENCILOP_INVERT,
	STENCILOP_INCR_WRAP,
	STENCILOP_DECR_WRAP,
	_STENCILOP_NUM,
	_STENCILOP_FORCE_U32 = 0x7FFFFFFF
};

/*
	BlendFactor

	The source and destination factors in blending operations.
	This is used in the following members when creating a pipeline object:

	PipelineDesc
		.blend
			.src_factor_rgb
			.dst_factor_rgb
			.src_factor_alpha
			.dst_factor_alpha

	The default value is BLENDFACTOR_ONE for source
	factors, and BLENDFACTOR_ZERO for destination factors.
*/
enum BlendFactor
{
	_BLENDFACTOR_DEFAULT,    /* value 0 reserved for default-init */
	BLENDFACTOR_ZERO,
	BLENDFACTOR_ONE,
	BLENDFACTOR_SRC_COLOR,
	BLENDFACTOR_ONE_MINUS_SRC_COLOR,
	BLENDFACTOR_SRC_ALPHA,
	BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
	BLENDFACTOR_DST_COLOR,
	BLENDFACTOR_ONE_MINUS_DST_COLOR,
	BLENDFACTOR_DST_ALPHA,
	BLENDFACTOR_ONE_MINUS_DST_ALPHA,
	BLENDFACTOR_SRC_ALPHA_SATURATED,
	BLENDFACTOR_BLEND_COLOR,
	BLENDFACTOR_ONE_MINUS_BLEND_COLOR,
	BLENDFACTOR_BLEND_ALPHA,
	BLENDFACTOR_ONE_MINUS_BLEND_ALPHA,
	_BLENDFACTOR_NUM,
	_BLENDFACTOR_FORCE_U32 = 0x7FFFFFFF
};

/*
	BlendOp

	Describes how the source and destination values are combined in the
	fragment blending operation. It is used in the following members when
	creating a pipeline object:

	PipelineDesc
		.blend
			.op_rgb
			.op_alpha

	The default value is BLENDOP_ADD.
*/
enum BlendOp
{
	_BLENDOP_DEFAULT,    /* value 0 reserved for default-init */
	BLENDOP_ADD,
	BLENDOP_SUBTRACT,
	BLENDOP_REVERSE_SUBTRACT,
	_BLENDOP_NUM,
	_BLENDOP_FORCE_U32 = 0x7FFFFFFF
};

/*
	ColorMask

	Selects the color channels when writing a fragment color to the
	framebuffer. This is used in the members
	PipelineDesc.blend.color_write_mask when creating a pipeline object.

	The default colormask is COLORMASK_RGBA (write all colors channels)

	NOTE: since the color mask value 0 is reserved for the default value
	(COLORMASK_RGBA), use COLORMASK_NONE if all color channels
	should be disabled.
*/
enum ColorMask
{
	_COLORMASK_DEFAULT = 0,      /* value 0 reserved for default-init */
	COLORMASK_NONE = ( 0x10 ),     /* special value for 'all channels disabled */
	COLORMASK_R = ( 1 << 0 ),
	COLORMASK_G = ( 1 << 1 ),
	COLORMASK_B = ( 1 << 2 ),
	COLORMASK_A = ( 1 << 3 ),
	COLORMASK_RGB = 0x7,
	COLORMASK_RGBA = 0xF,
	_COLORMASK_FORCE_U32 = 0x7FFFFFFF
};

/*
	Action

	Defines what action should be performed at the start of a render pass:

	ACTION_CLEAR:    clear the render target image
	ACTION_LOAD:     load the previous content of the render target image
	ACTION_DONTCARE: leave the render target image content undefined

	This is used in the PassAction structure.

	The default action for all pass attachments is ACTION_CLEAR, with the
	clear color rgba = {0.5f, 0.5f, 0.5f, 1.0f], depth=1.0 and stencil=0.

	If you want to override the default behaviour, it is important to not
	only set the clear color, but the 'action' field as well (as long as this
	is in its _ACTION_DEFAULT, the value fields will be ignored).
*/
enum Action
{
	_ACTION_DEFAULT,
	ACTION_CLEAR,
	ACTION_LOAD,
	ACTION_DONTCARE,
	_ACTION_NUM,
	_ACTION_FORCE_U32 = 0x7FFFFFFF
};

/*
	Runtime information about a pixel format, returned
	by query_pixelformat().
*/
struct PixelFormatInfo
{
	bool sample;        /* pixel format can be sampled in shaders */
	bool filter;        /* pixel format can be sampled with filtering */
	bool render;        /* pixel format can be used as render target */
	bool blend;         /* alpha-blending is supported */
	bool msaa;          /* pixel format can be used as MSAA render target */
	bool depth;         /* pixel format is a depth format */
};

/*
	Runtime information about available optional features,
	returned by query_features()
*/
struct Features
{
	bool instancing;                /* hardware instancing supported */
	bool origin_top_left;           /* framebuffer and texture origin is in top left corner */
	bool multiple_render_targets;   /* offscreen render passes can have multiple render targets attached */
	bool msaa_render_targets;       /* offscreen render passes support MSAA antialiasing */
	bool imagetype_3d;              /* creation of IMAGETYPE_3D images is supported */
	bool imagetype_array;           /* creation of IMAGETYPE_ARRAY images is supported */
	bool image_clamp_to_border;     /* border color and clamp-to-border UV-wrap mode is supported */
};

/*
	Runtime information about resource limits, returned by query_limit()
*/
struct Limits
{
	XE::uint32 max_image_size_2d;         /* max width/height of IMAGETYPE_2D images */
	XE::uint32 max_image_size_cube;       /* max width/height of IMAGETYPE_CUBE images */
	XE::uint32 max_image_size_3d;         /* max width/height/depth of IMAGETYPE_3D images */
	XE::uint32 max_image_size_array;      /* max width/height pf IMAGETYPE_ARRAY images */
	XE::uint32 max_image_array_layers;    /* max number of layers in IMAGETYPE_ARRAY images */
	XE::uint32 max_vertex_attrs;          /* <= MAX_VERTEX_ATTRIBUTES (only on some GLES2 impls) */
};

/*
	PassAction

	The PassAction struct defines the actions to be performed
	at the start of a rendering pass in the functions begin_pass()
	and begin_default_pass().

	A separate action and clear values can be defined for each
	color attachment, and for the depth-stencil attachment.

	The default clear values are defined by the macros:

	- DEFAULT_CLEAR_RED:     0.5f
	- DEFAULT_CLEAR_GREEN:   0.5f
	- DEFAULT_CLEAR_BLUE:    0.5f
	- DEFAULT_CLEAR_ALPHA:   1.0f
	- DEFAULT_CLEAR_DEPTH:   1.0f
	- DEFAULT_CLEAR_STENCIL: 0
*/
struct ColorAttachmentAction
{
	Action action;
	float val[4];
};

struct DepthAttachmentAction
{
	Action action;
	float val;
};

struct StencilAttachmentAction
{
	Action action;
	uint8_t val;
};

struct PassAction
{
	XE::uint32 _start_canary;
	ColorAttachmentAction colors[MAX_COLOR_ATTACHMENTS];
	DepthAttachmentAction depth;
	StencilAttachmentAction stencil;
	XE::uint32 _end_canary;
};

/*
	Bindings

	The Bindings structure defines the resource binding slots
	of the sokol_gfx render pipeline, used as argument to the
	apply_bindings() function.

	A resource binding struct contains:

	- 1..N vertex buffers
	- 0..N vertex buffer offsets
	- 0..1 index buffers
	- 0..1 index buffer offsets
	- 0..N vertex shader stage images
	- 0..N fragment shader stage images

	The max number of vertex buffer and shader stage images
	are defined by the MAX_SHADERSTAGE_BUFFERS and
	MAX_SHADERSTAGE_IMAGES configuration constants.

	The optional buffer offsets can be used to put different unrelated
	chunks of vertex- and/or index-data into the same buffer objects.
*/
struct Bindings
{
	XE::uint32 _start_canary;
	BufferHandle vertex_buffers[MAX_SHADERSTAGE_BUFFERS];
	XE::int32 vertex_buffer_offsets[MAX_SHADERSTAGE_BUFFERS];
	BufferHandle index_buffer;
	XE::int32 index_buffer_offset;
	ImageHandle vs_images[MAX_SHADERSTAGE_IMAGES];
	ImageHandle fs_images[MAX_SHADERSTAGE_IMAGES];
	XE::uint32 _end_canary;
};

/*
	BufferDesc

	Creation parameters for BufferHandle objects, used in the
	make_buffer() call.

	The default configuration is:

	.size:      0       (this *must* be set to a valid size in bytes)
	.type:      BUFFERTYPE_VERTEXBUFFER
	.usage:     USAGE_IMMUTABLE
	.content    0
	.label      0       (optional string label for trace hooks)

	The label will be ignored by sokol_gfx.h, it is only useful
	when hooking into make_buffer() or init_buffer() via
	the install_trace_hooks() function.

	ADVANCED TOPIC: Injecting native 3D-API buffers:

	The following struct members allow to inject your own GL, Metal
	or D3D11 buffers into sokol_gfx:

	.gl_buffers[NUM_INFLIGHT_FRAMES]
	.mtl_buffers[NUM_INFLIGHT_FRAMES]
	.d3d11_buffer

	You must still provide all other members except the .content member, and
	these must match the creation parameters of the native buffers you
	provide. For USAGE_IMMUTABLE, only provide a single native 3D-API
	buffer, otherwise you need to provide NUM_INFLIGHT_FRAMES buffers
	(only for GL and Metal, not D3D11). Providing multiple buffers for GL and
	Metal is necessary because sokol_gfx will rotate through them when
	calling update_buffer() to prevent lock-stalls.

	Note that it is expected that immutable injected buffer have already been
	initialized with content, and the .content member must be 0!

	Also you need to call reset_state_cache() after calling native 3D-API
	functions, and before calling any sokol_gfx function.
*/
struct BufferDesc
{
	XE::uint32 _start_canary;
	XE::int32 size;
	BufferType type;
	Usage usage;
	const void * content;
	XE::String label;
	union
	{
		/* GL specific */
		XE::uint32 gl_buffers[NUM_INFLIGHT_FRAMES];
		/* Metal specific */
		const void * mtl_buffers[NUM_INFLIGHT_FRAMES];
		/* D3D11 specific */
		const void * d3d11_buffer;
		/* Everything specific */
		const void * buffer;
	};
	XE::uint32 _end_canary;
};

/*
	SubImageContent

	Pointer to and size of a subimage-surface data, this is
	used to describe the initial content of immutable-usage images,
	or for updating a dynamic- or stream-usage images.

	For 3D- or array-textures, one SubImageContent item
	describes an entire mipmap level consisting of all array- or
	3D-slices of the mipmap level. It is only possible to update
	an entire mipmap level, not parts of it.
*/
struct SubImageContent
{
	const void * ptr;    /* pointer to subimage data */
	XE::int32 size;           /* size in bytes of pointed-to subimage data */
};

/*
	ImageContent

	Defines the content of an image through a 2D array
	of SubImageContent structs. The first array dimension
	is the cubemap face, and the second array dimension the
	mipmap level.
*/
struct ImageContent
{
	SubImageContent subimage[CUBEFACE_NUM][MAX_MIPMAPS];
};

/*
	ImageDesc

	Creation parameters for ImageHandle objects, used in the
	make_image() call.

	The default configuration is:

	.type:              IMAGETYPE_2D
	.render_target:     false
	.width              0 (must be set to >0)
	.height             0 (must be set to >0)
	.depth/.layers:     1
	.num_mipmaps:       1
	.usage:             USAGE_IMMUTABLE
	.pixel_format:      PIXELFORMAT_RGBA8 for textures, backend-dependent
						for render targets (RGBA8 or BGRA8)
	.sample_count:      1 (only used in render_targets)
	.min_filter:        FILTER_NEAREST
	.mag_filter:        FILTER_NEAREST
	.wrap_u:            WRAP_REPEAT
	.wrap_v:            WRAP_REPEAT
	.wrap_w:            WRAP_REPEAT (only IMAGETYPE_3D)
	.border_color       BORDERCOLOR_OPAQUE_BLACK
	.max_anisotropy     1 (must be 1..16)
	.min_lod            0.0f
	.max_lod            FLT_MAX
	.content            an ImageContent struct to define the initial content
	.label              0       (optional string label for trace hooks)

	IMAGETYPE_ARRAY and IMAGETYPE_3D are not supported on
	WebGL/GLES2, use query_features().imagetype_array and
	query_features().imagetype_3d at runtime to check
	if array- and 3D-textures are supported.

	Images with usage USAGE_IMMUTABLE must be fully initialized by
	providing a valid .content member which points to
	initialization data.

	ADVANCED TOPIC: Injecting native 3D-API textures:

	The following struct members allow to inject your own GL, Metal
	or D3D11 textures into sokol_gfx:

	.gl_textures[NUM_INFLIGHT_FRAMES]
	.mtl_textures[NUM_INFLIGHT_FRAMES]
	.d3d11_texture

	The same rules apply as for injecting native buffers
	(see BufferDesc documentation for more details).
*/
struct ImageDesc
{
	XE::uint32 _start_canary;
	ImageType type;
	bool render_target;
	XE::int32 width;
	XE::int32 height;
	union
	{
		XE::int32 depth;
		XE::int32 layers;
	};
	XE::int32 num_mipmaps;
	Usage usage;
	PixelFormat pixel_format;
	XE::int32 sample_count;
	Filter min_filter;
	Filter mag_filter;
	Wrap wrap_u;
	Wrap wrap_v;
	Wrap wrap_w;
	BorderColor border_color;
	XE::uint32 max_anisotropy;
	float min_lod;
	float max_lod;
	ImageContent content;
	XE::String label;
	union
	{
		/* GL specific */
		XE::uint32 gl_textures[NUM_INFLIGHT_FRAMES];
		/* Metal specific */
		const void * mtl_textures[NUM_INFLIGHT_FRAMES];
		/* D3D11 specific */
		const void * d3d11_texture;
		/* Everything specific */
		const void * texture;
	};
	XE::uint32 _end_canary;
};

/*
	ShaderDesc

	The structure ShaderDesc defines all creation parameters
	for shader programs, used as input to the make_shader() function:

	- reflection information for vertex attributes (vertex shader inputs):
		- vertex attribute name (required for GLES2, optional for GLES3 and GL)
		- a semantic name and index (required for D3D11)
	- for each vertex- and fragment-shader-stage:
		- the shader source or bytecode
		- an optional entry function name
		- reflection info for each uniform block used by the shader stage:
			- the size of the uniform block in bytes
			- reflection info for each uniform block member (only required for GL backends):
				- member name
				- member type (UNIFORMTYPE_xxx)
				- if the member is an array, the number of array items
		- reflection info for the texture images used by the shader stage:
			- the image type (IMAGETYPE_xxx)
			- the name of the texture sampler (required for GLES2, optional everywhere else)

	For all GL backends, shader source-code must be provided. For D3D11 and Metal,
	either shader source-code or byte-code can be provided.

	For D3D11, if source code is provided, the d3dcompiler_47.dll will be loaded
	on demand. If this fails, shader creation will fail.
*/
struct ShaderAttrDesc
{
	XE::String name;           /* GLSL vertex attribute name (only required for GLES2) */
	XE::String sem_name;       /* HLSL semantic name */
	XE::int32 sem_index;              /* HLSL semantic index */
};

struct ShaderUniformDesc
{
	XE::String name;
	UniformType type;
	XE::int32 array_count;
};

struct ShaderUniformBlockDesc
{
	XE::int32 size;
	ShaderUniformDesc uniforms[MAX_UB_MEMBERS];
};

struct ShaderImageDesc
{
	XE::String name;
	ImageType type;
};

struct ShaderStageDesc
{
	XE::String source;
	const uint8_t * byte_code;
	XE::int32 byte_code_size;
	XE::String entry;
	ShaderUniformBlockDesc uniform_blocks[MAX_SHADERSTAGE_UBS];
	ShaderImageDesc images[MAX_SHADERSTAGE_IMAGES];
};

struct ShaderDesc
{
	XE::uint32 _start_canary;
	ShaderAttrDesc attrs[MAX_VERTEX_ATTRIBUTES];
	ShaderStageDesc vs;
	ShaderStageDesc fs;
	XE::String label;
	XE::uint32 _end_canary;
};

/*
	PipelineDesc

	The PipelineDesc struct defines all creation parameters
	for an PipelineHandle object, used as argument to the
	make_pipeline() function:

	- the vertex layout for all input vertex buffers
	- a shader object
	- the 3D primitive type (points, lines, triangles, ...)
	- the index type (none, 16- or 32-bit)
	- depth-stencil state
	- alpha-blending state
	- rasterizer state

	If the vertex data has no gaps between vertex components, you can omit
	the .layout.buffers[].stride and layout.attrs[].offset items (leave them
	default-initialized to 0), sokol-gfx will then compute the offsets and strides
	from the vertex component formats (.layout.attrs[].format). Please note
	that ALL vertex attribute offsets must be 0 in order for the
	automatic offset computation to kick in.

	The default configuration is as follows:

	.layout:
		.buffers[]:         vertex buffer layouts
			.stride:        0 (if no stride is given it will be computed)
			.step_func      VERTEXSTEP_PER_VERTEX
			.step_rate      1
		.attrs[]:           vertex attribute declarations
			.buffer_index   0 the vertex buffer bind slot
			.offset         0 (offsets can be omitted if the vertex layout has no gaps)
			.format         VERTEXFORMAT_INVALID (must be initialized!)
	.shader:            0 (must be intilized with a valid ShaderHandle id!)
	.primitive_type:    PRIMITIVETYPE_TRIANGLES
	.index_type:        INDEXTYPE_NONE
	.depth_stencil:
		.stencil_front, .stencil_back:
			.fail_op:               STENCILOP_KEEP
			.depth_fail_op:         STENCILOP_KEEP
			.pass_op:               STENCILOP_KEEP
			.compare_func           COMPAREFUNC_ALWAYS
		.depth_compare_func:    COMPAREFUNC_ALWAYS
		.depth_write_enabled:   false
		.stencil_enabled:       false
		.stencil_read_mask:     0
		.stencil_write_mask:    0
		.stencil_ref:           0
	.blend:
		.enabled:               false
		.src_factor_rgb:        BLENDFACTOR_ONE
		.dst_factor_rgb:        BLENDFACTOR_ZERO
		.op_rgb:                BLENDOP_ADD
		.src_factor_alpha:      BLENDFACTOR_ONE
		.dst_factor_alpha:      BLENDFACTOR_ZERO
		.op_alpha:              BLENDOP_ADD
		.color_write_mask:      COLORMASK_RGBA
		.color_attachment_count 1
		.color_format           PIXELFORMAT_RGBA8
		.depth_format           PIXELFORMAT_DEPTHSTENCIL
		.blend_color:           { 0.0f, 0.0f, 0.0f, 0.0f }
	.rasterizer:
		.alpha_to_coverage_enabled:     false
		.cull_mode:                     CULLMODE_NONE
		.face_winding:                  FACEWINDING_CW
		.sample_count:                  1
		.depth_bias:                    0.0f
		.depth_bias_slope_scale:        0.0f
		.depth_bias_clamp:              0.0f
	.label  0       (optional string label for trace hooks)
*/
struct BufferLayoutDesc
{
	XE::int32 stride;
	VertexStep step_func;
	XE::int32 step_rate;
};

struct VertexAttrDesc
{
	XE::int32 buffer_index;
	XE::int32 offset;
	VertexFormat format;
};

struct LayoutDesc
{
	BufferLayoutDesc buffers[MAX_SHADERSTAGE_BUFFERS];
	VertexAttrDesc attrs[MAX_VERTEX_ATTRIBUTES];
};

struct StencilState
{
	StencilOp fail_op;
	StencilOp depth_fail_op;
	StencilOp pass_op;
	CompareFunc compare_func;
};

struct DepthStencilState
{
	StencilState stencil_front;
	StencilState stencil_back;
	CompareFunc depth_compare_func;
	bool depth_write_enabled;
	bool stencil_enabled;
	uint8_t stencil_read_mask;
	uint8_t stencil_write_mask;
	uint8_t stencil_ref;
};

struct BlendState
{
	bool enabled;
	BlendFactor src_factor_rgb;
	BlendFactor dst_factor_rgb;
	BlendOp op_rgb;
	BlendFactor src_factor_alpha;
	BlendFactor dst_factor_alpha;
	BlendOp op_alpha;
	uint8_t color_write_mask;
	XE::int32 color_attachment_count;
	PixelFormat color_format;
	PixelFormat depth_format;
	float blend_color[4];
};

struct RasterizerState
{
	bool alpha_to_coverage_enabled;
	CullMode cull_mode;
	FaceWinding face_winding;
	XE::int32 sample_count;
	float depth_bias;
	float depth_bias_slope_scale;
	float depth_bias_clamp;
};

struct PipelineDesc
{
	XE::uint32 _start_canary;
	LayoutDesc layout;
	ShaderHandle shader;
	PrimitiveType primitive_type;
	IndexType index_type;
	DepthStencilState depth_stencil;
	BlendState blend;
	RasterizerState rasterizer;
	XE::String label;
	XE::uint32 _end_canary;
};

/*
	PassDesc

	Creation parameters for an PassHandle object, used as argument
	to the make_pass() function.

	A pass object contains 1..4 color-attachments and none, or one,
	depth-stencil-attachment. Each attachment consists of
	an image, and two additional indices describing
	which subimage the pass will render to: one mipmap index, and
	if the image is a cubemap, array-texture or 3D-texture, the
	face-index, array-layer or depth-slice.

	Pass images must fulfill the following requirements:

	All images must have:
	- been created as render target (ImageDesc.render_target = true)
	- the same size
	- the same sample count

	In addition, all color-attachment images must have the same pixel format.
*/
struct AttachmentDesc
{
	ImageHandle image;
	XE::int32 mip_level;
	union
	{
		XE::int32 face;
		XE::int32 layer;
		XE::int32 slice;
	};
};

struct PassDesc
{
	XE::uint32 _start_canary;
	AttachmentDesc color_attachments[MAX_COLOR_ATTACHMENTS];
	AttachmentDesc depth_stencil_attachment;
	XE::String label;
	XE::uint32 _end_canary;
};

/*
	BufferInfo
	ImageInfo
	ShaderInfo
	PipelineInfo
	PassInfo

	These structs contain various internal resource attributes which
	might be useful for debug-inspection. Please don't rely on the
	actual content of those structs too much, as they are quite closely
	tied to sokol_gfx.h internals and may change more frequently than
	the other public API elements.

	The *_info structs are used as the return values of the following functions:

	query_buffer_info()
	query_image_info()
	query_shader_info()
	query_pipeline_info()
	query_pass_info()
*/
struct SlotInfo
{
	ResourceState state;    /* the current state of this resource slot */
	XE::uint32 res_id;        /* type-neutral resource if (e.g. BufferHandle.id) */
	XE::uint32 ctx_id;        /* the context this resource belongs to */
};

struct BufferInfo
{
	SlotInfo slot;              /* resource pool slot info */
	XE::uint32 update_frame_index;    /* frame index of last update_buffer() */
	XE::uint32 append_frame_index;    /* frame index of last append_buffer() */
	XE::int32 append_pos;                 /* current position in buffer for append_buffer() */
	bool append_overflow;           /* is buffer in overflow state (due to append_buffer) */
	XE::int32 num_slots;                  /* number of renaming-slots for dynamically updated buffers */
	XE::int32 active_slot;                /* currently active write-slot for dynamically updated buffers */
};

struct ImageInfo
{
	SlotInfo slot;              /* resource pool slot info */
	XE::uint32 upd_frame_index;       /* frame index of last update_image() */
	XE::int32 num_slots;                  /* number of renaming-slots for dynamically updated images */
	XE::int32 active_slot;                /* currently active write-slot for dynamically updated images */
};

struct ShaderInfo
{
	SlotInfo slot;              /* resoure pool slot info */
};

struct PipelineInfo
{
	SlotInfo slot;              /* resource pool slot info */
};

struct PassInfo
{
	SlotInfo slot;              /* resource pool slot info */
};

/*
	GfxDesc

	The GfxDesc struct contains configuration values for sokol_gfx,
	it is used as parameter to the setup() call.

	The default configuration is:

	.buffer_pool_size:      128
	.image_pool_size:       128
	.shader_pool_size:      32
	.pipeline_pool_size:    64
	.pass_pool_size:        16
	.context_pool_size:     16

	GL specific:
	.gl_force_gles2
		if this is true the GL backend will act in "GLES2 fallback mode" even
		when compiled with SOKOL_GLES3, this is useful to fall back
		to traditional WebGL if a browser doesn't support a WebGL2 context

	Metal specific:
		(NOTE: All Objective-C object references are transferred through
		a bridged (const void*) to sokol_gfx, which will use a unretained
		bridged cast (__bridged id<xxx>) to retrieve the Objective-C
		references back. Since the bridge cast is unretained, the caller
		must hold a strong reference to the Objective-C object for the
		duration of the sokol_gfx call!

	.mtl_device
		a pointer to the MTLDevice object
	.mtl_renderpass_descriptor_cb
		a C callback function to obtain the MTLRenderPassDescriptor for the
		current frame when rendering to the default framebuffer, will be called
		in begin_default_pass()
	.mtl_drawable_cb
		a C callback function to obtain a MTLDrawable for the current
		frame when rendering to the default framebuffer, will be called in
		end_pass() of the default pass
	.mtl_global_uniform_buffer_size
		the size of the global uniform buffer in bytes, this must be big
		enough to hold all uniform block updates for a single frame,
		the default value is 4 MByte (4 * 1024 * 1024)
	.mtl_sampler_cache_size
		the number of slots in the sampler cache, the Metal backend
		will share texture samplers with the same state in this
		cache, the default value is 64

	D3D11 specific:
	.d3d11_device
		a pointer to the ID3D11Device object, this must have been created
		before setup() is called
	.d3d11_device_context
		a pointer to the ID3D11DeviceContext object
	.d3d11_render_target_view_cb
		a C callback function to obtain a pointer to the current
		ID3D11RenderTargetView object of the default framebuffer,
		this function will be called in begin_pass() when rendering
		to the default framebuffer
	.d3d11_depth_stencil_view_cb
		a C callback function to obtain a pointer to the current
		ID3D11DepthStencilView object of the default framebuffer,
		this function will be called in begin_pass() when rendering
		to the default framebuffer
*/
struct GfxDesc
{
	XE::uint32 _start_canary;
	XE::int32 buffer_pool_size;
	XE::int32 image_pool_size;
	XE::int32 shader_pool_size;
	XE::int32 pipeline_pool_size;
	XE::int32 pass_pool_size;
	XE::int32 context_pool_size;
	union
	{
		struct
		{
			/* Metal-specific */
			const void * mtl_device;
			const void * ( *mtl_renderpass_descriptor_cb )( void );
			const void * ( *mtl_drawable_cb )( void );
			XE::int32 mtl_global_uniform_buffer_size;
			XE::int32 mtl_sampler_cache_size;
		};
		struct
		{
			/* D3D11-specific */
			const void * d3d11_device;
			const void * d3d11_device_context;
			const void * ( *d3d11_render_target_view_cb )( void );
			const void * ( *d3d11_depth_stencil_view_cb )( void );
		};
		struct
		{
			/* Everything specific */
			const void * device;
		};
	};
	XE::uint32 _end_canary;
	WindowHandle window_handle;
	XE::uint32 window_width;
	XE::uint32 window_height;
};

END_XE_NAMESPACE

#endif // __TYPE_H__C42D32D2_F661_421A_A1A7_D0EB0BB50848
