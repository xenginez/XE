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
#include <windowsx.h>
#include <d3d11.h>
#include <dxgi.h>
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
	_SlotType slot;
	_BufferCommonType cmn;
	struct
	{
		ID3D11Buffer * buf;
	} d3d11;
} _D3D11BufferType;
typedef _D3D11BufferType _BufferType;

typedef struct
{
	_SlotType slot;
	_ImageCommonType cmn;
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
} _D3D11ImageType;
typedef _D3D11ImageType _ImageType;

typedef struct
{
	XE::String sem_name;
	XE::int32 sem_index;
} _D3D11ShaderAttrType;

typedef struct
{
	ID3D11Buffer * cbufs[MAX_SHADERSTAGE_UBS];
} _D3D11ShaderStageType;

typedef struct
{
	_SlotType slot;
	_ShaderCommonType cmn;
	struct
	{
		_D3D11ShaderAttrType attrs[MAX_VERTEX_ATTRIBUTES];
		_D3D11ShaderStageType stage[NUM_SHADER_STAGES];
		ID3D11VertexShader * vs;
		ID3D11PixelShader * fs;
		void * vs_blob;
		XE::int32 vs_blob_length;
	} d3d11;
} _D3D11ShaderType;
typedef _D3D11ShaderType _ShaderType;

typedef struct
{
	_SlotType slot;
	_PipelineCommonType cmn;
	_ShaderType * shader;
	struct
	{
		XE::uint32 stencil_ref;
		XE::uint32 vb_strides[MAX_SHADERSTAGE_BUFFERS];
		D3D_PRIMITIVE_TOPOLOGY topology;
		DXGI_FORMAT index_format;
		ID3D11InputLayout * il;
		ID3D11RasterizerState * rs;
		ID3D11DepthStencilState * dss;
		ID3D11BlendState * bs;
	} d3d11;
} _D3D11PipelineType;
typedef _D3D11PipelineType _PipelineType;

typedef struct
{
	_ImageType * image;
	ID3D11RenderTargetView * rtv;
} _D3D11ColorAttachmentType;

typedef struct
{
	_ImageType * image;
	ID3D11DepthStencilView * dsv;
} _D3D11DSAttachmentType;

typedef struct
{
	_SlotType slot;
	_PassCommonType cmn;
	struct
	{
		_D3D11ColorAttachmentType color_atts[MAX_COLOR_ATTACHMENTS];
		_D3D11DSAttachmentType ds_att;
	} d3d11;
} _D3D11PassType;
typedef _D3D11PassType _PassType;
typedef _AttachmentCommonType _AttachmentType;

typedef struct
{
	_SlotType slot;
} _D3D11ContextType;
typedef _D3D11ContextType _ContextType;

typedef struct
{
	bool valid;
	ID3D11Device * dev;
	ID3D11DeviceContext * ctx;
	bool in_pass;
	bool use_indexed_draw;
	XE::int32 cur_width;
	XE::int32 cur_height;
	XE::int32 num_rtvs;
	_PassType * cur_pass;
	PassHandle cur_pass_id;
	_PipelineType * cur_pipeline;
	PipelineHandle cur_pipeline_id;
	ID3D11RenderTargetView * cur_rtvs[MAX_COLOR_ATTACHMENTS];
	ID3D11DepthStencilView * cur_dsv;
	/* on-demand loaded d3dcompiler_47.dll handles */
	HINSTANCE d3dcompiler_dll;
	bool d3dcompiler_dll_load_failed;
	pD3DCompile D3DCompile_func;
	/* the following arrays are used for unbinding resources, they will always contain zeroes */
	ID3D11RenderTargetView * zero_rtvs[MAX_COLOR_ATTACHMENTS];
	ID3D11Buffer * zero_vbs[MAX_SHADERSTAGE_BUFFERS];
	XE::uint32 zero_vb_offsets[MAX_SHADERSTAGE_BUFFERS];
	XE::uint32 zero_vb_strides[MAX_SHADERSTAGE_BUFFERS];
	ID3D11Buffer * zero_cbs[MAX_SHADERSTAGE_UBS];
	ID3D11ShaderResourceView * zero_srvs[MAX_SHADERSTAGE_IMAGES];
	ID3D11SamplerState * zero_smps[MAX_SHADERSTAGE_IMAGES];
	/* global subresourcedata array for texture updates */
	D3D11_SUBRESOURCE_DATA subres_data[MAX_MIPMAPS * MAX_TEXTUREARRAY_LAYERS];

	ID3D11Device * device;
	ID3D11DeviceContext * device_context;
	IDXGISwapChain * swap_chain;
	ID3D11Texture2D * render_target;
	ID3D11RenderTargetView * render_target_view;
	ID3D11Texture2D * depth_stencil_buffer;
	ID3D11DepthStencilView * depth_stencil_view;

} _D3D11BackendType;
typedef _D3D11BackendType _BackendType;

typedef struct
{
	_PoolType buffer_pool;
	_PoolType image_pool;
	_PoolType shader_pool;
	_PoolType pipeline_pool;
	_PoolType pass_pool;
	_PoolType context_pool;
	_BufferType * buffers;
	_ImageType * images;
	_ShaderType * shaders;
	_PipelineType * pipelines;
	_PassType * passes;
	_ContextType * contexts;
} _PoolsType;

typedef struct
{
	bool valid;
	GfxDesc desc;       /* original desc with default values patched in */
	XE::uint32 frame_index;
	ContextHandle active_context;
	PassHandle cur_pass;
	PipelineHandle cur_pipeline;
	bool pass_valid;
	bool bindings_valid;
	bool next_draw_valid;
	_ValidateErrorType validate_error;
	_PoolsType pools;
	Backend backend;
	Features features;
	Limits limits;
	PixelFormatInfo formats[_PIXELFORMAT_NUM];
	_BackendType d3d11;
	GfxTraceHooks * hooks;
} _StateType;

static _StateType _sg;



/* the default color pixelformat for render targets */
PixelFormat _default_rendertarget_colorformat( void )
{
	return PIXELFORMAT_BGRA8;
}

