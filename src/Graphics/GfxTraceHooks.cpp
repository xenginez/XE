#include "GfxTraceHooks.h"

USING_XE

void GfxTraceHooks::reset_state_cache()
{

}

void GfxTraceHooks::make_buffer( const BufferDesc * desc, BufferHandle result )
{

}

void GfxTraceHooks::make_image( const ImageDesc * desc, ImageHandle result )
{

}

void GfxTraceHooks::make_shader( const ShaderDesc * desc, ShaderHandle result )
{

}

void GfxTraceHooks::make_pipeline( const PipelineDesc * desc, PipelineHandle result )
{

}

void GfxTraceHooks::make_pass( const PassDesc * desc, PassHandle result )
{

}

void GfxTraceHooks::destroy_buffer( BufferHandle buf )
{

}

void GfxTraceHooks::destroy_image( ImageHandle img )
{

}

void GfxTraceHooks::destroy_shader( ShaderHandle shd )
{

}

void GfxTraceHooks::destroy_pipeline( PipelineHandle pip )
{

}

void GfxTraceHooks::destroy_pass( PassHandle pass )
{

}

void GfxTraceHooks::update_buffer( BufferHandle buf, const void * data_ptr, int data_size )
{

}

void GfxTraceHooks::update_image( ImageHandle img, const ImageContent * data )
{

}

void GfxTraceHooks::append_buffer( BufferHandle buf, const void * data_ptr, int data_size, int result )
{

}

void GfxTraceHooks::begin_default_pass( const PassAction * pass_action, int width, int height )
{

}

void GfxTraceHooks::begin_pass( PassHandle pass, const PassAction * pass_action )
{

}

void GfxTraceHooks::apply_viewport( int x, int y, int width, int height, bool origin_top_left )
{

}

void GfxTraceHooks::apply_scissor_rect( int x, int y, int width, int height, bool origin_top_left )
{

}

void GfxTraceHooks::apply_pipeline( PipelineHandle pip )
{

}

void GfxTraceHooks::apply_bindings( const Bindings * bindings )
{

}

void GfxTraceHooks::apply_uniforms( ShaderStage stage, int ub_index, const void * data, int num_bytes )
{

}

void GfxTraceHooks::draw( int base_element, int num_elements, int num_instances )
{

}

void GfxTraceHooks::end_pass()
{

}

void GfxTraceHooks::commit()
{

}

void GfxTraceHooks::alloc_buffer( BufferHandle result )
{

}

void GfxTraceHooks::alloc_image( ImageHandle result )
{

}

void GfxTraceHooks::alloc_shader( ShaderHandle result )
{

}

void GfxTraceHooks::alloc_pipeline( PipelineHandle result )
{

}

void GfxTraceHooks::alloc_pass( PassHandle result )
{

}

void GfxTraceHooks::init_buffer( BufferHandle buf_id, const BufferDesc * desc )
{

}

void GfxTraceHooks::init_image( ImageHandle img_id, const ImageDesc * desc )
{

}

void GfxTraceHooks::init_shader( ShaderHandle shd_id, const ShaderDesc * desc )
{

}

void GfxTraceHooks::init_pipeline( PipelineHandle pip_id, const PipelineDesc * desc )
{

}

void GfxTraceHooks::init_pass( PassHandle pass_id, const PassDesc * desc )
{

}

void GfxTraceHooks::fail_buffer( BufferHandle buf_id )
{

}

void GfxTraceHooks::fail_image( ImageHandle img_id )
{

}

void GfxTraceHooks::fail_shader( ShaderHandle shd_id )
{

}

void GfxTraceHooks::fail_pipeline( PipelineHandle pip_id )
{

}

void GfxTraceHooks::fail_pass( PassHandle pass_id )
{

}

void GfxTraceHooks::push_debug_group( const XE::String & name )
{

}

void GfxTraceHooks::pop_debug_group()
{

}

void GfxTraceHooks::err_buffer_pool_exhausted()
{

}

void GfxTraceHooks::err_image_pool_exhausted()
{

}

void GfxTraceHooks::err_shader_pool_exhausted()
{

}

void GfxTraceHooks::err_pipeline_pool_exhausted()
{

}

void GfxTraceHooks::err_pass_pool_exhausted()
{

}

void GfxTraceHooks::err_context_mismatch()
{

}

void GfxTraceHooks::err_pass_invalid()
{

}

void GfxTraceHooks::err_draw_invalid()
{

}

void GfxTraceHooks::err_bindings_invalid()
{

}
