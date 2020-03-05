#include "Gfx.h"

USING_XE

/* resource pool slots */
struct _slot_t
{
	uint32_t id;
	uint32_t ctx_id;
	ResourceState state;
};

struct _buffer_common_t
{
	void init( const BufferDesc * desc )
	{
		this->size = desc->size;
		this->append_pos = 0;
		this->append_overflow = false;
		this->type = desc->type;
		this->usage = desc->usage;
		this->update_frame_index = 0;
		this->append_frame_index = 0;
		this->num_slots = ( this->usage == Usage::USAGE_IMMUTABLE ) ? 1 : NUM_INFLIGHT_FRAMES;
		this->active_slot = 0;
	}

	int size;
	int append_pos;
	bool append_overflow;
	BufferType type;
	Usage usage;
	uint32_t update_frame_index;
	uint32_t append_frame_index;
	int num_slots;
	int active_slot;
};

struct _image_common_t
{
	void init( const ImageDesc * desc )
	{
		this->type = desc->type;
		this->render_target = desc->render_target;
		this->width = desc->width;
		this->height = desc->height;
		this->depth = desc->depth;
		this->num_mipmaps = desc->num_mipmaps;
		this->usage = desc->usage;
		this->pixel_format = desc->pixel_format;
		this->sample_count = desc->sample_count;
		this->min_filter = desc->min_filter;
		this->mag_filter = desc->mag_filter;
		this->wrap_u = desc->wrap_u;
		this->wrap_v = desc->wrap_v;
		this->wrap_w = desc->wrap_w;
		this->border_color = desc->border_color;
		this->max_anisotropy = desc->max_anisotropy;
		this->upd_frame_index = 0;
		this->num_slots = ( this->usage == Usage::USAGE_IMMUTABLE ) ? 1 : NUM_INFLIGHT_FRAMES;
		this->active_slot = 0;
	}

	ImageType type;
	bool render_target;
	int width;
	int height;
	int depth;
	int num_mipmaps;
	Usage usage;
	PixelFormat pixel_format;
	int sample_count;
	Filter min_filter;
	Filter mag_filter;
	Wrap wrap_u;
	Wrap wrap_v;
	Wrap wrap_w;
	BorderColor border_color;
	uint32_t max_anisotropy;
	uint32_t upd_frame_index;
	int num_slots;
	int active_slot;
};

struct _uniform_block_t
{
	int size;
};

struct _shader_image_t
{
	ImageType type;
};

struct _shader_stage_t
{
	int num_uniform_blocks;
	int num_images;
	_uniform_block_t uniform_blocks[MAX_SHADERSTAGE_UBS];
	_shader_image_t images[MAX_SHADERSTAGE_IMAGES];
};

struct _shader_common_t
{
	void init( const ShaderDesc * desc )
	{
		for( int stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
		{
			const ShaderStageDesc * stage_desc = ( stage_index == ShaderStage::SHADERSTAGE_VS ) ? &desc->vs : &desc->fs;
			_shader_stage_t * stage = &this->stage[stage_index];
			XE_ASSERT( stage->num_uniform_blocks == 0 );
			for( int ub_index = 0; ub_index < MAX_SHADERSTAGE_UBS; ub_index++ )
			{
				const ShaderUniformBlockDesc * ub_desc = &stage_desc->uniform_blocks[ub_index];
				if( 0 == ub_desc->size )
				{
					break;
				}
				stage->uniform_blocks[ub_index].size = ub_desc->size;
				stage->num_uniform_blocks++;
			}
			XE_ASSERT( stage->num_images == 0 );
			for( int img_index = 0; img_index < MAX_SHADERSTAGE_IMAGES; img_index++ )
			{
				const ShaderImageDesc * img_desc = &stage_desc->images[img_index];
				if( img_desc->type == ImageType::_IMAGETYPE_DEFAULT )
				{
					break;
				}
				stage->images[img_index].type = img_desc->type;
				stage->num_images++;
			}
		}
	}

	_shader_stage_t stage[NUM_SHADER_STAGES];
};

struct _pipeline_common_t
{
	void init( const PipelineDesc * desc )
	{
		this->shader_id = desc->shader;
		this->index_type = desc->index_type;
		for( int i = 0; i < MAX_SHADERSTAGE_BUFFERS; i++ )
		{
			this->vertex_layout_valid[i] = false;
		}
		this->color_attachment_count = desc->blend.color_attachment_count;
		this->color_format = desc->blend.color_format;
		this->depth_format = desc->blend.depth_format;
		this->sample_count = desc->rasterizer.sample_count;
		this->depth_bias = desc->rasterizer.depth_bias;
		this->depth_bias_slope_scale = desc->rasterizer.depth_bias_slope_scale;
		this->depth_bias_clamp = desc->rasterizer.depth_bias_clamp;
		for( int i = 0; i < 4; i++ )
		{
			this->blend_color[i] = desc->blend.blend_color[i];
		}
	}

	ShaderHandle shader_id;
	IndexType index_type;
	bool vertex_layout_valid[MAX_SHADERSTAGE_BUFFERS];
	int color_attachment_count;
	PixelFormat color_format;
	PixelFormat depth_format;
	int sample_count;
	float depth_bias;
	float depth_bias_slope_scale;
	float depth_bias_clamp;
	float blend_color[4];
};

struct _attachment_common_t
{
	ImageHandle image_id;
	int mip_level;
	int slice;
};

struct _pass_common_t
{
	void init( const PassDesc * desc )
	{
		const AttachmentDesc * att_desc;
		_attachment_common_t * att;
		for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			att_desc = &desc->color_attachments[i];
			if( att_desc->image )
			{
				this->num_color_atts++;
				att = &this->color_atts[i];
				att->image_id = att_desc->image;
				att->mip_level = att_desc->mip_level;
				att->slice = att_desc->slice;
			}
		}
		att_desc = &desc->depth_stencil_attachment;
		if( att_desc->image )
		{
			att = &this->ds_att;
			att->image_id = att_desc->image;
			att->mip_level = att_desc->mip_level;
			att->slice = att_desc->slice;
		}
	}

	int num_color_atts;
	_attachment_common_t color_atts[MAX_COLOR_ATTACHMENTS];
	_attachment_common_t ds_att;
};

struct _pool_t
{
	int size;
	int queue_top;
	uint32_t * gen_ctrs;
	int * free_queue;
};

enum _validate_error_t
{
	/* special case 'validation was successful' */
	_VALIDATE_SUCCESS,

	/* buffer creation */
	_VALIDATE_BUFFERDESC_CANARY,
	_VALIDATE_BUFFERDESC_SIZE,
	_VALIDATE_BUFFERDESC_CONTENT,
	_VALIDATE_BUFFERDESC_NO_CONTENT,

	/* image creation */
	_VALIDATE_IMAGEDESC_CANARY,
	_VALIDATE_IMAGEDESC_WIDTH,
	_VALIDATE_IMAGEDESC_HEIGHT,
	_VALIDATE_IMAGEDESC_RT_PIXELFORMAT,
	_VALIDATE_IMAGEDESC_NONRT_PIXELFORMAT,
	_VALIDATE_IMAGEDESC_MSAA_BUT_NO_RT,
	_VALIDATE_IMAGEDESC_NO_MSAA_RT_SUPPORT,
	_VALIDATE_IMAGEDESC_RT_IMMUTABLE,
	_VALIDATE_IMAGEDESC_RT_NO_CONTENT,
	_VALIDATE_IMAGEDESC_CONTENT,
	_VALIDATE_IMAGEDESC_NO_CONTENT,

	/* shader creation */
	_VALIDATE_SHADERDESC_CANARY,
	_VALIDATE_SHADERDESC_SOURCE,
	_VALIDATE_SHADERDESC_BYTECODE,
	_VALIDATE_SHADERDESC_SOURCE_OR_BYTECODE,
	_VALIDATE_SHADERDESC_NO_BYTECODE_SIZE,
	_VALIDATE_SHADERDESC_NO_CONT_UBS,
	_VALIDATE_SHADERDESC_NO_CONT_IMGS,
	_VALIDATE_SHADERDESC_NO_CONT_UB_MEMBERS,
	_VALIDATE_SHADERDESC_NO_UB_MEMBERS,
	_VALIDATE_SHADERDESC_UB_MEMBER_NAME,
	_VALIDATE_SHADERDESC_UB_SIZE_MISMATCH,
	_VALIDATE_SHADERDESC_IMG_NAME,
	_VALIDATE_SHADERDESC_ATTR_NAMES,
	_VALIDATE_SHADERDESC_ATTR_SEMANTICS,
	_VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG,

	/* pipeline creation */
	_VALIDATE_PIPELINEDESC_CANARY,
	_VALIDATE_PIPELINEDESC_SHADER,
	_VALIDATE_PIPELINEDESC_NO_ATTRS,
	_VALIDATE_PIPELINEDESC_LAYOUT_STRIDE4,
	_VALIDATE_PIPELINEDESC_ATTR_NAME,
	_VALIDATE_PIPELINEDESC_ATTR_SEMANTICS,

	/* pass creation */
	_VALIDATE_PASSDESC_CANARY,
	_VALIDATE_PASSDESC_NO_COLOR_ATTS,
	_VALIDATE_PASSDESC_NO_CONT_COLOR_ATTS,
	_VALIDATE_PASSDESC_IMAGE,
	_VALIDATE_PASSDESC_MIPLEVEL,
	_VALIDATE_PASSDESC_FACE,
	_VALIDATE_PASSDESC_LAYER,
	_VALIDATE_PASSDESC_SLICE,
	_VALIDATE_PASSDESC_IMAGE_NO_RT,
	_VALIDATE_PASSDESC_COLOR_PIXELFORMATS,
	_VALIDATE_PASSDESC_COLOR_INV_PIXELFORMAT,
	_VALIDATE_PASSDESC_DEPTH_INV_PIXELFORMAT,
	_VALIDATE_PASSDESC_IMAGE_SIZES,
	_VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS,

	/* begin_pass validation */
	_VALIDATE_BEGINPASS_PASS,
	_VALIDATE_BEGINPASS_IMAGE,

	/* apply_pipeline validation */
	_VALIDATE_APIP_PIPELINE_VALID_ID,
	_VALIDATE_APIP_PIPELINE_EXISTS,
	_VALIDATE_APIP_PIPELINE_VALID,
	_VALIDATE_APIP_SHADER_EXISTS,
	_VALIDATE_APIP_SHADER_VALID,
	_VALIDATE_APIP_ATT_COUNT,
	_VALIDATE_APIP_COLOR_FORMAT,
	_VALIDATE_APIP_DEPTH_FORMAT,
	_VALIDATE_APIP_SAMPLE_COUNT,

	/* apply_bindings validation */
	_VALIDATE_ABND_PIPELINE,
	_VALIDATE_ABND_PIPELINE_EXISTS,
	_VALIDATE_ABND_PIPELINE_VALID,
	_VALIDATE_ABND_VBS,
	_VALIDATE_ABND_VB_EXISTS,
	_VALIDATE_ABND_VB_TYPE,
	_VALIDATE_ABND_VB_OVERFLOW,
	_VALIDATE_ABND_NO_IB,
	_VALIDATE_ABND_IB,
	_VALIDATE_ABND_IB_EXISTS,
	_VALIDATE_ABND_IB_TYPE,
	_VALIDATE_ABND_IB_OVERFLOW,
	_VALIDATE_ABND_VS_IMGS,
	_VALIDATE_ABND_VS_IMG_EXISTS,
	_VALIDATE_ABND_VS_IMG_TYPES,
	_VALIDATE_ABND_FS_IMGS,
	_VALIDATE_ABND_FS_IMG_EXISTS,
	_VALIDATE_ABND_FS_IMG_TYPES,

	/* apply_uniforms validation */
	_VALIDATE_AUB_NO_PIPELINE,
	_VALIDATE_AUB_NO_UB_AT_SLOT,
	_VALIDATE_AUB_SIZE,

	/* update_buffer validation */
	_VALIDATE_UPDATEBUF_USAGE,
	_VALIDATE_UPDATEBUF_SIZE,
	_VALIDATE_UPDATEBUF_ONCE,
	_VALIDATE_UPDATEBUF_APPEND,

	/* append_buffer validation */
	_VALIDATE_APPENDBUF_USAGE,
	_VALIDATE_APPENDBUF_SIZE,
	_VALIDATE_APPENDBUF_UPDATE,

	/* update_image validation */
	_VALIDATE_UPDIMG_USAGE,
	_VALIDATE_UPDIMG_NOTENOUGHDATA,
	_VALIDATE_UPDIMG_SIZE,
	_VALIDATE_UPDIMG_COMPRESSED,
	_VALIDATE_UPDIMG_ONCE
};

/* constants */
enum
{
	_STRING_SIZE = 16,
	_SLOT_SHIFT = 16,
	_SLOT_MASK = ( 1 << _SLOT_SHIFT ) - 1,
	_MAX_POOL_SIZE = ( 1 << _SLOT_SHIFT ),
	_DEFAULT_BUFFER_POOL_SIZE = 128,
	_DEFAULT_IMAGE_POOL_SIZE = 128,
	_DEFAULT_SHADER_POOL_SIZE = 32,
	_DEFAULT_PIPELINE_POOL_SIZE = 64,
	_DEFAULT_PASS_POOL_SIZE = 16,
	_DEFAULT_CONTEXT_POOL_SIZE = 16,
	_MTL_DEFAULT_UB_SIZE = 4 * 1024 * 1024,
	_MTL_DEFAULT_SAMPLER_CACHE_CAPACITY = 64,
};

/* helper macros */
#define _def(val, def) (((val) == 0) ? (def) : (val))
#define _def_flt(val, def) (((val) == 0.0f) ? (def) : (val))
#define _min(a,b) ((a<b)?a:b)
#define _max(a,b) ((a>b)?a:b)
#define _clamp(v,v0,v1) ((v<v0)?(v0):((v>v1)?(v1):(v)))
#define _fequal(val,cmp,delta) (((val-cmp)> -delta)&&((val-cmp)<delta))


/* return byte size of a vertex format */
int _vertexformat_bytesize( VertexFormat fmt )
{
	switch( fmt )
	{
	case VERTEXFORMAT_FLOAT:     return 4;
	case VERTEXFORMAT_FLOAT2:    return 8;
	case VERTEXFORMAT_FLOAT3:    return 12;
	case VERTEXFORMAT_FLOAT4:    return 16;
	case VERTEXFORMAT_BYTE4:     return 4;
	case VERTEXFORMAT_BYTE4N:    return 4;
	case VERTEXFORMAT_UBYTE4:    return 4;
	case VERTEXFORMAT_UBYTE4N:   return 4;
	case VERTEXFORMAT_SHORT2:    return 4;
	case VERTEXFORMAT_SHORT2N:   return 4;
	case VERTEXFORMAT_USHORT2N:  return 4;
	case VERTEXFORMAT_SHORT4:    return 8;
	case VERTEXFORMAT_SHORT4N:   return 8;
	case VERTEXFORMAT_USHORT4N:  return 8;
	case VERTEXFORMAT_UINT10_N2: return 4;
	case VERTEXFORMAT_INVALID:   return 0;
	default:
		XE_ASSERT( false );
		return -1;
	}
}

/* return the byte size of a shader uniform */
int _uniform_size( UniformType type, int count )
{
	switch( type )
	{
	case UNIFORMTYPE_INVALID:    return 0;
	case UNIFORMTYPE_FLOAT:      return 4 * count;
	case UNIFORMTYPE_FLOAT2:     return 8 * count;
	case UNIFORMTYPE_FLOAT3:     return 12 * count; /* FIXME: std140??? */
	case UNIFORMTYPE_FLOAT4:     return 16 * count;
	case UNIFORMTYPE_MAT4:       return 64 * count;
	default:
		XE_ASSERT( false );
		return -1;
	}
}

