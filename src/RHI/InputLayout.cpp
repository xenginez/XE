#include "InputLayout.h"

USING_XE

BEG_META( InputLayout )
END_META()

XE::InputLayout::InputLayout()
{

}

XE::InputLayout::~InputLayout()
{

}

XE::InputLayout &XE::InputLayout::Add( const XE::String &name, XE::uint32 offset, XE::LayoutFormat format )
{
	Element e;
	
	e.Name = name;
	e.Offset = offset;
	e.Format = format;
	
	_Elements.emplace_back(e);
	
	return *this;
}

XE::uint64 XE::InputLayout::ElementCount() const
{
	return _Elements.size();
}

XE::InputLayout::Element &XE::InputLayout::GetElement( XE::uint64 val )
{
	return _Elements[val];
}

const XE::InputLayout::Element &XE::InputLayout::GetElement( XE::uint64 val ) const
{
	return _Elements[val];
}

const XE::Array < XE::InputLayout::Element > &XE::InputLayout::GetElements() const
{
	return _Elements;
}

XE::InputLayout::Element &XE::InputLayout::operator []( XE::uint64 val )
{
	return _Elements[val];
}

const XE::InputLayout::Element &XE::InputLayout::operator []( XE::uint64 val ) const
{
	return _Elements[val];
}
