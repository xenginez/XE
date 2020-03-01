#if defined(_WIN32)

#include "Gfx.h"

USING_XE

#ifndef D3D11_NO_HELPERS
#define D3D11_NO_HELPERS
#endif
#ifndef CINTERFACE
#define CINTERFACE
#endif
#ifndef COBJMACROS
#define COBJMACROS
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#if (defined(WINAPI_FAMILY_PARTITION) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))
#pragma comment (lib, "WindowsApp.lib")
#else
#pragma comment (lib, "user32.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxguid.lib")
#endif

typedef struct
{
	_sg_slot_t slot;
	_sg_buffer_common_t cmn;
	struct
	{
		ID3D11Buffer * buf;
	} d3d11;
} _sg_d3d11_buffer_t;
typedef _sg_d3d11_buffer_t _sg_buffer_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_image_common_t cmn;
	struct
	{
		DXGI_FORMAT format;
		ID3D11Texture2D * tex2d;
		ID3D11Texture3D * tex3d;
		ID3D11Texture2D * texds;
		ID3D11Texture2D * texmsaa;
		ID3D11ShaderResourceView * srv;
		ID3D11SamplerState * smp;
	} d3d11;
} _sg_d3d11_image_t;
typedef _sg_d3d11_image_t _sg_image_t;

typedef struct
{
	XE::String sem_name;
	int sem_index;
} _sg_d3d11_shader_attr_t;

typedef struct
{
	ID3D11Buffer * cbufs[SG_MAX_SHADERSTAGE_UBS];
} _sg_d3d11_shader_stage_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_shader_common_t cmn;
	struct
	{
		_sg_d3d11_shader_attr_t attrs[SG_MAX_VERTEX_ATTRIBUTES];
		_sg_d3d11_shader_stage_t stage[SG_NUM_SHADER_STAGES];
		ID3D11VertexShader * vs;
		ID3D11PixelShader * fs;
		void * vs_blob;
		int vs_blob_length;
	} d3d11;
} _sg_d3d11_shader_t;
typedef _sg_d3d11_shader_t _sg_shader_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_pipeline_common_t cmn;
	_sg_shader_t * shader;
	struct
	{
		UINT stencil_ref;
		UINT vb_strides[SG_MAX_SHADERSTAGE_BUFFERS];
		D3D_PRIMITIVE_TOPOLOGY topology;
		DXGI_FORMAT index_format;
		ID3D11InputLayout * il;
		ID3D11RasterizerState * rs;
		ID3D11DepthStencilState * dss;
		ID3D11BlendState * bs;
	} d3d11;
} _sg_d3d11_pipeline_t;
typedef _sg_d3d11_pipeline_t _sg_pipeline_t;

typedef struct
{
	_sg_image_t * image;
	ID3D11RenderTargetView * rtv;
} _sg_d3d11_color_attachment_t;

typedef struct
{
	_sg_image_t * image;
	ID3D11DepthStencilView * dsv;
} _sg_d3d11_ds_attachment_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_pass_common_t cmn;
	struct
	{
		_sg_d3d11_color_attachment_t color_atts[SG_MAX_COLOR_ATTACHMENTS];
		_sg_d3d11_ds_attachment_t ds_att;
	} d3d11;
} _sg_d3d11_pass_t;
typedef _sg_d3d11_pass_t _sg_pass_t;
typedef _sg_attachment_common_t _sg_attachment_t;

typedef struct
{
	_sg_slot_t slot;
} _sg_d3d11_context_t;
typedef _sg_d3d11_context_t _sg_context_t;

typedef struct
{
	bool valid;
	ID3D11Device * dev;
	ID3D11DeviceContext * ctx;
	const void * ( *rtv_cb )( void );
	const void * ( *dsv_cb )( void );
	bool in_pass;
	bool use_indexed_draw;
	int cur_width;
	int cur_height;
	int num_rtvs;
	_sg_pass_t * cur_pass;
	PassHandle cur_pass_id;
	_sg_pipeline_t * cur_pipeline;
	PipelineHandle cur_pipeline_id;
	ID3D11RenderTargetView * cur_rtvs[SG_MAX_COLOR_ATTACHMENTS];
	ID3D11DepthStencilView * cur_dsv;
	/* on-demand loaded d3dcompiler_47.dll handles */
	HINSTANCE d3dcompiler_dll;
	bool d3dcompiler_dll_load_failed;
	pD3DCompile D3DCompile_func;
	/* the following arrays are used for unbinding resources, they will always contain zeroes */
	ID3D11RenderTargetView * zero_rtvs[SG_MAX_COLOR_ATTACHMENTS];
	ID3D11Buffer * zero_vbs[SG_MAX_SHADERSTAGE_BUFFERS];
	UINT zero_vb_offsets[SG_MAX_SHADERSTAGE_BUFFERS];
	UINT zero_vb_strides[SG_MAX_SHADERSTAGE_BUFFERS];
	ID3D11Buffer * zero_cbs[SG_MAX_SHADERSTAGE_UBS];
	ID3D11ShaderResourceView * zero_srvs[SG_MAX_SHADERSTAGE_IMAGES];
	ID3D11SamplerState * zero_smps[SG_MAX_SHADERSTAGE_IMAGES];
	/* global subresourcedata array for texture updates */
	D3D11_SUBRESOURCE_DATA subres_data[SG_MAX_MIPMAPS * SG_MAX_TEXTUREARRAY_LAYERS];
} _sg_d3d11_backend_t;
typedef _sg_d3d11_backend_t _sg_backend_t;

typedef struct
{
	_sg_pool_t buffer_pool;
	_sg_pool_t image_pool;
	_sg_pool_t shader_pool;
	_sg_pool_t pipeline_pool;
	_sg_pool_t pass_pool;
	_sg_pool_t context_pool;
	_sg_buffer_t * buffers;
	_sg_image_t * images;
	_sg_shader_t * shaders;
	_sg_pipeline_t * pipelines;
	_sg_pass_t * passes;
	_sg_context_t * contexts;
} _sg_pools_t;

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
	_sg_validate_error_t validate_error;
	_sg_pools_t pools;
	Backend backend;
	Features features;
	Limits limits;
	PixelformatInfo formats[_SG_PIXELFORMAT_NUM];
	_sg_backend_t d3d11;
	GfxTraceHooks * hooks;
} _sg_state_t;

static _sg_state_t _sg;



/* the default color pixelformat for render targets */
PixelFormat _sg_default_rendertarget_colorformat( void )
{
	return SG_PIXELFORMAT_BGRA8;
}

