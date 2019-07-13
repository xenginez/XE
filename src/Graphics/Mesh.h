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
};

class GRAPHICS_API DynamicMesh : public Mesh
{
	OBJECT( DynamicMesh, Mesh )

public:
	DynamicMesh();

	~DynamicMesh() override;
};

class GRAPHICS_API SkinnedMesh : public Mesh
{
	OBJECT( SkinnedMesh, Mesh )

public:
	SkinnedMesh();

	~SkinnedMesh() override;
};

END_XE_NAMESPACE

#endif //__MESH_H__4FE59ADA_9803_44CA_A0B1_0D191345D16F
