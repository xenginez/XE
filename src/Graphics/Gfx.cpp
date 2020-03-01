#include "Gfx.h"

USING_XE

/* resource pool slots */
struct _sg_slot_t
{
	uint32_t id;
	uint32_t ctx_id;
	ResourceState state;
};

struct _sg_buffer_common_t
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
		this->num_slots = ( this->usage == Usage::SG_USAGE_IMMUTABLE ) ? 1 : SG_NUM_INFLIGHT_FRAMES;
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

struct _sg_image_common_t
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
		this->num_slots = ( this->usage == Usage::SG_USAGE_IMMUTABLE ) ? 1 : SG_NUM_INFLIGHT_FRAMES;
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

struct _sg_uniform_block_t
{
	int size;
};

struct _sg_shader_image_t
{
	ImageType type;
};

struct _sg_shader_stage_t
{
	int num_uniform_blocks;
	int num_images;
	_sg_uniform_block_t uniform_blocks[SG_MAX_SHADERSTAGE_UBS];
	_sg_shader_image_t images[SG_MAX_SHADERSTAGE_IMAGES];
};

struct _sg_shader_common_t
{
	void init( const ShaderDesc * desc )
	{
		for( int stage_index = 0; stage_index < SG_NUM_SHADER_STAGES; stage_index++ )
		{
			const ShaderStageDesc * stage_desc = ( stage_index == ShaderStage::SG_SHADERSTAGE_VS ) ? &desc->vs : &desc->fs;
			_sg_shader_stage_t * stage = &this->stage[stage_index];
			XE_ASSERT( stage->num_uniform_blocks == 0 );
			for( int ub_index = 0; ub_index < SG_MAX_SHADERSTAGE_UBS; ub_index++ )
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
			for( int img_index = 0; img_index < SG_MAX_SHADERSTAGE_IMAGES; img_index++ )
			{
				const ShaderImageDesc * img_desc = &stage_desc->images[img_index];
				if( img_desc->type == ImageType::_SG_IMAGETYPE_DEFAULT )
				{
					break;
				}
				stage->images[img_index].type = img_desc->type;
				stage->num_images++;
			}
		}
	}

	_sg_shader_stage_t stage[SG_NUM_SHADER_STAGES];
};