/* return true if pixel format is a valid render target format */
bool _sg_is_valid_rendertarget_color_format( PixelFormat fmt )
{
	const int fmt_index = (int )fmt;
	XE_ASSERT( ( fmt_index >= 0 ) && ( fmt_index < _SG_PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index].render && !_sg.formats[fmt_index].depth;
}

/* return true if pixel format is a valid depth format */
bool _sg_is_valid_rendertarget_depth_format( PixelFormat fmt )
{
	const int fmt_index = (int )fmt;
	XE_ASSERT( ( fmt_index >= 0 ) && ( fmt_index < _SG_PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index].render && _sg.formats[fmt_index].depth;
}




/*-- enum translation functions ----------------------------------------------*/
D3D11_USAGE _sg_usage( Usage usg )
{
	switch( usg )
	{
	case SG_USAGE_IMMUTABLE:
		return D3D11_USAGE_IMMUTABLE;
	case SG_USAGE_DYNAMIC:
	case SG_USAGE_STREAM:
		return D3D11_USAGE_DYNAMIC;
	default:
		XE_ASSERT(false);
		return (D3D11_USAGE )0;
	}
}

UINT _sg_cpu_access_flags( Usage usg )
{
	switch( usg )
	{
	case SG_USAGE_IMMUTABLE:
		return 0;
	case SG_USAGE_DYNAMIC:
	case SG_USAGE_STREAM:
		return D3D11_CPU_ACCESS_WRITE;
	default:
		XE_ASSERT(false);
		return 0;
	}
}

DXGI_FORMAT _sg_pixel_format( PixelFormat fmt )
{
	switch( fmt )
	{
	case SG_PIXELFORMAT_R8:             return DXGI_FORMAT_R8_UNORM;
	case SG_PIXELFORMAT_R8SN:           return DXGI_FORMAT_R8_SNORM;
	case SG_PIXELFORMAT_R8UI:           return DXGI_FORMAT_R8_UINT;
	case SG_PIXELFORMAT_R8SI:           return DXGI_FORMAT_R8_SINT;
	case SG_PIXELFORMAT_R16:            return DXGI_FORMAT_R16_UNORM;
	case SG_PIXELFORMAT_R16SN:          return DXGI_FORMAT_R16_SNORM;
	case SG_PIXELFORMAT_R16UI:          return DXGI_FORMAT_R16_UINT;
	case SG_PIXELFORMAT_R16SI:          return DXGI_FORMAT_R16_SINT;
	case SG_PIXELFORMAT_R16F:           return DXGI_FORMAT_R16_FLOAT;
	case SG_PIXELFORMAT_RG8:            return DXGI_FORMAT_R8G8_UNORM;
	case SG_PIXELFORMAT_RG8SN:          return DXGI_FORMAT_R8G8_SNORM;
	case SG_PIXELFORMAT_RG8UI:          return DXGI_FORMAT_R8G8_UINT;
	case SG_PIXELFORMAT_RG8SI:          return DXGI_FORMAT_R8G8_SINT;
	case SG_PIXELFORMAT_R32UI:          return DXGI_FORMAT_R32_UINT;
	case SG_PIXELFORMAT_R32SI:          return DXGI_FORMAT_R32_SINT;
	case SG_PIXELFORMAT_R32F:           return DXGI_FORMAT_R32_FLOAT;
	case SG_PIXELFORMAT_RG16:           return DXGI_FORMAT_R16G16_UNORM;
	case SG_PIXELFORMAT_RG16SN:         return DXGI_FORMAT_R16G16_SNORM;
	case SG_PIXELFORMAT_RG16UI:         return DXGI_FORMAT_R16G16_UINT;
	case SG_PIXELFORMAT_RG16SI:         return DXGI_FORMAT_R16G16_SINT;
	case SG_PIXELFORMAT_RG16F:          return DXGI_FORMAT_R16G16_FLOAT;
	case SG_PIXELFORMAT_RGBA8:          return DXGI_FORMAT_R8G8B8A8_UNORM;
	case SG_PIXELFORMAT_RGBA8SN:        return DXGI_FORMAT_R8G8B8A8_SNORM;
	case SG_PIXELFORMAT_RGBA8UI:        return DXGI_FORMAT_R8G8B8A8_UINT;
	case SG_PIXELFORMAT_RGBA8SI:        return DXGI_FORMAT_R8G8B8A8_SINT;
	case SG_PIXELFORMAT_BGRA8:          return DXGI_FORMAT_B8G8R8A8_UNORM;
	case SG_PIXELFORMAT_RGB10A2:        return DXGI_FORMAT_R10G10B10A2_UNORM;
	case SG_PIXELFORMAT_RG11B10F:       return DXGI_FORMAT_R11G11B10_FLOAT;
	case SG_PIXELFORMAT_RG32UI:         return DXGI_FORMAT_R32G32_UINT;
	case SG_PIXELFORMAT_RG32SI:         return DXGI_FORMAT_R32G32_SINT;
	case SG_PIXELFORMAT_RG32F:          return DXGI_FORMAT_R32G32_FLOAT;
	case SG_PIXELFORMAT_RGBA16:         return DXGI_FORMAT_R16G16B16A16_UNORM;
	case SG_PIXELFORMAT_RGBA16SN:       return DXGI_FORMAT_R16G16B16A16_SNORM;
	case SG_PIXELFORMAT_RGBA16UI:       return DXGI_FORMAT_R16G16B16A16_UINT;
	case SG_PIXELFORMAT_RGBA16SI:       return DXGI_FORMAT_R16G16B16A16_SINT;
	case SG_PIXELFORMAT_RGBA16F:        return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case SG_PIXELFORMAT_RGBA32UI:       return DXGI_FORMAT_R32G32B32A32_UINT;
	case SG_PIXELFORMAT_RGBA32SI:       return DXGI_FORMAT_R32G32B32A32_SINT;
	case SG_PIXELFORMAT_RGBA32F:        return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case SG_PIXELFORMAT_DEPTH:          return DXGI_FORMAT_D32_FLOAT;
	case SG_PIXELFORMAT_DEPTH_STENCIL:  return DXGI_FORMAT_D24_UNORM_S8_UINT;
	case SG_PIXELFORMAT_BC1_RGBA:       return DXGI_FORMAT_BC1_UNORM;
	case SG_PIXELFORMAT_BC2_RGBA:       return DXGI_FORMAT_BC2_UNORM;
	case SG_PIXELFORMAT_BC3_RGBA:       return DXGI_FORMAT_BC3_UNORM;
	case SG_PIXELFORMAT_BC4_R:          return DXGI_FORMAT_BC4_UNORM;
	case SG_PIXELFORMAT_BC4_RSN:        return DXGI_FORMAT_BC4_SNORM;
	case SG_PIXELFORMAT_BC5_RG:         return DXGI_FORMAT_BC5_UNORM;
	case SG_PIXELFORMAT_BC5_RGSN:       return DXGI_FORMAT_BC5_SNORM;
	case SG_PIXELFORMAT_BC6H_RGBF:      return DXGI_FORMAT_BC6H_SF16;
	case SG_PIXELFORMAT_BC6H_RGBUF:     return DXGI_FORMAT_BC6H_UF16;
	case SG_PIXELFORMAT_BC7_RGBA:       return DXGI_FORMAT_BC7_UNORM;
	default:                            return DXGI_FORMAT_UNKNOWN;
	};
}

D3D11_PRIMITIVE_TOPOLOGY _sg_primitive_topology( PrimitiveType prim_type )
{
	switch( prim_type )
	{
	case SG_PRIMITIVETYPE_POINTS:           return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case SG_PRIMITIVETYPE_LINES:            return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case SG_PRIMITIVETYPE_LINE_STRIP:       return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case SG_PRIMITIVETYPE_TRIANGLES:        return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case SG_PRIMITIVETYPE_TRIANGLE_STRIP:   return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	default: XE_ASSERT(false); return (D3D11_PRIMITIVE_TOPOLOGY )0;
	}
}

DXGI_FORMAT _sg_index_format( IndexType index_type )
{
	switch( index_type )
	{
	case SG_INDEXTYPE_NONE:     return DXGI_FORMAT_UNKNOWN;
	case SG_INDEXTYPE_UINT16:   return DXGI_FORMAT_R16_UINT;
	case SG_INDEXTYPE_UINT32:   return DXGI_FORMAT_R32_UINT;
	default: XE_ASSERT(false); return (DXGI_FORMAT )0;
	}
}

D3D11_FILTER _sg_filter( Filter min_f, Filter mag_f, uint32_t max_anisotropy )
{
	if( max_anisotropy > 1 )
	{
		return D3D11_FILTER_ANISOTROPIC;
	}
	else if( mag_f == SG_FILTER_NEAREST )
	{
		switch( min_f )
		{
		case SG_FILTER_NEAREST:
		case SG_FILTER_NEAREST_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_MAG_MIP_POINT;
		case SG_FILTER_LINEAR:
		case SG_FILTER_LINEAR_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		case SG_FILTER_NEAREST_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		case SG_FILTER_LINEAR_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		default:
			XE_ASSERT(false); break;
		}
	}
	else if( mag_f == SG_FILTER_LINEAR )
	{
		switch( min_f )
		{
		case SG_FILTER_NEAREST:
		case SG_FILTER_NEAREST_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
		case SG_FILTER_LINEAR:
		case SG_FILTER_LINEAR_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		case SG_FILTER_NEAREST_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		case SG_FILTER_LINEAR_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		default:
			XE_ASSERT(false); break;
		}
	}
	/* invalid value for mag filter */
	XE_ASSERT(false);
	return D3D11_FILTER_MIN_MAG_MIP_POINT;
}

D3D11_TEXTURE_ADDRESS_MODE _sg_address_mode( Wrap m )
{
	switch( m )
	{
	case SG_WRAP_REPEAT:            return D3D11_TEXTURE_ADDRESS_WRAP;
	case SG_WRAP_CLAMP_TO_EDGE:     return D3D11_TEXTURE_ADDRESS_CLAMP;
	case SG_WRAP_CLAMP_TO_BORDER:   return D3D11_TEXTURE_ADDRESS_BORDER;
	case SG_WRAP_MIRRORED_REPEAT:   return D3D11_TEXTURE_ADDRESS_MIRROR;
	default: XE_ASSERT(false); return (D3D11_TEXTURE_ADDRESS_MODE )0;
	}
}

DXGI_FORMAT _sg_vertex_format( VertexFormat fmt )
{
	switch( fmt )
	{
	case SG_VERTEXFORMAT_FLOAT:     return DXGI_FORMAT_R32_FLOAT;
	case SG_VERTEXFORMAT_FLOAT2:    return DXGI_FORMAT_R32G32_FLOAT;
	case SG_VERTEXFORMAT_FLOAT3:    return DXGI_FORMAT_R32G32B32_FLOAT;
	case SG_VERTEXFORMAT_FLOAT4:    return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case SG_VERTEXFORMAT_BYTE4:     return DXGI_FORMAT_R8G8B8A8_SINT;
	case SG_VERTEXFORMAT_BYTE4N:    return DXGI_FORMAT_R8G8B8A8_SNORM;
	case SG_VERTEXFORMAT_UBYTE4:    return DXGI_FORMAT_R8G8B8A8_UINT;
	case SG_VERTEXFORMAT_UBYTE4N:   return DXGI_FORMAT_R8G8B8A8_UNORM;
	case SG_VERTEXFORMAT_SHORT2:    return DXGI_FORMAT_R16G16_SINT;
	case SG_VERTEXFORMAT_SHORT2N:   return DXGI_FORMAT_R16G16_SNORM;
	case SG_VERTEXFORMAT_USHORT2N:  return DXGI_FORMAT_R16G16_UNORM;
	case SG_VERTEXFORMAT_SHORT4:    return DXGI_FORMAT_R16G16B16A16_SINT;
	case SG_VERTEXFORMAT_SHORT4N:   return DXGI_FORMAT_R16G16B16A16_SNORM;
	case SG_VERTEXFORMAT_USHORT4N:  return DXGI_FORMAT_R16G16B16A16_UNORM;
	case SG_VERTEXFORMAT_UINT10_N2: return DXGI_FORMAT_R10G10B10A2_UNORM;
	default: XE_ASSERT(false); return (DXGI_FORMAT )0;
	}
}

D3D11_INPUT_CLASSIFICATION _sg_input_classification( VertexStep step )
{
	switch( step )
	{
	case SG_VERTEXSTEP_PER_VERTEX:      return D3D11_INPUT_PER_VERTEX_DATA;
	case SG_VERTEXSTEP_PER_INSTANCE:    return D3D11_INPUT_PER_INSTANCE_DATA;
	default: XE_ASSERT(false); return (D3D11_INPUT_CLASSIFICATION )0;
	}
}

D3D11_CULL_MODE _sg_cull_mode( CullMode m )
{
	switch( m )
	{
	case SG_CULLMODE_NONE:      return D3D11_CULL_NONE;
	case SG_CULLMODE_FRONT:     return D3D11_CULL_FRONT;
	case SG_CULLMODE_BACK:      return D3D11_CULL_BACK;
	default: XE_ASSERT(false); return (D3D11_CULL_MODE )0;
	}
}

D3D11_COMPARISON_FUNC _sg_compare_func( CompareFunc f )
{
	switch( f )
	{
	case SG_COMPAREFUNC_NEVER:          return D3D11_COMPARISON_NEVER;
	case SG_COMPAREFUNC_LESS:           return D3D11_COMPARISON_LESS;
	case SG_COMPAREFUNC_EQUAL:          return D3D11_COMPARISON_EQUAL;
	case SG_COMPAREFUNC_LESS_EQUAL:     return D3D11_COMPARISON_LESS_EQUAL;
	case SG_COMPAREFUNC_GREATER:        return D3D11_COMPARISON_GREATER;
	case SG_COMPAREFUNC_NOT_EQUAL:      return D3D11_COMPARISON_NOT_EQUAL;
	case SG_COMPAREFUNC_GREATER_EQUAL:  return D3D11_COMPARISON_GREATER_EQUAL;
	case SG_COMPAREFUNC_ALWAYS:         return D3D11_COMPARISON_ALWAYS;
	default: XE_ASSERT(false); return (D3D11_COMPARISON_FUNC )0;
	}
}

D3D11_STENCIL_OP _sg_stencil_op( StencilOp op )
{
	switch( op )
	{
	case SG_STENCILOP_KEEP:         return D3D11_STENCIL_OP_KEEP;
	case SG_STENCILOP_ZERO:         return D3D11_STENCIL_OP_ZERO;
	case SG_STENCILOP_REPLACE:      return D3D11_STENCIL_OP_REPLACE;
	case SG_STENCILOP_INCR_CLAMP:   return D3D11_STENCIL_OP_INCR_SAT;
	case SG_STENCILOP_DECR_CLAMP:   return D3D11_STENCIL_OP_DECR_SAT;
	case SG_STENCILOP_INVERT:       return D3D11_STENCIL_OP_INVERT;
	case SG_STENCILOP_INCR_WRAP:    return D3D11_STENCIL_OP_INCR;
	case SG_STENCILOP_DECR_WRAP:    return D3D11_STENCIL_OP_DECR;
	default: XE_ASSERT(false); return (D3D11_STENCIL_OP )0;
	}
}

D3D11_BLEND _sg_blend_factor( BlendFactor f )
{
	switch( f )
	{
	case SG_BLENDFACTOR_ZERO:                   return D3D11_BLEND_ZERO;
	case SG_BLENDFACTOR_ONE:                    return D3D11_BLEND_ONE;
	case SG_BLENDFACTOR_SRC_COLOR:              return D3D11_BLEND_SRC_COLOR;
	case SG_BLENDFACTOR_ONE_MINUS_SRC_COLOR:    return D3D11_BLEND_INV_SRC_COLOR;
	case SG_BLENDFACTOR_SRC_ALPHA:              return D3D11_BLEND_SRC_ALPHA;
	case SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA:    return D3D11_BLEND_INV_SRC_ALPHA;
	case SG_BLENDFACTOR_DST_COLOR:              return D3D11_BLEND_DEST_COLOR;
	case SG_BLENDFACTOR_ONE_MINUS_DST_COLOR:    return D3D11_BLEND_INV_DEST_COLOR;
	case SG_BLENDFACTOR_DST_ALPHA:              return D3D11_BLEND_DEST_ALPHA;
	case SG_BLENDFACTOR_ONE_MINUS_DST_ALPHA:    return D3D11_BLEND_INV_DEST_ALPHA;
	case SG_BLENDFACTOR_SRC_ALPHA_SATURATED:    return D3D11_BLEND_SRC_ALPHA_SAT;
	case SG_BLENDFACTOR_BLEND_COLOR:            return D3D11_BLEND_BLEND_FACTOR;
	case SG_BLENDFACTOR_ONE_MINUS_BLEND_COLOR:  return D3D11_BLEND_INV_BLEND_FACTOR;
	case SG_BLENDFACTOR_BLEND_ALPHA:            return D3D11_BLEND_BLEND_FACTOR;
	case SG_BLENDFACTOR_ONE_MINUS_BLEND_ALPHA:  return D3D11_BLEND_INV_BLEND_FACTOR;
	default: XE_ASSERT(false); return (D3D11_BLEND )0;
	}
}

D3D11_BLEND_OP _sg_blend_op( BlendOp op )
{
	switch( op )
	{
	case SG_BLENDOP_ADD:                return D3D11_BLEND_OP_ADD;
	case SG_BLENDOP_SUBTRACT:           return D3D11_BLEND_OP_SUBTRACT;
	case SG_BLENDOP_REVERSE_SUBTRACT:   return D3D11_BLEND_OP_REV_SUBTRACT;
	default: XE_ASSERT(false); return (D3D11_BLEND_OP )0;
	}
}

UINT8 _sg_color_write_mask( ColorMask m )
{
	UINT8 res = 0;
	if( m & SG_COLORMASK_R )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_RED;
	}
	if( m & SG_COLORMASK_G )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_GREEN;
	}
	if( m & SG_COLORMASK_B )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_BLUE;
	}
	if( m & SG_COLORMASK_A )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_ALPHA;
	}
	return res;
}






