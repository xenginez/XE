#if defined(__ANDROID__)

#include "Gfx.h"

USING_XE

#include <GLES3/gl3.h>

#ifndef GL_UNSIGNED_INT_2_10_10_10_REV
#define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#endif
#ifndef GL_UNSIGNED_INT_24_8
#define GL_UNSIGNED_INT_24_8 0x84FA
#endif
#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif
#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#endif
#ifndef GL_COMPRESSED_RED_RGTC1
#define GL_COMPRESSED_RED_RGTC1 0x8DBB
#endif
#ifndef GL_COMPRESSED_SIGNED_RED_RGTC1
#define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8DBC
#endif
#ifndef GL_COMPRESSED_RED_GREEN_RGTC2
#define GL_COMPRESSED_RED_GREEN_RGTC2 0x8DBD
#endif
#ifndef GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2
#define GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2 0x8DBE
#endif
#ifndef GL_COMPRESSED_RGBA_BPTC_UNORM_ARB
#define GL_COMPRESSED_RGBA_BPTC_UNORM_ARB 0x8E8C
#endif
#ifndef GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB
#define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB 0x8E8D
#endif
#ifndef GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB
#define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB 0x8E8E
#endif
#ifndef GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB
#define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB 0x8E8F
#endif
#ifndef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG 0x8C01
#endif
#ifndef GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG 0x8C00
#endif
#ifndef GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#endif
#ifndef GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
#endif
#ifndef GL_COMPRESSED_RGB8_ETC2
#define GL_COMPRESSED_RGB8_ETC2 0x9274
#endif
#ifndef GL_COMPRESSED_RGBA8_ETC2_EAC
#define GL_COMPRESSED_RGBA8_ETC2_EAC 0x9278
#endif
#ifndef GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2
#define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#endif
#ifndef GL_COMPRESSED_RG11_EAC
#define GL_COMPRESSED_RG11_EAC 0x9272
#endif
#ifndef GL_COMPRESSED_SIGNED_RG11_EAC
#define GL_COMPRESSED_SIGNED_RG11_EAC 0x9273
#endif
#ifndef GL_DEPTH24_STENCIL8
#define GL_DEPTH24_STENCIL8 0x88F0
#endif
#ifndef GL_HALF_FLOAT
#define GL_HALF_FLOAT 0x140B
#endif
#ifndef GL_DEPTH_STENCIL
#define GL_DEPTH_STENCIL 0x84F9
#endif
#ifndef GL_LUMINANCE
#define GL_LUMINANCE 0x1909
#endif

#   define SOKOL_INSTANCING_ENABLED
#define _GL_CHECK_ERROR() { XE_ASSERT(glGetError() == GL_NO_ERROR); }

typedef struct
{
	_slot_t slot;
	_buffer_common_t cmn;
	struct
	{
		GLuint buf[NUM_INFLIGHT_FRAMES];
		bool ext_buffers;   /* if true, external buffers were injected with BufferDesc.gl_buffers */
	} gl;
} _gl_buffer_t;
typedef _gl_buffer_t _buffer_t;

typedef struct
{
	_slot_t slot;
	_image_common_t cmn;
	struct
	{
		GLenum target;
		GLuint depth_render_buffer;
		GLuint msaa_render_buffer;
		GLuint tex[NUM_INFLIGHT_FRAMES];
		bool ext_textures;  /* if true, external textures were injected with ImageDesc.gl_textures */
	} gl;
} _gl_image_t;
typedef _gl_image_t _image_t;

typedef struct
{
	GLint gl_loc;
	UniformType type;
	uint8_t count;
	uint16_t offset;
} _gl_uniform_t;

typedef struct
{
	int num_uniforms;
	_gl_uniform_t uniforms[MAX_UB_MEMBERS];
} _gl_uniform_block_t;

typedef struct
{
	GLint gl_loc;
	int gl_tex_slot;
} _gl_shader_image_t;

typedef struct
{
	XE::String name;
} _gl_shader_attr_t;

typedef struct
{
	_gl_uniform_block_t uniform_blocks[MAX_SHADERSTAGE_UBS];
	_gl_shader_image_t images[MAX_SHADERSTAGE_IMAGES];
} _gl_shader_stage_t;

typedef struct
{
	_slot_t slot;
	_shader_common_t cmn;
	struct
	{
		GLuint prog;
		_gl_shader_attr_t attrs[MAX_VERTEX_ATTRIBUTES];
		_gl_shader_stage_t stage[NUM_SHADER_STAGES];
	} gl;
} _gl_shader_t;
typedef _gl_shader_t _shader_t;

typedef struct
{
	int8_t vb_index;        /* -1 if attr is not enabled */
	int8_t divisor;         /* -1 if not initialized */
	uint8_t stride;
	uint8_t size;
	uint8_t normalized;
	int offset;
	GLenum type;
} _gl_attr_t;

typedef struct
{
	_slot_t slot;
	_pipeline_common_t cmn;
	_shader_t * shader;
	struct
	{
		_gl_attr_t attrs[MAX_VERTEX_ATTRIBUTES];
		DepthStencilState depth_stencil;
		PrimitiveType primitive_type;
		BlendState blend;
		RasterizerState rast;
	} gl;
} _gl_pipeline_t;
typedef _gl_pipeline_t _pipeline_t;

typedef struct
{
	_image_t * image;
	GLuint gl_msaa_resolve_buffer;
} _gl_attachment_t;

typedef struct
{
	_slot_t slot;
	_pass_common_t cmn;
	struct
	{
		GLuint fb;
		_gl_attachment_t color_atts[MAX_COLOR_ATTACHMENTS];
		_gl_attachment_t ds_att;
	} gl;
} _gl_pass_t;
typedef _gl_pass_t _pass_t;
typedef _attachment_common_t _attachment_t;

typedef struct
{
	_slot_t slot;
	GLuint vao;
	GLuint default_framebuffer;
} _gl_context_t;
typedef _gl_context_t _context_t;

typedef struct
{
	_gl_attr_t gl_attr;
	GLuint gl_vbuf;
} _gl_cache_attr_t;

typedef struct
{
	GLenum target;
	GLuint texture;
} _gl_texture_bind_slot;

typedef struct
{
	DepthStencilState ds;
	BlendState blend;
	RasterizerState rast;
	bool polygon_offset_enabled;
	_gl_cache_attr_t attrs[MAX_VERTEX_ATTRIBUTES];
	GLuint vertex_buffer;
	GLuint index_buffer;
	GLuint stored_vertex_buffer;
	GLuint stored_index_buffer;
	_gl_texture_bind_slot textures[MAX_SHADERSTAGE_IMAGES];
	_gl_texture_bind_slot stored_texture;
	int cur_ib_offset;
	GLenum cur_primitive_type;
	GLenum cur_index_type;
	_pipeline_t * cur_pipeline;
	PipelineHandle cur_pipeline_id;
} _gl_state_cache_t;

typedef struct
{
	bool valid;
	bool in_pass;
	int cur_pass_width;
	int cur_pass_height;
	_context_t * cur_context;
	_pass_t * cur_pass;
	PassHandle cur_pass_id;
	_gl_state_cache_t cache;
	bool ext_anisotropic;
	GLint max_anisotropy;
	GLint max_combined_texture_image_units;
} _gl_backend_t;
typedef _gl_backend_t _backend_t;

typedef struct
{
	_pool_t buffer_pool;
	_pool_t image_pool;
	_pool_t shader_pool;
	_pool_t pipeline_pool;
	_pool_t pass_pool;
	_pool_t context_pool;
	_buffer_t * buffers;
	_image_t * images;
	_shader_t * shaders;
	_pipeline_t * pipelines;
	_pass_t * passes;
	_context_t * contexts;
} _pools_t;

typedef struct
{
	bool valid;
	GfxDesc desc;       /* original desc with default values patched in */
	uint32_t frame_index;
	ContextHandle active_context;
	PassHandle cur_pass;
	PipelineHandle cur_pipeline;
	bool pass_valid;
	bool bindings_valid;
	bool next_draw_valid;
	_validate_error_t validate_error;
	_pools_t pools;
	Backend backend;
	Features features;
	Limits limits;
	PixelformatInfo formats[_PIXELFORMAT_NUM];
	_gl_backend_t gl;
	GfxTraceHooks * hooks;
} _state_t;

static _state_t _sg;


PixelFormat _default_rendertarget_colorformat( void )
{
	return PIXELFORMAT_RGBA8;
}

