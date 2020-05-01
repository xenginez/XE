/*!
 * \file	Encoder.h
 *
 * \author	ZhengYuanQing
 * \date	2020/04/04
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ENCODER_H__9F5CEFA2_B1B7_4F05_AE47_03B5764B16F6
#define ENCODER_H__9F5CEFA2_B1B7_4F05_AE47_03B5764B16F6

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Encoder
{
private:
	struct Private;

public:
	Encoder();

	~Encoder();

public:
	void SetMarker( const std::string & marker );

	void SetState( XE::Flags<XE::StateFlag> flags = XE::StateFlag::DEFAULT );

	void SetCondition( OcclusionQueryHandle handle, bool visible );

	void SetStencil( XE::Flags<XE::StencilFlag> front, XE::Flags<XE::StencilFlag> back = XE::StencilFlag::NONE );

	void SetScissor( const XE::Rect & scissor );

	void SetTransform( const XE::Mat4 & transform );

	void SetUniform( UniformHandle handle, const XE::Variant & value );

	void SetIndexBuffer( IndexBufferHandle handle );

	void SetIndexBuffer( IndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetIndexBuffer( DynamicIndexBufferHandle handle );

	void SetIndexBuffer( DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetIndexBuffer( TransientIndexBufferHandle handle );

	void SetIndexBuffer( TransientIndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetVertexBuffer( XE::uint8 steam, VertexBufferHandle handle );

	void SetVertexBuffer( XE::uint8 steam, VertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexBuffer( XE::uint8 steam, DynamicVertexBufferHandle handle );

	void SetVertexBuffer( XE::uint8 steam, DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexBuffer( XE::uint8 steam, TransientVertexBufferHandle handle );

	void SetVertexBuffer( XE::uint8 steam, TransientVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexCount( XE::uint32 num );

	void SetInstanceDataBuffer( VertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetInstanceDataBuffer( DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetInstanceDataBuffer( const XE::Array<InstanceDataBuffer> & buffers, XE::uint32 first, XE::uint32 num );

	void SetInstanceCount( XE::uint32 num );

	void SetTexture( XE::uint8 stage, UniformHandle sampler, TextureHandle handle,
					 SamplerWrap U, SamplerWrap V, SamplerWrap W,
					 SamplerMode MIN, SamplerMode MAG, SamplerMode MIP );

public:
	void Touch( ViewHandle handle );

	void Submit( ViewHandle handle, ProgramHandle program, XE::uint32 depth = 0, bool preserve_state = false );

	void Submit( ViewHandle handle, ProgramHandle program, OcclusionQueryHandle query, XE::uint32 depth = 0, bool preserve_state = false );

	void Submit( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 depth = 0, bool preserve_state = false );

	void SetBuffer( XE::uint8 stage, IndexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, DynamicIndexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, VertexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, DynamicVertexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, IndirectBufferHandle handle, Access access );

	void SetImage( XE::uint8 stage, IndirectBufferHandle handle, XE::uint8 mip, Access access, TextureFormat format = TextureFormat::COUNT );

	void Dispatch( ViewHandle handle, ProgramHandle program, XE::uint32 numX = 1, XE::uint32 numY = 1, XE::uint32 numZ = 1 );

	void Dispatch( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num );

	void Discard();

	void Blit( ViewHandle handle,
			   TextureHandle dst, XE::uint32 dst_x, XE::uint32 dst_y,
			   TextureHandle src, XE::uint32 src_x, XE::uint32 src_y,
			   XE::uint32 width, XE::uint32 height );

	void Blit( ViewHandle handle,
			   TextureHandle dst, XE::uint8 dst_mip, XE::uint32 dst_x, XE::uint32 dst_y, XE::uint32 dst_z,
			   TextureHandle src, XE::uint8 src_mip, XE::uint32 src_x, XE::uint32 src_y, XE::uint32 src_z,
			   XE::uint32 width, XE::uint32 height, XE::uint32 depth );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // ENCODER_H__9F5CEFA2_B1B7_4F05_AE47_03B5764B16F6
