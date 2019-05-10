#include "Mesh.h"

USING_XE

BEGIN_META( Mesh )
type->Property( "UV0", &Mesh::_UV0 );
type->Property( "UV1", &Mesh::_UV1 );
type->Property( "Colors", &Mesh::_Colors );
type->Property( "Tangents", &Mesh::_Tangents );
type->Property( "Vertices", &Mesh::_Vertices );
type->Property( "Indices", &Mesh::_Indices );
END_META()

XE::Mesh::Mesh()
{

}

XE::Mesh::~Mesh()
{

}
