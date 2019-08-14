/*!
 * \file	CommandList.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/21
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef COMMANDLIST_H__D330A60E_5A01_477B_923F_E62B117F3978
#define COMMANDLIST_H__D330A60E_5A01_477B_923F_E62B117F3978

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API CommandList : public std::enable_shared_from_this< CommandList >, public XE::NonCopyable
{
public:
	CommandList( RenderContextRPtr context, CommandListType type, CommandListHandle handle );

	~CommandList();

public:
	CommandListType GetType() const;

public:
	void Dispatch( XE::uint32 ThreadGroupCountX, XE::uint32 ThreadGroupCountY, XE::uint32 ThreadGroupCountZ );

	void SetComputeTexture( XE::uint32 RootParameterIndex, TexturePtr BufferLocation );

	void SetComputeConstantBuffer( XE::uint32 RootParameterIndex, ConstantBufferPtr BufferLocation );

	void SetComputeUnorderedAccess( XE::uint32 RootParameterIndex, UnorderedAccessPtr BufferLocation );

	void SetCompute32BitConstant( XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues );

	void SetCompute32BitConstants( XE::uint32 RootParameterIndex, XE::basic_memory_view<XE::uint8> pSrcData, XE::uint32 DestOffsetIn32BitValues );

public:
	bool Close();

	bool Reset( PipelineStatePtr & pInitialState );

	void ClearState( PipelineStatePtr & pPipelineState );

	void ResourceBarrierUAV( ResourcePtr pRsc );

	void ResourceBarrierAliasing( ResourcePtr pRscBefore, ResourcePtr pRscAfter );

	void ResourceBarrierTransition( ResourcePtr pRsc, ResourceState stateBefore, ResourceState stateAfter, XE::uint32 subRsc = 0xffffffff, BarrierFlag Flag = BarrierFlag::NONE );

	void SetPipelineState( PipelineStatePtr & pPipelineState );

	void ClearUnorderedAccessViewUint( UnorderedAccessPtr & pResource, const XE::uint32 Values[4], XE::basic_memory_view<Rect> pRects );

	void ClearUnorderedAccessViewFloat( UnorderedAccessPtr & pResource, const XE::float32 Values[4], XE::basic_memory_view<Rect> pRects );

	void DiscardResource( ResourcePtr & pResource, XE::basic_memory_view<Rect> pRects, XE::uint32 FirstSubresource, XE::uint32 NumSubresources );

	void ExecuteIndirect( XE::uint32 MaxCommandCount, ResourcePtr & pArgumentBuffer, XE::uint64 ArgumentBufferOffset, ResourcePtr & pCountBuffer, XE::uint64 CountBufferOffset );

public:
	void CopyBufferRegion( ResourcePtr & pDstBuffer, XE::uint64 DstOffset, ResourcePtr & pSrcBuffer, XE::uint64 SrcOffset, XE::uint64 NumBytes );

	void CopyTextureRegion( TexturePtr dst, XE::uint32 DstX, XE::uint32 DstY, XE::uint32 DstZ, TexturePtr src, const std::array<XE::uint32, 6> & pSrcBox );

	void CopyResource( ResourcePtr & dst, ResourcePtr & src );

	void CopyTiles( ResourcePtr & pTiledResource, XE::uint32 X, XE::uint32 Y, XE::uint32 Z, XE::uint32 Subresource, bool UseBox, XE::uint32 NumTiles, XE::uint32 Width, XE::uint16 Height, XE::uint16 Depth, ResourcePtr & pBuffer, XE::uint64 BufferStartOffsetInBytes, TileCopyType Flags );

public:
	void BeginQuery( QueryPtr Query, XE::uint32 Index );

	void EndQuery( QueryPtr Query, XE::uint32 Index );

	void BeginEvent( XE::uint32 Metadata, XE::basic_memory_view<XE::int8> pData );

	void EndEvent();

	void SetPredication( ResourcePtr & pBuffer, XE::uint64 AlignedBufferOffset, bool Equal );

	void SetMarker( XE::uint32 Metadata, XE::basic_memory_view<XE::int8> pData );

	void ResolveQueryData( QueryPtr Query, XE::uint32 StartIndex, XE::uint32 NumQueries, ResourcePtr & pDestinationBuffer, XE::uint64 AlignedDestinationBufferOffset );
	
	void ResolveSubresource( ResourcePtr pDstResource, XE::uint32 DstSubresource, ResourcePtr pSrcResource, XE::uint32 SrcSubresource, TextureFormat Format );

public:
	void DrawInstanced( XE::uint32 VertexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartVertexLocation, XE::uint32 StartInstanceLocation );

	void DrawIndexedInstanced( XE::uint32 IndexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartIndexLocation, XE::int32 BaseVertexLocation, XE::uint32 StartInstanceLocation );

	void SetPrimitiveTopology( TopologyType PrimitiveTopology );

	void SetViewports( XE::basic_memory_view<Viewport> Viewports );

	void SetScissorRects( XE::basic_memory_view<Rect> Rects );

	void SetBlendFactor( const XE::float32 BlendFactor[4] );

	void SetStencilRef( XE::uint32 StencilRef );

	void ExecuteBundle( CommandListPtr & pCommandList );

	void SetGraphicsTexture( XE::uint32 RootParameterIndex, TexturePtr BufferLocation );

	void SetGraphicsConstantBuffer( XE::uint32 RootParameterIndex, ConstantBufferPtr BufferLocation );

	void SetGraphicsUnorderedAccess( XE::uint32 RootParameterIndex, UnorderedAccessPtr BufferLocation );

	void SetGraphics32BitConstant( XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues );

	void SetGraphics32BitConstants( XE::uint32 RootParameterIndex, XE::basic_memory_view<XE::uint8> pSrcData, XE::uint32 DestOffsetIn32BitValues );

	void SetIndexBuffer( IndexBufferPtr & pView );

	void SetVertexBuffers( XE::uint32 StartSlot, XE::uint32 NumViews, VertexBufferPtr & pViews );

	void SetTargets( XE::uint32 StartSlot, XE::basic_memory_view<ResourcePtr> pSrcs );

	void SetRenderTargets( XE::basic_memory_view<RenderTargetPtr> pRenderTargets, XE::basic_memory_view<DepthStencilBufferPtr> pDepthStencils, bool RTsSingleHandleToDescriptorRange );

	void ClearRenderTargetView( RenderTargetPtr RenderTargetView, const Color & ColorRGBA, XE::basic_memory_view<Rect> pRects );

	void ClearDepthStencilView( DepthStencilBufferPtr DepthStencilView, ClearType ClearFlags, XE::float32 Depth, XE::uint8 Stencil, XE::basic_memory_view<Rect> pRects );

private:
	CommandListType _Type;
	CommandListHandle _Handle;
	RenderContextRPtr _Context;
};

END_XE_NAMESPACE

#endif // COMMANDLIST_H__D330A60E_5A01_477B_923F_E62B117F3978