/* return true if pixel format is a valid render target format */
bool _is_valid_rendertarget_color_format( PixelFormat fmt )
{
	const int fmt_index = (int )fmt;
	XE_ASSERT( ( fmt_index >= 0 ) && ( fmt_index < _PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index].render && !_sg.formats[fmt_index].depth;
}

/* return true if pixel format is a valid depth format */
bool _is_valid_rendertarget_depth_format( PixelFormat fmt )
{
	const int fmt_index = (int )fmt;
	XE_ASSERT( ( fmt_index >= 0 ) && ( fmt_index < _PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index].render && _sg.formats[fmt_index].depth;
}









/*-- type translation --------------------------------------------------------*/
GLenum _buffer_target( Buffer_type t )
{
	switch( t )
	{
	case BUFFERTYPE_VERTEXBUFFER:    return GL_ARRAY_BUFFER;
	case BUFFERTYPE_INDEXBUFFER:     return GL_ELEMENT_ARRAY_BUFFER;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _texture_target( ImageType t )
{
	switch( t )
	{
	case IMAGETYPE_2D:   return GL_TEXTURE_2D;
	case IMAGETYPE_CUBE: return GL_TEXTURE_CUBE_MAP;
	case IMAGETYPE_3D:       return GL_TEXTURE_3D;
	case IMAGETYPE_ARRAY:    return GL_TEXTURE_2D_ARRAY;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _usage( Usage u )
{
	switch( u )
	{
	case USAGE_IMMUTABLE:    return GL_STATIC_DRAW;
	case USAGE_DYNAMIC:      return GL_DYNAMIC_DRAW;
	case USAGE_STREAM:       return GL_STREAM_DRAW;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _shader_stage( ShaderStage stage )
{
	switch( stage )
	{
	case SHADERSTAGE_VS:     return GL_VERTEX_SHADER;
	case SHADERSTAGE_FS:     return GL_FRAGMENT_SHADER;
	default: XE_ASSERT(false); return 0;
	}
}

GLint _vertexformat_size( VertexFormat fmt )
{
	switch( fmt )
	{
	case VERTEXFORMAT_FLOAT:     return 1;
	case VERTEXFORMAT_FLOAT2:    return 2;
	case VERTEXFORMAT_FLOAT3:    return 3;
	case VERTEXFORMAT_FLOAT4:    return 4;
	case VERTEXFORMAT_BYTE4:     return 4;
	case VERTEXFORMAT_BYTE4N:    return 4;
	case VERTEXFORMAT_UBYTE4:    return 4;
	case VERTEXFORMAT_UBYTE4N:   return 4;
	case VERTEXFORMAT_SHORT2:    return 2;
	case VERTEXFORMAT_SHORT2N:   return 2;
	case VERTEXFORMAT_USHORT2N:  return 2;
	case VERTEXFORMAT_SHORT4:    return 4;
	case VERTEXFORMAT_SHORT4N:   return 4;
	case VERTEXFORMAT_USHORT4N:  return 4;
	case VERTEXFORMAT_UINT10_N2: return 4;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _vertexformat_type( VertexFormat fmt )
{
	switch( fmt )
	{
	case VERTEXFORMAT_FLOAT:
	case VERTEXFORMAT_FLOAT2:
	case VERTEXFORMAT_FLOAT3:
	case VERTEXFORMAT_FLOAT4:
		return GL_FLOAT;
	case VERTEXFORMAT_BYTE4:
	case VERTEXFORMAT_BYTE4N:
		return GL_BYTE;
	case VERTEXFORMAT_UBYTE4:
	case VERTEXFORMAT_UBYTE4N:
		return GL_UNSIGNED_BYTE;
	case VERTEXFORMAT_SHORT2:
	case VERTEXFORMAT_SHORT2N:
	case VERTEXFORMAT_SHORT4:
	case VERTEXFORMAT_SHORT4N:
		return GL_SHORT;
	case VERTEXFORMAT_USHORT2N:
	case VERTEXFORMAT_USHORT4N:
		return GL_UNSIGNED_SHORT;
	case VERTEXFORMAT_UINT10_N2:
		return GL_UNSIGNED_INT_2_10_10_10_REV;
	default:
		XE_ASSERT(false); return 0;
	}
}

GLboolean _vertexformat_normalized( VertexFormat fmt )
{
	switch( fmt )
	{
	case VERTEXFORMAT_BYTE4N:
	case VERTEXFORMAT_UBYTE4N:
	case VERTEXFORMAT_SHORT2N:
	case VERTEXFORMAT_USHORT2N:
	case VERTEXFORMAT_SHORT4N:
	case VERTEXFORMAT_USHORT4N:
	case VERTEXFORMAT_UINT10_N2:
		return GL_TRUE;
	default:
		return GL_FALSE;
	}
}

GLenum _primitive_type( PrimitiveType t )
{
	switch( t )
	{
	case PRIMITIVETYPE_POINTS:           return GL_POINTS;
	case PRIMITIVETYPE_LINES:            return GL_LINES;
	case PRIMITIVETYPE_LINE_STRIP:       return GL_LINE_STRIP;
	case PRIMITIVETYPE_TRIANGLES:        return GL_TRIANGLES;
	case PRIMITIVETYPE_TRIANGLE_STRIP:   return GL_TRIANGLE_STRIP;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _index_type( IndexType t )
{
	switch( t )
	{
	case INDEXTYPE_NONE:     return 0;
	case INDEXTYPE_UINT16:   return GL_UNSIGNED_SHORT;
	case INDEXTYPE_UINT32:   return GL_UNSIGNED_INT;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _compare_func( CompareFunc cmp )
{
	switch( cmp )
	{
	case COMPAREFUNC_NEVER:          return GL_NEVER;
	case COMPAREFUNC_LESS:           return GL_LESS;
	case COMPAREFUNC_EQUAL:          return GL_EQUAL;
	case COMPAREFUNC_LESS_EQUAL:     return GL_LEQUAL;
	case COMPAREFUNC_GREATER:        return GL_GREATER;
	case COMPAREFUNC_NOT_EQUAL:      return GL_NOTEQUAL;
	case COMPAREFUNC_GREATER_EQUAL:  return GL_GEQUAL;
	case COMPAREFUNC_ALWAYS:         return GL_ALWAYS;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _stencil_op( StencilOp op )
{
	switch( op )
	{
	case STENCILOP_KEEP:         return GL_KEEP;
	case STENCILOP_ZERO:         return GL_ZERO;
	case STENCILOP_REPLACE:      return GL_REPLACE;
	case STENCILOP_INCR_CLAMP:   return GL_INCR;
	case STENCILOP_DECR_CLAMP:   return GL_DECR;
	case STENCILOP_INVERT:       return GL_INVERT;
	case STENCILOP_INCR_WRAP:    return GL_INCR_WRAP;
	case STENCILOP_DECR_WRAP:    return GL_DECR_WRAP;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _blend_factor( BlendFactor f )
{
	switch( f )
	{
	case BLENDFACTOR_ZERO:                   return GL_ZERO;
	case BLENDFACTOR_ONE:                    return GL_ONE;
	case BLENDFACTOR_SRC_COLOR:              return GL_SRC_COLOR;
	case BLENDFACTOR_ONE_MINUS_SRC_COLOR:    return GL_ONE_MINUS_SRC_COLOR;
	case BLENDFACTOR_SRC_ALPHA:              return GL_SRC_ALPHA;
	case BLENDFACTOR_ONE_MINUS_SRC_ALPHA:    return GL_ONE_MINUS_SRC_ALPHA;
	case BLENDFACTOR_DST_COLOR:              return GL_DST_COLOR;
	case BLENDFACTOR_ONE_MINUS_DST_COLOR:    return GL_ONE_MINUS_DST_COLOR;
	case BLENDFACTOR_DST_ALPHA:              return GL_DST_ALPHA;
	case BLENDFACTOR_ONE_MINUS_DST_ALPHA:    return GL_ONE_MINUS_DST_ALPHA;
	case BLENDFACTOR_SRC_ALPHA_SATURATED:    return GL_SRC_ALPHA_SATURATE;
	case BLENDFACTOR_BLEND_COLOR:            return GL_CONSTANT_COLOR;
	case BLENDFACTOR_ONE_MINUS_BLEND_COLOR:  return GL_ONE_MINUS_CONSTANT_COLOR;
	case BLENDFACTOR_BLEND_ALPHA:            return GL_CONSTANT_ALPHA;
	case BLENDFACTOR_ONE_MINUS_BLEND_ALPHA:  return GL_ONE_MINUS_CONSTANT_ALPHA;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _blend_op( BlendOp op )
{
	switch( op )
	{
	case BLENDOP_ADD:                return GL_FUNC_ADD;
	case BLENDOP_SUBTRACT:           return GL_FUNC_SUBTRACT;
	case BLENDOP_REVERSE_SUBTRACT:   return GL_FUNC_REVERSE_SUBTRACT;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _filter( Filter f )
{
	switch( f )
	{
	case FILTER_NEAREST:                 return GL_NEAREST;
	case FILTER_LINEAR:                  return GL_LINEAR;
	case FILTER_NEAREST_MIPMAP_NEAREST:  return GL_NEAREST_MIPMAP_NEAREST;
	case FILTER_NEAREST_MIPMAP_LINEAR:   return GL_NEAREST_MIPMAP_LINEAR;
	case FILTER_LINEAR_MIPMAP_NEAREST:   return GL_LINEAR_MIPMAP_NEAREST;
	case FILTER_LINEAR_MIPMAP_LINEAR:    return GL_LINEAR_MIPMAP_LINEAR;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _wrap( Wrap w )
{
	switch( w )
	{
	case WRAP_CLAMP_TO_EDGE:     return GL_CLAMP_TO_EDGE;
	case WRAP_CLAMP_TO_BORDER:   return GL_CLAMP_TO_EDGE;
	case WRAP_REPEAT:            return GL_REPEAT;
	case WRAP_MIRRORED_REPEAT:   return GL_MIRRORED_REPEAT;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _teximage_type( PixelFormat fmt )
{
	switch( fmt )
	{
	case PIXELFORMAT_R8:
	case PIXELFORMAT_R8UI:
	case PIXELFORMAT_RG8:
	case PIXELFORMAT_RG8UI:
	case PIXELFORMAT_RGBA8:
	case PIXELFORMAT_RGBA8UI:
	case PIXELFORMAT_BGRA8:
		return GL_UNSIGNED_BYTE;
	case PIXELFORMAT_R8SN:
	case PIXELFORMAT_R8SI:
	case PIXELFORMAT_RG8SN:
	case PIXELFORMAT_RG8SI:
	case PIXELFORMAT_RGBA8SN:
	case PIXELFORMAT_RGBA8SI:
		return GL_BYTE;
	case PIXELFORMAT_R16:
	case PIXELFORMAT_R16UI:
	case PIXELFORMAT_RG16:
	case PIXELFORMAT_RG16UI:
	case PIXELFORMAT_RGBA16:
	case PIXELFORMAT_RGBA16UI:
		return GL_UNSIGNED_SHORT;
	case PIXELFORMAT_R16SN:
	case PIXELFORMAT_R16SI:
	case PIXELFORMAT_RG16SN:
	case PIXELFORMAT_RG16SI:
	case PIXELFORMAT_RGBA16SN:
	case PIXELFORMAT_RGBA16SI:
		return GL_SHORT;
	case PIXELFORMAT_R16F:
	case PIXELFORMAT_RG16F:
	case PIXELFORMAT_RGBA16F:
		return GL_HALF_FLOAT;
	case PIXELFORMAT_R32UI:
	case PIXELFORMAT_RG32UI:
	case PIXELFORMAT_RGBA32UI:
		return GL_UNSIGNED_INT;
	case PIXELFORMAT_R32SI:
	case PIXELFORMAT_RG32SI:
	case PIXELFORMAT_RGBA32SI:
		return GL_INT;
	case PIXELFORMAT_R32F:
	case PIXELFORMAT_RG32F:
	case PIXELFORMAT_RGBA32F:
		return GL_FLOAT;
	case PIXELFORMAT_RGB10A2:
		return GL_UNSIGNED_INT_2_10_10_10_REV;
	case PIXELFORMAT_RG11B10F:
		return GL_UNSIGNED_INT_10F_11F_11F_REV;
	case PIXELFORMAT_DEPTH:
		return GL_UNSIGNED_SHORT;
	case PIXELFORMAT_DEPTH_STENCIL:
		return GL_UNSIGNED_INT_24_8;
	default:
		XE_ASSERT(false); return 0;
	}
}

GLenum _teximage_format( PixelFormat fmt )
{
	switch( fmt )
	{
	case PIXELFORMAT_R8:
	case PIXELFORMAT_R8SN:
	case PIXELFORMAT_R16:
	case PIXELFORMAT_R16SN:
	case PIXELFORMAT_R16F:
	case PIXELFORMAT_R32F:
		return GL_RED;
	case PIXELFORMAT_R8UI:
	case PIXELFORMAT_R8SI:
	case PIXELFORMAT_R16UI:
	case PIXELFORMAT_R16SI:
	case PIXELFORMAT_R32UI:
	case PIXELFORMAT_R32SI:
		return GL_RED_INTEGER;
	case PIXELFORMAT_RG8:
	case PIXELFORMAT_RG8SN:
	case PIXELFORMAT_RG16:
	case PIXELFORMAT_RG16SN:
	case PIXELFORMAT_RG16F:
	case PIXELFORMAT_RG32F:
		return GL_RG;
	case PIXELFORMAT_RG8UI:
	case PIXELFORMAT_RG8SI:
	case PIXELFORMAT_RG16UI:
	case PIXELFORMAT_RG16SI:
	case PIXELFORMAT_RG32UI:
	case PIXELFORMAT_RG32SI:
		return GL_RG_INTEGER;
	case PIXELFORMAT_RGBA8:
	case PIXELFORMAT_RGBA8SN:
	case PIXELFORMAT_RGBA16:
	case PIXELFORMAT_RGBA16SN:
	case PIXELFORMAT_RGBA16F:
	case PIXELFORMAT_RGBA32F:
	case PIXELFORMAT_RGB10A2:
		return GL_RGBA;
	case PIXELFORMAT_RGBA8UI:
	case PIXELFORMAT_RGBA8SI:
	case PIXELFORMAT_RGBA16UI:
	case PIXELFORMAT_RGBA16SI:
	case PIXELFORMAT_RGBA32UI:
	case PIXELFORMAT_RGBA32SI:
		return GL_RGBA_INTEGER;
	case PIXELFORMAT_RG11B10F:
		return GL_RGB;
	case PIXELFORMAT_DEPTH:
		return GL_DEPTH_COMPONENT;
	case PIXELFORMAT_DEPTH_STENCIL:
		return GL_DEPTH_STENCIL;
	case PIXELFORMAT_BC1_RGBA:
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case PIXELFORMAT_BC2_RGBA:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case PIXELFORMAT_BC3_RGBA:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case PIXELFORMAT_BC4_R:
		return GL_COMPRESSED_RED_RGTC1;
	case PIXELFORMAT_BC4_RSN:
		return GL_COMPRESSED_SIGNED_RED_RGTC1;
	case PIXELFORMAT_BC5_RG:
		return GL_COMPRESSED_RED_GREEN_RGTC2;
	case PIXELFORMAT_BC5_RGSN:
		return GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2;
	case PIXELFORMAT_BC6H_RGBF:
		return GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB;
	case PIXELFORMAT_BC6H_RGBUF:
		return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;
	case PIXELFORMAT_BC7_RGBA:
		return GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
	case PIXELFORMAT_PVRTC_RGB_2BPP:
		return GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
	case PIXELFORMAT_PVRTC_RGB_4BPP:
		return GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
	case PIXELFORMAT_PVRTC_RGBA_2BPP:
		return GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
	case PIXELFORMAT_PVRTC_RGBA_4BPP:
		return GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
	case PIXELFORMAT_ETC2_RGB8:
		return GL_COMPRESSED_RGB8_ETC2;
	case PIXELFORMAT_ETC2_RGB8A1:
		return GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2;
	case PIXELFORMAT_ETC2_RGBA8:
		return GL_COMPRESSED_RGBA8_ETC2_EAC;
	case PIXELFORMAT_ETC2_RG11:
		return GL_COMPRESSED_RG11_EAC;
	case PIXELFORMAT_ETC2_RG11SN:
		return GL_COMPRESSED_SIGNED_RG11_EAC;
	default:
		XE_ASSERT(false); return 0;
	}
}

GLenum _teximage_internal_format( PixelFormat fmt )
{
	switch( fmt )
	{
	case PIXELFORMAT_R8:         return GL_R8;
	case PIXELFORMAT_R8SN:       return GL_R8_SNORM;
	case PIXELFORMAT_R8UI:       return GL_R8UI;
	case PIXELFORMAT_R8SI:       return GL_R8I;
	case PIXELFORMAT_R16UI:      return GL_R16UI;
	case PIXELFORMAT_R16SI:      return GL_R16I;
	case PIXELFORMAT_R16F:       return GL_R16F;
	case PIXELFORMAT_RG8:        return GL_RG8;
	case PIXELFORMAT_RG8SN:      return GL_RG8_SNORM;
	case PIXELFORMAT_RG8UI:      return GL_RG8UI;
	case PIXELFORMAT_RG8SI:      return GL_RG8I;
	case PIXELFORMAT_R32UI:      return GL_R32UI;
	case PIXELFORMAT_R32SI:      return GL_R32I;
	case PIXELFORMAT_R32F:       return GL_R32F;
	case PIXELFORMAT_RG16UI:     return GL_RG16UI;
	case PIXELFORMAT_RG16SI:     return GL_RG16I;
	case PIXELFORMAT_RG16F:      return GL_RG16F;
	case PIXELFORMAT_RGBA8:      return GL_RGBA8;
	case PIXELFORMAT_RGBA8SN:    return GL_RGBA8_SNORM;
	case PIXELFORMAT_RGBA8UI:    return GL_RGBA8UI;
	case PIXELFORMAT_RGBA8SI:    return GL_RGBA8I;
	case PIXELFORMAT_RGB10A2:    return GL_RGB10_A2;
	case PIXELFORMAT_RG11B10F:   return GL_R11F_G11F_B10F;
	case PIXELFORMAT_RG32UI:     return GL_RG32UI;
	case PIXELFORMAT_RG32SI:     return GL_RG32I;
	case PIXELFORMAT_RG32F:      return GL_RG32F;
	case PIXELFORMAT_RGBA16UI:   return GL_RGBA16UI;
	case PIXELFORMAT_RGBA16SI:   return GL_RGBA16I;
	case PIXELFORMAT_RGBA16F:    return GL_RGBA16F;
	case PIXELFORMAT_RGBA32UI:   return GL_RGBA32UI;
	case PIXELFORMAT_RGBA32SI:   return GL_RGBA32I;
	case PIXELFORMAT_RGBA32F:    return GL_RGBA32F;
	case PIXELFORMAT_DEPTH:      return GL_DEPTH_COMPONENT16;
	case PIXELFORMAT_DEPTH_STENCIL:      return GL_DEPTH24_STENCIL8;
	case PIXELFORMAT_BC1_RGBA:           return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case PIXELFORMAT_BC2_RGBA:           return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case PIXELFORMAT_BC3_RGBA:           return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	case PIXELFORMAT_BC4_R:              return GL_COMPRESSED_RED_RGTC1;
	case PIXELFORMAT_BC4_RSN:            return GL_COMPRESSED_SIGNED_RED_RGTC1;
	case PIXELFORMAT_BC5_RG:             return GL_COMPRESSED_RED_GREEN_RGTC2;
	case PIXELFORMAT_BC5_RGSN:           return GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2;
	case PIXELFORMAT_BC6H_RGBF:          return GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB;
	case PIXELFORMAT_BC6H_RGBUF:         return GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;
	case PIXELFORMAT_BC7_RGBA:           return GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
	case PIXELFORMAT_PVRTC_RGB_2BPP:     return GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
	case PIXELFORMAT_PVRTC_RGB_4BPP:     return GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
	case PIXELFORMAT_PVRTC_RGBA_2BPP:    return GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
	case PIXELFORMAT_PVRTC_RGBA_4BPP:    return GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
	case PIXELFORMAT_ETC2_RGB8:          return GL_COMPRESSED_RGB8_ETC2;
	case PIXELFORMAT_ETC2_RGB8A1:        return GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2;
	case PIXELFORMAT_ETC2_RGBA8:         return GL_COMPRESSED_RGBA8_ETC2_EAC;
	case PIXELFORMAT_ETC2_RG11:          return GL_COMPRESSED_RG11_EAC;
	case PIXELFORMAT_ETC2_RG11SN:        return GL_COMPRESSED_SIGNED_RG11_EAC;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _cubeface_target( int face_index )
{
	switch( face_index )
	{
	case 0: return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	case 1: return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
	case 2: return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
	case 3: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
	case 4: return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
	case 5: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
	default: XE_ASSERT(false); return 0;
	}
}

GLenum _depth_attachment_format( PixelFormat fmt )
{
	switch( fmt )
	{
	case PIXELFORMAT_DEPTH:          return GL_DEPTH_COMPONENT16;
	case PIXELFORMAT_DEPTH_STENCIL:  return GL_DEPTH24_STENCIL8;
	default: XE_ASSERT(false); return 0;
	}
}

void _init_attr( _gl_attr_t * attr )
{
	attr->vb_index = -1;
	attr->divisor = -1;
}

void _init_stencil_state( StencilState * s )
{
	XE_ASSERT( s );
	s->fail_op = STENCILOP_KEEP;
	s->depth_fail_op = STENCILOP_KEEP;
	s->pass_op = STENCILOP_KEEP;
	s->compare_func = COMPAREFUNC_ALWAYS;
}

void _init_depth_stencil_state( DepthStencilState * s )
{
	XE_ASSERT( s );
	_init_stencil_state( &s->stencil_front );
	_init_stencil_state( &s->stencil_back );
	s->depth_compare_func = COMPAREFUNC_ALWAYS;
}

void _init_blend_state( BlendState * s )
{
	XE_ASSERT( s );
	s->src_factor_rgb = BLENDFACTOR_ONE;
	s->dst_factor_rgb = BLENDFACTOR_ZERO;
	s->op_rgb = BLENDOP_ADD;
	s->src_factor_alpha = BLENDFACTOR_ONE;
	s->dst_factor_alpha = BLENDFACTOR_ZERO;
	s->op_alpha = BLENDOP_ADD;
	s->color_write_mask = COLORMASK_RGBA;
}

void _init_rasterizer_state( RasterizerState * s )
{
	XE_ASSERT( s );
	s->cull_mode = CULLMODE_NONE;
	s->face_winding = FACEWINDING_CW;
	s->sample_count = 1;
}

/* see: https://www.khronos.org/registry/OpenGL-Refpages/es3.0/html/glTexImage2D.xhtml */
void _init_pixelformats( bool has_bgra )
{
	_pixelformat_all( &_sg.formats[PIXELFORMAT_R8] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_R8SN] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_R8UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_R8SI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_R16UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_R16SI] );
	_pixelformat_all( &_sg.formats[PIXELFORMAT_RG8] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_RG8SN] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RG8UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RG8SI] );
	_pixelformat_sr( &_sg.formats[PIXELFORMAT_R32UI] );
	_pixelformat_sr( &_sg.formats[PIXELFORMAT_R32SI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RG16UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RG16SI] );
	_pixelformat_all( &_sg.formats[PIXELFORMAT_RGBA8] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_RGBA8SN] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RGBA8UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RGBA8SI] );
	if( has_bgra )
	{
		_pixelformat_all( &_sg.formats[PIXELFORMAT_BGRA8] );
	}
	_pixelformat_all( &_sg.formats[PIXELFORMAT_RGB10A2] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_RG11B10F] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RG32UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RG32SI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RGBA16UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RGBA16SI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RGBA32UI] );
	_pixelformat_srm( &_sg.formats[PIXELFORMAT_RGBA32SI] );
	// FIXME: WEBGL_depth_texture extension?
	_pixelformat_srmd( &_sg.formats[PIXELFORMAT_DEPTH] );
	_pixelformat_srmd( &_sg.formats[PIXELFORMAT_DEPTH_STENCIL] );
}

/* FIXME: OES_half_float_blend */
void _init_pixelformats_half_float( bool has_colorbuffer_half_float, bool has_texture_half_float_linear )
{
	if( has_texture_half_float_linear )
	{
		if( has_colorbuffer_half_float )
		{
			_pixelformat_all( &_sg.formats[PIXELFORMAT_R16F] );
			_pixelformat_all( &_sg.formats[PIXELFORMAT_RG16F] );
			_pixelformat_all( &_sg.formats[PIXELFORMAT_RGBA16F] );
		}
		else
		{
			_pixelformat_sf( &_sg.formats[PIXELFORMAT_R16F] );
			_pixelformat_sf( &_sg.formats[PIXELFORMAT_RG16F] );
			_pixelformat_sf( &_sg.formats[PIXELFORMAT_RGBA16F] );
		}
	}
	else
	{
		if( has_colorbuffer_half_float )
		{
			_pixelformat_sbrm( &_sg.formats[PIXELFORMAT_R16F] );
			_pixelformat_sbrm( &_sg.formats[PIXELFORMAT_RG16F] );
			_pixelformat_sbrm( &_sg.formats[PIXELFORMAT_RGBA16F] );
		}
		else
		{
			_pixelformat_s( &_sg.formats[PIXELFORMAT_R16F] );
			_pixelformat_s( &_sg.formats[PIXELFORMAT_RG16F] );
			_pixelformat_s( &_sg.formats[PIXELFORMAT_RGBA16F] );
		}
	}
}

void _init_pixelformats_float( bool has_colorbuffer_float, bool has_texture_float_linear, bool has_float_blend )
{
	if( has_texture_float_linear )
	{
		if( has_colorbuffer_float )
		{
			if( has_float_blend )
			{
				_pixelformat_all( &_sg.formats[PIXELFORMAT_R32F] );
				_pixelformat_all( &_sg.formats[PIXELFORMAT_RG32F] );
				_pixelformat_all( &_sg.formats[PIXELFORMAT_RGBA32F] );
			}
			else
			{
				_pixelformat_sfrm( &_sg.formats[PIXELFORMAT_R32F] );
				_pixelformat_sfrm( &_sg.formats[PIXELFORMAT_RG32F] );
				_pixelformat_sfrm( &_sg.formats[PIXELFORMAT_RGBA32F] );
			}
		}
		else
		{
			_pixelformat_sf( &_sg.formats[PIXELFORMAT_R32F] );
			_pixelformat_sf( &_sg.formats[PIXELFORMAT_RG32F] );
			_pixelformat_sf( &_sg.formats[PIXELFORMAT_RGBA32F] );
		}
	}
	else
	{
		if( has_colorbuffer_float )
		{
			_pixelformat_sbrm( &_sg.formats[PIXELFORMAT_R32F] );
			_pixelformat_sbrm( &_sg.formats[PIXELFORMAT_RG32F] );
			_pixelformat_sbrm( &_sg.formats[PIXELFORMAT_RGBA32F] );
		}
		else
		{
			_pixelformat_s( &_sg.formats[PIXELFORMAT_R32F] );
			_pixelformat_s( &_sg.formats[PIXELFORMAT_RG32F] );
			_pixelformat_s( &_sg.formats[PIXELFORMAT_RGBA32F] );
		}
	}
}

void _init_pixelformats_s3tc( void )
{
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC1_RGBA] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC2_RGBA] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC3_RGBA] );
}

void _init_pixelformats_rgtc( void )
{
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC4_R] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC4_RSN] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC5_RG] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC5_RGSN] );
}

void _init_pixelformats_bptc( void )
{
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC6H_RGBF] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC6H_RGBUF] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_BC7_RGBA] );
}

void _init_pixelformats_pvrtc( void )
{
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_PVRTC_RGB_2BPP] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_PVRTC_RGB_4BPP] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_PVRTC_RGBA_2BPP] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_PVRTC_RGBA_4BPP] );
}

void _init_pixelformats_etc2( void )
{
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_ETC2_RGB8] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_ETC2_RGB8A1] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_ETC2_RGBA8] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_ETC2_RG11] );
	_pixelformat_sf( &_sg.formats[PIXELFORMAT_ETC2_RG11SN] );
}