void _sg_init_caps( void )
{
	_sg.backend = SG_BACKEND_D3D11;

	_sg.features.instancing = true;
	_sg.features.origin_top_left = true;
	_sg.features.multiple_render_targets = true;
	_sg.features.msaa_render_targets = true;
	_sg.features.imagetype_3d = true;
	_sg.features.imagetype_array = true;
	_sg.features.image_clamp_to_border = true;

	_sg.limits.max_image_size_2d = 16 * 1024;
	_sg.limits.max_image_size_cube = 16 * 1024;
	_sg.limits.max_image_size_3d = 2 * 1024;
	_sg.limits.max_image_size_array = 16 * 1024;
	_sg.limits.max_image_array_layers = 2 * 1024;
	_sg.limits.max_vertex_attrs = SG_MAX_VERTEX_ATTRIBUTES;

	UINT dxgi_fmt_caps = 0;
	for( int fmt = ( SG_PIXELFORMAT_NONE + 1 ); fmt < _SG_PIXELFORMAT_NUM; fmt++ )
	{
		DXGI_FORMAT dxgi_fmt = _sg_pixel_format( (PixelFormat )fmt );
		HRESULT hr = ID3D11Device_CheckFormatSupport( _sg.d3d11.dev, dxgi_fmt, &dxgi_fmt_caps );
		XE_ASSERT( SUCCEEDED( hr ) );
		PixelformatInfo * info = &_sg.formats[fmt];
		info->sample = 0 != ( dxgi_fmt_caps & D3D11_FORMAT_SUPPORT_TEXTURE2D );
		info->filter = 0 != ( dxgi_fmt_caps & D3D11_FORMAT_SUPPORT_SHADER_SAMPLE );
		info->render = 0 != ( dxgi_fmt_caps & D3D11_FORMAT_SUPPORT_RENDER_TARGET );
		info->blend = 0 != ( dxgi_fmt_caps & D3D11_FORMAT_SUPPORT_BLENDABLE );
		info->msaa = 0 != ( dxgi_fmt_caps & D3D11_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET );
		info->depth = 0 != ( dxgi_fmt_caps & D3D11_FORMAT_SUPPORT_DEPTH_STENCIL );
		if( info->depth )
		{
			info->render = true;
		}
	}
}

void _sg_setup_backend( const GfxDesc * desc )
{
	/* assume _sg.d3d11 already is zero-initialized */
	XE_ASSERT( desc );
	XE_ASSERT( desc->d3d11_device );
	XE_ASSERT( desc->d3d11_device_context );
	XE_ASSERT( desc->d3d11_render_target_view_cb );
	XE_ASSERT( desc->d3d11_depth_stencil_view_cb );
	XE_ASSERT( desc->d3d11_render_target_view_cb != desc->d3d11_depth_stencil_view_cb );
	_sg.d3d11.valid = true;
	_sg.d3d11.dev = (ID3D11Device * )desc->d3d11_device;
	_sg.d3d11.ctx = (ID3D11DeviceContext * )desc->d3d11_device_context;
	_sg.d3d11.rtv_cb = desc->d3d11_render_target_view_cb;
	_sg.d3d11.dsv_cb = desc->d3d11_depth_stencil_view_cb;
	_sg_init_caps();
}

void _sg_discard_backend( void )
{
	XE_ASSERT( _sg.d3d11.valid );
	_sg.d3d11.valid = false;
}

void _sg_clear_state( void )
{
	/* clear all the device context state, so that resource refs don't keep stuck in the d3d device context */
	ID3D11DeviceContext_OMSetRenderTargets( _sg.d3d11.ctx, SG_MAX_COLOR_ATTACHMENTS, _sg.d3d11.zero_rtvs, NULL );
	ID3D11DeviceContext_RSSetState( _sg.d3d11.ctx, NULL );
	ID3D11DeviceContext_OMSetDepthStencilState( _sg.d3d11.ctx, NULL, 0 );
	ID3D11DeviceContext_OMSetBlendState( _sg.d3d11.ctx, NULL, NULL, 0xFFFFFFFF );
	ID3D11DeviceContext_IASetVertexBuffers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_BUFFERS, _sg.d3d11.zero_vbs, _sg.d3d11.zero_vb_strides, _sg.d3d11.zero_vb_offsets );
	ID3D11DeviceContext_IASetIndexBuffer( _sg.d3d11.ctx, NULL, DXGI_FORMAT_UNKNOWN, 0 );
	ID3D11DeviceContext_IASetInputLayout( _sg.d3d11.ctx, NULL );
	ID3D11DeviceContext_VSSetShader( _sg.d3d11.ctx, NULL, NULL, 0 );
	ID3D11DeviceContext_PSSetShader( _sg.d3d11.ctx, NULL, NULL, 0 );
	ID3D11DeviceContext_VSSetConstantBuffers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_UBS, _sg.d3d11.zero_cbs );
	ID3D11DeviceContext_PSSetConstantBuffers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_UBS, _sg.d3d11.zero_cbs );
	ID3D11DeviceContext_VSSetShaderResources( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_srvs );
	ID3D11DeviceContext_PSSetShaderResources( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_srvs );
	ID3D11DeviceContext_VSSetSamplers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_smps );
	ID3D11DeviceContext_PSSetSamplers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_smps );
}

void _sg_reset_state_cache( void )
{
	_sg_clear_state();
}

void _sg_activate_context( _sg_context_t * ctx )
{
	(void)( ctx );
	_sg_clear_state();
}

ResourceState _sg_create_context( _sg_context_t * ctx )
{
	XE_ASSERT( ctx );
	(void)( ctx );
	return SG_RESOURCESTATE_VALID;
}

void _sg_destroy_context( _sg_context_t * ctx )
{
	XE_ASSERT( ctx );
	(void)( ctx );
}

ResourceState _sg_create_buffer( _sg_buffer_t * buf, const BufferDesc * desc )
{
	XE_ASSERT( buf && desc );
	XE_ASSERT( !buf->d3d11.buf );
	buf->cmn.init( desc );
	const bool injected = ( 0 != desc->d3d11_buffer );
	if( injected )
	{
		buf->d3d11.buf = (ID3D11Buffer * )desc->d3d11_buffer;
		ID3D11Buffer_AddRef( buf->d3d11.buf );
	}
	else
	{
		D3D11_BUFFER_DESC d3d11_desc;
		memset( &d3d11_desc, 0, sizeof( d3d11_desc ) );
		d3d11_desc.ByteWidth = buf->cmn.size;
		d3d11_desc.Usage = _sg_usage( buf->cmn.usage );
		d3d11_desc.BindFlags = buf->cmn.type == SG_BUFFERTYPE_VERTEXBUFFER ? D3D11_BIND_VERTEX_BUFFER : D3D11_BIND_INDEX_BUFFER;
		d3d11_desc.CPUAccessFlags = _sg_cpu_access_flags( buf->cmn.usage );
		D3D11_SUBRESOURCE_DATA * init_data_ptr = 0;
		D3D11_SUBRESOURCE_DATA init_data;
		memset( &init_data, 0, sizeof( init_data ) );
		if( buf->cmn.usage == SG_USAGE_IMMUTABLE )
		{
			XE_ASSERT( desc->content );
			init_data.pSysMem = desc->content;
			init_data_ptr = &init_data;
		}
		HRESULT hr = ID3D11Device_CreateBuffer( _sg.d3d11.dev, &d3d11_desc, init_data_ptr, &buf->d3d11.buf );
		(void)( hr );
		XE_ASSERT( SUCCEEDED( hr ) && buf->d3d11.buf );
	}
	return SG_RESOURCESTATE_VALID;
}

void _sg_destroy_buffer( _sg_buffer_t * buf )
{
	XE_ASSERT( buf );
	if( buf->d3d11.buf )
	{
		ID3D11Buffer_Release( buf->d3d11.buf );
	}
}

void _sg_fill_subres_data( const _sg_image_t * img, const ImageContent * content )
{
	const int num_faces = ( img->cmn.type == SG_IMAGETYPE_CUBE ) ? 6 : 1;
	const int num_slices = ( img->cmn.type == SG_IMAGETYPE_ARRAY ) ? img->cmn.depth : 1;
	int subres_index = 0;
	for( int face_index = 0; face_index < num_faces; face_index++ )
	{
		for( int slice_index = 0; slice_index < num_slices; slice_index++ )
		{
			for( int mip_index = 0; mip_index < img->cmn.num_mipmaps; mip_index++, subres_index++ )
			{
				XE_ASSERT( subres_index < ( SG_MAX_MIPMAPS * SG_MAX_TEXTUREARRAY_LAYERS ) );
				D3D11_SUBRESOURCE_DATA * subres_data = &_sg.d3d11.subres_data[subres_index];
				const int mip_width = ( ( img->cmn.width >> mip_index ) > 0 ) ? img->cmn.width >> mip_index : 1;
				const int mip_height = ( ( img->cmn.height >> mip_index ) > 0 ) ? img->cmn.height >> mip_index : 1;
				const SubimageContent * subimg_content = &( content->subimage[face_index][mip_index] );
				const int slice_size = subimg_content->size / num_slices;
				const int slice_offset = slice_size * slice_index;
				const uint8_t * ptr = (const uint8_t * )subimg_content->ptr;
				subres_data->pSysMem = ptr + slice_offset;
				subres_data->SysMemPitch = _sg_row_pitch( img->cmn.pixel_format, mip_width );
				if( img->cmn.type == SG_IMAGETYPE_3D )
				{
					/* FIXME? const int mip_depth = ((img->depth>>mip_index)>0) ? img->depth>>mip_index : 1; */
					subres_data->SysMemSlicePitch = _sg_surface_pitch( img->cmn.pixel_format, mip_width, mip_height );
				}
				else
				{
					subres_data->SysMemSlicePitch = 0;
				}
			}
		}
	}
}