PixelFormat _default_rendertarget_depthformat( void )
{
	return PIXELFORMAT_DEPTH_STENCIL;
}

/* return true if pixel format is a compressed format */
bool _is_compressed_pixel_format( PixelFormat fmt )
{
	switch( fmt )
	{
	case PIXELFORMAT_BC1_RGBA:
	case PIXELFORMAT_BC2_RGBA:
	case PIXELFORMAT_BC3_RGBA:
	case PIXELFORMAT_BC4_R:
	case PIXELFORMAT_BC4_RSN:
	case PIXELFORMAT_BC5_RG:
	case PIXELFORMAT_BC5_RGSN:
	case PIXELFORMAT_BC6H_RGBF:
	case PIXELFORMAT_BC6H_RGBUF:
	case PIXELFORMAT_BC7_RGBA:
	case PIXELFORMAT_PVRTC_RGB_2BPP:
	case PIXELFORMAT_PVRTC_RGB_4BPP:
	case PIXELFORMAT_PVRTC_RGBA_2BPP:
	case PIXELFORMAT_PVRTC_RGBA_4BPP:
	case PIXELFORMAT_ETC2_RGB8:
	case PIXELFORMAT_ETC2_RGB8A1:
	case PIXELFORMAT_ETC2_RGBA8:
	case PIXELFORMAT_ETC2_RG11:
	case PIXELFORMAT_ETC2_RG11SN:
		return true;
	default:
		return false;
	}
}

/* return true if pixel format is a depth-stencil format */
bool _is_depth_stencil_format( PixelFormat fmt )
{
	return ( PIXELFORMAT_DEPTH_STENCIL == fmt );
}

/* return the bytes-per-pixel for a pixel format */
int _pixelformat_bytesize( PixelFormat fmt )
{
	switch( fmt )
	{
	case PIXELFORMAT_R8:
	case PIXELFORMAT_R8SN:
	case PIXELFORMAT_R8UI:
	case PIXELFORMAT_R8SI:
		return 1;

	case PIXELFORMAT_R16:
	case PIXELFORMAT_R16SN:
	case PIXELFORMAT_R16UI:
	case PIXELFORMAT_R16SI:
	case PIXELFORMAT_R16F:
	case PIXELFORMAT_RG8:
	case PIXELFORMAT_RG8SN:
	case PIXELFORMAT_RG8UI:
	case PIXELFORMAT_RG8SI:
		return 2;

	case PIXELFORMAT_R32UI:
	case PIXELFORMAT_R32SI:
	case PIXELFORMAT_R32F:
	case PIXELFORMAT_RG16:
	case PIXELFORMAT_RG16SN:
	case PIXELFORMAT_RG16UI:
	case PIXELFORMAT_RG16SI:
	case PIXELFORMAT_RG16F:
	case PIXELFORMAT_RGBA8:
	case PIXELFORMAT_RGBA8SN:
	case PIXELFORMAT_RGBA8UI:
	case PIXELFORMAT_RGBA8SI:
	case PIXELFORMAT_BGRA8:
	case PIXELFORMAT_RGB10A2:
	case PIXELFORMAT_RG11B10F:
		return 4;

	case PIXELFORMAT_RG32UI:
	case PIXELFORMAT_RG32SI:
	case PIXELFORMAT_RG32F:
	case PIXELFORMAT_RGBA16:
	case PIXELFORMAT_RGBA16SN:
	case PIXELFORMAT_RGBA16UI:
	case PIXELFORMAT_RGBA16SI:
	case PIXELFORMAT_RGBA16F:
		return 8;

	case PIXELFORMAT_RGBA32UI:
	case PIXELFORMAT_RGBA32SI:
	case PIXELFORMAT_RGBA32F:
		return 16;

	default:
		XE_ASSERT( false );
		return 0;
	}
}

/* return row pitch for an image
	see ComputePitch in https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexUtil.cpp
*/
int _row_pitch( PixelFormat fmt, int width )
{
	int pitch;
	switch( fmt )
	{
	case PIXELFORMAT_BC1_RGBA:
	case PIXELFORMAT_BC4_R:
	case PIXELFORMAT_BC4_RSN:
	case PIXELFORMAT_ETC2_RGB8:
	case PIXELFORMAT_ETC2_RGB8A1:
		pitch = ( ( width + 3 ) / 4 ) * 8;
		pitch = pitch < 8 ? 8 : pitch;
		break;
	case PIXELFORMAT_BC2_RGBA:
	case PIXELFORMAT_BC3_RGBA:
	case PIXELFORMAT_BC5_RG:
	case PIXELFORMAT_BC5_RGSN:
	case PIXELFORMAT_BC6H_RGBF:
	case PIXELFORMAT_BC6H_RGBUF:
	case PIXELFORMAT_BC7_RGBA:
	case PIXELFORMAT_ETC2_RGBA8:
	case PIXELFORMAT_ETC2_RG11:
	case PIXELFORMAT_ETC2_RG11SN:
		pitch = ( ( width + 3 ) / 4 ) * 16;
		pitch = pitch < 16 ? 16 : pitch;
		break;
	case PIXELFORMAT_PVRTC_RGB_4BPP:
	case PIXELFORMAT_PVRTC_RGBA_4BPP:
	{
		const int block_size = 4 * 4;
		const int bpp = 4;
		int width_blocks = width / 4;
		width_blocks = width_blocks < 2 ? 2 : width_blocks;
		pitch = width_blocks * ( ( block_size * bpp ) / 8 );
	}
	break;
	case PIXELFORMAT_PVRTC_RGB_2BPP:
	case PIXELFORMAT_PVRTC_RGBA_2BPP:
	{
		const int block_size = 8 * 4;
		const int bpp = 2;
		int width_blocks = width / 4;
		width_blocks = width_blocks < 2 ? 2 : width_blocks;
		pitch = width_blocks * ( ( block_size * bpp ) / 8 );
	}
	break;
	default:
		pitch = width * _pixelformat_bytesize( fmt );
		break;
	}
	return pitch;
}

/* return pitch of a 2D subimage / texture slice
	see ComputePitch in https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexUtil.cpp
*/
int _surface_pitch( PixelFormat fmt, int width, int height )
{
	int num_rows = 0;
	switch( fmt )
	{
	case PIXELFORMAT_BC1_RGBA:
	case PIXELFORMAT_BC4_R:
	case PIXELFORMAT_BC4_RSN:
	case PIXELFORMAT_ETC2_RGB8:
	case PIXELFORMAT_ETC2_RGB8A1:
	case PIXELFORMAT_ETC2_RGBA8:
	case PIXELFORMAT_ETC2_RG11:
	case PIXELFORMAT_ETC2_RG11SN:
	case PIXELFORMAT_BC2_RGBA:
	case PIXELFORMAT_BC3_RGBA:
	case PIXELFORMAT_BC5_RG:
	case PIXELFORMAT_BC5_RGSN:
	case PIXELFORMAT_BC6H_RGBF:
	case PIXELFORMAT_BC6H_RGBUF:
	case PIXELFORMAT_BC7_RGBA:
	case PIXELFORMAT_PVRTC_RGB_4BPP:
	case PIXELFORMAT_PVRTC_RGBA_4BPP:
	case PIXELFORMAT_PVRTC_RGB_2BPP:
	case PIXELFORMAT_PVRTC_RGBA_2BPP:
		num_rows = ( ( height + 3 ) / 4 );
		break;
	default:
		num_rows = height;
		break;
	}
	if( num_rows < 1 )
	{
		num_rows = 1;
	}
	return num_rows * _row_pitch( fmt, width );
}

/* capability table pixel format helper functions */
void _pixelformat_all( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
	pfi->blend = true;
	pfi->render = true;
	pfi->msaa = true;
}

void _pixelformat_s( PixelformatInfo * pfi )
{
	pfi->sample = true;
}

void _pixelformat_sf( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
}

void _pixelformat_sr( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->render = true;
}

void _pixelformat_srmd( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->render = true;
	pfi->msaa = true;
	pfi->depth = true;
}

void _pixelformat_srm( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->render = true;
	pfi->msaa = true;
}

void _pixelformat_sfrm( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
	pfi->render = true;
	pfi->msaa = true;
}
void _pixelformat_sbrm( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->blend = true;
	pfi->render = true;
	pfi->msaa = true;
}

void _pixelformat_sbr( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->blend = true;
	pfi->render = true;
}

void _pixelformat_sfbr( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
	pfi->blend = true;
	pfi->render = true;
}

/* resolve pass action defaults into a new pass action struct */
void _resolve_default_pass_action( const PassAction * from, PassAction * to )
{
	XE_ASSERT( from && to );
	*to = *from;
	for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
	{
		if( to->colors[i].action == _ACTION_DEFAULT )
		{
			to->colors[i].action = ACTION_CLEAR;
			to->colors[i].val[0] = DEFAULT_CLEAR_RED;
			to->colors[i].val[1] = DEFAULT_CLEAR_GREEN;
			to->colors[i].val[2] = DEFAULT_CLEAR_BLUE;
			to->colors[i].val[3] = DEFAULT_CLEAR_ALPHA;
		}
	}
	if( to->depth.action == _ACTION_DEFAULT )
	{
		to->depth.action = ACTION_CLEAR;
		to->depth.val = DEFAULT_CLEAR_DEPTH;
	}
	if( to->stencil.action == _ACTION_DEFAULT )
	{
		to->stencil.action = ACTION_CLEAR;
		to->stencil.val = DEFAULT_CLEAR_STENCIL;
	}
}

#include "Gfx_GLES.h"
#include "Gfx_D3D11.h"
#include "Gfx_D3D12.h"
#include "Gfx_Metal.h"
#include "Gfx_Vulkan.h"

void _init_pool( _pool_t * pool, int num )
{
	XE_ASSERT( pool && ( num >= 1 ) );
	/* slot 0 is reserved for the 'invalid id', so bump the pool size by 1 */
	pool->size = num + 1;
	pool->queue_top = 0;
	/* generation counters indexable by pool slot index, slot 0 is reserved */
	size_t gen_ctrs_size = sizeof( uint32_t ) * pool->size;
	pool->gen_ctrs = (uint32_t * )malloc( gen_ctrs_size );
	XE_ASSERT( pool->gen_ctrs );
	memset( pool->gen_ctrs, 0, gen_ctrs_size );
	/* it's not a bug to only reserve 'num' here */
	pool->free_queue = (int * )malloc( sizeof( int ) * num );
	XE_ASSERT( pool->free_queue );
	/* never allocate the zero-th pool item since the invalid id is 0 */
	for( int i = pool->size - 1; i >= 1; i-- )
	{
		pool->free_queue[pool->queue_top++] = i;
	}
}

void _discard_pool( _pool_t * pool )
{
	XE_ASSERT( pool );
	XE_ASSERT( pool->free_queue );
	free( pool->free_queue );
	pool->free_queue = 0;
	XE_ASSERT( pool->gen_ctrs );
	free( pool->gen_ctrs );
	pool->gen_ctrs = 0;
	pool->size = 0;
	pool->queue_top = 0;
}

int _pool_alloc_index( _pool_t * pool )
{
	XE_ASSERT( pool );
	XE_ASSERT( pool->free_queue );
	if( pool->queue_top > 0 )
	{
		int slot_index = pool->free_queue[--pool->queue_top];
		XE_ASSERT( ( slot_index > 0 ) && ( slot_index < pool->size ) );
		return slot_index;
	}
	else
	{
		/* pool exhausted */
		return INVALID_SLOT_INDEX;
	}
}

void _pool_free_index( _pool_t * pool, int slot_index )
{
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < pool->size ) );
	XE_ASSERT( pool );
	XE_ASSERT( pool->free_queue );
	XE_ASSERT( pool->queue_top < pool->size );
#ifdef SOKOL_DEBUG
	/* debug check against double-free */
	for( int i = 0; i < pool->queue_top; i++ )
	{
		XE_ASSERT( pool->free_queue[i] != slot_index );
	}
#endif
	pool->free_queue[pool->queue_top++] = slot_index;
	XE_ASSERT( pool->queue_top <= ( pool->size - 1 ) );
}

void _reset_buffer( _buffer_t * buf )
{
	XE_ASSERT( buf );
	memset( buf, 0, sizeof( _buffer_t ) );
}

void _reset_image( _image_t * img )
{
	XE_ASSERT( img );
	memset( img, 0, sizeof( _image_t ) );
}

void _reset_shader( _shader_t * shd )
{
	XE_ASSERT( shd );
	memset( shd, 0, sizeof( _shader_t ) );
}

void _reset_pipeline( _pipeline_t * pip )
{
	XE_ASSERT( pip );
	memset( pip, 0, sizeof( _pipeline_t ) );
}

void _reset_pass( _pass_t * pass )
{
	XE_ASSERT( pass );
	memset( pass, 0, sizeof( _pass_t ) );
}

void _reset_context( _context_t * ctx )
{
	XE_ASSERT( ctx );
	memset( ctx, 0, sizeof( _context_t ) );
}

void _setup_pools( _pools_t * p, const GfxDesc * desc )
{
	XE_ASSERT( p );
	XE_ASSERT( desc );
	/* note: the pools here will have an additional item, since slot 0 is reserved */
	XE_ASSERT( ( desc->buffer_pool_size > 0 ) && ( desc->buffer_pool_size < _MAX_POOL_SIZE ) );
	_init_pool( &p->buffer_pool, desc->buffer_pool_size );
	size_t buffer_pool_byte_size = sizeof( _buffer_t ) * p->buffer_pool.size;
	p->buffers = (_buffer_t * )malloc( buffer_pool_byte_size );
	XE_ASSERT( p->buffers );
	memset( p->buffers, 0, buffer_pool_byte_size );

	XE_ASSERT( ( desc->image_pool_size > 0 ) && ( desc->image_pool_size < _MAX_POOL_SIZE ) );
	_init_pool( &p->image_pool, desc->image_pool_size );
	size_t image_pool_byte_size = sizeof( _image_t ) * p->image_pool.size;
	p->images = (_image_t * )malloc( image_pool_byte_size );
	XE_ASSERT( p->images );
	memset( p->images, 0, image_pool_byte_size );

	XE_ASSERT( ( desc->shader_pool_size > 0 ) && ( desc->shader_pool_size < _MAX_POOL_SIZE ) );
	_init_pool( &p->shader_pool, desc->shader_pool_size );
	size_t shader_pool_byte_size = sizeof( _shader_t ) * p->shader_pool.size;
	p->shaders = (_shader_t * )malloc( shader_pool_byte_size );
	XE_ASSERT( p->shaders );
	memset( p->shaders, 0, shader_pool_byte_size );

	XE_ASSERT( ( desc->pipeline_pool_size > 0 ) && ( desc->pipeline_pool_size < _MAX_POOL_SIZE ) );
	_init_pool( &p->pipeline_pool, desc->pipeline_pool_size );
	size_t pipeline_pool_byte_size = sizeof( _pipeline_t ) * p->pipeline_pool.size;
	p->pipelines = (_pipeline_t * )malloc( pipeline_pool_byte_size );
	XE_ASSERT( p->pipelines );
	memset( p->pipelines, 0, pipeline_pool_byte_size );

	XE_ASSERT( ( desc->pass_pool_size > 0 ) && ( desc->pass_pool_size < _MAX_POOL_SIZE ) );
	_init_pool( &p->pass_pool, desc->pass_pool_size );
	size_t pass_pool_byte_size = sizeof( _pass_t ) * p->pass_pool.size;
	p->passes = (_pass_t * )malloc( pass_pool_byte_size );
	XE_ASSERT( p->passes );
	memset( p->passes, 0, pass_pool_byte_size );

	XE_ASSERT( ( desc->context_pool_size > 0 ) && ( desc->context_pool_size < _MAX_POOL_SIZE ) );
	_init_pool( &p->context_pool, desc->context_pool_size );
	size_t context_pool_byte_size = sizeof( _context_t ) * p->context_pool.size;
	p->contexts = (_context_t * )malloc( context_pool_byte_size );
	XE_ASSERT( p->contexts );
	memset( p->contexts, 0, context_pool_byte_size );
}