struct _sg_pipeline_common_t
{
	void init( const PipelineDesc * desc )
	{
		this->shader_id = desc->shader;
		this->index_type = desc->index_type;
		for( int i = 0; i < SG_MAX_SHADERSTAGE_BUFFERS; i++ )
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
	bool vertex_layout_valid[SG_MAX_SHADERSTAGE_BUFFERS];
	int color_attachment_count;
	PixelFormat color_format;
	PixelFormat depth_format;
	int sample_count;
	float depth_bias;
	float depth_bias_slope_scale;
	float depth_bias_clamp;
	float blend_color[4];
};

struct _sg_attachment_common_t
{
	ImageHandle image_id;
	int mip_level;
	int slice;
};

struct _sg_pass_common_t
{
	void init( const PassDesc * desc )
	{
		const AttachmentDesc * att_desc;
		_sg_attachment_common_t * att;
		for( int i = 0; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
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
	_sg_attachment_common_t color_atts[SG_MAX_COLOR_ATTACHMENTS];
	_sg_attachment_common_t ds_att;
};

struct _sg_pool_t
{
	int size;
	int queue_top;
	uint32_t * gen_ctrs;
	int * free_queue;
};

enum _sg_validate_error_t
{
	/* special case 'validation was successful' */
	_SG_VALIDATE_SUCCESS,

	/* buffer creation */
	_SG_VALIDATE_BUFFERDESC_CANARY,
	_SG_VALIDATE_BUFFERDESC_SIZE,
	_SG_VALIDATE_BUFFERDESC_CONTENT,
	_SG_VALIDATE_BUFFERDESC_NO_CONTENT,

	/* image creation */
	_SG_VALIDATE_IMAGEDESC_CANARY,
	_SG_VALIDATE_IMAGEDESC_WIDTH,
	_SG_VALIDATE_IMAGEDESC_HEIGHT,
	_SG_VALIDATE_IMAGEDESC_RT_PIXELFORMAT,
	_SG_VALIDATE_IMAGEDESC_NONRT_PIXELFORMAT,
	_SG_VALIDATE_IMAGEDESC_MSAA_BUT_NO_RT,
	_SG_VALIDATE_IMAGEDESC_NO_MSAA_RT_SUPPORT,
	_SG_VALIDATE_IMAGEDESC_RT_IMMUTABLE,
	_SG_VALIDATE_IMAGEDESC_RT_NO_CONTENT,
	_SG_VALIDATE_IMAGEDESC_CONTENT,
	_SG_VALIDATE_IMAGEDESC_NO_CONTENT,

	/* shader creation */
	_SG_VALIDATE_SHADERDESC_CANARY,
	_SG_VALIDATE_SHADERDESC_SOURCE,
	_SG_VALIDATE_SHADERDESC_BYTECODE,
	_SG_VALIDATE_SHADERDESC_SOURCE_OR_BYTECODE,
	_SG_VALIDATE_SHADERDESC_NO_BYTECODE_SIZE,
	_SG_VALIDATE_SHADERDESC_NO_CONT_UBS,
	_SG_VALIDATE_SHADERDESC_NO_CONT_IMGS,
	_SG_VALIDATE_SHADERDESC_NO_CONT_UB_MEMBERS,
	_SG_VALIDATE_SHADERDESC_NO_UB_MEMBERS,
	_SG_VALIDATE_SHADERDESC_UB_MEMBER_NAME,
	_SG_VALIDATE_SHADERDESC_UB_SIZE_MISMATCH,
	_SG_VALIDATE_SHADERDESC_IMG_NAME,
	_SG_VALIDATE_SHADERDESC_ATTR_NAMES,
	_SG_VALIDATE_SHADERDESC_ATTR_SEMANTICS,
	_SG_VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG,

	/* pipeline creation */
	_SG_VALIDATE_PIPELINEDESC_CANARY,
	_SG_VALIDATE_PIPELINEDESC_SHADER,
	_SG_VALIDATE_PIPELINEDESC_NO_ATTRS,
	_SG_VALIDATE_PIPELINEDESC_LAYOUT_STRIDE4,
	_SG_VALIDATE_PIPELINEDESC_ATTR_NAME,
	_SG_VALIDATE_PIPELINEDESC_ATTR_SEMANTICS,

	/* pass creation */
	_SG_VALIDATE_PASSDESC_CANARY,
	_SG_VALIDATE_PASSDESC_NO_COLOR_ATTS,
	_SG_VALIDATE_PASSDESC_NO_CONT_COLOR_ATTS,
	_SG_VALIDATE_PASSDESC_IMAGE,
	_SG_VALIDATE_PASSDESC_MIPLEVEL,
	_SG_VALIDATE_PASSDESC_FACE,
	_SG_VALIDATE_PASSDESC_LAYER,
	_SG_VALIDATE_PASSDESC_SLICE,
	_SG_VALIDATE_PASSDESC_IMAGE_NO_RT,
	_SG_VALIDATE_PASSDESC_COLOR_PIXELFORMATS,
	_SG_VALIDATE_PASSDESC_COLOR_INV_PIXELFORMAT,
	_SG_VALIDATE_PASSDESC_DEPTH_INV_PIXELFORMAT,
	_SG_VALIDATE_PASSDESC_IMAGE_SIZES,
	_SG_VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS,

	/* sg_begin_pass validation */
	_SG_VALIDATE_BEGINPASS_PASS,
	_SG_VALIDATE_BEGINPASS_IMAGE,

	/* sg_apply_pipeline validation */
	_SG_VALIDATE_APIP_PIPELINE_VALID_ID,
	_SG_VALIDATE_APIP_PIPELINE_EXISTS,
	_SG_VALIDATE_APIP_PIPELINE_VALID,
	_SG_VALIDATE_APIP_SHADER_EXISTS,
	_SG_VALIDATE_APIP_SHADER_VALID,
	_SG_VALIDATE_APIP_ATT_COUNT,
	_SG_VALIDATE_APIP_COLOR_FORMAT,
	_SG_VALIDATE_APIP_DEPTH_FORMAT,
	_SG_VALIDATE_APIP_SAMPLE_COUNT,

	/* sg_apply_bindings validation */
	_SG_VALIDATE_ABND_PIPELINE,
	_SG_VALIDATE_ABND_PIPELINE_EXISTS,
	_SG_VALIDATE_ABND_PIPELINE_VALID,
	_SG_VALIDATE_ABND_VBS,
	_SG_VALIDATE_ABND_VB_EXISTS,
	_SG_VALIDATE_ABND_VB_TYPE,
	_SG_VALIDATE_ABND_VB_OVERFLOW,
	_SG_VALIDATE_ABND_NO_IB,
	_SG_VALIDATE_ABND_IB,
	_SG_VALIDATE_ABND_IB_EXISTS,
	_SG_VALIDATE_ABND_IB_TYPE,
	_SG_VALIDATE_ABND_IB_OVERFLOW,
	_SG_VALIDATE_ABND_VS_IMGS,
	_SG_VALIDATE_ABND_VS_IMG_EXISTS,
	_SG_VALIDATE_ABND_VS_IMG_TYPES,
	_SG_VALIDATE_ABND_FS_IMGS,
	_SG_VALIDATE_ABND_FS_IMG_EXISTS,
	_SG_VALIDATE_ABND_FS_IMG_TYPES,

	/* sg_apply_uniforms validation */
	_SG_VALIDATE_AUB_NO_PIPELINE,
	_SG_VALIDATE_AUB_NO_UB_AT_SLOT,
	_SG_VALIDATE_AUB_SIZE,

	/* sg_update_buffer validation */
	_SG_VALIDATE_UPDATEBUF_USAGE,
	_SG_VALIDATE_UPDATEBUF_SIZE,
	_SG_VALIDATE_UPDATEBUF_ONCE,
	_SG_VALIDATE_UPDATEBUF_APPEND,

	/* sg_append_buffer validation */
	_SG_VALIDATE_APPENDBUF_USAGE,
	_SG_VALIDATE_APPENDBUF_SIZE,
	_SG_VALIDATE_APPENDBUF_UPDATE,

	/* sg_update_image validation */
	_SG_VALIDATE_UPDIMG_USAGE,
	_SG_VALIDATE_UPDIMG_NOTENOUGHDATA,
	_SG_VALIDATE_UPDIMG_SIZE,
	_SG_VALIDATE_UPDIMG_COMPRESSED,
	_SG_VALIDATE_UPDIMG_ONCE
};

/* constants */
enum
{
	_SG_STRING_SIZE = 16,
	_SG_SLOT_SHIFT = 16,
	_SG_SLOT_MASK = ( 1 << _SG_SLOT_SHIFT ) - 1,
	_SG_MAX_POOL_SIZE = ( 1 << _SG_SLOT_SHIFT ),
	_SG_DEFAULT_BUFFER_POOL_SIZE = 128,
	_SG_DEFAULT_IMAGE_POOL_SIZE = 128,
	_SG_DEFAULT_SHADER_POOL_SIZE = 32,
	_SG_DEFAULT_PIPELINE_POOL_SIZE = 64,
	_SG_DEFAULT_PASS_POOL_SIZE = 16,
	_SG_DEFAULT_CONTEXT_POOL_SIZE = 16,
	_SG_MTL_DEFAULT_UB_SIZE = 4 * 1024 * 1024,
	_SG_MTL_DEFAULT_SAMPLER_CACHE_CAPACITY = 64,
};

/* helper macros */
#define _sg_def(val, def) (((val) == 0) ? (def) : (val))
#define _sg_def_flt(val, def) (((val) == 0.0f) ? (def) : (val))
#define _sg_min(a,b) ((a<b)?a:b)
#define _sg_max(a,b) ((a>b)?a:b)
#define _sg_clamp(v,v0,v1) ((v<v0)?(v0):((v>v1)?(v1):(v)))
#define _sg_fequal(val,cmp,delta) (((val-cmp)> -delta)&&((val-cmp)<delta))


/* return byte size of a vertex format */
int _sg_vertexformat_bytesize( VertexFormat fmt )
{
	switch( fmt )
	{
	case SG_VERTEXFORMAT_FLOAT:     return 4;
	case SG_VERTEXFORMAT_FLOAT2:    return 8;
	case SG_VERTEXFORMAT_FLOAT3:    return 12;
	case SG_VERTEXFORMAT_FLOAT4:    return 16;
	case SG_VERTEXFORMAT_BYTE4:     return 4;
	case SG_VERTEXFORMAT_BYTE4N:    return 4;
	case SG_VERTEXFORMAT_UBYTE4:    return 4;
	case SG_VERTEXFORMAT_UBYTE4N:   return 4;
	case SG_VERTEXFORMAT_SHORT2:    return 4;
	case SG_VERTEXFORMAT_SHORT2N:   return 4;
	case SG_VERTEXFORMAT_USHORT2N:  return 4;
	case SG_VERTEXFORMAT_SHORT4:    return 8;
	case SG_VERTEXFORMAT_SHORT4N:   return 8;
	case SG_VERTEXFORMAT_USHORT4N:  return 8;
	case SG_VERTEXFORMAT_UINT10_N2: return 4;
	case SG_VERTEXFORMAT_INVALID:   return 0;
	default:
		XE_ASSERT( false );
		return -1;
	}
}

/* return the byte size of a shader uniform */
int _sg_uniform_size( UniformType type, int count )
{
	switch( type )
	{
	case SG_UNIFORMTYPE_INVALID:    return 0;
	case SG_UNIFORMTYPE_FLOAT:      return 4 * count;
	case SG_UNIFORMTYPE_FLOAT2:     return 8 * count;
	case SG_UNIFORMTYPE_FLOAT3:     return 12 * count; /* FIXME: std140??? */
	case SG_UNIFORMTYPE_FLOAT4:     return 16 * count;
	case SG_UNIFORMTYPE_MAT4:       return 64 * count;
	default:
		XE_ASSERT( false );
		return -1;
	}
}

PixelFormat _sg_default_rendertarget_depthformat( void )
{
	return SG_PIXELFORMAT_DEPTH_STENCIL;
}

/* return true if pixel format is a compressed format */
bool _sg_is_compressed_pixel_format( PixelFormat fmt )
{
	switch( fmt )
	{
	case SG_PIXELFORMAT_BC1_RGBA:
	case SG_PIXELFORMAT_BC2_RGBA:
	case SG_PIXELFORMAT_BC3_RGBA:
	case SG_PIXELFORMAT_BC4_R:
	case SG_PIXELFORMAT_BC4_RSN:
	case SG_PIXELFORMAT_BC5_RG:
	case SG_PIXELFORMAT_BC5_RGSN:
	case SG_PIXELFORMAT_BC6H_RGBF:
	case SG_PIXELFORMAT_BC6H_RGBUF:
	case SG_PIXELFORMAT_BC7_RGBA:
	case SG_PIXELFORMAT_PVRTC_RGB_2BPP:
	case SG_PIXELFORMAT_PVRTC_RGB_4BPP:
	case SG_PIXELFORMAT_PVRTC_RGBA_2BPP:
	case SG_PIXELFORMAT_PVRTC_RGBA_4BPP:
	case SG_PIXELFORMAT_ETC2_RGB8:
	case SG_PIXELFORMAT_ETC2_RGB8A1:
	case SG_PIXELFORMAT_ETC2_RGBA8:
	case SG_PIXELFORMAT_ETC2_RG11:
	case SG_PIXELFORMAT_ETC2_RG11SN:
		return true;
	default:
		return false;
	}
}

/* return true if pixel format is a depth-stencil format */
bool _sg_is_depth_stencil_format( PixelFormat fmt )
{
	return ( SG_PIXELFORMAT_DEPTH_STENCIL == fmt );
}

/* return the bytes-per-pixel for a pixel format */
int _sg_pixelformat_bytesize( PixelFormat fmt )
{
	switch( fmt )
	{
	case SG_PIXELFORMAT_R8:
	case SG_PIXELFORMAT_R8SN:
	case SG_PIXELFORMAT_R8UI:
	case SG_PIXELFORMAT_R8SI:
		return 1;

	case SG_PIXELFORMAT_R16:
	case SG_PIXELFORMAT_R16SN:
	case SG_PIXELFORMAT_R16UI:
	case SG_PIXELFORMAT_R16SI:
	case SG_PIXELFORMAT_R16F:
	case SG_PIXELFORMAT_RG8:
	case SG_PIXELFORMAT_RG8SN:
	case SG_PIXELFORMAT_RG8UI:
	case SG_PIXELFORMAT_RG8SI:
		return 2;

	case SG_PIXELFORMAT_R32UI:
	case SG_PIXELFORMAT_R32SI:
	case SG_PIXELFORMAT_R32F:
	case SG_PIXELFORMAT_RG16:
	case SG_PIXELFORMAT_RG16SN:
	case SG_PIXELFORMAT_RG16UI:
	case SG_PIXELFORMAT_RG16SI:
	case SG_PIXELFORMAT_RG16F:
	case SG_PIXELFORMAT_RGBA8:
	case SG_PIXELFORMAT_RGBA8SN:
	case SG_PIXELFORMAT_RGBA8UI:
	case SG_PIXELFORMAT_RGBA8SI:
	case SG_PIXELFORMAT_BGRA8:
	case SG_PIXELFORMAT_RGB10A2:
	case SG_PIXELFORMAT_RG11B10F:
		return 4;

	case SG_PIXELFORMAT_RG32UI:
	case SG_PIXELFORMAT_RG32SI:
	case SG_PIXELFORMAT_RG32F:
	case SG_PIXELFORMAT_RGBA16:
	case SG_PIXELFORMAT_RGBA16SN:
	case SG_PIXELFORMAT_RGBA16UI:
	case SG_PIXELFORMAT_RGBA16SI:
	case SG_PIXELFORMAT_RGBA16F:
		return 8;

	case SG_PIXELFORMAT_RGBA32UI:
	case SG_PIXELFORMAT_RGBA32SI:
	case SG_PIXELFORMAT_RGBA32F:
		return 16;

	default:
		XE_ASSERT( false );
		return 0;
	}
}

/* return row pitch for an image
	see ComputePitch in https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexUtil.cpp
*/
int _sg_row_pitch( PixelFormat fmt, int width )
{
	int pitch;
	switch( fmt )
	{
	case SG_PIXELFORMAT_BC1_RGBA:
	case SG_PIXELFORMAT_BC4_R:
	case SG_PIXELFORMAT_BC4_RSN:
	case SG_PIXELFORMAT_ETC2_RGB8:
	case SG_PIXELFORMAT_ETC2_RGB8A1:
		pitch = ( ( width + 3 ) / 4 ) * 8;
		pitch = pitch < 8 ? 8 : pitch;
		break;
	case SG_PIXELFORMAT_BC2_RGBA:
	case SG_PIXELFORMAT_BC3_RGBA:
	case SG_PIXELFORMAT_BC5_RG:
	case SG_PIXELFORMAT_BC5_RGSN:
	case SG_PIXELFORMAT_BC6H_RGBF:
	case SG_PIXELFORMAT_BC6H_RGBUF:
	case SG_PIXELFORMAT_BC7_RGBA:
	case SG_PIXELFORMAT_ETC2_RGBA8:
	case SG_PIXELFORMAT_ETC2_RG11:
	case SG_PIXELFORMAT_ETC2_RG11SN:
		pitch = ( ( width + 3 ) / 4 ) * 16;
		pitch = pitch < 16 ? 16 : pitch;
		break;
	case SG_PIXELFORMAT_PVRTC_RGB_4BPP:
	case SG_PIXELFORMAT_PVRTC_RGBA_4BPP:
	{
		const int block_size = 4 * 4;
		const int bpp = 4;
		int width_blocks = width / 4;
		width_blocks = width_blocks < 2 ? 2 : width_blocks;
		pitch = width_blocks * ( ( block_size * bpp ) / 8 );
	}
	break;
	case SG_PIXELFORMAT_PVRTC_RGB_2BPP:
	case SG_PIXELFORMAT_PVRTC_RGBA_2BPP:
	{
		const int block_size = 8 * 4;
		const int bpp = 2;
		int width_blocks = width / 4;
		width_blocks = width_blocks < 2 ? 2 : width_blocks;
		pitch = width_blocks * ( ( block_size * bpp ) / 8 );
	}
	break;
	default:
		pitch = width * _sg_pixelformat_bytesize( fmt );
		break;
	}
	return pitch;
}

/* return pitch of a 2D subimage / texture slice
	see ComputePitch in https://github.com/microsoft/DirectXTex/blob/master/DirectXTex/DirectXTexUtil.cpp
*/
int _sg_surface_pitch( PixelFormat fmt, int width, int height )
{
	int num_rows = 0;
	switch( fmt )
	{
	case SG_PIXELFORMAT_BC1_RGBA:
	case SG_PIXELFORMAT_BC4_R:
	case SG_PIXELFORMAT_BC4_RSN:
	case SG_PIXELFORMAT_ETC2_RGB8:
	case SG_PIXELFORMAT_ETC2_RGB8A1:
	case SG_PIXELFORMAT_ETC2_RGBA8:
	case SG_PIXELFORMAT_ETC2_RG11:
	case SG_PIXELFORMAT_ETC2_RG11SN:
	case SG_PIXELFORMAT_BC2_RGBA:
	case SG_PIXELFORMAT_BC3_RGBA:
	case SG_PIXELFORMAT_BC5_RG:
	case SG_PIXELFORMAT_BC5_RGSN:
	case SG_PIXELFORMAT_BC6H_RGBF:
	case SG_PIXELFORMAT_BC6H_RGBUF:
	case SG_PIXELFORMAT_BC7_RGBA:
	case SG_PIXELFORMAT_PVRTC_RGB_4BPP:
	case SG_PIXELFORMAT_PVRTC_RGBA_4BPP:
	case SG_PIXELFORMAT_PVRTC_RGB_2BPP:
	case SG_PIXELFORMAT_PVRTC_RGBA_2BPP:
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
	return num_rows * _sg_row_pitch( fmt, width );
}

/* capability table pixel format helper functions */
void _sg_pixelformat_all( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
	pfi->blend = true;
	pfi->render = true;
	pfi->msaa = true;
}

void _sg_pixelformat_s( PixelformatInfo * pfi )
{
	pfi->sample = true;
}

void _sg_pixelformat_sf( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
}

void _sg_pixelformat_sr( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->render = true;
}

void _sg_pixelformat_srmd( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->render = true;
	pfi->msaa = true;
	pfi->depth = true;
}

void _sg_pixelformat_srm( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->render = true;
	pfi->msaa = true;
}

void _sg_pixelformat_sfrm( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
	pfi->render = true;
	pfi->msaa = true;
}
void _sg_pixelformat_sbrm( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->blend = true;
	pfi->render = true;
	pfi->msaa = true;
}

void _sg_pixelformat_sbr( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->blend = true;
	pfi->render = true;
}

void _sg_pixelformat_sfbr( PixelformatInfo * pfi )
{
	pfi->sample = true;
	pfi->filter = true;
	pfi->blend = true;
	pfi->render = true;
}

/* resolve pass action defaults into a new pass action struct */
void _sg_resolve_default_pass_action( const PassAction * from, PassAction * to )
{
	XE_ASSERT( from && to );
	*to = *from;
	for( int i = 0; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
	{
		if( to->colors[i].action == _SG_ACTION_DEFAULT )
		{
			to->colors[i].action = SG_ACTION_CLEAR;
			to->colors[i].val[0] = SG_DEFAULT_CLEAR_RED;
			to->colors[i].val[1] = SG_DEFAULT_CLEAR_GREEN;
			to->colors[i].val[2] = SG_DEFAULT_CLEAR_BLUE;
			to->colors[i].val[3] = SG_DEFAULT_CLEAR_ALPHA;
		}
	}
	if( to->depth.action == _SG_ACTION_DEFAULT )
	{
		to->depth.action = SG_ACTION_CLEAR;
		to->depth.val = SG_DEFAULT_CLEAR_DEPTH;
	}
	if( to->stencil.action == _SG_ACTION_DEFAULT )
	{
		to->stencil.action = SG_ACTION_CLEAR;
		to->stencil.val = SG_DEFAULT_CLEAR_STENCIL;
	}
}

#include "Gfx_GLES.h"
#include "Gfx_D3D11.h"
#include "Gfx_D3D12.h"
#include "Gfx_Metal.h"
#include "Gfx_Vulkan.h"

void _sg_init_pool( _sg_pool_t * pool, int num )
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

void _sg_discard_pool( _sg_pool_t * pool )
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

int _sg_pool_alloc_index( _sg_pool_t * pool )
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
		return SG_INVALID_SLOT_INDEX;
	}
}

void _sg_pool_free_index( _sg_pool_t * pool, int slot_index )
{
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < pool->size ) );
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

void _sg_reset_buffer( _sg_buffer_t * buf )
{
	XE_ASSERT( buf );
	memset( buf, 0, sizeof( _sg_buffer_t ) );
}

void _sg_reset_image( _sg_image_t * img )
{
	XE_ASSERT( img );
	memset( img, 0, sizeof( _sg_image_t ) );
}

void _sg_reset_shader( _sg_shader_t * shd )
{
	XE_ASSERT( shd );
	memset( shd, 0, sizeof( _sg_shader_t ) );
}

void _sg_reset_pipeline( _sg_pipeline_t * pip )
{
	XE_ASSERT( pip );
	memset( pip, 0, sizeof( _sg_pipeline_t ) );
}

void _sg_reset_pass( _sg_pass_t * pass )
{
	XE_ASSERT( pass );
	memset( pass, 0, sizeof( _sg_pass_t ) );
}

void _sg_reset_context( _sg_context_t * ctx )
{
	XE_ASSERT( ctx );
	memset( ctx, 0, sizeof( _sg_context_t ) );
}

void _sg_setup_pools( _sg_pools_t * p, const GfxDesc * desc )
{
	XE_ASSERT( p );
	XE_ASSERT( desc );
	/* note: the pools here will have an additional item, since slot 0 is reserved */
	XE_ASSERT( ( desc->buffer_pool_size > 0 ) && ( desc->buffer_pool_size < _SG_MAX_POOL_SIZE ) );
	_sg_init_pool( &p->buffer_pool, desc->buffer_pool_size );
	size_t buffer_pool_byte_size = sizeof( _sg_buffer_t ) * p->buffer_pool.size;
	p->buffers = (_sg_buffer_t * )malloc( buffer_pool_byte_size );
	XE_ASSERT( p->buffers );
	memset( p->buffers, 0, buffer_pool_byte_size );

	XE_ASSERT( ( desc->image_pool_size > 0 ) && ( desc->image_pool_size < _SG_MAX_POOL_SIZE ) );
	_sg_init_pool( &p->image_pool, desc->image_pool_size );
	size_t image_pool_byte_size = sizeof( _sg_image_t ) * p->image_pool.size;
	p->images = (_sg_image_t * )malloc( image_pool_byte_size );
	XE_ASSERT( p->images );
	memset( p->images, 0, image_pool_byte_size );

	XE_ASSERT( ( desc->shader_pool_size > 0 ) && ( desc->shader_pool_size < _SG_MAX_POOL_SIZE ) );
	_sg_init_pool( &p->shader_pool, desc->shader_pool_size );
	size_t shader_pool_byte_size = sizeof( _sg_shader_t ) * p->shader_pool.size;
	p->shaders = (_sg_shader_t * )malloc( shader_pool_byte_size );
	XE_ASSERT( p->shaders );
	memset( p->shaders, 0, shader_pool_byte_size );

	XE_ASSERT( ( desc->pipeline_pool_size > 0 ) && ( desc->pipeline_pool_size < _SG_MAX_POOL_SIZE ) );
	_sg_init_pool( &p->pipeline_pool, desc->pipeline_pool_size );
	size_t pipeline_pool_byte_size = sizeof( _sg_pipeline_t ) * p->pipeline_pool.size;
	p->pipelines = (_sg_pipeline_t * )malloc( pipeline_pool_byte_size );
	XE_ASSERT( p->pipelines );
	memset( p->pipelines, 0, pipeline_pool_byte_size );

	XE_ASSERT( ( desc->pass_pool_size > 0 ) && ( desc->pass_pool_size < _SG_MAX_POOL_SIZE ) );
	_sg_init_pool( &p->pass_pool, desc->pass_pool_size );
	size_t pass_pool_byte_size = sizeof( _sg_pass_t ) * p->pass_pool.size;
	p->passes = (_sg_pass_t * )malloc( pass_pool_byte_size );
	XE_ASSERT( p->passes );
	memset( p->passes, 0, pass_pool_byte_size );

	XE_ASSERT( ( desc->context_pool_size > 0 ) && ( desc->context_pool_size < _SG_MAX_POOL_SIZE ) );
	_sg_init_pool( &p->context_pool, desc->context_pool_size );
	size_t context_pool_byte_size = sizeof( _sg_context_t ) * p->context_pool.size;
	p->contexts = (_sg_context_t * )malloc( context_pool_byte_size );
	XE_ASSERT( p->contexts );
	memset( p->contexts, 0, context_pool_byte_size );
}

void _sg_discard_pools( _sg_pools_t * p )
{
	XE_ASSERT( p );
	free( p->contexts );    p->contexts = 0;
	free( p->passes );      p->passes = 0;
	free( p->pipelines );   p->pipelines = 0;
	free( p->shaders );     p->shaders = 0;
	free( p->images );      p->images = 0;
	free( p->buffers );     p->buffers = 0;
	_sg_discard_pool( &p->context_pool );
	_sg_discard_pool( &p->pass_pool );
	_sg_discard_pool( &p->pipeline_pool );
	_sg_discard_pool( &p->shader_pool );
	_sg_discard_pool( &p->image_pool );
	_sg_discard_pool( &p->buffer_pool );
}

/* allocate the slot at slot_index:
	- bump the slot's generation counter
	- create a resource id from the generation counter and slot index
	- set the slot's id to this id
	- set the slot's state to ALLOC
	- return the resource id
*/
uint32_t _sg_slot_alloc( _sg_pool_t * pool, _sg_slot_t * slot, int slot_index )
{
	/* FIXME: add handling for an overflowing generation counter,
	   for now, just overflow (another option is to disable
	   the slot)
	*/
	XE_ASSERT( pool && pool->gen_ctrs );
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < pool->size ) );
	XE_ASSERT( ( slot->state == SG_RESOURCESTATE_INITIAL ) && !( slot->id ) );
	uint32_t ctr = ++pool->gen_ctrs[slot_index];
	slot->id = ( ctr << _SG_SLOT_SHIFT ) | ( slot_index & _SG_SLOT_MASK );
	slot->state = SG_RESOURCESTATE_ALLOC;
	return slot->id;
}

/* extract slot index from id */
int _sg_slot_index( uint32_t id )
{
	int slot_index = (int )( id & _SG_SLOT_MASK );
	XE_ASSERT( SG_INVALID_SLOT_INDEX != slot_index );
	return slot_index;
}