ResourceState _sg_create_image( _sg_image_t * img, const ImageDesc * desc )
{
	XE_ASSERT( img && desc );
	XE_ASSERT( !img->d3d11.tex2d && !img->d3d11.tex3d && !img->d3d11.texds && !img->d3d11.texmsaa );
	XE_ASSERT( !img->d3d11.srv && !img->d3d11.smp );
	HRESULT hr;

	img->cmn.init( desc );
	const bool injected = ( 0 != desc->d3d11_texture );
	const bool msaa = ( img->cmn.sample_count > 1 );

	/* special case depth-stencil buffer? */
	if( _sg_is_valid_rendertarget_depth_format( img->cmn.pixel_format ) )
	{
		/* create only a depth-texture */
		XE_ASSERT( !injected );
		img->d3d11.format = _sg_pixel_format( img->cmn.pixel_format );
		if( img->d3d11.format == DXGI_FORMAT_UNKNOWN )
		{
			puts( "trying to create a D3D11 depth-texture with unsupported pixel format\n" );
			return SG_RESOURCESTATE_FAILED;
		}
		D3D11_TEXTURE2D_DESC d3d11_desc;
		memset( &d3d11_desc, 0, sizeof( d3d11_desc ) );
		d3d11_desc.Width = img->cmn.width;
		d3d11_desc.Height = img->cmn.height;
		d3d11_desc.MipLevels = 1;
		d3d11_desc.ArraySize = 1;
		d3d11_desc.Format = img->d3d11.format;
		d3d11_desc.Usage = D3D11_USAGE_DEFAULT;
		d3d11_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		d3d11_desc.SampleDesc.Count = img->cmn.sample_count;
		d3d11_desc.SampleDesc.Quality = msaa ? D3D11_STANDARD_MULTISAMPLE_PATTERN : 0;
		hr = ID3D11Device_CreateTexture2D( _sg.d3d11.dev, &d3d11_desc, NULL, &img->d3d11.texds );
		XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.texds );
	}
	else
	{
		/* create (or inject) color texture */

		/* prepare initial content pointers */
		D3D11_SUBRESOURCE_DATA * init_data = 0;
		if( !injected && ( img->cmn.usage == SG_USAGE_IMMUTABLE ) && !img->cmn.render_target )
		{
			_sg_fill_subres_data( img, &desc->content );
			init_data = _sg.d3d11.subres_data;
		}
		if( img->cmn.type != SG_IMAGETYPE_3D )
		{
			/* 2D-, cube- or array-texture */
			/* if this is an MSAA render target, the following texture will be the 'resolve-texture' */
			D3D11_TEXTURE2D_DESC d3d11_tex_desc;
			memset( &d3d11_tex_desc, 0, sizeof( d3d11_tex_desc ) );
			d3d11_tex_desc.Width = img->cmn.width;
			d3d11_tex_desc.Height = img->cmn.height;
			d3d11_tex_desc.MipLevels = img->cmn.num_mipmaps;
			switch( img->cmn.type )
			{
			case SG_IMAGETYPE_ARRAY:    d3d11_tex_desc.ArraySize = img->cmn.depth; break;
			case SG_IMAGETYPE_CUBE:     d3d11_tex_desc.ArraySize = 6; break;
			default:                    d3d11_tex_desc.ArraySize = 1; break;
			}
			d3d11_tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			if( img->cmn.render_target )
			{
				img->d3d11.format = _sg_pixel_format( img->cmn.pixel_format );
				d3d11_tex_desc.Format = img->d3d11.format;
				d3d11_tex_desc.Usage = D3D11_USAGE_DEFAULT;
				if( !msaa )
				{
					d3d11_tex_desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
				}
				d3d11_tex_desc.CPUAccessFlags = 0;
			}
			else
			{
				img->d3d11.format = _sg_pixel_format( img->cmn.pixel_format );
				d3d11_tex_desc.Format = img->d3d11.format;
				d3d11_tex_desc.Usage = _sg_usage( img->cmn.usage );
				d3d11_tex_desc.CPUAccessFlags = _sg_cpu_access_flags( img->cmn.usage );
			}
			if( img->d3d11.format == DXGI_FORMAT_UNKNOWN )
			{
				/* trying to create a texture format that's not supported by D3D */
				puts( "trying to create a D3D11 texture with unsupported pixel format\n" );
				return SG_RESOURCESTATE_FAILED;
			}
			d3d11_tex_desc.SampleDesc.Count = 1;
			d3d11_tex_desc.SampleDesc.Quality = 0;
			d3d11_tex_desc.MiscFlags = ( img->cmn.type == SG_IMAGETYPE_CUBE ) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;
			if( injected )
			{
				img->d3d11.tex2d = (ID3D11Texture2D * )desc->d3d11_texture;
				ID3D11Texture2D_AddRef( img->d3d11.tex2d );
			}
			else
			{
				hr = ID3D11Device_CreateTexture2D( _sg.d3d11.dev, &d3d11_tex_desc, init_data, &img->d3d11.tex2d );
				XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.tex2d );
			}

			/* shader-resource-view */
			D3D11_SHADER_RESOURCE_VIEW_DESC d3d11_srv_desc;
			memset( &d3d11_srv_desc, 0, sizeof( d3d11_srv_desc ) );
			d3d11_srv_desc.Format = d3d11_tex_desc.Format;
			switch( img->cmn.type )
			{
			case SG_IMAGETYPE_2D:
				d3d11_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				d3d11_srv_desc.Texture2D.MipLevels = img->cmn.num_mipmaps;
				break;
			case SG_IMAGETYPE_CUBE:
				d3d11_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
				d3d11_srv_desc.TextureCube.MipLevels = img->cmn.num_mipmaps;
				break;
			case SG_IMAGETYPE_ARRAY:
				d3d11_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
				d3d11_srv_desc.Texture2DArray.MipLevels = img->cmn.num_mipmaps;
				d3d11_srv_desc.Texture2DArray.ArraySize = img->cmn.depth;
				break;
			default:
				XE_ASSERT(false); break;
			}
			hr = ID3D11Device_CreateShaderResourceView( _sg.d3d11.dev, (ID3D11Resource * )img->d3d11.tex2d, &d3d11_srv_desc, &img->d3d11.srv );
			XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.srv );
		}
		else
		{
			/* 3D texture */
			D3D11_TEXTURE3D_DESC d3d11_tex_desc;
			memset( &d3d11_tex_desc, 0, sizeof( d3d11_tex_desc ) );
			d3d11_tex_desc.Width = img->cmn.width;
			d3d11_tex_desc.Height = img->cmn.height;
			d3d11_tex_desc.Depth = img->cmn.depth;
			d3d11_tex_desc.MipLevels = img->cmn.num_mipmaps;
			d3d11_tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			if( img->cmn.render_target )
			{
				img->d3d11.format = _sg_pixel_format( img->cmn.pixel_format );
				d3d11_tex_desc.Format = img->d3d11.format;
				d3d11_tex_desc.Usage = D3D11_USAGE_DEFAULT;
				if( !msaa )
				{
					d3d11_tex_desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
				}
				d3d11_tex_desc.CPUAccessFlags = 0;
			}
			else
			{
				img->d3d11.format = _sg_pixel_format( img->cmn.pixel_format );
				d3d11_tex_desc.Format = img->d3d11.format;
				d3d11_tex_desc.Usage = _sg_usage( img->cmn.usage );
				d3d11_tex_desc.CPUAccessFlags = _sg_cpu_access_flags( img->cmn.usage );
			}
			if( img->d3d11.format == DXGI_FORMAT_UNKNOWN )
			{
				/* trying to create a texture format that's not supported by D3D */
				puts( "trying to create a D3D11 texture with unsupported pixel format\n" );
				return SG_RESOURCESTATE_FAILED;
			}
			if( injected )
			{
				img->d3d11.tex3d = (ID3D11Texture3D * )desc->d3d11_texture;
				ID3D11Texture3D_AddRef( img->d3d11.tex3d );
			}
			else
			{
				hr = ID3D11Device_CreateTexture3D( _sg.d3d11.dev, &d3d11_tex_desc, init_data, &img->d3d11.tex3d );
				XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.tex3d );
			}

			/* shader resource view for 3d texture */
			D3D11_SHADER_RESOURCE_VIEW_DESC d3d11_srv_desc;
			memset( &d3d11_srv_desc, 0, sizeof( d3d11_srv_desc ) );
			d3d11_srv_desc.Format = d3d11_tex_desc.Format;
			d3d11_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
			d3d11_srv_desc.Texture3D.MipLevels = img->cmn.num_mipmaps;
			hr = ID3D11Device_CreateShaderResourceView( _sg.d3d11.dev, (ID3D11Resource * )img->d3d11.tex3d, &d3d11_srv_desc, &img->d3d11.srv );
			XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.srv );
		}

		/* also need to create a separate MSAA render target texture? */
		if( msaa )
		{
			D3D11_TEXTURE2D_DESC d3d11_tex_desc;
			memset( &d3d11_tex_desc, 0, sizeof( d3d11_tex_desc ) );
			d3d11_tex_desc.Width = img->cmn.width;
			d3d11_tex_desc.Height = img->cmn.height;
			d3d11_tex_desc.MipLevels = 1;
			d3d11_tex_desc.ArraySize = 1;
			d3d11_tex_desc.Format = img->d3d11.format;
			d3d11_tex_desc.Usage = D3D11_USAGE_DEFAULT;
			d3d11_tex_desc.BindFlags = D3D11_BIND_RENDER_TARGET;
			d3d11_tex_desc.CPUAccessFlags = 0;
			d3d11_tex_desc.SampleDesc.Count = img->cmn.sample_count;
			d3d11_tex_desc.SampleDesc.Quality = (UINT )D3D11_STANDARD_MULTISAMPLE_PATTERN;
			hr = ID3D11Device_CreateTexture2D( _sg.d3d11.dev, &d3d11_tex_desc, NULL, &img->d3d11.texmsaa );
			XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.texmsaa );
		}

		/* sampler state object, note D3D11 implements an internal shared-pool for sampler objects */
		D3D11_SAMPLER_DESC d3d11_smp_desc;
		memset( &d3d11_smp_desc, 0, sizeof( d3d11_smp_desc ) );
		d3d11_smp_desc.Filter = _sg_filter( img->cmn.min_filter, img->cmn.mag_filter, img->cmn.max_anisotropy );
		d3d11_smp_desc.AddressU = _sg_address_mode( img->cmn.wrap_u );
		d3d11_smp_desc.AddressV = _sg_address_mode( img->cmn.wrap_v );
		d3d11_smp_desc.AddressW = _sg_address_mode( img->cmn.wrap_w );
		switch( img->cmn.border_color )
		{
		case SG_BORDERCOLOR_TRANSPARENT_BLACK:
			/* all 0.0f */
			break;
		case SG_BORDERCOLOR_OPAQUE_WHITE:
			for( int i = 0; i < 4; i++ )
			{
				d3d11_smp_desc.BorderColor[i] = 1.0f;
			}
			break;
		default:
			/* opaque black */
			d3d11_smp_desc.BorderColor[3] = 1.0f;
			break;
		}
		d3d11_smp_desc.MaxAnisotropy = img->cmn.max_anisotropy;
		d3d11_smp_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		d3d11_smp_desc.MinLOD = desc->min_lod;
		d3d11_smp_desc.MaxLOD = desc->max_lod;
		hr = ID3D11Device_CreateSamplerState( _sg.d3d11.dev, &d3d11_smp_desc, &img->d3d11.smp );
		XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.smp );
	}
	return SG_RESOURCESTATE_VALID;
}