void _init_limits( void )
{
	_GL_CHECK_ERROR();
	GLint gl_int;
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, &gl_int );
	_GL_CHECK_ERROR();
	_sg.limits.max_image_size_2d = gl_int;
	_sg.limits.max_image_size_array = gl_int;
	glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, &gl_int );
	_GL_CHECK_ERROR();
	_sg.limits.max_image_size_cube = gl_int;
	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &gl_int );
	_GL_CHECK_ERROR();
	if( gl_int > MAX_VERTEX_ATTRIBUTES )
	{
		gl_int = MAX_VERTEX_ATTRIBUTES;
	}
	_sg.limits.max_vertex_attrs = gl_int;

	glGetIntegerv( GL_MAX_3D_TEXTURE_SIZE, &gl_int );
	_GL_CHECK_ERROR();
	_sg.limits.max_image_size_3d = gl_int;
	glGetIntegerv( GL_MAX_ARRAY_TEXTURE_LAYERS, &gl_int );
	_GL_CHECK_ERROR();
	_sg.limits.max_image_array_layers = gl_int;

	if( _sg.gl.ext_anisotropic )
	{
		glGetIntegerv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &gl_int );
		_GL_CHECK_ERROR();
		_sg.gl.max_anisotropy = gl_int;
	}
	else
	{
		_sg.gl.max_anisotropy = 1;
	}
	glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &gl_int );
	_GL_CHECK_ERROR();
	_sg.gl.max_combined_texture_image_units = gl_int;
}

