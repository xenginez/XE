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

const AABB & SubMesh::GetBoundingBox() const
{
	return _BoundingBox;
}

const XE::IndexBufferPtr & XE::SubMesh::GetIndexBuffer() const
{
	return _IndexBuffer;
}

BEG_META(Mesh)
END_META()

XE::Mesh::Mesh()
{

}

XE::Mesh::~Mesh()
{

}

XE::AABB XE::Mesh::GetBoundingBox() const
{
	XE::AABB ret;

	for( const auto & sub : _SubMesh )
	{
		ret.Merge( sub.GetBoundingBox() );
	}

	return ret;
}

const XE::InputLayoutPtr & XE::Mesh::GetInputLayout() const
{
	return _InputLayout;
}

const XE::VertexBufferPtr & XE::Mesh::GetVertexBuffer() const
{
	return _VertexBuffer;
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
