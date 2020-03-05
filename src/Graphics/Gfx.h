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
	static void Setup( const GfxDesc * desc );
	static void ShutDown( void );
	static bool IsValid( void );
	static void ResetStateCache( void );
	static GfxTraceHooks * InstallTraceHooks( GfxTraceHooks * trace_hooks );
	static void PushDebugGroup( const XE::String & name );
	static void PopDebugGroup( void );

public:
	/* resource creation, destruction and updating */
	static BufferHandle MakeBuffer( const BufferDesc * desc );
	static ImageHandle MakeImage( const ImageDesc * desc );
	static ShaderHandle MakeShader( const ShaderDesc * desc );
	static PipelineHandle MakePipeline( const PipelineDesc * desc );
	static PassHandle MakePass( const PassDesc * desc );
	static void DestroyBuffer( BufferHandle buf );
	static void DestroyImage( ImageHandle img );
	static void DestroyShader( ShaderHandle shd );
	static void DestroyPipeline( PipelineHandle pip );
	static void DestroyPass( PassHandle pass );
	static void UpdateBuffer( BufferHandle buf, const void * data_ptr, int data_size );
	static void UpdateImage( ImageHandle img, const ImageContent * data );
	static int AppendBuffer( BufferHandle buf, const void * data_ptr, int data_size );
	static bool QueryBufferOverflow( BufferHandle buf );

public:
	/* rendering functions */
	static void BeginDefaultPass( const PassAction * pass_action, int width, int height );
	static void BeginPass( PassHandle pass, const PassAction * pass_action );
	static void ApplyViewport( int x, int y, int width, int height, bool origin_top_left );
	static void ApplyScissorRect( int x, int y, int width, int height, bool origin_top_left );
	static void ApplyPipeline( PipelineHandle pip );
	static void ApplyBindings( const Bindings * bindings );
	static void ApplyUniforms( ShaderStage stage, int ub_index, const void * data, int num_bytes );
	static void Draw( int base_element, int num_elements, int num_instances );
	static void EndPass( void );
	static void Commit( void );

public:
	/* getting information */
	static GfxDesc QueryDesc( void );
	static Backend QueryBackend( void );
	static Features QueryFeatures( void );
	static Limits QueryLimits( void );
	static PixelformatInfo QueryPixelformat( PixelFormat fmt );
	/* get current state of a resource (INITIAL, ALLOC, VALID, FAILED, INVALID) */
	static ResourceState QueryBufferState( BufferHandle buf );
	static ResourceState QueryImageState( ImageHandle img );
	static ResourceState QueryShaderState( ShaderHandle shd );
	static ResourceState QueryPipelineState( PipelineHandle pip );
	static ResourceState QueryPassState( PassHandle pass );
	/* get runtime information about a resource */
	static BufferInfo QueryBufferInfo( BufferHandle buf );
	static ImageInfo QueryImageInfo( ImageHandle img );
	static ShaderInfo QueryShaderInfo( ShaderHandle shd );
	static PipelineInfo QueryPipelineInfo( PipelineHandle pip );
	static PassInfo QueryPassInfo( PassHandle pass );
	/* get resource creation desc struct with their default values replaced */
	static BufferDesc QueryBufferDefaults( const BufferDesc * desc );
	static ImageDesc QueryImageDefaults( const ImageDesc * desc );
	static ShaderDesc QueryShaderDefaults( const ShaderDesc * desc );
	static PipelineDesc QueryPipelineDefaults( const PipelineDesc * desc );
	static PassDesc QueryPassDefaults( const PassDesc * desc );

public:
	/* separate resource allocation and initialization (for async setup) */
	static BufferHandle AllocBuffer( void );
	static ImageHandle AllocImage( void );
	static ShaderHandle AllocShader( void );
	static PipelineHandle AllocPipeline( void );
	static PassHandle AllocPass( void );
	static void InitBuffer( BufferHandle buf_id, const BufferDesc * desc );
	static void InitImage( ImageHandle img_id, const ImageDesc * desc );
	static void InitShader( ShaderHandle shd_id, const ShaderDesc * desc );
	static void InitPipeline( PipelineHandle pip_id, const PipelineDesc * desc );
	static void InitPass( PassHandle pass_id, const PassDesc * desc );
	static void FailBuffer( BufferHandle buf_id );
	static void FailImage( ImageHandle img_id );
	static void FailShader( ShaderHandle shd_id );
	static void FailPipeline( PipelineHandle pip_id );
	static void FailPass( PassHandle pass_id );

public:
	/* rendering contexts (optional) */
	static ContextHandle SetupContext( void );
	static void ActivateContext( ContextHandle ctx_id );
	static void DiscardContext( ContextHandle ctx_id );

};

END_XE_NAMESPACE

#endif //GFX_H__12636FE6_A92D_467B_909E_9892450A6029