/* return true if pixel format is a valid render target format */
bool _is_valid_rendertarget_color_format( PixelFormat fmt )
{
	const XE::int32 fmt_index = (XE::int32 )fmt;
	XE_ASSERT( ( fmt_index >= 0 ) && ( fmt_index < _PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index].render && !_sg.formats[fmt_index].depth;
}

/* return true if pixel format is a valid depth format */
bool _is_valid_rendertarget_depth_format( PixelFormat fmt )
{
	const XE::int32 fmt_index = (XE::int32 )fmt;
	XE_ASSERT( ( fmt_index >= 0 ) && ( fmt_index < _PIXELFORMAT_NUM ) );
	return _sg.formats[fmt_index].render && _sg.formats[fmt_index].depth;
}




/*-- enum translation functions ----------------------------------------------*/
D3D11_USAGE _usage( Usage usg )
{
	switch( usg )
	{
	case USAGE_IMMUTABLE:
		return D3D11_USAGE_IMMUTABLE;
	case USAGE_DYNAMIC:
	case USAGE_STREAM:
		return D3D11_USAGE_DYNAMIC;
	default:
		XE_ASSERT(false);
		return (D3D11_USAGE )0;
	}
}

XE::uint32 _cpu_access_flags( Usage usg )
{
	switch( usg )
	{
	case USAGE_IMMUTABLE:
		return 0;
	case USAGE_DYNAMIC:
	case USAGE_STREAM:
		return D3D11_CPU_ACCESS_WRITE;
	default:
		XE_ASSERT(false);
		return 0;
	}
}

DXGI_FORMAT _pixel_format( PixelFormat fmt )
{
	switch( fmt )
	{
	case PIXELFORMAT_R8:             return DXGI_FORMAT_R8_UNORM;
	case PIXELFORMAT_R8SN:           return DXGI_FORMAT_R8_SNORM;
	case PIXELFORMAT_R8UI:           return DXGI_FORMAT_R8_UINT;
	case PIXELFORMAT_R8SI:           return DXGI_FORMAT_R8_SINT;
	case PIXELFORMAT_R16:            return DXGI_FORMAT_R16_UNORM;
	case PIXELFORMAT_R16SN:          return DXGI_FORMAT_R16_SNORM;
	case PIXELFORMAT_R16UI:          return DXGI_FORMAT_R16_UINT;
	case PIXELFORMAT_R16SI:          return DXGI_FORMAT_R16_SINT;
	case PIXELFORMAT_R16F:           return DXGI_FORMAT_R16_FLOAT;
	case PIXELFORMAT_RG8:            return DXGI_FORMAT_R8G8_UNORM;
	case PIXELFORMAT_RG8SN:          return DXGI_FORMAT_R8G8_SNORM;
	case PIXELFORMAT_RG8UI:          return DXGI_FORMAT_R8G8_UINT;
	case PIXELFORMAT_RG8SI:          return DXGI_FORMAT_R8G8_SINT;
	case PIXELFORMAT_R32UI:          return DXGI_FORMAT_R32_UINT;
	case PIXELFORMAT_R32SI:          return DXGI_FORMAT_R32_SINT;
	case PIXELFORMAT_R32F:           return DXGI_FORMAT_R32_FLOAT;
	case PIXELFORMAT_RG16:           return DXGI_FORMAT_R16G16_UNORM;
	case PIXELFORMAT_RG16SN:         return DXGI_FORMAT_R16G16_SNORM;
	case PIXELFORMAT_RG16UI:         return DXGI_FORMAT_R16G16_UINT;
	case PIXELFORMAT_RG16SI:         return DXGI_FORMAT_R16G16_SINT;
	case PIXELFORMAT_RG16F:          return DXGI_FORMAT_R16G16_FLOAT;
	case PIXELFORMAT_RGBA8:          return DXGI_FORMAT_R8G8B8A8_UNORM;
	case PIXELFORMAT_RGBA8SN:        return DXGI_FORMAT_R8G8B8A8_SNORM;
	case PIXELFORMAT_RGBA8UI:        return DXGI_FORMAT_R8G8B8A8_UINT;
	case PIXELFORMAT_RGBA8SI:        return DXGI_FORMAT_R8G8B8A8_SINT;
	case PIXELFORMAT_BGRA8:          return DXGI_FORMAT_B8G8R8A8_UNORM;
	case PIXELFORMAT_RGB10A2:        return DXGI_FORMAT_R10G10B10A2_UNORM;
	case PIXELFORMAT_RG11B10F:       return DXGI_FORMAT_R11G11B10_FLOAT;
	case PIXELFORMAT_RG32UI:         return DXGI_FORMAT_R32G32_UINT;
	case PIXELFORMAT_RG32SI:         return DXGI_FORMAT_R32G32_SINT;
	case PIXELFORMAT_RG32F:          return DXGI_FORMAT_R32G32_FLOAT;
	case PIXELFORMAT_RGBA16:         return DXGI_FORMAT_R16G16B16A16_UNORM;
	case PIXELFORMAT_RGBA16SN:       return DXGI_FORMAT_R16G16B16A16_SNORM;
	case PIXELFORMAT_RGBA16UI:       return DXGI_FORMAT_R16G16B16A16_UINT;
	case PIXELFORMAT_RGBA16SI:       return DXGI_FORMAT_R16G16B16A16_SINT;
	case PIXELFORMAT_RGBA16F:        return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case PIXELFORMAT_RGBA32UI:       return DXGI_FORMAT_R32G32B32A32_UINT;
	case PIXELFORMAT_RGBA32SI:       return DXGI_FORMAT_R32G32B32A32_SINT;
	case PIXELFORMAT_RGBA32F:        return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case PIXELFORMAT_DEPTH:          return DXGI_FORMAT_D32_FLOAT;
	case PIXELFORMAT_DEPTH_STENCIL:  return DXGI_FORMAT_D24_UNORM_S8_UINT;
	case PIXELFORMAT_BC1_RGBA:       return DXGI_FORMAT_BC1_UNORM;
	case PIXELFORMAT_BC2_RGBA:       return DXGI_FORMAT_BC2_UNORM;
	case PIXELFORMAT_BC3_RGBA:       return DXGI_FORMAT_BC3_UNORM;
	case PIXELFORMAT_BC4_R:          return DXGI_FORMAT_BC4_UNORM;
	case PIXELFORMAT_BC4_RSN:        return DXGI_FORMAT_BC4_SNORM;
	case PIXELFORMAT_BC5_RG:         return DXGI_FORMAT_BC5_UNORM;
	case PIXELFORMAT_BC5_RGSN:       return DXGI_FORMAT_BC5_SNORM;
	case PIXELFORMAT_BC6H_RGBF:      return DXGI_FORMAT_BC6H_SF16;
	case PIXELFORMAT_BC6H_RGBUF:     return DXGI_FORMAT_BC6H_UF16;
	case PIXELFORMAT_BC7_RGBA:       return DXGI_FORMAT_BC7_UNORM;
	default:                            return DXGI_FORMAT_UNKNOWN;
	};
}

D3D11_PRIMITIVE_TOPOLOGY _primitive_topology( PrimitiveType prim_type )
{
	switch( prim_type )
	{
	case PRIMITIVETYPE_POINTS:           return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case PRIMITIVETYPE_LINES:            return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case PRIMITIVETYPE_LINE_STRIP:       return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case PRIMITIVETYPE_TRIANGLES:        return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case PRIMITIVETYPE_TRIANGLE_STRIP:   return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	default: XE_ASSERT(false); return (D3D11_PRIMITIVE_TOPOLOGY )0;
	}
}

DXGI_FORMAT _index_format( IndexType index_type )
{
	switch( index_type )
	{
	case INDEXTYPE_NONE:     return DXGI_FORMAT_UNKNOWN;
	case INDEXTYPE_UINT16:   return DXGI_FORMAT_R16_UINT;
	case INDEXTYPE_UINT32:   return DXGI_FORMAT_R32_UINT;
	default: XE_ASSERT(false); return (DXGI_FORMAT )0;
	}
}

D3D11_FILTER _filter( Filter min_f, Filter mag_f, XE::uint32 max_anisotropy )
{
	if( max_anisotropy > 1 )
	{
		return D3D11_FILTER_ANISOTROPIC;
	}
	else if( mag_f == FILTER_NEAREST )
	{
		switch( min_f )
		{
		case FILTER_NEAREST:
		case FILTER_NEAREST_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_MAG_MIP_POINT;
		case FILTER_LINEAR:
		case FILTER_LINEAR_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		case FILTER_NEAREST_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
		case FILTER_LINEAR_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR;
		default:
			XE_ASSERT(false); break;
		}
	}
	else if( mag_f == FILTER_LINEAR )
	{
		switch( min_f )
		{
		case FILTER_NEAREST:
		case FILTER_NEAREST_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT;
		case FILTER_LINEAR:
		case FILTER_LINEAR_MIPMAP_NEAREST:
			return D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT;
		case FILTER_NEAREST_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		case FILTER_LINEAR_MIPMAP_LINEAR:
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		default:
			XE_ASSERT(false); break;
		}
	}
	/* invalid value for mag filter */
	XE_ASSERT(false);
	return D3D11_FILTER_MIN_MAG_MIP_POINT;
}

D3D11_TEXTURE_ADDRESS_MODE _address_mode( Wrap m )
{
	switch( m )
	{
	case WRAP_REPEAT:            return D3D11_TEXTURE_ADDRESS_WRAP;
	case WRAP_CLAMP_TO_EDGE:     return D3D11_TEXTURE_ADDRESS_CLAMP;
	case WRAP_CLAMP_TO_BORDER:   return D3D11_TEXTURE_ADDRESS_BORDER;
	case WRAP_MIRRORED_REPEAT:   return D3D11_TEXTURE_ADDRESS_MIRROR;
	default: XE_ASSERT(false); return (D3D11_TEXTURE_ADDRESS_MODE )0;
	}
}

DXGI_FORMAT _vertex_format( VertexFormat fmt )
{
	switch( fmt )
	{
	case VERTEXFORMAT_FLOAT:     return DXGI_FORMAT_R32_FLOAT;
	case VERTEXFORMAT_FLOAT2:    return DXGI_FORMAT_R32G32_FLOAT;
	case VERTEXFORMAT_FLOAT3:    return DXGI_FORMAT_R32G32B32_FLOAT;
	case VERTEXFORMAT_FLOAT4:    return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case VERTEXFORMAT_BYTE4:     return DXGI_FORMAT_R8G8B8A8_SINT;
	case VERTEXFORMAT_BYTE4N:    return DXGI_FORMAT_R8G8B8A8_SNORM;
	case VERTEXFORMAT_UBYTE4:    return DXGI_FORMAT_R8G8B8A8_UINT;
	case VERTEXFORMAT_UBYTE4N:   return DXGI_FORMAT_R8G8B8A8_UNORM;
	case VERTEXFORMAT_SHORT2:    return DXGI_FORMAT_R16G16_SINT;
	case VERTEXFORMAT_SHORT2N:   return DXGI_FORMAT_R16G16_SNORM;
	case VERTEXFORMAT_USHORT2N:  return DXGI_FORMAT_R16G16_UNORM;
	case VERTEXFORMAT_SHORT4:    return DXGI_FORMAT_R16G16B16A16_SINT;
	case VERTEXFORMAT_SHORT4N:   return DXGI_FORMAT_R16G16B16A16_SNORM;
	case VERTEXFORMAT_USHORT4N:  return DXGI_FORMAT_R16G16B16A16_UNORM;
	case VERTEXFORMAT_UINT10_N2: return DXGI_FORMAT_R10G10B10A2_UNORM;
	default: XE_ASSERT(false); return (DXGI_FORMAT )0;
	}
}

D3D11_INPUT_CLASSIFICATION _input_classification( VertexStep step )
{
	switch( step )
	{
	case VERTEXSTEP_PER_VERTEX:      return D3D11_INPUT_PER_VERTEX_DATA;
	case VERTEXSTEP_PER_INSTANCE:    return D3D11_INPUT_PER_INSTANCE_DATA;
	default: XE_ASSERT(false); return (D3D11_INPUT_CLASSIFICATION )0;
	}
}

D3D11_CULL_MODE _cull_mode( CullMode m )
{
	switch( m )
	{
	case CULLMODE_NONE:      return D3D11_CULL_NONE;
	case CULLMODE_FRONT:     return D3D11_CULL_FRONT;
	case CULLMODE_BACK:      return D3D11_CULL_BACK;
	default: XE_ASSERT(false); return (D3D11_CULL_MODE )0;
	}
}

D3D11_COMPARISON_FUNC _compare_func( CompareFunc f )
{
	switch( f )
	{
	case COMPAREFUNC_NEVER:          return D3D11_COMPARISON_NEVER;
	case COMPAREFUNC_LESS:           return D3D11_COMPARISON_LESS;
	case COMPAREFUNC_EQUAL:          return D3D11_COMPARISON_EQUAL;
	case COMPAREFUNC_LESS_EQUAL:     return D3D11_COMPARISON_LESS_EQUAL;
	case COMPAREFUNC_GREATER:        return D3D11_COMPARISON_GREATER;
	case COMPAREFUNC_NOT_EQUAL:      return D3D11_COMPARISON_NOT_EQUAL;
	case COMPAREFUNC_GREATER_EQUAL:  return D3D11_COMPARISON_GREATER_EQUAL;
	case COMPAREFUNC_ALWAYS:         return D3D11_COMPARISON_ALWAYS;
	default: XE_ASSERT(false); return (D3D11_COMPARISON_FUNC )0;
	}
}

D3D11_STENCIL_OP _stencil_op( StencilOp op )
{
	switch( op )
	{
	case STENCILOP_KEEP:         return D3D11_STENCIL_OP_KEEP;
	case STENCILOP_ZERO:         return D3D11_STENCIL_OP_ZERO;
	case STENCILOP_REPLACE:      return D3D11_STENCIL_OP_REPLACE;
	case STENCILOP_INCR_CLAMP:   return D3D11_STENCIL_OP_INCR_SAT;
	case STENCILOP_DECR_CLAMP:   return D3D11_STENCIL_OP_DECR_SAT;
	case STENCILOP_INVERT:       return D3D11_STENCIL_OP_INVERT;
	case STENCILOP_INCR_WRAP:    return D3D11_STENCIL_OP_INCR;
	case STENCILOP_DECR_WRAP:    return D3D11_STENCIL_OP_DECR;
	default: XE_ASSERT(false); return (D3D11_STENCIL_OP )0;
	}
}

D3D11_BLEND _blend_factor( BlendFactor f )
{
	switch( f )
	{
	case BLENDFACTOR_ZERO:                   return D3D11_BLEND_ZERO;
	case BLENDFACTOR_ONE:                    return D3D11_BLEND_ONE;
	case BLENDFACTOR_SRC_COLOR:              return D3D11_BLEND_SRC_COLOR;
	case BLENDFACTOR_ONE_MINUS_SRC_COLOR:    return D3D11_BLEND_INV_SRC_COLOR;
	case BLENDFACTOR_SRC_ALPHA:              return D3D11_BLEND_SRC_ALPHA;
	case BLENDFACTOR_ONE_MINUS_SRC_ALPHA:    return D3D11_BLEND_INV_SRC_ALPHA;
	case BLENDFACTOR_DST_COLOR:              return D3D11_BLEND_DEST_COLOR;
	case BLENDFACTOR_ONE_MINUS_DST_COLOR:    return D3D11_BLEND_INV_DEST_COLOR;
	case BLENDFACTOR_DST_ALPHA:              return D3D11_BLEND_DEST_ALPHA;
	case BLENDFACTOR_ONE_MINUS_DST_ALPHA:    return D3D11_BLEND_INV_DEST_ALPHA;
	case BLENDFACTOR_SRC_ALPHA_SATURATED:    return D3D11_BLEND_SRC_ALPHA_SAT;
	case BLENDFACTOR_BLEND_COLOR:            return D3D11_BLEND_BLEND_FACTOR;
	case BLENDFACTOR_ONE_MINUS_BLEND_COLOR:  return D3D11_BLEND_INV_BLEND_FACTOR;
	case BLENDFACTOR_BLEND_ALPHA:            return D3D11_BLEND_BLEND_FACTOR;
	case BLENDFACTOR_ONE_MINUS_BLEND_ALPHA:  return D3D11_BLEND_INV_BLEND_FACTOR;
	default: XE_ASSERT(false); return (D3D11_BLEND )0;
	}
}

D3D11_BLEND_OP _blend_op( BlendOp op )
{
	switch( op )
	{
	case BLENDOP_ADD:                return D3D11_BLEND_OP_ADD;
	case BLENDOP_SUBTRACT:           return D3D11_BLEND_OP_SUBTRACT;
	case BLENDOP_REVERSE_SUBTRACT:   return D3D11_BLEND_OP_REV_SUBTRACT;
	default: XE_ASSERT(false); return (D3D11_BLEND_OP )0;
	}
}

UINT8 _color_write_mask( ColorMask m )
{
	UINT8 res = 0;
	if( m & COLORMASK_R )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_RED;
	}
	if( m & COLORMASK_G )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_GREEN;
	}
	if( m & COLORMASK_B )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_BLUE;
	}
	if( m & COLORMASK_A )
	{
		res |= D3D11_COLOR_WRITE_ENABLE_ALPHA;
	}
	return res;
}






