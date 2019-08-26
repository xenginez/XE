#include "CommandList.h"

#include "IRenderContext.h"

USING_XE

XE::CommandList::CommandList( IRenderContextRPtr context, CommandListType type, CommandListHandle handle )
	:_Context( context ), _Type( type ), _Handle( handle )
{

}

XE::CommandList::~CommandList()
{

}

XE::CommandListType XE::CommandList::GetType() const
{
	return _Type;
}

void XE::CommandList::Dispatch( XE::uint32 ThreadGroupCountX, XE::uint32 ThreadGroupCountY, XE::uint32 ThreadGroupCountZ )
{
	_Context->Dispatch( _Handle, ThreadGroupCountX, ThreadGroupCountY, ThreadGroupCountZ );
}

void XE::CommandList::SetComputeTexture( XE::uint32 RootParameterIndex, TexturePtr BufferLocation )
{
	_Context->SetComputeTexture( _Handle, RootParameterIndex, BufferLocation );
}

void XE::CommandList::SetComputeConstantBuffer( XE::uint32 RootParameterIndex, ConstantBufferPtr BufferLocation )
{
	_Context->SetComputeConstantBuffer( _Handle, RootParameterIndex, BufferLocation );
}

void XE::CommandList::SetComputeUnorderedAccess( XE::uint32 RootParameterIndex, UnorderedAccessPtr BufferLocation )
{
	_Context->SetComputeUnorderedAccess( _Handle, RootParameterIndex, BufferLocation );
}

void XE::CommandList::SetCompute32BitConstant( XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues )
{
	_Context->SetCompute32BitConstant( _Handle, RootParameterIndex, SrcData, DestOffsetIn32BitValues );
}

void XE::CommandList::SetCompute32BitConstants( XE::uint32 RootParameterIndex, XE::memory_view pSrcData, XE::uint32 DestOffsetIn32BitValues )
{
	_Context->SetCompute32BitConstants( _Handle, RootParameterIndex, pSrcData, DestOffsetIn32BitValues );
}

bool XE::CommandList::Close()
{
	return _Context->Close( _Handle );
}

bool XE::CommandList::Reset( PipelineStatePtr & pInitialState )
{
	return _Context->Reset( _Handle, pInitialState );
}

void XE::CommandList::ClearState( PipelineStatePtr & pPipelineState )
{
	_Context->ClearState( _Handle, pPipelineState );
}

void XE::CommandList::ResourceBarrierUAV( ResourcePtr pRsc )
{
	_Context->ResourceBarrierUAV( _Handle, pRsc );
}

void XE::CommandList::ResourceBarrierAliasing( ResourcePtr pRscBefore, ResourcePtr pRscAfter )
{
	_Context->ResourceBarrierAliasing( _Handle, pRscBefore, pRscAfter );
}

void XE::CommandList::ResourceBarrierTransition( ResourcePtr pRsc, ResourceState stateBefore, ResourceState stateAfter, XE::uint32 subRsc /*= 0xffffffff*/, BarrierFlag Flag /*= BarrierFlag::NONE */ )
{
	_Context->ResourceBarrierTransition( _Handle, pRsc, stateBefore, stateAfter, subRsc, Flag );
}

void XE::CommandList::SetPipelineState( PipelineStatePtr & pPipelineState )
{
	_Context->SetPipelineState( _Handle, pPipelineState );
}

void XE::CommandList::ClearUnorderedAccessViewUint( UnorderedAccessPtr & pResource, const XE::uint32 Values[4], XE::basic_memory_view<Rect> pRects )
{
	_Context->ClearUnorderedAccessViewUint( _Handle, pResource, Values, pRects );
}

void XE::CommandList::ClearUnorderedAccessViewFloat( UnorderedAccessPtr & pResource, const XE::float32 Values[4], XE::basic_memory_view<Rect> pRects )
{
	_Context->ClearUnorderedAccessViewFloat( _Handle, pResource, Values, pRects );
}

void XE::CommandList::DiscardResource( ResourcePtr & pResource, XE::basic_memory_view<Rect> pRects, XE::uint32 FirstSubresource, XE::uint32 NumSubresources )
{
	_Context->DiscardResource( _Handle, pResource, pRects, FirstSubresource, NumSubresources );
}

