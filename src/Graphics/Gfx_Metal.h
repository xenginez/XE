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
	uint32_t frame_index;   /* frame index at which it is safe to release this resource */
	uint32_t slot_index;
} _mtl_release_item_t;

typedef struct
{
	uint32_t num_slots;
	uint32_t free_queue_top;
	uint32_t * free_queue;
	uint32_t release_queue_front;
	uint32_t release_queue_back;
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
	uint32_t max_anisotropy;
	int min_lod;    /* orig min/max_lod is float, this is int(min/max_lod*1000.0) */
	int max_lod;
	uint32_t mtl_sampler_state;
} _mtl_sampler_cache_item_t;

typedef struct
{
	int capacity;
	int num_items;
	_mtl_sampler_cache_item_t * items;
} _mtl_sampler_cache_t;

typedef struct
{
	_slot_t slot;
	_Buffer_common_t cmn;
	struct
	{
		uint32_t buf[NUM_INFLIGHT_FRAMES];  /* index into _mtl_pool */
	} mtl;
} _mtl_buffer_t;
typedef _mtl_buffer_t _Buffer_t;

typedef struct
{
	_slot_t slot;
	_image_common_t cmn;
	struct
	{
		uint32_t tex[NUM_INFLIGHT_FRAMES];
		uint32_t depth_tex;
		uint32_t msaa_tex;
		uint32_t sampler_state;
	} mtl;
} _mtl_image_t;
typedef _mtl_image_t _image_t;

typedef struct
{
	uint32_t mtl_lib;
	uint32_t mtl_func;
} _mtl_shader_stage_t;

typedef struct
{
	_slot_t slot;
	_shader_common_t cmn;
	struct
	{
		_mtl_shader_stage_t stage[NUM_SHADER_STAGES];
	} mtl;
} _mtl_shader_t;
typedef _mtl_shader_t _shader_t;

typedef struct
{
	_slot_t slot;
	_pipeline_common_t cmn;
	_shader_t * shader;
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
} _mtl_pipeline_t;
typedef _mtl_pipeline_t _pipeline_t;

typedef struct
{
	_image_t * image;
} _mtl_attachment_t;

typedef struct
{
	_slot_t slot;
	_pass_common_t cmn;
	struct
	{
		_mtl_attachment_t color_atts[MAX_COLOR_ATTACHMENTS];
		_mtl_attachment_t ds_att;
	} mtl;
} _mtl_pass_t;
typedef _mtl_pass_t _pass_t;
typedef _attachment_common_t _attachment_t;

typedef struct
{
	_slot_t slot;
} _mtl_context_t;
typedef _mtl_context_t _context_t;

/* resouce binding state cache */
typedef struct
{
	const _pipeline_t * cur_pipeline;
	PipelineHandle cur_pipeline_id;
	const _Buffer_t * cur_indexbuffer;
	int cur_indexbuffer_offset;
	BufferHandle cur_indexbuffer_id;
	const _Buffer_t * cur_vertexbuffers[MAX_SHADERSTAGE_BUFFERS];
	int cur_vertexbuffer_offsets[MAX_SHADERSTAGE_BUFFERS];
	BufferHandle cur_vertexbuffer_ids[MAX_SHADERSTAGE_BUFFERS];
	const _image_t * cur_vs_images[MAX_SHADERSTAGE_IMAGES];
	ImageHandle cur_vs_image_ids[MAX_SHADERSTAGE_IMAGES];
	const _image_t * cur_fs_images[MAX_SHADERSTAGE_IMAGES];
	ImageHandle cur_fs_image_ids[MAX_SHADERSTAGE_IMAGES];
} _mtl_state_cache_t;

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
	_mtl_state_cache_t state_cache;
	_mtl_sampler_cache_t sampler_cache;
	_mtl_idpool_t idpool;
} _mtl_backend_t;
typedef _mtl_backend_t _backend_t;

typedef struct
{
	_pool_t buffer_pool;
	_pool_t image_pool;
	_pool_t shader_pool;
	_pool_t pipeline_pool;
	_pool_t pass_pool;
	_pool_t context_pool;
	_Buffer_t * buffers;
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
#if defined(SOKOL_DEBUG)
	_validate_error_t validate_error;
#endif
	_pools_t pools;
	Backend backend;
	Features features;
	Limits limits;
	PixelformatInfo formats[_PIXELFORMAT_NUM];
	_backend_t mtl;
#if defined(SOKOL_TRACE_HOOKS)
	GfxTraceHooks hooks;
#endif
} _state_t;

/* keep Objective-C 'smart data' in a separate static objects, these can't be in a C struct until Xcode10 or so */
static NSMutableArray * _mtl_idpool;
static id<MTLDevice> _mtl_device;
static id<MTLCommandQueue> _mtl_cmd_queue;
static id<MTLCommandBuffer> _mtl_cmd_buffer;
static id<MTLBuffer> _mtl_uniform_buffers[NUM_INFLIGHT_FRAMES];
static id<MTLRenderCommandEncoder> _mtl_cmd_encoder;
static dispatch_semaphore_t _mtl_sem;

#endif