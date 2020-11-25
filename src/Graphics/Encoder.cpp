#include "Encoder.h"

#include <mutex>

#include "Private.h"

XE::MemoryView CopyToFrame( XE::RenderFrame * frame, XE::MemoryView mem )
{
	std::unique_lock<std::mutex> lock( frame->TransientBufferMutex );

	auto pos = frame->TransientBuffers.WirtePos();
	frame->TransientBuffers.Wirte( mem );

	return XE::MemoryView( ( const char * )pos, mem.size() );
}

struct XE::Encoder::Private
{
	XE::RenderFrame * _Frame;
	XE::RenderBind _Bind;
	XE::RenderDraw _Draw;
	XE::RenderCompute _Compute;
	XE::Map<XE::String, XE::PUniform> _Uniforms;
};

XE::Encoder::Encoder()
	:_p( new Private )
{

}

XE::Encoder::~Encoder()
{
	delete _p;
}

void XE::Encoder::SetFrame( RenderFrame* val )
{
	_p->_Frame = val;
}

void XE::Encoder::SetState( XE::Flags<XE::StateFlags> flags /*= XE::StateFlag::DEFAULT */ )
{
	_p->_Draw.StateFlags = flags;
}

void XE::Encoder::SetCondition( OcclusionQueryHandle handle, bool visible )
{
	_p->_Draw.OcclusionQuery = handle;
}

void XE::Encoder::SetStencil( XE::Flags<XE::StencilFlags> front, XE::Flags<XE::StencilFlags> back /*= XE::StencilFlag::NONE */ )
{
	_p->_Draw.FrontStencilFlags = front;
	_p->_Draw.BackStencilFlags = back;
}

void XE::Encoder::SetScissor( const XE::Rectf & scissor )
{
	_p->_Draw.Scissor = scissor;
}

void XE::Encoder::SetTransform( XE::BasicMemoryView<XE::Mat4f>  transform )
{
	XE::uint32 start = 0;

	while( !_p->_Frame->TransformsSize.compare_exchange_weak( start, start + transform.size() ) );

	std::memcpy( &_p->_Frame->Transforms[start], transform.data(), transform.size() );

	_p->_Draw.StartMatrix = start;
	_p->_Draw.NumMatrices = transform.size();
}

void XE::Encoder::SetIndexBuffer( IndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.Indices.Handle = handle.GetValue();
	_p->_Draw.Indices.StartIndex = first;
	_p->_Draw.Indices.NumIndices = num;
	_p->_Draw.IsDynamicIndices = false;
}

void XE::Encoder::SetIndexBuffer( DynamicIndexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.Indices.Handle = handle.GetValue();
	_p->_Draw.Indices.StartIndex = first;
	_p->_Draw.Indices.NumIndices = num;
	_p->_Draw.IsDynamicIndices = true;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 stream, VertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.Vertices[stream].Handle = handle.GetValue();
	_p->_Draw.Vertices[stream].StartVertex = first;
	_p->_Draw.Vertices[stream].NumVertices = num;
	_p->_Draw.IsDynamicVertices[stream] = false;
}

void XE::Encoder::SetVertexBuffer( XE::uint8 stream, DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.Vertices[stream].Handle = handle.GetValue();
	_p->_Draw.Vertices[stream].StartVertex = first;
	_p->_Draw.Vertices[stream].NumVertices = num;
	_p->_Draw.IsDynamicVertices[stream] = true;
}

void XE::Encoder::SetInstanceDataBuffer( VertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.InstanceDataBuffer = handle;
	_p->_Draw.InstanceDataOffset = first;
	_p->_Draw.NumInstances = num;
	_p->_Draw.IsDynamicInstanceDataBuffer = false;
}

void XE::Encoder::SetInstanceDataBuffer( DynamicVertexBufferHandle handle, XE::uint32 first, XE::uint32 num )
{
	_p->_Draw.InstanceDataBuffer = handle.GetValue();
	_p->_Draw.InstanceDataOffset = first;
	_p->_Draw.NumInstances = num;
	_p->_Draw.IsDynamicInstanceDataBuffer = true;
}

