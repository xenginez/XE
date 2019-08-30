/*!
 * \file	IRenderContext.h
 *
 * \author	ZhengYuanQing
 * \date	2019/08/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef IRENDERCONTEXT_H__2A432E01_836A_457E_A061_58BD721E11C7
#define IRENDERCONTEXT_H__2A432E01_836A_457E_A061_58BD721E11C7

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API IRenderContext : public XE::Object, public NonCopyable
{
	OBJECT( IRenderContext, Object )

public:
	friend class CommandList;

public:
	IRenderContext();

	virtual ~IRenderContext();

public:
	virtual void Startup() = 0;

	virtual void Present() = 0;

	virtual void Clearup() = 0;

public:
	virtual RenderContextType GetType() const = 0;

public:
	virtual IndexBufferHandle CreateIndexBuffer( XE::memory_view mem ) = 0;

	virtual void SetDebugName( IndexBufferHandle handle, const String & name ) = 0;

	virtual void Destroy( IndexBufferHandle handle ) = 0;

	virtual VertexBufferHandle CreateVertexBuffer( XE::memory_view mem, const VertexLayout & decl ) = 0;

	virtual void SetDebugName( VertexBufferHandle handle, const String & name ) = 0;

	virtual void Destroy( VertexBufferHandle handle ) = 0;

	virtual DynamicIndexBufferHandle CreateDynamicIndexBuffer( XE::memory_view mem ) = 0;

	virtual void Update( DynamicIndexBufferHandle handle, XE::uint32 startIndex, XE::memory_view mem ) = 0;

	virtual void Destroy( DynamicIndexBufferHandle handle ) = 0;

	virtual DynamicVertexBufferHandle CreateDynamicVertexBuffer( XE::memory_view mem, const VertexLayout & decl ) = 0;

	virtual void Update( DynamicVertexBufferHandle handle, XE::uint32 startVertex, XE::memory_view mem ) = 0;

	virtual void Destroy( DynamicVertexBufferHandle handle ) = 0;

	virtual InstanceBufferHandle CreateInstanceBuffer( XE::memory_view mem, XE::uint32 offset, XE::uint32 num, XE::uint16 stride, VertexBufferHandle handle ) = 0;

	virtual void Destroy( InstanceBufferHandle handle ) = 0;

	virtual IndirectBufferHandle CreateIndirectBuffer( XE::uint32 num ) = 0;

	virtual void Destroy( IndirectBufferHandle handle ) = 0;

	virtual ShaderHandle CreateShader( XE::memory_view mem ) = 0;

	virtual void SetDebugName( ShaderHandle handle, const String & name ) = 0;

	virtual XE::uint16 GetShaderUniforms( ShaderHandle handle, UniformHandle * uniforms = NULL, XE::uint16 max = 0 ) = 0;

	virtual void Destroy( ShaderHandle handle ) = 0;

	virtual BlendStateHandle CreateBlendState( bool independentblend, bool alphatocoverage ) = 0;

	virtual void Destroy( BlendStateHandle handle ) = 0;

	virtual RasterizerStateHandle CreateRasterizerState() = 0;

	virtual void Destroy( RasterizerStateHandle handle ) = 0;

	virtual DepthStencilStateHandle CreateDepthStencilState() = 0;

	virtual void Destroy( DepthStencilStateHandle handle ) = 0;

	virtual GraphicsPipelineStateHandle CreatePipelineState( BlendStateHandle bhandle, RasterizerStateHandle rhandle, DepthStencilStateHandle dhandle, ShaderHandle vs, ShaderHandle ps, ShaderHandle hs, ShaderHandle gs, ShaderHandle ds ) = 0;

	virtual void Destroy( GraphicsPipelineStateHandle handle ) = 0;

	virtual ComputePipelineStateHandle CreatePipelineState( ShaderHandle cs ) = 0;

	virtual void Destroy( ComputePipelineStateHandle handle ) = 0;

	virtual bool IsTextureValid( XE::uint16 depth, bool cubeMap, XE::uint16 numLayers, TextureFormat format, XE::uint64 flags ) = 0;

	virtual TextureHandle CreateTexture1D( XE::uint16 width, bool hasMips, XE::uint16 numLayers, TextureFormat format, SamplerFilter filter, SamplerAddress address, CompareType compare, XE::memory_view mem = nullptr ) = 0;

	virtual TextureHandle CreateTexture2D( XE::uint16 width, XE::uint16 height, bool hasMips, XE::uint16 numLayers, TextureFormat format, SamplerFilter filter, SamplerAddress address, CompareType compare, XE::memory_view mem = nullptr ) = 0;

	virtual TextureHandle CreateTexture3D( XE::uint16 width, XE::uint16 height, XE::uint16 depth, bool hasMips, TextureFormat format, SamplerFilter filter, SamplerAddress address, CompareType compare, XE::memory_view mem = nullptr ) = 0;

	virtual TextureHandle CreateTextureCube( XE::uint16 size, bool hasMips, XE::uint16 numLayers, TextureFormat format, SamplerFilter filter, SamplerAddress address, CompareType compare, XE::memory_view mem = nullptr ) = 0;

	virtual void UpdateTexture1D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip, XE::uint16 x, XE::uint16 width, XE::memory_view mem ) = 0;

	virtual void UpdateTexture2D( TextureHandle handle, XE::uint16 layer, XE::uint8 mip, XE::uint16 x, XE::uint16 y, XE::uint16 width, XE::uint16 height, XE::memory_view mem, XE::uint16 pitch = UINT16_MAX ) = 0;

	virtual void UpdateTexture3D( TextureHandle handle, XE::uint8 mip, XE::uint16 x, XE::uint16 y, XE::uint16 z, XE::uint16 width, XE::uint16 height, XE::uint16 depth, XE::memory_view mem ) = 0;

	virtual void UpdateTextureCube( TextureHandle handle, XE::uint16 layer, XE::uint8 side, XE::uint8 mip, XE::uint16 x, XE::uint16 y, XE::uint16 width, XE::uint16 height, XE::memory_view mem, XE::uint16 pitch = UINT16_MAX ) = 0;

	virtual XE::uint32 ReadTexture( TextureHandle handle, void * data, XE::uint8 mip = 0 ) = 0;

	virtual void SetDebugName( TextureHandle handle, const String & name ) = 0;

	virtual void Destroy( TextureHandle handle ) = 0;

	virtual FrameBufferHandle CreateFrameBuffer( XE::uint16 width, XE::uint16 height, TextureFormat format, SamplerFilter filter, SamplerAddress address, CompareType comparea ) = 0;

	virtual FrameBufferHandle CreateFrameBuffer( XE::basic_memory_view<TextureHandle> mem ) = 0;

	virtual FrameBufferHandle CreateFrameBuffer( WindowHandle handle, XE::uint16 width, XE::uint16 height, TextureFormat format = TextureFormat::RGBA8, TextureFormat depthFormat = TextureFormat::D24S8 ) = 0;

	virtual TextureHandle GetTexture( FrameBufferHandle handle, XE::uint8 index = 0 ) = 0;

	virtual void SetDebugName( FrameBufferHandle handle, const String & name ) = 0;

	virtual void Destroy( FrameBufferHandle handle ) = 0;

	virtual UniformHandle CreateUniform( const String & name, UniformType type, XE::uint16 num = 1 ) = 0;

	virtual void Destroy( UniformHandle handle ) = 0;

	virtual OcclusionQueryHandle CreateOcclusionQuery() = 0;

	virtual bool GetResult( OcclusionQueryHandle handle, XE::int32 * result = NULL ) = 0;

	virtual void Destroy( OcclusionQueryHandle handle ) = 0;

public:
	virtual CommandListHandle CreateCommandList( CommandListType type ) = 0;

	virtual void Destory( CommandListHandle handle ) = 0;

public:
	virtual void SetViewRect( CommandListHandle cmd, XE::uint16 x, XE::uint16 y, XE::uint16 width, XE::uint16 height ) = 0;

	virtual void SetViewClear( CommandListHandle cmd, ClearType type, XE::uint32 rgba, XE::float32 depth, XE::uint8 stencil ) = 0;

	virtual void SetViewFrameBuffer( CommandListHandle cmd, FrameBufferHandle handle ) = 0;

	virtual void SetViewTransform( CommandListHandle cmd, const Mat4 & view, const Mat4 & proj ) = 0;

	virtual XE::uint16 SetViewScissor( CommandListHandle cmd, XE::uint16 x, XE::uint16 y, XE::uint16 width, XE::uint16 height ) = 0;

	virtual void SetTransform( CommandListHandle cmd, const Mat4 & trans ) = 0;

	virtual void SetCondition( CommandListHandle cmd, OcclusionQueryHandle handle, bool visible ) = 0;

	virtual void SetIndexBuffer( CommandListHandle cmd, IndexBufferHandle handle ) = 0;

	virtual void SetIndexBuffer( CommandListHandle cmd, IndexBufferHandle handle, XE::uint32 firstIndex, XE::uint32 numIndices ) = 0;

	virtual void SetIndexBuffer( CommandListHandle cmd, DynamicIndexBufferHandle handle ) = 0;

	virtual void SetIndexBuffer( CommandListHandle cmd, DynamicIndexBufferHandle handle, XE::uint32 firstIndex, XE::uint32 numIndices ) = 0;

	virtual void SetVertexBuffer( CommandListHandle cmd, XE::uint8 stream, VertexBufferHandle handle ) = 0;

	virtual void SetVertexBuffer( CommandListHandle cmd, XE::uint8 stream, VertexBufferHandle handle, XE::uint32 startVertex, XE::uint32 numVertices ) = 0;

	virtual void SetVertexBuffer( CommandListHandle cmd, XE::uint8 stream, DynamicVertexBufferHandle handle ) = 0;

	virtual void SetVertexBuffer( CommandListHandle cmd, XE::uint8 stream, DynamicVertexBufferHandle handle, XE::uint32 startVertex, XE::uint32 numVertices ) = 0;

	virtual void SetInstanceBuffer( CommandListHandle cmd, InstanceBufferHandle handle ) = 0;

	virtual void SetInstanceBuffer( CommandListHandle cmd, InstanceBufferHandle handle, XE::uint32 start, XE::uint32 num ) = 0;

	virtual void SetTexture( CommandListHandle cmd, XE::uint8 stage, UniformHandle sampler, TextureHandle handle, XE::uint32 flags ) = 0;

	virtual void Touch( CommandListHandle cmd ) = 0;

	virtual void Submit( CommandListHandle cmd, GraphicsPipelineStateHandle state, XE::uint32 depth, bool preserveState ) = 0;

	virtual void Submit( CommandListHandle cmd, GraphicsPipelineStateHandle state, OcclusionQueryHandle occlusionQuery, XE::uint32 depth, bool preserveState ) = 0;

	virtual void Submit( CommandListHandle cmd, GraphicsPipelineStateHandle state, IndirectBufferHandle indirectHandle, XE::uint16 start, XE::uint16 num, XE::uint32 depth, bool preserveState ) = 0;

	virtual void SetBuffer( CommandListHandle cmd, XE::uint8 stage, IndexBufferHandle handle, AccessType access ) = 0;

	virtual void SetBuffer( CommandListHandle cmd, XE::uint8 stage, VertexBufferHandle handle, AccessType access ) = 0;

	virtual void SetBuffer( CommandListHandle cmd, XE::uint8 stage, DynamicIndexBufferHandle handle, AccessType access ) = 0;

	virtual void SetBuffer( CommandListHandle cmd, XE::uint8 stage, DynamicVertexBufferHandle handle, AccessType access ) = 0;

	virtual void SetBuffer( CommandListHandle cmd, XE::uint8 stage, IndirectBufferHandle handle, AccessType access ) = 0;

	virtual void SetBuffer( CommandListHandle cmd, XE::uint8 stage, InstanceBufferHandle handle, AccessType access ) = 0;

	virtual void SetImage( CommandListHandle cmd, XE::uint8 stage, TextureHandle handle, XE::uint8 mip, AccessType access, TextureFormat format ) = 0;

	virtual void Dispatch( CommandListHandle cmd, ComputePipelineStateHandle state, XE::uint32 numX, XE::uint32 numY, XE::uint32 numZ ) = 0;

	virtual void Dispatch( CommandListHandle cmd, ComputePipelineStateHandle state, IndirectBufferHandle indirectHandle, XE::uint16 start, XE::uint16 num ) = 0;

	virtual void Discard( CommandListHandle cmd ) = 0;

	virtual void Blit( CommandListHandle cmd, TextureHandle dst, XE::uint16 dstX, XE::uint16 dstY, TextureHandle src, XE::uint16 srcX, XE::uint16 srcY, XE::uint16 width, XE::uint16 height ) = 0;

	virtual void Blit( CommandListHandle cmd, TextureHandle dst, XE::uint8 dstMip, XE::uint16 dstX, XE::uint16 dstY, XE::uint16 dstZ, TextureHandle src, XE::uint8 srcMip, XE::uint16 srcX, XE::uint16 srcY, XE::uint16 srcZ, XE::uint16 width, XE::uint16 height, XE::uint16 depth ) = 0;

};

END_XE_NAMESPACE

#endif // IRENDERCONTEXT_H__2A432E01_836A_457E_A061_58BD721E11C7