/* returns pointer to resource by id without matching id check */
_sg_buffer_t * _sg_buffer_at( const _sg_pools_t * p, uint32_t buf_id )
{
	XE_ASSERT( p && ( buf_id ) );
	int slot_index = _sg_slot_index( buf_id );
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < p->buffer_pool.size ) );
	return &p->buffers[slot_index];
}

_sg_image_t * _sg_image_at( const _sg_pools_t * p, uint32_t img_id )
{
	XE_ASSERT( p && ( img_id ) );
	int slot_index = _sg_slot_index( img_id );
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < p->image_pool.size ) );
	return &p->images[slot_index];
}

_sg_shader_t * _sg_shader_at( const _sg_pools_t * p, uint32_t shd_id )
{
	XE_ASSERT( p && ( shd_id ) );
	int slot_index = _sg_slot_index( shd_id );
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < p->shader_pool.size ) );
	return &p->shaders[slot_index];
}

_sg_pipeline_t * _sg_pipeline_at( const _sg_pools_t * p, uint32_t pip_id )
{
	XE_ASSERT( p && ( pip_id ) );
	int slot_index = _sg_slot_index( pip_id );
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < p->pipeline_pool.size ) );
	return &p->pipelines[slot_index];
}

_sg_pass_t * _sg_pass_at( const _sg_pools_t * p, uint32_t pass_id )
{
	XE_ASSERT( p && ( pass_id ) );
	int slot_index = _sg_slot_index( pass_id );
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < p->pass_pool.size ) );
	return &p->passes[slot_index];
}

_sg_context_t * _sg_context_at( const _sg_pools_t * p, uint32_t context_id )
{
	XE_ASSERT( p && ( context_id ) );
	int slot_index = _sg_slot_index( context_id );
	XE_ASSERT( ( slot_index > SG_INVALID_SLOT_INDEX ) && ( slot_index < p->context_pool.size ) );
	return &p->contexts[slot_index];
}

/* returns pointer to resource with matching id check, may return 0 */
_sg_buffer_t * _sg_lookup_buffer( const _sg_pools_t * p, uint32_t buf_id )
{
	if( buf_id )
	{
		_sg_buffer_t * buf = _sg_buffer_at( p, buf_id );
		if( buf->slot.id == buf_id )
		{
			return buf;
		}
	}
	return 0;
}

_sg_image_t * _sg_lookup_image( const _sg_pools_t * p, uint32_t img_id )
{
	if( img_id )
	{
		_sg_image_t * img = _sg_image_at( p, img_id );
		if( img->slot.id == img_id )
		{
			return img;
		}
	}
	return 0;
}

_sg_shader_t * _sg_lookup_shader( const _sg_pools_t * p, uint32_t shd_id )
{
	XE_ASSERT( p );
	if( shd_id )
	{
		_sg_shader_t * shd = _sg_shader_at( p, shd_id );
		if( shd->slot.id == shd_id )
		{
			return shd;
		}
	}
	return 0;
}

_sg_pipeline_t * _sg_lookup_pipeline( const _sg_pools_t * p, uint32_t pip_id )
{
	XE_ASSERT( p );
	if( pip_id )
	{
		_sg_pipeline_t * pip = _sg_pipeline_at( p, pip_id );
		if( pip->slot.id == pip_id )
		{
			return pip;
		}
	}
	return 0;
}

_sg_pass_t * _sg_lookup_pass( const _sg_pools_t * p, uint32_t pass_id )
{
	XE_ASSERT( p );
	if( pass_id )
	{
		_sg_pass_t * pass = _sg_pass_at( p, pass_id );
		if( pass->slot.id == pass_id )
		{
			return pass;
		}
	}
	return 0;
}

_sg_context_t * _sg_lookup_context( const _sg_pools_t * p, uint32_t ctx_id )
{
	XE_ASSERT( p );
	if( ctx_id )
	{
		_sg_context_t * ctx = _sg_context_at( p, ctx_id );
		if( ctx->slot.id == ctx_id )
		{
			return ctx;
		}
	}
	return 0;
}

