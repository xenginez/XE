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

class XE_API Mesh : public XE::Object
{
	OBJECT( Mesh, Object )
	
public:
	Mesh();
	
	~Mesh() override;

public:
	const XE::Array<XE::Vec2> & GetUV1() const;

	void SetUV1( const XE::Array<XE::Vec2> & val );

	const XE::Array<XE::Vec2> & GetUV2() const;

	void SetUV2( const XE::Array<XE::Vec2> & val );

	const XE::Array<XE::Vec3> & GetNormals() const;

	void SetNormals( const XE::Array<XE::Vec3> & val );

	const XE::Array<XE::Vec3> & GetTangents() const;

	void SetTangents( const XE::Array<XE::Vec3> & val );

	const XE::Array<XE::Vec3> & GetVertices() const;

	void SetVertices( const XE::Array<XE::Vec3> & val );

	const XE::Array<XE::uint32> & GetTriangles() const;

	void SetTriangles( const XE::Array<XE::uint32> & val );

private:
	XE::Array<XE::Vec2> _UV1;
	XE::Array<XE::Vec2> _UV2;
	XE::Array<XE::Vec3> _Normals;
	XE::Array<XE::Vec3> _Tangents;
	XE::Array<XE::Vec3> _Vertices;
	XE::Array<XE::uint32> _Triangles;
};

END_XE_NAMESPACE

#endif //__MESH_H__4FE59ADA_9803_44CA_A0B1_0D191345D16F