void _init_caps_gles3( void )
{
	_sg.backend = BACKEND_GLES3;

	_sg.features.origin_top_left = false;
	_sg.features.instancing = true;
	_sg.features.multiple_render_targets = true;
	_sg.features.msaa_render_targets = true;
	_sg.features.imagetype_3d = true;
	_sg.features.imagetype_array = true;
	_sg.features.image_clamp_to_border = false;

	bool has_s3tc = false;  /* BC1..BC3 */
	bool has_rgtc = false;  /* BC4 and BC5 */
	bool has_bptc = false;  /* BC6H and BC7 */
	bool has_pvrtc = false;
#if defined(__EMSCRIPTEN__)
	bool has_etc2 = false;
#else
	bool has_etc2 = true;
#endif
	bool has_colorbuffer_float = false;
	bool has_colorbuffer_half_float = false;
	bool has_texture_float_linear = false;
	bool has_float_blend = false;
	GLint num_ext = 0;
	glGetIntegerv( GL_NUM_EXTENSIONS, &num_ext );
	for( int i = 0; i < num_ext; i++ )
	{
		XE::String ext = glGetStringi( GL_EXTENSIONS, i );
		if( ext != "" )
		{
			if( ext == "_texture_compression_s3tc" )
			{
				has_s3tc = true;
			}
			else if( ext == "_compressed_texture_s3tc" )
			{
				has_s3tc = true;
			}
			else if( ext == "_texture_compression_rgtc" )
			{
				has_rgtc = true;
			}
			else if( ext == "_texture_compression_bptc" )
			{
				has_bptc = true;
			}
			else if( ext == "_texture_compression_pvrtc" )
			{
				has_pvrtc = true;
			}
			else if( ext == "_compressed_texture_etc" )
			{
				has_etc2 = true;
			}
			else if( ext == "_color_buffer_float" )
			{
				has_colorbuffer_float = true;
			}
			else if( ext == "_color_buffer_half_float" )
			{
				has_colorbuffer_half_float = true;
			}
			else if( ext == "_texture_float_linear" )
			{
				has_texture_float_linear = true;
			}
			else if( ext == "_float_blend" )
			{
				has_float_blend = true;
			}
			else if( ext == "_texture_filter_anisotropic" )
			{
				_sg.gl.ext_anisotropic = true;
			}
		}
	}

	/* limits */
	_init_limits();

	/* pixel formats */
	const bool has_texture_half_float_linear = true;
	const bool has_bgra = false;    /* not a bug */
	_init_pixelformats( has_bgra );
	_init_pixelformats_float( has_colorbuffer_float, has_texture_float_linear, has_float_blend );
	_init_pixelformats_half_float( has_colorbuffer_half_float, has_texture_half_float_linear );
	if( has_s3tc )
	{
		_init_pixelformats_s3tc();
	}
	if( has_rgtc )
	{
		_init_pixelformats_rgtc();
	}
	if( has_bptc )
	{
		_init_pixelformats_bptc();
	}
	if( has_pvrtc )
	{
		_init_pixelformats_pvrtc();
	}
	if( has_etc2 )
	{
		_init_pixelformats_etc2();
	}
}

/*-- state cache implementation ----------------------------------------------*/
void _clear_buffer_bindings( bool force )
{
	if( force || ( _sg.gl.cache.vertex_buffer != 0 ) )
	{
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		_sg.gl.cache.vertex_buffer = 0;
	}
	if( force || ( _sg.gl.cache.index_buffer != 0 ) )
	{
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		_sg.gl.cache.index_buffer = 0;
	}
}

void _bind_buffer( GLenum target, GLuint buffer )
{
	XE_ASSERT( ( GL_ARRAY_BUFFER == target ) || ( GL_ELEMENT_ARRAY_BUFFER == target ) );
	if( target == GL_ARRAY_BUFFER )
	{
		if( _sg.gl.cache.vertex_buffer != buffer )
		{
			_sg.gl.cache.vertex_buffer = buffer;
			glBindBuffer( target, buffer );
		}
	}
	else
	{
		if( _sg.gl.cache.index_buffer != buffer )
		{
			_sg.gl.cache.index_buffer = buffer;
			glBindBuffer( target, buffer );
		}
	}
}

void _store_buffer_binding( GLenum target )
{
	if( target == GL_ARRAY_BUFFER )
	{
		_sg.gl.cache.stored_vertex_buffer = _sg.gl.cache.vertex_buffer;
	}
	else
	{
		_sg.gl.cache.stored_index_buffer = _sg.gl.cache.index_buffer;
	}
}

void _restore_buffer_binding( GLenum target )
{
	if( target == GL_ARRAY_BUFFER )
	{
		_bind_buffer( target, _sg.gl.cache.stored_vertex_buffer );
	}
	else
	{
		_bind_buffer( target, _sg.gl.cache.stored_index_buffer );
	}
}

void _clear_texture_bindings( bool force )
{
	for( int i = 0; ( i < MAX_SHADERSTAGE_IMAGES ) && ( i < _sg.gl.max_combined_texture_image_units ); i++ )
	{
		if( force || ( _sg.gl.cache.textures[i].texture != 0 ) )
		{
			glActiveTexture( GL_TEXTURE0 + i );
			glBindTexture( GL_TEXTURE_2D, 0 );
			glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
			glBindTexture( GL_TEXTURE_3D, 0 );
			glBindTexture( GL_TEXTURE_2D_ARRAY, 0 );
			_sg.gl.cache.textures[i].target = 0;
			_sg.gl.cache.textures[i].texture = 0;
		}
	}
}

void _bind_texture( int slot_index, GLenum target, GLuint texture )
{
	/* it's valid to call this function with target=0 and/or texture=0
	   target=0 will unbind the previous binding, texture=0 will clear
	   the new binding
	*/
	XE_ASSERT( slot_index < MAX_SHADERSTAGE_IMAGES );
	if( slot_index >= _sg.gl.max_combined_texture_image_units )
	{
		return;
	}
	_gl_texture_bind_slot * slot = &_sg.gl.cache.textures[slot_index];
	if( ( slot->target != target ) || ( slot->texture != texture ) )
	{
		glActiveTexture( GL_TEXTURE0 + slot_index );
		/* if the target has changed, clear the previous binding on that target */
		if( ( target != slot->target ) && ( slot->target != 0 ) )
		{
			glBindTexture( slot->target, 0 );
		}
		/* apply new binding (texture can be 0 to unbind) */
		if( target != 0 )
		{
			glBindTexture( target, texture );
		}
		slot->target = target;
		slot->texture = texture;
	}
}

void _store_texture_binding( int slot_index )
{
	XE_ASSERT( slot_index < MAX_SHADERSTAGE_IMAGES );
	_sg.gl.cache.stored_texture = _sg.gl.cache.textures[slot_index];
}

void _restore_texture_binding( int slot_index )
{
	XE_ASSERT( slot_index < MAX_SHADERSTAGE_IMAGES );
	const _gl_texture_bind_slot * slot = &_sg.gl.cache.stored_texture;
	_bind_texture( slot_index, slot->target, slot->texture );
}

void _setup_backend( const GfxDesc * desc )
{
	/* assumes that _sg.gl is already zero-initialized */
	_sg.gl.valid = true;

	/* clear initial GL error state */
	while( glGetError() != GL_NO_ERROR );

	_init_caps_gles3();
}

void _discard_backend( void )
{
	XE_ASSERT( _sg.gl.valid );
	_sg.gl.valid = false;
}

void _reset_state_cache( void )
{
	if( _sg.gl.cur_context )
	{
		_GL_CHECK_ERROR();
		glBindVertexArray( _sg.gl.cur_context->vao );
		_GL_CHECK_ERROR();
		memset( &_sg.gl.cache, 0, sizeof( _sg.gl.cache ) );
		_clear_buffer_bindings( true );
		_GL_CHECK_ERROR();
		_clear_texture_bindings( true );
		_GL_CHECK_ERROR();
		for( uint32_t i = 0; i < _sg.limits.max_vertex_attrs; i++ )
		{
			_init_attr( &_sg.gl.cache.attrs[i].gl_attr );
			glDisableVertexAttribArray( i );
			_GL_CHECK_ERROR();
		}
		_sg.gl.cache.cur_primitive_type = GL_TRIANGLES;

		/* depth-stencil state */
		_init_depth_stencil_state( &_sg.gl.cache.ds );
		glEnable( GL_DEPTH_TEST );
		glDepthFunc( GL_ALWAYS );
		glDepthMask( GL_FALSE );
		glDisable( GL_STENCIL_TEST );
		glStencilFunc( GL_ALWAYS, 0, 0 );
		glStencilOp( GL_KEEP, GL_KEEP, GL_KEEP );
		glStencilMask( 0 );

		/* blend state */
		_init_blend_state( &_sg.gl.cache.blend );
		glDisable( GL_BLEND );
		glBlendFuncSeparate( GL_ONE, GL_ZERO, GL_ONE, GL_ZERO );
		glBlendEquationSeparate( GL_FUNC_ADD, GL_FUNC_ADD );
		glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
		glBlendColor( 0.0f, 0.0f, 0.0f, 0.0f );

		/* rasterizer state */
		_init_rasterizer_state( &_sg.gl.cache.rast );
		glPolygonOffset( 0.0f, 0.0f );
		glDisable( GL_POLYGON_OFFSET_FILL );
		glDisable( GL_CULL_FACE );
		glFrontFace( GL_CW );
		glCullFace( GL_BACK );
		glEnable( GL_SCISSOR_TEST );
		glDisable( GL_SAMPLE_ALPHA_TO_COVERAGE );
		glEnable( GL_DITHER );
		glDisable( GL_POLYGON_OFFSET_FILL );
	}
}

void _activate_context( _context_t * ctx )
{
	XE_ASSERT( _sg.gl.valid );
	/* NOTE: ctx can be 0 to unset the current context */
	_sg.gl.cur_context = ctx;
	_reset_state_cache();
}

/*-- GL backend resource creation and destruction ----------------------------*/
ResourceState _create_context( _context_t * ctx )
{
	XE_ASSERT( ctx );
	XE_ASSERT( 0 == ctx->default_framebuffer );
	_GL_CHECK_ERROR();
	glGetIntegerv( GL_FRAMEBUFFER_BINDING, (GLint * )& ctx->default_framebuffer );
	_GL_CHECK_ERROR();

	XE_ASSERT( 0 == ctx->vao );
	glGenVertexArrays( 1, &ctx->vao );
	glBindVertexArray( ctx->vao );
	_GL_CHECK_ERROR();
	return RESOURCESTATE_VALID;
}

void _destroy_context( _context_t * ctx )
{
	XE_ASSERT( ctx );
	if( ctx->vao )
	{
		glDeleteVertexArrays( 1, &ctx->vao );
	}
	_GL_CHECK_ERROR();
}

ResourceState _create_buffer( _buffer_t * buf, const BufferDesc * desc )
{
	XE_ASSERT( buf && desc );
	_GL_CHECK_ERROR();
	buf->cmn.init( desc );
	buf->gl.ext_buffers = ( 0 != desc->gl_buffers[0] );
	GLenum gl_target = _buffer_target( buf->cmn.type );
	GLenum gl_usage = _usage( buf->cmn.usage );
	for( int slot = 0; slot < buf->cmn.num_slots; slot++ )
	{
		GLuint gl_buf = 0;
		if( buf->gl.ext_buffers )
		{
			XE_ASSERT( desc->gl_buffers[slot] );
			gl_buf = desc->gl_buffers[slot];
		}
		else
		{
			glGenBuffers( 1, &gl_buf );
			_store_buffer_binding( gl_target );
			_bind_buffer( gl_target, gl_buf );
			glBufferData( gl_target, buf->cmn.size, 0, gl_usage );
			if( buf->cmn.usage == USAGE_IMMUTABLE )
			{
				XE_ASSERT( desc->content );
				glBufferSubData( gl_target, 0, buf->cmn.size, desc->content );
			}
			_restore_buffer_binding( gl_target );
		}
		buf->gl.buf[slot] = gl_buf;
	}
	_GL_CHECK_ERROR();
	return RESOURCESTATE_VALID;
}

void _destroy_buffer( _buffer_t * buf )
{
	XE_ASSERT( buf );
	_GL_CHECK_ERROR();
	if( !buf->gl.ext_buffers )
	{
		for( int slot = 0; slot < buf->cmn.num_slots; slot++ )
		{
			if( buf->gl.buf[slot] )
			{
				glDeleteBuffers( 1, &buf->gl.buf[slot] );
			}
		}
		_GL_CHECK_ERROR();
	}
}