void XE::CommandList::ExecuteIndirect( XE::uint32 MaxCommandCount, ResourcePtr & pArgumentBuffer, XE::uint64 ArgumentBufferOffset, ResourcePtr & pCountBuffer, XE::uint64 CountBufferOffset )
{
	_Context->ExecuteIndirect( _Handle, MaxCommandCount, pArgumentBuffer, ArgumentBufferOffset, pCountBuffer, CountBufferOffset );
}

void XE::CommandList::CopyBufferRegion( ResourcePtr & pDstBuffer, XE::uint64 DstOffset, ResourcePtr & pSrcBuffer, XE::uint64 SrcOffset, XE::uint64 NumBytes )
{
	_Context->CopyBufferRegion( _Handle, pDstBuffer, DstOffset, pSrcBuffer, SrcOffset, NumBytes );
}

void XE::CommandList::CopyTextureRegion( TexturePtr dst, XE::uint32 DstX, XE::uint32 DstY, XE::uint32 DstZ, TexturePtr src, const std::array<XE::uint32, 6> & pSrcBox )
{
	_Context->CopyTextureRegion( _Handle, dst, DstX, DstY, DstZ, src, pSrcBox );
}

void XE::CommandList::CopyResource( ResourcePtr & dst, ResourcePtr & src )
{
	_Context->CopyResource( _Handle, dst, src );
}

void XE::CommandList::CopyTiles( ResourcePtr & pTiledResource, XE::uint32 X, XE::uint32 Y, XE::uint32 Z, XE::uint32 Subresource, bool UseBox, XE::uint32 NumTiles, XE::uint32 Width, XE::uint16 Height, XE::uint16 Depth, ResourcePtr & pBuffer, XE::uint64 BufferStartOffsetInBytes, TileCopyType Flags )
{
	_Context->CopyTiles( _Handle, pTiledResource, X, Y, Z, Subresource, UseBox, NumTiles, Width, Height, Depth, pBuffer, BufferStartOffsetInBytes, Flags );
}

void XE::CommandList::BeginQuery( QueryPtr Query, XE::uint32 Index )
{
	_Context->BeginQuery( _Handle, Query, Index );
}

void XE::CommandList::EndQuery( QueryPtr Query, XE::uint32 Index )
{
	_Context->EndQuery( _Handle, Query, Index );
}

void XE::CommandList::BeginEvent( XE::uint32 Metadata, XE::memory_view pData )
{
	_Context->BeginEvent( _Handle, Metadata, pData );
}

void XE::CommandList::EndEvent()
{
	_Context->EndEvent( _Handle );
}

void XE::CommandList::SetPredication( ResourcePtr & pBuffer, XE::uint64 AlignedBufferOffset, bool Equal )
{
	_Context->SetPredication( _Handle, pBuffer, AlignedBufferOffset, Equal );
}

void XE::CommandList::SetMarker( XE::uint32 Metadata, XE::memory_view pData )
{
	_Context->SetMarker( _Handle, Metadata, pData );
}

void XE::CommandList::ResolveQueryData( QueryPtr Query, XE::uint32 StartIndex, XE::uint32 NumQueries, ResourcePtr & pDestinationBuffer, XE::uint64 AlignedDestinationBufferOffset )
{
	_Context->ResolveQueryData( _Handle, Query, StartIndex, NumQueries, pDestinationBuffer, AlignedDestinationBufferOffset );
}

void XE::CommandList::ResolveSubresource( ResourcePtr pDstResource, XE::uint32 DstSubresource, ResourcePtr pSrcResource, XE::uint32 SrcSubresource, TextureFormat Format )
{
	_Context->ResolveSubresource( _Handle, pDstResource, DstSubresource, pSrcResource, SrcSubresource, Format );
}

void XE::CommandList::DrawInstanced( XE::uint32 VertexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartVertexLocation, XE::uint32 StartInstanceLocation )
{
	_Context->DrawInstanced( _Handle, VertexCountPerInstance, InstanceCount, StartVertexLocation, StartInstanceLocation );
}

