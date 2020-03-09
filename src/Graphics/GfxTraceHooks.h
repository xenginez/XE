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
	virtual void ResetStateCache();
	virtual void MakeBuffer( const BufferDesc * desc, BufferHandle result );
	virtual void MakeImage( const ImageDesc * desc, ImageHandle result );
	virtual void MakeShader( const ShaderDesc * desc, ShaderHandle result );
	virtual void MakePipeline( const PipelineDesc * desc, PipelineHandle result );
	virtual void MakePass( const PassDesc * desc, PassHandle result );
	virtual void DestroyBuffer( BufferHandle buf );
	virtual void DestroyImage( ImageHandle img );
	virtual void DestroyShader( ShaderHandle shd );
	virtual void DestroyPipeline( PipelineHandle pip );
	virtual void DestroyPass( PassHandle pass );
	virtual void UpdateBuffer( BufferHandle buf, const void * data_ptr, XE::int32 data_size );
	virtual void UpdateImage( ImageHandle img, const ImageContent * data );
	virtual void AppendBuffer( BufferHandle buf, const void * data_ptr, XE::int32 data_size, XE::int32 result );
	virtual void BeginDefaultPass( const PassAction * pass_action, XE::int32 width, XE::int32 height );
	virtual void BeginPass( PassHandle pass, const PassAction * pass_action );
	virtual void ApplyViewport( XE::int32 x, XE::int32 y, XE::int32 width, XE::int32 height, bool origin_top_left );
	virtual void ApplyScissorRect( XE::int32 x, XE::int32 y, XE::int32 width, XE::int32 height, bool origin_top_left );
	virtual void ApplyPipeline( PipelineHandle pip );
	virtual void ApplyBindings( const Bindings * bindings );
	virtual void ApplyUniforms( ShaderStage stage, XE::int32 ub_index, const void * data, XE::int32 num_bytes );
	virtual void Draw( XE::int32 base_element, XE::int32 num_elements, XE::int32 num_instances );
	virtual void EndPass();
	virtual void Commit();
	virtual void AllocBuffer( BufferHandle result );
	virtual void AllocImage( ImageHandle result );
	virtual void AllocShader( ShaderHandle result );
	virtual void AllocPipeline( PipelineHandle result );
	virtual void AllocPass( PassHandle result );
	virtual void InitBuffer( BufferHandle buf_id, const BufferDesc * desc );
	virtual void InitImage( ImageHandle img_id, const ImageDesc * desc );
	virtual void InitShader( ShaderHandle shd_id, const ShaderDesc * desc );
	virtual void InitPipeline( PipelineHandle pip_id, const PipelineDesc * desc );
	virtual void InitPass( PassHandle pass_id, const PassDesc * desc );
	virtual void FailBuffer( BufferHandle buf_id );
	virtual void FailImage( ImageHandle img_id );
	virtual void FailShader( ShaderHandle shd_id );
	virtual void FailPipeline( PipelineHandle pip_id );
	virtual void FailPass( PassHandle pass_id );
	virtual void PushDebugGroup( const XE::String & name );
	virtual void PopDebugGroup();
	virtual void ErrBufferPoolExhausted();
	virtual void ErrImagePoolExhausted();
	virtual void ErrShaderPoolExhausted();
	virtual void ErrPipelinePoolExhausted();
	virtual void ErrPassPoolExhausted();
	virtual void ErrContextMismatch();
	virtual void ErrPassInvalid();
	virtual void ErrDrawInvalid();
	virtual void ErrBindingsInvalid();
};


#define _TRACE_ARGS(fn, ...) if (_sg.hooks) { _sg.hooks->fn(__VA_ARGS__); }
#define _TRACE_NOARGS(fn) if (_sg.hooks) { _sg.hooks->fn(); }

END_XE_NAMESPACE

#endif // GFXTRACEHOOKS_H__6070A7ED_210F_45D4_902A_AA93362E5A83
