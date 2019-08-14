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

	virtual ResourceHandle CreateShader( ShaderPtr & val ) = 0;

	virtual bool DestoryShader( ShaderPtr & val ) = 0;

	virtual ResourceHandle CreateTexture( TexturePtr & val ) = 0;

	virtual bool DestoryTexture( TexturePtr & val ) = 0;

	virtual ResourceHandle CreateUnorderedAccess( UnorderedAccessPtr & val ) = 0;

	virtual bool DestoryUnorderedAccess( UnorderedAccessPtr & val ) = 0;

	virtual ResourceHandle CreateSampler( SamplerPtr & val ) = 0;

	virtual bool DestroySampler( SamplerPtr & val ) = 0;

	virtual ResourceHandle CreateRenderTarget( RenderTargetPtr & val ) = 0;

	virtual bool DestroyRenderTarget( RenderTargetPtr & val ) = 0;

	virtual ResourceHandle CreateQuery( QueryPtr & val ) = 0;

	virtual bool DestoryQuery( QueryPtr & val ) = 0;

	virtual CommandListHandle CreateCommandList( CommandListPtr & val ) = 0;

	virtual void DestoryCommandList( CommandListHandle val ) = 0;

	virtual PipelineStateHandle CreatePipelineState( PipelineStatePtr & val ) = 0;

	virtual void DestoryPipelineState( PipelineStateHandle val ) = 0;

	/// CommandList Method