void _sg_destroy_image( _sg_image_t * img )
{
	XE_ASSERT( img );
	if( img->d3d11.tex2d )
	{
		ID3D11Texture2D_Release( img->d3d11.tex2d );
	}
	if( img->d3d11.tex3d )
	{
		ID3D11Texture3D_Release( img->d3d11.tex3d );
	}
	if( img->d3d11.texds )
	{
		ID3D11Texture2D_Release( img->d3d11.texds );
	}
	if( img->d3d11.texmsaa )
	{
		ID3D11Texture2D_Release( img->d3d11.texmsaa );
	}
	if( img->d3d11.srv )
	{
		ID3D11ShaderResourceView_Release( img->d3d11.srv );
	}
	if( img->d3d11.smp )
	{
		ID3D11SamplerState_Release( img->d3d11.smp );
	}
}

#define _sg_roundup(val, round_to) (((val)+((round_to)-1))&~((round_to)-1))

#if (defined(WINAPI_FAMILY_PARTITION) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))
#define _sg_D3DCompile D3DCompile
#else
#define _sg_D3DCompile _sg.d3d11.D3DCompile_func
#endif

bool _sg_load_d3dcompiler_dll( void )
{
	/* on UWP, don't do anything (not tested) */
#if (defined(WINAPI_FAMILY_PARTITION) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))
	return true;
#else
	/* load DLL on demand */
	if( ( 0 == _sg.d3d11.d3dcompiler_dll ) && !_sg.d3d11.d3dcompiler_dll_load_failed )
	{
		_sg.d3d11.d3dcompiler_dll = LoadLibraryA( "d3dcompiler_47.dll" );
		if( 0 == _sg.d3d11.d3dcompiler_dll )
		{
			/* don't attempt to load missing DLL in the future */
			puts( "failed to load d3dcompiler_47.dll!\n" );
			_sg.d3d11.d3dcompiler_dll_load_failed = true;
			return false;
		}
		/* look up function pointers */
		_sg.d3d11.D3DCompile_func = (pD3DCompile )GetProcAddress( _sg.d3d11.d3dcompiler_dll, "D3DCompile" );
		XE_ASSERT( _sg.d3d11.D3DCompile_func );
	}
	return 0 != _sg.d3d11.d3dcompiler_dll;
#endif
}

ID3DBlob * _sg_compile_shader( const ShaderStageDesc * stage_desc, XE::String target )
{
	if( !_sg_load_d3dcompiler_dll() )
	{
		return NULL;
	}
	ID3DBlob * output = NULL;
	ID3DBlob * errors_or_warnings = NULL;
	HRESULT hr = _sg_D3DCompile(
		stage_desc->source,             /* pSrcData */
		strlen( stage_desc->source ),     /* SrcDataSize */
		NULL,                           /* pSourceName */
		NULL,                           /* pDefines */
		NULL,                           /* pInclude */
		stage_desc->entry ? stage_desc->entry : "main",     /* pEntryPoint */
		target,     /* pTarget (vs_5_0 or ps_5_0) */
		D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR | D3DCOMPILE_OPTIMIZATION_LEVEL3,   /* Flags1 */
		0,          /* Flags2 */
		&output,    /* ppCode */
		&errors_or_warnings );   /* ppErrorMsgs */
	if( errors_or_warnings )
	{
		puts( (LPCSTR )ID3D10Blob_GetBufferPointer( errors_or_warnings ) );
		ID3D10Blob_Release( errors_or_warnings ); errors_or_warnings = NULL;
	}
	if( FAILED( hr ) )
	{
		/* just in case, usually output is NULL here */
		if( output )
		{
			ID3D10Blob_Release( output );
			output = NULL;
		}
	}
	return output;
}

ResourceState _sg_create_shader( _sg_shader_t * shd, const ShaderDesc * desc )
{
	XE_ASSERT( shd && desc );
	XE_ASSERT( !shd->d3d11.vs && !shd->d3d11.fs && !shd->d3d11.vs_blob );
	HRESULT hr;

	shd->cmn.init( desc );

	/* copy vertex attribute semantic names and indices */
	for( int i = 0; i < SG_MAX_VERTEX_ATTRIBUTES; i++ )
	{
		shd->d3d11.attrs[i].sem_name = desc->attrs[i].sem_name;
		shd->d3d11.attrs[i].sem_index = desc->attrs[i].sem_index;
	}

	/* shader stage uniform blocks and image slots */
	for( int stage_index = 0; stage_index < SG_NUM_SHADER_STAGES; stage_index++ )
	{
		_sg_shader_stage_t * cmn_stage = &shd->cmn.stage[stage_index];
		_sg_d3d11_shader_stage_t * d3d11_stage = &shd->d3d11.stage[stage_index];
		for( int ub_index = 0; ub_index < cmn_stage->num_uniform_blocks; ub_index++ )
		{
			const _sg_uniform_block_t * ub = &cmn_stage->uniform_blocks[ub_index];

			/* create a D3D constant buffer for each uniform block */
			XE_ASSERT( 0 == d3d11_stage->cbufs[ub_index] );
			D3D11_BUFFER_DESC cb_desc;
			memset( &cb_desc, 0, sizeof( cb_desc ) );
			cb_desc.ByteWidth = _sg_roundup( ub->size, 16 );
			cb_desc.Usage = D3D11_USAGE_DEFAULT;
			cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			hr = ID3D11Device_CreateBuffer( _sg.d3d11.dev, &cb_desc, NULL, &d3d11_stage->cbufs[ub_index] );
			XE_ASSERT( SUCCEEDED( hr ) && d3d11_stage->cbufs[ub_index] );
		}
	}

	const void * vs_ptr = 0, *fs_ptr = 0;
	SIZE_T vs_length = 0, fs_length = 0;
	ID3DBlob * vs_blob = 0, *fs_blob = 0;
	if( desc->vs.byte_code && desc->fs.byte_code )
	{
		/* create from shader byte code */
		vs_ptr = desc->vs.byte_code;
		fs_ptr = desc->fs.byte_code;
		vs_length = desc->vs.byte_code_size;
		fs_length = desc->fs.byte_code_size;
	}
	else
	{
		/* compile from shader source code */
		vs_blob = _sg_compile_shader( &desc->vs, "vs_5_0" );
		fs_blob = _sg_compile_shader( &desc->fs, "ps_5_0" );
		if( vs_blob && fs_blob )
		{
			vs_ptr = ID3D10Blob_GetBufferPointer( vs_blob );
			vs_length = ID3D10Blob_GetBufferSize( vs_blob );
			fs_ptr = ID3D10Blob_GetBufferPointer( fs_blob );
			fs_length = ID3D10Blob_GetBufferSize( fs_blob );
		}
	}
	ResourceState result = SG_RESOURCESTATE_FAILED;
	if( vs_ptr && fs_ptr && ( vs_length > 0 ) && ( fs_length > 0 ) )
	{
		/* create the D3D vertex- and pixel-shader objects */
		hr = ID3D11Device_CreateVertexShader( _sg.d3d11.dev, vs_ptr, vs_length, NULL, &shd->d3d11.vs );
		XE_ASSERT( SUCCEEDED( hr ) && shd->d3d11.vs );
		hr = ID3D11Device_CreatePixelShader( _sg.d3d11.dev, fs_ptr, fs_length, NULL, &shd->d3d11.fs );
		XE_ASSERT( SUCCEEDED( hr ) && shd->d3d11.fs );

		/* need to store the vertex shader byte code, this is needed later in sg_create_pipeline */
		shd->d3d11.vs_blob_length = (int )vs_length;
		shd->d3d11.vs_blob = malloc( (int )vs_length );
		XE_ASSERT( shd->d3d11.vs_blob );
		memcpy( shd->d3d11.vs_blob, vs_ptr, vs_length );

		result = SG_RESOURCESTATE_VALID;
	}
	if( vs_blob )
	{
		ID3D10Blob_Release( vs_blob ); vs_blob = 0;
	}
	if( fs_blob )
	{
		ID3D10Blob_Release( fs_blob ); fs_blob = 0;
	}
	return result;
}

void _sg_destroy_shader( _sg_shader_t * shd )
{
	XE_ASSERT( shd );
	if( shd->d3d11.vs )
	{
		ID3D11VertexShader_Release( shd->d3d11.vs );
	}
	if( shd->d3d11.fs )
	{
		ID3D11PixelShader_Release( shd->d3d11.fs );
	}
	if( shd->d3d11.vs_blob )
	{
		free( shd->d3d11.vs_blob );
	}
	for( int stage_index = 0; stage_index < SG_NUM_SHADER_STAGES; stage_index++ )
	{
		_sg_shader_stage_t * cmn_stage = &shd->cmn.stage[stage_index];
		_sg_d3d11_shader_stage_t * d3d11_stage = &shd->d3d11.stage[stage_index];
		for( int ub_index = 0; ub_index < cmn_stage->num_uniform_blocks; ub_index++ )
		{
			if( d3d11_stage->cbufs[ub_index] != nullptr )
			{
				ID3D11Buffer_Release( d3d11_stage->cbufs[ub_index] );
			}
		}
	}
}

