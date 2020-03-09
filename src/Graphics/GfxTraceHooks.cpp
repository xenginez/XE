#include "GfxTraceHooks.h"

USING_XE

void GfxTraceHooks::ResetStateCache()
{

}

void GfxTraceHooks::MakeBuffer( const BufferDesc * desc, BufferHandle result )
{

}

void GfxTraceHooks::MakeImage( const ImageDesc * desc, ImageHandle result )
{

}

void GfxTraceHooks::MakeShader( const ShaderDesc * desc, ShaderHandle result )
{

}

void GfxTraceHooks::MakePipeline( const PipelineDesc * desc, PipelineHandle result )
{

}

void GfxTraceHooks::MakePass( const PassDesc * desc, PassHandle result )
{

}

void GfxTraceHooks::DestroyBuffer( BufferHandle buf )
{

}

void GfxTraceHooks::DestroyImage( ImageHandle img )
{

}

void GfxTraceHooks::DestroyShader( ShaderHandle shd )
{

}

void GfxTraceHooks::DestroyPipeline( PipelineHandle pip )
{

}

void GfxTraceHooks::DestroyPass( PassHandle pass )
{

}

void GfxTraceHooks::UpdateBuffer( BufferHandle buf, const void * data_ptr, XE::int32 data_size )
{

}

void GfxTraceHooks::UpdateImage( ImageHandle img, const ImageContent * data )
{

}

void GfxTraceHooks::AppendBuffer( BufferHandle buf, const void * data_ptr, XE::int32 data_size, XE::int32 result )
{

}

void GfxTraceHooks::BeginDefaultPass( const PassAction * pass_action, XE::int32 width, XE::int32 height )
{

}

void GfxTraceHooks::BeginPass( PassHandle pass, const PassAction * pass_action )
{

}

void GfxTraceHooks::ApplyViewport( XE::int32 x, XE::int32 y, XE::int32 width, XE::int32 height, bool origin_top_left )
{

}

void GfxTraceHooks::ApplyScissorRect( XE::int32 x, XE::int32 y, XE::int32 width, XE::int32 height, bool origin_top_left )
{

}

void GfxTraceHooks::ApplyPipeline( PipelineHandle pip )
{

}

void GfxTraceHooks::ApplyBindings( const Bindings * bindings )
{

}

void GfxTraceHooks::ApplyUniforms( ShaderStage stage, XE::int32 ub_index, const void * data, XE::int32 num_bytes )
{

}

void GfxTraceHooks::Draw( XE::int32 base_element, XE::int32 num_elements, XE::int32 num_instances )
{

}

void GfxTraceHooks::EndPass()
{

}

void GfxTraceHooks::Commit()
{

}

void GfxTraceHooks::AllocBuffer( BufferHandle result )
{

}

void GfxTraceHooks::AllocImage( ImageHandle result )
{

}

void GfxTraceHooks::AllocShader( ShaderHandle result )
{

}

void GfxTraceHooks::AllocPipeline( PipelineHandle result )
{

}

void GfxTraceHooks::AllocPass( PassHandle result )
{

}

void GfxTraceHooks::InitBuffer( BufferHandle buf_id, const BufferDesc * desc )
{

}

void GfxTraceHooks::InitImage( ImageHandle img_id, const ImageDesc * desc )
{

}

void GfxTraceHooks::InitShader( ShaderHandle shd_id, const ShaderDesc * desc )
{

}

void GfxTraceHooks::InitPipeline( PipelineHandle pip_id, const PipelineDesc * desc )
{

}

void GfxTraceHooks::InitPass( PassHandle pass_id, const PassDesc * desc )
{

}

void GfxTraceHooks::FailBuffer( BufferHandle buf_id )
{

}

void GfxTraceHooks::FailImage( ImageHandle img_id )
{

}

void GfxTraceHooks::FailShader( ShaderHandle shd_id )
{

}

void GfxTraceHooks::FailPipeline( PipelineHandle pip_id )
{

}

void GfxTraceHooks::FailPass( PassHandle pass_id )
{

}

void GfxTraceHooks::PushDebugGroup( const XE::String & name )
{

}

void GfxTraceHooks::PopDebugGroup()
{

}

void GfxTraceHooks::ErrBufferPoolExhausted()
{

}

void GfxTraceHooks::ErrImagePoolExhausted()
{

}

void GfxTraceHooks::ErrShaderPoolExhausted()
{

}

void GfxTraceHooks::ErrPipelinePoolExhausted()
{

}

void GfxTraceHooks::ErrPassPoolExhausted()
{

}

void GfxTraceHooks::ErrContextMismatch()
{

}

void GfxTraceHooks::ErrPassInvalid()
{

}

void GfxTraceHooks::ErrDrawInvalid()
{

}

void GfxTraceHooks::ErrBindingsInvalid()
{

}
