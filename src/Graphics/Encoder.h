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
	void SetState( XE::Flags<XE::StateFlags> flags = XE::StateFlags::DEFAULT );

	void SetCondition( XE::OcclusionQueryHandle handle, bool visible );

	void SetStencil( XE::Flags<XE::StencilFlags> front, XE::Flags<XE::StencilFlags> back = XE::StencilFlags::NONE );

	void SetScissor( const XE::Rectf & scissor );

	void SetTransform( XE::BasicMemoryView<XE::Mat4f> transform );

	void SetUniform( const XE::String & name, XE::int32 data );

	void SetUniform( const XE::String & name, XE::uint32 data );

	void SetUniform( const XE::String & name, XE::float32 data );

	void SetUniform( const XE::String & name, const XE::Vec2f & data );

	void SetUniform( const XE::String & name, const XE::Vec3f & data );

	void SetUniform( const XE::String & name, const XE::Vec4f & data );

	void SetUniform( const XE::String & name, const XE::Mat3f & data );

	void SetUniform( const XE::String & name, const XE::Mat4f & data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView<XE::int32> data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView <XE::uint32> data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView <XE::float32> data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView <XE::Vec2f> data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView <XE::Vec3f> data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView <XE::Vec4f> data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView <XE::Mat3f> data );

	void SetUniform( const XE::String & name, XE::BasicMemoryView <XE::Mat4f> data );

	void SetUniform( const XE::String & name, XE::TextureHandle data, XE::Flags<XE::SamplerFlags> flags );

	void SetIndexBuffer( XE::IndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetIndexBuffer( XE::DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetVertexBuffer( XE::uint8 stream, XE::VertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetVertexBuffer( XE::uint8 stream, XE::DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetInstanceDataBuffer( XE::VertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetInstanceDataBuffer( XE::DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num );

	void SetBuffer( XE::uint8 stage, XE::IndexBufferHandle handle, XE::Access access );

	void SetBuffer( XE::uint8 stage, XE::VertexBufferHandle handle, XE::Access access );

	void SetImage( XE::uint8 stage, XE::TextureHandle handle, XE::uint8 mip, XE::Access access, XE::TextureFormat format = XE::TextureFormat::RGBA8 );

public:
	void Discard();

	void Submit( XE::ViewHandle handle, XE::RenderGroup group, XE::ProgramHandle program, XE::OcclusionQueryHandle query = XE::OcclusionQueryHandle::Invalid, XE::uint32 depth = 0 );

	void Submit( XE::ViewHandle handle, XE::RenderGroup group, XE::ProgramHandle program, XE::IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num, XE::uint32 depth = 0 );

	void Dispatch( XE::ViewHandle handle, XE::ProgramHandle program, XE::uint32 numX = 1, XE::uint32 numY = 1, XE::uint32 numZ = 1 );

	void Dispatch( XE::ViewHandle handle, XE::ProgramHandle program, XE::IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num );

public:
	void Blit( XE::ViewHandle handle,
			   XE::TextureHandle dst, XE::uint8 dst_mip, XE::uint32 dst_x, XE::uint32 dst_y, XE::uint32 dst_z,
			   XE::TextureHandle src, XE::uint8 src_mip, XE::uint32 src_x, XE::uint32 src_y, XE::uint32 src_z,
			   XE::uint32 width, XE::uint32 height, XE::uint32 depth );

private:
	void SetFrame( RenderFrame * val );

private:
	Private * _p;
};

END_XE_NAMESPACE

#endif // ENCODER_H__9F5CEFA2_B1B7_4F05_AE47_03B5764B16F6
