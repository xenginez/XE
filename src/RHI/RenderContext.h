/*!
 * \file	Context.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CONTEXT_H__D80BEEA9_CB5A_4757_89F8_785D078A7BDB
#define CONTEXT_H__D80BEEA9_CB5A_4757_89F8_785D078A7BDB

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API RenderContext : public NonCopyable
{
	OBJECT( RenderContext )

public:
	RenderContext();

	virtual ~RenderContext();

public:
	virtual void Startup() = 0;

	virtual void Present() = 0;

	virtual void Clearup() = 0;

public:
	virtual RenderContextType GetType() const = 0;

public:
	virtual ResourceHandle CreateBuffer( BufferPtr & val ) = 0;

	virtual bool DestoryBuffer( BufferPtr & val ) = 0;

public:
	virtual ResourceHandle CreateShader( ShaderPtr & val ) = 0;

	virtual bool DestoryShader( ShaderPtr & val ) = 0;

public:
	virtual ResourceHandle CreateTexture( TexturePtr & val ) = 0;

	virtual bool DestoryTexture( TexturePtr & val ) = 0;

public:
	virtual ResourceHandle CreateUnorderedAccess( UnorderedAccessPtr & val ) = 0;

	virtual bool DestoryUnorderedAccess( UnorderedAccessPtr & val ) = 0;

public:
	virtual ResourceHandle CreateSampler( SamplerPtr & val ) = 0;

	virtual bool DestroySampler( SamplerPtr & val ) = 0;

public:
	virtual ResourceHandle CreateRenderTarget( RenderTargetPtr & val ) = 0;

	virtual bool DestroyRenderTarget( RenderTargetPtr & val ) = 0;

public:
	virtual ResourceHandle CreateQuery( QueryPtr & val ) = 0;

	virtual bool DestoryQuery( QueryPtr & val ) = 0;

public:
	virtual CommandListHandle CreateCommandList( CommandListPtr & val ) = 0;

	virtual void DestoryCommandList( CommandListHandle val ) = 0;

public:
	virtual PipelineStateHandle CreatePipelineState( PipelineStatePtr & val ) = 0;

	virtual void DestoryPipelineState( PipelineStateHandle val ) = 0;

};

END_XE_NAMESPACE

#endif // CONTEXT_H__D80BEEA9_CB5A_4757_89F8_785D078A7BDB