public:
	virtual void Dispatch( CommandListHandle handle, XE::uint32 ThreadGroupCountX, XE::uint32 ThreadGroupCountY, XE::uint32 ThreadGroupCountZ ) = 0;

	virtual void SetComputeTexture( CommandListHandle handle, XE::uint32 RootParameterIndex, TexturePtr BufferLocation ) = 0;

	virtual void SetComputeConstantBuffer( CommandListHandle handle, XE::uint32 RootParameterIndex, ConstantBufferPtr BufferLocation ) = 0;

	virtual void SetComputeUnorderedAccess( CommandListHandle handle, XE::uint32 RootParameterIndex, UnorderedAccessPtr BufferLocation ) = 0;

	virtual void SetCompute32BitConstant( CommandListHandle handle, XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues ) = 0;

	virtual void SetCompute32BitConstants( CommandListHandle handle, XE::uint32 RootParameterIndex, XE::basic_memory_view<XE::uint8> pSrcData, XE::uint32 DestOffsetIn32BitValues ) = 0;

	virtual bool Close( CommandListHandle handle ) = 0;

	virtual bool Reset( CommandListHandle handle, PipelineStatePtr & pInitialState ) = 0;

	virtual void ClearState( CommandListHandle handle, PipelineStatePtr & pPipelineState ) = 0;

	virtual void ResourceBarrierUAV( CommandListHandle handle, ResourcePtr pRsc ) = 0;

	virtual void ResourceBarrierAliasing( CommandListHandle handle, ResourcePtr pRscBefore, ResourcePtr pRscAfter ) = 0;

	virtual void ResourceBarrierTransition( CommandListHandle handle, ResourcePtr pRsc, ResourceState stateBefore, ResourceState stateAfter, XE::uint32 subRsc, BarrierFlag Flag ) = 0;

	virtual void SetPipelineState( CommandListHandle handle, PipelineStatePtr & pPipelineState ) = 0;

	virtual void ClearUnorderedAccessViewUint( CommandListHandle handle, UnorderedAccessPtr & pResource, const XE::uint32 Values[4], XE::basic_memory_view<Rect> pRects ) = 0;

	virtual void ClearUnorderedAccessViewFloat( CommandListHandle handle, UnorderedAccessPtr & pResource, const XE::float32 Values[4], XE::basic_memory_view<Rect> pRects ) = 0;

	virtual void DiscardResource( CommandListHandle handle, ResourcePtr & pResource, XE::basic_memory_view<Rect> pRects, XE::uint32 FirstSubresource, XE::uint32 NumSubresources ) = 0;

	virtual void ExecuteIndirect( CommandListHandle handle, XE::uint32 MaxCommandCount, ResourcePtr & pArgumentBuffer, XE::uint64 ArgumentBufferOffset, ResourcePtr & pCountBuffer, XE::uint64 CountBufferOffset ) = 0;

	virtual void CopyBufferRegion( CommandListHandle handle, ResourcePtr & pDstBuffer, XE::uint64 DstOffset, ResourcePtr & pSrcBuffer, XE::uint64 SrcOffset, XE::uint64 NumBytes ) = 0;

	virtual void CopyTextureRegion( CommandListHandle handle, TexturePtr dst, XE::uint32 DstX, XE::uint32 DstY, XE::uint32 DstZ, TexturePtr src, const std::array<XE::uint32, 6> & pSrcBox ) = 0;

	virtual void CopyResource( CommandListHandle handle, ResourcePtr & dst, ResourcePtr & src ) = 0;

	virtual void CopyTiles( CommandListHandle handle, ResourcePtr & pTiledResource, XE::uint32 X, XE::uint32 Y, XE::uint32 Z, XE::uint32 Subresource, bool UseBox, XE::uint32 NumTiles, XE::uint32 Width, XE::uint16 Height, XE::uint16 Depth, ResourcePtr & pBuffer, XE::uint64 BufferStartOffsetInBytes, TileCopyType Flags ) = 0;

	virtual void BeginQuery( CommandListHandle handle, QueryPtr Query, XE::uint32 Index ) = 0;

	virtual void EndQuery( CommandListHandle handle, QueryPtr Query, XE::uint32 Index ) = 0;

	virtual void BeginEvent( CommandListHandle handle, XE::uint32 Metadata, XE::basic_memory_view<XE::int8> pData ) = 0;

	virtual void EndEvent( CommandListHandle handle ) = 0;

	virtual void SetPredication( CommandListHandle handle, ResourcePtr & pBuffer, XE::uint64 AlignedBufferOffset, bool Equal ) = 0;

	virtual void SetMarker( CommandListHandle handle, XE::uint32 Metadata, XE::basic_memory_view<XE::int8> pData ) = 0;

	virtual void ResolveQueryData( CommandListHandle handle, QueryPtr Query, XE::uint32 StartIndex, XE::uint32 NumQueries, ResourcePtr & pDestinationBuffer, XE::uint64 AlignedDestinationBufferOffset ) = 0;

	virtual void ResolveSubresource( CommandListHandle handle, ResourcePtr pDstResource, XE::uint32 DstSubresource, ResourcePtr pSrcResource, XE::uint32 SrcSubresource, TextureFormat Format ) = 0;

	virtual void DrawInstanced( CommandListHandle handle, XE::uint32 VertexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartVertexLocation, XE::uint32 StartInstanceLocation ) = 0;

	virtual void DrawIndexedInstanced( CommandListHandle handle, XE::uint32 IndexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartIndexLocation, XE::int32 BaseVertexLocation, XE::uint32 StartInstanceLocation ) = 0;

	virtual void SetPrimitiveTopology( CommandListHandle handle, TopologyType PrimitiveTopology ) = 0;

	virtual void SetViewports( CommandListHandle handle, XE::basic_memory_view<Viewport> Viewports ) = 0;

	virtual void SetScissorRects( CommandListHandle handle, XE::basic_memory_view<Rect> Rects ) = 0;

	virtual void SetBlendFactor( CommandListHandle handle, const XE::float32 BlendFactor[4] ) = 0;

	virtual void SetStencilRef( CommandListHandle handle, XE::uint32 StencilRef ) = 0;

	virtual void ExecuteBundle( CommandListHandle handle, CommandListPtr & pCommandList ) = 0;

	virtual void SetGraphicsTexture( CommandListHandle handle, XE::uint32 RootParameterIndex, TexturePtr BufferLocation ) = 0;

	virtual void SetGraphicsConstantBuffer( CommandListHandle handle, XE::uint32 RootParameterIndex, ConstantBufferPtr BufferLocation ) = 0;

	virtual void SetGraphicsUnorderedAccess( CommandListHandle handle, XE::uint32 RootParameterIndex, UnorderedAccessPtr BufferLocation ) = 0;

	virtual void SetGraphics32BitConstant( CommandListHandle handle, XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues ) = 0;

	virtual void SetGraphics32BitConstants( CommandListHandle handle, XE::uint32 RootParameterIndex, XE::basic_memory_view<XE::uint8> pSrcData, XE::uint32 DestOffsetIn32BitValues ) = 0;

	virtual void SetIndexBuffer( CommandListHandle handle, IndexBufferPtr & pView ) = 0;

	virtual void SetVertexBuffers( CommandListHandle handle, XE::uint32 StartSlot, XE::uint32 NumViews, VertexBufferPtr & pViews ) = 0;

	virtual void SetTargets( CommandListHandle handle, XE::uint32 StartSlot, XE::basic_memory_view<ResourcePtr> pSrcs ) = 0;

	virtual void SetRenderTargets( CommandListHandle handle, XE::basic_memory_view<RenderTargetPtr> pRenderTargets, XE::basic_memory_view<DepthStencilBufferPtr> pDepthStencils, bool RTsSingleHandleToDescriptorRange ) = 0;

	virtual void ClearRenderTargetView( CommandListHandle handle, RenderTargetPtr RenderTargetView, const Color & ColorRGBA, XE::basic_memory_view<Rect> pRects ) = 0;

	virtual void ClearDepthStencilView( CommandListHandle handle, DepthStencilBufferPtr DepthStencilView, ClearType ClearFlags, XE::float32 Depth, XE::uint8 Stencil, XE::basic_memory_view<Rect> pRects ) = 0;

};

END_XE_NAMESPACE

#endif // CONTEXT_H__D80BEEA9_CB5A_4757_89F8_785D078A7BDB
