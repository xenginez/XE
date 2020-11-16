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

XE::RenderItem::RenderItem( RenderItem && val )
{
	Type = val.Type;

	if( Type == ItemType::DRAW )
	{
		Draw = std::move( val.Draw );
	}
	else
	{
		Compute = std::move( val.Compute );
	}
}

XE::RenderItem::~RenderItem()
{

}

XE::RenderItem & XE::RenderItem::operator=( RenderItem && val )
{
	Type = val.Type;

	if( Type == ItemType::DRAW )
	{
		Draw = std::move( val.Draw );
	}
	else
	{
		Compute = std::move( val.Compute );
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
