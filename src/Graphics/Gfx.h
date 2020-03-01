/*!
 * \file	Gfx.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/23
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GFX_H__12636FE6_A92D_467B_909E_9892450A6029
#define GFX_H__12636FE6_A92D_467B_909E_9892450A6029

#include "GfxTraceHooks.h"

BEG_XE_NAMESPACE

class Gfx
{
public:
	/* setup and misc functions */
	static void sg_setup( const GfxDesc * desc );
	static void sg_shutdown( void );
	static bool sg_isvalid( void );
	static void sg_reset_state_cache( void );
	static GfxTraceHooks * sg_install_trace_hooks( GfxTraceHooks * trace_hooks );
	static void sg_push_debug_group( const XE::String & name );
	static void sg_pop_debug_group( void );

	/* resource creation, destruction and updating */
	static BufferHandle sg_make_buffer( const BufferDesc * desc );
	static ImageHandle sg_make_image( const ImageDesc * desc );
	static ShaderHandle sg_make_shader( const ShaderDesc * desc );
	static PipelineHandle sg_make_pipeline( const PipelineDesc * desc );
	static PassHandle sg_make_pass( const PassDesc * desc );
	static void sg_destroy_buffer( BufferHandle buf );
	static void sg_destroy_image( ImageHandle img );
	static void sg_destroy_shader( ShaderHandle shd );
	static void sg_destroy_pipeline( PipelineHandle pip );
	static void sg_destroy_pass( PassHandle pass );
	static void sg_update_buffer( BufferHandle buf, const void * data_ptr, int data_size );
	static void sg_update_image( ImageHandle img, const ImageContent * data );
	static int sg_append_buffer( BufferHandle buf, const void * data_ptr, int data_size );
	static bool sg_query_buffer_overflow( BufferHandle buf );

	/* rendering functions */
	static void sg_begin_default_pass( const PassAction * pass_action, int width, int height );
	static void sg_begin_pass( PassHandle pass, const PassAction * pass_action );
	static void sg_apply_viewport( int x, int y, int width, int height, bool origin_top_left );
	static void sg_apply_scissor_rect( int x, int y, int width, int height, bool origin_top_left );
	static void sg_apply_pipeline( PipelineHandle pip );
	static void sg_apply_bindings( const Bindings * bindings );
	static void sg_apply_uniforms( ShaderStage stage, int ub_index, const void * data, int num_bytes );
	static void sg_draw( int base_element, int num_elements, int num_instances );
	static void sg_end_pass( void );
	static void sg_commit( void );

	/* getting information */
	static GfxDesc sg_query_desc( void );
	static Backend sg_query_backend( void );
	static Features sg_query_features( void );
	static Limits sg_query_limits( void );
	static PixelformatInfo sg_query_pixelformat( PixelFormat fmt );
	/* get current state of a resource (INITIAL, ALLOC, VALID, FAILED, INVALID) */
	static ResourceState sg_query_buffer_state( BufferHandle buf );
	static ResourceState sg_query_image_state( ImageHandle img );
	static ResourceState sg_query_shader_state( ShaderHandle shd );
	static ResourceState sg_query_pipeline_state( PipelineHandle pip );
	static ResourceState sg_query_pass_state( PassHandle pass );
	/* get runtime information about a resource */
	static BufferInfo sg_query_buffer_info( BufferHandle buf );
	static ImageInfo sg_query_image_info( ImageHandle img );
	static ShaderInfo sg_query_shader_info( ShaderHandle shd );
	static PipelineInfo sg_query_pipeline_info( PipelineHandle pip );
	static PassInfo sg_query_pass_info( PassHandle pass );
	/* get resource creation desc struct with their default values replaced */
	static BufferDesc sg_query_buffer_defaults( const BufferDesc * desc );
	static ImageDesc sg_query_image_defaults( const ImageDesc * desc );
	static ShaderDesc sg_query_shader_defaults( const ShaderDesc * desc );
	static PipelineDesc sg_query_pipeline_defaults( const PipelineDesc * desc );
	static PassDesc sg_query_pass_defaults( const PassDesc * desc );

	/* separate resource allocation and initialization (for async setup) */
	static BufferHandle sg_alloc_buffer( void );
	static ImageHandle sg_alloc_image( void );
	static ShaderHandle sg_alloc_shader( void );
	static PipelineHandle sg_alloc_pipeline( void );
	static PassHandle sg_alloc_pass( void );
	static void sg_init_buffer( BufferHandle buf_id, const BufferDesc * desc );
	static void sg_init_image( ImageHandle img_id, const ImageDesc * desc );
	static void sg_init_shader( ShaderHandle shd_id, const ShaderDesc * desc );
	static void sg_init_pipeline( PipelineHandle pip_id, const PipelineDesc * desc );
	static void sg_init_pass( PassHandle pass_id, const PassDesc * desc );
	static void sg_fail_buffer( BufferHandle buf_id );
	static void sg_fail_image( ImageHandle img_id );
	static void sg_fail_shader( ShaderHandle shd_id );
	static void sg_fail_pipeline( PipelineHandle pip_id );
	static void sg_fail_pass( PassHandle pass_id );

	/* rendering contexts (optional) */
	static ContextHandle sg_setup_context( void );
	static void sg_activate_context( ContextHandle ctx_id );
	static void sg_discard_context( ContextHandle ctx_id );

};

END_XE_NAMESPACE

#endif //GFX_H__12636FE6_A92D_467B_909E_9892450A6029
