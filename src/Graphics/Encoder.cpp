#include "Encoder.h"

#include "Structs.h"

XE::memory_view CopyToFrame( XE::Frame * frame, XE::memory_view mem )
{
	std::unique_lock<std::mutex> lock( frame->TransientBufferMutex );

	auto pos = frame->TransientBuffer.WirtePos();
	frame->TransientBuffer.Wirte( mem );

	return XE::memory_view( ( const char * )pos, mem.size() );
}

struct XE::Encoder::Private
{
	XE::Frame * _Frame;
	XE::RenderBind _Bind;
	XE::RenderDraw _Draw;
	XE::RenderCompute _Compute;
	XE::Map<UniformHandle, XE::memory_view> _Uniforms;
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

	while( !_p->_Frame->TransformsSize.compare_exchange_weak( start, start + transform.size() ) );

	std::memcpy( &_p->_Frame->Transforms[start], transform.data(), transform.size() * sizeof( XE::Mat4 ) );

	_p->_Draw.StartMatrix = start;
	_p->_Draw.NumMatrices = transform.size();
}

void XE::Encoder::SetUniform( UniformHandle handle, XE::memory_view mem )
{
	_p->_Uniforms[handle] = CopyToFrame( _p->_Frame, mem );
}

void XE::Encoder::SetIndexBuffer( IndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.Indices.Type = IndexBuffer::HandleType::INDEX;
	_p->_Draw.Indices.Handle = handle.GetValue();
	_p->_Draw.Indices.StartIndex = first;
	_p->_Draw.Indices.NumIndices = num;
}

void XE::Encoder::SetIndexBuffer( DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.Indices.Type = IndexBuffer::HandleType::DYNAMIC;
	_p->_Draw.Indices.Handle = handle.GetValue();
	_p->_Draw.Indices.StartIndex = first;
	_p->_Draw.Indices.NumIndices = num;
}