void XE::Encoder::SetBind( XE::uint8 stage, IndexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::INDEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetBind( XE::uint8 stage, VertexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::VERTEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetBind( XE::uint8 stage, DynamicIndexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::DYNAMICINDEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetBind( XE::uint8 stage, DynamicVertexBufferHandle handle, Access access )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::DYNAMICVERTEXBUFFER;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = 0;
}

void XE::Encoder::SetBind( XE::uint8 stage, const XE::String & uniformname, TextureHandle handle, XE::Flags<XE::SamplerFlags> flags )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::TEXTURE;
	_p->_Bind.Binds[stage].SamplerFlags = flags.GetValue();

	_p->_Uniforms[uniformname] = { uniformname, 1, ( XE::uint32 )stage, XE::UniformType::SAMPLER };
}

void XE::Encoder::SetBind( XE::uint8 stage, TextureHandle handle, XE::uint8 mip, Access access, TextureFormat format /*= TextureFormat::COUNT */ )
{
	_p->_Bind.Binds[stage].Handle = handle.GetValue();
	_p->_Bind.Binds[stage].Type = RenderBind::BindType::IMAGE;
	_p->_Bind.Binds[stage].Format = format;
	_p->_Bind.Binds[stage].Access = access;
	_p->_Bind.Binds[stage].Mip = mip;
}

void XE::Encoder::Discard()
{
	_p->_Bind.Reset();
	_p->_Draw.Reset();
	_p->_Compute.Reset();
}

void XE::Encoder::Submit( ViewHandle handle, RenderGroup group, ProgramHandle program, OcclusionQueryHandle query /*= OcclusionQueryHandle::Invalid*/, XE::uint32 depth /*= 0*/ )
{
	if( !_p->_Draw.Indices.Handle )
	{
		Discard();

		return;
	}

	if( query )
	{
		_p->_Draw.OcclusionQuery = query;
	}
	
	if( program )
	{
		_p->_Draw.Program = program;
	}

	{
		int i = 0;
		for( auto it = _p->_Uniforms.begin(); it != _p->_Uniforms.end(); ++it, ++i )
		{
			_p->_Draw.Uniforms[i] = std::move( it->second );
		}
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
	std::memcpy( item.Data, &_p->_Draw, sizeof( XE::RenderDraw ) );
	
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
		int i = 0;
		for( auto it = _p->_Uniforms.begin(); it != _p->_Uniforms.end(); ++it, ++i )
		{
			_p->_Draw.Uniforms[i] = std::move( it->second );
		}
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
	std::memcpy( item.Data, &_p->_Compute, sizeof( XE::RenderCompute ) );

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
	XE::RenderBlit blit;

	blit.Src = src;
	blit.SrcX = src_x;
	blit.SrcY = src_y;
	blit.SrcZ = src_z;
	blit.SrcMip = src_mip;

	blit.Dst = dst;
	blit.DstX = dst_x;
	blit.DstY = dst_y;
	blit.DstZ = dst_z;
	blit.DstMip = dst_mip;

	blit.Width = width;
	blit.Height = height;
	blit.Depth = depth;

	blit.Handle = handle;

	XE::uint32 key = XE::uint32( handle.GetValue() << 24 );

	auto index = _p->_Frame->RenderItemSize++;

	_p->_Frame->RenderItemKeys[index] = key;

	auto & item = _p->_Frame->RenderItems[index];
	item.Type = RenderItem::ItemType::BLIT;
	std::memcpy( item.Data, &blit, sizeof( XE::RenderBlit ) );

	Discard();
}

void XE::Encoder::SetUniform( const XE::String & name, XE::int32 data )
{
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.i = data;
	uniform.Type = UniformType::INT;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::uint32 data )
{
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.u = data;
	uniform.Type = UniformType::UINT;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::float32 data )
{
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.f = data;
	uniform.Type = UniformType::FLOAT;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, const XE::Vec2f & data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )&data, sizeof( data ) } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.p = view.data();
	uniform.Type = UniformType::VEC2f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, const XE::Vec3f & data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )&data, sizeof( data ) } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.p = view.data();
	uniform.Type = UniformType::VEC3f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, const XE::Vec4f & data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )&data, sizeof( data ) } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.p = view.data();
	uniform.Type = UniformType::VEC4f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, const XE::Mat3f & data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )&data, sizeof( data ) } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.p = view.data();
	uniform.Type = UniformType::MAT3f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, const XE::Mat4f & data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )&data, sizeof( data ) } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = 1;
	uniform.p = view.data();
	uniform.Type = UniformType::MAT4f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::int32> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::int32 ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::INT;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::uint32> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::uint32 ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::UINT;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::float32> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::float32 ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::FLOAT;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::Vec2f> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::Vec2f ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::VEC2f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::Vec3f> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::Vec3f ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::VEC3f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::Vec4f> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::Vec4f ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::VEC4f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::Mat3f> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::Mat3f ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::MAT3f;
	_p->_Uniforms[name] = std::move( uniform );
}

void XE::Encoder::SetUniform( const XE::String & name, XE::BasicMemoryView<XE::Mat4f> data )
{
	auto view = CopyToFrame( _p->_Frame, { ( const char * )data.data(), sizeof( XE::Mat4f ) * data.size() } );
	XE::PUniform uniform;
	uniform.Name = name;
	uniform.Size = data.size();
	uniform.p = view.data();
	uniform.Type = UniformType::MAT4f;
	_p->_Uniforms[name] = std::move( uniform );
}
