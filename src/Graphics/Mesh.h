/*!
 * \file   Mesh.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/11
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __MESH_H__4E34786E_911B_4D68_95AE_5016D3DC3B8F
#define __MESH_H__4E34786E_911B_4D68_95AE_5016D3DC3B8F

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Mesh : public Object
{
	OBJECT( Mesh, Object )

public:
	Mesh();

	~Mesh();

public:
	Array<Vec2> _UV0;
	Array<Vec2> _UV1;
	Array<Color> _Colors;
	Array<Vec4> _Tangents;
	Array<Vec3> _Vertices;
	Array<uint32> _Indices;

	VertexLayout _Layout;
	IndexBufferHandle _IndexBuffer;
	VertexBufferHandle _VertexBuffer;
};

class GRAPHICS_API StaticMesh : public Mesh
{
	OBJECT( StaticMesh, Mesh )

public:
	StaticMesh();

	~StaticMesh();
};

class GRAPHICS_API DynamicMesh : public Mesh
{
	OBJECT( DynamicMesh, Mesh )

public:
	DynamicMesh();

	~DynamicMesh();
};

class GRAPHICS_API SkeletonMesh : public Mesh
{
	OBJECT( SkeletonMesh, Mesh )

public:
	SkeletonMesh();

	~SkeletonMesh();
};

END_XE_NAMESAPCE

#endif // __MESH_H__4E34786E_911B_4D68_95AE_5016D3DC3B8F