bool _supported_texture_format( PixelFormat fmt )
{
	const int fmt_index = (int )fmt;
	XE_ASSERT( ( fmt_index > PIXELFORMAT_NONE ) && ( fmt_index < _PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index].sample;
}

ResourceState _create_image( _image_t * img, const ImageDesc * desc )
{
	XE_ASSERT( img && desc );
	_GL_CHECK_ERROR();
	img->cmn.init( desc );
	img->gl.ext_textures = ( 0 != desc->gl_textures[0] );

	/* check if texture format is support */
	if( !_supported_texture_format( img->cmn.pixel_format ) )
	{
		puts( "texture format not supported by GL context\n" );
		return RESOURCESTATE_FAILED;
	}
	/* check for optional texture types */
	if( ( img->cmn.type == IMAGETYPE_3D ) && !_sg.features.imagetype_3d )
	{
		puts( "3D textures not supported by GL context\n" );
		return RESOURCESTATE_FAILED;
	}
	if( ( img->cmn.type == IMAGETYPE_ARRAY ) && !_sg.features.imagetype_array )
	{
		puts( "array textures not supported by GL context\n" );
		return RESOURCESTATE_FAILED;
	}

	bool msaa = ( img->cmn.sample_count > 1 ) && ( _sg.features.msaa_render_targets );

	if( _is_valid_rendertarget_depth_format( img->cmn.pixel_format ) )
	{
		/* special case depth-stencil-buffer? */
		XE_ASSERT( ( img->cmn.usage == USAGE_IMMUTABLE ) && ( img->cmn.num_slots == 1 ) );
		XE_ASSERT( !img->gl.ext_textures );   /* cannot provide external texture for depth images */
		glGenRenderbuffers( 1, &img->gl.depth_render_buffer );
		glBindRenderbuffer( GL_RENDERBUFFER, img->gl.depth_render_buffer );
		GLenum gl_depth_format = _depth_attachment_format( img->cmn.pixel_format );
		if( msaa )
		{
			glRenderbufferStorageMultisample( GL_RENDERBUFFER, img->cmn.sample_count, gl_depth_format, img->cmn.width, img->cmn.height );
		}
		else
		{
			glRenderbufferStorage( GL_RENDERBUFFER, gl_depth_format, img->cmn.width, img->cmn.height );
		}
	}
	else
	{
		/* regular color texture */
		img->gl.target = _texture_target( img->cmn.type );
		const GLenum gl_internal_format = _teximage_internal_format( img->cmn.pixel_format );

		/* if this is a MSAA render target, need to create a separate render buffer */
		if( img->cmn.render_target && msaa )
		{
			glGenRenderbuffers( 1, &img->gl.msaa_render_buffer );
			glBindRenderbuffer( GL_RENDERBUFFER, img->gl.msaa_render_buffer );
			glRenderbufferStorageMultisample( GL_RENDERBUFFER, img->cmn.sample_count, gl_internal_format, img->cmn.width, img->cmn.height );
		}

		if( img->gl.ext_textures )
		{
			/* inject externally GL textures */
			for( int slot = 0; slot < img->cmn.num_slots; slot++ )
			{
				XE_ASSERT( desc->gl_textures[slot] );
				img->gl.tex[slot] = desc->gl_textures[slot];
			}
		}
		else
		{
			/* create our own GL texture(s) */
			const GLenum gl_format = _teximage_format( img->cmn.pixel_format );
			const bool is_compressed = _is_compressed_pixel_format( img->cmn.pixel_format );
			for( int slot = 0; slot < img->cmn.num_slots; slot++ )
			{
				glGenTextures( 1, &img->gl.tex[slot] );
				_store_texture_binding( 0 );
				_bind_texture( 0, img->gl.target, img->gl.tex[slot] );
				GLenum gl_min_filter = _filter( img->cmn.min_filter );
				GLenum gl_mag_filter = _filter( img->cmn.mag_filter );
				glTexParameteri( img->gl.target, GL_TEXTURE_MIN_FILTER, gl_min_filter );
				glTexParameteri( img->gl.target, GL_TEXTURE_MAG_FILTER, gl_mag_filter );
				if( _sg.gl.ext_anisotropic && ( img->cmn.max_anisotropy > 1 ) )
				{
					GLint max_aniso = (GLint )img->cmn.max_anisotropy;
					if( max_aniso > _sg.gl.max_anisotropy )
					{
						max_aniso = _sg.gl.max_anisotropy;
					}
					glTexParameteri( img->gl.target, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso );
				}
				if( img->cmn.type == IMAGETYPE_CUBE )
				{
					glTexParameteri( img->gl.target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
					glTexParameteri( img->gl.target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
				}
				else
				{
					glTexParameteri( img->gl.target, GL_TEXTURE_WRAP_S, _wrap( img->cmn.wrap_u ) );
					glTexParameteri( img->gl.target, GL_TEXTURE_WRAP_T, _wrap( img->cmn.wrap_v ) );
					if( img->cmn.type == IMAGETYPE_3D )
					{
						glTexParameteri( img->gl.target, GL_TEXTURE_WRAP_R, _wrap( img->cmn.wrap_w ) );
					}
				}
				/* GL spec has strange defaults for mipmap min/max lod: -1000 to +1000 */
				glTexParameterf( img->gl.target, GL_TEXTURE_MIN_LOD, _clamp( desc->min_lod, 0.0f, 1000.0f ) );
				glTexParameterf( img->gl.target, GL_TEXTURE_MAX_LOD, _clamp( desc->max_lod, 0.0f, 1000.0f ) );
				const int num_faces = img->cmn.type == IMAGETYPE_CUBE ? 6 : 1;
				int data_index = 0;
				for( int face_index = 0; face_index < num_faces; face_index++ )
				{
					for( int mip_index = 0; mip_index < img->cmn.num_mipmaps; mip_index++, data_index++ )
					{
						GLenum gl_img_target = img->gl.target;
						if( IMAGETYPE_CUBE == img->cmn.type )
						{
							gl_img_target = _cubeface_target( face_index );
						}
						const GLvoid * data_ptr = desc->content.subimage[face_index][mip_index].ptr;
						const int data_size = desc->content.subimage[face_index][mip_index].size;
						int mip_width = img->cmn.width >> mip_index;
						if( mip_width == 0 )
						{
							mip_width = 1;
						}
						int mip_height = img->cmn.height >> mip_index;
						if( mip_height == 0 )
						{
							mip_height = 1;
						}
						if( ( IMAGETYPE_2D == img->cmn.type ) || ( IMAGETYPE_CUBE == img->cmn.type ) )
						{
							if( is_compressed )
							{
								glCompressedTexImage2D( gl_img_target, mip_index, gl_internal_format,
														mip_width, mip_height, 0, data_size, data_ptr );
							}
							else
							{
								const GLenum gl_type = _teximage_type( img->cmn.pixel_format );
								glTexImage2D( gl_img_target, mip_index, gl_internal_format,
											  mip_width, mip_height, 0, gl_format, gl_type, data_ptr );
							}
						}
						else if( ( IMAGETYPE_3D == img->cmn.type ) || ( IMAGETYPE_ARRAY == img->cmn.type ) )
						{
							int mip_depth = img->cmn.depth;
							if( IMAGETYPE_3D == img->cmn.type )
							{
								mip_depth >>= mip_index;
							}
							if( mip_depth == 0 )
							{
								mip_depth = 1;
							}
							if( is_compressed )
							{
								glCompressedTexImage3D( gl_img_target, mip_index, gl_internal_format,
														mip_width, mip_height, mip_depth, 0, data_size, data_ptr );
							}
							else
							{
								const GLenum gl_type = _teximage_type( img->cmn.pixel_format );
								glTexImage3D( gl_img_target, mip_index, gl_internal_format,
											  mip_width, mip_height, mip_depth, 0, gl_format, gl_type, data_ptr );
							}
						}
					}
				}
				_restore_texture_binding( 0 );
			}
		}
	}
	_GL_CHECK_ERROR();
	return RESOURCESTATE_VALID;
}

void _destroy_image( _image_t * img )
{
	XE_ASSERT( img );
	_GL_CHECK_ERROR();
	if( !img->gl.ext_textures )
	{
		for( int slot = 0; slot < img->cmn.num_slots; slot++ )
		{
			if( img->gl.tex[slot] )
			{
				glDeleteTextures( 1, &img->gl.tex[slot] );
			}
		}
	}
	if( img->gl.depth_render_buffer )
	{
		glDeleteRenderbuffers( 1, &img->gl.depth_render_buffer );
	}
	if( img->gl.msaa_render_buffer )
	{
		glDeleteRenderbuffers( 1, &img->gl.msaa_render_buffer );
	}
	_GL_CHECK_ERROR();
}

GLuint _compile_shader( ShaderStage stage, XE::String src )
{
	XE_ASSERT( src );
	_GL_CHECK_ERROR();
	GLuint gl_shd = glCreateShader( _shader_stage( stage ) );
	glShaderSource( gl_shd, 1, &src, 0 );
	glCompileShader( gl_shd );
	GLint compile_status = 0;
	glGetShaderiv( gl_shd, GL_COMPILE_STATUS, &compile_status );
	if( !compile_status )
	{
		/* compilation failed, log error and delete shader */
		GLint log_len = 0;
		glGetShaderiv( gl_shd, GL_INFO_LOG_LENGTH, &log_len );
		if( log_len > 0 )
		{
			GLchar * log_buf = (GLchar * )malloc( log_len );
			glGetShaderInfoLog( gl_shd, log_len, &log_len, log_buf );
			puts( log_buf );
			free( log_buf );
		}
		glDeleteShader( gl_shd );
		gl_shd = 0;
	}
	_GL_CHECK_ERROR();
	return gl_shd;
}

ResourceState _create_shader( _shader_t * shd, const ShaderDesc * desc )
{
	XE_ASSERT( shd && desc );
	XE_ASSERT( !shd->gl.prog );
	_GL_CHECK_ERROR();

	shd->cmn.init( desc );

	/* copy vertex attribute names over, these are required for GLES2, and optional for GLES3 and GL3.x */
	for( int i = 0; i < MAX_VERTEX_ATTRIBUTES; i++ )
	{
		shd->gl.attrs[i].name = desc->attrs[i].name;
	}

	GLuint gl_vs = _compile_shader( SHADERSTAGE_VS, desc->vs.source );
	GLuint gl_fs = _compile_shader( SHADERSTAGE_FS, desc->fs.source );
	if( !( gl_vs && gl_fs ) )
	{
		return RESOURCESTATE_FAILED;
	}
	GLuint gl_prog = glCreateProgram();
	glAttachShader( gl_prog, gl_vs );
	glAttachShader( gl_prog, gl_fs );
	glLinkProgram( gl_prog );
	glDeleteShader( gl_vs );
	glDeleteShader( gl_fs );
	_GL_CHECK_ERROR();

	GLint link_status;
	glGetProgramiv( gl_prog, GL_LINK_STATUS, &link_status );
	if( !link_status )
	{
		GLint log_len = 0;
		glGetProgramiv( gl_prog, GL_INFO_LOG_LENGTH, &log_len );
		if( log_len > 0 )
		{
			GLchar * log_buf = (GLchar * )malloc( log_len );
			glGetProgramInfoLog( gl_prog, log_len, &log_len, log_buf );
			puts( log_buf );
			free( log_buf );
		}
		glDeleteProgram( gl_prog );
		return RESOURCESTATE_FAILED;
	}
	shd->gl.prog = gl_prog;

	/* resolve uniforms */
	_GL_CHECK_ERROR();
	for( int stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
	{
		const ShaderStageDesc * stage_desc = ( stage_index == SHADERSTAGE_VS ) ? &desc->vs : &desc->fs;
		_gl_shader_stage_t * gl_stage = &shd->gl.stage[stage_index];
		for( int ub_index = 0; ub_index < shd->cmn.stage[stage_index].num_uniform_blocks; ub_index++ )
		{
			const ShaderUniformBlockDesc * ub_desc = &stage_desc->uniform_blocks[ub_index];
			XE_ASSERT( ub_desc->size > 0 );
			_gl_uniform_block_t * ub = &gl_stage->uniform_blocks[ub_index];
			XE_ASSERT( ub->num_uniforms == 0 );
			int cur_uniform_offset = 0;
			for( int u_index = 0; u_index < MAX_UB_MEMBERS; u_index++ )
			{
				const ShaderUniformDesc * u_desc = &ub_desc->uniforms[u_index];
				if( u_desc->type == UNIFORMTYPE_INVALID )
				{
					break;
				}
				_gl_uniform_t * u = &ub->uniforms[u_index];
				u->type = u_desc->type;
				u->count = (uint8_t )u_desc->array_count;
				u->offset = (uint16_t )cur_uniform_offset;
				cur_uniform_offset += _uniform_size( u->type, u->count );
				if( u_desc->name )
				{
					u->gl_loc = glGetUniformLocation( gl_prog, u_desc->name );
				}
				else
				{
					u->gl_loc = u_index;
				}
				ub->num_uniforms++;
			}
			XE_ASSERT( ub_desc->size == cur_uniform_offset );
		}
	}

	/* resolve image locations */
	_GL_CHECK_ERROR();
	int gl_tex_slot = 0;
	for( int stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
	{
		const ShaderStageDesc * stage_desc = ( stage_index == SHADERSTAGE_VS ) ? &desc->vs : &desc->fs;
		_gl_shader_stage_t * gl_stage = &shd->gl.stage[stage_index];
		for( int img_index = 0; img_index < shd->cmn.stage[stage_index].num_images; img_index++ )
		{
			const ShaderImageDesc * img_desc = &stage_desc->images[img_index];
			XE_ASSERT( img_desc->type != _IMAGETYPE_DEFAULT );
			_gl_shader_image_t * gl_img = &gl_stage->images[img_index];
			gl_img->gl_loc = img_index;
			if( img_desc->name )
			{
				gl_img->gl_loc = glGetUniformLocation( gl_prog, img_desc->name );
			}
			if( gl_img->gl_loc != -1 )
			{
				gl_img->gl_tex_slot = gl_tex_slot++;
			}
			else
			{
				gl_img->gl_tex_slot = -1;
			}
		}
	}
	_GL_CHECK_ERROR();
	return RESOURCESTATE_VALID;
}

void _destroy_shader( _shader_t * shd )
{
	XE_ASSERT( shd );
	_GL_CHECK_ERROR();
	if( shd->gl.prog )
	{
		glDeleteProgram( shd->gl.prog );
	}
	_GL_CHECK_ERROR();
}

ResourceState _create_pipeline( _pipeline_t * pip, _shader_t * shd, const PipelineDesc * desc )
{
	XE_ASSERT( pip && shd && desc );
	XE_ASSERT( !pip->shader && pip->cmn.shader_id.GetValue() == INVALID_ID );
	XE_ASSERT( desc->shader.GetValue() == shd->slot.id );
	XE_ASSERT( shd->gl.prog );
	pip->shader = shd;
	pip->cmn.init( desc );
	pip->gl.primitive_type = desc->primitive_type;
	pip->gl.depth_stencil = desc->depth_stencil;
	pip->gl.blend = desc->blend;
	pip->gl.rast = desc->rasterizer;

	/* resolve vertex attributes */
	for( int attr_index = 0; attr_index < MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		pip->gl.attrs[attr_index].vb_index = -1;
	}
	for( uint32_t attr_index = 0; attr_index < _sg.limits.max_vertex_attrs; attr_index++ )
	{
		const VertexAttrDesc * a_desc = &desc->layout.attrs[attr_index];
		if( a_desc->format == VERTEXFORMAT_INVALID )
		{
			break;
		}
		XE_ASSERT( ( a_desc->buffer_index >= 0 ) && ( a_desc->buffer_index < MAX_SHADERSTAGE_BUFFERS ) );
		const Buffer_layout_desc * l_desc = &desc->layout.buffers[a_desc->buffer_index];
		const VertexStep step_func = l_desc->step_func;
		const int step_rate = l_desc->step_rate;
		GLint attr_loc = attr_index;
		if( shd->gl.attrs[attr_index].name != "" )
		{
			attr_loc = glGetAttribLocation( pip->shader->gl.prog, shd->gl.attrs[attr_index].name.ToCString() );
		}
		XE_ASSERT( attr_loc < (GLint )_sg.limits.max_vertex_attrs );
		if( attr_loc != -1 )
		{
			_gl_attr_t * gl_attr = &pip->gl.attrs[attr_loc];
			XE_ASSERT( gl_attr->vb_index == -1 );
			gl_attr->vb_index = (int8_t )a_desc->buffer_index;
			if( step_func == VERTEXSTEP_PER_VERTEX )
			{
				gl_attr->divisor = 0;
			}
			else
			{
				gl_attr->divisor = (int8_t )step_rate;
			}
			XE_ASSERT( l_desc->stride > 0 );
			gl_attr->stride = (uint8_t )l_desc->stride;
			gl_attr->offset = a_desc->offset;
			gl_attr->size = (uint8_t )_vertexformat_size( a_desc->format );
			gl_attr->type = _vertexformat_type( a_desc->format );
			gl_attr->normalized = _vertexformat_normalized( a_desc->format );
			pip->cmn.vertex_layout_valid[a_desc->buffer_index] = true;
		}
		else
		{
			puts( "Vertex attribute not found in shader: " );
			puts( shd->gl.attrs[attr_index].name.ToCString() );
		}
	}
	return RESOURCESTATE_VALID;
}

void _destroy_pipeline( _pipeline_t * pip )
{
	XE_ASSERT( pip );
	/* empty */
}

/*
	_create_pass

	att_imgs must point to a _image* att_imgs[MAX_COLOR_ATTACHMENTS+1] array,
	first entries are the color attachment images (or nullptr), last entry
	is the depth-stencil image (or nullptr).
*/
ResourceState _create_pass( _pass_t * pass, _image_t ** att_images, const PassDesc * desc )
{
	XE_ASSERT( pass && att_images && desc );
	XE_ASSERT( att_images && att_images[0] );
	_GL_CHECK_ERROR();

	pass->cmn.init( desc );

	/* copy image pointers */
	const AttachmentDesc * att_desc;
	for( int i = 0; i < pass->cmn.num_color_atts; i++ )
	{
		att_desc = &desc->color_attachments[i];
		XE_ASSERT( att_desc->image.GetValue() != INVALID_ID );
		XE_ASSERT( 0 == pass->gl.color_atts[i].image );
		XE_ASSERT( att_images[i] && ( att_images[i]->slot.id == att_desc->image.GetValue() ) );
		XE_ASSERT( _is_valid_rendertarget_color_format( att_images[i]->cmn.pixel_format ) );
		pass->gl.color_atts[i].image = att_images[i];
	}
	XE_ASSERT( 0 == pass->gl.ds_att.image );
	att_desc = &desc->depth_stencil_attachment;
	if( att_desc->image.GetValue() != INVALID_ID )
	{
		const int ds_img_index = MAX_COLOR_ATTACHMENTS;
		XE_ASSERT( att_images[ds_img_index] && ( att_images[ds_img_index]->slot.id == att_desc->image.GetValue() ) );
		XE_ASSERT( _is_valid_rendertarget_depth_format( att_images[ds_img_index]->cmn.pixel_format ) );
		pass->gl.ds_att.image = att_images[ds_img_index];
	}

	/* store current framebuffer binding (restored at end of function) */
	GLuint gl_orig_fb;
	glGetIntegerv( GL_FRAMEBUFFER_BINDING, (GLint * )& gl_orig_fb );

	/* create a framebuffer object */
	glGenFramebuffers( 1, &pass->gl.fb );
	glBindFramebuffer( GL_FRAMEBUFFER, pass->gl.fb );

	/* attach msaa render buffer or textures */
	const bool is_msaa = ( 0 != att_images[0]->gl.msaa_render_buffer );
	if( is_msaa )
	{
		for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			const _image_t * att_img = pass->gl.color_atts[i].image;
			if( att_img )
			{
				const GLuint gl_render_buffer = att_img->gl.msaa_render_buffer;
				XE_ASSERT( gl_render_buffer );
				glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_RENDERBUFFER, gl_render_buffer );
			}
		}
	}
	else
	{
		for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			const _image_t * att_img = pass->gl.color_atts[i].image;
			const int mip_level = pass->cmn.color_atts[i].mip_level;
			const int slice = pass->cmn.color_atts[i].slice;
			if( att_img )
			{
				const GLuint gl_tex = att_img->gl.tex[0];
				XE_ASSERT( gl_tex );
				const GLenum gl_att = GL_COLOR_ATTACHMENT0 + i;
				switch( att_img->cmn.type )
				{
				case IMAGETYPE_2D:
					glFramebufferTexture2D( GL_FRAMEBUFFER, gl_att, GL_TEXTURE_2D, gl_tex, mip_level );
					break;
				case IMAGETYPE_CUBE:
					glFramebufferTexture2D( GL_FRAMEBUFFER, gl_att, _cubeface_target( slice ), gl_tex, mip_level );
					break;
				default:
					/* 3D- or array-texture */
					glFramebufferTextureLayer( GL_FRAMEBUFFER, gl_att, gl_tex, mip_level, slice );
					break;
				}
			}
		}
	}

	/* attach depth-stencil buffer to framebuffer */
	if( pass->gl.ds_att.image )
	{
		const GLuint gl_render_buffer = pass->gl.ds_att.image->gl.depth_render_buffer;
		XE_ASSERT( gl_render_buffer );
		glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gl_render_buffer );
		if( _is_depth_stencil_format( pass->gl.ds_att.image->cmn.pixel_format ) )
		{
			glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, gl_render_buffer );
		}
	}

	/* check if framebuffer is complete */
	if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
	{
		puts( "Framebuffer completeness check failed!\n" );
		return RESOURCESTATE_FAILED;
	}

	/* create MSAA resolve framebuffers if necessary */
	if( is_msaa )
	{
		for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			_gl_attachment_t * gl_att = &pass->gl.color_atts[i];
			_attachment_t * cmn_att = &pass->cmn.color_atts[i];
			if( gl_att->image )
			{
				XE_ASSERT( 0 == gl_att->gl_msaa_resolve_buffer );
				glGenFramebuffers( 1, &gl_att->gl_msaa_resolve_buffer );
				glBindFramebuffer( GL_FRAMEBUFFER, gl_att->gl_msaa_resolve_buffer );
				const GLuint gl_tex = gl_att->image->gl.tex[0];
				XE_ASSERT( gl_tex );
				switch( gl_att->image->cmn.type )
				{
				case IMAGETYPE_2D:
					glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
											GL_TEXTURE_2D, gl_tex, cmn_att->mip_level );
					break;
				case IMAGETYPE_CUBE:
					glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
											_cubeface_target( cmn_att->slice ), gl_tex, cmn_att->mip_level );
					break;
				default:
					glFramebufferTextureLayer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gl_tex, cmn_att->mip_level, cmn_att->slice );
					break;
				}
				/* check if framebuffer is complete */
				if( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
				{
					puts( "Framebuffer completeness check failed (msaa resolve buffer)!\n" );
					return RESOURCESTATE_FAILED;
				}
			}
		}
	}

	/* restore original framebuffer binding */
	glBindFramebuffer( GL_FRAMEBUFFER, gl_orig_fb );
	_GL_CHECK_ERROR();
	return RESOURCESTATE_VALID;
}

