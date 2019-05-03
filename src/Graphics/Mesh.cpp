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

BEGIN_META( StaticMesh )
END_META()

XE::StaticMesh::StaticMesh()
{

}

XE::StaticMesh::~StaticMesh()
{

}

BEGIN_META( DynamicMesh )
END_META()

XE::DynamicMesh::DynamicMesh()
{

}

XE::DynamicMesh::~DynamicMesh()
{

}

BEGIN_META( SkinnedMesh )
END_META()

XE::SkinnedMesh::SkinnedMesh()
{

}

XE::SkinnedMesh::~SkinnedMesh()
{

}
