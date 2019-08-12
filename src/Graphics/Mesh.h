/*!
 * \file    Mesh.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MESH_H__4FE59ADA_9803_44CA_A0B1_0D191345D16F
#define __MESH_H__4FE59ADA_9803_44CA_A0B1_0D191345D16F

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Mesh : public Object
{
	OBJECT(Mesh, Object)
	
public:
	Mesh();
	
	~Mesh() override;

public:
	const AABB & GetBoundingBox() const;

	const InputLayoutPtr & GetInputLayout() const;

	const IndexBufferPtr & GetIndexBuffer() const;

	const VertexBufferPtr & GetVertexBuffer() const;

private:
	AABB _BoundingBox;
	InputLayoutPtr _InputLayout;
	IndexBufferPtr _IndexBuffer;
	VertexBufferPtr _VertexBuffer;
};

class GRAPHICS_API DynamicMesh : public Mesh
{
	OBJECT( DynamicMesh, Mesh )

public:
	DynamicMesh();

	~DynamicMesh() override;

public:
	const DynamicIndexBufferPtr & GetDynamicIndexBuffer() const;

	const DynamicVertexBufferPtr & GetDynamicVertexBuffer() const;

private:
	DynamicIndexBufferPtr _DynamicIndexBuffer;
	DynamicVertexBufferPtr _DynamicVertexBuffer;
};

class GRAPHICS_API SkinnedMesh : public Mesh
{
	OBJECT( SkinnedMesh, Mesh )

public:
	SkinnedMesh();

	~SkinnedMesh() override;

public:
	const SkeletonPtr & GetSkeleton() const;

private:
	SkeletonPtr _Skeleton;
};

END_XE_NAMESPACE

#endif //__MESH_H__4FE59ADA_9803_44CA_A0B1_0D191345D16F
