#include "Mesh.h"

USING_XE

BEG_META(Mesh)
END_META()

XE::Mesh::Mesh()
{

}

XE::Mesh::~Mesh()
{

}

const XE::AABB & XE::Mesh::GetBoundingBox() const
{
	return _BoundingBox;
}

const XE::InputLayoutPtr & XE::Mesh::GetInputLayout() const
{
	return _InputLayout;
}

const XE::IndexBufferPtr & XE::Mesh::GetIndexBuffer() const
{
	return _IndexBuffer;
}

const XE::VertexBufferPtr & XE::Mesh::GetVertexBuffer() const
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
