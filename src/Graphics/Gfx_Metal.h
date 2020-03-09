#if defined(__APPLE__) || defined(_IOS)

#include "Gfx.h"

USING_XE

 #if !__has_feature(objc_arc)
    #error "Please enable ARC when using the Metal backend"
    #endif
    #include <TargetConditionals.h>
    #import <Metal/Metal.h>
    #if defined(TARGET_OS_IPHONE) && !TARGET_OS_IPHONE
        #define _TARGET_MACOS (1)
    #else
        #define _TARGET_IOS (1)
        #if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
            #define _TARGET_IOS_SIMULATOR (1)
        #endif
    #endif

enum
{
#if defined(_TARGET_MACOS) || defined(_TARGET_IOS_SIMULATOR)
	_MTL_UB_ALIGN = 256,
#else
	_MTL_UB_ALIGN = 16,
#endif
	_MTL_INVALID_SLOT_INDEX = 0
};

/* note that there's a free-standing _mtl_idpool NSMutableArray,
	this can't be part of a C struct before Xcode10.x
*/
typedef struct
{
	XE::uint32 frame_index;   /* frame index at which it is safe to release this resource */
	XE::uint32 slot_index;
} _mtl_release_item_t;

typedef struct
{
	XE::uint32 num_slots;
	XE::uint32 free_queue_top;
	XE::uint32 * free_queue;
	XE::uint32 release_queue_front;
	XE::uint32 release_queue_back;
	_mtl_release_item_t * release_queue;
} _mtl_idpool_t;

/* Metal sampler cache */
typedef struct
{
	Filter min_filter;
	Filter mag_filter;
	Wrap wrap_u;
	Wrap wrap_v;
	Wrap wrap_w;
	BorderColor border_color;
	XE::uint32 max_anisotropy;
	XE::int32 min_lod;    /* orig min/max_lod is float, this is XE::int32(min/max_lod*1000.0) */
	XE::int32 max_lod;
	XE::uint32 mtl_sampler_state;
} _mtl_sampler_cache_item_t;

typedef struct
{
	XE::int32 capacity;
	XE::int32 num_items;
	_mtl_sampler_cache_item_t * items;
} _mtl_sampler_cache_t;

typedef struct
{
	_SlotType slot;
	_Buffer_common_t cmn;
	struct
	{
		XE::uint32 buf[NUM_INFLIGHT_FRAMES];  /* index into _mtl_pool */
	} mtl;
} _mtl_buffer_t;
typedef _mtl_buffer_t _Buffer_t;

typedef struct
{
	_SlotType slot;
	_ImageCommonType cmn;
	struct
	{
		XE::uint32 tex[NUM_INFLIGHT_FRAMES];
		XE::uint32 depth_tex;
		XE::uint32 msaa_tex;
		XE::uint32 sampler_state;
	} mtl;
} _mtl_image_t;
typedef _mtl_image_t _ImageType;

typedef struct
{
	XE::uint32 mtl_lib;
	XE::uint32 mtl_func;
} _mtl_shader_stage_t;

typedef struct
{
	_SlotType slot;
	_ShaderCommonType cmn;
	struct
	{
		_mtl_shader_stage_t stage[NUM_SHADER_STAGES];
	} mtl;
} _mtl_shader_t;
typedef _mtl_shader_t _ShaderType;

typedef struct
{
	_SlotType slot;
	_PipelineCommonType cmn;
	_ShaderType * shader;
	struct
	{
		MTLPrimitiveType prim_type;
		NSUInteger index_size;
		MTLIndexType index_type;
		MTLCullMode cull_mode;
		MTLWinding winding;
		XE::uint32 stencil_ref;
		XE::uint32 rps;
		XE::uint32 dss;
	} mtl;
} _mtl_pipeline_t;
typedef _mtl_pipeline_t _PipelineType;

typedef struct
{
	_ImageType * image;
} _mtl_attachment_t;

typedef struct
{
	_SlotType slot;
	_PassCommonType cmn;
	struct
	{
		_mtl_attachment_t color_atts[MAX_COLOR_ATTACHMENTS];
		_mtl_attachment_t ds_att;
	} mtl;
} _mtl_pass_t;
typedef _mtl_pass_t _PassType;
typedef _AttachmentCommonType _AttachmentType;

typedef struct
{
	_SlotType slot;
} _mtl_context_t;
typedef _mtl_context_t _ContextType;

/* resouce binding state cache */
typedef struct
{
	const _PipelineType * cur_pipeline;
	PipelineHandle cur_pipeline_id;
	const _Buffer_t * cur_indexbuffer;
	XE::int32 cur_indexbuffer_offset;
	BufferHandle cur_indexbuffer_id;
	const _Buffer_t * cur_vertexbuffers[MAX_SHADERSTAGE_BUFFERS];
	XE::int32 cur_vertexbuffer_offsets[MAX_SHADERSTAGE_BUFFERS];
	BufferHandle cur_vertexbuffer_ids[MAX_SHADERSTAGE_BUFFERS];
	const _ImageType * cur_vs_images[MAX_SHADERSTAGE_IMAGES];
	ImageHandle cur_vs_image_ids[MAX_SHADERSTAGE_IMAGES];
	const _ImageType * cur_fs_images[MAX_SHADERSTAGE_IMAGES];
	ImageHandle cur_fs_image_ids[MAX_SHADERSTAGE_IMAGES];
} _mtl_state_cache_t;

typedef struct
{
	bool valid;
	const void * ( *renderpass_descriptor_cb )( void );
	const void * ( *drawable_cb )( void );
	XE::uint32 frame_index;
	XE::uint32 cur_frame_rotate_index;
	XE::uint32 ub_size;
	XE::uint32 cur_ub_offset;
	uint8_t * cur_ub_base_ptr;
	bool in_pass;
	bool pass_valid;
	XE::int32 cur_width;
	XE::int32 cur_height;
	_mtl_state_cache_t state_cache;
	_mtl_sampler_cache_t sampler_cache;
	_mtl_idpool_t idpool;
} _mtl_backend_t;
typedef _mtl_backend_t _BackendType;

typedef struct
{
	_PoolType buffer_pool;
	_PoolType image_pool;
	_PoolType shader_pool;
	_PoolType pipeline_pool;
	_PoolType pass_pool;
	_PoolType context_pool;
	_Buffer_t * buffers;
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
#if defined(SOKOL_DEBUG)
	_ValidateErrorType validate_error;
#endif
	_PoolsType pools;
	Backend backend;
	Features features;
	Limits limits;
	PixelFormatInfo formats[_PIXELFORMAT_NUM];
	_BackendType mtl;
#if defined(SOKOL_TRACE_HOOKS)
	GfxTraceHooks hooks;
#endif
} _StateType;

/* keep Objective-C 'smart data' in a separate static objects, these can't be in a C struct until Xcode10 or so */
static NSMutableArray * _mtl_idpool;
static id<MTLDevice> _mtl_device;
static id<MTLCommandQueue> _mtl_cmd_queue;
static id<MTLCommandBuffer> _mtl_cmd_buffer;
static id<MTLBuffer> _mtl_uniform_buffers[NUM_INFLIGHT_FRAMES];
static id<MTLRenderCommandEncoder> _mtl_cmd_encoder;
static dispatch_semaphore_t _mtl_sem;

#endif