#include "VertexLayout.h"

USING_XE

XE::VertexLayout::VertexLayout()
{

}

XE::VertexLayout::~VertexLayout()
{

}

XE::VertexLayout & XE::VertexLayout::Add( const String & name, XE::uint32 count, AttributeType type )
{
	Element e;

	e.Name = name;
	e.Type = type;
	e.Count = count;
	switch( e.Type )
	{
	case XE::AttributeType::INT8:
		e.Size = 1 * count;
		break;
	case XE::AttributeType::INT16:
		e.Size = 2 * count;
		break;
	case XE::AttributeType::INT32:
		e.Size = 4 * count;
		break;
	case XE::AttributeType::INT64:
		e.Size = 8 * count;
		break;
	case XE::AttributeType::UINT8:
		e.Size = 1 * count;
		break;
	case XE::AttributeType::UINT16:
		e.Size = 2 * count;
		break;
	case XE::AttributeType::UINT32:
		e.Size = 4 * count;
		break;
	case XE::AttributeType::UINT64:
		e.Size = 8 * count;
		break;
	case XE::AttributeType::FLOAT16:
		e.Size = 2 * count;
		break;
	case XE::AttributeType::FLOAT32:
		e.Size = 4 * count;
		break;
	case XE::AttributeType::FLOAT64:
		e.Size = 8 * count;
		break;
	default:
		break;
	}
	if( !_Elements.empty() )
	{
		e.Offset = _Elements.back().Offset + _Elements.back().Size;
	}

	_Elements.push_back( std::move( e ) );

	return *this;
}

XE::uint64 XE::VertexLayout::GetElementCount() const
{
	return _Elements.size();
}

const XE::VertexLayout::Element & XE::VertexLayout::GetElement( XE::uint64 val ) const
{
	return _Elements[val];
}

const XE::VertexLayout::Element & XE::VertexLayout::operator []( XE::uint64 val ) const
{
	return _Elements[val];
}
