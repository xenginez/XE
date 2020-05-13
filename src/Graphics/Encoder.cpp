#include "Encoder.h"

#include "Structs.h"

struct XE::Encoder::Private
{
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

void XE::Encoder::SetState( XE::Flags<XE::StateFlag> flags /*= XE::StateFlag::DEFAULT */ )
{
	_p->_Draw.StateFlags = flags;
}

void XE::Encoder::SetCondition( OcclusionQueryHandle handle, bool visible )
{
	_p->_Draw.OcclusionQuery = handle;
}

void XE::Encoder::SetStencil( XE::Flags<XE::StencilFlag> front, XE::Flags<XE::StencilFlag> back /*= XE::StencilFlag::NONE */ )
{
	_p->_Draw.FrontStencilFlags = front;
	_p->_Draw.BackStencilFlags = back;
}

void XE::Encoder::SetScissor( const XE::Rect & scissor )
{
	_p->_Draw.Scissor = scissor;
}

void XE::Encoder::SetTransform( XE::basic_memory_view<XE::Mat4> transform )
{
	XE::uint64 start = _p->_Frame->TransformsSize;
	while( !_p->_Frame->TransformsSize.compare_exchange_weak( start, start + transform.size() ) )
	{
		start = _p->_Frame->TransformsSize;
	}

	std::memcpy( &_p->_Frame->Transforms[start], transform.data(), transform.size() * sizeof( XE::Mat4 ) );

	_p->_Draw.StartMatrix = start;
	_p->_Draw.NumMatrices = transform.size();
}

void XE::Encoder::SetIndexBuffer( IndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.IndexBuffer = handle;
	_p->_Draw.StartIndex = first;
	_p->_Draw.NumIndices = num;
}

void XE::Encoder::SetIndexBuffer( DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.DynamicIndexBuffer = handle;
	_p->_Draw.StartIndex = first;
	_p->_Draw.NumIndices = num;
}

void XE::Encoder::SetIndexBuffer( TransientIndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.TransientIndexBuffer = handle;
	_p->_Draw.StartIndex = first;
	_p->_Draw.NumIndices = num;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, VertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{
	_p->_Draw.Vertices[steam].VertexBuffer = handle;
	_p->_Draw.Vertices[steam].StartVertices = first;
	_p->_Draw.Vertices[steam].NumVertices = num;
	_p->_Draw.Vertices[steam].LayoutHandle = layout;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{
	_p->_Draw.Vertices[steam].DynamicVertexBuffer = handle;
	_p->_Draw.Vertices[steam].StartVertices = first;
	_p->_Draw.Vertices[steam].NumVertices = num;
	_p->_Draw.Vertices[steam].LayoutHandle = layout;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 steam, TransientVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{
	_p->_Draw.Vertices[steam].TransientVertexBuffer = handle;
	_p->_Draw.Vertices[steam].StartVertices = first;
	_p->_Draw.Vertices[steam].NumVertices = num;
	_p->_Draw.Vertices[steam].LayoutHandle = layout;
}

void XE::Encoder::SetInstanceDataBuffer( VertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.InstanceDataBuffer = handle;
	_p->_Draw.InstanceDataOffset = first;
	_p->_Draw.NumInstances = num;
}

void XE::Encoder::SetInstanceDataBuffer( DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.DynamicInstanceDataBuffer = handle;
	_p->_Draw.InstanceDataOffset = first;
	_p->_Draw.NumInstances = num;
}

void XE::Encoder::SetTexture( XE::uint8 stage, UniformHandle sampler, TextureHandle handle, bool sampler_shared /*= false */ )
{
	_p->_Bind.Binds[stage].Texture = handle;
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::TEXTURE;
	_p->_Bind.Binds[stage].SamplerFlags = sampler_shared;
}

void XE::Encoder::SetBuffer( XE::uint8 stage, IndexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Index = handle;
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::INDEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetBuffer( XE::uint8 stage, VertexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Vertex = handle;
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::VERTEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetImage( XE::uint8 stage, TextureHandle handle, XE::uint8 mip, Access access, TextureFormat format /*= TextureFormat::COUNT */ )
{
	_p->_Bind.Binds[stage].Texture = handle;
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::IMAGE;
	_p->_Bind.Binds[stage].Format = format;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = mip;
}

void XE::Encoder::Discard()
{
	_p->_Bind;
	_p->_Draw = {};
	_p->_Compute = {};
}

void XE::Encoder::Touch( ViewHandle handle )
{
	Submit( handle, ProgramHandle::Invalid, OcclusionQueryHandle::Invalid );
}

void XE::Encoder::Submit( ViewHandle handle, ProgramHandle program, OcclusionQueryHandle query, XE::uint32 depth /*= 0*/, bool preserve_state /*= false */ )
{
	
}

void XE::Encoder::Submit( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num, XE::uint32 depth /*= 0*/, bool preserve_state /*= false */ )
{
	_p->_Draw.StartIndirect = first;
	_p->_Draw.NumIndirect = num;
	_p->_Draw.IndirectBuffer = indirect;

	Submit( handle, program, XE::OcclusionQueryHandle::Invalid, depth, preserve_state );
}

void XE::Encoder::Dispatch( ViewHandle handle, ProgramHandle program, XE::uint32 numX /*= 1*/, XE::uint32 numY /*= 1*/, XE::uint32 numZ /*= 1 */ )
{

}

void XE::Encoder::Dispatch( ViewHandle handle, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num )
{
	_p->_Compute.IndirectBuffer = indirect;
	_p->_Compute.StartIndirect = first;
	_p->_Compute.NumIndirect = num;

	Dispatch( handle, program );
}

void XE::Encoder::Blit( ViewHandle handle, TextureHandle dst, XE::uint8 dst_mip, XE::uint32 dst_x, XE::uint32 dst_y, XE::uint32 dst_z, TextureHandle src, XE::uint8 src_mip, XE::uint32 src_x, XE::uint32 src_y, XE::uint32 src_z, XE::uint32 width, XE::uint32 height, XE::uint32 depth )
{

}