void _init_caps( void )
{
	_sg.backend = BACKEND_D3D11;

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
	_sg.limits.max_vertex_attrs = MAX_VERTEX_ATTRIBUTES;

	XE::uint32 dxgi_fmt_caps = 0;
	for( XE::int32 fmt = ( PIXELFORMAT_NONE + 1 ); fmt < _PIXELFORMAT_NUM; fmt++ )
	{
		DXGI_FORMAT dxgi_fmt = _pixel_format( (PixelFormat )fmt );
		HRESULT hr = ID3D11Device_CheckFormatSupport( _sg.d3d11.dev, dxgi_fmt, &dxgi_fmt_caps );
		XE_ASSERT( SUCCEEDED( hr ) );
		PixelFormatInfo * info = &_sg.formats[fmt];
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

void _create_device_swap_chain_render_target( const GfxDesc * desc )
{
	DXGI_SWAP_CHAIN_DESC swap_chain_desc;

	swap_chain_desc.BufferDesc.Width = desc->window_width;
	swap_chain_desc.BufferDesc.Height = desc->window_height;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.OutputWindow = (HWND )desc->window_handle.GetValue();
	swap_chain_desc.Windowed = true;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.SampleDesc.Count = 4;
	swap_chain_desc.SampleDesc.Quality = D3D11_STANDARD_MULTISAMPLE_PATTERN;

	XE::int32 create_flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef XE_DEBUG
	create_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL feature_level;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,                       /* pAdapter (use default) */
		D3D_DRIVER_TYPE_HARDWARE,   /* DriverType */
		NULL,                       /* Software */
		create_flags,               /* Flags */
		NULL,                       /* pFeatureLevels */
		0,                          /* FeatureLevels */
		D3D11_SDK_VERSION,          /* SDKVersion */
		&swap_chain_desc,           /* pSwapChainDesc */
		&_sg.d3d11.swap_chain,                /* ppSwapChain */
		&_sg.d3d11.device,                    /* ppDevice */
		&feature_level,             /* pFeatureLevel */
		&_sg.d3d11.device_context );           /* ppImmediateContext */
	XE_ASSERT( SUCCEEDED( hr ) && _sg.d3d11.swap_chain && _sg.d3d11.device && _sg.d3d11.device_context );

	// d3d11_create_default_render_target
	hr = IDXGISwapChain_GetBuffer( _sg.d3d11.swap_chain, 0, IID_ID3D11Texture2D, (void ** )& _sg.d3d11.render_target );
	XE_ASSERT( SUCCEEDED( hr ) && _sg.d3d11.render_target );
	hr = ID3D11Device_CreateRenderTargetView( _sg.d3d11.device, (ID3D11Resource * )_sg.d3d11.render_target, NULL, &_sg.d3d11.render_target_view );
	XE_ASSERT( SUCCEEDED( hr ) && _sg.d3d11.render_target_view );

	D3D11_TEXTURE2D_DESC ds_desc;
	ds_desc.Width = desc->window_width;
	ds_desc.Height = desc->window_height;
	ds_desc.MipLevels = 1;
	ds_desc.ArraySize = 1;
	ds_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ds_desc.SampleDesc = swap_chain_desc.SampleDesc;
	ds_desc.Usage = D3D11_USAGE_DEFAULT;
	ds_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	hr = ID3D11Device_CreateTexture2D( _sg.d3d11.device, &ds_desc, NULL, &_sg.d3d11.depth_stencil_buffer );
	XE_ASSERT( SUCCEEDED( hr ) && _sg.d3d11.depth_stencil_buffer );

	const XE::int32 sample_count = swap_chain_desc.SampleDesc.Count;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
	dsv_desc.Format = ds_desc.Format;
	dsv_desc.ViewDimension = sample_count > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = ID3D11Device_CreateDepthStencilView( _sg.d3d11.device, (ID3D11Resource * )_sg.d3d11.depth_stencil_buffer, &dsv_desc, &_sg.d3d11.depth_stencil_view );
	XE_ASSERT( SUCCEEDED( hr ) && _sg.d3d11.depth_stencil_view );

	_sg.d3d11.valid = true;
}

void _setup_backend( const GfxDesc * desc )
{
	_create_device_swap_chain_render_target( desc );

	_init_caps();
}

void _discard_backend( void )
{
	XE_ASSERT( _sg.d3d11.valid );
	_sg.d3d11.valid = false;
}

void _clear_state( void )
{
	/* clear all the device context state, so that resource refs don't keep stuck in the d3d device context */
	ID3D11DeviceContext_OMSetRenderTargets( _sg.d3d11.ctx, MAX_COLOR_ATTACHMENTS, _sg.d3d11.zero_rtvs, NULL );
	ID3D11DeviceContext_RSSetState( _sg.d3d11.ctx, NULL );
	ID3D11DeviceContext_OMSetDepthStencilState( _sg.d3d11.ctx, NULL, 0 );
	ID3D11DeviceContext_OMSetBlendState( _sg.d3d11.ctx, NULL, NULL, 0xFFFFFFFF );
	ID3D11DeviceContext_IASetVertexBuffers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_BUFFERS, _sg.d3d11.zero_vbs, _sg.d3d11.zero_vb_strides, _sg.d3d11.zero_vb_offsets );
	ID3D11DeviceContext_IASetIndexBuffer( _sg.d3d11.ctx, NULL, DXGI_FORMAT_UNKNOWN, 0 );
	ID3D11DeviceContext_IASetInputLayout( _sg.d3d11.ctx, NULL );
	ID3D11DeviceContext_VSSetShader( _sg.d3d11.ctx, NULL, NULL, 0 );
	ID3D11DeviceContext_PSSetShader( _sg.d3d11.ctx, NULL, NULL, 0 );
	ID3D11DeviceContext_VSSetConstantBuffers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_UBS, _sg.d3d11.zero_cbs );
	ID3D11DeviceContext_PSSetConstantBuffers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_UBS, _sg.d3d11.zero_cbs );
	ID3D11DeviceContext_VSSetShaderResources( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_srvs );
	ID3D11DeviceContext_PSSetShaderResources( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_srvs );
	ID3D11DeviceContext_VSSetSamplers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_smps );
	ID3D11DeviceContext_PSSetSamplers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, _sg.d3d11.zero_smps );
}

