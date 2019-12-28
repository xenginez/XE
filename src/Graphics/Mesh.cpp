#include "Mesh.h"

#include "Skeleton.h"

USING_XE

BEG_META( Mesh )
type->Property( "UV1", &Mesh::_UV1, XE::IMetaProperty::NoDesign );
type->Property( "UV2", &Mesh::_UV2, XE::IMetaProperty::NoDesign );
type->Property( "Normals", &Mesh::_Normals, XE::IMetaProperty::NoDesign );
type->Property( "Tangents", &Mesh::_Tangents, XE::IMetaProperty::NoDesign );
type->Property( "Vertices", &Mesh::_Vertices, XE::IMetaProperty::NoDesign );
type->Property( "Triangles", &Mesh::_Triangles, XE::IMetaProperty::NoDesign );
type->Property( "Skeleton", &Mesh::_Skeleton, XE::IMetaProperty::NoDesign );
END_META()

XE::Mesh::Mesh()
{

}

XE::Mesh::~Mesh()
{

}

const XE::SkeletonPtr & Mesh::GetSkeleton() const
{
	return _Skeleton;
}

void Mesh::SetSkeleton( const XE::SkeletonPtr & val )
{
	_Skeleton = val;
}

const XE::Array<XE::Vec2> & Mesh::GetUV1() const
{
	return _UV1;
}

void Mesh::SetUV1( const XE::Array<XE::Vec2> & val )
{
	_UV1 = val;
}

const XE::Array<XE::Vec2> & Mesh::GetUV2() const
{
	return _UV2;
}

void Mesh::SetUV2( const XE::Array<XE::Vec2> & val )
{
	_UV2 = val;
}

const XE::Array<XE::Vec3> & Mesh::GetNormals() const
{
	return _Normals;
}

void Mesh::SetNormals( const XE::Array<XE::Vec3> & val )
{
	_Normals = val;
}

const XE::Array<XE::Vec3> & Mesh::GetTangents() const
{
	return _Tangents;
}

void Mesh::SetTangents( const XE::Array<XE::Vec3> & val )
{
	_Tangents = val;
}

const XE::Array<XE::Vec3> & Mesh::GetVertices() const
{
	return _Vertices;
}

void Mesh::SetVertices( const XE::Array<XE::Vec3> & val )
{
	_Vertices = val;
}

const XE::Array<XE::uint32> & Mesh::GetTriangles() const
{
	return _Triangles;
}

void Mesh::SetTriangles( const XE::Array<XE::uint32> & val )
{
	_Triangles = val;
}