ResourceState _sg_create_pipeline( _sg_pipeline_t * pip, _sg_shader_t * shd, const PipelineDesc * desc )
{
	XE_ASSERT( pip && shd && desc );
	XE_ASSERT( desc->shader.GetValue() == shd->slot.id );
	XE_ASSERT( shd->slot.state == SG_RESOURCESTATE_VALID );
	XE_ASSERT( shd->d3d11.vs_blob && shd->d3d11.vs_blob_length > 0 );
	XE_ASSERT( !pip->d3d11.il && !pip->d3d11.rs && !pip->d3d11.dss && !pip->d3d11.bs );

	pip->shader = shd;
	pip->cmn.init( desc );
	pip->d3d11.index_format = _sg_index_format( pip->cmn.index_type );
	pip->d3d11.topology = _sg_primitive_topology( desc->primitive_type );
	pip->d3d11.stencil_ref = desc->depth_stencil.stencil_ref;

	/* create input layout object */
	HRESULT hr;
	D3D11_INPUT_ELEMENT_DESC d3d11_comps[SG_MAX_VERTEX_ATTRIBUTES];
	memset( d3d11_comps, 0, sizeof( d3d11_comps ) );
	int attr_index = 0;
	for( ; attr_index < SG_MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		const VertexAttrDesc * a_desc = &desc->layout.attrs[attr_index];
		if( a_desc->format == SG_VERTEXFORMAT_INVALID )
		{
			break;
		}
		XE_ASSERT( ( a_desc->buffer_index >= 0 ) && ( a_desc->buffer_index < SG_MAX_SHADERSTAGE_BUFFERS ) );
		const BufferLayoutDesc * l_desc = &desc->layout.buffers[a_desc->buffer_index];
		const VertexStep step_func = l_desc->step_func;
		const int step_rate = l_desc->step_rate;
		D3D11_INPUT_ELEMENT_DESC * d3d11_comp = &d3d11_comps[attr_index];
		d3d11_comp->SemanticName = shd->d3d11.attrs[attr_index].sem_name.ToCString();
		d3d11_comp->SemanticIndex = shd->d3d11.attrs[attr_index].sem_index;
		d3d11_comp->Format = _sg_vertex_format( a_desc->format );
		d3d11_comp->InputSlot = a_desc->buffer_index;
		d3d11_comp->AlignedByteOffset = a_desc->offset;
		d3d11_comp->InputSlotClass = _sg_input_classification( step_func );
		if( SG_VERTEXSTEP_PER_INSTANCE == step_func )
		{
			d3d11_comp->InstanceDataStepRate = step_rate;
		}
		pip->cmn.vertex_layout_valid[a_desc->buffer_index] = true;
	}
	for( int layout_index = 0; layout_index < SG_MAX_SHADERSTAGE_BUFFERS; layout_index++ )
	{
		if( pip->cmn.vertex_layout_valid[layout_index] )
		{
			const BufferLayoutDesc * l_desc = &desc->layout.buffers[layout_index];
			XE_ASSERT( l_desc->stride > 0 );
			pip->d3d11.vb_strides[layout_index] = l_desc->stride;
		}
		else
		{
			pip->d3d11.vb_strides[layout_index] = 0;
		}
	}
	hr = ID3D11Device_CreateInputLayout( _sg.d3d11.dev,
										 d3d11_comps,                /* pInputElementDesc */
										 attr_index,                 /* NumElements */
										 shd->d3d11.vs_blob,         /* pShaderByteCodeWithInputSignature */
										 shd->d3d11.vs_blob_length,  /* BytecodeLength */
										 &pip->d3d11.il );
	XE_ASSERT( SUCCEEDED( hr ) && pip->d3d11.il );

	/* create rasterizer state */
	D3D11_RASTERIZER_DESC rs_desc;
	memset( &rs_desc, 0, sizeof( rs_desc ) );
	rs_desc.FillMode = D3D11_FILL_SOLID;
	rs_desc.CullMode = _sg_cull_mode( desc->rasterizer.cull_mode );
	rs_desc.FrontCounterClockwise = desc->rasterizer.face_winding == SG_FACEWINDING_CCW;
	rs_desc.DepthBias = (INT )pip->cmn.depth_bias;
	rs_desc.DepthBiasClamp = pip->cmn.depth_bias_clamp;
	rs_desc.SlopeScaledDepthBias = pip->cmn.depth_bias_slope_scale;
	rs_desc.DepthClipEnable = TRUE;
	rs_desc.ScissorEnable = TRUE;
	rs_desc.MultisampleEnable = desc->rasterizer.sample_count > 1;
	rs_desc.AntialiasedLineEnable = FALSE;
	hr = ID3D11Device_CreateRasterizerState( _sg.d3d11.dev, &rs_desc, &pip->d3d11.rs );
	XE_ASSERT( SUCCEEDED( hr ) && pip->d3d11.rs );

	/* create depth-stencil state */
	D3D11_DEPTH_STENCIL_DESC dss_desc;
	memset( &dss_desc, 0, sizeof( dss_desc ) );
	dss_desc.DepthEnable = TRUE;
	dss_desc.DepthWriteMask = desc->depth_stencil.depth_write_enabled ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
	dss_desc.DepthFunc = _sg_compare_func( desc->depth_stencil.depth_compare_func );
	dss_desc.StencilEnable = desc->depth_stencil.stencil_enabled;
	dss_desc.StencilReadMask = desc->depth_stencil.stencil_read_mask;
	dss_desc.StencilWriteMask = desc->depth_stencil.stencil_write_mask;
	const StencilState * sf = &desc->depth_stencil.stencil_front;
	dss_desc.FrontFace.StencilFailOp = _sg_stencil_op( sf->fail_op );
	dss_desc.FrontFace.StencilDepthFailOp = _sg_stencil_op( sf->depth_fail_op );
	dss_desc.FrontFace.StencilPassOp = _sg_stencil_op( sf->pass_op );
	dss_desc.FrontFace.StencilFunc = _sg_compare_func( sf->compare_func );
	const StencilState * sb = &desc->depth_stencil.stencil_back;
	dss_desc.BackFace.StencilFailOp = _sg_stencil_op( sb->fail_op );
	dss_desc.BackFace.StencilDepthFailOp = _sg_stencil_op( sb->depth_fail_op );
	dss_desc.BackFace.StencilPassOp = _sg_stencil_op( sb->pass_op );
	dss_desc.BackFace.StencilFunc = _sg_compare_func( sb->compare_func );
	hr = ID3D11Device_CreateDepthStencilState( _sg.d3d11.dev, &dss_desc, &pip->d3d11.dss );
	XE_ASSERT( SUCCEEDED( hr ) && pip->d3d11.dss );

	/* create blend state */
	D3D11_BLEND_DESC bs_desc;
	memset( &bs_desc, 0, sizeof( bs_desc ) );
	bs_desc.AlphaToCoverageEnable = desc->rasterizer.alpha_to_coverage_enabled;
	bs_desc.IndependentBlendEnable = FALSE;
	bs_desc.RenderTarget[0].BlendEnable = desc->blend.enabled;
	bs_desc.RenderTarget[0].SrcBlend = _sg_blend_factor( desc->blend.src_factor_rgb );
	bs_desc.RenderTarget[0].DestBlend = _sg_blend_factor( desc->blend.dst_factor_rgb );
	bs_desc.RenderTarget[0].BlendOp = _sg_blend_op( desc->blend.op_rgb );
	bs_desc.RenderTarget[0].SrcBlendAlpha = _sg_blend_factor( desc->blend.src_factor_alpha );
	bs_desc.RenderTarget[0].DestBlendAlpha = _sg_blend_factor( desc->blend.dst_factor_alpha );
	bs_desc.RenderTarget[0].BlendOpAlpha = _sg_blend_op( desc->blend.op_alpha );
	bs_desc.RenderTarget[0].RenderTargetWriteMask = _sg_color_write_mask( (ColorMask )desc->blend.color_write_mask );
	hr = ID3D11Device_CreateBlendState( _sg.d3d11.dev, &bs_desc, &pip->d3d11.bs );
	XE_ASSERT( SUCCEEDED( hr ) && pip->d3d11.bs );

	return SG_RESOURCESTATE_VALID;
}

void _sg_destroy_pipeline( _sg_pipeline_t * pip )
{
	XE_ASSERT( pip );
	if( pip->d3d11.il )
	{
		ID3D11InputLayout_Release( pip->d3d11.il );
	}
	if( pip->d3d11.rs )
	{
		ID3D11RasterizerState_Release( pip->d3d11.rs );
	}
	if( pip->d3d11.dss )
	{
		ID3D11DepthStencilState_Release( pip->d3d11.dss );
	}
	if( pip->d3d11.bs )
	{
		ID3D11BlendState_Release( pip->d3d11.bs );
	}
}

ResourceState _sg_create_pass( _sg_pass_t * pass, _sg_image_t ** att_images, const PassDesc * desc )
{
	XE_ASSERT( pass && desc );
	XE_ASSERT( att_images && att_images[0] );
	XE_ASSERT( _sg.d3d11.dev );

	pass->cmn.init( desc );

	for( int i = 0; i < pass->cmn.num_color_atts; i++ )
	{
		const AttachmentDesc * att_desc = &desc->color_attachments[i];
		XE_ASSERT( att_desc->image );
		_sg_image_t * att_img = att_images[i];
		XE_ASSERT( att_img && ( att_img->slot.id == att_desc->image.GetValue() ) );
		XE_ASSERT( _sg_is_valid_rendertarget_color_format( att_img->cmn.pixel_format ) );
		XE_ASSERT( 0 == pass->d3d11.color_atts[i].image );
		pass->d3d11.color_atts[i].image = att_img;

		/* create D3D11 render-target-view */
		const _sg_attachment_t * cmn_att = &pass->cmn.color_atts[i];
		XE_ASSERT( 0 == pass->d3d11.color_atts[i].rtv );
		ID3D11Resource * d3d11_res = 0;
		const bool is_msaa = att_img->cmn.sample_count > 1;
		D3D11_RENDER_TARGET_VIEW_DESC d3d11_rtv_desc;
		memset( &d3d11_rtv_desc, 0, sizeof( d3d11_rtv_desc ) );
		d3d11_rtv_desc.Format = att_img->d3d11.format;
		if( ( att_img->cmn.type == SG_IMAGETYPE_2D ) || is_msaa )
		{
			if( is_msaa )
			{
				d3d11_res = (ID3D11Resource * )att_img->d3d11.texmsaa;
				d3d11_rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			}
			else
			{
				d3d11_res = (ID3D11Resource * )att_img->d3d11.tex2d;
				d3d11_rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
				d3d11_rtv_desc.Texture2D.MipSlice = cmn_att->mip_level;
			}
		}
		else if( ( att_img->cmn.type == SG_IMAGETYPE_CUBE ) || ( att_img->cmn.type == SG_IMAGETYPE_ARRAY ) )
		{
			d3d11_res = (ID3D11Resource * )att_img->d3d11.tex2d;
			d3d11_rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
			d3d11_rtv_desc.Texture2DArray.MipSlice = cmn_att->mip_level;
			d3d11_rtv_desc.Texture2DArray.FirstArraySlice = cmn_att->slice;
			d3d11_rtv_desc.Texture2DArray.ArraySize = 1;
		}
		else
		{
			XE_ASSERT( att_img->cmn.type == SG_IMAGETYPE_3D );
			d3d11_res = (ID3D11Resource * )att_img->d3d11.tex3d;
			d3d11_rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
			d3d11_rtv_desc.Texture3D.MipSlice = cmn_att->mip_level;
			d3d11_rtv_desc.Texture3D.FirstWSlice = cmn_att->slice;
			d3d11_rtv_desc.Texture3D.WSize = 1;
		}
		XE_ASSERT( d3d11_res );
		HRESULT hr = ID3D11Device_CreateRenderTargetView( _sg.d3d11.dev, d3d11_res, &d3d11_rtv_desc, &pass->d3d11.color_atts[i].rtv );
		(void)( hr );
		XE_ASSERT( SUCCEEDED( hr ) && pass->d3d11.color_atts[i].rtv );
	}

	/* optional depth-stencil image */
	XE_ASSERT( 0 == pass->d3d11.ds_att.image );
	XE_ASSERT( 0 == pass->d3d11.ds_att.dsv );
	if( desc->depth_stencil_attachment.image )
	{
		const int ds_img_index = SG_MAX_COLOR_ATTACHMENTS;
		const AttachmentDesc * att_desc = &desc->depth_stencil_attachment;
		_sg_image_t * att_img = att_images[ds_img_index];
		XE_ASSERT( att_img && ( att_img->slot.id == att_desc->image.GetValue() ) );
		XE_ASSERT( _sg_is_valid_rendertarget_depth_format( att_img->cmn.pixel_format ) );
		XE_ASSERT( 0 == pass->d3d11.ds_att.image );
		pass->d3d11.ds_att.image = att_img;

		/* create D3D11 depth-stencil-view */
		D3D11_DEPTH_STENCIL_VIEW_DESC d3d11_dsv_desc;
		memset( &d3d11_dsv_desc, 0, sizeof( d3d11_dsv_desc ) );
		d3d11_dsv_desc.Format = att_img->d3d11.format;
		const bool is_msaa = att_img->cmn.sample_count > 1;
		if( is_msaa )
		{
			d3d11_dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			d3d11_dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		}
		ID3D11Resource * d3d11_res = (ID3D11Resource * )att_img->d3d11.texds;
		XE_ASSERT( d3d11_res );
		HRESULT hr = ID3D11Device_CreateDepthStencilView( _sg.d3d11.dev, d3d11_res, &d3d11_dsv_desc, &pass->d3d11.ds_att.dsv );
		(void)( hr );
		XE_ASSERT( SUCCEEDED( hr ) && pass->d3d11.ds_att.dsv );
	}
	return SG_RESOURCESTATE_VALID;
}