void _reset_state_cache( void )
{
	_clear_state();
}

void _activate_context( _ContextType * ctx )
{
	(void)( ctx );
	_clear_state();
}

ResourceState _create_context( _ContextType * ctx )
{
	XE_ASSERT( ctx );
	(void)( ctx );
	return RESOURCESTATE_VALID;
}

void _destroy_context( _ContextType * ctx )
{
	XE_ASSERT( ctx );
	(void)( ctx );
}

ResourceState _create_buffer( _BufferType * buf, const BufferDesc * desc )
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
		d3d11_desc.Usage = _usage( buf->cmn.usage );
		d3d11_desc.BindFlags = buf->cmn.type == BUFFERTYPE_VERTEXBUFFER ? D3D11_BIND_VERTEX_BUFFER : D3D11_BIND_INDEX_BUFFER;
		d3d11_desc.CPUAccessFlags = _cpu_access_flags( buf->cmn.usage );
		D3D11_SUBRESOURCE_DATA * init_data_ptr = 0;
		D3D11_SUBRESOURCE_DATA init_data;
		memset( &init_data, 0, sizeof( init_data ) );
		if( buf->cmn.usage == USAGE_IMMUTABLE )
		{
			XE_ASSERT( desc->content );
			init_data.pSysMem = desc->content;
			init_data_ptr = &init_data;
		}
		HRESULT hr = ID3D11Device_CreateBuffer( _sg.d3d11.dev, &d3d11_desc, init_data_ptr, &buf->d3d11.buf );
		(void)( hr );
		XE_ASSERT( SUCCEEDED( hr ) && buf->d3d11.buf );
	}
	return RESOURCESTATE_VALID;
}

void _destroy_buffer( _BufferType * buf )
{
	XE_ASSERT( buf );
	if( buf->d3d11.buf )
	{
		ID3D11Buffer_Release( buf->d3d11.buf );
	}
}

