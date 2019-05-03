#include "VertexDecl.h"

USING_XE

void XE::PosTexcoord0Vertex::Init( VertexLayout& decl )
{
	decl.begin()
		.add( Attribute::Position, 3, AttributeType::Float )
		.add( Attribute::TexCoord0, 2, AttributeType::Float )
		.end();
}

void XE::MeshVertex::Init( VertexLayout& decl )
{
	decl.begin()
		.add( Attribute::Position, 3, AttributeType::Float )
		.add( Attribute::Normal, 3, AttributeType::Uint8, true, true )
		.add( Attribute::Tangent, 3, AttributeType::Uint8, true, true )
		.add( Attribute::Bitangent, 3, AttributeType::Uint8, true, true )
		.add( Attribute::TexCoord0, 2, AttributeType::Float )
		.end();
}

void XE::PosTexcoord0Color0Vertex::Init( VertexLayout& decl )
{
	decl.begin()
		.add( Attribute::Position, 2, AttributeType::Float )
		.add( Attribute::TexCoord0, 2, AttributeType::Float )
		.add( Attribute::Color0, 4, AttributeType::Uint8, true )
		.end();
}