void _destroy_pass( _pass_t * pass )
{
	XE_ASSERT( pass );
	_GL_CHECK_ERROR();
	if( 0 != pass->gl.fb )
	{
		glDeleteFramebuffers( 1, &pass->gl.fb );
	}
	for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
	{
		if( pass->gl.color_atts[i].gl_msaa_resolve_buffer )
		{
			glDeleteFramebuffers( 1, &pass->gl.color_atts[i].gl_msaa_resolve_buffer );
		}
	}
	if( pass->gl.ds_att.gl_msaa_resolve_buffer )
	{
		glDeleteFramebuffers( 1, &pass->gl.ds_att.gl_msaa_resolve_buffer );
	}
	_GL_CHECK_ERROR();
}

_image_t * _pass_color_image( const _pass_t * pass, int index )
{
	XE_ASSERT( pass && ( index >= 0 ) && ( index < MAX_COLOR_ATTACHMENTS ) );
	/* NOTE: may return null */
	return pass->gl.color_atts[index].image;
}

_image_t * _pass_ds_image( const _pass_t * pass )
{
	/* NOTE: may return null */
	XE_ASSERT( pass );
	return pass->gl.ds_att.image;
}

void _begin_pass( _pass_t * pass, const PassAction * action, int w, int h )
{
	/* FIXME: what if a texture used as render target is still bound, should we
	   unbind all currently bound textures in begin pass? */
	XE_ASSERT( action );
	XE_ASSERT( !_sg.gl.in_pass );
	_GL_CHECK_ERROR();
	_sg.gl.in_pass = true;
	_sg.gl.cur_pass = pass; /* can be 0 */
	if( pass )
	{
		_sg.gl.cur_pass_id = pass->slot.id;
	}
	else
	{
		_sg.gl.cur_pass_id = INVALID_ID;
	}
	_sg.gl.cur_pass_width = w;
	_sg.gl.cur_pass_height = h;
	if( pass )
	{
		/* offscreen pass */
		XE_ASSERT( pass->gl.fb );
		glBindFramebuffer( GL_FRAMEBUFFER, pass->gl.fb );
		GLenum att[MAX_COLOR_ATTACHMENTS] = {
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2,
			GL_COLOR_ATTACHMENT3
		};
		int num_attrs = 0;
		for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			if( pass->gl.color_atts[num_attrs].image )
			{
				num_attrs++;
			}
			else
			{
				break;
			}
		}
		glDrawBuffers( num_attrs, att );
	}
	else
	{
		/* default pass */
		XE_ASSERT( _sg.gl.cur_context );
		glBindFramebuffer( GL_FRAMEBUFFER, _sg.gl.cur_context->default_framebuffer );
	}
	glViewport( 0, 0, w, h );
	glScissor( 0, 0, w, h );
	bool need_pip_cache_flush = false;
	if( _sg.gl.cache.blend.color_write_mask != COLORMASK_RGBA )
	{
		need_pip_cache_flush = true;
		_sg.gl.cache.blend.color_write_mask = COLORMASK_RGBA;
		glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE );
	}
	if( !_sg.gl.cache.ds.depth_write_enabled )
	{
		need_pip_cache_flush = true;
		_sg.gl.cache.ds.depth_write_enabled = true;
		glDepthMask( GL_TRUE );
	}
	if( _sg.gl.cache.ds.depth_compare_func != COMPAREFUNC_ALWAYS )
	{
		need_pip_cache_flush = true;
		_sg.gl.cache.ds.depth_compare_func = COMPAREFUNC_ALWAYS;
		glDepthFunc( GL_ALWAYS );
	}
	if( _sg.gl.cache.ds.stencil_write_mask != 0xFF )
	{
		need_pip_cache_flush = true;
		_sg.gl.cache.ds.stencil_write_mask = 0xFF;
		glStencilMask( 0xFF );
	}
	if( need_pip_cache_flush )
	{
		/* we messed with the state cache directly, need to clear cached
		   pipeline to force re-evaluation in next apply_pipeline() */
		_sg.gl.cache.cur_pipeline = 0;
		_sg.gl.cache.cur_pipeline_id = INVALID_ID;
	}
	bool use_mrt_clear = ( 0 != pass );
	if( !use_mrt_clear )
	{
		GLbitfield clear_mask = 0;
		if( action->colors[0].action == ACTION_CLEAR )
		{
			clear_mask |= GL_COLOR_BUFFER_BIT;
			const float * c = action->colors[0].val;
			glClearColor( c[0], c[1], c[2], c[3] );
		}
		if( action->depth.action == ACTION_CLEAR )
		{
			clear_mask |= GL_DEPTH_BUFFER_BIT;
			glClearDepthf( action->depth.val );
		}
		if( action->stencil.action == ACTION_CLEAR )
		{
			clear_mask |= GL_STENCIL_BUFFER_BIT;
			glClearStencil( action->stencil.val );
		}
		if( 0 != clear_mask )
		{
			glClear( clear_mask );
		}
	}
	else
	{
		XE_ASSERT( pass );
		for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			if( pass->gl.color_atts[i].image )
			{
				if( action->colors[i].action == ACTION_CLEAR )
				{
					glClearBufferfv( GL_COLOR, i, action->colors[i].val );
				}
			}
			else
			{
				break;
			}
		}
		if( pass->gl.ds_att.image )
		{
			if( ( action->depth.action == ACTION_CLEAR ) && ( action->stencil.action == ACTION_CLEAR ) )
			{
				glClearBufferfi( GL_DEPTH_STENCIL, 0, action->depth.val, action->stencil.val );
			}
			else if( action->depth.action == ACTION_CLEAR )
			{
				glClearBufferfv( GL_DEPTH, 0, &action->depth.val );
			}
			else if( action->stencil.action == ACTION_CLEAR )
			{
				GLuint val = action->stencil.val;
				glClearBufferuiv( GL_STENCIL, 0, &val );
			}
		}
	}
	_GL_CHECK_ERROR();
}

