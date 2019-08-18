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

const XE::InputLayoutPtr & XE::Mesh::GetInputLayout() const
{
	return _InputLayout;
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

const IndexBufferPtr & XE::StaticMesh::GetIndexBuffer() const
{
	return _IndexBuffer;
}

const XE::VertexBufferPtr & XE::StaticMesh::GetVertexBuffer() const
{
	return _VertexBuffer;
}

BEG_META( DynamicMesh )
END_META()

XE::DynamicMesh::DynamicMesh()
{

}

XE::DynamicMesh::~DynamicMesh()
{

}

const XE::DynamicIndexBufferPtr & XE::DynamicMesh::GetDynamicIndexBuffer() const
{
	return _DynamicIndexBuffer;
}

const XE::DynamicVertexBufferPtr & XE::DynamicMesh::GetDynamicVertexBuffer() const
{
	return _DynamicVertexBuffer;
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
