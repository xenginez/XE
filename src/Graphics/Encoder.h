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

class XE_API Encoder : public XE::NonCopyable
{
	friend class RendererContext;

private:
	struct Private;

private:
	Encoder();

	~Encoder();

public:
	void SetState( XE::Flags<XE::StateFlag> flags = XE::StateFlag::DEFAULT );

	void SetCondition( OcclusionQueryHandle handle, bool visible );

	void SetStencil( XE::Flags<XE::StencilFlag> front, XE::Flags<XE::StencilFlag> back = XE::StencilFlag::NONE );

	void SetScissor( const XE::Rect & scissor );

	void SetTransform( XE::basic_memory_view<XE::Mat4> transform );

	void SetUniform( UniformHandle handle, XE::memory_view mem );

	void SetIndexBuffer( IndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetIndexBuffer( DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetIndexBuffer( TransientIndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetVertexBuffer( XE::uint8 stream, VertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexBuffer( XE::uint8 stream, DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetVertexBuffer( XE::uint8 stream, TransientVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout = VertexLayoutHandle::Invalid );

	void SetInstanceDataBuffer( VertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetInstanceDataBuffer( DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetTexture( XE::uint8 stage, UniformHandle sampler, TextureHandle handle, bool sampler_shared = false);

	void SetBuffer( XE::uint8 stage, IndexBufferHandle handle, Access access );

	void SetBuffer( XE::uint8 stage, VertexBufferHandle handle, Access access );

	void SetImage( XE::uint8 stage, TextureHandle handle, XE::uint8 mip, Access access, TextureFormat format = TextureFormat::COUNT );

public:
	void Discard();

	void Submit( ViewHandle handle, RenderGroup group, ProgramHandle program, OcclusionQueryHandle query = OcclusionQueryHandle::Invalid, XE::uint32 depth = 0 );

	void Submit( ViewHandle handle, RenderGroup group, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num, XE::uint32 depth = 0 );

	void Dispatch( ViewHandle handle, ProgramHandle program, XE::uint32 numX = 1, XE::uint32 numY = 1, XE::uint32 numZ = 1 );

	void Dispatch( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num );

	void Blit( ViewHandle handle,
			   TextureHandle dst, XE::uint8 dst_mip, XE::uint32 dst_x, XE::uint32 dst_y, XE::uint32 dst_z,
			   TextureHandle src, XE::uint8 src_mip, XE::uint32 src_x, XE::uint32 src_y, XE::uint32 src_z,
			   XE::uint32 width, XE::uint32 height, XE::uint32 depth );

private:
	void SetFrame( Frame * val );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // ENCODER_H__9F5CEFA2_B1B7_4F05_AE47_03B5764B16F6
