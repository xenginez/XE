#include "Encoder.h"

#include "Structs.h"

struct XE::Encoder::Private
{
	bool _Discard;
	XE::Frame * _Frame;
	XE::RenderBind _Bind;
	XE::RenderDraw _Draw;
	XE::RenderCompute _Compute;
};

void XE::Encoder::SetFrame( Frame * val )
{
	_p->_Frame = val;
}

XE::Encoder::Encoder()
{

}

XE::Encoder::~Encoder()
{

}

void XE::Encoder::SetMarker( const std::string & marker )
{

}

void XE::Encoder::SetState( XE::Flags<XE::StateFlag> flags /*= XE::StateFlag::DEFAULT */ )
{

}

void XE::Encoder::SetCondition( OcclusionQueryHandle handle, bool visible )
{

}

void XE::Encoder::SetStencil( XE::Flags<XE::StencilFlag> front, XE::Flags<XE::StencilFlag> back /*= XE::StencilFlag::NONE */ )
{

}

void XE::Encoder::SetScissor( const XE::Rect & scissor )
{

}

void XE::Encoder::SetTransform( const XE::Mat4 & transform )
{

}

void XE::Encoder::SetUniform( UniformHandle handle, const XE::Variant & value )
{

}

void XE::Encoder::SetIndexBuffer( IndexBufferHandle handle )
{

}

void XE::Encoder::SetIndexBuffer( IndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{

}

void XE::Encoder::SetIndexBuffer( DynamicIndexBufferHandle handle )
{

}

void XE::Encoder::SetIndexBuffer( DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{

}

void XE::Encoder::SetIndexBuffer( TransientIndexBufferHandle handle )
{

}

void XE::Encoder::SetIndexBuffer( TransientIndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{

}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, VertexBufferHandle handle )
{

}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, VertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{

}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, DynamicVertexBufferHandle handle )
{

}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{

}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, TransientVertexBufferHandle handle )
{

}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, TransientVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{

}

void XE::Encoder::SetVertexCount( XE::uint32 num )
{

}

void XE::Encoder::SetInstanceDataBuffer( VertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{

}

void XE::Encoder::SetInstanceDataBuffer( DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{

}

void XE::Encoder::SetInstanceCount( XE::uint32 num )
{

}

void XE::Encoder::SetTexture( XE::uint8 stage, UniformHandle sampler, TextureHandle handle, SamplerWrap U, SamplerWrap V, SamplerWrap W, SamplerMode MIN, SamplerMode MAG, SamplerMode MIP )
{

}

void XE::Encoder::Touch( ViewHandle handle )
{

}

void XE::Encoder::Submit( ViewHandle handle, ProgramHandle program, XE::uint32 depth /*= 0*/, bool preserve_state /*= false */ )
{

}

void XE::Encoder::Submit( ViewHandle handle, ProgramHandle program, OcclusionQueryHandle query, XE::uint32 depth /*= 0*/, bool preserve_state /*= false */ )
{

}

void XE::Encoder::Submit( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 depth /*= 0*/, bool preserve_state /*= false */ )
{

}

void XE::Encoder::SetBuffer( XE::uint8 stage, IndexBufferHandle handle, Access access )
{

}

void XE::Encoder::SetBuffer( XE::uint8 stage, DynamicIndexBufferHandle handle, Access access )
{

}

void XE::Encoder::SetBuffer( XE::uint8 stage, VertexBufferHandle handle, Access access )
{

}

void XE::Encoder::SetBuffer( XE::uint8 stage, DynamicVertexBufferHandle handle, Access access )
{

}

void XE::Encoder::SetBuffer( XE::uint8 stage, IndirectBufferHandle handle, Access access )
{

}

void XE::Encoder::SetImage( XE::uint8 stage, IndirectBufferHandle handle, XE::uint8 mip, Access access, TextureFormat format /*= TextureFormat::COUNT */ )
{

}

void XE::Encoder::Dispatch( ViewHandle handle, ProgramHandle program, XE::uint32 numX /*= 1*/, XE::uint32 numY /*= 1*/, XE::uint32 numZ /*= 1 */ )
{

}

void XE::Encoder::Dispatch( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num )
{

}

void XE::Encoder::Discard()
{

}

void XE::Encoder::Blit( ViewHandle handle, TextureHandle dst, XE::uint32 dst_x, XE::uint32 dst_y, TextureHandle src, XE::uint32 src_x, XE::uint32 src_y, XE::uint32 width, XE::uint32 height )
{

}

void XE::Encoder::Blit( ViewHandle handle, TextureHandle dst, XE::uint8 dst_mip, XE::uint32 dst_x, XE::uint32 dst_y, XE::uint32 dst_z, TextureHandle src, XE::uint8 src_mip, XE::uint32 src_x, XE::uint32 src_y, XE::uint32 src_z, XE::uint32 width, XE::uint32 height, XE::uint32 depth )
{

}