void _end_pass( void )
{
	XE_ASSERT( _sg.gl.in_pass );
	_GL_CHECK_ERROR();

	/* if this was an offscreen pass, and MSAA rendering was used, need
	   to resolve into the pass images */
	if( _sg.gl.cur_pass )
	{
		/* check if the pass object is still valid */
		const _pass_t * pass = _sg.gl.cur_pass;
		XE_ASSERT( pass->slot.id == _sg.gl.cur_pass_id.GetValue() );
		bool is_msaa = ( 0 != _sg.gl.cur_pass->gl.color_atts[0].gl_msaa_resolve_buffer );
		if( is_msaa )
		{
			XE_ASSERT( pass->gl.fb );
			glBindFramebuffer( GL_READ_FRAMEBUFFER, pass->gl.fb );
			XE_ASSERT( pass->gl.color_atts[0].image );
			const int w = pass->gl.color_atts[0].image->cmn.width;
			const int h = pass->gl.color_atts[0].image->cmn.height;
			for( int att_index = 0; att_index < MAX_COLOR_ATTACHMENTS; att_index++ )
			{
				const _gl_attachment_t * gl_att = &pass->gl.color_atts[att_index];
				if( gl_att->image )
				{
					XE_ASSERT( gl_att->gl_msaa_resolve_buffer );
					glBindFramebuffer( GL_DRAW_FRAMEBUFFER, gl_att->gl_msaa_resolve_buffer );
					glReadBuffer( GL_COLOR_ATTACHMENT0 + att_index );
					const GLenum gl_draw_bufs = GL_COLOR_ATTACHMENT0;
					glDrawBuffers( 1, &gl_draw_bufs );
					glBlitFramebuffer( 0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST );
				}
				else
				{
					break;
				}
			}
		}
	}
	_sg.gl.cur_pass = 0;
	_sg.gl.cur_pass_id = INVALID_ID;
	_sg.gl.cur_pass_width = 0;
	_sg.gl.cur_pass_height = 0;

	XE_ASSERT( _sg.gl.cur_context );
	glBindFramebuffer( GL_FRAMEBUFFER, _sg.gl.cur_context->default_framebuffer );
	_sg.gl.in_pass = false;
	_GL_CHECK_ERROR();
}

void _apply_viewport( int x, int y, int w, int h, bool origin_top_left )
{
	XE_ASSERT( _sg.gl.in_pass );
	y = origin_top_left ? ( _sg.gl.cur_pass_height - ( y + h ) ) : y;
	glViewport( x, y, w, h );
}

void _apply_scissor_rect( int x, int y, int w, int h, bool origin_top_left )
{
	XE_ASSERT( _sg.gl.in_pass );
	y = origin_top_left ? ( _sg.gl.cur_pass_height - ( y + h ) ) : y;
	glScissor( x, y, w, h );
}

void _apply_pipeline( _pipeline_t * pip )
{
	XE_ASSERT( pip );
	XE_ASSERT( pip->shader );
	_GL_CHECK_ERROR();
	if( ( _sg.gl.cache.cur_pipeline != pip ) || ( _sg.gl.cache.cur_pipeline_id.GetValue() != pip->slot.id ) )
	{
		_sg.gl.cache.cur_pipeline = pip;
		_sg.gl.cache.cur_pipeline_id = pip->slot.id;
		_sg.gl.cache.cur_primitive_type = _primitive_type( pip->gl.primitive_type );
		_sg.gl.cache.cur_index_type = _index_type( pip->cmn.index_type );

		/* update depth-stencil state */
		const DepthStencilState * new_ds = &pip->gl.depth_stencil;
		DepthStencilState * cache_ds = &_sg.gl.cache.ds;
		if( new_ds->depth_compare_func != cache_ds->depth_compare_func )
		{
			cache_ds->depth_compare_func = new_ds->depth_compare_func;
			glDepthFunc( _compare_func( new_ds->depth_compare_func ) );
		}
		if( new_ds->depth_write_enabled != cache_ds->depth_write_enabled )
		{
			cache_ds->depth_write_enabled = new_ds->depth_write_enabled;
			glDepthMask( new_ds->depth_write_enabled );
		}
		if( new_ds->stencil_enabled != cache_ds->stencil_enabled )
		{
			cache_ds->stencil_enabled = new_ds->stencil_enabled;
			if( new_ds->stencil_enabled ) glEnable( GL_STENCIL_TEST );
			else glDisable( GL_STENCIL_TEST );
		}
		if( new_ds->stencil_write_mask != cache_ds->stencil_write_mask )
		{
			cache_ds->stencil_write_mask = new_ds->stencil_write_mask;
			glStencilMask( new_ds->stencil_write_mask );
		}
		for( int i = 0; i < 2; i++ )
		{
			const StencilState * new_ss = ( i == 0 ) ? &new_ds->stencil_front : &new_ds->stencil_back;
			StencilState * cache_ss = ( i == 0 ) ? &cache_ds->stencil_front : &cache_ds->stencil_back;
			GLenum gl_face = ( i == 0 ) ? GL_FRONT : GL_BACK;
			if( ( new_ss->compare_func != cache_ss->compare_func ) ||
				( new_ds->stencil_read_mask != cache_ds->stencil_read_mask ) ||
				( new_ds->stencil_ref != cache_ds->stencil_ref ) )
			{
				cache_ss->compare_func = new_ss->compare_func;
				glStencilFuncSeparate( gl_face,
									   _compare_func( new_ss->compare_func ),
									   new_ds->stencil_ref,
									   new_ds->stencil_read_mask );
			}
			if( ( new_ss->fail_op != cache_ss->fail_op ) ||
				( new_ss->depth_fail_op != cache_ss->depth_fail_op ) ||
				( new_ss->pass_op != cache_ss->pass_op ) )
			{
				cache_ss->fail_op = new_ss->fail_op;
				cache_ss->depth_fail_op = new_ss->depth_fail_op;
				cache_ss->pass_op = new_ss->pass_op;
				glStencilOpSeparate( gl_face,
									 _stencil_op( new_ss->fail_op ),
									 _stencil_op( new_ss->depth_fail_op ),
									 _stencil_op( new_ss->pass_op ) );
			}
		}
		cache_ds->stencil_read_mask = new_ds->stencil_read_mask;
		cache_ds->stencil_ref = new_ds->stencil_ref;

		/* update blend state */
		const BlendState * new_b = &pip->gl.blend;
		BlendState * cache_b = &_sg.gl.cache.blend;
		if( new_b->enabled != cache_b->enabled )
		{
			cache_b->enabled = new_b->enabled;
			if( new_b->enabled ) glEnable( GL_BLEND );
			else glDisable( GL_BLEND );
		}
		if( ( new_b->src_factor_rgb != cache_b->src_factor_rgb ) ||
			( new_b->dst_factor_rgb != cache_b->dst_factor_rgb ) ||
			( new_b->src_factor_alpha != cache_b->src_factor_alpha ) ||
			( new_b->dst_factor_alpha != cache_b->dst_factor_alpha ) )
		{
			cache_b->src_factor_rgb = new_b->src_factor_rgb;
			cache_b->dst_factor_rgb = new_b->dst_factor_rgb;
			cache_b->src_factor_alpha = new_b->src_factor_alpha;
			cache_b->dst_factor_alpha = new_b->dst_factor_alpha;
			glBlendFuncSeparate( _blend_factor( new_b->src_factor_rgb ),
								 _blend_factor( new_b->dst_factor_rgb ),
								 _blend_factor( new_b->src_factor_alpha ),
								 _blend_factor( new_b->dst_factor_alpha ) );
		}
		if( ( new_b->op_rgb != cache_b->op_rgb ) || ( new_b->op_alpha != cache_b->op_alpha ) )
		{
			cache_b->op_rgb = new_b->op_rgb;
			cache_b->op_alpha = new_b->op_alpha;
			glBlendEquationSeparate( _blend_op( new_b->op_rgb ), _blend_op( new_b->op_alpha ) );
		}
		if( new_b->color_write_mask != cache_b->color_write_mask )
		{
			cache_b->color_write_mask = new_b->color_write_mask;
			glColorMask( ( new_b->color_write_mask & COLORMASK_R ) != 0,
				( new_b->color_write_mask & COLORMASK_G ) != 0,
						 ( new_b->color_write_mask & COLORMASK_B ) != 0,
						 ( new_b->color_write_mask & COLORMASK_A ) != 0 );
		}
		if( !_fequal( new_b->blend_color[0], cache_b->blend_color[0], 0.0001f ) ||
			!_fequal( new_b->blend_color[1], cache_b->blend_color[1], 0.0001f ) ||
			!_fequal( new_b->blend_color[2], cache_b->blend_color[2], 0.0001f ) ||
			!_fequal( new_b->blend_color[3], cache_b->blend_color[3], 0.0001f ) )
		{
			const float * bc = new_b->blend_color;
			for( int i = 0; i < 4; i++ )
			{
				cache_b->blend_color[i] = bc[i];
			}
			glBlendColor( bc[0], bc[1], bc[2], bc[3] );
		}

		/* update rasterizer state */
		const RasterizerState * new_r = &pip->gl.rast;
		RasterizerState * cache_r = &_sg.gl.cache.rast;
		if( new_r->cull_mode != cache_r->cull_mode )
		{
			cache_r->cull_mode = new_r->cull_mode;
			if( CULLMODE_NONE == new_r->cull_mode )
			{
				glDisable( GL_CULL_FACE );
			}
			else
			{
				glEnable( GL_CULL_FACE );
				GLenum gl_mode = ( CULLMODE_FRONT == new_r->cull_mode ) ? GL_FRONT : GL_BACK;
				glCullFace( gl_mode );
			}
		}
		if( new_r->face_winding != cache_r->face_winding )
		{
			cache_r->face_winding = new_r->face_winding;
			GLenum gl_winding = ( FACEWINDING_CW == new_r->face_winding ) ? GL_CW : GL_CCW;
			glFrontFace( gl_winding );
		}
		if( new_r->alpha_to_coverage_enabled != cache_r->alpha_to_coverage_enabled )
		{
			cache_r->alpha_to_coverage_enabled = new_r->alpha_to_coverage_enabled;
			if( new_r->alpha_to_coverage_enabled ) glEnable( GL_SAMPLE_ALPHA_TO_COVERAGE );
			else glDisable( GL_SAMPLE_ALPHA_TO_COVERAGE );
		}
		if( !_fequal( new_r->depth_bias, cache_r->depth_bias, 0.000001f ) ||
			!_fequal( new_r->depth_bias_slope_scale, cache_r->depth_bias_slope_scale, 0.000001f ) )
		{
			/* according to ANGLE's D3D11 backend:
				D3D11 SlopeScaledDepthBias ==> GL polygonOffsetFactor
				D3D11 DepthBias ==> GL polygonOffsetUnits
				DepthBiasClamp has no meaning on GL
			*/
			cache_r->depth_bias = new_r->depth_bias;
			cache_r->depth_bias_slope_scale = new_r->depth_bias_slope_scale;
			glPolygonOffset( new_r->depth_bias_slope_scale, new_r->depth_bias );
			bool po_enabled = true;
			if( _fequal( new_r->depth_bias, 0.0f, 0.000001f ) &&
				_fequal( new_r->depth_bias_slope_scale, 0.0f, 0.000001f ) )
			{
				po_enabled = false;
			}
			if( po_enabled != _sg.gl.cache.polygon_offset_enabled )
			{
				_sg.gl.cache.polygon_offset_enabled = po_enabled;
				if( po_enabled ) glEnable( GL_POLYGON_OFFSET_FILL );
				else glDisable( GL_POLYGON_OFFSET_FILL );
			}
		}

		/* bind shader program */
		glUseProgram( pip->shader->gl.prog );
	}
}

