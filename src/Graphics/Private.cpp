#include "Private.h"

XE::SortKey::SortKey()
	:_Key( 0 )
{

}

XE::SortKey::SortKey( XE::uint64 val )
	: _Key( val )
{

}

XE::SortKey::SortKey( const SortKey & val )
	: _Key( val._Key )
{

}

XE::SortKey & XE::SortKey::operator=( const SortKey & val )
{
	_Key = val._Key;

	return *this;
}

bool XE::SortKey::operator<( const SortKey & val ) const
{
	return _Key < val._Key;
}

bool XE::SortKey::operator>( const SortKey & val ) const
{
	return _Key > val._Key;
}

bool XE::SortKey::operator<=( const SortKey & val ) const
{
	return _Key <= val._Key;
}

bool XE::SortKey::operator>=( const SortKey & val ) const
{
	return _Key >= val._Key;
}

bool XE::SortKey::operator==( const SortKey & val ) const
{
	return _Key == val._Key;
}

bool XE::SortKey::operator!=( const SortKey & val ) const
{
	return _Key != val._Key;
}

XE::uint8 XE::SortKey::GetView() const
{
	return _Key >> VIEW_LEFT_SHIFT;
}

void XE::SortKey::SetView( XE::uint8 val )
{
	val = std::min<XE::uint8>( val, MAX_VIEW );

	_Key |= ( std::uint64_t( val ) ) << VIEW_LEFT_SHIFT;
}

XE::uint8 XE::SortKey::GetGroup() const
{
	return ( _Key & ( MAX_GROUP << GROUP_LEFT_SHIFT ) ) >> GROUP_LEFT_SHIFT;
}

void XE::SortKey::SetGroup( XE::uint8 val )
{
	val = std::min<XE::uint8>( val, MAX_GROUP );

	_Key |= ( std::uint64_t( val ) ) << GROUP_LEFT_SHIFT;
}

XE::uint32 XE::SortKey::GetProgram() const
{
	return ( _Key & MAX_PROGRAM );
}

void XE::SortKey::SetProgram( XE::uint32 val )
{
	val = std::min<XE::uint32>( val, MAX_PROGRAM );

	_Key |= ( std::uint64_t( val ) );
}

XE::uint32 XE::SortKey::GetDepth() const
{
	return ( _Key & ( MAX_DEPTH << DEPTH_LEFT_SHIFT ) ) >> DEPTH_LEFT_SHIFT;
}

void XE::SortKey::SetDepth( XE::uint32 val )
{
	val = std::min<XE::uint32>( val, MAX_DEPTH );

	_Key |= ( std::uint64_t( val ) ) << DEPTH_LEFT_SHIFT;
}

XE::uint64 XE::SortKey::GetKey() const
{
	return _Key;
}

void XE::SortKey::SetKey( XE::uint64 val )
{
	_Key = val;
}

void XE::Frame::Reset()
{
	RenderItemSize = 0;
	RenderBlitSize = 0;
	RenderOcclusionSize = 0;

	PrevCmd.Reset();
	PostCmd.Reset();
	DestoryCmd.Reset();
	TransientBuffers.Reset();
	TransientIndexBufferHandleAlloc.Reset();
	TransientVertexBufferHandleAlloc.Reset();
}

XE::RenderItem::RenderItem()
{

}

XE::RenderItem::RenderItem( const RenderItem & val )
{
	Type = val.Type;

	if( Type == ItemType::DRAW )
	{
		Draw = val.Draw;
	}
	else
	{
		Compute = val.Compute;
	}
}

XE::RenderItem::~RenderItem()
{

}

XE::RenderItem & XE::RenderItem::operator=( const RenderItem & val )
{
	Type = val.Type;

	if( Type == ItemType::DRAW )
	{
		Draw = val.Draw;
	}
	else
	{
		Compute = val.Compute;
	}

	return *this;
}

XE::uint32 XE::RefCount::Inc()
{
	return ++Count;
}

XE::uint32 XE::RefCount::Dec()
{
	return --Count;
}

XE::Shader::Shader()
{

}

XE::Shader::Shader( const Shader & val )
{

}

XE::Shader & XE::Shader::operator=( const Shader & val )
{

	return *this;
}

XE::Texture::Texture()
{

}

XE::Texture::Texture( const Texture & val )
{

}

XE::Texture & XE::Texture::operator=( const Texture & val )
{

	return *this;
}

XE::Uniform::Uniform()
{

}

XE::Uniform::Uniform( const Uniform & val )
{

}

XE::Uniform & XE::Uniform::operator=( const Uniform & val )
{

	return *this;
}

XE::Program::Program()
{

}

XE::Program::Program( const Program & val )
{

}

XE::Program & XE::Program::operator=( const Program & val )
{

	return *this;
}

XE::FrameBuffer::FrameBuffer()
{

}

XE::FrameBuffer::FrameBuffer( const FrameBuffer & val )
{

}

XE::FrameBuffer & XE::FrameBuffer::operator=( const FrameBuffer & val )
{

	return *this;
}

XE::IndexBuffer::IndexBuffer()
{

}

XE::IndexBuffer::IndexBuffer( const IndexBuffer & val )
{

}

XE::IndexBuffer & XE::IndexBuffer::operator=( const IndexBuffer & val )
{

	return *this;
}

