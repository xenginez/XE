#include "NavigationMesh.h"

BEG_META( XE::NavigationMesh )
END_META()

XE::NavigationMesh::NavigationMesh()
{

}

XE::NavigationMesh::~NavigationMesh()
{

}

XE::NavigationMeshHandle NavigationMesh::GetHandle() const
{
	return _Handle;
}

void XE::NavigationMesh::AssetLoad()
{

}