void _apply_bindings(
	_pipeline_t * pip,
	_buffer_t ** vbs, const int * vb_offsets, int num_vbs,
	_buffer_t * ib, int ib_offset,
	_image_t ** vs_imgs, int num_vs_imgs,
	_image_t ** fs_imgs, int num_fs_imgs )
{
	XE_ASSERT( pip );
	(void)( num_fs_imgs );
	(void)( num_vs_imgs );
	(void)( num_vbs );
	_GL_CHECK_ERROR();

	/* bind textures */
	_GL_CHECK_ERROR();
	for( int stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
	{
		const _shader_stage_t * stage = &pip->shader->cmn.stage[stage_index];
		const _gl_shader_stage_t * gl_stage = &pip->shader->gl.stage[stage_index];
		_image_t ** imgs = ( stage_index == SHADERSTAGE_VS ) ? vs_imgs : fs_imgs;
		XE_ASSERT( ( ( stage_index == SHADERSTAGE_VS ) ? num_vs_imgs : num_fs_imgs ) == stage->num_images );
		for( int img_index = 0; img_index < stage->num_images; img_index++ )
		{
			const _gl_shader_image_t * gl_shd_img = &gl_stage->images[img_index];
			if( gl_shd_img->gl_loc != -1 )
			{
				_image_t * img = imgs[img_index];
				const GLuint gl_tex = img->gl.tex[img->cmn.active_slot];
				XE_ASSERT( img && img->gl.target );
				XE_ASSERT( ( gl_shd_img->gl_tex_slot != -1 ) && gl_tex );
				glUniform1i( gl_shd_img->gl_loc, gl_shd_img->gl_tex_slot );
				_bind_texture( gl_shd_img->gl_tex_slot, img->gl.target, gl_tex );
			}
		}
	}
	_GL_CHECK_ERROR();

	/* index buffer (can be 0) */
	const GLuint gl_ib = ib ? ib->gl.buf[ib->cmn.active_slot] : 0;
	_bind_buffer( GL_ELEMENT_ARRAY_BUFFER, gl_ib );
	_sg.gl.cache.cur_ib_offset = ib_offset;

	/* vertex attributes */
	for( uint32_t attr_index = 0; attr_index < _sg.limits.max_vertex_attrs; attr_index++ )
	{
		_gl_attr_t * attr = &pip->gl.attrs[attr_index];
		_gl_cache_attr_t * cache_attr = &_sg.gl.cache.attrs[attr_index];
		bool cache_attr_dirty = false;
		int vb_offset = 0;
		GLuint gl_vb = 0;
		if( attr->vb_index >= 0 )
		{
			/* attribute is enabled */
			XE_ASSERT( attr->vb_index < num_vbs );
			_buffer_t * vb = vbs[attr->vb_index];
			XE_ASSERT( vb );
			gl_vb = vb->gl.buf[vb->cmn.active_slot];
			vb_offset = vb_offsets[attr->vb_index] + attr->offset;
			if( ( gl_vb != cache_attr->gl_vbuf ) ||
				( attr->size != cache_attr->gl_attr.size ) ||
				( attr->type != cache_attr->gl_attr.type ) ||
				( attr->normalized != cache_attr->gl_attr.normalized ) ||
				( attr->stride != cache_attr->gl_attr.stride ) ||
				( vb_offset != cache_attr->gl_attr.offset ) ||
				( cache_attr->gl_attr.divisor != attr->divisor ) )
			{
				_bind_buffer( GL_ARRAY_BUFFER, gl_vb );
				glVertexAttribPointer( attr_index, attr->size, attr->type,
									   attr->normalized, attr->stride,
									   (const GLvoid * )(GLintptr )vb_offset );
			#ifdef SOKOL_INSTANCING_ENABLED
				if( _sg.features.instancing )
				{
					glVertexAttribDivisor( attr_index, attr->divisor );
				}
			#endif
				cache_attr_dirty = true;
			}
			if( cache_attr->gl_attr.vb_index == -1 )
			{
				glEnableVertexAttribArray( attr_index );
				cache_attr_dirty = true;
			}
		}
		else
		{
			/* attribute is disabled */
			if( cache_attr->gl_attr.vb_index != -1 )
			{
				glDisableVertexAttribArray( attr_index );
				cache_attr_dirty = true;
			}
		}
		if( cache_attr_dirty )
		{
			cache_attr->gl_attr = *attr;
			cache_attr->gl_attr.offset = vb_offset;
			cache_attr->gl_vbuf = gl_vb;
		}
	}
	_GL_CHECK_ERROR();
}

void _apply_uniforms( ShaderStage stage_index, int ub_index, const void * data, int num_bytes )
{
	(void)( num_bytes );
	XE_ASSERT( data && ( num_bytes > 0 ) );
	XE_ASSERT( ( stage_index >= 0 ) && ( (int )stage_index < NUM_SHADER_STAGES ) );
	XE_ASSERT( _sg.gl.cache.cur_pipeline );
	XE_ASSERT( _sg.gl.cache.cur_pipeline->slot.id == _sg.gl.cache.cur_pipeline_id.GetValue() );
	XE_ASSERT( _sg.gl.cache.cur_pipeline->shader->slot.id == _sg.gl.cache.cur_pipeline->cmn.shader_id.GetValue() );
	XE_ASSERT( _sg.gl.cache.cur_pipeline->shader->cmn.stage[stage_index].num_uniform_blocks > ub_index );
	XE_ASSERT( _sg.gl.cache.cur_pipeline->shader->cmn.stage[stage_index].uniform_blocks[ub_index].size == num_bytes );
	const _gl_shader_stage_t * gl_stage = &_sg.gl.cache.cur_pipeline->shader->gl.stage[stage_index];
	const _gl_uniform_block_t * gl_ub = &gl_stage->uniform_blocks[ub_index];
	for( int u_index = 0; u_index < gl_ub->num_uniforms; u_index++ )
	{
		const _gl_uniform_t * u = &gl_ub->uniforms[u_index];
		XE_ASSERT( u->type != UNIFORMTYPE_INVALID );
		if( u->gl_loc == -1 )
		{
			continue;
		}
		GLfloat * ptr = (GLfloat * )( ( (uint8_t * )data ) + u->offset );
		switch( u->type )
		{
		case UNIFORMTYPE_INVALID:
			break;
		case UNIFORMTYPE_FLOAT:
			glUniform1fv( u->gl_loc, u->count, ptr );
			break;
		case UNIFORMTYPE_FLOAT2:
			glUniform2fv( u->gl_loc, u->count, ptr );
			break;
		case UNIFORMTYPE_FLOAT3:
			glUniform3fv( u->gl_loc, u->count, ptr );
			break;
		case UNIFORMTYPE_FLOAT4:
			glUniform4fv( u->gl_loc, u->count, ptr );
			break;
		case UNIFORMTYPE_MAT4:
			glUniformMatrix4fv( u->gl_loc, u->count, GL_FALSE, ptr );
			break;
		default:
			XE_ASSERT(false);
			break;
		}
	}
}

void _draw( int base_element, int num_elements, int num_instances )
{
	const GLenum i_type = _sg.gl.cache.cur_index_type;
	const GLenum p_type = _sg.gl.cache.cur_primitive_type;
	if( 0 != i_type )
	{
		/* indexed rendering */
		const int i_size = ( i_type == GL_UNSIGNED_SHORT ) ? 2 : 4;
		const int ib_offset = _sg.gl.cache.cur_ib_offset;
		const GLvoid * indices = (const GLvoid * )(GLintptr )( base_element * i_size + ib_offset );
		if( num_instances == 1 )
		{
			glDrawElements( p_type, num_elements, i_type, indices );
		}
		else
		{
			if( _sg.features.instancing )
			{
				glDrawElementsInstanced( p_type, num_elements, i_type, indices, num_instances );
			}
		}
	}
	else
	{
		/* non-indexed rendering */
		if( num_instances == 1 )
		{
			glDrawArrays( p_type, base_element, num_elements );
		}
		else
		{
			if( _sg.features.instancing )
			{
				glDrawArraysInstanced( p_type, base_element, num_elements, num_instances );
			}
		}
	}
}

void _commit( void )
{
	XE_ASSERT( !_sg.gl.in_pass );
	/* "soft" clear bindings (only those that are actually bound) */
	_clear_buffer_bindings( false );
	_clear_texture_bindings( false );
}

void _update_buffer( _buffer_t * buf, const void * data_ptr, int data_size )
{
	XE_ASSERT( buf && data_ptr && ( data_size > 0 ) );
	/* only one update per buffer per frame allowed */
	if( ++buf->cmn.active_slot >= buf->cmn.num_slots )
	{
		buf->cmn.active_slot = 0;
	}
	GLenum gl_tgt = _buffer_target( buf->cmn.type );
	XE_ASSERT( buf->cmn.active_slot < NUM_INFLIGHT_FRAMES );
	GLuint gl_buf = buf->gl.buf[buf->cmn.active_slot];
	XE_ASSERT( gl_buf );
	_GL_CHECK_ERROR();
	_store_buffer_binding( gl_tgt );
	_bind_buffer( gl_tgt, gl_buf );
	glBufferSubData( gl_tgt, 0, data_size, data_ptr );
	_restore_buffer_binding( gl_tgt );
	_GL_CHECK_ERROR();
}

void _append_buffer( _buffer_t * buf, const void * data_ptr, int data_size, bool new_frame )
{
	XE_ASSERT( buf && data_ptr && ( data_size > 0 ) );
	if( new_frame )
	{
		if( ++buf->cmn.active_slot >= buf->cmn.num_slots )
		{
			buf->cmn.active_slot = 0;
		}
	}
	GLenum gl_tgt = _buffer_target( buf->cmn.type );
	XE_ASSERT( buf->cmn.active_slot < NUM_INFLIGHT_FRAMES );
	GLuint gl_buf = buf->gl.buf[buf->cmn.active_slot];
	XE_ASSERT( gl_buf );
	_GL_CHECK_ERROR();
	_store_buffer_binding( gl_tgt );
	_bind_buffer( gl_tgt, gl_buf );
	glBufferSubData( gl_tgt, buf->cmn.append_pos, data_size, data_ptr );
	_restore_buffer_binding( gl_tgt );
	_GL_CHECK_ERROR();
}

void _update_image( _image_t * img, const ImageContent * data )
{
	XE_ASSERT( img && data );
	/* only one update per image per frame allowed */
	if( ++img->cmn.active_slot >= img->cmn.num_slots )
	{
		img->cmn.active_slot = 0;
	}
	XE_ASSERT( img->cmn.active_slot < NUM_INFLIGHT_FRAMES );
	XE_ASSERT( 0 != img->gl.tex[img->cmn.active_slot] );
	_store_texture_binding( 0 );
	_bind_texture( 0, img->gl.target, img->gl.tex[img->cmn.active_slot] );
	const GLenum gl_img_format = _teximage_format( img->cmn.pixel_format );
	const GLenum gl_img_type = _teximage_type( img->cmn.pixel_format );
	const int num_faces = img->cmn.type == IMAGETYPE_CUBE ? 6 : 1;
	const int num_mips = img->cmn.num_mipmaps;
	for( int face_index = 0; face_index < num_faces; face_index++ )
	{
		for( int mip_index = 0; mip_index < num_mips; mip_index++ )
		{
			GLenum gl_img_target = img->gl.target;
			if( IMAGETYPE_CUBE == img->cmn.type )
			{
				gl_img_target = _cubeface_target( face_index );
			}
			const GLvoid * data_ptr = data->subimage[face_index][mip_index].ptr;
			int mip_width = img->cmn.width >> mip_index;
			if( mip_width == 0 )
			{
				mip_width = 1;
			}
			int mip_height = img->cmn.height >> mip_index;
			if( mip_height == 0 )
			{
				mip_height = 1;
			}
			if( ( IMAGETYPE_2D == img->cmn.type ) || ( IMAGETYPE_CUBE == img->cmn.type ) )
			{
				glTexSubImage2D( gl_img_target, mip_index,
								 0, 0,
								 mip_width, mip_height,
								 gl_img_format, gl_img_type,
								 data_ptr );
			}
			else if( ( IMAGETYPE_3D == img->cmn.type ) || ( IMAGETYPE_ARRAY == img->cmn.type ) )
			{
				int mip_depth = img->cmn.depth >> mip_index;
				if( mip_depth == 0 )
				{
					mip_depth = 1;
				}
				glTexSubImage3D( gl_img_target, mip_index,
								 0, 0, 0,
								 mip_width, mip_height, mip_depth,
								 gl_img_format, gl_img_type,
								 data_ptr );

			}
		}
	}
	_restore_texture_binding( 0 );
}

#endif