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

class RHI_API Context : public NonCopyable
{
	OBJECT( Context )

public:
	Context();

	virtual ~Context();

public:
	virtual void Startup() = 0;

	virtual void Present() = 0;

	virtual void Clearup() = 0;

public:
	virtual DeviceType GetType() const = 0;

public:
	virtual SwapChainHandle CreateSwapChain( SwapChainPtr & val ) = 0;

	virtual bool DestroySwapChain( SwapChainHandle handle ) = 0;

public:
	virtual ResourceHandle CreateResource( ResourcePtr & val ) = 0;

	virtual XE::basic_memory_view<XE::uint8> Map( ResourceHandle handle, XE::uint32 sub, XE::uint64 begin, XE::uint64 end, XE::uint8 * read_data ) = 0;

	virtual void Unmap( ResourceHandle handle, XE::uint32 sub, XE::uint64 begin, XE::uint64 end ) = 0;

	virtual bool DestoryResource( ResourceHandle handle ) = 0;

public:
	virtual ResourceHandle CreateBuffer( BufferPtr & val ) = 0;

	virtual bool ClearDepth( ResourceHandle handle, XE::real val ) = 0;

	virtual bool ClearStencil( ResourceHandle handle, XE::uint32 val ) = 0;

	virtual bool ClearDepthStencil( ResourceHandle handle, XE::real depth, XE::uint32 val ) = 0;

	virtual bool DestoryBuffer( ResourceHandle handle ) = 0;

public:
	virtual ResourceHandle CreateShader( ShaderPtr & val ) = 0;

	virtual bool DestoryShader( ResourceHandle handle ) = 0;

public:
	virtual ResourceHandle CreateTexture( TexturePtr & val ) = 0;

	virtual bool DestoryTexture( ResourceHandle handle ) = 0;

public:
	virtual ResourceHandle CreateUnorderedAccess( UnorderedAccessPtr & val ) = 0;

	virtual bool DestoryUnorderedAccess( ResourceHandle handle ) = 0;

public:
	virtual SamplerHandle CreateSampler( SamplerPtr & desc ) = 0;

	virtual bool DestroySampler( SamplerHandle handle ) = 0;

public:
	virtual RenderTargetHandle CreateRenderTarget( RenderTargetPtr & desc ) = 0;

	virtual bool ClearColor( RenderTargetHandle handle, const Color & val ) = 0;

	virtual bool DestroyRenderTarget( RenderTargetHandle handle ) = 0;

public:
	virtual FenceHandle CreateFence( XE::uint64 val ) = 0;

	virtual bool Wait( FenceHandle handle, XE::uint64 val ) = 0;

	virtual bool Signal( FenceHandle handle, XE::uint64 val ) = 0;

	virtual XE::uint64 GetCompletedValue( FenceHandle handle ) = 0;

	virtual bool DestroyFence( FenceHandle handle ) = 0;

public:
	virtual QueryHandle CreateQuery( QueryPtr & val ) = 0;

	virtual void BeginQuery( QueryHandle handle, XE::uint32 index ) = 0;

	virtual void EndQuery( QueryHandle handle, XE::uint32 index ) = 0;

	virtual Variant ReadBack( QueryHandle handle ) = 0;

	virtual bool DestoryQuery( QueryHandle handle ) = 0;

public:
	virtual EncoderPtr ResetEncoder( std::thread::id id = std::this_thread::get_id() ) = 0;

	virtual void CloseEncoder( const EncoderPtr & val ) = 0;

};

END_XE_NAMESPACE

#endif // CONTEXT_H__D80BEEA9_CB5A_4757_89F8_785D078A7BDB
