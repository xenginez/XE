#include "Mesh.h"

USING_XE

BEG_META( SubMesh )
END_META()

SubMesh::SubMesh()
{

}

SubMesh::~SubMesh()
{

}

XE::uint32 XE::SubMesh::GetIndexStart() const
{
	return _IndexStart;
}

XE::uint32 XE::SubMesh::GetIndexCount() const
{
	return _IndexCount;
}

BEG_META(Mesh)
END_META()

XE::Mesh::Mesh()
{

}

XE::Mesh::~Mesh()
{

}

XE::uint64 XE::Mesh::GetSubMeshCount() const
{
	return _SubMesh.size();
}

const Array<SubMesh> & XE::Mesh::GetSubMeshs() const
{
	return _SubMesh;
}

const XE::SubMesh & XE::Mesh::GetSubMesh( XE::uint64 val ) const
{
	return _SubMesh[val];
}

BEG_META( StaticMesh )
END_META()

XE::StaticMesh::StaticMesh()
{

}

XE::StaticMesh::~StaticMesh()
{

}

BEG_META( DynamicMesh )
END_META()

XE::DynamicMesh::DynamicMesh()
{

}

XE::DynamicMesh::~DynamicMesh()
{

}

BEG_META( SkinnedMesh )
END_META()

XE::SkinnedMesh::SkinnedMesh()
{

}

XE::SkinnedMesh::~SkinnedMesh()
{

}

const XE::SkeletonPtr & XE::SkinnedMesh::GetSkeleton() const
{
	return _Skeleton;
}