void _sg_destroy_pass( _sg_pass_t * pass )
{
	XE_ASSERT( pass );
	for( int i = 0; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
	{
		if( pass->d3d11.color_atts[i].rtv )
		{
			ID3D11RenderTargetView_Release( pass->d3d11.color_atts[i].rtv );
		}
	}
	if( pass->d3d11.ds_att.dsv )
	{
		ID3D11DepthStencilView_Release( pass->d3d11.ds_att.dsv );
	}
}

_sg_image_t * _sg_pass_color_image( const _sg_pass_t * pass, int index )
{
	XE_ASSERT( pass && ( index >= 0 ) && ( index < SG_MAX_COLOR_ATTACHMENTS ) );
	/* NOTE: may return null */
	return pass->d3d11.color_atts[index].image;
}

_sg_image_t * _sg_pass_ds_image( const _sg_pass_t * pass )
{
	/* NOTE: may return null */
	XE_ASSERT( pass );
	return pass->d3d11.ds_att.image;
}

void _sg_begin_pass( _sg_pass_t * pass, const PassAction * action, int w, int h )
{
	XE_ASSERT( action );
	XE_ASSERT( !_sg.d3d11.in_pass );
	_sg.d3d11.in_pass = true;
	_sg.d3d11.cur_width = w;
	_sg.d3d11.cur_height = h;
	if( pass )
	{
		_sg.d3d11.cur_pass = pass;
		_sg.d3d11.cur_pass_id = pass->slot.id;
		_sg.d3d11.num_rtvs = 0;
		for( int i = 0; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
		{
			_sg.d3d11.cur_rtvs[i] = pass->d3d11.color_atts[i].rtv;
			if( _sg.d3d11.cur_rtvs[i] )
			{
				_sg.d3d11.num_rtvs++;
			}
		}
		_sg.d3d11.cur_dsv = pass->d3d11.ds_att.dsv;
	}
	else
	{
		/* render to default frame buffer */
		_sg.d3d11.cur_pass = 0;
		_sg.d3d11.cur_pass_id = XE::PassHandle::Invalid;
		_sg.d3d11.num_rtvs = 1;
		_sg.d3d11.cur_rtvs[0] = (ID3D11RenderTargetView * )_sg.d3d11.rtv_cb();
		for( int i = 1; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
		{
			_sg.d3d11.cur_rtvs[i] = 0;
		}
		_sg.d3d11.cur_dsv = (ID3D11DepthStencilView * )_sg.d3d11.dsv_cb();
		XE_ASSERT( _sg.d3d11.cur_rtvs[0] && _sg.d3d11.cur_dsv );
	}
	/* apply the render-target- and depth-stencil-views */
	ID3D11DeviceContext_OMSetRenderTargets( _sg.d3d11.ctx, SG_MAX_COLOR_ATTACHMENTS, _sg.d3d11.cur_rtvs, _sg.d3d11.cur_dsv );

	/* set viewport and scissor rect to cover whole screen */
	D3D11_VIEWPORT vp;
	memset( &vp, 0, sizeof( vp ) );
	vp.Width = (FLOAT )w;
	vp.Height = (FLOAT )h;
	vp.MaxDepth = 1.0f;
	ID3D11DeviceContext_RSSetViewports( _sg.d3d11.ctx, 1, &vp );
	D3D11_RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = w;
	rect.bottom = h;
	ID3D11DeviceContext_RSSetScissorRects( _sg.d3d11.ctx, 1, &rect );

	/* perform clear action */
	for( int i = 0; i < _sg.d3d11.num_rtvs; i++ )
	{
		if( action->colors[i].action == SG_ACTION_CLEAR )
		{
			ID3D11DeviceContext_ClearRenderTargetView( _sg.d3d11.ctx, _sg.d3d11.cur_rtvs[i], action->colors[i].val );
		}
	}
	UINT ds_flags = 0;
	if( action->depth.action == SG_ACTION_CLEAR )
	{
		ds_flags |= D3D11_CLEAR_DEPTH;
	}
	if( action->stencil.action == SG_ACTION_CLEAR )
	{
		ds_flags |= D3D11_CLEAR_STENCIL;
	}
	if( ( 0 != ds_flags ) && _sg.d3d11.cur_dsv )
	{
		ID3D11DeviceContext_ClearDepthStencilView( _sg.d3d11.ctx, _sg.d3d11.cur_dsv, ds_flags, action->depth.val, action->stencil.val );
	}
}

UINT _sg_calcsubresource( UINT mip_slice, UINT array_slice, UINT mip_levels )
{
	return mip_slice + array_slice * mip_levels;
}

void _sg_end_pass( void )
{
	XE_ASSERT( _sg.d3d11.in_pass && _sg.d3d11.ctx );
	_sg.d3d11.in_pass = false;

	/* need to resolve MSAA render target into texture? */
	if( _sg.d3d11.cur_pass )
	{
		XE_ASSERT( _sg.d3d11.cur_pass->slot.id == _sg.d3d11.cur_pass_id.GetValue() );
		for( int i = 0; i < _sg.d3d11.num_rtvs; i++ )
		{
			_sg_attachment_t * cmn_att = &_sg.d3d11.cur_pass->cmn.color_atts[i];
			_sg_image_t * att_img = _sg.d3d11.cur_pass->d3d11.color_atts[i].image;
			XE_ASSERT( att_img && ( att_img->slot.id == cmn_att->image_id.GetValue() ) );
			if( att_img->cmn.sample_count > 1 )
			{
				/* FIXME: support MSAA resolve into 3D texture */
				XE_ASSERT( att_img->d3d11.tex2d && att_img->d3d11.texmsaa && !att_img->d3d11.tex3d );
				XE_ASSERT( DXGI_FORMAT_UNKNOWN != att_img->d3d11.format );
				UINT dst_subres = _sg_calcsubresource( cmn_att->mip_level, cmn_att->slice, att_img->cmn.num_mipmaps );
				ID3D11DeviceContext_ResolveSubresource( _sg.d3d11.ctx,
					(ID3D11Resource * )att_img->d3d11.tex2d,     /* pDstResource */
														dst_subres,                                 /* DstSubresource */
														(ID3D11Resource * )att_img->d3d11.texmsaa,   /* pSrcResource */
														0,                                          /* SrcSubresource */
														att_img->d3d11.format );
			}
		}
	}
	_sg.d3d11.cur_pass = 0;
	_sg.d3d11.cur_pass_id = XE::PassHandle::Invalid;
	_sg.d3d11.cur_pipeline = 0;
	_sg.d3d11.cur_pipeline_id = XE::PipelineHandle::Invalid;
	for( int i = 0; i < SG_MAX_COLOR_ATTACHMENTS; i++ )
	{
		_sg.d3d11.cur_rtvs[i] = 0;
	}
	_sg.d3d11.cur_dsv = 0;
	_sg_clear_state();
}

void _sg_apply_viewport( int x, int y, int w, int h, bool origin_top_left )
{
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( _sg.d3d11.in_pass );
	D3D11_VIEWPORT vp;
	vp.TopLeftX = (FLOAT )x;
	vp.TopLeftY = (FLOAT )( origin_top_left ? y : ( _sg.d3d11.cur_height - ( y + h ) ) );
	vp.Width = (FLOAT )w;
	vp.Height = (FLOAT )h;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	ID3D11DeviceContext_RSSetViewports( _sg.d3d11.ctx, 1, &vp );
}

void _sg_apply_scissor_rect( int x, int y, int w, int h, bool origin_top_left )
{
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( _sg.d3d11.in_pass );
	D3D11_RECT rect;
	rect.left = x;
	rect.top = ( origin_top_left ? y : ( _sg.d3d11.cur_height - ( y + h ) ) );
	rect.right = x + w;
	rect.bottom = origin_top_left ? ( y + h ) : ( _sg.d3d11.cur_height - y );
	ID3D11DeviceContext_RSSetScissorRects( _sg.d3d11.ctx, 1, &rect );
}

void _sg_apply_pipeline( _sg_pipeline_t * pip )
{
	XE_ASSERT( pip );
	XE_ASSERT( pip->shader );
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( _sg.d3d11.in_pass );
	XE_ASSERT( pip->d3d11.rs && pip->d3d11.bs && pip->d3d11.dss && pip->d3d11.il );

	_sg.d3d11.cur_pipeline = pip;
	_sg.d3d11.cur_pipeline_id = pip->slot.id;
	_sg.d3d11.use_indexed_draw = ( pip->d3d11.index_format != DXGI_FORMAT_UNKNOWN );

	ID3D11DeviceContext_RSSetState( _sg.d3d11.ctx, pip->d3d11.rs );
	ID3D11DeviceContext_OMSetDepthStencilState( _sg.d3d11.ctx, pip->d3d11.dss, pip->d3d11.stencil_ref );
	ID3D11DeviceContext_OMSetBlendState( _sg.d3d11.ctx, pip->d3d11.bs, pip->cmn.blend_color, 0xFFFFFFFF );
	ID3D11DeviceContext_IASetPrimitiveTopology( _sg.d3d11.ctx, pip->d3d11.topology );
	ID3D11DeviceContext_IASetInputLayout( _sg.d3d11.ctx, pip->d3d11.il );
	ID3D11DeviceContext_VSSetShader( _sg.d3d11.ctx, pip->shader->d3d11.vs, NULL, 0 );
	ID3D11DeviceContext_VSSetConstantBuffers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_UBS, pip->shader->d3d11.stage[SG_SHADERSTAGE_VS].cbufs );
	ID3D11DeviceContext_PSSetShader( _sg.d3d11.ctx, pip->shader->d3d11.fs, NULL, 0 );
	ID3D11DeviceContext_PSSetConstantBuffers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_UBS, pip->shader->d3d11.stage[SG_SHADERSTAGE_FS].cbufs );
}

void _sg_apply_bindings(
	_sg_pipeline_t * pip,
	_sg_buffer_t ** vbs, const int * vb_offsets, int num_vbs,
	_sg_buffer_t * ib, int ib_offset,
	_sg_image_t ** vs_imgs, int num_vs_imgs,
	_sg_image_t ** fs_imgs, int num_fs_imgs )
{
	XE_ASSERT( pip );
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( _sg.d3d11.in_pass );

	/* gather all the D3D11 resources into arrays */
	ID3D11Buffer * d3d11_ib = ib ? ib->d3d11.buf : 0;
	ID3D11Buffer * d3d11_vbs[SG_MAX_SHADERSTAGE_BUFFERS];
	UINT d3d11_vb_offsets[SG_MAX_SHADERSTAGE_BUFFERS];
	ID3D11ShaderResourceView * d3d11_vs_srvs[SG_MAX_SHADERSTAGE_IMAGES];
	ID3D11SamplerState * d3d11_vs_smps[SG_MAX_SHADERSTAGE_IMAGES];
	ID3D11ShaderResourceView * d3d11_fs_srvs[SG_MAX_SHADERSTAGE_IMAGES];
	ID3D11SamplerState * d3d11_fs_smps[SG_MAX_SHADERSTAGE_IMAGES];
	int i;
	for( i = 0; i < num_vbs; i++ )
	{
		XE_ASSERT( vbs[i]->d3d11.buf );
		d3d11_vbs[i] = vbs[i]->d3d11.buf;
		d3d11_vb_offsets[i] = vb_offsets[i];
	}
	for( ; i < SG_MAX_SHADERSTAGE_BUFFERS; i++ )
	{
		d3d11_vbs[i] = 0;
		d3d11_vb_offsets[i] = 0;
	}
	for( i = 0; i < num_vs_imgs; i++ )
	{
		XE_ASSERT( vs_imgs[i]->d3d11.srv );
		XE_ASSERT( vs_imgs[i]->d3d11.smp );
		d3d11_vs_srvs[i] = vs_imgs[i]->d3d11.srv;
		d3d11_vs_smps[i] = vs_imgs[i]->d3d11.smp;
	}
	for( ; i < SG_MAX_SHADERSTAGE_IMAGES; i++ )
	{
		d3d11_vs_srvs[i] = 0;
		d3d11_vs_smps[i] = 0;
	}
	for( i = 0; i < num_fs_imgs; i++ )
	{
		XE_ASSERT( fs_imgs[i]->d3d11.srv );
		XE_ASSERT( fs_imgs[i]->d3d11.smp );
		d3d11_fs_srvs[i] = fs_imgs[i]->d3d11.srv;
		d3d11_fs_smps[i] = fs_imgs[i]->d3d11.smp;
	}
	for( ; i < SG_MAX_SHADERSTAGE_IMAGES; i++ )
	{
		d3d11_fs_srvs[i] = 0;
		d3d11_fs_smps[i] = 0;
	}

	ID3D11DeviceContext_IASetVertexBuffers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_BUFFERS, d3d11_vbs, pip->d3d11.vb_strides, d3d11_vb_offsets );
	ID3D11DeviceContext_IASetIndexBuffer( _sg.d3d11.ctx, d3d11_ib, pip->d3d11.index_format, ib_offset );
	ID3D11DeviceContext_VSSetShaderResources( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, d3d11_vs_srvs );
	ID3D11DeviceContext_VSSetSamplers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, d3d11_vs_smps );
	ID3D11DeviceContext_PSSetShaderResources( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, d3d11_fs_srvs );
	ID3D11DeviceContext_PSSetSamplers( _sg.d3d11.ctx, 0, SG_MAX_SHADERSTAGE_IMAGES, d3d11_fs_smps );
}

