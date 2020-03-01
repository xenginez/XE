#if defined(__APPLE__) || defined(_IOS)

#include "Gfx.h"

USING_XE

 #if !__has_feature(objc_arc)
    #error "Please enable ARC when using the Metal backend"
    #endif
    #include <TargetConditionals.h>
    #import <Metal/Metal.h>
    #if defined(TARGET_OS_IPHONE) && !TARGET_OS_IPHONE
        #define _SG_TARGET_MACOS (1)
    #else
        #define _SG_TARGET_IOS (1)
        #if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
            #define _SG_TARGET_IOS_SIMULATOR (1)
        #endif
    #endif

enum
{
#if defined(_SG_TARGET_MACOS) || defined(_SG_TARGET_IOS_SIMULATOR)
	_SG_MTL_UB_ALIGN = 256,
#else
	_SG_MTL_UB_ALIGN = 16,
#endif
	_SG_MTL_INVALID_SLOT_INDEX = 0
};

/* note that there's a free-standing _sg_mtl_idpool NSMutableArray,
	this can't be part of a C struct before Xcode10.x
*/
typedef struct
{
	uint32_t frame_index;   /* frame index at which it is safe to release this resource */
	uint32_t slot_index;
} _sg_mtl_release_item_t;

typedef struct
{
	uint32_t num_slots;
	uint32_t free_queue_top;
	uint32_t * free_queue;
	uint32_t release_queue_front;
	uint32_t release_queue_back;
	_sg_mtl_release_item_t * release_queue;
} _sg_mtl_idpool_t;

/* Metal sampler cache */
typedef struct
{
	Filter min_filter;
	Filter mag_filter;
	Wrap wrap_u;
	Wrap wrap_v;
	Wrap wrap_w;
	BorderColor border_color;
	uint32_t max_anisotropy;
	int min_lod;    /* orig min/max_lod is float, this is int(min/max_lod*1000.0) */
	int max_lod;
	uint32_t mtl_sampler_state;
} _sg_mtl_sampler_cache_item_t;

typedef struct
{
	int capacity;
	int num_items;
	_sg_mtl_sampler_cache_item_t * items;
} _sg_mtl_sampler_cache_t;

typedef struct
{
	_sg_slot_t slot;
	_Buffer_common_t cmn;
	struct
	{
		uint32_t buf[SG_NUM_INFLIGHT_FRAMES];  /* index into _sg_mtl_pool */
	} mtl;
} _sg_mtl_buffer_t;
typedef _sg_mtl_buffer_t _Buffer_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_image_common_t cmn;
	struct
	{
		uint32_t tex[SG_NUM_INFLIGHT_FRAMES];
		uint32_t depth_tex;
		uint32_t msaa_tex;
		uint32_t sampler_state;
	} mtl;
} _sg_mtl_image_t;
typedef _sg_mtl_image_t _sg_image_t;

typedef struct
{
	uint32_t mtl_lib;
	uint32_t mtl_func;
} _sg_mtl_shader_stage_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_shader_common_t cmn;
	struct
	{
		_sg_mtl_shader_stage_t stage[SG_NUM_SHADER_STAGES];
	} mtl;
} _sg_mtl_shader_t;
typedef _sg_mtl_shader_t _sg_shader_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_pipeline_common_t cmn;
	_sg_shader_t * shader;
	struct
	{
		MTLPrimitiveType prim_type;
		NSUInteger index_size;
		MTLIndexType index_type;
		MTLCullMode cull_mode;
		MTLWinding winding;
		uint32_t stencil_ref;
		uint32_t rps;
		uint32_t dss;
	} mtl;
} _sg_mtl_pipeline_t;
typedef _sg_mtl_pipeline_t _sg_pipeline_t;

typedef struct
{
	_sg_image_t * image;
} _sg_mtl_attachment_t;

typedef struct
{
	_sg_slot_t slot;
	_sg_pass_common_t cmn;
	struct
	{
		_sg_mtl_attachment_t color_atts[SG_MAX_COLOR_ATTACHMENTS];
		_sg_mtl_attachment_t ds_att;
	} mtl;
} _sg_mtl_pass_t;
typedef _sg_mtl_pass_t _sg_pass_t;
typedef _sg_attachment_common_t _sg_attachment_t;

typedef struct
{
	_sg_slot_t slot;
} _sg_mtl_context_t;
typedef _sg_mtl_context_t _sg_context_t;

/* resouce binding state cache */
typedef struct
{
	const _sg_pipeline_t * cur_pipeline;
	PipelineHandle cur_pipeline_id;
	const _Buffer_t * cur_indexbuffer;
	int cur_indexbuffer_offset;
	BufferHandle cur_indexbuffer_id;
	const _Buffer_t * cur_vertexbuffers[SG_MAX_SHADERSTAGE_BUFFERS];
	int cur_vertexbuffer_offsets[SG_MAX_SHADERSTAGE_BUFFERS];
	BufferHandle cur_vertexbuffer_ids[SG_MAX_SHADERSTAGE_BUFFERS];
	const _sg_image_t * cur_vs_images[SG_MAX_SHADERSTAGE_IMAGES];
	ImageHandle cur_vs_image_ids[SG_MAX_SHADERSTAGE_IMAGES];
	const _sg_image_t * cur_fs_images[SG_MAX_SHADERSTAGE_IMAGES];
	ImageHandle cur_fs_image_ids[SG_MAX_SHADERSTAGE_IMAGES];
} _sg_mtl_state_cache_t;

typedef struct
{
	bool valid;
	const void * ( *renderpass_descriptor_cb )( void );
	const void * ( *drawable_cb )( void );
	uint32_t frame_index;
	uint32_t cur_frame_rotate_index;
	uint32_t ub_size;
	uint32_t cur_ub_offset;
	uint8_t * cur_ub_base_ptr;
	bool in_pass;
	bool pass_valid;
	int cur_width;
	int cur_height;
	_sg_mtl_state_cache_t state_cache;
	_sg_mtl_sampler_cache_t sampler_cache;
	_sg_mtl_idpool_t idpool;
} _sg_mtl_backend_t;
typedef _sg_mtl_backend_t _sg_backend_t;

typedef struct
{
	_sg_pool_t buffer_pool;
	_sg_pool_t image_pool;
	_sg_pool_t shader_pool;
	_sg_pool_t pipeline_pool;
	_sg_pool_t pass_pool;
	_sg_pool_t context_pool;
	_Buffer_t * buffers;
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
#if defined(SOKOL_DEBUG)
	_sg_validate_error_t validate_error;
#endif
	_sg_pools_t pools;
	Backend backend;
	Features features;
	Limits limits;
	PixelformatInfo formats[_SG_PIXELFORMAT_NUM];
	_sg_backend_t mtl;
#if defined(SOKOL_TRACE_HOOKS)
	GfxTraceHooks hooks;
#endif
} _sg_state_t;

/* keep Objective-C 'smart data' in a separate static objects, these can't be in a C struct until Xcode10 or so */
static NSMutableArray * _sg_mtl_idpool;
static id<MTLDevice> _sg_mtl_device;
static id<MTLCommandQueue> _sg_mtl_cmd_queue;
static id<MTLCommandBuffer> _sg_mtl_cmd_buffer;
static id<MTLBuffer> _sg_mtl_uniform_buffers[SG_NUM_INFLIGHT_FRAMES];
static id<MTLRenderCommandEncoder> _sg_mtl_cmd_encoder;
static dispatch_semaphore_t _sg_mtl_sem;

#endif