XE::VertexBuffer::VertexBuffer()
{

}

XE::VertexBuffer::VertexBuffer( const VertexBuffer & val )
{

}

XE::VertexBuffer & XE::VertexBuffer::operator=( const VertexBuffer & val )
{

	return *this;
}

XE::UniformBuffer::UniformBuffer()
{

}

XE::UniformBuffer::UniformBuffer( const UniformBuffer & val )
{

}

XE::UniformBuffer & XE::UniformBuffer::operator=( const UniformBuffer & val )
{

	return *this;
}

XE::InstanceDataBuffer::InstanceDataBuffer()
{

}

XE::InstanceDataBuffer::InstanceDataBuffer( const InstanceDataBuffer & val )
{

}

XE::InstanceDataBuffer & XE::InstanceDataBuffer::operator=( const InstanceDataBuffer & val )
{

	return *this;
}

XE::TransientIndexBuffer::TransientIndexBuffer()
{

}

XE::TransientIndexBuffer::TransientIndexBuffer( const TransientIndexBuffer & val )
{

}

XE::TransientIndexBuffer & XE::TransientIndexBuffer::operator=( const TransientIndexBuffer & val )
{

	return *this;
}

XE::TransientVertexBuffer::TransientVertexBuffer()
{

}

XE::TransientVertexBuffer::TransientVertexBuffer( const TransientVertexBuffer & val )
{

}

XE::TransientVertexBuffer & XE::TransientVertexBuffer::operator=( const TransientVertexBuffer & val )
{

	return *this;
}

XE::PredefinedUniform::PredefinedUniform()
{

}

XE::PredefinedUniform::PredefinedUniform( const PredefinedUniform & val )
{

}

XE::PredefinedUniform & XE::PredefinedUniform::operator=( const PredefinedUniform & val )
{

	return *this;
}

XE::View::View()
{

}

XE::View::View( const View & val )
{

}

XE::View & XE::View::operator=( const View & val )
{

	return *this;
}

XE::RenderDraw::RenderDraw()
{

}

XE::RenderDraw::RenderDraw( const RenderDraw & val )
	:Indices( val.Indices ),
	Rgba( val.Rgba ),
	UniformBegin( val.UniformBegin ),
	UniformEnd( val.UniformEnd ),
	StartMatrix( val.StartMatrix ),
	NumMatrices( val.NumMatrices ),
	InstanceDataOffset( val.InstanceDataOffset ),
	NumInstances( val.NumInstances ),
	StartIndirect( val.StartIndirect ),
	NumIndirect( val.NumIndirect ),
	Scissor( val.Scissor ),
	SubmitFlags( val.SubmitFlags ),
	StreamMask( val.StreamMask ),
	InstanceDataBuffer( val.InstanceDataBuffer ),
	DynamicInstanceDataBuffer( val.DynamicInstanceDataBuffer ),
	IndirectBuffer( val.IndirectBuffer ),
	OcclusionQuery( val.OcclusionQuery ),
	StateFlags( val.StateFlags ),
	FrontStencilFlags( val.FrontStencilFlags ),
	BackStencilFlags( val.BackStencilFlags )
{
	for( int i = 0; i < GFX_MAX_VERTEXS; ++i )
	{
		Vertices[i] = val.Vertices[i];
	}
}

XE::RenderDraw & XE::RenderDraw::operator=( const RenderDraw & val )
{
	Indices = val.Indices;
	Rgba = val.Rgba;
	UniformBegin = val.UniformBegin;
	UniformEnd = val.UniformEnd;
	StartMatrix = val.StartMatrix;
	NumMatrices = val.NumMatrices;
	InstanceDataOffset = val.InstanceDataOffset;
	NumInstances = val.NumInstances;
	StartIndirect = val.StartIndirect;
	NumIndirect = val.NumIndirect;
	Scissor = val.Scissor;
	SubmitFlags = val.SubmitFlags;
	StreamMask = val.StreamMask;
	InstanceDataBuffer = val.InstanceDataBuffer;
	DynamicInstanceDataBuffer = val.DynamicInstanceDataBuffer;
	IndirectBuffer = val.IndirectBuffer;
	OcclusionQuery = val.OcclusionQuery;
	StateFlags = val.StateFlags;
	FrontStencilFlags = val.FrontStencilFlags;
	BackStencilFlags = val.BackStencilFlags;

	for( int i = 0; i < GFX_MAX_VERTEXS; ++i )
	{
		Vertices[i] = val.Vertices[i];
	}

	return *this;
}

XE::RenderBind::RenderBind()
{

}

XE::RenderBind::RenderBind( const RenderBind & val )
{

}

XE::RenderBind & XE::RenderBind::operator=( const RenderBind & val )
{

	return *this;
}

XE::RenderBlit::RenderBlit()
{

}

XE::RenderBlit::RenderBlit( const RenderBlit & val )
{

}

XE::RenderBlit & XE::RenderBlit::operator=( const RenderBlit & val )
{

	return *this;
}

XE::RenderCompute::RenderCompute()
{

}

XE::RenderCompute::RenderCompute( const RenderCompute & val )
{

}

XE::RenderCompute & XE::RenderCompute::operator=( const RenderCompute & val )
{

	return *this;
}