void _sg_destroy_all_resources( _sg_pools_t * p, uint32_t ctx_id )
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
			if( ( state == SG_RESOURCESTATE_VALID ) || ( state == SG_RESOURCESTATE_FAILED ) )
			{
				_sg_destroy_buffer( &p->buffers[i] );
			}
		}
	}
	for( int i = 1; i < p->image_pool.size; i++ )
	{
		if( p->images[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->images[i].slot.state;
			if( ( state == SG_RESOURCESTATE_VALID ) || ( state == SG_RESOURCESTATE_FAILED ) )
			{
				_sg_destroy_image( &p->images[i] );
			}
		}
	}
	for( int i = 1; i < p->shader_pool.size; i++ )
	{
		if( p->shaders[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->shaders[i].slot.state;
			if( ( state == SG_RESOURCESTATE_VALID ) || ( state == SG_RESOURCESTATE_FAILED ) )
			{
				_sg_destroy_shader( &p->shaders[i] );
			}
		}
	}
	for( int i = 1; i < p->pipeline_pool.size; i++ )
	{
		if( p->pipelines[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->pipelines[i].slot.state;
			if( ( state == SG_RESOURCESTATE_VALID ) || ( state == SG_RESOURCESTATE_FAILED ) )
			{
				_sg_destroy_pipeline( &p->pipelines[i] );
			}
		}
	}
	for( int i = 1; i < p->pass_pool.size; i++ )
	{
		if( p->passes[i].slot.ctx_id == ctx_id )
		{
			ResourceState state = p->passes[i].slot.state;
			if( ( state == SG_RESOURCESTATE_VALID ) || ( state == SG_RESOURCESTATE_FAILED ) )
			{
				_sg_destroy_pass( &p->passes[i] );
			}
		}
	}
}



XE::String _sg_validate_string( _sg_validate_error_t err )
{
	switch( err )
	{
		/* buffer creation validation errors */
	case _sg_validate_error_t::_SG_VALIDATE_BUFFERDESC_CANARY:        return "BufferDesc not initialized";
	case _sg_validate_error_t::_SG_VALIDATE_BUFFERDESC_SIZE:          return "BufferDesc.size cannot be 0";
	case _sg_validate_error_t::_SG_VALIDATE_BUFFERDESC_CONTENT:       return "immutable buffers must be initialized with content (BufferDesc.content)";
	case _sg_validate_error_t::_SG_VALIDATE_BUFFERDESC_NO_CONTENT:    return "dynamic/stream usage buffers cannot be initialized with content";

		/* image creation validation errros */
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_CANARY:             return "ImageDesc not initialized";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_WIDTH:              return "ImageDesc.width must be > 0";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_HEIGHT:             return "ImageDesc.height must be > 0";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_RT_PIXELFORMAT:     return "invalid pixel format for render-target image";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_NONRT_PIXELFORMAT:  return "invalid pixel format for non-render-target image";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_MSAA_BUT_NO_RT:     return "non-render-target images cannot be multisampled";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_NO_MSAA_RT_SUPPORT: return "MSAA not supported for this pixel format";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_RT_IMMUTABLE:       return "render target images must be SG_USAGE_IMMUTABLE";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_RT_NO_CONTENT:      return "render target images cannot be initialized with content";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_CONTENT:            return "missing or invalid content for immutable image";
	case _sg_validate_error_t::_SG_VALIDATE_IMAGEDESC_NO_CONTENT:         return "dynamic/stream usage images cannot be initialized with content";

		/* shader creation */
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_CANARY:                return "ShaderDesc not initialized";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_SOURCE:                return "shader source code required";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_BYTECODE:              return "shader byte code required";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_SOURCE_OR_BYTECODE:    return "shader source or byte code required";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_NO_BYTECODE_SIZE:      return "shader byte code length (in bytes) required";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_NO_CONT_UBS:           return "shader uniform blocks must occupy continuous slots";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_NO_CONT_UB_MEMBERS:    return "uniform block members must occupy continuous slots";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_NO_UB_MEMBERS:         return "GL backend requires uniform block member declarations";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_UB_MEMBER_NAME:        return "uniform block member name missing";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_UB_SIZE_MISMATCH:      return "size of uniform block members doesn't match uniform block size";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_NO_CONT_IMGS:          return "shader images must occupy continuous slots";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_IMG_NAME:              return "GL backend requires uniform block member names";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_ATTR_NAMES:            return "GLES2 backend requires vertex attribute names";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_ATTR_SEMANTICS:        return "D3D11 backend requires vertex attribute semantics";
	case _sg_validate_error_t::_SG_VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG:  return "vertex attribute name/semantic string too long (max len 16)";

		/* pipeline creation */
	case _sg_validate_error_t::_SG_VALIDATE_PIPELINEDESC_CANARY:          return "PipelineDesc not initialized";
	case _sg_validate_error_t::_SG_VALIDATE_PIPELINEDESC_SHADER:          return "PipelineDesc.shader missing or invalid";
	case _sg_validate_error_t::_SG_VALIDATE_PIPELINEDESC_NO_ATTRS:        return "PipelineDesc.layout.attrs is empty or not continuous";
	case _sg_validate_error_t::_SG_VALIDATE_PIPELINEDESC_LAYOUT_STRIDE4:  return "PipelineDesc.layout.buffers[].stride must be multiple of 4";
	case _sg_validate_error_t::_SG_VALIDATE_PIPELINEDESC_ATTR_NAME:       return "GLES2/WebGL missing vertex attribute name in shader";
	case _sg_validate_error_t::_SG_VALIDATE_PIPELINEDESC_ATTR_SEMANTICS:  return "D3D11 missing vertex attribute semantics in shader";

		/* pass creation */
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_CANARY:                  return "PassDesc not initialized";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_NO_COLOR_ATTS:           return "PassDesc.color_attachments[0] must be valid";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_NO_CONT_COLOR_ATTS:      return "color attachments must occupy continuous slots";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_IMAGE:                   return "pass attachment image is not valid";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_MIPLEVEL:                return "pass attachment mip level is bigger than image has mipmaps";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_FACE:                    return "pass attachment image is cubemap, but face index is too big";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_LAYER:                   return "pass attachment image is array texture, but layer index is too big";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_SLICE:                   return "pass attachment image is 3d texture, but slice value is too big";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_IMAGE_NO_RT:             return "pass attachment image must be render targets";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_COLOR_PIXELFORMATS:      return "all pass color attachment images must have the same pixel format";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_COLOR_INV_PIXELFORMAT:   return "pass color-attachment images must have a renderable pixel format";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_DEPTH_INV_PIXELFORMAT:   return "pass depth-attachment image must have depth pixel format";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_IMAGE_SIZES:             return "all pass attachments must have the same size";
	case _sg_validate_error_t::_SG_VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS:     return "all pass attachments must have the same sample count";

		/* sg_begin_pass */
	case _sg_validate_error_t::_SG_VALIDATE_BEGINPASS_PASS:       return "sg_begin_pass: pass must be valid";
	case _sg_validate_error_t::_SG_VALIDATE_BEGINPASS_IMAGE:      return "sg_begin_pass: one or more attachment images are not valid";

		/* sg_apply_pipeline */
	case _sg_validate_error_t::_SG_VALIDATE_APIP_PIPELINE_VALID_ID:   return "sg_apply_pipeline: invalid pipeline id provided";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_PIPELINE_EXISTS:     return "sg_apply_pipeline: pipeline object no longer alive";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_PIPELINE_VALID:      return "sg_apply_pipeline: pipeline object not in valid state";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_SHADER_EXISTS:       return "sg_apply_pipeline: shader object no longer alive";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_SHADER_VALID:        return "sg_apply_pipeline: shader object not in valid state";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_ATT_COUNT:           return "sg_apply_pipeline: color_attachment_count in pipeline doesn't match number of pass color attachments";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_COLOR_FORMAT:        return "sg_apply_pipeline: color_format in pipeline doesn't match pass color attachment pixel format";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_DEPTH_FORMAT:        return "sg_apply_pipeline: depth_format in pipeline doesn't match pass depth attachment pixel format";
	case _sg_validate_error_t::_SG_VALIDATE_APIP_SAMPLE_COUNT:        return "sg_apply_pipeline: MSAA sample count in pipeline doesn't match render pass attachment sample count";

		/* sg_apply_bindings */
	case _sg_validate_error_t::_SG_VALIDATE_ABND_PIPELINE:            return "sg_apply_bindings: must be called after sg_apply_pipeline";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_PIPELINE_EXISTS:     return "sg_apply_bindings: currently applied pipeline object no longer alive";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_PIPELINE_VALID:      return "sg_apply_bindings: currently applied pipeline object not in valid state";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_VBS:                 return "sg_apply_bindings: number of vertex buffers doesn't match number of pipeline vertex layouts";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_VB_EXISTS:           return "sg_apply_bindings: vertex buffer no longer alive";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_VB_TYPE:             return "sg_apply_bindings: buffer in vertex buffer slot is not a SG_BUFFERTYPE_VERTEXBUFFER";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_VB_OVERFLOW:         return "sg_apply_bindings: buffer in vertex buffer slot is overflown";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_NO_IB:               return "sg_apply_bindings: pipeline object defines indexed rendering, but no index buffer provided";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_IB:                  return "sg_apply_bindings: pipeline object defines non-indexed rendering, but index buffer provided";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_IB_EXISTS:           return "sg_apply_bindings: index buffer no longer alive";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_IB_TYPE:             return "sg_apply_bindings: buffer in index buffer slot is not a SG_BUFFERTYPE_INDEXBUFFER";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_IB_OVERFLOW:         return "sg_apply_bindings: buffer in index buffer slot is overflown";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_VS_IMGS:             return "sg_apply_bindings: vertex shader image count doesn't match ShaderDesc";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_VS_IMG_EXISTS:       return "sg_apply_bindings: vertex shader image no longer alive";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_VS_IMG_TYPES:        return "sg_apply_bindings: one or more vertex shader image types don't match ShaderDesc";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_FS_IMGS:             return "sg_apply_bindings: fragment shader image count doesn't match ShaderDesc";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_FS_IMG_EXISTS:       return "sg_apply_bindings: fragment shader image no longer alive";
	case _sg_validate_error_t::_SG_VALIDATE_ABND_FS_IMG_TYPES:        return "sg_apply_bindings: one or more fragment shader image types don't match ShaderDesc";

		/* sg_apply_uniforms */
	case _sg_validate_error_t::_SG_VALIDATE_AUB_NO_PIPELINE:      return "sg_apply_uniforms: must be called after sg_apply_pipeline()";
	case _sg_validate_error_t::_SG_VALIDATE_AUB_NO_UB_AT_SLOT:    return "sg_apply_uniforms: no uniform block declaration at this shader stage UB slot";
	case _sg_validate_error_t::_SG_VALIDATE_AUB_SIZE:             return "sg_apply_uniforms: data size exceeds declared uniform block size";

		/* sg_update_buffer */
	case _sg_validate_error_t::_SG_VALIDATE_UPDATEBUF_USAGE:      return "sg_update_buffer: cannot update immutable buffer";
	case _sg_validate_error_t::_SG_VALIDATE_UPDATEBUF_SIZE:       return "sg_update_buffer: update size is bigger than buffer size";
	case _sg_validate_error_t::_SG_VALIDATE_UPDATEBUF_ONCE:       return "sg_update_buffer: only one update allowed per buffer and frame";
	case _sg_validate_error_t::_SG_VALIDATE_UPDATEBUF_APPEND:     return "sg_update_buffer: cannot call sg_update_buffer and sg_append_buffer in same frame";

		/* sg_append_buffer */
	case _sg_validate_error_t::_SG_VALIDATE_APPENDBUF_USAGE:      return "sg_append_buffer: cannot append to immutable buffer";
	case _sg_validate_error_t::_SG_VALIDATE_APPENDBUF_SIZE:       return "sg_append_buffer: overall appended size is bigger than buffer size";
	case _sg_validate_error_t::_SG_VALIDATE_APPENDBUF_UPDATE:     return "sg_append_buffer: cannot call sg_append_buffer and sg_update_buffer in same frame";

		/* sg_update_image */
	case _sg_validate_error_t::_SG_VALIDATE_UPDIMG_USAGE:         return "sg_update_image: cannot update immutable image";
	case _sg_validate_error_t::_SG_VALIDATE_UPDIMG_NOTENOUGHDATA: return "sg_update_image: not enough subimage data provided";
	case _sg_validate_error_t::_SG_VALIDATE_UPDIMG_SIZE:          return "sg_update_image: provided subimage data size too big";
	case _sg_validate_error_t::_SG_VALIDATE_UPDIMG_COMPRESSED:    return "sg_update_image: cannot update images with compressed format";
	case _sg_validate_error_t::_SG_VALIDATE_UPDIMG_ONCE:          return "sg_update_image: only one update allowed per image and frame";

	default: return "unknown validation error";
	}
}



void _sg_validate_begin( void )
{
	_sg.validate_error = _SG_VALIDATE_SUCCESS;
}

void _sg_validate( bool cond, _sg_validate_error_t err )
{
	if( !cond )
	{
		_sg.validate_error = err;
		puts( _sg_validate_string( err ) );
	}
}

bool _sg_validate_end( void )
{
	if( _sg.validate_error != _SG_VALIDATE_SUCCESS )
	{
	#if !defined(_sg_validate_NON_FATAL)
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

bool _sg_validate_buffer_desc( const BufferDesc * desc )
{
	XE_ASSERT( desc );
	_sg_validate_begin();
	_sg_validate( desc->_start_canary == 0, _SG_VALIDATE_BUFFERDESC_CANARY );
	_sg_validate( desc->_end_canary == 0, _SG_VALIDATE_BUFFERDESC_CANARY );
	_sg_validate( desc->size > 0, _SG_VALIDATE_BUFFERDESC_SIZE );
	bool ext = ( 0 != desc->gl_buffers[0] ) || ( 0 != desc->mtl_buffers[0] ) || ( 0 != desc->d3d11_buffer );
	if( !ext && ( desc->usage == SG_USAGE_IMMUTABLE ) )
	{
		_sg_validate( 0 != desc->content, _SG_VALIDATE_BUFFERDESC_CONTENT );
	}
	else
	{
		_sg_validate( 0 == desc->content, _SG_VALIDATE_BUFFERDESC_NO_CONTENT );
	}
	return _sg_validate_end();
}

bool _sg_validate_image_desc( const ImageDesc * desc )
{
	XE_ASSERT( desc );
	_sg_validate_begin();
	_sg_validate( desc->_start_canary == 0, _SG_VALIDATE_IMAGEDESC_CANARY );
	_sg_validate( desc->_end_canary == 0, _SG_VALIDATE_IMAGEDESC_CANARY );
	_sg_validate( desc->width > 0, _SG_VALIDATE_IMAGEDESC_WIDTH );
	_sg_validate( desc->height > 0, _SG_VALIDATE_IMAGEDESC_HEIGHT );
	const PixelFormat fmt = desc->pixel_format;
	const Usage usage = desc->usage;
	const bool ext = ( 0 != desc->gl_textures[0] ) || ( 0 != desc->mtl_textures[0] ) || ( 0 != desc->d3d11_texture );
	if( desc->render_target )
	{
		XE_ASSERT( ( (int )fmt >= 0 ) && ( (int )fmt < _SG_PIXELFORMAT_NUM ) );
		_sg_validate( _sg.formats[fmt].render, _SG_VALIDATE_IMAGEDESC_RT_PIXELFORMAT );
		/* on GLES2, sample count for render targets is completely ignored */
	#if defined(SOKOL_GLES2) || defined(SOKOL_GLES3)
		if( !_sg.gl.gles2 )
		{
		#endif
			if( desc->sample_count > 1 )
			{
				_sg_validate( _sg.features.msaa_render_targets && _sg.formats[fmt].msaa, _SG_VALIDATE_IMAGEDESC_NO_MSAA_RT_SUPPORT );
			}
		#if defined(SOKOL_GLES2) || defined(SOKOL_GLES3)
		}
	#endif
		_sg_validate( usage == SG_USAGE_IMMUTABLE, _SG_VALIDATE_IMAGEDESC_RT_IMMUTABLE );
		_sg_validate( desc->content.subimage[0][0].ptr == 0, _SG_VALIDATE_IMAGEDESC_RT_NO_CONTENT );
	}
	else
	{
		_sg_validate( desc->sample_count <= 1, _SG_VALIDATE_IMAGEDESC_MSAA_BUT_NO_RT );
		const bool valid_nonrt_fmt = !_sg_is_valid_rendertarget_depth_format( fmt );
		_sg_validate( valid_nonrt_fmt, _SG_VALIDATE_IMAGEDESC_NONRT_PIXELFORMAT );
		/* FIXME: should use the same "expected size" computation as in _sg_validate_update_image() here */
		if( !ext && ( usage == SG_USAGE_IMMUTABLE ) )
		{
			const int num_faces = desc->type == SG_IMAGETYPE_CUBE ? 6 : 1;
			const int num_mips = desc->num_mipmaps;
			for( int face_index = 0; face_index < num_faces; face_index++ )
			{
				for( int mip_index = 0; mip_index < num_mips; mip_index++ )
				{
					const bool has_data = desc->content.subimage[face_index][mip_index].ptr != 0;
					const bool has_size = desc->content.subimage[face_index][mip_index].size > 0;
					_sg_validate( has_data && has_size, _SG_VALIDATE_IMAGEDESC_CONTENT );
				}
			}
		}
		else
		{
			for( int face_index = 0; face_index < SG_CUBEFACE_NUM; face_index++ )
			{
				for( int mip_index = 0; mip_index < SG_MAX_MIPMAPS; mip_index++ )
				{
					const bool no_data = 0 == desc->content.subimage[face_index][mip_index].ptr;
					const bool no_size = 0 == desc->content.subimage[face_index][mip_index].size;
					_sg_validate( no_data && no_size, _SG_VALIDATE_IMAGEDESC_NO_CONTENT );
				}
			}
		}
	}
	return _sg_validate_end();
}

bool _sg_validate_shader_desc( const ShaderDesc * desc )
{
	XE_ASSERT( desc );
	_sg_validate_begin();
	_sg_validate( desc->_start_canary == 0, _SG_VALIDATE_SHADERDESC_CANARY );
	_sg_validate( desc->_end_canary == 0, _SG_VALIDATE_SHADERDESC_CANARY );
	_sg_validate( 0 != desc->attrs[0].name, _SG_VALIDATE_SHADERDESC_ATTR_NAMES );
	_sg_validate( 0 != desc->attrs[0].sem_name, _SG_VALIDATE_SHADERDESC_ATTR_SEMANTICS );
	_sg_validate( 0 != desc->vs.source, _SG_VALIDATE_SHADERDESC_SOURCE );
	_sg_validate( 0 != desc->fs.source, _SG_VALIDATE_SHADERDESC_SOURCE );

	for( int i = 0; i < SG_MAX_VERTEX_ATTRIBUTES; i++ )
	{
		if( desc->attrs[i].name )
		{
			_sg_validate( strlen( desc->attrs[i].name ) < _SG_STRING_SIZE, _SG_VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG );
		}
		if( desc->attrs[i].sem_name )
		{
			_sg_validate( strlen( desc->attrs[i].sem_name ) < _SG_STRING_SIZE, _SG_VALIDATE_SHADERDESC_ATTR_STRING_TOO_LONG );
		}
	}
	/* if shader byte code, the size must also be provided */
	if( 0 != desc->vs.byte_code )
	{
		_sg_validate( desc->vs.byte_code_size > 0, _SG_VALIDATE_SHADERDESC_NO_BYTECODE_SIZE );
	}
	if( 0 != desc->fs.byte_code )
	{
		_sg_validate( desc->fs.byte_code_size > 0, _SG_VALIDATE_SHADERDESC_NO_BYTECODE_SIZE );
	}
	for( int stage_index = 0; stage_index < SG_NUM_SHADER_STAGES; stage_index++ )
	{
		const ShaderStageDesc * stage_desc = ( stage_index == 0 ) ? &desc->vs : &desc->fs;
		bool uniform_blocks_continuous = true;
		for( int ub_index = 0; ub_index < SG_MAX_SHADERSTAGE_UBS; ub_index++ )
		{
			const ShaderUniformBlockDesc * ub_desc = &stage_desc->uniform_blocks[ub_index];
			if( ub_desc->size > 0 )
			{
				_sg_validate( uniform_blocks_continuous, _SG_VALIDATE_SHADERDESC_NO_CONT_UBS );
				bool uniforms_continuous = true;
				int uniform_offset = 0;
				int num_uniforms = 0;
				for( int u_index = 0; u_index < SG_MAX_UB_MEMBERS; u_index++ )
				{
					const ShaderUniformDesc * u_desc = &ub_desc->uniforms[u_index];
					if( u_desc->type != SG_UNIFORMTYPE_INVALID )
					{
						_sg_validate( uniforms_continuous, _SG_VALIDATE_SHADERDESC_NO_CONT_UB_MEMBERS );
						_sg_validate( u_desc->name, _SG_VALIDATE_SHADERDESC_UB_MEMBER_NAME );
						const int array_count = u_desc->array_count;
						uniform_offset += _sg_uniform_size( u_desc->type, array_count );
						num_uniforms++;
					}
					else
					{
						uniforms_continuous = false;
					}
				}
				_sg_validate( uniform_offset == ub_desc->size, _SG_VALIDATE_SHADERDESC_UB_SIZE_MISMATCH );
				_sg_validate( num_uniforms > 0, _SG_VALIDATE_SHADERDESC_NO_UB_MEMBERS );
			}
			else
			{
				uniform_blocks_continuous = false;
			}
		}
		bool images_continuous = true;
		for( int img_index = 0; img_index < SG_MAX_SHADERSTAGE_IMAGES; img_index++ )
		{
			const ShaderImageDesc * img_desc = &stage_desc->images[img_index];
			if( img_desc->type != _SG_IMAGETYPE_DEFAULT )
			{
				_sg_validate( images_continuous, _SG_VALIDATE_SHADERDESC_NO_CONT_IMGS );
				_sg_validate( img_desc->name, _SG_VALIDATE_SHADERDESC_IMG_NAME );
			}
			else
			{
				images_continuous = false;
			}
		}
	}
	return _sg_validate_end();
}

bool _sg_validate_pipeline_desc( const PipelineDesc * desc )
{
	XE_ASSERT( desc );
	_sg_validate_begin();
	_sg_validate( desc->_start_canary == 0, _SG_VALIDATE_PIPELINEDESC_CANARY );
	_sg_validate( desc->_end_canary == 0, _SG_VALIDATE_PIPELINEDESC_CANARY );
	_sg_validate( desc->shader, _SG_VALIDATE_PIPELINEDESC_SHADER );
	const _sg_shader_t * shd = _sg_lookup_shader( &_sg.pools, desc->shader.GetValue() );
	_sg_validate( shd && shd->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_PIPELINEDESC_SHADER );
	for( int buf_index = 0; buf_index < SG_MAX_SHADERSTAGE_BUFFERS; buf_index++ )
	{
		const BufferLayoutDesc * l_desc = &desc->layout.buffers[buf_index];
		if( l_desc->stride == 0 )
		{
			continue;
		}
		_sg_validate( ( l_desc->stride & 3 ) == 0, _SG_VALIDATE_PIPELINEDESC_LAYOUT_STRIDE4 );
	}
	_sg_validate( desc->layout.attrs[0].format != SG_VERTEXFORMAT_INVALID, _SG_VALIDATE_PIPELINEDESC_NO_ATTRS );
	bool attrs_cont = true;
	for( int attr_index = 0; attr_index < SG_MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		const VertexAttrDesc * a_desc = &desc->layout.attrs[attr_index];
		if( a_desc->format == SG_VERTEXFORMAT_INVALID )
		{
			attrs_cont = false;
			continue;
		}
		_sg_validate( attrs_cont, _SG_VALIDATE_PIPELINEDESC_NO_ATTRS );
		XE_ASSERT( a_desc->buffer_index < SG_MAX_SHADERSTAGE_BUFFERS );
	#if defined(SOKOL_GLES2)
		/* on GLES2, vertex attribute names must be provided */
		_sg_validate( shd->attrs[attr_index].name != "", _SG_VALIDATE_PIPELINEDESC_ATTR_NAME );
	#elif defined(SOKOL_D3D11)
		/* on D3D11, semantic names (and semantic indices) must be provided */
		_sg_validate( shd->d3d11.attrs[attr_index].sem_name != "", _SG_VALIDATE_PIPELINEDESC_ATTR_SEMANTICS );
	#endif
	}
	return _sg_validate_end();
}

bool _sg_validate_pass_desc( const PassDesc * desc )
{
	XE_ASSERT( desc );
	_sg_validate_begin();
	_sg_validate( desc->_start_canary == 0, _SG_VALIDATE_PASSDESC_CANARY );
	_sg_validate( desc->_end_canary == 0, _SG_VALIDATE_PASSDESC_CANARY );
	bool atts_cont = true;
	PixelFormat color_fmt = SG_PIXELFORMAT_NONE;
	int width = -1, height = -1, sample_count = -1;
	for( int att_index = 0; att_index < SG_MAX_COLOR_ATTACHMENTS; att_index++ )
	{
		const AttachmentDesc * att = &desc->color_attachments[att_index];
		if( att->image )
		{
			_sg_validate( att_index > 0, _SG_VALIDATE_PASSDESC_NO_COLOR_ATTS );
			atts_cont = false;
			continue;
		}
		_sg_validate( atts_cont, _SG_VALIDATE_PASSDESC_NO_CONT_COLOR_ATTS );
		const _sg_image_t * img = _sg_lookup_image( &_sg.pools, att->image.GetValue() );
		_sg_validate( img && img->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_PASSDESC_IMAGE );
		_sg_validate( att->mip_level < img->cmn.num_mipmaps, _SG_VALIDATE_PASSDESC_MIPLEVEL );
		if( img->cmn.type == SG_IMAGETYPE_CUBE )
		{
			_sg_validate( att->face < 6, _SG_VALIDATE_PASSDESC_FACE );
		}
		else if( img->cmn.type == SG_IMAGETYPE_ARRAY )
		{
			_sg_validate( att->layer < img->cmn.depth, _SG_VALIDATE_PASSDESC_LAYER );
		}
		else if( img->cmn.type == SG_IMAGETYPE_3D )
		{
			_sg_validate( att->slice < img->cmn.depth, _SG_VALIDATE_PASSDESC_SLICE );
		}
		_sg_validate( img->cmn.render_target, _SG_VALIDATE_PASSDESC_IMAGE_NO_RT );
		if( att_index == 0 )
		{
			color_fmt = img->cmn.pixel_format;
			width = img->cmn.width >> att->mip_level;
			height = img->cmn.height >> att->mip_level;
			sample_count = img->cmn.sample_count;
		}
		else
		{
			_sg_validate( img->cmn.pixel_format == color_fmt, _SG_VALIDATE_PASSDESC_COLOR_PIXELFORMATS );
			_sg_validate( width == img->cmn.width >> att->mip_level, _SG_VALIDATE_PASSDESC_IMAGE_SIZES );
			_sg_validate( height == img->cmn.height >> att->mip_level, _SG_VALIDATE_PASSDESC_IMAGE_SIZES );
			_sg_validate( sample_count == img->cmn.sample_count, _SG_VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS );
		}
		_sg_validate( _sg_is_valid_rendertarget_color_format( img->cmn.pixel_format ), _SG_VALIDATE_PASSDESC_COLOR_INV_PIXELFORMAT );
	}
	if( desc->depth_stencil_attachment.image )
	{
		const AttachmentDesc * att = &desc->depth_stencil_attachment;
		const _sg_image_t * img = _sg_lookup_image( &_sg.pools, att->image.GetValue() );
		_sg_validate( img && img->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_PASSDESC_IMAGE );
		_sg_validate( att->mip_level < img->cmn.num_mipmaps, _SG_VALIDATE_PASSDESC_MIPLEVEL );
		if( img->cmn.type == SG_IMAGETYPE_CUBE )
		{
			_sg_validate( att->face < 6, _SG_VALIDATE_PASSDESC_FACE );
		}
		else if( img->cmn.type == SG_IMAGETYPE_ARRAY )
		{
			_sg_validate( att->layer < img->cmn.depth, _SG_VALIDATE_PASSDESC_LAYER );
		}
		else if( img->cmn.type == SG_IMAGETYPE_3D )
		{
			_sg_validate( att->slice < img->cmn.depth, _SG_VALIDATE_PASSDESC_SLICE );
		}
		_sg_validate( img->cmn.render_target, _SG_VALIDATE_PASSDESC_IMAGE_NO_RT );
		_sg_validate( width == img->cmn.width >> att->mip_level, _SG_VALIDATE_PASSDESC_IMAGE_SIZES );
		_sg_validate( height == img->cmn.height >> att->mip_level, _SG_VALIDATE_PASSDESC_IMAGE_SIZES );
		_sg_validate( sample_count == img->cmn.sample_count, _SG_VALIDATE_PASSDESC_IMAGE_SAMPLE_COUNTS );
		_sg_validate( _sg_is_valid_rendertarget_depth_format( img->cmn.pixel_format ), _SG_VALIDATE_PASSDESC_DEPTH_INV_PIXELFORMAT );
	}
	return _sg_validate_end();
}

bool _sg_validate_begin_pass( _sg_pass_t * pass )
{
	_sg_validate_begin();
	_sg_validate( pass->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_BEGINPASS_PASS );

	for( int i = 0; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
	{
		const _sg_attachment_t * att = &pass->cmn.color_atts[i];
		const _sg_image_t * img = _sg_pass_color_image( pass, i );
		if( img )
		{
			_sg_validate( img->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_BEGINPASS_IMAGE );
			_sg_validate( img->slot.id == att->image_id.GetValue(), _SG_VALIDATE_BEGINPASS_IMAGE );
		}
	}
	const _sg_image_t * ds_img = _sg_pass_ds_image( pass );
	if( ds_img )
	{
		const _sg_attachment_t * att = &pass->cmn.ds_att;
		_sg_validate( ds_img->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_BEGINPASS_IMAGE );
		_sg_validate( ds_img->slot.id == att->image_id.GetValue(), _SG_VALIDATE_BEGINPASS_IMAGE );
	}
	return _sg_validate_end();
}

bool _sg_validate_apply_pipeline( PipelineHandle pip_id )
{
	_sg_validate_begin();
	/* the pipeline object must be alive and valid */
	_sg_validate( pip_id, _SG_VALIDATE_APIP_PIPELINE_VALID_ID );
	const _sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	_sg_validate( pip != 0, _SG_VALIDATE_APIP_PIPELINE_EXISTS );
	if( !pip )
	{
		return _sg_validate_end();
	}
	_sg_validate( pip->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_APIP_PIPELINE_VALID );
	/* the pipeline's shader must be alive and valid */
	XE_ASSERT( pip->shader );
	_sg_validate( pip->shader->slot.id == pip->cmn.shader_id.GetValue(), _SG_VALIDATE_APIP_SHADER_EXISTS );
	_sg_validate( pip->shader->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_APIP_SHADER_VALID );
	/* check that pipeline attributes match current pass attributes */
	const _sg_pass_t * pass = _sg_lookup_pass( &_sg.pools, _sg.cur_pass.GetValue() );
	if( pass )
	{
		/* an offscreen pass */
		const _sg_image_t * att_img = _sg_pass_color_image( pass, 0 );
		_sg_validate( pip->cmn.color_attachment_count == pass->cmn.num_color_atts, _SG_VALIDATE_APIP_ATT_COUNT );
		_sg_validate( pip->cmn.color_format == att_img->cmn.pixel_format, _SG_VALIDATE_APIP_COLOR_FORMAT );
		_sg_validate( pip->cmn.sample_count == att_img->cmn.sample_count, _SG_VALIDATE_APIP_SAMPLE_COUNT );
		const _sg_image_t * att_dsimg = _sg_pass_ds_image( pass );
		if( att_dsimg )
		{
			_sg_validate( pip->cmn.depth_format == att_dsimg->cmn.pixel_format, _SG_VALIDATE_APIP_DEPTH_FORMAT );
		}
		else
		{
			_sg_validate( pip->cmn.depth_format == SG_PIXELFORMAT_NONE, _SG_VALIDATE_APIP_DEPTH_FORMAT );
		}
	}
	else
	{
		/* default pass */
		_sg_validate( pip->cmn.color_attachment_count == 1, _SG_VALIDATE_APIP_ATT_COUNT );
		_sg_validate( pip->cmn.color_format == _sg_default_rendertarget_colorformat(), _SG_VALIDATE_APIP_COLOR_FORMAT );
		_sg_validate( pip->cmn.depth_format == _sg_default_rendertarget_depthformat(), _SG_VALIDATE_APIP_DEPTH_FORMAT );
		/* FIXME: hmm, we don't know if the default framebuffer is multisampled here */
	}
	return _sg_validate_end();
}

bool _sg_validate_apply_bindings( const Bindings * bindings )
{
	_sg_validate_begin();

	/* a pipeline object must have been applied */
	_sg_validate( _sg.cur_pipeline, _SG_VALIDATE_ABND_PIPELINE );
	const _sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, _sg.cur_pipeline.GetValue() );
	_sg_validate( pip != 0, _SG_VALIDATE_ABND_PIPELINE_EXISTS );
	if( !pip )
	{
		return _sg_validate_end();
	}
	_sg_validate( pip->slot.state == SG_RESOURCESTATE_VALID, _SG_VALIDATE_ABND_PIPELINE_VALID );
	XE_ASSERT( pip->shader );

	/* has expected vertex buffers, and vertex buffers still exist */
	for( int i = 0; i < SG_MAX_SHADERSTAGE_BUFFERS; i++ )
	{
		if( bindings->vertex_buffers[i] )
		{
			_sg_validate( pip->cmn.vertex_layout_valid[i], _SG_VALIDATE_ABND_VBS );
			/* buffers in vertex-buffer-slots must be of type SG_BUFFERTYPE_VERTEXBUFFER */
			const _sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, bindings->vertex_buffers[i].GetValue() );
			_sg_validate( buf != 0, _SG_VALIDATE_ABND_VB_EXISTS );
			if( buf && buf->slot.state == SG_RESOURCESTATE_VALID )
			{
				_sg_validate( SG_BUFFERTYPE_VERTEXBUFFER == buf->cmn.type, _SG_VALIDATE_ABND_VB_TYPE );
				_sg_validate( !buf->cmn.append_overflow, _SG_VALIDATE_ABND_VB_OVERFLOW );
			}
		}
		else
		{
			/* vertex buffer provided in a slot which has no vertex layout in pipeline */
			_sg_validate( !pip->cmn.vertex_layout_valid[i], _SG_VALIDATE_ABND_VBS );
		}
	}

	/* index buffer expected or not, and index buffer still exists */
	if( pip->cmn.index_type == SG_INDEXTYPE_NONE )
	{
		/* pipeline defines non-indexed rendering, but index buffer provided */
		_sg_validate( bindings->index_buffer == XE::BufferHandle::Invalid, _SG_VALIDATE_ABND_IB );
	}
	else
	{
		/* pipeline defines indexed rendering, but no index buffer provided */
		_sg_validate( bindings->index_buffer, _SG_VALIDATE_ABND_NO_IB );
	}
	if( bindings->index_buffer )
	{
		/* buffer in index-buffer-slot must be of type SG_BUFFERTYPE_INDEXBUFFER */
		const _sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, bindings->index_buffer.GetValue() );
		_sg_validate( buf != 0, _SG_VALIDATE_ABND_IB_EXISTS );
		if( buf && buf->slot.state == SG_RESOURCESTATE_VALID )
		{
			_sg_validate( SG_BUFFERTYPE_INDEXBUFFER == buf->cmn.type, _SG_VALIDATE_ABND_IB_TYPE );
			_sg_validate( !buf->cmn.append_overflow, _SG_VALIDATE_ABND_IB_OVERFLOW );
		}
	}

	/* has expected vertex shader images */
	for( int i = 0; i < SG_MAX_SHADERSTAGE_IMAGES; i++ )
	{
		_sg_shader_stage_t * stage = &pip->shader->cmn.stage[SG_SHADERSTAGE_VS];
		if( bindings->vs_images[i] )
		{
			_sg_validate( i < stage->num_images, _SG_VALIDATE_ABND_VS_IMGS );
			const _sg_image_t * img = _sg_lookup_image( &_sg.pools, bindings->vs_images[i].GetValue() );
			_sg_validate( img != 0, _SG_VALIDATE_ABND_VS_IMG_EXISTS );
			if( img && img->slot.state == SG_RESOURCESTATE_VALID )
			{
				_sg_validate( img->cmn.type == stage->images[i].type, _SG_VALIDATE_ABND_VS_IMG_TYPES );
			}
		}
		else
		{
			_sg_validate( i >= stage->num_images, _SG_VALIDATE_ABND_VS_IMGS );
		}
	}

	/* has expected fragment shader images */
	for( int i = 0; i < SG_MAX_SHADERSTAGE_IMAGES; i++ )
	{
		_sg_shader_stage_t * stage = &pip->shader->cmn.stage[SG_SHADERSTAGE_FS];
		if( bindings->fs_images[i] )
		{
			_sg_validate( i < stage->num_images, _SG_VALIDATE_ABND_FS_IMGS );
			const _sg_image_t * img = _sg_lookup_image( &_sg.pools, bindings->fs_images[i].GetValue() );
			_sg_validate( img != 0, _SG_VALIDATE_ABND_FS_IMG_EXISTS );
			if( img && img->slot.state == SG_RESOURCESTATE_VALID )
			{
				_sg_validate( img->cmn.type == stage->images[i].type, _SG_VALIDATE_ABND_FS_IMG_TYPES );
			}
		}
		else
		{
			_sg_validate( i >= stage->num_images, _SG_VALIDATE_ABND_FS_IMGS );
		}
	}
	return _sg_validate_end();
}

bool _sg_validate_apply_uniforms( ShaderStage stage_index, int ub_index, const void * data, int num_bytes )
{
	XE_ASSERT( ( stage_index == SG_SHADERSTAGE_VS ) || ( stage_index == SG_SHADERSTAGE_FS ) );
	XE_ASSERT( ( ub_index >= 0 ) && ( ub_index < SG_MAX_SHADERSTAGE_UBS ) );
	_sg_validate_begin();
	_sg_validate( _sg.cur_pipeline, _SG_VALIDATE_AUB_NO_PIPELINE );
	const _sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, _sg.cur_pipeline.GetValue() );
	XE_ASSERT( pip && ( pip->slot.id == _sg.cur_pipeline.GetValue() ) );
	XE_ASSERT( pip->shader && ( pip->shader->slot.id == pip->cmn.shader_id.GetValue() ) );

	/* check that there is a uniform block at 'stage' and 'ub_index' */
	const _sg_shader_stage_t * stage = &pip->shader->cmn.stage[stage_index];
	_sg_validate( ub_index < stage->num_uniform_blocks, _SG_VALIDATE_AUB_NO_UB_AT_SLOT );

	/* check that the provided data size doesn't exceed the uniform block size */
	_sg_validate( num_bytes <= stage->uniform_blocks[ub_index].size, _SG_VALIDATE_AUB_SIZE );

	return _sg_validate_end();
}

bool _sg_validate_update_buffer( const _sg_buffer_t * buf, const void * data, int size )
{
	XE_ASSERT( buf && data );
	_sg_validate_begin();
	_sg_validate( buf->cmn.usage != SG_USAGE_IMMUTABLE, _SG_VALIDATE_UPDATEBUF_USAGE );
	_sg_validate( buf->cmn.size >= size, _SG_VALIDATE_UPDATEBUF_SIZE );
	_sg_validate( buf->cmn.update_frame_index != _sg.frame_index, _SG_VALIDATE_UPDATEBUF_ONCE );
	_sg_validate( buf->cmn.append_frame_index != _sg.frame_index, _SG_VALIDATE_UPDATEBUF_APPEND );
	return _sg_validate_end();
}

bool _sg_validate_append_buffer( const _sg_buffer_t * buf, const void * data, int size )
{
	XE_ASSERT( buf && data );
	_sg_validate_begin();
	_sg_validate( buf->cmn.usage != SG_USAGE_IMMUTABLE, _SG_VALIDATE_APPENDBUF_USAGE );
	_sg_validate( buf->cmn.size >= ( buf->cmn.append_pos + size ), _SG_VALIDATE_APPENDBUF_SIZE );
	_sg_validate( buf->cmn.update_frame_index != _sg.frame_index, _SG_VALIDATE_APPENDBUF_UPDATE );
	return _sg_validate_end();
}

bool _sg_validate_update_image( const _sg_image_t * img, const ImageContent * data )
{
	XE_ASSERT( img && data );
	_sg_validate_begin();
	_sg_validate( img->cmn.usage != SG_USAGE_IMMUTABLE, _SG_VALIDATE_UPDIMG_USAGE );
	_sg_validate( img->cmn.upd_frame_index != _sg.frame_index, _SG_VALIDATE_UPDIMG_ONCE );
	_sg_validate( !_sg_is_compressed_pixel_format( img->cmn.pixel_format ), _SG_VALIDATE_UPDIMG_COMPRESSED );
	const int num_faces = ( img->cmn.type == SG_IMAGETYPE_CUBE ) ? 6 : 1;
	const int num_mips = img->cmn.num_mipmaps;
	for( int face_index = 0; face_index < num_faces; face_index++ )
	{
		for( int mip_index = 0; mip_index < num_mips; mip_index++ )
		{
			_sg_validate( 0 != data->subimage[face_index][mip_index].ptr, _SG_VALIDATE_UPDIMG_NOTENOUGHDATA );
			const int mip_width = _sg_max( img->cmn.width >> mip_index, 1 );
			const int mip_height = _sg_max( img->cmn.height >> mip_index, 1 );
			const int bytes_per_slice = _sg_surface_pitch( img->cmn.pixel_format, mip_width, mip_height );
			const int expected_size = bytes_per_slice * img->cmn.depth;
			_sg_validate( data->subimage[face_index][mip_index].size <= expected_size, _SG_VALIDATE_UPDIMG_SIZE );
		}
	}
	return _sg_validate_end();
}



BufferDesc _Buffer_desc_defaults( const BufferDesc * desc )
{
	BufferDesc def = *desc;
	def.type = _sg_def( def.type, SG_BUFFERTYPE_VERTEXBUFFER );
	def.usage = _sg_def( def.usage, SG_USAGE_IMMUTABLE );
	return def;
}

ImageDesc _sg_image_desc_defaults( const ImageDesc * desc )
{
	ImageDesc def = *desc;
	def.type = _sg_def( def.type, SG_IMAGETYPE_2D );
	def.depth = _sg_def( def.depth, 1 );
	def.num_mipmaps = _sg_def( def.num_mipmaps, 1 );
	def.usage = _sg_def( def.usage, SG_USAGE_IMMUTABLE );
	if( desc->render_target )
	{
		def.pixel_format = _sg_def( def.pixel_format, _sg_default_rendertarget_colorformat() );
	}
	else
	{
		def.pixel_format = _sg_def( def.pixel_format, SG_PIXELFORMAT_RGBA8 );
	}
	def.sample_count = _sg_def( def.sample_count, 1 );
	def.min_filter = _sg_def( def.min_filter, SG_FILTER_NEAREST );
	def.mag_filter = _sg_def( def.mag_filter, SG_FILTER_NEAREST );
	def.wrap_u = _sg_def( def.wrap_u, SG_WRAP_REPEAT );
	def.wrap_v = _sg_def( def.wrap_v, SG_WRAP_REPEAT );
	def.wrap_w = _sg_def( def.wrap_w, SG_WRAP_REPEAT );
	def.border_color = _sg_def( def.border_color, SG_BORDERCOLOR_OPAQUE_BLACK );
	def.max_anisotropy = _sg_def( def.max_anisotropy, 1 );
	def.max_lod = _sg_def_flt( def.max_lod, FLT_MAX );
	return def;
}

ShaderDesc _sg_shader_desc_defaults( const ShaderDesc * desc )
{
	ShaderDesc def = *desc;
#if defined(SOKOL_METAL)
	def.vs.entry = _sg_def( def.vs.entry, "_main" );
	def.fs.entry = _sg_def( def.fs.entry, "_main" );
#else
	def.vs.entry = _sg_def( def.vs.entry, "main" );
	def.fs.entry = _sg_def( def.fs.entry, "main" );
#endif
	for( int stage_index = 0; stage_index < SG_NUM_SHADER_STAGES; stage_index++ )
	{
		ShaderStageDesc * stage_desc = ( stage_index == SG_SHADERSTAGE_VS ) ? &def.vs : &def.fs;
		for( int ub_index = 0; ub_index < SG_MAX_SHADERSTAGE_UBS; ub_index++ )
		{
			ShaderUniformBlockDesc * ub_desc = &stage_desc->uniform_blocks[ub_index];
			if( 0 == ub_desc->size )
			{
				break;
			}
			for( int u_index = 0; u_index < SG_MAX_UB_MEMBERS; u_index++ )
			{
				ShaderUniformDesc * u_desc = &ub_desc->uniforms[u_index];
				if( u_desc->type == SG_UNIFORMTYPE_INVALID )
				{
					break;
				}
				u_desc->array_count = _sg_def( u_desc->array_count, 1 );
			}
		}
	}
	return def;
}

PipelineDesc _sg_pipeline_desc_defaults( const PipelineDesc * desc )
{
	PipelineDesc def = *desc;

	def.primitive_type = _sg_def( def.primitive_type, SG_PRIMITIVETYPE_TRIANGLES );
	def.index_type = _sg_def( def.index_type, SG_INDEXTYPE_NONE );

	def.depth_stencil.stencil_front.fail_op = _sg_def( def.depth_stencil.stencil_front.fail_op, SG_STENCILOP_KEEP );
	def.depth_stencil.stencil_front.depth_fail_op = _sg_def( def.depth_stencil.stencil_front.depth_fail_op, SG_STENCILOP_KEEP );
	def.depth_stencil.stencil_front.pass_op = _sg_def( def.depth_stencil.stencil_front.pass_op, SG_STENCILOP_KEEP );
	def.depth_stencil.stencil_front.compare_func = _sg_def( def.depth_stencil.stencil_front.compare_func, SG_COMPAREFUNC_ALWAYS );
	def.depth_stencil.stencil_back.fail_op = _sg_def( def.depth_stencil.stencil_back.fail_op, SG_STENCILOP_KEEP );
	def.depth_stencil.stencil_back.depth_fail_op = _sg_def( def.depth_stencil.stencil_back.depth_fail_op, SG_STENCILOP_KEEP );
	def.depth_stencil.stencil_back.pass_op = _sg_def( def.depth_stencil.stencil_back.pass_op, SG_STENCILOP_KEEP );
	def.depth_stencil.stencil_back.compare_func = _sg_def( def.depth_stencil.stencil_back.compare_func, SG_COMPAREFUNC_ALWAYS );
	def.depth_stencil.depth_compare_func = _sg_def( def.depth_stencil.depth_compare_func, SG_COMPAREFUNC_ALWAYS );

	def.blend.src_factor_rgb = _sg_def( def.blend.src_factor_rgb, SG_BLENDFACTOR_ONE );
	def.blend.dst_factor_rgb = _sg_def( def.blend.dst_factor_rgb, SG_BLENDFACTOR_ZERO );
	def.blend.op_rgb = _sg_def( def.blend.op_rgb, SG_BLENDOP_ADD );
	def.blend.src_factor_alpha = _sg_def( def.blend.src_factor_alpha, SG_BLENDFACTOR_ONE );
	def.blend.dst_factor_alpha = _sg_def( def.blend.dst_factor_alpha, SG_BLENDFACTOR_ZERO );
	def.blend.op_alpha = _sg_def( def.blend.op_alpha, SG_BLENDOP_ADD );
	if( def.blend.color_write_mask == SG_COLORMASK_NONE )
	{
		def.blend.color_write_mask = 0;
	}
	else
	{
		def.blend.color_write_mask = (uint8_t )_sg_def( (ColorMask )def.blend.color_write_mask, SG_COLORMASK_RGBA );
	}
	def.blend.color_attachment_count = _sg_def( def.blend.color_attachment_count, 1 );
	def.blend.color_format = _sg_def( def.blend.color_format, _sg_default_rendertarget_colorformat() );
	def.blend.depth_format = _sg_def( def.blend.depth_format, _sg_default_rendertarget_depthformat() );

	def.rasterizer.cull_mode = _sg_def( def.rasterizer.cull_mode, SG_CULLMODE_NONE );
	def.rasterizer.face_winding = _sg_def( def.rasterizer.face_winding, SG_FACEWINDING_CW );
	def.rasterizer.sample_count = _sg_def( def.rasterizer.sample_count, 1 );

	for( int attr_index = 0; attr_index < SG_MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		VertexAttrDesc * a_desc = &def.layout.attrs[attr_index];
		if( a_desc->format == SG_VERTEXFORMAT_INVALID )
		{
			break;
		}
		XE_ASSERT( ( a_desc->buffer_index >= 0 ) && ( a_desc->buffer_index < SG_MAX_SHADERSTAGE_BUFFERS ) );
		BufferLayoutDesc * b_desc = &def.layout.buffers[a_desc->buffer_index];
		b_desc->step_func = _sg_def( b_desc->step_func, SG_VERTEXSTEP_PER_VERTEX );
		b_desc->step_rate = _sg_def( b_desc->step_rate, 1 );
	}

	/* resolve vertex layout strides and offsets */
	int auto_offset[SG_MAX_SHADERSTAGE_BUFFERS];
	memset( auto_offset, 0, sizeof( auto_offset ) );
	bool use_auto_offset = true;
	for( int attr_index = 0; attr_index < SG_MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		/* to use computed offsets, *all* attr offsets must be 0 */
		if( def.layout.attrs[attr_index].offset != 0 )
		{
			use_auto_offset = false;
		}
	}
	for( int attr_index = 0; attr_index < SG_MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		VertexAttrDesc * a_desc = &def.layout.attrs[attr_index];
		if( a_desc->format == SG_VERTEXFORMAT_INVALID )
		{
			break;
		}
		XE_ASSERT( ( a_desc->buffer_index >= 0 ) && ( a_desc->buffer_index < SG_MAX_SHADERSTAGE_BUFFERS ) );
		if( use_auto_offset )
		{
			a_desc->offset = auto_offset[a_desc->buffer_index];
		}
		auto_offset[a_desc->buffer_index] += _sg_vertexformat_bytesize( a_desc->format );
	}
	/* compute vertex strides if needed */
	for( int buf_index = 0; buf_index < SG_MAX_SHADERSTAGE_BUFFERS; buf_index++ )
	{
		BufferLayoutDesc * l_desc = &def.layout.buffers[buf_index];
		if( l_desc->stride == 0 )
		{
			l_desc->stride = auto_offset[buf_index];
		}
	}

	return def;
}

PassDesc _sg_pass_desc_defaults( const PassDesc * desc )
{
	/* FIXME: no values to replace in PassDesc? */
	PassDesc def = *desc;
	return def;
}



BufferHandle _sg_alloc_buffer( void )
{
	BufferHandle res;
	int slot_index = _sg_pool_alloc_index( &_sg.pools.buffer_pool );
	if( SG_INVALID_SLOT_INDEX != slot_index )
	{
		res = _sg_slot_alloc( &_sg.pools.buffer_pool, &_sg.pools.buffers[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::BufferHandle::Invalid;
	}
	return res;
}

ImageHandle _sg_alloc_image( void )
{
	ImageHandle res;
	int slot_index = _sg_pool_alloc_index( &_sg.pools.image_pool );
	if( SG_INVALID_SLOT_INDEX != slot_index )
	{
		res = _sg_slot_alloc( &_sg.pools.image_pool, &_sg.pools.images[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::ImageHandle::Invalid;
	}
	return res;
}

ShaderHandle _sg_alloc_shader( void )
{
	ShaderHandle res;
	int slot_index = _sg_pool_alloc_index( &_sg.pools.shader_pool );
	if( SG_INVALID_SLOT_INDEX != slot_index )
	{
		res = _sg_slot_alloc( &_sg.pools.shader_pool, &_sg.pools.shaders[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::ShaderHandle::Invalid;
	}
	return res;
}

PipelineHandle _sg_alloc_pipeline( void )
{
	PipelineHandle res;
	int slot_index = _sg_pool_alloc_index( &_sg.pools.pipeline_pool );
	if( SG_INVALID_SLOT_INDEX != slot_index )
	{
		res = _sg_slot_alloc( &_sg.pools.pipeline_pool, &_sg.pools.pipelines[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::PipelineHandle::Invalid;
	}
	return res;
}

PassHandle _sg_alloc_pass( void )
{
	PassHandle res;
	int slot_index = _sg_pool_alloc_index( &_sg.pools.pass_pool );
	if( SG_INVALID_SLOT_INDEX != slot_index )
	{
		res = _sg_slot_alloc( &_sg.pools.pass_pool, &_sg.pools.passes[slot_index].slot, slot_index );
	}
	else
	{
		/* pool is exhausted */
		res = XE::PassHandle::Invalid;
	}
	return res;
}

void _sg_init_buffer( BufferHandle buf_id, const BufferDesc * desc )
{
	XE_ASSERT( buf_id && desc );
	_sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
	XE_ASSERT( buf && buf->slot.state == SG_RESOURCESTATE_ALLOC );
	buf->slot.ctx_id = _sg.active_context.GetValue();
	if( _sg_validate_buffer_desc( desc ) )
	{
		buf->slot.state = _sg_create_buffer( buf, desc );
	}
	else
	{
		buf->slot.state = SG_RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( buf->slot.state == SG_RESOURCESTATE_VALID ) || ( buf->slot.state == SG_RESOURCESTATE_FAILED ) );
}

void _sg_init_image( ImageHandle img_id, const ImageDesc * desc )
{
	XE_ASSERT( img_id && desc );
	_sg_image_t * img = _sg_lookup_image( &_sg.pools, img_id.GetValue() );
	XE_ASSERT( img && img->slot.state == SG_RESOURCESTATE_ALLOC );
	img->slot.ctx_id = _sg.active_context.GetValue();
	if( _sg_validate_image_desc( desc ) )
	{
		img->slot.state = _sg_create_image( img, desc );
	}
	else
	{
		img->slot.state = SG_RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( img->slot.state == SG_RESOURCESTATE_VALID ) || ( img->slot.state == SG_RESOURCESTATE_FAILED ) );
}

void _sg_init_shader( ShaderHandle shd_id, const ShaderDesc * desc )
{
	XE_ASSERT( shd_id && desc );
	_sg_shader_t * shd = _sg_lookup_shader( &_sg.pools, shd_id.GetValue() );
	XE_ASSERT( shd && shd->slot.state == SG_RESOURCESTATE_ALLOC );
	shd->slot.ctx_id = _sg.active_context.GetValue();
	if( _sg_validate_shader_desc( desc ) )
	{
		shd->slot.state = _sg_create_shader( shd, desc );
	}
	else
	{
		shd->slot.state = SG_RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( shd->slot.state == SG_RESOURCESTATE_VALID ) || ( shd->slot.state == SG_RESOURCESTATE_FAILED ) );
}

void _sg_init_pipeline( PipelineHandle pip_id, const PipelineDesc * desc )
{
	XE_ASSERT( pip_id && desc );
	_sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	XE_ASSERT( pip && pip->slot.state == SG_RESOURCESTATE_ALLOC );
	pip->slot.ctx_id = _sg.active_context.GetValue();
	if( _sg_validate_pipeline_desc( desc ) )
	{
		_sg_shader_t * shd = _sg_lookup_shader( &_sg.pools, desc->shader.GetValue() );
		XE_ASSERT( shd && shd->slot.state == SG_RESOURCESTATE_VALID );
		pip->slot.state = _sg_create_pipeline( pip, shd, desc );
	}
	else
	{
		pip->slot.state = SG_RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( pip->slot.state == SG_RESOURCESTATE_VALID ) || ( pip->slot.state == SG_RESOURCESTATE_FAILED ) );
}

void _sg_init_pass( PassHandle pass_id, const PassDesc * desc )
{
	XE_ASSERT( pass_id && desc );
	_sg_pass_t * pass = _sg_lookup_pass( &_sg.pools, pass_id.GetValue() );
	XE_ASSERT( pass && pass->slot.state == SG_RESOURCESTATE_ALLOC );
	pass->slot.ctx_id = _sg.active_context.GetValue();
	if( _sg_validate_pass_desc( desc ) )
	{
		/* lookup pass attachment image pointers */
		_sg_image_t * att_imgs[SG_MAX_COLOR_ATTACHMENTS + 1];
		for( int i = 0; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
		{
			if( desc->color_attachments[i].image.GetValue() )
			{
				att_imgs[i] = _sg_lookup_image( &_sg.pools, desc->color_attachments[i].image.GetValue() );
				XE_ASSERT( att_imgs[i] && att_imgs[i]->slot.state == SG_RESOURCESTATE_VALID );
			}
			else
			{
				att_imgs[i] = 0;
			}
		}
		const int ds_att_index = SG_MAX_COLOR_ATTACHMENTS;
		if( desc->depth_stencil_attachment.image.GetValue() )
		{
			att_imgs[ds_att_index] = _sg_lookup_image( &_sg.pools, desc->depth_stencil_attachment.image.GetValue() );
			XE_ASSERT( att_imgs[ds_att_index] && att_imgs[ds_att_index]->slot.state == SG_RESOURCESTATE_VALID );
		}
		else
		{
			att_imgs[ds_att_index] = 0;
		}
		pass->slot.state = _sg_create_pass( pass, att_imgs, desc );
	}
	else
	{
		pass->slot.state = SG_RESOURCESTATE_FAILED;
	}
	XE_ASSERT( ( pass->slot.state == SG_RESOURCESTATE_VALID ) || ( pass->slot.state == SG_RESOURCESTATE_FAILED ) );
}






void Gfx::sg_setup( const GfxDesc * desc )
{
	XE_ASSERT( desc );
	XE_ASSERT( ( desc->_start_canary == 0 ) && ( desc->_end_canary == 0 ) );
	memset( &_sg, 0, sizeof( _sg ) );
	_sg.desc = *desc;

	/* replace zero-init items with their default values */
	_sg.desc.buffer_pool_size = _sg_def( _sg.desc.buffer_pool_size, _SG_DEFAULT_BUFFER_POOL_SIZE );
	_sg.desc.image_pool_size = _sg_def( _sg.desc.image_pool_size, _SG_DEFAULT_IMAGE_POOL_SIZE );
	_sg.desc.shader_pool_size = _sg_def( _sg.desc.shader_pool_size, _SG_DEFAULT_SHADER_POOL_SIZE );
	_sg.desc.pipeline_pool_size = _sg_def( _sg.desc.pipeline_pool_size, _SG_DEFAULT_PIPELINE_POOL_SIZE );
	_sg.desc.pass_pool_size = _sg_def( _sg.desc.pass_pool_size, _SG_DEFAULT_PASS_POOL_SIZE );
	_sg.desc.context_pool_size = _sg_def( _sg.desc.context_pool_size, _SG_DEFAULT_CONTEXT_POOL_SIZE );
	_sg.desc.mtl_global_uniform_buffer_size = _sg_def( _sg.desc.mtl_global_uniform_buffer_size, _SG_MTL_DEFAULT_UB_SIZE );
	_sg.desc.mtl_sampler_cache_size = _sg_def( _sg.desc.mtl_sampler_cache_size, _SG_MTL_DEFAULT_SAMPLER_CACHE_CAPACITY );

	_sg_setup_pools( &_sg.pools, &_sg.desc );
	_sg.frame_index = 1;
	_sg_setup_backend( &_sg.desc );
	_sg.valid = true;
	sg_setup_context();
}

void Gfx::sg_shutdown( void )
{
	if( _sg.active_context )
	{
		_sg_context_t * ctx = _sg_lookup_context( &_sg.pools, _sg.active_context.GetValue() );
		if( ctx )
		{
			_sg_destroy_all_resources( &_sg.pools, _sg.active_context.GetValue() );
			_sg_destroy_context( ctx );
		}
	}
	_sg_discard_backend();
	_sg_discard_pools( &_sg.pools );
	_sg.valid = false;
}

bool Gfx::sg_isvalid( void )
{
	return _sg.valid;
}

void Gfx::sg_reset_state_cache( void )
{
	XE_ASSERT( _sg.valid );
	_sg_reset_state_cache();
	_SG_TRACE_NOARGS( reset_state_cache );
}

GfxTraceHooks * Gfx::sg_install_trace_hooks( GfxTraceHooks * trace_hooks )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( trace_hooks );
	GfxTraceHooks * old_hooks = _sg.hooks;
	_sg.hooks = trace_hooks;
	return old_hooks;
}

void Gfx::sg_push_debug_group( const XE::String & name )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( name );
	_SG_TRACE_ARGS( push_debug_group, name );
}

void Gfx::sg_pop_debug_group( void )
{
	XE_ASSERT( _sg.valid );
	_SG_TRACE_NOARGS( pop_debug_group );
}

BufferHandle Gfx::sg_make_buffer( const BufferDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	BufferDesc desc_def = _Buffer_desc_defaults( desc );
	BufferHandle buf_id = _sg_alloc_buffer();
	if( buf_id )
	{
		_sg_init_buffer( buf_id, &desc_def );
	}
	else
	{
		puts( "buffer pool exhausted!" );
		_SG_TRACE_NOARGS( err_buffer_pool_exhausted );
	}
	_SG_TRACE_ARGS( make_buffer, &desc_def, buf_id );
	return buf_id;
}

ImageHandle Gfx::sg_make_image( const ImageDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	ImageDesc desc_def = _sg_image_desc_defaults( desc );
	ImageHandle img_id = _sg_alloc_image();
	if( img_id )
	{
		_sg_init_image( img_id, &desc_def );
	}
	else
	{
		puts( "image pool exhausted!" );
		_SG_TRACE_NOARGS( err_image_pool_exhausted );
	}
	_SG_TRACE_ARGS( make_image, &desc_def, img_id );
	return img_id;
}

ShaderHandle Gfx::sg_make_shader( const ShaderDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	ShaderDesc desc_def = _sg_shader_desc_defaults( desc );
	ShaderHandle shd_id = _sg_alloc_shader();
	if( shd_id )
	{
		_sg_init_shader( shd_id, &desc_def );
	}
	else
	{
		puts( "shader pool exhausted!" );
		_SG_TRACE_NOARGS( err_shader_pool_exhausted );
	}
	_SG_TRACE_ARGS( make_shader, &desc_def, shd_id );
	return shd_id;
}

PipelineHandle Gfx::sg_make_pipeline( const PipelineDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	PipelineDesc desc_def = _sg_pipeline_desc_defaults( desc );
	PipelineHandle pip_id = _sg_alloc_pipeline();
	if( pip_id )
	{
		_sg_init_pipeline( pip_id, &desc_def );
	}
	else
	{
		puts( "pipeline pool exhausted!" );
		_SG_TRACE_NOARGS( err_pipeline_pool_exhausted );
	}
	_SG_TRACE_ARGS( make_pipeline, &desc_def, pip_id );
	return pip_id;
}

PassHandle Gfx::sg_make_pass( const PassDesc * desc )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( desc );
	PassDesc desc_def = _sg_pass_desc_defaults( desc );
	PassHandle pass_id = _sg_alloc_pass();
	if( pass_id )
	{
		_sg_init_pass( pass_id, &desc_def );
	}
	else
	{
		puts( "pass pool exhausted!" );
		_SG_TRACE_NOARGS( err_pass_pool_exhausted );
	}
	_SG_TRACE_ARGS( make_pass, &desc_def, pass_id );
	return pass_id;
}

void Gfx::sg_destroy_buffer( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	_SG_TRACE_ARGS( destroy_buffer, buf_id );
	_sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
	if( buf )
	{
		if( buf->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_sg_destroy_buffer( buf );
			_sg_reset_buffer( buf );
			_sg_pool_free_index( &_sg.pools.buffer_pool, _sg_slot_index( buf_id.GetValue() ) );
		}
		else
		{
			puts( "sg_destroy_buffer: active context mismatch (must be same as for creation)" );
			_SG_TRACE_NOARGS( err_context_mismatch );
		}
	}
}

void Gfx::sg_destroy_image( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	_SG_TRACE_ARGS( destroy_image, img_id );
	_sg_image_t * img = _sg_lookup_image( &_sg.pools, img_id.GetValue() );
	if( img )
	{
		if( img->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_sg_destroy_image( img );
			_sg_reset_image( img );
			_sg_pool_free_index( &_sg.pools.image_pool, _sg_slot_index( img_id.GetValue() ) );
		}
		else
		{
			puts( "sg_destroy_image: active context mismatch (must be same as for creation)" );
			_SG_TRACE_NOARGS( err_context_mismatch );
		}
	}
}

void Gfx::sg_destroy_shader( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	_SG_TRACE_ARGS( destroy_shader, shd_id );
	_sg_shader_t * shd = _sg_lookup_shader( &_sg.pools, shd_id.GetValue() );
	if( shd )
	{
		if( shd->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_sg_destroy_shader( shd );
			_sg_reset_shader( shd );
			_sg_pool_free_index( &_sg.pools.shader_pool, _sg_slot_index( shd_id.GetValue() ) );
		}
		else
		{
			puts( "sg_destroy_shader: active context mismatch (must be same as for creation)" );
			_SG_TRACE_NOARGS( err_context_mismatch );
		}
	}
}

void Gfx::sg_destroy_pipeline( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	_SG_TRACE_ARGS( destroy_pipeline, pip_id );
	_sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	if( pip )
	{
		if( pip->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_sg_destroy_pipeline( pip );
			_sg_reset_pipeline( pip );
			_sg_pool_free_index( &_sg.pools.pipeline_pool, _sg_slot_index( pip_id.GetValue() ) );
		}
		else
		{
			puts( "sg_destroy_pipeline: active context mismatch (must be same as for creation)" );
			_SG_TRACE_NOARGS( err_context_mismatch );
		}
	}
}

void Gfx::sg_destroy_pass( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	_SG_TRACE_ARGS( destroy_pass, pass_id );
	_sg_pass_t * pass = _sg_lookup_pass( &_sg.pools, pass_id.GetValue() );
	if( pass )
	{
		if( pass->slot.ctx_id == _sg.active_context.GetValue() )
		{
			_sg_destroy_pass( pass );
			_sg_reset_pass( pass );
			_sg_pool_free_index( &_sg.pools.pass_pool, _sg_slot_index( pass_id.GetValue() ) );
		}
		else
		{
			puts( "sg_destroy_pass: active context mismatch (must be same as for creation)" );
			_SG_TRACE_NOARGS( err_context_mismatch );
		}
	}
}

void Gfx::sg_update_buffer( BufferHandle buf_id, const void * data, int num_bytes )
{
	XE_ASSERT( _sg.valid );
	_sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
	if( ( num_bytes > 0 ) && buf && ( buf->slot.state == SG_RESOURCESTATE_VALID ) )
	{
		if( _sg_validate_update_buffer( buf, data, num_bytes ) )
		{
			XE_ASSERT( num_bytes <= buf->cmn.size );
			/* only one update allowed per buffer and frame */
			XE_ASSERT( buf->cmn.update_frame_index != _sg.frame_index );
			/* update and append on same buffer in same frame not allowed */
			XE_ASSERT( buf->cmn.append_frame_index != _sg.frame_index );
			_sg_update_buffer( buf, data, num_bytes );
			buf->cmn.update_frame_index = _sg.frame_index;
		}
	}
	_SG_TRACE_ARGS( update_buffer, buf_id, data, num_bytes );
}

void Gfx::sg_update_image( ImageHandle img_id, const ImageContent * data )
{
	XE_ASSERT( _sg.valid );
	_sg_image_t * img = _sg_lookup_image( &_sg.pools, img_id.GetValue() );
	if( img && img->slot.state == SG_RESOURCESTATE_VALID )
	{
		if( _sg_validate_update_image( img, data ) )
		{
			XE_ASSERT( img->cmn.upd_frame_index != _sg.frame_index );
			_sg_update_image( img, data );
			img->cmn.upd_frame_index = _sg.frame_index;
		}
	}
	_SG_TRACE_ARGS( update_image, img_id, data );
}

int Gfx::sg_append_buffer( BufferHandle buf_id, const void * data, int num_bytes )
{
	XE_ASSERT( _sg.valid );
	_sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
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
		if( buf->slot.state == SG_RESOURCESTATE_VALID )
		{
			if( _sg_validate_append_buffer( buf, data, num_bytes ) )
			{
				if( !buf->cmn.append_overflow && ( num_bytes > 0 ) )
				{
					/* update and append on same buffer in same frame not allowed */
					XE_ASSERT( buf->cmn.update_frame_index != _sg.frame_index );
					_sg_append_buffer( buf, data, num_bytes, buf->cmn.append_frame_index != _sg.frame_index );
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
	_SG_TRACE_ARGS( append_buffer, buf_id, data, num_bytes, result );
	return result;
}

bool Gfx::sg_query_buffer_overflow( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	_sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
	bool result = buf ? buf->cmn.append_overflow : false;
	return result;
}

void Gfx::sg_begin_default_pass( const PassAction * pass_action, int width, int height )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pass_action );
	XE_ASSERT( ( pass_action->_start_canary == 0 ) && ( pass_action->_end_canary == 0 ) );
	PassAction pa;
	_sg_resolve_default_pass_action( pass_action, &pa );
	_sg.cur_pass = XE::PassHandle::Invalid;
	_sg.pass_valid = true;
	_sg_begin_pass( 0, &pa, width, height );
	_SG_TRACE_ARGS( begin_default_pass, pass_action, width, height );
}

void Gfx::sg_begin_pass( PassHandle pass_id, const PassAction * pass_action )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pass_action );
	XE_ASSERT( ( pass_action->_start_canary == 0 ) && ( pass_action->_end_canary == 0 ) );
	_sg.cur_pass = pass_id;
	_sg_pass_t * pass = _sg_lookup_pass( &_sg.pools, pass_id.GetValue() );
	if( pass && _sg_validate_begin_pass( pass ) )
	{
		_sg.pass_valid = true;
		PassAction pa;
		_sg_resolve_default_pass_action( pass_action, &pa );
		const _sg_image_t * img = _sg_pass_color_image( pass, 0 );
		const int w = img->cmn.width;
		const int h = img->cmn.height;
		_sg_begin_pass( pass, &pa, w, h );
		_SG_TRACE_ARGS( begin_pass, pass_id, pass_action );
	}
	else
	{
		_sg.pass_valid = false;
		_SG_TRACE_NOARGS( err_pass_invalid );
	}
}

void Gfx::sg_apply_viewport( int x, int y, int width, int height, bool origin_top_left )
{
	XE_ASSERT( _sg.valid );
	if( !_sg.pass_valid )
	{
		_SG_TRACE_NOARGS( err_pass_invalid );
		return;
	}
	_sg_apply_viewport( x, y, width, height, origin_top_left );
	_SG_TRACE_ARGS( apply_viewport, x, y, width, height, origin_top_left );
}

void Gfx::sg_apply_scissor_rect( int x, int y, int width, int height, bool origin_top_left )
{
	XE_ASSERT( _sg.valid );
	if( !_sg.pass_valid )
	{
		_SG_TRACE_NOARGS( err_pass_invalid );
		return;
	}
	_sg_apply_scissor_rect( x, y, width, height, origin_top_left );
	_SG_TRACE_ARGS( apply_scissor_rect, x, y, width, height, origin_top_left );
}

void Gfx::sg_apply_pipeline( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	_sg.bindings_valid = false;
	if( !_sg_validate_apply_pipeline( pip_id ) )
	{
		_sg.next_draw_valid = false;
		_SG_TRACE_NOARGS( err_draw_invalid );
		return;
	}
	if( !_sg.pass_valid )
	{
		_SG_TRACE_NOARGS( err_pass_invalid );
		return;
	}
	_sg.cur_pipeline = pip_id;
	_sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	XE_ASSERT( pip );
	_sg.next_draw_valid = ( SG_RESOURCESTATE_VALID == pip->slot.state );
	XE_ASSERT( pip->shader && ( pip->shader->slot.id == pip->cmn.shader_id.GetValue() ) );
	_sg_apply_pipeline( pip );
	_SG_TRACE_ARGS( apply_pipeline, pip_id );
}

void Gfx::sg_apply_bindings( const Bindings * bindings )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( bindings );
	XE_ASSERT( ( bindings->_start_canary == 0 ) && ( bindings->_end_canary == 0 ) );
	if( !_sg_validate_apply_bindings( bindings ) )
	{
		_sg.next_draw_valid = false;
		_SG_TRACE_NOARGS( err_draw_invalid );
		return;
	}
	_sg.bindings_valid = true;

	_sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, _sg.cur_pipeline.GetValue() );
	XE_ASSERT( pip );

	_sg_buffer_t * vbs[SG_MAX_SHADERSTAGE_BUFFERS] = { 0 };
	int num_vbs = 0;
	for( int i = 0; i < SG_MAX_SHADERSTAGE_BUFFERS; i++, num_vbs++ )
	{
		if( bindings->vertex_buffers[i].GetValue() )
		{
			vbs[i] = _sg_lookup_buffer( &_sg.pools, bindings->vertex_buffers[i].GetValue() );
			XE_ASSERT( vbs[i] );
			_sg.next_draw_valid &= ( SG_RESOURCESTATE_VALID == vbs[i]->slot.state );
			_sg.next_draw_valid &= !vbs[i]->cmn.append_overflow;
		}
		else
		{
			break;
		}
	}

	_sg_buffer_t * ib = 0;
	if( bindings->index_buffer.GetValue() )
	{
		ib = _sg_lookup_buffer( &_sg.pools, bindings->index_buffer.GetValue() );
		XE_ASSERT( ib );
		_sg.next_draw_valid &= ( SG_RESOURCESTATE_VALID == ib->slot.state );
		_sg.next_draw_valid &= !ib->cmn.append_overflow;
	}

	_sg_image_t * vs_imgs[SG_MAX_SHADERSTAGE_IMAGES] = { 0 };
	int num_vs_imgs = 0;
	for( int i = 0; i < SG_MAX_SHADERSTAGE_IMAGES; i++, num_vs_imgs++ )
	{
		if( bindings->vs_images[i].GetValue() )
		{
			vs_imgs[i] = _sg_lookup_image( &_sg.pools, bindings->vs_images[i].GetValue() );
			XE_ASSERT( vs_imgs[i] );
			_sg.next_draw_valid &= ( SG_RESOURCESTATE_VALID == vs_imgs[i]->slot.state );
		}
		else
		{
			break;
		}
	}

	_sg_image_t * fs_imgs[SG_MAX_SHADERSTAGE_IMAGES] = { 0 };
	int num_fs_imgs = 0;
	for( int i = 0; i < SG_MAX_SHADERSTAGE_IMAGES; i++, num_fs_imgs++ )
	{
		if( bindings->fs_images[i].GetValue() )
		{
			fs_imgs[i] = _sg_lookup_image( &_sg.pools, bindings->fs_images[i].GetValue() );
			XE_ASSERT( fs_imgs[i] );
			_sg.next_draw_valid &= ( SG_RESOURCESTATE_VALID == fs_imgs[i]->slot.state );
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
		_sg_apply_bindings( pip, vbs, vb_offsets, num_vbs, ib, ib_offset, vs_imgs, num_vs_imgs, fs_imgs, num_fs_imgs );
		_SG_TRACE_ARGS( apply_bindings, bindings );
	}
	else
	{
		_SG_TRACE_NOARGS( err_draw_invalid );
	}
}

void Gfx::sg_apply_uniforms( ShaderStage stage, int ub_index, const void * data, int num_bytes )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( ( stage == SG_SHADERSTAGE_VS ) || ( stage == SG_SHADERSTAGE_FS ) );
	XE_ASSERT( ( ub_index >= 0 ) && ( ub_index < SG_MAX_SHADERSTAGE_UBS ) );
	XE_ASSERT( data && ( num_bytes > 0 ) );
	if( !_sg_validate_apply_uniforms( stage, ub_index, data, num_bytes ) )
	{
		_sg.next_draw_valid = false;
		_SG_TRACE_NOARGS( err_draw_invalid );
		return;
	}
	if( !_sg.pass_valid )
	{
		_SG_TRACE_NOARGS( err_pass_invalid );
		return;
	}
	if( !_sg.next_draw_valid )
	{
		_SG_TRACE_NOARGS( err_draw_invalid );
	}
	_sg_apply_uniforms( stage, ub_index, data, num_bytes );
	_SG_TRACE_ARGS( apply_uniforms, stage, ub_index, data, num_bytes );
}

void Gfx::sg_draw( int base_element, int num_elements, int num_instances )
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
		_SG_TRACE_NOARGS( err_pass_invalid );
		return;
	}
	if( !_sg.next_draw_valid )
	{
		_SG_TRACE_NOARGS( err_draw_invalid );
		return;
	}
	if( !_sg.bindings_valid )
	{
		_SG_TRACE_NOARGS( err_bindings_invalid );
		return;
	}
	_sg_draw( base_element, num_elements, num_instances );
	_SG_TRACE_ARGS( draw, base_element, num_elements, num_instances );
}

void Gfx::sg_end_pass( void )
{
	XE_ASSERT( _sg.valid );
	if( !_sg.pass_valid )
	{
		_SG_TRACE_NOARGS( err_pass_invalid );
		return;
	}
	_sg_end_pass();
	_sg.cur_pass = XE::PassHandle::Invalid;
	_sg.cur_pipeline = XE::PipelineHandle::Invalid;
	_sg.pass_valid = false;
	_SG_TRACE_NOARGS( end_pass );
}

void Gfx::sg_commit( void )
{
	XE_ASSERT( _sg.valid );
	_sg_commit();
	_SG_TRACE_NOARGS( commit );
	_sg.frame_index++;
}

GfxDesc Gfx::sg_query_desc( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.desc;
}

Backend Gfx::sg_query_backend( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.backend;
}

Features Gfx::sg_query_features( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.features;
}

Limits Gfx::sg_query_limits( void )
{
	XE_ASSERT( _sg.valid );
	return _sg.limits;
}

PixelformatInfo Gfx::sg_query_pixelformat( PixelFormat fmt )
{
	XE_ASSERT( _sg.valid );
	int fmt_index = (int )fmt;
	XE_ASSERT( ( fmt_index > SG_PIXELFORMAT_NONE ) && ( fmt_index < _SG_PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index];
}

ResourceState Gfx::sg_query_buffer_state( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	_sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
	ResourceState res = buf ? buf->slot.state : SG_RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::sg_query_image_state( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	_sg_image_t * img = _sg_lookup_image( &_sg.pools, img_id.GetValue() );
	ResourceState res = img ? img->slot.state : SG_RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::sg_query_shader_state( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	_sg_shader_t * shd = _sg_lookup_shader( &_sg.pools, shd_id.GetValue() );
	ResourceState res = shd ? shd->slot.state : SG_RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::sg_query_pipeline_state( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	_sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	ResourceState res = pip ? pip->slot.state : SG_RESOURCESTATE_INVALID;
	return res;
}

ResourceState Gfx::sg_query_pass_state( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	_sg_pass_t * pass = _sg_lookup_pass( &_sg.pools, pass_id.GetValue() );
	ResourceState res = pass ? pass->slot.state : SG_RESOURCESTATE_INVALID;
	return res;
}

BufferInfo Gfx::sg_query_buffer_info( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	BufferInfo info;
	memset( &info, 0, sizeof( info ) );
	const _sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
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

ImageInfo Gfx::sg_query_image_info( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	ImageInfo info;
	memset( &info, 0, sizeof( info ) );
	const _sg_image_t * img = _sg_lookup_image( &_sg.pools, img_id.GetValue() );
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

ShaderInfo Gfx::sg_query_shader_info( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	ShaderInfo info;
	memset( &info, 0, sizeof( info ) );
	const _sg_shader_t * shd = _sg_lookup_shader( &_sg.pools, shd_id.GetValue() );
	if( shd )
	{
		info.slot.state = shd->slot.state;
		info.slot.res_id = shd->slot.id;
		info.slot.ctx_id = shd->slot.ctx_id;
	}
	return info;
}

PipelineInfo Gfx::sg_query_pipeline_info( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	PipelineInfo info;
	memset( &info, 0, sizeof( info ) );
	const _sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	if( pip )
	{
		info.slot.state = pip->slot.state;
		info.slot.res_id = pip->slot.id;
		info.slot.ctx_id = pip->slot.ctx_id;
	}
	return info;
}

PassInfo Gfx::sg_query_pass_info( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	PassInfo info;
	memset( &info, 0, sizeof( info ) );
	const _sg_pass_t * pass = _sg_lookup_pass( &_sg.pools, pass_id.GetValue() );
	if( pass )
	{
		info.slot.state = pass->slot.state;
		info.slot.res_id = pass->slot.id;
		info.slot.ctx_id = pass->slot.ctx_id;
	}
	return info;
}

BufferDesc Gfx::sg_query_buffer_defaults( const BufferDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _Buffer_desc_defaults( desc );
}

ImageDesc Gfx::sg_query_image_defaults( const ImageDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _sg_image_desc_defaults( desc );
}

ShaderDesc Gfx::sg_query_shader_defaults( const ShaderDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _sg_shader_desc_defaults( desc );
}

PipelineDesc Gfx::sg_query_pipeline_defaults( const PipelineDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _sg_pipeline_desc_defaults( desc );
}

PassDesc Gfx::sg_query_pass_defaults( const PassDesc * desc )
{
	XE_ASSERT( _sg.valid && desc );
	return _sg_pass_desc_defaults( desc );
}

BufferHandle Gfx::sg_alloc_buffer( void )
{
	XE_ASSERT( _sg.valid );
	BufferHandle res = _sg_alloc_buffer();
	_SG_TRACE_ARGS( alloc_buffer, res );
	return res;
}

ImageHandle Gfx::sg_alloc_image( void )
{
	XE_ASSERT( _sg.valid );
	ImageHandle res = _sg_alloc_image();
	_SG_TRACE_ARGS( alloc_image, res );
	return res;
}

ShaderHandle Gfx::sg_alloc_shader( void )
{
	XE_ASSERT( _sg.valid );
	ShaderHandle res = _sg_alloc_shader();
	_SG_TRACE_ARGS( alloc_shader, res );
	return res;
}

PipelineHandle Gfx::sg_alloc_pipeline( void )
{
	XE_ASSERT( _sg.valid );
	PipelineHandle res = _sg_alloc_pipeline();
	_SG_TRACE_ARGS( alloc_pipeline, res );
	return res;
}

PassHandle Gfx::sg_alloc_pass( void )
{
	XE_ASSERT( _sg.valid );
	PassHandle res = _sg_alloc_pass();
	_SG_TRACE_ARGS( alloc_pass, res );
	return res;
}

void Gfx::sg_init_buffer( BufferHandle buf_id, const BufferDesc * desc )
{
	XE_ASSERT( _sg.valid );
	BufferDesc desc_def = _Buffer_desc_defaults( desc );
	_sg_init_buffer( buf_id, &desc_def );
	_SG_TRACE_ARGS( init_buffer, buf_id, &desc_def );
}

void Gfx::sg_init_image( ImageHandle img_id, const ImageDesc * desc )
{
	XE_ASSERT( _sg.valid );
	ImageDesc desc_def = _sg_image_desc_defaults( desc );
	_sg_init_image( img_id, &desc_def );
	_SG_TRACE_ARGS( init_image, img_id, &desc_def );
}

void Gfx::sg_init_shader( ShaderHandle shd_id, const ShaderDesc * desc )
{
	XE_ASSERT( _sg.valid );
	ShaderDesc desc_def = _sg_shader_desc_defaults( desc );
	_sg_init_shader( shd_id, &desc_def );
	_SG_TRACE_ARGS( init_shader, shd_id, &desc_def );
}

void Gfx::sg_init_pipeline( PipelineHandle pip_id, const PipelineDesc * desc )
{
	XE_ASSERT( _sg.valid );
	PipelineDesc desc_def = _sg_pipeline_desc_defaults( desc );
	_sg_init_pipeline( pip_id, &desc_def );
	_SG_TRACE_ARGS( init_pipeline, pip_id, &desc_def );
}

void Gfx::sg_init_pass( PassHandle pass_id, const PassDesc * desc )
{
	XE_ASSERT( _sg.valid );
	PassDesc desc_def = _sg_pass_desc_defaults( desc );
	_sg_init_pass( pass_id, &desc_def );
	_SG_TRACE_ARGS( init_pass, pass_id, &desc_def );
}

void Gfx::sg_fail_buffer( BufferHandle buf_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( buf_id );
	_sg_buffer_t * buf = _sg_lookup_buffer( &_sg.pools, buf_id.GetValue() );
	XE_ASSERT( buf && buf->slot.state == SG_RESOURCESTATE_ALLOC );
	buf->slot.ctx_id = _sg.active_context.GetValue();
	buf->slot.state = SG_RESOURCESTATE_FAILED;
	_SG_TRACE_ARGS( fail_buffer, buf_id );
}

void Gfx::sg_fail_image( ImageHandle img_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( img_id );
	_sg_image_t * img = _sg_lookup_image( &_sg.pools, img_id.GetValue() );
	XE_ASSERT( img && img->slot.state == SG_RESOURCESTATE_ALLOC );
	img->slot.ctx_id = _sg.active_context.GetValue();
	img->slot.state = SG_RESOURCESTATE_FAILED;
	_SG_TRACE_ARGS( fail_image, img_id );
}

void Gfx::sg_fail_shader( ShaderHandle shd_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( shd_id );
	_sg_shader_t * shd = _sg_lookup_shader( &_sg.pools, shd_id.GetValue() );
	XE_ASSERT( shd && shd->slot.state == SG_RESOURCESTATE_ALLOC );
	shd->slot.ctx_id = _sg.active_context.GetValue();
	shd->slot.state = SG_RESOURCESTATE_FAILED;
	_SG_TRACE_ARGS( fail_shader, shd_id );
}

void Gfx::sg_fail_pipeline( PipelineHandle pip_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pip_id );
	_sg_pipeline_t * pip = _sg_lookup_pipeline( &_sg.pools, pip_id.GetValue() );
	XE_ASSERT( pip && pip->slot.state == SG_RESOURCESTATE_ALLOC );
	pip->slot.ctx_id = _sg.active_context.GetValue();
	pip->slot.state = SG_RESOURCESTATE_FAILED;
	_SG_TRACE_ARGS( fail_pipeline, pip_id );
}

void Gfx::sg_fail_pass( PassHandle pass_id )
{
	XE_ASSERT( _sg.valid );
	XE_ASSERT( pass_id );
	_sg_pass_t * pass = _sg_lookup_pass( &_sg.pools, pass_id.GetValue() );
	XE_ASSERT( pass && pass->slot.state == SG_RESOURCESTATE_ALLOC );
	pass->slot.ctx_id = _sg.active_context.GetValue();
	pass->slot.state = SG_RESOURCESTATE_FAILED;
	_SG_TRACE_ARGS( fail_pass, pass_id );
}

ContextHandle Gfx::sg_setup_context( void )
{
	XE_ASSERT( _sg.valid );
	ContextHandle res;
	int slot_index = _sg_pool_alloc_index( &_sg.pools.context_pool );
	if( SG_INVALID_SLOT_INDEX != slot_index )
	{
		res = _sg_slot_alloc( &_sg.pools.context_pool, &_sg.pools.contexts[slot_index].slot, slot_index );
		_sg_context_t * ctx = _sg_context_at( &_sg.pools, res.GetValue() );
		ctx->slot.state = _sg_create_context( ctx );
		XE_ASSERT( ctx->slot.state == SG_RESOURCESTATE_VALID );
		_sg_activate_context( ctx );
	}
	else
	{
		/* pool is exhausted */
		res = XE::ContextHandle::Invalid;
	}
	_sg.active_context = res;
	return res;
}

void Gfx::sg_activate_context( ContextHandle ctx_id )
{
	XE_ASSERT( _sg.valid );
	_sg.active_context = ctx_id;
	_sg_context_t * ctx = _sg_lookup_context( &_sg.pools, ctx_id.GetValue() );
	/* NOTE: ctx can be 0 here if the context is no longer valid */
	_sg_activate_context( ctx );
}

void Gfx::sg_discard_context( ContextHandle ctx_id )
{
	XE_ASSERT( _sg.valid );
	_sg_destroy_all_resources( &_sg.pools, ctx_id.GetValue() );
	_sg_context_t * ctx = _sg_lookup_context( &_sg.pools, ctx_id.GetValue() );
	if( ctx )
	{
		_sg_destroy_context( ctx );
		_sg_reset_context( ctx );
		_sg_pool_free_index( &_sg.pools.context_pool, _sg_slot_index( ctx_id.GetValue() ) );
	}
	_sg.active_context = XE::ContextHandle::Invalid;
	_sg_activate_context( 0 );
}