void _fill_subres_data( const _ImageType * img, const ImageContent * content )
{
	const XE::int32 num_faces = ( img->cmn.type == IMAGETYPE_CUBE ) ? 6 : 1;
	const XE::int32 num_slices = ( img->cmn.type == IMAGETYPE_ARRAY ) ? img->cmn.depth : 1;
	XE::int32 subres_index = 0;
	for( XE::int32 face_index = 0; face_index < num_faces; face_index++ )
	{
		for( XE::int32 slice_index = 0; slice_index < num_slices; slice_index++ )
		{
			for( XE::int32 mip_index = 0; mip_index < img->cmn.num_mipmaps; mip_index++, subres_index++ )
			{
				XE_ASSERT( subres_index < ( MAX_MIPMAPS * MAX_TEXTUREARRAY_LAYERS ) );
				D3D11_SUBRESOURCE_DATA * subres_data = &_sg.d3d11.subres_data[subres_index];
				const XE::int32 mip_width = ( ( img->cmn.width >> mip_index ) > 0 ) ? img->cmn.width >> mip_index : 1;
				const XE::int32 mip_height = ( ( img->cmn.height >> mip_index ) > 0 ) ? img->cmn.height >> mip_index : 1;
				const SubImageContent * subimg_content = &( content->subimage[face_index][mip_index] );
				const XE::int32 slice_size = subimg_content->size / num_slices;
				const XE::int32 slice_offset = slice_size * slice_index;
				const uint8_t * ptr = (const uint8_t * )subimg_content->ptr;
				subres_data->pSysMem = ptr + slice_offset;
				subres_data->SysMemPitch = _RowPitch( img->cmn.pixel_format, mip_width );
				if( img->cmn.type == IMAGETYPE_3D )
				{
					/* FIXME? const XE::int32 mip_depth = ((img->depth>>mip_index)>0) ? img->depth>>mip_index : 1; */
					subres_data->SysMemSlicePitch = _SurfacePitch( img->cmn.pixel_format, mip_width, mip_height );
				}
				else
				{
					subres_data->SysMemSlicePitch = 0;
				}
			}
		}
	}
}