void XE::Encoder::SetIndexBuffer( TransientIndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.Indices.Type = IndexBuffer::HandleType::TRANSIENT;
	_p->_Draw.Indices.Handle = handle.GetValue();
	_p->_Draw.Indices.StartIndex = first;
	_p->_Draw.Indices.NumIndices = num;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 stream, VertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{
	_p->_Draw.Vertices[stream].Type = VertexBuffer::HandleType::VERTEX;
	_p->_Draw.Vertices[stream].Handle = handle.GetValue();
	_p->_Draw.Vertices[stream].LayoutHandle = layout;
	_p->_Draw.Vertices[stream].StartVertex = first;
	_p->_Draw.Vertices[stream].NumVertices = num;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 stream, DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{
	_p->_Draw.Vertices[stream].Type = VertexBuffer::HandleType::DYNAMIC;
	_p->_Draw.Vertices[stream].Handle = handle.GetValue();
	_p->_Draw.Vertices[stream].LayoutHandle = layout;
	_p->_Draw.Vertices[stream].StartVertex = first;
	_p->_Draw.Vertices[stream].NumVertices = num;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 stream, TransientVertexBufferHandle handle, XE::uint32 first, XE::uint32 num, VertexLayoutHandle layout /*= VertexLayoutHandle::Invalid */ )
{
	_p->_Draw.Vertices[stream].Type = VertexBuffer::HandleType::TRANSIENT;
	_p->_Draw.Vertices[stream].Handle = handle.GetValue();
	_p->_Draw.Vertices[stream].LayoutHandle = layout;
	_p->_Draw.Vertices[stream].StartVertex = first;
	_p->_Draw.Vertices[stream].NumVertices = num;
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
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::TEXTURE;
	_p->_Bind.Binds[stage].SamplerFlags = sampler_shared;
}

void XE::Encoder::SetBuffer( XE::uint8 stage, IndexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::INDEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetBuffer( XE::uint8 stage, VertexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::VERTEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetImage( XE::uint8 stage, TextureHandle handle, XE::uint8 mip, Access access, TextureFormat format /*= TextureFormat::COUNT */ )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
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

void XE::Encoder::Submit( ViewHandle handle, RenderGroup group, ProgramHandle program, OcclusionQueryHandle query /*= OcclusionQueryHandle::Invalid*/, XE::uint32 depth /*= 0*/ )
{
	if( _p->_Draw.Indices.Handle == IndexBufferHandle::Invalid.GetValue() )
	{
		Discard();

		return;
	}

	if( query )
	{
		_p->_Draw.StateFlags |= StateFlag::INTERNAL_OCCLUSION_QUERY;
		_p->_Draw.OcclusionQuery = query;
	}
	
	{
		std::unique_lock<std::mutex> lock( _p->_Frame->UniformBufferMutex );

		_p->_Draw.UniformBegin = _p->_Frame->UniformBuffer.WirtePos();
		for( const auto & it : _p->_Uniforms )
		{
			_p->_Frame->UniformBuffer.Wirte( it.first );
			_p->_Frame->UniformBuffer.Wirte( it.second.size() );
			_p->_Frame->UniformBuffer.Wirte( it.second.data(), it.second.size() );
		}
		_p->_Draw.UniformEnd = _p->_Frame->UniformBuffer.WirtePos();
	}
	
	XE::uint64 key = 0;
	{
		SortKey sort_key;
		sort_key.SetView( handle.GetValue() );
		sort_key.SetGroup( ( XE::uint8 )group );
		sort_key.SetDepth( group != RenderGroup::TRANSPARENT ? depth : std::numeric_limits<XE::uint32>::max() - depth );
		if( program )
		{
			sort_key.SetProgram( program.GetValue() );
		}

		key = sort_key.GetKey();
	}

	auto index = _p->_Frame->RenderItemSize++;

	_p->_Frame->RenderItemKeys[index] = key;

	auto & item = _p->_Frame->RenderItems[index];
	item.Type = RenderItem::ItemType::DRAW;
	item.Draw = std::move( _p->_Draw );

	_p->_Frame->RenderBinds[index] = std::move( _p->_Bind );

	Discard();
}

void XE::Encoder::Submit( ViewHandle handle, RenderGroup group, ProgramHandle program, IndirectBufferHandle indirect, XE::uint32 first, XE::uint32 num, XE::uint32 depth /*= 0*/ )
{
	_p->_Draw.StartIndirect = first;
	_p->_Draw.NumIndirect = num;
	_p->_Draw.IndirectBuffer = indirect;

	Submit( handle, group, program, XE::OcclusionQueryHandle::Invalid, depth );
}

void XE::Encoder::Dispatch( ViewHandle handle, ProgramHandle program, XE::uint32 numX /*= 1*/, XE::uint32 numY /*= 1*/, XE::uint32 numZ /*= 1 */ )
{
	{
		std::unique_lock<std::mutex> lock( _p->_Frame->UniformBufferMutex );

		_p->_Compute.UniformBegin = _p->_Frame->UniformBuffer.WirtePos();
		for( const auto & it : _p->_Uniforms )
		{
			_p->_Frame->UniformBuffer.Wirte( it.first );
			_p->_Frame->UniformBuffer.Wirte( it.second.size() );
			_p->_Frame->UniformBuffer.Wirte( it.second.data(), it.second.size() );
		}
		_p->_Compute.UniformEnd = _p->_Frame->UniformBuffer.WirtePos();
	}

	_p->_Compute.StartMatrix = _p->_Draw.StartMatrix;
	_p->_Compute.NumMatrices = _p->_Draw.NumMatrices;
	_p->_Compute.NumX = std::max( numX, 1u );
	_p->_Compute.NumY = std::max( numY, 1u );
	_p->_Compute.NumZ = std::max( numZ, 1u );

	XE::uint64 key = 0;
	{
		SortKey sort_key;
		sort_key.SetView( handle.GetValue() );
		sort_key.SetGroup( SortKey::MAX_GROUP );
		sort_key.SetDepth( SortKey::MAX_DEPTH );
		if( program )
		{
			sort_key.SetProgram( program.GetValue() );
		}

		key = sort_key.GetKey();
	}

	auto index = _p->_Frame->RenderItemSize++;

	_p->_Frame->RenderItemKeys[index] = key;

	auto & item = _p->_Frame->RenderItems[index];
	item.Type = RenderItem::ItemType::COMPUTE;
	item.Compute = std::move( _p->_Compute );

	_p->_Frame->RenderBinds[index] = std::move( _p->_Bind );

	Discard();
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
