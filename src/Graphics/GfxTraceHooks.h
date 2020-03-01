/*!
 * \file	GfxTraceHooks.h
 *
 * \author	ZhengYuanQing
 * \date	2020/02/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GFXTRACEHOOKS_H__6070A7ED_210F_45D4_902A_AA93362E5A83
#define GFXTRACEHOOKS_H__6070A7ED_210F_45D4_902A_AA93362E5A83

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API GfxTraceHooks
{
public:
	virtual void reset_state_cache();
	virtual void make_buffer( const BufferDesc * desc, BufferHandle result );
	virtual void make_image( const ImageDesc * desc, ImageHandle result );
	virtual void make_shader( const ShaderDesc * desc, ShaderHandle result );
	virtual void make_pipeline( const PipelineDesc * desc, PipelineHandle result );
	virtual void make_pass( const PassDesc * desc, PassHandle result );
	virtual void destroy_buffer( BufferHandle buf );
	virtual void destroy_image( ImageHandle img );
	virtual void destroy_shader( ShaderHandle shd );
	virtual void destroy_pipeline( PipelineHandle pip );
	virtual void destroy_pass( PassHandle pass );
	virtual void update_buffer( BufferHandle buf, const void * data_ptr, int data_size );
	virtual void update_image( ImageHandle img, const ImageContent * data );
	virtual void append_buffer( BufferHandle buf, const void * data_ptr, int data_size, int result );
	virtual void begin_default_pass( const PassAction * pass_action, int width, int height );
	virtual void begin_pass( PassHandle pass, const PassAction * pass_action );
	virtual void apply_viewport( int x, int y, int width, int height, bool origin_top_left );
	virtual void apply_scissor_rect( int x, int y, int width, int height, bool origin_top_left );
	virtual void apply_pipeline( PipelineHandle pip );
	virtual void apply_bindings( const Bindings * bindings );
	virtual void apply_uniforms( ShaderStage stage, int ub_index, const void * data, int num_bytes );
	virtual void draw( int base_element, int num_elements, int num_instances );
	virtual void end_pass();
	virtual void commit();
	virtual void alloc_buffer( BufferHandle result );
	virtual void alloc_image( ImageHandle result );
	virtual void alloc_shader( ShaderHandle result );
	virtual void alloc_pipeline( PipelineHandle result );
	virtual void alloc_pass( PassHandle result );
	virtual void init_buffer( BufferHandle buf_id, const BufferDesc * desc );
	virtual void init_image( ImageHandle img_id, const ImageDesc * desc );
	virtual void init_shader( ShaderHandle shd_id, const ShaderDesc * desc );
	virtual void init_pipeline( PipelineHandle pip_id, const PipelineDesc * desc );
	virtual void init_pass( PassHandle pass_id, const PassDesc * desc );
	virtual void fail_buffer( BufferHandle buf_id );
	virtual void fail_image( ImageHandle img_id );
	virtual void fail_shader( ShaderHandle shd_id );
	virtual void fail_pipeline( PipelineHandle pip_id );
	virtual void fail_pass( PassHandle pass_id );
	virtual void push_debug_group( const XE::String & name );
	virtual void pop_debug_group();
	virtual void err_buffer_pool_exhausted();
	virtual void err_image_pool_exhausted();
	virtual void err_shader_pool_exhausted();
	virtual void err_pipeline_pool_exhausted();
	virtual void err_pass_pool_exhausted();
	virtual void err_context_mismatch();
	virtual void err_pass_invalid();
	virtual void err_draw_invalid();
	virtual void err_bindings_invalid();
};


#define _SG_TRACE_ARGS(fn, ...) if (_sg.hooks) { _sg.hooks->fn(__VA_ARGS__); }
#define _SG_TRACE_NOARGS(fn) if (_sg.hooks) { _sg.hooks->fn(); }

END_XE_NAMESPACE

#endif // GFXTRACEHOOKS_H__6070A7ED_210F_45D4_902A_AA93362E5A83