void _discard_pools( _pools_t * p )
{
	XE_ASSERT( p );
	free( p->contexts );    p->contexts = 0;
	free( p->passes );      p->passes = 0;
	free( p->pipelines );   p->pipelines = 0;
	free( p->shaders );     p->shaders = 0;
	free( p->images );      p->images = 0;
	free( p->buffers );     p->buffers = 0;
	_discard_pool( &p->context_pool );
	_discard_pool( &p->pass_pool );
	_discard_pool( &p->pipeline_pool );
	_discard_pool( &p->shader_pool );
	_discard_pool( &p->image_pool );
	_discard_pool( &p->buffer_pool );
}

/* allocate the slot at slot_index:
	- bump the slot's generation counter
	- create a resource id from the generation counter and slot index
	- set the slot's id to this id
	- set the slot's state to ALLOC
	- return the resource id
*/
uint32_t _slot_alloc( _pool_t * pool, _slot_t * slot, int slot_index )
{
	/* FIXME: add handling for an overflowing generation counter,
	   for now, just overflow (another option is to disable
	   the slot)
	*/
	XE_ASSERT( pool && pool->gen_ctrs );
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < pool->size ) );
	XE_ASSERT( ( slot->state == RESOURCESTATE_INITIAL ) && !( slot->id ) );
	uint32_t ctr = ++pool->gen_ctrs[slot_index];
	slot->id = ( ctr << _SLOT_SHIFT ) | ( slot_index & _SLOT_MASK );
	slot->state = RESOURCESTATE_ALLOC;
	return slot->id;
}

/* extract slot index from id */
int _slot_index( uint32_t id )
{
	int slot_index = (int )( id & _SLOT_MASK );
	XE_ASSERT( INVALID_SLOT_INDEX != slot_index );
	return slot_index;
}

/* returns pointer to resource by id without matching id check */
_buffer_t * _buffer_at( const _pools_t * p, uint32_t buf_id )
{
	XE_ASSERT( p && ( buf_id ) );
	int slot_index = _slot_index( buf_id );
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < p->buffer_pool.size ) );
	return &p->buffers[slot_index];
}

_image_t * _image_at( const _pools_t * p, uint32_t img_id )
{
	XE_ASSERT( p && ( img_id ) );
	int slot_index = _slot_index( img_id );
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < p->image_pool.size ) );
	return &p->images[slot_index];
}

_shader_t * _shader_at( const _pools_t * p, uint32_t shd_id )
{
	XE_ASSERT( p && ( shd_id ) );
	int slot_index = _slot_index( shd_id );
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < p->shader_pool.size ) );
	return &p->shaders[slot_index];
}

_pipeline_t * _pipeline_at( const _pools_t * p, uint32_t pip_id )
{
	XE_ASSERT( p && ( pip_id ) );
	int slot_index = _slot_index( pip_id );
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < p->pipeline_pool.size ) );
	return &p->pipelines[slot_index];
}

_pass_t * _pass_at( const _pools_t * p, uint32_t pass_id )
{
	XE_ASSERT( p && ( pass_id ) );
	int slot_index = _slot_index( pass_id );
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < p->pass_pool.size ) );
	return &p->passes[slot_index];
}

_context_t * _context_at( const _pools_t * p, uint32_t context_id )
{
	XE_ASSERT( p && ( context_id ) );
	int slot_index = _slot_index( context_id );
	XE_ASSERT( ( slot_index > INVALID_SLOT_INDEX ) && ( slot_index < p->context_pool.size ) );
	return &p->contexts[slot_index];
}

/* returns pointer to resource with matching id check, may return 0 */
_buffer_t * _lookup_buffer( const _pools_t * p, uint32_t buf_id )
{
	if( buf_id )
	{
		_buffer_t * buf = _buffer_at( p, buf_id );
		if( buf->slot.id == buf_id )
		{
			return buf;
		}
	}
	return 0;
}

_image_t * _lookup_image( const _pools_t * p, uint32_t img_id )
{
	if( img_id )
	{
		_image_t * img = _image_at( p, img_id );
		if( img->slot.id == img_id )
		{
			return img;
		}
	}
	return 0;
}

_shader_t * _lookup_shader( const _pools_t * p, uint32_t shd_id )
{
	XE_ASSERT( p );
	if( shd_id )
	{
		_shader_t * shd = _shader_at( p, shd_id );
		if( shd->slot.id == shd_id )
		{
			return shd;
		}
	}
	return 0;
}

_pipeline_t * _lookup_pipeline( const _pools_t * p, uint32_t pip_id )
{
	XE_ASSERT( p );
	if( pip_id )
	{
		_pipeline_t * pip = _pipeline_at( p, pip_id );
		if( pip->slot.id == pip_id )
		{
			return pip;
		}
	}
	return 0;
}

_pass_t * _lookup_pass( const _pools_t * p, uint32_t pass_id )
{
	XE_ASSERT( p );
	if( pass_id )
	{
		_pass_t * pass = _pass_at( p, pass_id );
		if( pass->slot.id == pass_id )
		{
			return pass;
		}
	}
	return 0;
}

_context_t * _lookup_context( const _pools_t * p, uint32_t ctx_id )
{
	XE_ASSERT( p );
	if( ctx_id )
	{
		_context_t * ctx = _context_at( p, ctx_id );
		if( ctx->slot.id == ctx_id )
		{
			return ctx;
		}
	}
	return 0;
}