void _sg_apply_uniforms( ShaderStage stage_index, int ub_index, const void * data, int num_bytes )
{
	(void)( num_bytes );
	XE_ASSERT( _sg.d3d11.ctx && _sg.d3d11.in_pass );
	XE_ASSERT( data && ( num_bytes > 0 ) );
	XE_ASSERT( ( stage_index >= 0 ) && ( (int )stage_index < SG_NUM_SHADER_STAGES ) );
	XE_ASSERT( ( ub_index >= 0 ) && ( ub_index < SG_MAX_SHADERSTAGE_UBS ) );
	XE_ASSERT( _sg.d3d11.cur_pipeline && _sg.d3d11.cur_pipeline->slot.id == _sg.d3d11.cur_pipeline_id.GetValue() );
	XE_ASSERT( _sg.d3d11.cur_pipeline->shader && _sg.d3d11.cur_pipeline->shader->slot.id == _sg.d3d11.cur_pipeline->cmn.shader_id.GetValue() );
	XE_ASSERT( ub_index < _sg.d3d11.cur_pipeline->shader->cmn.stage[stage_index].num_uniform_blocks );
	XE_ASSERT( num_bytes == _sg.d3d11.cur_pipeline->shader->cmn.stage[stage_index].uniform_blocks[ub_index].size );
	ID3D11Buffer * cb = _sg.d3d11.cur_pipeline->shader->d3d11.stage[stage_index].cbufs[ub_index];
	XE_ASSERT( cb );
	ID3D11DeviceContext_UpdateSubresource( _sg.d3d11.ctx, (ID3D11Resource * )cb, 0, NULL, data, 0, 0 );
}

void _sg_draw( int base_element, int num_elements, int num_instances )
{
	XE_ASSERT( _sg.d3d11.in_pass );
	if( _sg.d3d11.use_indexed_draw )
	{
		if( 1 == num_instances )
		{
			ID3D11DeviceContext_DrawIndexed( _sg.d3d11.ctx, num_elements, base_element, 0 );
		}
		else
		{
			ID3D11DeviceContext_DrawIndexedInstanced( _sg.d3d11.ctx, num_elements, num_instances, base_element, 0, 0 );
		}
	}
	else
	{
		if( 1 == num_instances )
		{
			ID3D11DeviceContext_Draw( _sg.d3d11.ctx, num_elements, base_element );
		}
		else
		{
			ID3D11DeviceContext_DrawInstanced( _sg.d3d11.ctx, num_elements, num_instances, base_element, 0 );
		}
	}
}

void _sg_commit( void )
{
	XE_ASSERT( !_sg.d3d11.in_pass );
}

void _sg_update_buffer( _sg_buffer_t * buf, const void * data_ptr, int data_size )
{
	XE_ASSERT( buf && data_ptr && ( data_size > 0 ) );
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( buf->d3d11.buf );
	D3D11_MAPPED_SUBRESOURCE d3d11_msr;
	HRESULT hr = ID3D11DeviceContext_Map( _sg.d3d11.ctx, (ID3D11Resource * )buf->d3d11.buf, 0, D3D11_MAP_WRITE_DISCARD, 0, &d3d11_msr );
	(void)( hr );
	XE_ASSERT( SUCCEEDED( hr ) );
	memcpy( d3d11_msr.pData, data_ptr, data_size );
	ID3D11DeviceContext_Unmap( _sg.d3d11.ctx, (ID3D11Resource * )buf->d3d11.buf, 0 );
}

void _sg_append_buffer( _sg_buffer_t * buf, const void * data_ptr, int data_size, bool new_frame )
{
	XE_ASSERT( buf && data_ptr && ( data_size > 0 ) );
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( buf->d3d11.buf );
	D3D11_MAP map_type = new_frame ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
	D3D11_MAPPED_SUBRESOURCE d3d11_msr;
	HRESULT hr = ID3D11DeviceContext_Map( _sg.d3d11.ctx, (ID3D11Resource * )buf->d3d11.buf, 0, map_type, 0, &d3d11_msr );
	(void)( hr );
	XE_ASSERT( SUCCEEDED( hr ) );
	uint8_t * dst_ptr = (uint8_t * )d3d11_msr.pData + buf->cmn.append_pos;
	memcpy( dst_ptr, data_ptr, data_size );
	ID3D11DeviceContext_Unmap( _sg.d3d11.ctx, (ID3D11Resource * )buf->d3d11.buf, 0 );
}

void _sg_update_image( _sg_image_t * img, const ImageContent * data )
{
	XE_ASSERT( img && data );
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( img->d3d11.tex2d || img->d3d11.tex3d );
	ID3D11Resource * d3d11_res = 0;
	if( img->d3d11.tex3d )
	{
		d3d11_res = (ID3D11Resource * )img->d3d11.tex3d;
	}
	else
	{
		d3d11_res = (ID3D11Resource * )img->d3d11.tex2d;
	}
	XE_ASSERT( d3d11_res );
	const int num_faces = ( img->cmn.type == SG_IMAGETYPE_CUBE ) ? 6 : 1;
	const int num_slices = ( img->cmn.type == SG_IMAGETYPE_ARRAY ) ? img->cmn.depth : 1;
	int subres_index = 0;
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE d3d11_msr;
	for( int face_index = 0; face_index < num_faces; face_index++ )
	{
		for( int slice_index = 0; slice_index < num_slices; slice_index++ )
		{
			for( int mip_index = 0; mip_index < img->cmn.num_mipmaps; mip_index++, subres_index++ )
			{
				XE_ASSERT( subres_index < ( SG_MAX_MIPMAPS * SG_MAX_TEXTUREARRAY_LAYERS ) );
				const int mip_width = ( ( img->cmn.width >> mip_index ) > 0 ) ? img->cmn.width >> mip_index : 1;
				const int mip_height = ( ( img->cmn.height >> mip_index ) > 0 ) ? img->cmn.height >> mip_index : 1;
				const int src_pitch = _sg_row_pitch( img->cmn.pixel_format, mip_width );
				const SubimageContent * subimg_content = &( data->subimage[face_index][mip_index] );
				const int slice_size = subimg_content->size / num_slices;
				const int slice_offset = slice_size * slice_index;
				const uint8_t * slice_ptr = ( (const uint8_t * )subimg_content->ptr ) + slice_offset;
				hr = ID3D11DeviceContext_Map( _sg.d3d11.ctx, d3d11_res, subres_index, D3D11_MAP_WRITE_DISCARD, 0, &d3d11_msr );
				XE_ASSERT( SUCCEEDED( hr ) );
				/* FIXME: need to handle difference in depth-pitch for 3D textures as well! */
				if( src_pitch == (int )d3d11_msr.RowPitch )
				{
					memcpy( d3d11_msr.pData, slice_ptr, slice_size );
				}
				else
				{
					XE_ASSERT( src_pitch < (int )d3d11_msr.RowPitch );
					const uint8_t * src_ptr = slice_ptr;
					uint8_t * dst_ptr = (uint8_t * )d3d11_msr.pData;
					for( int row_index = 0; row_index < mip_height; row_index++ )
					{
						memcpy( dst_ptr, src_ptr, src_pitch );
						src_ptr += src_pitch;
						dst_ptr += d3d11_msr.RowPitch;
					}
				}
				ID3D11DeviceContext_Unmap( _sg.d3d11.ctx, d3d11_res, subres_index );
			}
		}
	}
}

#endif