void XE::CommandList::DrawIndexedInstanced( XE::uint32 IndexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartIndexLocation, XE::int32 BaseVertexLocation, XE::uint32 StartInstanceLocation )
{
	_Context->DrawIndexedInstanced( _Handle, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation );
}

void XE::CommandList::SetPrimitiveTopology( TopologyType PrimitiveTopology )
{
	_Context->SetPrimitiveTopology( _Handle, PrimitiveTopology );
}

void XE::CommandList::SetViewports( XE::basic_memory_view<Viewport> Viewports )
{
	_Context->SetViewports( _Handle, Viewports );
}

void XE::CommandList::SetScissorRects( XE::basic_memory_view<Rect> Rects )
{
	_Context->SetScissorRects( _Handle, Rects );
}

void XE::CommandList::SetBlendFactor( const XE::float32 BlendFactor[4] )
{
	_Context->SetBlendFactor( _Handle, BlendFactor );
}

void XE::CommandList::SetStencilRef( XE::uint32 StencilRef )
{
	_Context->SetStencilRef( _Handle, StencilRef );
}

void XE::CommandList::ExecuteBundle( CommandListPtr & pCommandList )
{
	_Context->ExecuteBundle( _Handle, pCommandList );
}

void XE::CommandList::SetGraphicsTexture( XE::uint32 RootParameterIndex, TexturePtr BufferLocation )
{
	_Context->SetGraphicsTexture( _Handle, RootParameterIndex, BufferLocation );
}

void XE::CommandList::SetGraphicsConstantBuffer( XE::uint32 RootParameterIndex, ConstantBufferPtr BufferLocation )
{
	_Context->SetGraphicsConstantBuffer( _Handle, RootParameterIndex, BufferLocation );
}

void XE::CommandList::SetGraphicsUnorderedAccess( XE::uint32 RootParameterIndex, UnorderedAccessPtr BufferLocation )
{
	_Context->SetGraphicsUnorderedAccess( _Handle, RootParameterIndex, BufferLocation );
}

void XE::CommandList::SetGraphics32BitConstant( XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues )
{
	_Context->SetGraphics32BitConstant( _Handle, RootParameterIndex, SrcData, DestOffsetIn32BitValues );
}

void XE::CommandList::SetGraphics32BitConstants( XE::uint32 RootParameterIndex, XE::memory_view pSrcData, XE::uint32 DestOffsetIn32BitValues )
{
	_Context->SetGraphics32BitConstants( _Handle, RootParameterIndex, pSrcData, DestOffsetIn32BitValues );
}

void XE::CommandList::SetIndexBuffer( IndexBufferPtr & pView )
{
	_Context->SetIndexBuffer( _Handle, pView );
}

void XE::CommandList::SetVertexBuffers( XE::uint32 StartSlot, XE::uint32 NumViews, VertexBufferPtr & pViews )
{
	_Context->SetVertexBuffers( _Handle, StartSlot, NumViews, pViews );
}

void XE::CommandList::SetTargets( XE::uint32 StartSlot, XE::basic_memory_view<ResourcePtr> pSrcs )
{
	_Context->SetTargets( _Handle, StartSlot, pSrcs );
}

void XE::CommandList::SetRenderTargets( XE::basic_memory_view<RenderTargetPtr> pRenderTargets, XE::basic_memory_view<DepthStencilBufferPtr> pDepthStencils, bool RTsSingleHandleToDescriptorRange )
{
	_Context->SetRenderTargets( _Handle, pRenderTargets, pDepthStencils, RTsSingleHandleToDescriptorRange );
}

void XE::CommandList::ClearRenderTargetView( RenderTargetPtr RenderTargetView, const Color & ColorRGBA, XE::basic_memory_view<Rect> pRects )
{
	_Context->ClearRenderTargetView( _Handle, RenderTargetView, ColorRGBA, pRects );
}

void XE::CommandList::ClearDepthStencilView( DepthStencilBufferPtr DepthStencilView, ClearType ClearFlags, XE::float32 Depth, XE::uint8 Stencil, XE::basic_memory_view<Rect> pRects )
{
	_Context->ClearDepthStencilView( _Handle, DepthStencilView, ClearFlags, Depth, Stencil, pRects );
}
