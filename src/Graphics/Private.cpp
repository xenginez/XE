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

void XE::RenderBind::Reset()
{
	for( auto & it : Binds )
	{
		it.Type = BindType::NONE;
		it.Mip = 0;
		it.Handle = std::numeric_limits<XE::uint64>::max();
		it.Access = XE::Access::COUNT;
		it.SamplerFlags = 0;
		it.Format = XE::TextureFormat::RGBA8;
	}
}

void XE::RenderDraw::Reset()
{
	IsDynamicIndices = false;
	Rgba = XE::Color::Black;
	StartMatrix = 0;
	NumMatrices = 0;
	InstanceDataOffset = 0;
	NumInstances = 0;
	StartIndirect = 0;
	NumIndirect = 0;
	Scissor = XE::Rectf::Zero;
	SubmitFlags = 0;
	StreamMask = 0;
	IsDynamicInstanceDataBuffer = false;
	InstanceDataBuffer = XE::VertexBufferHandle::Invalid;
	IndirectBuffer = XE::IndirectBufferHandle::Invalid;
	OcclusionQuery = XE::OcclusionQueryHandle::Invalid;
	StateFlags = XE::StateFlags::NONE;
	FrontStencilFlags = XE::StencilFlags::NONE;
	BackStencilFlags = XE::StencilFlags::NONE;
}

void XE::RenderBlit::Reset()
{
	SrcX = 0;
	SrcY = 0;
	SrcZ = 0;
	DstX = 0;
	DstY = 0;
	DstZ = 0;
	Width = 0;
	Height = 0;
	Depth = 0;
	SrcMip = 0;
	DstMip = 0;
	Handle = XE::ViewHandle::Invalid;
	Src = XE::TextureHandle::Invalid;
	Dst = XE::TextureHandle::Invalid;
}

void XE::RenderCompute::Reset()
{
	StartMatrix = 0;
	NumMatrices = 0;

	StartIndirect = 0;
	NumIndirect = 0;

	NumX = 0;
	NumY = 0;
	NumZ = 0;

	IndirectBuffer = XE::IndirectBufferHandle::Invalid;
}

void XE::RenderFrame::Reset()
{
	UniformsSize = 0;
	TransformsSize = 0;
	RenderItemSize = 0;
	RenderBlitSize = 0;
	DestoryHandleSize = 0;
	RenderOcclusionSize = 0;

	PrevCmd.Reset();
	PostCmd.Reset();
	TransientBuffers.Reset();
}
