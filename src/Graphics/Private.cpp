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

XE::uint32 XE::GfxRefCount::Inc()
{
	return ++_Count;
}

XE::uint32 XE::GfxRefCount::Dec()
{
	return --_Count;
}

void XE::GfxRefCount::Reset()
{
	_Count = 0;
}

void XE::RenderFrame::Reset()
{
	RenderItemSize = 0;
	RenderBlitSize = 0;
	RenderOcclusionSize = 0;

	PrevCmd.Reset();
	PostCmd.Reset();
	DestoryCmd.Reset();
	TransientBuffers.Reset();
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

XE::PShader::PShader()
{

}

XE::PShader::PShader( const PShader & val )
{

}

XE::PShader & XE::PShader::operator=( const PShader & val )
{

	return *this;
}

XE::PTexture::PTexture()
{

}

XE::PTexture::PTexture( const PTexture & val )
{

}

XE::PTexture & XE::PTexture::operator=( const PTexture & val )
{

	return *this;
}

XE::PProgram::PProgram()
{

}

XE::PProgram::PProgram( const PProgram & val )
{

}

XE::PProgram & XE::PProgram::operator=( const PProgram & val )
{

	return *this;
}

XE::PVertexLayout::PVertexLayout()
{

}

XE::PVertexLayout::PVertexLayout( const PVertexLayout & val )
{

}

XE::PVertexLayout & XE::PVertexLayout::operator=( const PVertexLayout & val )
{

}

XE::PFrameBuffer::PFrameBuffer()
{

}

XE::PFrameBuffer::PFrameBuffer( const PFrameBuffer & val )
{

}

XE::PFrameBuffer & XE::PFrameBuffer::operator=( const PFrameBuffer & val )
{

	return *this;
}

XE::PIndexBuffer::PIndexBuffer()
{

}

XE::PIndexBuffer::PIndexBuffer( const PIndexBuffer & val )
{

}

XE::PIndexBuffer & XE::PIndexBuffer::operator=( const PIndexBuffer & val )
{

	return *this;
}

XE::PVertexBuffer::PVertexBuffer()
{

}

XE::PVertexBuffer::PVertexBuffer( const PVertexBuffer & val )
{

}

XE::PVertexBuffer & XE::PVertexBuffer::operator=( const PVertexBuffer & val )
{

	return *this;
}

XE::PIndirectBuffer::PIndirectBuffer()
{

}

XE::PIndirectBuffer::PIndirectBuffer( const PIndirectBuffer & val )
{

}

XE::PIndirectBuffer & XE::PIndirectBuffer::operator=( const PIndirectBuffer & val )
{

}


XE::PView::PView()
{

}

XE::PView::PView( const PView & val )
{

}

XE::PView & XE::PView::operator=( const PView & val )
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