void _destroy_all_resources( _pools_t * p, uint32_t ctx_id )
{
	/*  this is a bit dumb since it loops over all pool slots to
		find the occupied slots, on the other hand it is only ever
		executed at shutdown
		NOTE: ONLY EXECUTE THIS AT SHUTDOWN
			  ...because the free queues will not be reset
			  and the resource slots not be cleared!
	*/
	for( int i = 1; i < p->buffer_pool.size; i++ )
	{
		if( p->buffers[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->buffers[i].slot.state;
			if( ( state == RESOURCESTATE_VALID ) || ( state == RESOURCESTATE_FAILED ) )
			{
				_destroy_buffer( &p->buffers[i] );
			}
		}
	}
	for( int i = 1; i < p->image_pool.size; i++ )
	{
		if( p->images[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->images[i].slot.state;
			if( ( state == RESOURCESTATE_VALID ) || ( state == RESOURCESTATE_FAILED ) )
			{
				_destroy_image( &p->images[i] );
			}
		}
	}
	for( int i = 1; i < p->shader_pool.size; i++ )
	{
		if( p->shaders[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->shaders[i].slot.state;
			if( ( state == RESOURCESTATE_VALID ) || ( state == RESOURCESTATE_FAILED ) )
			{
				_destroy_shader( &p->shaders[i] );
			}
		}
	}
	for( int i = 1; i < p->pipeline_pool.size; i++ )
	{
		if( p->pipelines[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->pipelines[i].slot.state;
			if( ( state == RESOURCESTATE_VALID ) || ( state == RESOURCESTATE_FAILED ) )
			{
				_destroy_pipeline( &p->pipelines[i] );
			}
		}
	}
	for( int i = 1; i < p->pass_pool.size; i++ )
	{
		if( p->passes[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->passes[i].slot.state;
			if( ( state == RESOURCESTATE_VALID ) || ( state == RESOURCESTATE_FAILED ) )
			{
				_destroy_pass( &p->passes[i] );
			}
		}
	}
}



XE::String _validate_string( _validate_error_t err )
{
	switch( err )
	{
		/* buffer creation validation errors */
	case _validate_error_t::_VALIDATE_BUFFERDESC_CANARY:        return "BufferDesc not initialized";
	case _validate_error_t::_VALIDATE_BUFFERDESC_SIZE:          return "BufferDesc.size cannot be 0";
	case _validate_error_t::_VALIDATE_BUFFERDESC_CONTENT:       return "immutable buffers must be initialized with content (BufferDesc.content)";
	case _validate_error_t::_VALIDATE_BUFFERDESC_NO_CONTENT:    return "dynamic/stream usage buffers cannot be initialized with content";

		/* image creation validation errros */
	case _validate_error_t::_VALIDATE_IMAGEDESC_CANARY:             return "ImageDesc not initialized";
	case _validate_error_t::_VALIDATE_IMAGEDESC_WIDTH:              return "ImageDesc.width must be > 0";
	case _validate_error_t::_VALIDATE_IMAGEDESC_HEIGHT:             return "ImageDesc.height must be > 0";
	case _validate_error_t::_VALIDATE_IMAGEDESC_RT_PIXELFORMAT:     return "invalid pixel format for render-target image";
	case _validate_error_t::_VALIDATE_IMAGEDESC_NONRT_PIXELFORMAT:  return "invalid pixel format for non-render-target image";
	case _validate_error_t::_VALIDATE_IMAGEDESC_MSAA_BUT_NO_RT:     return "non-render-target images cannot be multisampled";
	case _validate_error_t::_VALIDATE_IMAGEDESC_NO_MSAA_RT_SUPPORT: return "MSAA not supported for this pixel format";
	case _validate_error_t::_VALIDATE_IMAGEDESC_RT_IMMUTABLE:       return "render target images must be USAGE_IMMUTABLE";
	case _validate_error_t::_VALIDATE_IMAGEDESC_RT_NO_CONTENT:      return "render target images cannot be initialized with content";
	case _validate_error_t::_VALIDATE_IMAGEDESC_CONTENT:            return "missing or invalid content for immutable image";
	case _validate_error_t::_VALIDATE_IMAGEDESC_NO_CONTENT:         return "dynamic/stream usage images cannot be initialized with content";

		/* shader creation */
	case _validate_error_t::_VALIDATE_SHADERDESC_CANARY:                return "ShaderDesc not initialized";
	case _validate_error_t::_VALIDATE_SHADERDESC_SOURCE:                return "shader source code required";
	case _validate_error_t::_VALIDATE_SHADERDESC_BYTECODE:              return "shader byte code required";
	case _validate_error_t::_VALIDATE_SHADERDESC_SOURCE_OR_BYTECODE:    return "shader source or byte code required";
	case _validate_error_t::_VALIDATE_SHADERDESC_NO_BYTECODE_SIZE:      return "shader byte code length (in bytes) required";
	case _validate_error_t::_VALIDATE_SHADERDESC_NO_CONT_UBS:           return "shader uniform blocks must occupy continuous slots";
	case _validate_error_t::_VALIDATE_SHADERDESC_NO_CONT_UB_MEMBERS:    return "uniform block members must occupy continuous slots";
	case _validate_error_t::_VALIDATE_SHADERDESC_NO_UB_MEMBERS:         return "GL backend requires uniform block member declarations";
	case _validate_error_t::_VALIDATE_SHADERDESC_UB_MEMBER_NAME:        return "uniform block member name missing";
	case _validate_error_t::_VALIDATE_SHADERDESC_UB_SIZE_MISMATCH:      return "size of uniform block members doesn't match uniform block size";
	case _validate_error_t::_VALIDATE_SHADERDESC_NO_CONT_IMGS:          return "shader images must occupy continuous slots";
	case _validate_error_t::_VALIDATE_SHADERDESC_IMG_NAME:              return "GL backend requires uniform block member names";
	case _validate_error_t::_VALIDATE_SHADERDESC_ATTR_NAMES:            return "GLES2 backend requires vertex attribute names";
	case _validate_error_t::_VALIDATE_SHADERDESC_ATTR_SEMANTICS:        return "D3D11 backend requires vertex attribute semantics";
	case _validate_error_t::_VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG:  return "vertex attribute name/semantic string too long (max len 16)";

		/* pipeline creation */
	case _validate_error_t::_VALIDATE_PIPELINEDESC_CANARY:          return "PipelineDesc not initialized";
	case _validate_error_t::_VALIDATE_PIPELINEDESC_SHADER:          return "PipelineDesc.shader missing or invalid";
	case _validate_error_t::_VALIDATE_PIPELINEDESC_NO_ATTRS:        return "PipelineDesc.layout.attrs is empty or not continuous";
	case _validate_error_t::_VALIDATE_PIPELINEDESC_LAYOUT_STRIDE4:  return "PipelineDesc.layout.buffers[].stride must be multiple of 4";
	case _validate_error_t::_VALIDATE_PIPELINEDESC_ATTR_NAME:       return "GLES2/WebGL missing vertex attribute name in shader";
	case _validate_error_t::_VALIDATE_PIPELINEDESC_ATTR_SEMANTICS:  return "D3D11 missing vertex attribute semantics in shader";

		/* pass creation */
	case _validate_error_t::_VALIDATE_PASSDESC_CANARY:                  return "PassDesc not initialized";
	case _validate_error_t::_VALIDATE_PASSDESC_NO_COLOR_ATTS:           return "PassDesc.color_attachments[0] must be valid";
	case _validate_error_t::_VALIDATE_PASSDESC_NO_CONT_COLOR_ATTS:      return "color attachments must occupy continuous slots";
	case _validate_error_t::_VALIDATE_PASSDESC_IMAGE:                   return "pass attachment image is not valid";
	case _validate_error_t::_VALIDATE_PASSDESC_MIPLEVEL:                return "pass attachment mip level is bigger than image has mipmaps";
	case _validate_error_t::_VALIDATE_PASSDESC_FACE:                    return "pass attachment image is cubemap, but face index is too big";
	case _validate_error_t::_VALIDATE_PASSDESC_LAYER:                   return "pass attachment image is array texture, but layer index is too big";
	case _validate_error_t::_VALIDATE_PASSDESC_SLICE:                   return "pass attachment image is 3d texture, but slice value is too big";
	case _validate_error_t::_VALIDATE_PASSDESC_IMAGE_NO_RT:             return "pass attachment image must be render targets";
	case _validate_error_t::_VALIDATE_PASSDESC_COLOR_PIXELFORMATS:      return "all pass color attachment images must have the same pixel format";
	case _validate_error_t::_VALIDATE_PASSDESC_COLOR_INV_PIXELFORMAT:   return "pass color-attachment images must have a renderable pixel format";
	case _validate_error_t::_VALIDATE_PASSDESC_DEPTH_INV_PIXELFORMAT:   return "pass depth-attachment image must have depth pixel format";
	case _validate_error_t::_VALIDATE_PASSDESC_IMAGE_SIZES:             return "all pass attachments must have the same size";
	case _validate_error_t::_VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS:     return "all pass attachments must have the same sample count";

		/* begin_pass */
	case _validate_error_t::_VALIDATE_BEGINPASS_PASS:       return "begin_pass: pass must be valid";
	case _validate_error_t::_VALIDATE_BEGINPASS_IMAGE:      return "begin_pass: one or more attachment images are not valid";

		/* apply_pipeline */
	case _validate_error_t::_VALIDATE_APIP_PIPELINE_VALID_ID:   return "apply_pipeline: invalid pipeline id provided";
	case _validate_error_t::_VALIDATE_APIP_PIPELINE_EXISTS:     return "apply_pipeline: pipeline object no longer alive";
	case _validate_error_t::_VALIDATE_APIP_PIPELINE_VALID:      return "apply_pipeline: pipeline object not in valid state";
	case _validate_error_t::_VALIDATE_APIP_SHADER_EXISTS:       return "apply_pipeline: shader object no longer alive";
	case _validate_error_t::_VALIDATE_APIP_SHADER_VALID:        return "apply_pipeline: shader object not in valid state";
	case _validate_error_t::_VALIDATE_APIP_ATT_COUNT:           return "apply_pipeline: color_attachment_count in pipeline doesn't match number of pass color attachments";
	case _validate_error_t::_VALIDATE_APIP_COLOR_FORMAT:        return "apply_pipeline: color_format in pipeline doesn't match pass color attachment pixel format";
	case _validate_error_t::_VALIDATE_APIP_DEPTH_FORMAT:        return "apply_pipeline: depth_format in pipeline doesn't match pass depth attachment pixel format";
	case _validate_error_t::_VALIDATE_APIP_SAMPLE_COUNT:        return "apply_pipeline: MSAA sample count in pipeline doesn't match render pass attachment sample count";

		/* apply_bindings */
	case _validate_error_t::_VALIDATE_ABND_PIPELINE:            return "apply_bindings: must be called after apply_pipeline";
	case _validate_error_t::_VALIDATE_ABND_PIPELINE_EXISTS:     return "apply_bindings: currently applied pipeline object no longer alive";
	case _validate_error_t::_VALIDATE_ABND_PIPELINE_VALID:      return "apply_bindings: currently applied pipeline object not in valid state";
	case _validate_error_t::_VALIDATE_ABND_VBS:                 return "apply_bindings: number of vertex buffers doesn't match number of pipeline vertex layouts";
	case _validate_error_t::_VALIDATE_ABND_VB_EXISTS:           return "apply_bindings: vertex buffer no longer alive";
	case _validate_error_t::_VALIDATE_ABND_VB_TYPE:             return "apply_bindings: buffer in vertex buffer slot is not a BUFFERTYPE_VERTEXBUFFER";
	case _validate_error_t::_VALIDATE_ABND_VB_OVERFLOW:         return "apply_bindings: buffer in vertex buffer slot is overflown";
	case _validate_error_t::_VALIDATE_ABND_NO_IB:               return "apply_bindings: pipeline object defines indexed rendering, but no index buffer provided";
	case _validate_error_t::_VALIDATE_ABND_IB:                  return "apply_bindings: pipeline object defines non-indexed rendering, but index buffer provided";
	case _validate_error_t::_VALIDATE_ABND_IB_EXISTS:           return "apply_bindings: index buffer no longer alive";
	case _validate_error_t::_VALIDATE_ABND_IB_TYPE:             return "apply_bindings: buffer in index buffer slot is not a BUFFERTYPE_INDEXBUFFER";
	case _validate_error_t::_VALIDATE_ABND_IB_OVERFLOW:         return "apply_bindings: buffer in index buffer slot is overflown";
	case _validate_error_t::_VALIDATE_ABND_VS_IMGS:             return "apply_bindings: vertex shader image count doesn't match ShaderDesc";
	case _validate_error_t::_VALIDATE_ABND_VS_IMG_EXISTS:       return "apply_bindings: vertex shader image no longer alive";
	case _validate_error_t::_VALIDATE_ABND_VS_IMG_TYPES:        return "apply_bindings: one or more vertex shader image types don't match ShaderDesc";
	case _validate_error_t::_VALIDATE_ABND_FS_IMGS:             return "apply_bindings: fragment shader image count doesn't match ShaderDesc";
	case _validate_error_t::_VALIDATE_ABND_FS_IMG_EXISTS:       return "apply_bindings: fragment shader image no longer alive";
	case _validate_error_t::_VALIDATE_ABND_FS_IMG_TYPES:        return "apply_bindings: one or more fragment shader image types don't match ShaderDesc";

		/* apply_uniforms */
	case _validate_error_t::_VALIDATE_AUB_NO_PIPELINE:      return "apply_uniforms: must be called after apply_pipeline()";
	case _validate_error_t::_VALIDATE_AUB_NO_UB_AT_SLOT:    return "apply_uniforms: no uniform block declaration at this shader stage UB slot";
	case _validate_error_t::_VALIDATE_AUB_SIZE:             return "apply_uniforms: data size exceeds declared uniform block size";

		/* update_buffer */
	case _validate_error_t::_VALIDATE_UPDATEBUF_USAGE:      return "update_buffer: cannot update immutable buffer";
	case _validate_error_t::_VALIDATE_UPDATEBUF_SIZE:       return "update_buffer: update size is bigger than buffer size";
	case _validate_error_t::_VALIDATE_UPDATEBUF_ONCE:       return "update_buffer: only one update allowed per buffer and frame";
	case _validate_error_t::_VALIDATE_UPDATEBUF_APPEND:     return "update_buffer: cannot call update_buffer and append_buffer in same frame";

		/* append_buffer */
	case _validate_error_t::_VALIDATE_APPENDBUF_USAGE:      return "append_buffer: cannot append to immutable buffer";
	case _validate_error_t::_VALIDATE_APPENDBUF_SIZE:       return "append_buffer: overall appended size is bigger than buffer size";
	case _validate_error_t::_VALIDATE_APPENDBUF_UPDATE:     return "append_buffer: cannot call append_buffer and update_buffer in same frame";

		/* update_image */
	case _validate_error_t::_VALIDATE_UPDIMG_USAGE:         return "update_image: cannot update immutable image";
	case _validate_error_t::_VALIDATE_UPDIMG_NOTENOUGHDATA: return "update_image: not enough subimage data provided";
	case _validate_error_t::_VALIDATE_UPDIMG_SIZE:          return "update_image: provided subimage data size too big";
	case _validate_error_t::_VALIDATE_UPDIMG_COMPRESSED:    return "update_image: cannot update images with compressed format";
	case _validate_error_t::_VALIDATE_UPDIMG_ONCE:          return "update_image: only one update allowed per image and frame";

	default: return "unknown validation error";
	}
}



void _validate_begin( void )
{
	_sg.validate_error = _VALIDATE_SUCCESS;
}

void _validate( bool cond, _validate_error_t err )
{
	if( !cond )
	{
		_sg.validate_error = err;
		puts( _validate_string( err ) );
	}
}

bool _validate_end( void )
{
	if( _sg.validate_error != _VALIDATE_SUCCESS )
	{
	#if !defined(_validate_NON_FATAL)
		puts( "^^^^  VALIDATION FAILED, TERMINATING ^^^^" );
		XE_ASSERT( false );
	#endif
		return false;
	}
	else
	{
		return true;
	}
}

bool _validate_buffer_desc( const BufferDesc * desc )
{
	XE_ASSERT( desc );
	_validate_begin();
	_validate( desc->_start_canary == 0, _VALIDATE_BUFFERDESC_CANARY );
	_validate( desc->_end_canary == 0, _VALIDATE_BUFFERDESC_CANARY );
	_validate( desc->size > 0, _VALIDATE_BUFFERDESC_SIZE );
	bool ext = ( 0 != desc->gl_buffers[0] ) || ( 0 != desc->mtl_buffers[0] ) || ( 0 != desc->d3d11_buffer );
	if( !ext && ( desc->usage == USAGE_IMMUTABLE ) )
	{
		_validate( 0 != desc->content, _VALIDATE_BUFFERDESC_CONTENT );
	}
	else
	{
		_validate( 0 == desc->content, _VALIDATE_BUFFERDESC_NO_CONTENT );
	}
	return _validate_end();
}

bool _validate_image_desc( const ImageDesc * desc )
{
	XE_ASSERT( desc );
	_validate_begin();
	_validate( desc->_start_canary == 0, _VALIDATE_IMAGEDESC_CANARY );
	_validate( desc->_end_canary == 0, _VALIDATE_IMAGEDESC_CANARY );
	_validate( desc->width > 0, _VALIDATE_IMAGEDESC_WIDTH );
	_validate( desc->height > 0, _VALIDATE_IMAGEDESC_HEIGHT );
	const PixelFormat fmt = desc->pixel_format;
	const Usage usage = desc->usage;
	const bool ext = ( 0 != desc->gl_textures[0] ) || ( 0 != desc->mtl_textures[0] ) || ( 0 != desc->d3d11_texture );
	if( desc->render_target )
	{
		XE_ASSERT( ( (int )fmt >= 0 ) && ( (int )fmt < _PIXELFORMAT_NUM ) );
		_validate( _sg.formats[fmt].render, _VALIDATE_IMAGEDESC_RT_PIXELFORMAT );
		/* on GLES2, sample count for render targets is completely ignored */
	#if defined(SOKOL_GLES2) || defined(SOKOL_GLES3)
		if( !_sg.gl.gles2 )
		{
		#endif
			if( desc->sample_count > 1 )
			{
				_validate( _sg.features.msaa_render_targets && _sg.formats[fmt].msaa, _VALIDATE_IMAGEDESC_NO_MSAA_RT_SUPPORT );
			}
		#if defined(SOKOL_GLES2) || defined(SOKOL_GLES3)
		}
	#endif
		_validate( usage == USAGE_IMMUTABLE, _VALIDATE_IMAGEDESC_RT_IMMUTABLE );
		_validate( desc->content.subimage[0][0].ptr == 0, _VALIDATE_IMAGEDESC_RT_NO_CONTENT );
	}
	else
	{
		_validate( desc->sample_count <= 1, _VALIDATE_IMAGEDESC_MSAA_BUT_NO_RT );
		const bool valid_nonrt_fmt = !_is_valid_rendertarget_depth_format( fmt );
		_validate( valid_nonrt_fmt, _VALIDATE_IMAGEDESC_NONRT_PIXELFORMAT );
		/* FIXME: should use the same "expected size" computation as in _validate_update_image() here */
		if( !ext && ( usage == USAGE_IMMUTABLE ) )
		{
			const int num_faces = desc->type == IMAGETYPE_CUBE ? 6 : 1;
			const int num_mips = desc->num_mipmaps;
			for( int face_index = 0; face_index < num_faces; face_index++ )
			{
				for( int mip_index = 0; mip_index < num_mips; mip_index++ )
				{
					const bool has_data = desc->content.subimage[face_index][mip_index].ptr != 0;
					const bool has_size = desc->content.subimage[face_index][mip_index].size > 0;
					_validate( has_data && has_size, _VALIDATE_IMAGEDESC_CONTENT );
				}
			}
		}
		else
		{
			for( int face_index = 0; face_index < CUBEFACE_NUM; face_index++ )
			{
				for( int mip_index = 0; mip_index < MAX_MIPMAPS; mip_index++ )
				{
					const bool no_data = 0 == desc->content.subimage[face_index][mip_index].ptr;
					const bool no_size = 0 == desc->content.subimage[face_index][mip_index].size;
					_validate( no_data && no_size, _VALIDATE_IMAGEDESC_NO_CONTENT );
				}
			}
		}
	}
	return _validate_end();
}

bool _validate_shader_desc( const ShaderDesc * desc )
{
	XE_ASSERT( desc );
	_validate_begin();
	_validate( desc->_start_canary == 0, _VALIDATE_SHADERDESC_CANARY );
	_validate( desc->_end_canary == 0, _VALIDATE_SHADERDESC_CANARY );
	_validate( 0 != desc->attrs[0].name, _VALIDATE_SHADERDESC_ATTR_NAMES );
	_validate( 0 != desc->attrs[0].sem_name, _VALIDATE_SHADERDESC_ATTR_SEMANTICS );
	_validate( 0 != desc->vs.source, _VALIDATE_SHADERDESC_SOURCE );
	_validate( 0 != desc->fs.source, _VALIDATE_SHADERDESC_SOURCE );

	for( int i = 0; i < MAX_VERTEX_ATTRIBUTES; i++ )
	{
		if( desc->attrs[i].name )
		{
			_validate( strlen( desc->attrs[i].name ) < _STRING_SIZE, _VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG );
		}
		if( desc->attrs[i].sem_name )
		{
			_validate( strlen( desc->attrs[i].sem_name ) < _STRING_SIZE, _VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG );
		}
	}
	/* if shader byte code, the size must also be provided */
	if( 0 != desc->vs.byte_code )
	{
		_validate( desc->vs.byte_code_size > 0, _VALIDATE_SHADERDESC_NO_BYTECODE_SIZE );
	}
	if( 0 != desc->fs.byte_code )
	{
		_validate( desc->fs.byte_code_size > 0, _VALIDATE_SHADERDESC_NO_BYTECODE_SIZE );
	}
	for( int stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
	{
		const ShaderStageDesc * stage_desc = ( stage_index == 0 ) ? &desc->vs : &desc->fs;
		bool uniform_blocks_continuous = true;
		for( int ub_index = 0; ub_index < MAX_SHADERSTAGE_UBS; ub_index++ )
		{
			const ShaderUniformBlockDesc * ub_desc = &stage_desc->uniform_blocks[ub_index];
			if( ub_desc->size > 0 )
			{
				_validate( uniform_blocks_continuous, _VALIDATE_SHADERDESC_NO_CONT_UBS );
				bool uniforms_continuous = true;
				int uniform_offset = 0;
				int num_uniforms = 0;
				for( int u_index = 0; u_index < MAX_UB_MEMBERS; u_index++ )
				{
					const ShaderUniformDesc * u_desc = &ub_desc->uniforms[u_index];
					if( u_desc->type != UNIFORMTYPE_INVALID )
					{
						_validate( uniforms_continuous, _VALIDATE_SHADERDESC_NO_CONT_UB_MEMBERS );
						_validate( u_desc->name, _VALIDATE_SHADERDESC_UB_MEMBER_NAME );
						const int array_count = u_desc->array_count;
						uniform_offset += _uniform_size( u_desc->type, array_count );
						num_uniforms++;
					}
					else
					{
						uniforms_continuous = false;
					}
				}
				_validate( uniform_offset == ub_desc->size, _VALIDATE_SHADERDESC_UB_SIZE_MISMATCH );
				_validate( num_uniforms > 0, _VALIDATE_SHADERDESC_NO_UB_MEMBERS );
			}
			else
			{
				uniform_blocks_continuous = false;
			}
		}
		bool images_continuous = true;
		for( int img_index = 0; img_index < MAX_SHADERSTAGE_IMAGES; img_index++ )
		{
			const ShaderImageDesc * img_desc = &stage_desc->images[img_index];
			if( img_desc->type != _IMAGETYPE_DEFAULT )
			{
				_validate( images_continuous, _VALIDATE_SHADERDESC_NO_CONT_IMGS );
				_validate( img_desc->name, _VALIDATE_SHADERDESC_IMG_NAME );
			}
			else
			{
				images_continuous = false;
			}
		}
	}
	return _validate_end();
}

bool _validate_pipeline_desc( const PipelineDesc * desc )
{
	XE_ASSERT( desc );
	_validate_begin();
	_validate( desc->_start_canary == 0, _VALIDATE_PIPELINEDESC_CANARY );
	_validate( desc->_end_canary == 0, _VALIDATE_PIPELINEDESC_CANARY );
	_validate( desc->shader, _VALIDATE_PIPELINEDESC_SHADER );
	const _shader_t * shd = _lookup_shader( &_sg.pools, desc->shader.GetValue() );
	_validate( shd && shd->slot.state == RESOURCESTATE_VALID, _VALIDATE_PIPELINEDESC_SHADER );
	for( int buf_index = 0; buf_index < MAX_SHADERSTAGE_BUFFERS; buf_index++ )
	{
		const BufferLayoutDesc * l_desc = &desc->layout.buffers[buf_index];
		if( l_desc->stride == 0 )
		{
			continue;
		}
		_validate( ( l_desc->stride & 3 ) == 0, _VALIDATE_PIPELINEDESC_LAYOUT_STRIDE4 );
	}
	_validate( desc->layout.attrs[0].format != VERTEXFORMAT_INVALID, _VALIDATE_PIPELINEDESC_NO_ATTRS );
	bool attrs_cont = true;
	for( int attr_index = 0; attr_index < MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		const VertexAttrDesc * a_desc = &desc->layout.attrs[attr_index];
		if( a_desc->format == VERTEXFORMAT_INVALID )
		{
			attrs_cont = false;
			continue;
		}
		_validate( attrs_cont, _VALIDATE_PIPELINEDESC_NO_ATTRS );
		XE_ASSERT( a_desc->buffer_index < MAX_SHADERSTAGE_BUFFERS );
	#if defined(SOKOL_GLES2)
		/* on GLES2, vertex attribute names must be provided */
		_validate( shd->attrs[attr_index].name != "", _VALIDATE_PIPELINEDESC_ATTR_NAME );
	#elif defined(SOKOL_D3D11)
		/* on D3D11, semantic names (and semantic indices) must be provided */
		_validate( shd->d3d11.attrs[attr_index].sem_name != "", _VALIDATE_PIPELINEDESC_ATTR_SEMANTICS );
	#endif
	}
	return _validate_end();
}

bool _validate_pass_desc( const PassDesc * desc )
{
	XE_ASSERT( desc );
	_validate_begin();
	_validate( desc->_start_canary == 0, _VALIDATE_PASSDESC_CANARY );
	_validate( desc->_end_canary == 0, _VALIDATE_PASSDESC_CANARY );
	bool atts_cont = true;
	PixelFormat color_fmt = PIXELFORMAT_NONE;
	int width = -1, height = -1, sample_count = -1;
	for( int att_index = 0; att_index < MAX_COLOR_ATTACHMENTS; att_index++ )
	{
		const AttachmentDesc * att = &desc->color_attachments[att_index];
		if( att->image )
		{
			_validate( att_index > 0, _VALIDATE_PASSDESC_NO_COLOR_ATTS );
			atts_cont = false;
			continue;
		}
		_validate( atts_cont, _VALIDATE_PASSDESC_NO_CONT_COLOR_ATTS );
		const _image_t * img = _lookup_image( &_sg.pools, att->image.GetValue() );
		_validate( img && img->slot.state == RESOURCESTATE_VALID, _VALIDATE_PASSDESC_IMAGE );
		_validate( att->mip_level < img->cmn.num_mipmaps, _VALIDATE_PASSDESC_MIPLEVEL );
		if( img->cmn.type == IMAGETYPE_CUBE )
		{
			_validate( att->face < 6, _VALIDATE_PASSDESC_FACE );
		}
		else if( img->cmn.type == IMAGETYPE_ARRAY )
		{
			_validate( att->layer < img->cmn.depth, _VALIDATE_PASSDESC_LAYER );
		}
		else if( img->cmn.type == IMAGETYPE_3D )
		{
			_validate( att->slice < img->cmn.depth, _VALIDATE_PASSDESC_SLICE );
		}
		_validate( img->cmn.render_target, _VALIDATE_PASSDESC_IMAGE_NO_RT );
		if( att_index == 0 )
		{
			color_fmt = img->cmn.pixel_format;
			width = img->cmn.width >> att->mip_level;
			height = img->cmn.height >> att->mip_level;
			sample_count = img->cmn.sample_count;
		}
		else
		{
			_validate( img->cmn.pixel_format == color_fmt, _VALIDATE_PASSDESC_COLOR_PIXELFORMATS );
			_validate( width == img->cmn.width >> att->mip_level, _VALIDATE_PASSDESC_IMAGE_SIZES );
			_validate( height == img->cmn.height >> att->mip_level, _VALIDATE_PASSDESC_IMAGE_SIZES );
			_validate( sample_count == img->cmn.sample_count, _VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS );
		}
		_validate( _is_valid_rendertarget_color_format( img->cmn.pixel_format ), _VALIDATE_PASSDESC_COLOR_INV_PIXELFORMAT );
	}
	if( desc->depth_stencil_attachment.image )
	{
		const AttachmentDesc * att = &desc->depth_stencil_attachment;
		const _image_t * img = _lookup_image( &_sg.pools, att->image.GetValue() );
		_validate( img && img->slot.state == RESOURCESTATE_VALID, _VALIDATE_PASSDESC_IMAGE );
		_validate( att->mip_level < img->cmn.num_mipmaps, _VALIDATE_PASSDESC_MIPLEVEL );
		if( img->cmn.type == IMAGETYPE_CUBE )
		{
			_validate( att->face < 6, _VALIDATE_PASSDESC_FACE );
		}
		else if( img->cmn.type == IMAGETYPE_ARRAY )
		{
			_validate( att->layer < img->cmn.depth, _VALIDATE_PASSDESC_LAYER );
		}
		else if( img->cmn.type == IMAGETYPE_3D )
		{
			_validate( att->slice < img->cmn.depth, _VALIDATE_PASSDESC_SLICE );
		}
		_validate( img->cmn.render_target, _VALIDATE_PASSDESC_IMAGE_NO_RT );
		_validate( width == img->cmn.width >> att->mip_level, _VALIDATE_PASSDESC_IMAGE_SIZES );
		_validate( height == img->cmn.height >> att->mip_level, _VALIDATE_PASSDESC_IMAGE_SIZES );
		_validate( sample_count == img->cmn.sample_count, _VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS );
		_validate( _is_valid_rendertarget_depth_format( img->cmn.pixel_format ), _VALIDATE_PASSDESC_DEPTH_INV_PIXELFORMAT );
	}
	return _validate_end();
}

bool _validate_begin_pass( _pass_t * pass )
{
	_validate_begin();
	_validate( pass->slot.state == RESOURCESTATE_VALID, _VALIDATE_BEGINPASS_PASS );

	for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
	{
		const _attachment_t * att = &pass->cmn.color_atts[i];
		const _image_t * img = _pass_color_image( pass, i );
		if( img )
		{
			_validate( img->slot.state == RESOURCESTATE_VALID, _VALIDATE_BEGINPASS_IMAGE );
			_validate( img->slot.id == att->image_id.GetValue(), _VALIDATE_BEGINPASS_IMAGE );
		}
	}
	const _image_t * ds_img = _pass_ds_image( pass );
	if( ds_img )
	{
		const _attachment_t * att = &pass->cmn.ds_att;
		_validate( ds_img->slot.state == RESOURCESTATE_VALID, _VALIDATE_BEGINPASS_IMAGE );
		_validate( ds_img->slot.id == att->image_id.GetValue(), _VALIDATE_BEGINPASS_IMAGE );
	}
	return _validate_end();
}

bool _validate_apply_pipeline( PipelineHandle pip_id )
{
	_validate_begin();
	/* the pipeline object must be alive and valid */
	_validate( pip_id, _VALIDATE_APIP_PIPELINE_VALID_ID );
	const _pipeline_t * pip = _lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	_validate( pip != 0, _VALIDATE_APIP_PIPELINE_EXISTS );
	if( !pip )
	{
		return _validate_end();
	}
	_validate( pip->slot.state == RESOURCESTATE_VALID, _VALIDATE_APIP_PIPELINE_VALID );
	/* the pipeline's shader must be alive and valid */
	XE_ASSERT( pip->shader );
	_validate( pip->shader->slot.id == pip->cmn.shader_id.GetValue(), _VALIDATE_APIP_SHADER_EXISTS );
	_validate( pip->shader->slot.state == RESOURCESTATE_VALID, _VALIDATE_APIP_SHADER_VALID );
	/* check that pipeline attributes match current pass attributes */
	const _pass_t * pass = _lookup_pass( &_sg.pools, _sg.cur_pass.GetValue() );
	if( pass )
	{
		/* an offscreen pass */
		const _image_t * att_img = _pass_color_image( pass, 0 );
		_validate( pip->cmn.color_attachment_count == pass->cmn.num_color_atts, _VALIDATE_APIP_ATT_COUNT );
		_validate( pip->cmn.color_format == att_img->cmn.pixel_format, _VALIDATE_APIP_COLOR_FORMAT );
		_validate( pip->cmn.sample_count == att_img->cmn.sample_count, _VALIDATE_APIP_SAMPLE_COUNT );
		const _image_t * att_dsimg = _pass_ds_image( pass );
		if( att_dsimg )
		{
			_validate( pip->cmn.depth_format == att_dsimg->cmn.pixel_format, _VALIDATE_APIP_DEPTH_FORMAT );
		}
		else
		{
			_validate( pip->cmn.depth_format == PIXELFORMAT_NONE, _VALIDATE_APIP_DEPTH_FORMAT );
		}
	}
	else
	{
		/* default pass */
		_validate( pip->cmn.color_attachment_count == 1, _VALIDATE_APIP_ATT_COUNT );
		_validate( pip->cmn.color_format == _default_rendertarget_colorformat(), _VALIDATE_APIP_COLOR_FORMAT );
		_validate( pip->cmn.depth_format == _default_rendertarget_depthformat(), _VALIDATE_APIP_DEPTH_FORMAT );
		/* FIXME: hmm, we don't know if the default framebuffer is multisampled here */
	}
	return _validate_end();
}

bool _validate_apply_bindings( const Bindings * bindings )
{
	_validate_begin();

	/* a pipeline object must have been applied */
	_validate( _sg.cur_pipeline, _VALIDATE_ABND_PIPELINE );
	const _pipeline_t * pip = _lookup_pipeline( &_sg.pools, _sg.cur_pipeline.GetValue() );
	_validate( pip != 0, _VALIDATE_ABND_PIPELINE_EXISTS );
	if( !pip )
	{
		return _validate_end();
	}
	_validate( pip->slot.state == RESOURCESTATE_VALID, _VALIDATE_ABND_PIPELINE_VALID );
	XE_ASSERT( pip->shader );

	/* has expected vertex buffers, and vertex buffers still exist */
	for( int i = 0; i < MAX_SHADERSTAGE_BUFFERS; i++ )
	{
		if( bindings->vertex_buffers[i] )
		{
			_validate( pip->cmn.vertex_layout_valid[i], _VALIDATE_ABND_VBS );
			/* buffers in vertex-buffer-slots must be of type BUFFERTYPE_VERTEXBUFFER */
			const _buffer_t * buf = _lookup_buffer( &_sg.pools, bindings->vertex_buffers[i].GetValue() );
			_validate( buf != 0, _VALIDATE_ABND_VB_EXISTS );
			if( buf && buf->slot.state == RESOURCESTATE_VALID )
			{
				_validate( BUFFERTYPE_VERTEXBUFFER == buf->cmn.type, _VALIDATE_ABND_VB_TYPE );
				_validate( !buf->cmn.append_overflow, _VALIDATE_ABND_VB_OVERFLOW );
			}
		}
		else
		{
			/* vertex buffer provided in a slot which has no vertex layout in pipeline */
			_validate( !pip->cmn.vertex_layout_valid[i], _VALIDATE_ABND_VBS );
		}
	}

	/* index buffer expected or not, and index buffer still exists */
	if( pip->cmn.index_type == INDEXTYPE_NONE )
	{
		/* pipeline defines non-indexed rendering, but index buffer provided */
		_validate( bindings->index_buffer == XE::BufferHandle::Invalid, _VALIDATE_ABND_IB );
	}
	else
	{
		/* pipeline defines indexed rendering, but no index buffer provided */
		_validate( bindings->index_buffer, _VALIDATE_ABND_NO_IB );
	}
	if( bindings->index_buffer )
	{
		/* buffer in index-buffer-slot must be of type BUFFERTYPE_INDEXBUFFER */
		const _buffer_t * buf = _lookup_buffer( &_sg.pools, bindings->index_buffer.GetValue() );
		_validate( buf != 0, _VALIDATE_ABND_IB_EXISTS );
		if( buf && buf->slot.state == RESOURCESTATE_VALID )
		{
			_validate( BUFFERTYPE_INDEXBUFFER == buf->cmn.type, _VALIDATE_ABND_IB_TYPE );
			_validate( !buf->cmn.append_overflow, _VALIDATE_ABND_IB_OVERFLOW );
		}
	}

	/* has expected vertex shader images */
	for( int i = 0; i < MAX_SHADERSTAGE_IMAGES; i++ )
	{
		_shader_stage_t * stage = &pip->shader->cmn.stage[SHADERSTAGE_VS];
		if( bindings->vs_images[i] )
		{
			_validate( i < stage->num_images, _VALIDATE_ABND_VS_IMGS );
			const _image_t * img = _lookup_image( &_sg.pools, bindings->vs_images[i].GetValue() );
			_validate( img != 0, _VALIDATE_ABND_VS_IMG_EXISTS );
			if( img && img->slot.state == RESOURCESTATE_VALID )
			{
				_validate( img->cmn.type == stage->images[i].type, _VALIDATE_ABND_VS_IMG_TYPES );
			}
		}
		else
		{
			_validate( i >= stage->num_images, _VALIDATE_ABND_VS_IMGS );
		}
	}

	/* has expected fragment shader images */
	for( int i = 0; i < MAX_SHADERSTAGE_IMAGES; i++ )
	{
		_shader_stage_t * stage = &pip->shader->cmn.stage[SHADERSTAGE_FS];
		if( bindings->fs_images[i] )
		{
			_validate( i < stage->num_images, _VALIDATE_ABND_FS_IMGS );
			const _image_t * img = _lookup_image( &_sg.pools, bindings->fs_images[i].GetValue() );
			_validate( img != 0, _VALIDATE_ABND_FS_IMG_EXISTS );
			if( img && img->slot.state == RESOURCESTATE_VALID )
			{
				_validate( img->cmn.type == stage->images[i].type, _VALIDATE_ABND_FS_IMG_TYPES );
			}
		}
		else
		{
			_validate( i >= stage->num_images, _VALIDATE_ABND_FS_IMGS );
		}
	}
	return _validate_end();
}

bool _validate_apply_uniforms( ShaderStage stage_index, int ub_index, const void * data, int num_bytes )
{
	XE_ASSERT( ( stage_index == SHADERSTAGE_VS ) || ( stage_index == SHADERSTAGE_FS ) );
	XE_ASSERT( ( ub_index >= 0 ) && ( ub_index < MAX_SHADERSTAGE_UBS ) );
	_validate_begin();
	_validate( _sg.cur_pipeline, _VALIDATE_AUB_NO_PIPELINE );
	const _pipeline_t * pip = _lookup_pipeline( &_sg.pools, _sg.cur_pipeline.GetValue() );
	XE_ASSERT( pip && ( pip->slot.id == _sg.cur_pipeline.GetValue() ) );
	XE_ASSERT( pip->shader && ( pip->shader->slot.id == pip->cmn.shader_id.GetValue() ) );

	/* check that there is a uniform block at 'stage' and 'ub_index' */
	const _shader_stage_t * stage = &pip->shader->cmn.stage[stage_index];
	_validate( ub_index < stage->num_uniform_blocks, _VALIDATE_AUB_NO_UB_AT_SLOT );

	/* check that the provided data size doesn't exceed the uniform block size */
	_validate( num_bytes <= stage->uniform_blocks[ub_index].size, _VALIDATE_AUB_SIZE );

	return _validate_end();
}

bool _validate_update_buffer( const _buffer_t * buf, const void * data, int size )
{
	XE_ASSERT( buf && data );
	_validate_begin();
	_validate( buf->cmn.usage != USAGE_IMMUTABLE, _VALIDATE_UPDATEBUF_USAGE );
	_validate( buf->cmn.size >= size, _VALIDATE_UPDATEBUF_SIZE );
	_validate( buf->cmn.update_frame_index != _sg.frame_index, _VALIDATE_UPDATEBUF_ONCE );
	_validate( buf->cmn.append_frame_index != _sg.frame_index, _VALIDATE_UPDATEBUF_APPEND );
	return _validate_end();
}

bool _validate_append_buffer( const _buffer_t * buf, const void * data, int size )
{
	XE_ASSERT( buf && data );
	_validate_begin();
	_validate( buf->cmn.usage != USAGE_IMMUTABLE, _VALIDATE_APPENDBUF_USAGE );
	_validate( buf->cmn.size >= ( buf->cmn.append_pos + size ), _VALIDATE_APPENDBUF_SIZE );
	_validate( buf->cmn.update_frame_index != _sg.frame_index, _VALIDATE_APPENDBUF_UPDATE );
	return _validate_end();
}

bool _validate_update_image( const _image_t * img, const ImageContent * data )
{
	XE_ASSERT( img && data );
	_validate_begin();
	_validate( img->cmn.usage != USAGE_IMMUTABLE, _VALIDATE_UPDIMG_USAGE );
	_validate( img->cmn.upd_frame_index != _sg.frame_index, _VALIDATE_UPDIMG_ONCE );
	_validate( !_is_compressed_pixel_format( img->cmn.pixel_format ), _VALIDATE_UPDIMG_COMPRESSED );
	const int num_faces = ( img->cmn.type == IMAGETYPE_CUBE ) ? 6 : 1;
	const int num_mips = img->cmn.num_mipmaps;
	for( int face_index = 0; face_index < num_faces; face_index++ )
	{
		for( int mip_index = 0; mip_index < num_mips; mip_index++ )
		{
			_validate( 0 != data->subimage[face_index][mip_index].ptr, _VALIDATE_UPDIMG_NOTENOUGHDATA );
			const int mip_width = _max( img->cmn.width >> mip_index, 1 );
			const int mip_height = _max( img->cmn.height >> mip_index, 1 );
			const int bytes_per_slice = _surface_pitch( img->cmn.pixel_format, mip_width, mip_height );
			const int expected_size = bytes_per_slice * img->cmn.depth;
			_validate( data->subimage[face_index][mip_index].size <= expected_size, _VALIDATE_UPDIMG_SIZE );
		}
	}
	return _validate_end();
}



BufferDesc _Buffer_desc_defaults( const BufferDesc * desc )
{
	BufferDesc def = *desc;
	def.type = _def( def.type, BUFFERTYPE_VERTEXBUFFER );
	def.usage = _def( def.usage, USAGE_IMMUTABLE );
	return def;
}

ImageDesc _image_desc_defaults( const ImageDesc * desc )
{
	ImageDesc def = *desc;
	def.type = _def( def.type, IMAGETYPE_2D );
	def.depth = _def( def.depth, 1 );
	def.num_mipmaps = _def( def.num_mipmaps, 1 );
	def.usage = _def( def.usage, USAGE_IMMUTABLE );
	if( desc->render_target )
	{
		def.pixel_format = _def( def.pixel_format, _default_rendertarget_colorformat() );
	}
	else
	{
		def.pixel_format = _def( def.pixel_format, PIXELFORMAT_RGBA8 );
	}
	def.sample_count = _def( def.sample_count, 1 );
	def.min_filter = _def( def.min_filter, FILTER_NEAREST );
	def.mag_filter = _def( def.mag_filter, FILTER_NEAREST );
	def.wrap_u = _def( def.wrap_u, WRAP_REPEAT );
	def.wrap_v = _def( def.wrap_v, WRAP_REPEAT );
	def.wrap_w = _def( def.wrap_w, WRAP_REPEAT );
	def.border_color = _def( def.border_color, BORDERCOLOR_OPAQUE_BLACK );
	def.max_anisotropy = _def( def.max_anisotropy, 1 );
	def.max_lod = _def_flt( def.max_lod, FLT_MAX );
	return def;
}

ShaderDesc _shader_desc_defaults( const ShaderDesc * desc )
{
	ShaderDesc def = *desc;
#if defined(SOKOL_METAL)
	def.vs.entry = _def( def.vs.entry, "_main" );
	def.fs.entry = _def( def.fs.entry, "_main" );
#else
	def.vs.entry = _def( def.vs.entry, "main" );
	def.fs.entry = _def( def.fs.entry, "main" );
#endif
	for( int stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
	{
		ShaderStageDesc * stage_desc = ( stage_index == SHADERSTAGE_VS ) ? &def.vs : &def.fs;
		for( int ub_index = 0; ub_index < MAX_SHADERSTAGE_UBS; ub_index++ )
		{
			ShaderUniformBlockDesc * ub_desc = &stage_desc->uniform_blocks[ub_index];
			if( 0 == ub_desc->size )
			{
				break;
			}
			for( int u_index = 0; u_index < MAX_UB_MEMBERS; u_index++ )
			{
				ShaderUniformDesc * u_desc = &ub_desc->uniforms[u_index];
				if( u_desc->type == UNIFORMTYPE_INVALID )
				{
					break;
				}
				u_desc->array_count = _def( u_desc->array_count, 1 );
			}
		}
	}
	return def;
}

PipelineDesc _pipeline_desc_defaults( const PipelineDesc * desc )
{
	PipelineDesc def = *desc;

	def.primitive_type = _def( def.primitive_type, PRIMITIVETYPE_TRIANGLES );
	def.index_type = _def( def.index_type, INDEXTYPE_NONE );

	def.depth_stencil.stencil_front.fail_op = _def( def.depth_stencil.stencil_front.fail_op, STENCILOP_KEEP );
	def.depth_stencil.stencil_front.depth_fail_op = _def( def.depth_stencil.stencil_front.depth_fail_op, STENCILOP_KEEP );
	def.depth_stencil.stencil_front.pass_op = _def( def.depth_stencil.stencil_front.pass_op, STENCILOP_KEEP );
	def.depth_stencil.stencil_front.compare_func = _def( def.depth_stencil.stencil_front.compare_func, COMPAREFUNC_ALWAYS );
	def.depth_stencil.stencil_back.fail_op = _def( def.depth_stencil.stencil_back.fail_op, STENCILOP_KEEP );
	def.depth_stencil.stencil_back.depth_fail_op = _def( def.depth_stencil.stencil_back.depth_fail_op, STENCILOP_KEEP );
	def.depth_stencil.stencil_back.pass_op = _def( def.depth_stencil.stencil_back.pass_op, STENCILOP_KEEP );
	def.depth_stencil.stencil_back.compare_func = _def( def.depth_stencil.stencil_back.compare_func, COMPAREFUNC_ALWAYS );
	def.depth_stencil.depth_compare_func = _def( def.depth_stencil.depth_compare_func, COMPAREFUNC_ALWAYS );

	def.blend.src_factor_rgb = _def( def.blend.src_factor_rgb, BLENDFACTOR_ONE );
	def.blend.dst_factor_rgb = _def( def.blend.dst_factor_rgb, BLENDFACTOR_ZERO );
	def.blend.op_rgb = _def( def.blend.op_rgb, BLENDOP_ADD );
	def.blend.src_factor_alpha = _def( def.blend.src_factor_alpha, BLENDFACTOR_ONE );
	def.blend.dst_factor_alpha = _def( def.blend.dst_factor_alpha, BLENDFACTOR_ZERO );
	def.blend.op_alpha = _def( def.blend.op_alpha, BLENDOP_ADD );
	if( def.blend.color_write_mask == COLORMASK_NONE )
	{
		def.blend.color_write_mask = 0;
	}
	else
	{
		def.blend.color_write_mask = (uint8_t )_def( (ColorMask )def.blend.color_write_mask, COLORMASK_RGBA );
	}
	def.blend.color_attachment_count = _def( def.blend.color_attachment_count, 1 );
	def.blend.color_format = _def( def.blend.color_format, _default_rendertarget_colorformat() );
	def.blend.depth_format = _def( def.blend.depth_format, _default_rendertarget_depthformat() );

	def.rasterizer.cull_mode = _def( def.rasterizer.cull_mode, CULLMODE_NONE );
	def.rasterizer.face_winding = _def( def.rasterizer.face_winding, FACEWINDING_CW );
	def.rasterizer.sample_count = _def( def.rasterizer.sample_count, 1 );

	for( int attr_index = 0; attr_index < MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		VertexAttrDesc * a_desc = &def.layout.attrs[attr_index];
		if( a_desc->format == VERTEXFORMAT_INVALID )
		{
			break;
		}
		XE_ASSERT( ( a_desc->buffer_index >= 0 ) && ( a_desc->buffer_index < MAX_SHADERSTAGE_BUFFERS ) );
		BufferLayoutDesc * b_desc = &def.layout.buffers[a_desc->buffer_index];
		b_desc->step_func = _def( b_desc->step_func, VERTEXSTEP_PER_VERTEX );
		b_desc->step_rate = _def( b_desc->step_rate, 1 );
	}

	/* resolve vertex layout strides and offsets */
	int auto_offset[MAX_SHADERSTAGE_BUFFERS];
	memset( auto_offset, 0, sizeof( auto_offset ) );
	bool use_auto_offset = true;
	for( int attr_index = 0; attr_index < MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		/* to use computed offsets, *all* attr offsets must be 0 */
		if( def.layout.attrs[attr_index].offset != 0 )
		{
			use_auto_offset = false;
		}
	}
	for( int attr_index = 0; attr_index < MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		VertexAttrDesc * a_desc = &def.layout.attrs[attr_index];
		if( a_desc->format == VERTEXFORMAT_INVALID )
		{
			break;
		}
		XE_ASSERT( ( a_desc->buffer_index >= 0 ) && ( a_desc->buffer_index < MAX_SHADERSTAGE_BUFFERS ) );
		if( use_auto_offset )
		{
			a_desc->offset = auto_offset[a_desc->buffer_index];
		}
		auto_offset[a_desc->buffer_index] += _vertexformat_bytesize( a_desc->format );
	}
	/* compute vertex strides if needed */
	for( int buf_index = 0; buf_index < MAX_SHADERSTAGE_BUFFERS; buf_index++ )
	{
		BufferLayoutDesc * l_desc = &def.layout.buffers[buf_index];
		if( l_desc->stride == 0 )
		{
			l_desc->stride = auto_offset[buf_index];
		}
	}

	return def;
}

PassDesc _pass_desc_defaults( const PassDesc * desc )
{
	/* FIXME: no values to replace in PassDesc? */
	PassDesc def = *desc;
	return def;
}



BufferHandle _alloc_buffer( void )
{
	BufferHandle res;
	int slot_index = _pool_alloc_index( &_sg.pools.buffer_pool );
	if( INVALID_SLOT_INDEX != slot_index )
	{
		res = _slot_alloc( &_sg.pools.buffer_pool, &_sg.pools.buffers[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::BufferHandle::Invalid;
	}
	return res;
}

ImageHandle _alloc_image( void )
{
	ImageHandle res;
	int slot_index = _pool_alloc_index( &_sg.pools.image_pool );
	if( INVALID_SLOT_INDEX != slot_index )
	{
		res = _slot_alloc( &_sg.pools.image_pool, &_sg.pools.images[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::ImageHandle::Invalid;
	}
	return res;
}

ShaderHandle _alloc_shader( void )
{
	ShaderHandle res;
	int slot_index = _pool_alloc_index( &_sg.pools.shader_pool );
	if( INVALID_SLOT_INDEX != slot_index )
	{
		res = _slot_alloc( &_sg.pools.shader_pool, &_sg.pools.shaders[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::ShaderHandle::Invalid;
	}
	return res;
}

PipelineHandle _alloc_pipeline( void )
{
	PipelineHandle res;
	int slot_index = _pool_alloc_index( &_sg.pools.pipeline_pool );
	if( INVALID_SLOT_INDEX != slot_index )
	{
		res = _slot_alloc( &_sg.pools.pipeline_pool, &_sg.pools.pipelines[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::PipelineHandle::Invalid;
	}
	return res;
}

PassHandle _alloc_pass( void )
{
	PassHandle res;
	int slot_index = _pool_alloc_index( &_sg.pools.pass_pool );
	if( INVALID_SLOT_INDEX != slot_index )
	{
		res = _slot_alloc( &_sg.pools.pass_pool, &_sg.pools.passes[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::PassHandle::Invalid;
	}
	return res;
}

void _init_buffer( BufferHandle buf_id, const BufferDesc * desc )
{
	XE_ASSERT( buf_id && desc );
	_buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	XE_ASSERT( buf && buf->slot.state == RESOURCESTATE_ALLOC );
	buf->slot.ctx_id = _sg.active_context.GetValue();
	if( _validate_buffer_desc( desc ) )
	{
		buf->slot.state = _create_buffer( buf, desc );
	}
	else
	{
		buf->slot.state = RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( buf->slot.state == RESOURCESTATE_VALID ) || ( buf->slot.state == RESOURCESTATE_FAILED ) );
}

void _init_image( ImageHandle img_id, const ImageDesc * desc )
{
	XE_ASSERT( img_id && desc );
	_image_t * img = _lookup_image( &_sg.pools, img_id.GetValue() );
	XE_ASSERT( img && img->slot.state == RESOURCESTATE_ALLOC );
	img->slot.ctx_id = _sg.active_context.GetValue();
	if( _validate_image_desc( desc ) )
	{
		img->slot.state = _create_image( img, desc );
	}
	else
	{
		img->slot.state = RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( img->slot.state == RESOURCESTATE_VALID ) || ( img->slot.state == RESOURCESTATE_FAILED ) );
}

void _init_shader( ShaderHandle shd_id, const ShaderDesc * desc )
{
	XE_ASSERT( shd_id && desc );
	_shader_t * shd = _lookup_shader( &_sg.pools, shd_id.GetValue() );
	XE_ASSERT( shd && shd->slot.state == RESOURCESTATE_ALLOC );
	shd->slot.ctx_id = _sg.active_context.GetValue();
	if( _validate_shader_desc( desc ) )
	{
		shd->slot.state = _create_shader( shd, desc );
	}
	else
	{
		shd->slot.state = RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( shd->slot.state == RESOURCESTATE_VALID ) || ( shd->slot.state == RESOURCESTATE_FAILED ) );
}

void _init_pipeline( PipelineHandle pip_id, const PipelineDesc * desc )
{
	XE_ASSERT( pip_id && desc );
	_pipeline_t * pip = _lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	XE_ASSERT( pip && pip->slot.state == RESOURCESTATE_ALLOC );
	pip->slot.ctx_id = _sg.active_context.GetValue();
	if( _validate_pipeline_desc( desc ) )
	{
		_shader_t * shd = _lookup_shader( &_sg.pools, desc->shader.GetValue() );
		XE_ASSERT( shd && shd->slot.state == RESOURCESTATE_VALID );
		pip->slot.state = _create_pipeline( pip, shd, desc );
	}
	else
	{
		pip->slot.state = RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( pip->slot.state == RESOURCESTATE_VALID ) || ( pip->slot.state == RESOURCESTATE_FAILED ) );
}

void _init_pass( PassHandle pass_id, const PassDesc * desc )
{
	XE_ASSERT( pass_id && desc );
	_pass_t * pass = _lookup_pass( &_sg.pools, pass_id.GetValue() );
	XE_ASSERT( pass && pass->slot.state == RESOURCESTATE_ALLOC );
	pass->slot.ctx_id = _sg.active_context.GetValue();
	if( _validate_pass_desc( desc ) )
	{
		/* lookup pass attachment image pointers */
		_image_t * att_imgs[MAX_COLOR_ATTACHMENTS + 1];
		for( int i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			if( desc->color_attachments[i].image.GetValue() )
			{
				att_imgs[i] = _lookup_image( &_sg.pools, desc->color_attachments[i].image.GetValue() );
				XE_ASSERT( att_imgs[i] && att_imgs[i]->slot.state == RESOURCESTATE_VALID );
			}
			else
			{
				att_imgs[i] = 0;
			}
		}
		const int ds_att_index = MAX_COLOR_ATTACHMENTS;
		if( desc->depth_stencil_attachment.image.GetValue() )
		{
			att_imgs[ds_att_index] = _lookup_image( &_sg.pools, desc->depth_stencil_attachment.image.GetValue() );
			XE_ASSERT( att_imgs[ds_att_index] && att_imgs[ds_att_index]->slot.state == RESOURCESTATE_VALID );
		}
		else
		{
			att_imgs[ds_att_index] = 0;
		}
		pass->slot.state = _create_pass( pass, att_imgs, desc );
	}
	else
	{
		pass->slot.state = RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( pass->slot.state == RESOURCESTATE_VALID ) || ( pass->slot.state == RESOURCESTATE_FAILED ) );
}






void Gfx::Setup( const GfxDesc * desc )
{
	XE_ASSERT( desc );
	XE_ASSERT( ( desc->_start_canary == 0 ) && ( desc->_end_canary == 0 ) );
	memset( &_sg, 0, sizeof( _sg ) );
	_sg.desc = *desc;

	/* replace zero-init items with their default values */
	_sg.desc.buffer_pool_size = _def( _sg.desc.buffer_pool_size, _DEFAULT_BUFFER_POOL_SIZE );
	_sg.desc.image_pool_size = _def( _sg.desc.image_pool_size, _DEFAULT_IMAGE_POOL_SIZE );
	_sg.desc.shader_pool_size = _def( _sg.desc.shader_pool_size, _DEFAULT_SHADER_POOL_SIZE );
	_sg.desc.pipeline_pool_size = _def( _sg.desc.pipeline_pool_size, _DEFAULT_PIPELINE_POOL_SIZE );
	_sg.desc.pass_pool_size = _def( _sg.desc.pass_pool_size, _DEFAULT_PASS_POOL_SIZE );
	_sg.desc.context_pool_size = _def( _sg.desc.context_pool_size, _DEFAULT_CONTEXT_POOL_SIZE );
	_sg.desc.mtl_global_uniform_buffer_size = _def( _sg.desc.mtl_global_uniform_buffer_size, _MTL_DEFAULT_UB_SIZE );
	_sg.desc.mtl_sampler_cache_size = _def( _sg.desc.mtl_sampler_cache_size, _MTL_DEFAULT_SAMPLER_CACHE_CAPACITY );

	_setup_pools( &_sg.pools, &_sg.desc );
	_sg.frame_index = 1;
	_setup_backend( &_sg.desc );
	_sg.valid = true;
	SetupContext();
}

void Gfx::ShutDown( void )
{
	if( _sg.active_context )
	{
		_context_t * ctx = _lookup_context( &_sg.pools, _sg.active_context.GetValue() );
		if( ctx )
		{
			_destroy_all_resources( &_sg.pools, _sg.active_context.GetValue() );
			_destroy_context( ctx );
		}
	}
	_discard_backend();
	_discard_pools( &_sg.pools );
	_sg.valid = false;
}

bool Gfx::IsValid( void )
{
	return _sg.valid;
}

void Gfx::ResetStateCache( void )
{
	XE_ASSERT( _sg.valid );
	_reset_state_cache();
	_TRACE_NOARGS( ResetStateCache );
}

GfxTraceHooks * Gfx::InstallTraceHooks( GfxTraceHooks * trace_hooks )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( trace_hooks );
	GfxTraceHooks * old_hooks = _sg.hooks;
	_sg.hooks = trace_hooks;
	return old_hooks;
}

void Gfx::PushDebugGroup( const XE::String & name )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( name );
	_TRACE_ARGS( PushDebugGroup, name );
}

void Gfx::PopDebugGroup( void )
{
	XE_ASSERT( _sg.valid );
	_TRACE_NOARGS( PopDebugGroup );
}

BufferHandle Gfx::MakeBuffer( const BufferDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	BufferDesc desc_def = _Buffer_desc_defaults( desc );
	BufferHandle buf_id = _alloc_buffer();
	if( buf_id )
	{
		_init_buffer( buf_id, &desc_def );
	}
	else
	{
		puts( "buffer pool exhausted!" );
		_TRACE_NOARGS( ErrBufferPoolExhausted );
	}
	_TRACE_ARGS( MakeBuffer, &desc_def, buf_id );
	return buf_id;
}

ImageHandle Gfx::MakeImage( const ImageDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	ImageDesc desc_def = _image_desc_defaults( desc );
	ImageHandle img_id = _alloc_image();
	if( img_id )
	{
		_init_image( img_id, &desc_def );
	}
	else
	{
		puts( "image pool exhausted!" );
		_TRACE_NOARGS( ErrImagePoolExhausted );
	}
	_TRACE_ARGS( MakeImage, &desc_def, img_id );
	return img_id;
}

ShaderHandle Gfx::MakeShader( const ShaderDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	ShaderDesc desc_def = _shader_desc_defaults( desc );
	ShaderHandle shd_id = _alloc_shader();
	if( shd_id )
	{
		_init_shader( shd_id, &desc_def );
	}
	else
	{
		puts( "shader pool exhausted!" );
		_TRACE_NOARGS( ErrShaderPoolExhausted );
	}
	_TRACE_ARGS( MakeShader, &desc_def, shd_id );
	return shd_id;
}

PipelineHandle Gfx::MakePipeline( const PipelineDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	PipelineDesc desc_def = _pipeline_desc_defaults( desc );
	PipelineHandle pip_id = _alloc_pipeline();
	if( pip_id )
	{
		_init_pipeline( pip_id, &desc_def );
	}
	else
	{
		puts( "pipeline pool exhausted!" );
		_TRACE_NOARGS( ErrPipelinePoolExhausted );
	}
	_TRACE_ARGS( MakePipeline, &desc_def, pip_id );
	return pip_id;
}

PassHandle Gfx::MakePass( const PassDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	PassDesc desc_def = _pass_desc_defaults( desc );
	PassHandle pass_id = _alloc_pass();
	if( pass_id )
	{
		_init_pass( pass_id, &desc_def );
	}
	else
	{
		puts( "pass pool exhausted!" );
		_TRACE_NOARGS( ErrPassPoolExhausted );
	}
	_TRACE_ARGS( MakePass, &desc_def, pass_id );
	return pass_id;
}

void Gfx::DestroyBuffer( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	_TRACE_ARGS( DestroyBuffer, buf_id );
	_buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	if( buf )
	{
		if( buf->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_destroy_buffer( buf );
			_reset_buffer( buf );
			_pool_free_index( &_sg.pools.buffer_pool, _slot_index( buf_id.GetValue() ) );
		}
		else
		{
			puts( "destroy_buffer: active context mismatch (must be same as for creation)" );
			_TRACE_NOARGS( ErrContextMismatch );
		}
	}
}

void Gfx::DestroyImage( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	_TRACE_ARGS( DestroyImage, img_id );
	_image_t * img = _lookup_image( &_sg.pools, img_id.GetValue() );
	if( img )
	{
		if( img->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_destroy_image( img );
			_reset_image( img );
			_pool_free_index( &_sg.pools.image_pool, _slot_index( img_id.GetValue() ) );
		}
		else
		{
			puts( "destroy_image: active context mismatch (must be same as for creation)" );
			_TRACE_NOARGS( ErrContextMismatch );
		}
	}
}

void Gfx::DestroyShader( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	_TRACE_ARGS( DestroyShader, shd_id );
	_shader_t * shd = _lookup_shader( &_sg.pools, shd_id.GetValue() );
	if( shd )
	{
		if( shd->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_destroy_shader( shd );
			_reset_shader( shd );
			_pool_free_index( &_sg.pools.shader_pool, _slot_index( shd_id.GetValue() ) );
		}
		else
		{
			puts( "destroy_shader: active context mismatch (must be same as for creation)" );
			_TRACE_NOARGS( ErrContextMismatch );
		}
	}
}

void Gfx::DestroyPipeline( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	_TRACE_ARGS( DestroyPipeline, pip_id );
	_pipeline_t * pip = _lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	if( pip )
	{
		if( pip->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_destroy_pipeline( pip );
			_reset_pipeline( pip );
			_pool_free_index( &_sg.pools.pipeline_pool, _slot_index( pip_id.GetValue() ) );
		}
		else
		{
			puts( "destroy_pipeline: active context mismatch (must be same as for creation)" );
			_TRACE_NOARGS( ErrContextMismatch );
		}
	}
}

void Gfx::DestroyPass( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	_TRACE_ARGS( DestroyPass, pass_id );
	_pass_t * pass = _lookup_pass( &_sg.pools, pass_id.GetValue() );
	if( pass )
	{
		if( pass->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_destroy_pass( pass );
			_reset_pass( pass );
			_pool_free_index( &_sg.pools.pass_pool, _slot_index( pass_id.GetValue() ) );
		}
		else
		{
			puts( "destroy_pass: active context mismatch (must be same as for creation)" );
			_TRACE_NOARGS( ErrContextMismatch );
		}
	}
}

void Gfx::UpdateBuffer( BufferHandle buf_id, const void * data, int num_bytes )
{
	XE_ASSERT( _sg.valid );
	_buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	if( ( num_bytes > 0 ) && buf && ( buf->slot.state == RESOURCESTATE_VALID ) )
	{
		if( _validate_update_buffer( buf, data, num_bytes ) )
		{
			XE_ASSERT( num_bytes <= buf->cmn.size );
			/* only one update allowed per buffer and frame */
			XE_ASSERT( buf->cmn.update_frame_index != _sg.frame_index );
			/* update and append on same buffer in same frame not allowed */
			XE_ASSERT( buf->cmn.append_frame_index != _sg.frame_index );
			_update_buffer( buf, data, num_bytes );
			buf->cmn.update_frame_index = _sg.frame_index;
		}
	}
	_TRACE_ARGS( UpdateBuffer, buf_id, data, num_bytes );
}

void Gfx::UpdateImage( ImageHandle img_id, const ImageContent * data )
{
	XE_ASSERT( _sg.valid );
	_image_t * img = _lookup_image( &_sg.pools, img_id.GetValue() );
	if( img && img->slot.state == RESOURCESTATE_VALID )
	{
		if( _validate_update_image( img, data ) )
		{
			XE_ASSERT( img->cmn.upd_frame_index != _sg.frame_index );
			_update_image( img, data );
			img->cmn.upd_frame_index = _sg.frame_index;
		}
	}
	_TRACE_ARGS( UpdateImage, img_id, data );
}

int Gfx::AppendBuffer( BufferHandle buf_id, const void * data, int num_bytes )
{
	XE_ASSERT( _sg.valid );
	_buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	int result;
	if( buf )
	{
		/* rewind append cursor in a new frame */
		if( buf->cmn.append_frame_index != _sg.frame_index )
		{
			buf->cmn.append_pos = 0;
			buf->cmn.append_overflow = false;
		}
		if( ( buf->cmn.append_pos + num_bytes ) > buf->cmn.size )
		{
			buf->cmn.append_overflow = true;
		}
		const int start_pos = buf->cmn.append_pos;
		if( buf->slot.state == RESOURCESTATE_VALID )
		{
			if( _validate_append_buffer( buf, data, num_bytes ) )
			{
				if( !buf->cmn.append_overflow && ( num_bytes > 0 ) )
				{
					/* update and append on same buffer in same frame not allowed */
					XE_ASSERT( buf->cmn.update_frame_index != _sg.frame_index );
					_append_buffer( buf, data, num_bytes, buf->cmn.append_frame_index != _sg.frame_index );
					buf->cmn.append_pos += num_bytes;
					buf->cmn.append_frame_index = _sg.frame_index;
				}
			}
		}
		result = start_pos;
	}
	else
	{
		/* FIXME: should we return -1 here? */
		result = 0;
	}
	_TRACE_ARGS( AppendBuffer, buf_id, data, num_bytes, result );
	return result;
}

bool Gfx::QueryBufferOverflow( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	_buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	bool result = buf ? buf->cmn.append_overflow : false;
	return result;
}

void Gfx::BeginDefaultPass( const PassAction * pass_action, int width, int height )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pass_action );
	XE_ASSERT( ( pass_action->_start_canary == 0 ) && ( pass_action->_end_canary == 0 ) );
	PassAction pa;
	_resolve_default_pass_action( pass_action, &pa );
	_sg.cur_pass = XE::PassHandle::Invalid;
	_sg.pass_valid = true;
	_begin_pass( 0, &pa, width, height );
	_TRACE_ARGS( BeginDefaultPass, pass_action, width, height );
}

void Gfx::BeginPass( PassHandle pass_id, const PassAction * pass_action )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pass_action );
	XE_ASSERT( ( pass_action->_start_canary == 0 ) && ( pass_action->_end_canary == 0 ) );
	_sg.cur_pass = pass_id;
	_pass_t * pass = _lookup_pass( &_sg.pools, pass_id.GetValue() );
	if( pass && _validate_begin_pass( pass ) )
	{
		_sg.pass_valid = true;
		PassAction pa;
		_resolve_default_pass_action( pass_action, &pa );
		const _image_t * img = _pass_color_image( pass, 0 );
		const int w = img->cmn.width;
		const int h = img->cmn.height;
		_begin_pass( pass, &pa, w, h );
		_TRACE_ARGS( BeginPass, pass_id, pass_action );
	}
	else
	{
		_sg.pass_valid = false;
		_TRACE_NOARGS( ErrPassInvalid );
	}
}

void Gfx::ApplyViewport( int x, int y, int width, int height, bool origin_top_left )
{
	XE_ASSERT( _sg.valid );
	if( !_sg.pass_valid )
	{
		_TRACE_NOARGS( ErrPassInvalid );
		return;
	}
	_apply_viewport( x, y, width, height, origin_top_left );
	_TRACE_ARGS( ApplyViewport, x, y, width, height, origin_top_left );
}

void Gfx::ApplyScissorRect( int x, int y, int width, int height, bool origin_top_left )
{
	XE_ASSERT( _sg.valid );
	if( !_sg.pass_valid )
	{
		_TRACE_NOARGS( ErrPassInvalid );
		return;
	}
	_apply_scissor_rect( x, y, width, height, origin_top_left );
	_TRACE_ARGS( ApplyScissorRect, x, y, width, height, origin_top_left );
}

void Gfx::ApplyPipeline( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	_sg.bindings_valid = false;
	if( !_validate_apply_pipeline( pip_id ) )
	{
		_sg.next_draw_valid = false;
		_TRACE_NOARGS( ErrDrawInvalid );
		return;
	}
	if( !_sg.pass_valid )
	{
		_TRACE_NOARGS( ErrPassInvalid );
		return;
	}
	_sg.cur_pipeline = pip_id;
	_pipeline_t * pip = _lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	XE_ASSERT( pip );
	_sg.next_draw_valid = ( RESOURCESTATE_VALID == pip->slot.state );
	XE_ASSERT( pip->shader && ( pip->shader->slot.id == pip->cmn.shader_id.GetValue() ) );
	_apply_pipeline( pip );
	_TRACE_ARGS( ApplyPipeline, pip_id );
}

void Gfx::ApplyBindings( const Bindings * bindings )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( bindings );
	XE_ASSERT( ( bindings->_start_canary == 0 ) && ( bindings->_end_canary == 0 ) );
	if( !_validate_apply_bindings( bindings ) )
	{
		_sg.next_draw_valid = false;
		_TRACE_NOARGS( ErrDrawInvalid );
		return;
	}
	_sg.bindings_valid = true;

	_pipeline_t * pip = _lookup_pipeline( &_sg.pools, _sg.cur_pipeline.GetValue() );
	XE_ASSERT( pip );

	_buffer_t * vbs[MAX_SHADERSTAGE_BUFFERS] = { 0 };
	int num_vbs = 0;
	for( int i = 0; i < MAX_SHADERSTAGE_BUFFERS; i++, num_vbs++ )
	{
		if( bindings->vertex_buffers[i].GetValue() )
		{
			vbs[i] = _lookup_buffer( &_sg.pools, bindings->vertex_buffers[i].GetValue() );
			XE_ASSERT( vbs[i] );
			_sg.next_draw_valid &= ( RESOURCESTATE_VALID == vbs[i]->slot.state );
			_sg.next_draw_valid &= !vbs[i]->cmn.append_overflow;
		}
		else
		{
			break;
		}
	}

	_buffer_t * ib = 0;
	if( bindings->index_buffer.GetValue() )
	{
		ib = _lookup_buffer( &_sg.pools, bindings->index_buffer.GetValue() );
		XE_ASSERT( ib );
		_sg.next_draw_valid &= ( RESOURCESTATE_VALID == ib->slot.state );
		_sg.next_draw_valid &= !ib->cmn.append_overflow;
	}

	_image_t * vs_imgs[MAX_SHADERSTAGE_IMAGES] = { 0 };
	int num_vs_imgs = 0;
	for( int i = 0; i < MAX_SHADERSTAGE_IMAGES; i++, num_vs_imgs++ )
	{
		if( bindings->vs_images[i].GetValue() )
		{
			vs_imgs[i] = _lookup_image( &_sg.pools, bindings->vs_images[i].GetValue() );
			XE_ASSERT( vs_imgs[i] );
			_sg.next_draw_valid &= ( RESOURCESTATE_VALID == vs_imgs[i]->slot.state );
		}
		else
		{
			break;
		}
	}

	_image_t * fs_imgs[MAX_SHADERSTAGE_IMAGES] = { 0 };
	int num_fs_imgs = 0;
	for( int i = 0; i < MAX_SHADERSTAGE_IMAGES; i++, num_fs_imgs++ )
	{
		if( bindings->fs_images[i].GetValue() )
		{
			fs_imgs[i] = _lookup_image( &_sg.pools, bindings->fs_images[i].GetValue() );
			XE_ASSERT( fs_imgs[i] );
			_sg.next_draw_valid &= ( RESOURCESTATE_VALID == fs_imgs[i]->slot.state );
		}
		else
		{
			break;
		}
	}
	if( _sg.next_draw_valid )
	{
		const int * vb_offsets = bindings->vertex_buffer_offsets;
		int ib_offset = bindings->index_buffer_offset;
		_apply_bindings( pip, vbs, vb_offsets, num_vbs, ib, ib_offset, vs_imgs, num_vs_imgs, fs_imgs, num_fs_imgs );
		_TRACE_ARGS( ApplyBindings, bindings );
	}
	else
	{
		_TRACE_NOARGS( ErrDrawInvalid );
	}
}

void Gfx::ApplyUniforms( ShaderStage stage, int ub_index, const void * data, int num_bytes )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( ( stage == SHADERSTAGE_VS ) || ( stage == SHADERSTAGE_FS ) );
	XE_ASSERT( ( ub_index >= 0 ) && ( ub_index < MAX_SHADERSTAGE_UBS ) );
	XE_ASSERT( data && ( num_bytes > 0 ) );
	if( !_validate_apply_uniforms( stage, ub_index, data, num_bytes ) )
	{
		_sg.next_draw_valid = false;
		_TRACE_NOARGS( ErrDrawInvalid );
		return;
	}
	if( !_sg.pass_valid )
	{
		_TRACE_NOARGS( ErrPassInvalid );
		return;
	}
	if( !_sg.next_draw_valid )
	{
		_TRACE_NOARGS( ErrDrawInvalid );
	}
	_apply_uniforms( stage, ub_index, data, num_bytes );
	_TRACE_ARGS( ApplyUniforms, stage, ub_index, data, num_bytes );
}

void Gfx::Draw( int base_element, int num_elements, int num_instances )
{
	XE_ASSERT( _sg.valid );
#if defined(SOKOL_DEBUG)
	if( !_sg.bindings_valid )
	{
		puts( "attempting to draw without resource bindings" );
	}
#endif
	if( !_sg.pass_valid )
	{
		_TRACE_NOARGS( ErrPassInvalid );
		return;
	}
	if( !_sg.next_draw_valid )
	{
		_TRACE_NOARGS( ErrDrawInvalid );
		return;
	}
	if( !_sg.bindings_valid )
	{
		_TRACE_NOARGS( ErrBindingsInvalid );
		return;
	}
	_draw( base_element, num_elements, num_instances );
	_TRACE_ARGS( Draw, base_element, num_elements, num_instances );
}

void Gfx::EndPass( void )
{
	XE_ASSERT( _sg.valid );
	if( !_sg.pass_valid )
	{
		_TRACE_NOARGS( ErrPassInvalid );
		return;
	}
	_end_pass();
	_sg.cur_pass = XE::PassHandle::Invalid;
	_sg.cur_pipeline = XE::PipelineHandle::Invalid;
	_sg.pass_valid = false;
	_TRACE_NOARGS( EndPass );
}

void Gfx::Commit( void )
{
	XE_ASSERT( _sg.valid );
	_commit();
	_TRACE_NOARGS( Commit );
	_sg.frame_index++;
}

GfxDesc Gfx::QueryDesc( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.desc;
}

Backend Gfx::QueryBackend( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.backend;
}

Features Gfx::QueryFeatures( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.features;
}

Limits Gfx::QueryLimits( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.limits;
}

PixelformatInfo Gfx::QueryPixelformat( PixelFormat fmt )
{
	XE_ASSERT( _sg.valid );
	int fmt_index = (int )fmt;
	XE_ASSERT( ( fmt_index > PIXELFORMAT_NONE ) && ( fmt_index < _PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index];
}

ResourceState Gfx::QueryBufferState( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	_buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	ResourceState res = buf ? buf->slot.state : RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::QueryImageState( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	_image_t * img = _lookup_image( &_sg.pools, img_id.GetValue() );
	ResourceState res = img ? img->slot.state : RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::QueryShaderState( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	_shader_t * shd = _lookup_shader( &_sg.pools, shd_id.GetValue() );
	ResourceState res = shd ? shd->slot.state : RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::QueryPipelineState( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	_pipeline_t * pip = _lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	ResourceState res = pip ? pip->slot.state : RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::QueryPassState( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	_pass_t * pass = _lookup_pass( &_sg.pools, pass_id.GetValue() );
	ResourceState res = pass ? pass->slot.state : RESOURCESTATE_INVALID;
	return res;
}

BufferInfo Gfx::QueryBufferInfo( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	BufferInfo info;
	memset( &info, 0, sizeof( info ) );
	const _buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	if( buf )
	{
		info.slot.state = buf->slot.state;
		info.slot.res_id = buf->slot.id;
		info.slot.ctx_id = buf->slot.ctx_id;
		info.update_frame_index = buf->cmn.update_frame_index;
		info.append_frame_index = buf->cmn.append_frame_index;
		info.append_pos = buf->cmn.append_pos;
		info.append_overflow = buf->cmn.append_overflow;
	#if defined(SOKOL_D3D11)
		info.num_slots = 1;
		info.active_slot = 0;
	#else
		info.num_slots = buf->cmn.num_slots;
		info.active_slot = buf->cmn.active_slot;
	#endif
	}
	return info;
}

ImageInfo Gfx::QueryImageInfo( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	ImageInfo info;
	memset( &info, 0, sizeof( info ) );
	const _image_t * img = _lookup_image( &_sg.pools, img_id.GetValue() );
	if( img )
	{
		info.slot.state = img->slot.state;
		info.slot.res_id = img->slot.id;
		info.slot.ctx_id = img->slot.ctx_id;
	#if defined(SOKOL_D3D11)
		info.num_slots = 1;
		info.active_slot = 0;
	#else
		info.num_slots = img->cmn.num_slots;
		info.active_slot = img->cmn.active_slot;
	#endif
	}
	return info;
}

ShaderInfo Gfx::QueryShaderInfo( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	ShaderInfo info;
	memset( &info, 0, sizeof( info ) );
	const _shader_t * shd = _lookup_shader( &_sg.pools, shd_id.GetValue() );
	if( shd )
	{
		info.slot.state = shd->slot.state;
		info.slot.res_id = shd->slot.id;
		info.slot.ctx_id = shd->slot.ctx_id;
	}
	return info;
}

PipelineInfo Gfx::QueryPipelineInfo( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	PipelineInfo info;
	memset( &info, 0, sizeof( info ) );
	const _pipeline_t * pip = _lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	if( pip )
	{
		info.slot.state = pip->slot.state;
		info.slot.res_id = pip->slot.id;
		info.slot.ctx_id = pip->slot.ctx_id;
	}
	return info;
}

PassInfo Gfx::QueryPassInfo( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	PassInfo info;
	memset( &info, 0, sizeof( info ) );
	const _pass_t * pass = _lookup_pass( &_sg.pools, pass_id.GetValue() );
	if( pass )
	{
		info.slot.state = pass->slot.state;
		info.slot.res_id = pass->slot.id;
		info.slot.ctx_id = pass->slot.ctx_id;
	}
	return info;
}

BufferDesc Gfx::QueryBufferDefaults( const BufferDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _Buffer_desc_defaults( desc );
}

ImageDesc Gfx::QueryImageDefaults( const ImageDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _image_desc_defaults( desc );
}

ShaderDesc Gfx::QueryShaderDefaults( const ShaderDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _shader_desc_defaults( desc );
}

PipelineDesc Gfx::QueryPipelineDefaults( const PipelineDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _pipeline_desc_defaults( desc );
}

PassDesc Gfx::QueryPassDefaults( const PassDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _pass_desc_defaults( desc );
}

BufferHandle Gfx::AllocBuffer( void )
{
	XE_ASSERT( _sg.valid );
	BufferHandle res = _alloc_buffer();
	_TRACE_ARGS( AllocBuffer, res );
	return res;
}

ImageHandle Gfx::AllocImage( void )
{
	XE_ASSERT( _sg.valid );
	ImageHandle res = _alloc_image();
	_TRACE_ARGS( AllocImage, res );
	return res;
}

ShaderHandle Gfx::AllocShader( void )
{
	XE_ASSERT( _sg.valid );
	ShaderHandle res = _alloc_shader();
	_TRACE_ARGS( AllocShader, res );
	return res;
}

PipelineHandle Gfx::AllocPipeline( void )
{
	XE_ASSERT( _sg.valid );
	PipelineHandle res = _alloc_pipeline();
	_TRACE_ARGS( AllocPipeline, res );
	return res;
}

PassHandle Gfx::AllocPass( void )
{
	XE_ASSERT( _sg.valid );
	PassHandle res = _alloc_pass();
	_TRACE_ARGS( AllocPass, res );
	return res;
}

void Gfx::InitBuffer( BufferHandle buf_id, const BufferDesc * desc )
{
	XE_ASSERT( _sg.valid );
	BufferDesc desc_def = _Buffer_desc_defaults( desc );
	_init_buffer( buf_id, &desc_def );
	_TRACE_ARGS( InitBuffer, buf_id, &desc_def );
}

void Gfx::InitImage( ImageHandle img_id, const ImageDesc * desc )
{
	XE_ASSERT( _sg.valid );
	ImageDesc desc_def = _image_desc_defaults( desc );
	_init_image( img_id, &desc_def );
	_TRACE_ARGS( InitImage, img_id, &desc_def );
}

void Gfx::InitShader( ShaderHandle shd_id, const ShaderDesc * desc )
{
	XE_ASSERT( _sg.valid );
	ShaderDesc desc_def = _shader_desc_defaults( desc );
	_init_shader( shd_id, &desc_def );
	_TRACE_ARGS( InitShader, shd_id, &desc_def );
}

void Gfx::InitPipeline( PipelineHandle pip_id, const PipelineDesc * desc )
{
	XE_ASSERT( _sg.valid );
	PipelineDesc desc_def = _pipeline_desc_defaults( desc );
	_init_pipeline( pip_id, &desc_def );
	_TRACE_ARGS( InitPipeline, pip_id, &desc_def );
}

void Gfx::InitPass( PassHandle pass_id, const PassDesc * desc )
{
	XE_ASSERT( _sg.valid );
	PassDesc desc_def = _pass_desc_defaults( desc );
	_init_pass( pass_id, &desc_def );
	_TRACE_ARGS( InitPass, pass_id, &desc_def );
}

void Gfx::FailBuffer( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( buf_id );
	_buffer_t * buf = _lookup_buffer( &_sg.pools, buf_id.GetValue() );
	XE_ASSERT( buf && buf->slot.state == RESOURCESTATE_ALLOC );
	buf->slot.ctx_id = _sg.active_context.GetValue();
	buf->slot.state = RESOURCESTATE_FAILED;
	_TRACE_ARGS( FailBuffer, buf_id );
}

void Gfx::FailImage( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( img_id );
	_image_t * img = _lookup_image( &_sg.pools, img_id.GetValue() );
	XE_ASSERT( img && img->slot.state == RESOURCESTATE_ALLOC );
	img->slot.ctx_id = _sg.active_context.GetValue();
	img->slot.state = RESOURCESTATE_FAILED;
	_TRACE_ARGS( FailImage, img_id );
}

void Gfx::FailShader( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( shd_id );
	_shader_t * shd = _lookup_shader( &_sg.pools, shd_id.GetValue() );
	XE_ASSERT( shd && shd->slot.state == RESOURCESTATE_ALLOC );
	shd->slot.ctx_id = _sg.active_context.GetValue();
	shd->slot.state = RESOURCESTATE_FAILED;
	_TRACE_ARGS( FailShader, shd_id );
}

void Gfx::FailPipeline( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pip_id );
	_pipeline_t * pip = _lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	XE_ASSERT( pip && pip->slot.state == RESOURCESTATE_ALLOC );
	pip->slot.ctx_id = _sg.active_context.GetValue();
	pip->slot.state = RESOURCESTATE_FAILED;
	_TRACE_ARGS( FailPipeline, pip_id );
}

void Gfx::FailPass( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pass_id );
	_pass_t * pass = _lookup_pass( &_sg.pools, pass_id.GetValue() );
	XE_ASSERT( pass && pass->slot.state == RESOURCESTATE_ALLOC );
	pass->slot.ctx_id = _sg.active_context.GetValue();
	pass->slot.state = RESOURCESTATE_FAILED;
	_TRACE_ARGS( FailPass, pass_id );
}

ContextHandle Gfx::SetupContext( void )
{
	XE_ASSERT( _sg.valid );
	ContextHandle res;
	int slot_index = _pool_alloc_index( &_sg.pools.context_pool );
	if( INVALID_SLOT_INDEX != slot_index )
	{
		res = _slot_alloc( &_sg.pools.context_pool, &_sg.pools.contexts[slot_index].slot, slot_index );
		_context_t * ctx = _context_at( &_sg.pools, res.GetValue() );
		ctx->slot.state = _create_context( ctx );
		XE_ASSERT( ctx->slot.state == RESOURCESTATE_VALID );
		_activate_context( ctx );
	}
	else
	{
		/* pool is exhausted */
		res = XE::ContextHandle::Invalid;
	}
	_sg.active_context = res;
	return res;
}

void Gfx::ActivateContext( ContextHandle ctx_id )
{
	XE_ASSERT( _sg.valid );
	_sg.active_context = ctx_id;
	_context_t * ctx = _lookup_context( &_sg.pools, ctx_id.GetValue() );
	/* NOTE: ctx can be 0 here if the context is no longer valid */
	_activate_context( ctx );
}

void Gfx::DiscardContext( ContextHandle ctx_id )
{
	XE_ASSERT( _sg.valid );
	_destroy_all_resources( &_sg.pools, ctx_id.GetValue() );
	_context_t * ctx = _lookup_context( &_sg.pools, ctx_id.GetValue() );
	if( ctx )
	{
		_destroy_context( ctx );
		_reset_context( ctx );
		_pool_free_index( &_sg.pools.context_pool, _slot_index( ctx_id.GetValue() ) );
	}
	_sg.active_context = XE::ContextHandle::Invalid;
	_activate_context( 0 );
}