ResourceState _create_image( _ImageType * img, const ImageDesc * desc )
{
	XE_ASSERT( img && desc );
	XE_ASSERT( !img->d3d11.tex2d && !img->d3d11.tex3d && !img->d3d11.texds && !img->d3d11.texmsaa );
	XE_ASSERT( !img->d3d11.srv && !img->d3d11.smp );
	HRESULT hr;

	img->cmn.init( desc );
	const bool injected = ( 0 != desc->d3d11_texture );
	const bool msaa = ( img->cmn.sample_count > 1 );

	/* special case depth-stencil buffer? */
	if( _is_valid_rendertarget_depth_format( img->cmn.pixel_format ) )
	{
		/* create only a depth-texture */
		XE_ASSERT( !injected );
		img->d3d11.format = _pixel_format( img->cmn.pixel_format );
		if( img->d3d11.format == DXGI_FORMAT_UNKNOWN )
		{
			puts( "trying to create a D3D11 depth-texture with unsupported pixel format\n" );
			return RESOURCESTATE_FAILED;
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
		if( !injected && ( img->cmn.usage == USAGE_IMMUTABLE ) && !img->cmn.render_target )
		{
			_fill_subres_data( img, &desc->content );
			init_data = _sg.d3d11.subres_data;
		}
		if( img->cmn.type != IMAGETYPE_3D )
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
			case IMAGETYPE_ARRAY:    d3d11_tex_desc.ArraySize = img->cmn.depth; break;
			case IMAGETYPE_CUBE:     d3d11_tex_desc.ArraySize = 6; break;
			default:                    d3d11_tex_desc.ArraySize = 1; break;
			}
			d3d11_tex_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			if( img->cmn.render_target )
			{
				img->d3d11.format = _pixel_format( img->cmn.pixel_format );
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
				img->d3d11.format = _pixel_format( img->cmn.pixel_format );
				d3d11_tex_desc.Format = img->d3d11.format;
				d3d11_tex_desc.Usage = _usage( img->cmn.usage );
				d3d11_tex_desc.CPUAccessFlags = _cpu_access_flags( img->cmn.usage );
			}
			if( img->d3d11.format == DXGI_FORMAT_UNKNOWN )
			{
				/* trying to create a texture format that's not supported by D3D */
				puts( "trying to create a D3D11 texture with unsupported pixel format\n" );
				return RESOURCESTATE_FAILED;
			}
			d3d11_tex_desc.SampleDesc.Count = 1;
			d3d11_tex_desc.SampleDesc.Quality = 0;
			d3d11_tex_desc.MiscFlags = ( img->cmn.type == IMAGETYPE_CUBE ) ? D3D11_RESOURCE_MISC_TEXTURECUBE : 0;
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
			case IMAGETYPE_2D:
				d3d11_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				d3d11_srv_desc.Texture2D.MipLevels = img->cmn.num_mipmaps;
				break;
			case IMAGETYPE_CUBE:
				d3d11_srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
				d3d11_srv_desc.TextureCube.MipLevels = img->cmn.num_mipmaps;
				break;
			case IMAGETYPE_ARRAY:
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
				img->d3d11.format = _pixel_format( img->cmn.pixel_format );
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
				img->d3d11.format = _pixel_format( img->cmn.pixel_format );
				d3d11_tex_desc.Format = img->d3d11.format;
				d3d11_tex_desc.Usage = _usage( img->cmn.usage );
				d3d11_tex_desc.CPUAccessFlags = _cpu_access_flags( img->cmn.usage );
			}
			if( img->d3d11.format == DXGI_FORMAT_UNKNOWN )
			{
				/* trying to create a texture format that's not supported by D3D */
				puts( "trying to create a D3D11 texture with unsupported pixel format\n" );
				return RESOURCESTATE_FAILED;
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
			d3d11_tex_desc.SampleDesc.Quality = (XE::uint32 )D3D11_STANDARD_MULTISAMPLE_PATTERN;
			hr = ID3D11Device_CreateTexture2D( _sg.d3d11.dev, &d3d11_tex_desc, NULL, &img->d3d11.texmsaa );
			XE_ASSERT( SUCCEEDED( hr ) && img->d3d11.texmsaa );
		}

		/* sampler state object, note D3D11 implements an internal shared-pool for sampler objects */
		D3D11_SAMPLER_DESC d3d11_smp_desc;
		memset( &d3d11_smp_desc, 0, sizeof( d3d11_smp_desc ) );
		d3d11_smp_desc.Filter = _filter( img->cmn.min_filter, img->cmn.mag_filter, img->cmn.max_anisotropy );
		d3d11_smp_desc.AddressU = _address_mode( img->cmn.wrap_u );
		d3d11_smp_desc.AddressV = _address_mode( img->cmn.wrap_v );
		d3d11_smp_desc.AddressW = _address_mode( img->cmn.wrap_w );
		switch( img->cmn.border_color )
		{
		case BORDERCOLOR_TRANSPARENT_BLACK:
			/* all 0.0f */
			break;
		case BORDERCOLOR_OPAQUE_WHITE:
			for( XE::int32 i = 0; i < 4; i++ )
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
	return RESOURCESTATE_VALID;
}

void _destroy_image( _ImageType * img )
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

bool _load_d3dcompiler_dll( void )
{
	/* on UWP, don't do anything (not tested) */
#if (defined(WINAPI_FAMILY_PARTITION) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))
	_sg.d3d11.D3DCompile_func = D3DCompile;
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

ID3DBlob * _compile_shader( const ShaderStageDesc * stage_desc, XE::String target )
{
	if( !_load_d3dcompiler_dll() )
	{
		return NULL;
	}
	ID3DBlob * output = NULL;
	ID3DBlob * errors_or_warnings = NULL;
	
	HRESULT hr = _sg.d3d11.D3DCompile_func(
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

ResourceState _create_shader( _ShaderType * shd, const ShaderDesc * desc )
{
	XE_ASSERT( shd && desc );
	XE_ASSERT( !shd->d3d11.vs && !shd->d3d11.fs && !shd->d3d11.vs_blob );
	HRESULT hr;

	shd->cmn.init( desc );

	/* copy vertex attribute semantic names and indices */
	for( XE::int32 i = 0; i < MAX_VERTEX_ATTRIBUTES; i++ )
	{
		shd->d3d11.attrs[i].sem_name = desc->attrs[i].sem_name;
		shd->d3d11.attrs[i].sem_index = desc->attrs[i].sem_index;
	}

	/* shader stage uniform blocks and image slots */
	for( XE::int32 stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
	{
		_ShaderStageType * cmn_stage = &shd->cmn.stage[stage_index];
		_D3D11ShaderStageType * d3d11_stage = &shd->d3d11.stage[stage_index];
		for( XE::int32 ub_index = 0; ub_index < cmn_stage->num_uniform_blocks; ub_index++ )
		{
			const _UniformBlockType * ub = &cmn_stage->uniform_blocks[ub_index];

			/* create a D3D constant buffer for each uniform block */
			XE_ASSERT( 0 == d3d11_stage->cbufs[ub_index] );
			D3D11_BUFFER_DESC cb_desc;
			memset( &cb_desc, 0, sizeof( cb_desc ) );
			cb_desc.ByteWidth = ( ( ( ub->size ) + ( ( 16 ) - 1 ) ) & ~( ( 16 ) - 1 ) );
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
		vs_blob = _compile_shader( &desc->vs, "vs_5_0" );
		fs_blob = _compile_shader( &desc->fs, "ps_5_0" );
		if( vs_blob && fs_blob )
		{
			vs_ptr = ID3D10Blob_GetBufferPointer( vs_blob );
			vs_length = ID3D10Blob_GetBufferSize( vs_blob );
			fs_ptr = ID3D10Blob_GetBufferPointer( fs_blob );
			fs_length = ID3D10Blob_GetBufferSize( fs_blob );
		}
	}
	ResourceState result = RESOURCESTATE_FAILED;
	if( vs_ptr && fs_ptr && ( vs_length > 0 ) && ( fs_length > 0 ) )
	{
		/* create the D3D vertex- and pixel-shader objects */
		hr = ID3D11Device_CreateVertexShader( _sg.d3d11.dev, vs_ptr, vs_length, NULL, &shd->d3d11.vs );
		XE_ASSERT( SUCCEEDED( hr ) && shd->d3d11.vs );
		hr = ID3D11Device_CreatePixelShader( _sg.d3d11.dev, fs_ptr, fs_length, NULL, &shd->d3d11.fs );
		XE_ASSERT( SUCCEEDED( hr ) && shd->d3d11.fs );

		/* need to store the vertex shader byte code, this is needed later in create_pipeline */
		shd->d3d11.vs_blob_length = (XE::int32 )vs_length;
		shd->d3d11.vs_blob = malloc( (XE::int32 )vs_length );
		XE_ASSERT( shd->d3d11.vs_blob );
		memcpy( shd->d3d11.vs_blob, vs_ptr, vs_length );

		result = RESOURCESTATE_VALID;
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

void _destroy_shader( _ShaderType * shd )
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
	for( XE::int32 stage_index = 0; stage_index < NUM_SHADER_STAGES; stage_index++ )
	{
		_ShaderStageType * cmn_stage = &shd->cmn.stage[stage_index];
		_D3D11ShaderStageType * d3d11_stage = &shd->d3d11.stage[stage_index];
		for( XE::int32 ub_index = 0; ub_index < cmn_stage->num_uniform_blocks; ub_index++ )
		{
			if( d3d11_stage->cbufs[ub_index] != nullptr )
			{
				ID3D11Buffer_Release( d3d11_stage->cbufs[ub_index] );
			}
		}
	}
}

ResourceState _create_pipeline( _PipelineType * pip, _ShaderType * shd, const PipelineDesc * desc )
{
	XE_ASSERT( pip && shd && desc );
	XE_ASSERT( desc->shader.GetValue() == shd->slot.id );
	XE_ASSERT( shd->slot.state == RESOURCESTATE_VALID );
	XE_ASSERT( shd->d3d11.vs_blob && shd->d3d11.vs_blob_length > 0 );
	XE_ASSERT( !pip->d3d11.il && !pip->d3d11.rs && !pip->d3d11.dss && !pip->d3d11.bs );

	pip->shader = shd;
	pip->cmn.init( desc );
	pip->d3d11.index_format = _index_format( pip->cmn.index_type );
	pip->d3d11.topology = _primitive_topology( desc->primitive_type );
	pip->d3d11.stencil_ref = desc->depth_stencil.stencil_ref;

	/* create input layout object */
	HRESULT hr;
	D3D11_INPUT_ELEMENT_DESC d3d11_comps[MAX_VERTEX_ATTRIBUTES];
	memset( d3d11_comps, 0, sizeof( d3d11_comps ) );
	XE::int32 attr_index = 0;
	for( ; attr_index < MAX_VERTEX_ATTRIBUTES; attr_index++ )
	{
		const VertexAttrDesc * a_desc = &desc->layout.attrs[attr_index];
		if( a_desc->format == VERTEXFORMAT_INVALID )
		{
			break;
		}
		XE_ASSERT( ( a_desc->buffer_index >= 0 ) && ( a_desc->buffer_index < MAX_SHADERSTAGE_BUFFERS ) );
		const BufferLayoutDesc * l_desc = &desc->layout.buffers[a_desc->buffer_index];
		const VertexStep step_func = l_desc->step_func;
		const XE::int32 step_rate = l_desc->step_rate;
		D3D11_INPUT_ELEMENT_DESC * d3d11_comp = &d3d11_comps[attr_index];
		d3d11_comp->SemanticName = shd->d3d11.attrs[attr_index].sem_name.ToCString();
		d3d11_comp->SemanticIndex = shd->d3d11.attrs[attr_index].sem_index;
		d3d11_comp->Format = _vertex_format( a_desc->format );
		d3d11_comp->InputSlot = a_desc->buffer_index;
		d3d11_comp->AlignedByteOffset = a_desc->offset;
		d3d11_comp->InputSlotClass = _input_classification( step_func );
		if( VERTEXSTEP_PER_INSTANCE == step_func )
		{
			d3d11_comp->InstanceDataStepRate = step_rate;
		}
		pip->cmn.vertex_layout_valid[a_desc->buffer_index] = true;
	}
	for( XE::int32 layout_index = 0; layout_index < MAX_SHADERSTAGE_BUFFERS; layout_index++ )
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
	rs_desc.CullMode = _cull_mode( desc->rasterizer.cull_mode );
	rs_desc.FrontCounterClockwise = desc->rasterizer.face_winding == FACEWINDING_CCW;
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
	dss_desc.DepthFunc = _compare_func( desc->depth_stencil.depth_compare_func );
	dss_desc.StencilEnable = desc->depth_stencil.stencil_enabled;
	dss_desc.StencilReadMask = desc->depth_stencil.stencil_read_mask;
	dss_desc.StencilWriteMask = desc->depth_stencil.stencil_write_mask;
	const StencilState * sf = &desc->depth_stencil.stencil_front;
	dss_desc.FrontFace.StencilFailOp = _stencil_op( sf->fail_op );
	dss_desc.FrontFace.StencilDepthFailOp = _stencil_op( sf->depth_fail_op );
	dss_desc.FrontFace.StencilPassOp = _stencil_op( sf->pass_op );
	dss_desc.FrontFace.StencilFunc = _compare_func( sf->compare_func );
	const StencilState * sb = &desc->depth_stencil.stencil_back;
	dss_desc.BackFace.StencilFailOp = _stencil_op( sb->fail_op );
	dss_desc.BackFace.StencilDepthFailOp = _stencil_op( sb->depth_fail_op );
	dss_desc.BackFace.StencilPassOp = _stencil_op( sb->pass_op );
	dss_desc.BackFace.StencilFunc = _compare_func( sb->compare_func );
	hr = ID3D11Device_CreateDepthStencilState( _sg.d3d11.dev, &dss_desc, &pip->d3d11.dss );
	XE_ASSERT( SUCCEEDED( hr ) && pip->d3d11.dss );

	/* create blend state */
	D3D11_BLEND_DESC bs_desc;
	memset( &bs_desc, 0, sizeof( bs_desc ) );
	bs_desc.AlphaToCoverageEnable = desc->rasterizer.alpha_to_coverage_enabled;
	bs_desc.IndependentBlendEnable = FALSE;
	bs_desc.RenderTarget[0].BlendEnable = desc->blend.enabled;
	bs_desc.RenderTarget[0].SrcBlend = _blend_factor( desc->blend.src_factor_rgb );
	bs_desc.RenderTarget[0].DestBlend = _blend_factor( desc->blend.dst_factor_rgb );
	bs_desc.RenderTarget[0].BlendOp = _blend_op( desc->blend.op_rgb );
	bs_desc.RenderTarget[0].SrcBlendAlpha = _blend_factor( desc->blend.src_factor_alpha );
	bs_desc.RenderTarget[0].DestBlendAlpha = _blend_factor( desc->blend.dst_factor_alpha );
	bs_desc.RenderTarget[0].BlendOpAlpha = _blend_op( desc->blend.op_alpha );
	bs_desc.RenderTarget[0].RenderTargetWriteMask = _color_write_mask( (ColorMask )desc->blend.color_write_mask );
	hr = ID3D11Device_CreateBlendState( _sg.d3d11.dev, &bs_desc, &pip->d3d11.bs );
	XE_ASSERT( SUCCEEDED( hr ) && pip->d3d11.bs );

	return RESOURCESTATE_VALID;
}

void _destroy_pipeline( _PipelineType * pip )
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

ResourceState _create_pass( _PassType * pass, _ImageType ** att_images, const PassDesc * desc )
{
	XE_ASSERT( pass && desc );
	XE_ASSERT( att_images && att_images[0] );
	XE_ASSERT( _sg.d3d11.dev );

	pass->cmn.init( desc );

	for( XE::int32 i = 0; i < pass->cmn.num_color_atts; i++ )
	{
		const AttachmentDesc * att_desc = &desc->color_attachments[i];
		XE_ASSERT( att_desc->image );
		_ImageType * att_img = att_images[i];
		XE_ASSERT( att_img && ( att_img->slot.id == att_desc->image.GetValue() ) );
		XE_ASSERT( _is_valid_rendertarget_color_format( att_img->cmn.pixel_format ) );
		XE_ASSERT( 0 == pass->d3d11.color_atts[i].image );
		pass->d3d11.color_atts[i].image = att_img;

		/* create D3D11 render-target-view */
		const _AttachmentType * cmn_att = &pass->cmn.color_atts[i];
		XE_ASSERT( 0 == pass->d3d11.color_atts[i].rtv );
		ID3D11Resource * d3d11_res = 0;
		const bool is_msaa = att_img->cmn.sample_count > 1;
		D3D11_RENDER_TARGET_VIEW_DESC d3d11_rtv_desc;
		memset( &d3d11_rtv_desc, 0, sizeof( d3d11_rtv_desc ) );
		d3d11_rtv_desc.Format = att_img->d3d11.format;
		if( ( att_img->cmn.type == IMAGETYPE_2D ) || is_msaa )
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
		else if( ( att_img->cmn.type == IMAGETYPE_CUBE ) || ( att_img->cmn.type == IMAGETYPE_ARRAY ) )
		{
			d3d11_res = (ID3D11Resource * )att_img->d3d11.tex2d;
			d3d11_rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
			d3d11_rtv_desc.Texture2DArray.MipSlice = cmn_att->mip_level;
			d3d11_rtv_desc.Texture2DArray.FirstArraySlice = cmn_att->slice;
			d3d11_rtv_desc.Texture2DArray.ArraySize = 1;
		}
		else
		{
			XE_ASSERT( att_img->cmn.type == IMAGETYPE_3D );
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
		const XE::int32 ds_img_index = MAX_COLOR_ATTACHMENTS;
		const AttachmentDesc * att_desc = &desc->depth_stencil_attachment;
		_ImageType * att_img = att_images[ds_img_index];
		XE_ASSERT( att_img && ( att_img->slot.id == att_desc->image.GetValue() ) );
		XE_ASSERT( _is_valid_rendertarget_depth_format( att_img->cmn.pixel_format ) );
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
	return RESOURCESTATE_VALID;
}

void _destroy_pass( _PassType * pass )
{
	XE_ASSERT( pass );
	for( XE::int32 i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
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

_ImageType * _pass_color_image( const _PassType * pass, XE::int32 index )
{
	XE_ASSERT( pass && ( index >= 0 ) && ( index < MAX_COLOR_ATTACHMENTS ) );
	/* NOTE: may return null */
	return pass->d3d11.color_atts[index].image;
}

_ImageType * _pass_ds_image( const _PassType * pass )
{
	/* NOTE: may return null */
	XE_ASSERT( pass );
	return pass->d3d11.ds_att.image;
}

void _begin_pass( _PassType * pass, const PassAction * action, XE::int32 w, XE::int32 h )
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
		for( XE::int32 i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
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
		_sg.d3d11.cur_rtvs[0] = _sg.d3d11.render_target_view;
		for( XE::int32 i = 1; i < MAX_COLOR_ATTACHMENTS; i++ )
		{
			_sg.d3d11.cur_rtvs[i] = 0;
		}
		_sg.d3d11.cur_dsv = _sg.d3d11.depth_stencil_view;
		XE_ASSERT( _sg.d3d11.cur_rtvs[0] && _sg.d3d11.cur_dsv );
	}
	/* apply the render-target- and depth-stencil-views */
	ID3D11DeviceContext_OMSetRenderTargets( _sg.d3d11.ctx, MAX_COLOR_ATTACHMENTS, _sg.d3d11.cur_rtvs, _sg.d3d11.cur_dsv );

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
	for( XE::int32 i = 0; i < _sg.d3d11.num_rtvs; i++ )
	{
		if( action->colors[i].action == ACTION_CLEAR )
		{
			ID3D11DeviceContext_ClearRenderTargetView( _sg.d3d11.ctx, _sg.d3d11.cur_rtvs[i], action->colors[i].val );
		}
	}
	XE::uint32 ds_flags = 0;
	if( action->depth.action == ACTION_CLEAR )
	{
		ds_flags |= D3D11_CLEAR_DEPTH;
	}
	if( action->stencil.action == ACTION_CLEAR )
	{
		ds_flags |= D3D11_CLEAR_STENCIL;
	}
	if( ( 0 != ds_flags ) && _sg.d3d11.cur_dsv )
	{
		ID3D11DeviceContext_ClearDepthStencilView( _sg.d3d11.ctx, _sg.d3d11.cur_dsv, ds_flags, action->depth.val, action->stencil.val );
	}
}

XE::uint32 _calcsubresource( XE::uint32 mip_slice, XE::uint32 array_slice, XE::uint32 mip_levels )
{
	return mip_slice + array_slice * mip_levels;
}

void _end_pass( void )
{
	XE_ASSERT( _sg.d3d11.in_pass && _sg.d3d11.ctx );
	_sg.d3d11.in_pass = false;

	/* need to resolve MSAA render target into texture? */
	if( _sg.d3d11.cur_pass )
	{
		XE_ASSERT( _sg.d3d11.cur_pass->slot.id == _sg.d3d11.cur_pass_id.GetValue() );
		for( XE::int32 i = 0; i < _sg.d3d11.num_rtvs; i++ )
		{
			_AttachmentType * cmn_att = &_sg.d3d11.cur_pass->cmn.color_atts[i];
			_ImageType * att_img = _sg.d3d11.cur_pass->d3d11.color_atts[i].image;
			XE_ASSERT( att_img && ( att_img->slot.id == cmn_att->image_id.GetValue() ) );
			if( att_img->cmn.sample_count > 1 )
			{
				/* FIXME: support MSAA resolve into 3D texture */
				XE_ASSERT( att_img->d3d11.tex2d && att_img->d3d11.texmsaa && !att_img->d3d11.tex3d );
				XE_ASSERT( DXGI_FORMAT_UNKNOWN != att_img->d3d11.format );
				XE::uint32 dst_subres = _calcsubresource( cmn_att->mip_level, cmn_att->slice, att_img->cmn.num_mipmaps );
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
	for( XE::int32 i = 0; i < MAX_COLOR_ATTACHMENTS; i++ )
	{
		_sg.d3d11.cur_rtvs[i] = 0;
	}
	_sg.d3d11.cur_dsv = 0;
	_clear_state();
}

void _apply_viewport( XE::int32 x, XE::int32 y, XE::int32 w, XE::int32 h, bool origin_top_left )
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

void _apply_scissor_rect( XE::int32 x, XE::int32 y, XE::int32 w, XE::int32 h, bool origin_top_left )
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

void _apply_pipeline( _PipelineType * pip )
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
	ID3D11DeviceContext_VSSetConstantBuffers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_UBS, pip->shader->d3d11.stage[SHADERSTAGE_VS].cbufs );
	ID3D11DeviceContext_PSSetShader( _sg.d3d11.ctx, pip->shader->d3d11.fs, NULL, 0 );
	ID3D11DeviceContext_PSSetConstantBuffers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_UBS, pip->shader->d3d11.stage[SHADERSTAGE_FS].cbufs );
}

void _apply_bindings(
	_PipelineType * pip,
	_BufferType ** vbs, const XE::int32 * vb_offsets, XE::int32 num_vbs,
	_BufferType * ib, XE::int32 ib_offset,
	_ImageType ** vs_imgs, XE::int32 num_vs_imgs,
	_ImageType ** fs_imgs, XE::int32 num_fs_imgs )
{
	XE_ASSERT( pip );
	XE_ASSERT( _sg.d3d11.ctx );
	XE_ASSERT( _sg.d3d11.in_pass );

	/* gather all the D3D11 resources into arrays */
	ID3D11Buffer * d3d11_ib = ib ? ib->d3d11.buf : 0;
	ID3D11Buffer * d3d11_vbs[MAX_SHADERSTAGE_BUFFERS];
	XE::uint32 d3d11_vb_offsets[MAX_SHADERSTAGE_BUFFERS];
	ID3D11ShaderResourceView * d3d11_vs_srvs[MAX_SHADERSTAGE_IMAGES];
	ID3D11SamplerState * d3d11_vs_smps[MAX_SHADERSTAGE_IMAGES];
	ID3D11ShaderResourceView * d3d11_fs_srvs[MAX_SHADERSTAGE_IMAGES];
	ID3D11SamplerState * d3d11_fs_smps[MAX_SHADERSTAGE_IMAGES];
	XE::int32 i;
	for( i = 0; i < num_vbs; i++ )
	{
		XE_ASSERT( vbs[i]->d3d11.buf );
		d3d11_vbs[i] = vbs[i]->d3d11.buf;
		d3d11_vb_offsets[i] = vb_offsets[i];
	}
	for( ; i < MAX_SHADERSTAGE_BUFFERS; i++ )
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
	for( ; i < MAX_SHADERSTAGE_IMAGES; i++ )
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
	for( ; i < MAX_SHADERSTAGE_IMAGES; i++ )
	{
		d3d11_fs_srvs[i] = 0;
		d3d11_fs_smps[i] = 0;
	}

	ID3D11DeviceContext_IASetVertexBuffers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_BUFFERS, d3d11_vbs, pip->d3d11.vb_strides, d3d11_vb_offsets );
	ID3D11DeviceContext_IASetIndexBuffer( _sg.d3d11.ctx, d3d11_ib, pip->d3d11.index_format, ib_offset );
	ID3D11DeviceContext_VSSetShaderResources( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, d3d11_vs_srvs );
	ID3D11DeviceContext_VSSetSamplers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, d3d11_vs_smps );
	ID3D11DeviceContext_PSSetShaderResources( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, d3d11_fs_srvs );
	ID3D11DeviceContext_PSSetSamplers( _sg.d3d11.ctx, 0, MAX_SHADERSTAGE_IMAGES, d3d11_fs_smps );
}

void _apply_uniforms( ShaderStage stage_index, XE::int32 ub_index, const void * data, XE::int32 num_bytes )
{
	(void)( num_bytes );
	XE_ASSERT( _sg.d3d11.ctx && _sg.d3d11.in_pass );
	XE_ASSERT( data && ( num_bytes > 0 ) );
	XE_ASSERT( ( stage_index >= 0 ) && ( (XE::int32 )stage_index < NUM_SHADER_STAGES ) );
	XE_ASSERT( ( ub_index >= 0 ) && ( ub_index < MAX_SHADERSTAGE_UBS ) );
	XE_ASSERT( _sg.d3d11.cur_pipeline && _sg.d3d11.cur_pipeline->slot.id == _sg.d3d11.cur_pipeline_id.GetValue() );
	XE_ASSERT( _sg.d3d11.cur_pipeline->shader && _sg.d3d11.cur_pipeline->shader->slot.id == _sg.d3d11.cur_pipeline->cmn.shader_id.GetValue() );
	XE_ASSERT( ub_index < _sg.d3d11.cur_pipeline->shader->cmn.stage[stage_index].num_uniform_blocks );
	XE_ASSERT( num_bytes == _sg.d3d11.cur_pipeline->shader->cmn.stage[stage_index].uniform_blocks[ub_index].size );
	ID3D11Buffer * cb = _sg.d3d11.cur_pipeline->shader->d3d11.stage[stage_index].cbufs[ub_index];
	XE_ASSERT( cb );
	ID3D11DeviceContext_UpdateSubresource( _sg.d3d11.ctx, (ID3D11Resource * )cb, 0, NULL, data, 0, 0 );
}

void _draw( XE::int32 base_element, XE::int32 num_elements, XE::int32 num_instances )
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

void _commit( void )
{
	XE_ASSERT( !_sg.d3d11.in_pass );
}

void _update_buffer( _BufferType * buf, const void * data_ptr, XE::int32 data_size )
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

void _append_buffer( _BufferType * buf, const void * data_ptr, XE::int32 data_size, bool new_frame )
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

void _update_image( _ImageType * img, const ImageContent * data )
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
	const XE::int32 num_faces = ( img->cmn.type == IMAGETYPE_CUBE ) ? 6 : 1;
	const XE::int32 num_slices = ( img->cmn.type == IMAGETYPE_ARRAY ) ? img->cmn.depth : 1;
	XE::int32 subres_index = 0;
	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE d3d11_msr;
	for( XE::int32 face_index = 0; face_index < num_faces; face_index++ )
	{
		for( XE::int32 slice_index = 0; slice_index < num_slices; slice_index++ )
		{
			for( XE::int32 mip_index = 0; mip_index < img->cmn.num_mipmaps; mip_index++, subres_index++ )
			{
				XE_ASSERT( subres_index < ( MAX_MIPMAPS * MAX_TEXTUREARRAY_LAYERS ) );
				const XE::int32 mip_width = ( ( img->cmn.width >> mip_index ) > 0 ) ? img->cmn.width >> mip_index : 1;
				const XE::int32 mip_height = ( ( img->cmn.height >> mip_index ) > 0 ) ? img->cmn.height >> mip_index : 1;
				const XE::int32 src_pitch = _RowPitch( img->cmn.pixel_format, mip_width );
				const SubImageContent * subimg_content = &( data->subimage[face_index][mip_index] );
				const XE::int32 slice_size = subimg_content->size / num_slices;
				const XE::int32 slice_offset = slice_size * slice_index;
				const uint8_t * slice_ptr = ( (const uint8_t * )subimg_content->ptr ) + slice_offset;
				hr = ID3D11DeviceContext_Map( _sg.d3d11.ctx, d3d11_res, subres_index, D3D11_MAP_WRITE_DISCARD, 0, &d3d11_msr );
				XE_ASSERT( SUCCEEDED( hr ) );
				/* FIXME: need to handle difference in depth-pitch for 3D textures as well! */
				if( src_pitch == (XE::int32 )d3d11_msr.RowPitch )
				{
					memcpy( d3d11_msr.pData, slice_ptr, slice_size );
				}
				else
				{
					XE_ASSERT( src_pitch < (XE::int32 )d3d11_msr.RowPitch );
					const uint8_t * src_ptr = slice_ptr;
					uint8_t * dst_ptr = (uint8_t * )d3d11_msr.pData;
					for( XE::int32 row_index = 0; row_index < mip_height; row_index++ )
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