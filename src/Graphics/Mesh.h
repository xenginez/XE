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

class GRAPHICS_API SubMesh : public XE::Object
{
	OBJECT( SubMesh, Object )

public:
	SubMesh();

	~SubMesh() override;

public:
	XE::uint32 GetIndexStart() const;

	XE::uint32 GetIndexCount() const;

private:
	XE::uint32 _IndexStart;
	XE::uint32 _IndexCount;
};

class GRAPHICS_API Mesh : public XE::Object
{
	OBJECT( Mesh, Object )
	
public:
	Mesh();
	
	~Mesh() override;

public:
	const InputLayoutPtr & GetInputLayout() const;

public:
	XE::uint64 GetSubMeshCount() const;

	const Array<SubMesh> & GetSubMeshs() const;

	const SubMesh & GetSubMesh( XE::uint64 val ) const;

protected:
	Array<SubMesh> _SubMesh;
	InputLayoutPtr _InputLayout;
};

class GRAPHICS_API StaticMesh : public Mesh
{
	OBJECT( StaticMesh, Mesh )

public:
	StaticMesh();

	~StaticMesh() override;

public:
	const IndexBufferPtr & GetIndexBuffer() const;

	const VertexBufferPtr & GetVertexBuffer() const;

private:
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

class GRAPHICS_API SkinnedMesh : public StaticMesh
{
	OBJECT( SkinnedMesh, StaticMesh )

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
