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

class RHI_API CommandList
{
public:
	CommandList( RenderContextRPtr val );

	~CommandList();

	/*

public:
	bool Close();

	bool Reset( PipelineStatePtr & pInitialState );

	void ClearState( PipelineStatePtr & pPipelineState );

	void DrawInstanced( XE::uint32 VertexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartVertexLocation, XE::uint32 StartInstanceLocation );

	void DrawIndexedInstanced( XE::uint32 IndexCountPerInstance, XE::uint32 InstanceCount, XE::uint32 StartIndexLocation, XE::int32 BaseVertexLocation, XE::uint32 StartInstanceLocation );

	void Dispatch( XE::uint32 ThreadGroupCountX, XE::uint32 ThreadGroupCountY, XE::uint32 ThreadGroupCountZ );

	void CopyBufferRegion( ResourcePtr & pDstBuffer, XE::uint64 DstOffset, ResourcePtr & pSrcBuffer, XE::uint64 SrcOffset, XE::uint64 NumBytes );

	void CopyTextureRegion( const D3D12_TEXTURE_COPY_LOCATION * dst, XE::uint32 DstX, XE::uint32 DstY, XE::uint32 DstZ, const D3D12_TEXTURE_COPY_LOCATION * src, const D3D12_BOX * pSrcBox );

	void CopyResource( ResourcePtr & dst, ResourcePtr & src );

	void CopyTiles( ResourcePtr & pTiledResource, const D3D12_TILED_RESOURCE_COORDINATE * pTileRegionStartCoordinate, const D3D12_TILE_REGION_SIZE * pTileRegionSize, ResourcePtr & pBuffer, XE::uint64 BufferStartOffsetInBytes, D3D12_TILE_COPY_FLAGS Flags );

	void ResolveSubresource( ResourcePtr & dst, XE::uint32 DstSubresource, ResourcePtr & src, XE::uint32 SrcSubresource, TextureFormat Format );

	void SetPrimitiveTopology( TopologyType PrimitiveTopology );

	void SetViewports( XE::basic_memory_view<Viewport> Viewports );

	void SetScissorRects( XE::basic_memory_view<Rect> Rects );

	void SetBlendFactor( const XE::float32 BlendFactor[4] );

	void SetStencilRef( XE::uint32 StencilRef );

	void SetPipelineState( PipelineStatePtr & pPipelineState );

	void ResourceBarrier( XE::uint32 NumBarriers, const D3D12_RESOURCE_BARRIER * pBarriers );

	void ExecuteBundle( ID3D12GraphicsCommandList * pCommandList );

	void SetDescriptorHeaps( XE::uint32 NumDescriptorHeaps, ID3D12DescriptorHeap * const * ppDescriptorHeaps );

	void SetComputeRootSignature( ID3D12RootSignature * pRootSignature );

	void SetGraphicsRootSignature( ID3D12RootSignature * pRootSignature );

	void SetComputeRootDescriptorTable( XE::uint32 RootParameterIndex, D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor );

	void SetGraphicsRootDescriptorTable( XE::uint32 RootParameterIndex, D3D12_GPU_DESCRIPTOR_HANDLE BaseDescriptor );

	void SetComputeRoot32BitConstant( XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues );

	void SetGraphicsRoot32BitConstant( XE::uint32 RootParameterIndex, XE::uint32 SrcData, XE::uint32 DestOffsetIn32BitValues );

	void SetComputeRoot32BitConstants( XE::uint32 RootParameterIndex, XE::uint32 Num32BitValuesToSet, const void * pSrcData, XE::uint32 DestOffsetIn32BitValues );

	void SetGraphicsRoot32BitConstants( XE::uint32 RootParameterIndex, XE::uint32 Num32BitValuesToSet, const void * pSrcData, XE::uint32 DestOffsetIn32BitValues );

	void SetComputeRootConstantBufferView( XE::uint32 RootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS BufferLocation );

	void SetGraphicsRootConstantBufferView( XE::uint32 RootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS BufferLocation );

	void SetComputeRootShaderResourceView( XE::uint32 RootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS BufferLocation );

	void SetGraphicsRootShaderResourceView( XE::uint32 RootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS BufferLocation );

	void SetComputeRootUnorderedAccessView( XE::uint32 RootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS BufferLocation );

	void SetGraphicsRootUnorderedAccessView( XE::uint32 RootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS BufferLocation );

	void SetIndexBuffer( IndexBufferPtr & pView );

	void SetVertexBuffers( XE::uint32 StartSlot, XE::uint32 NumViews, VertexBufferPtr & pViews );

	void SetTargets( XE::uint32 StartSlot, XE::uint32 NumViews, const D3D12_STREAM_OUTPUT_BUFFER_VIEW * pViews );

	void SetRenderTargets( XE::uint32 NumRenderTargetDescriptors, const D3D12_CPU_DESCRIPTOR_HANDLE * pRenderTargetDescriptors, BOOL RTsSingleHandleToDescriptorRange, const D3D12_CPU_DESCRIPTOR_HANDLE * pDepthStencilDescriptor );

	void ClearDepthStencilView( D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView, D3D12_CLEAR_FLAGS ClearFlags, XE::float32 Depth, XE::uint8 Stencil, XE::uint32 NumRects, const D3D12_RECT * pRects );

	void ClearRenderTargetView( D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView, const XE::float32 ColorRGBA[4], XE::uint32 NumRects, const D3D12_RECT * pRects );

	void ClearUnorderedAccessViewUint( D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap, D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle, ResourcePtr & pResource, const XE::uint32 Values[4], XE::uint32 NumRects, const D3D12_RECT * pRects );

	void ClearUnorderedAccessViewFloat( D3D12_GPU_DESCRIPTOR_HANDLE ViewGPUHandleInCurrentHeap, D3D12_CPU_DESCRIPTOR_HANDLE ViewCPUHandle, ResourcePtr & pResource, const XE::float32 Values[4], XE::uint32 NumRects, const D3D12_RECT * pRects );

	void DiscardResource( ResourcePtr & pResource, const D3D12_DISCARD_REGION * pRegion );

	void BeginQuery( ID3D12QueryHeap * pQueryHeap, D3D12_QUERY_TYPE Type, XE::uint32 Index );

	void EndQuery( ID3D12QueryHeap * pQueryHeap, D3D12_QUERY_TYPE Type, XE::uint32 Index );

	void ResolveQueryData( ID3D12QueryHeap * pQueryHeap, D3D12_QUERY_TYPE Type, XE::uint32 StartIndex, XE::uint32 NumQueries, ResourcePtr & pDestinationBuffer, XE::uint64 AlignedDestinationBufferOffset );

	void SetPredication( ResourcePtr & pBuffer, XE::uint64 AlignedBufferOffset, bool Equal );

	void SetMarker( XE::uint32 Metadata, XE::basic_memory_view<XE::int8> pData );

	void BeginEvent( XE::uint32 Metadata, XE::basic_memory_view<XE::int8> pData );

	void EndEvent( void );

	void ExecuteIndirect( ID3D12CommandSignature * pCommandSignature, XE::uint32 MaxCommandCount, ResourcePtr & pArgumentBuffer, XE::uint64 ArgumentBufferOffset, ResourcePtr & pCountBuffer, XE::uint64 CountBufferOffset );
	*/
private:
	RenderContextRPtr _Context;
};

END_XE_NAMESPACE

#endif // COMMANDLIST_H__D330A60E_5A01_477B_923F_E62B117F3978
