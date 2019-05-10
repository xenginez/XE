#include "Model.h"

USING_XE

BEGIN_META(Model)
END_META()

XE::Model::Model()
{

}

XE::Model::~Model()
{

}

const Mat4 &Model::GetWorldTransform() const
{
	return _Transform;
}

void Model::SetWorldTransform( const Mat4 &val )
{
	_Transform = val;
}

const XE::LOD &XE::Model::GetLOD() const
{
	return _LOD;
}

void XE::Model::SetLOD( const XE::LOD &val )
{
	_LOD = val;
}

XE::MeshPtr XE::Model::GetMesh( XE::uint64 lod ) const
{
	return _Mesh[lod];
}

void XE::Model::SetMesh( XE::MeshPtr val, XE::uint64 lod )
{
	_Mesh[lod] = std::move(val);
}

XE::MaterialPtr XE::Model::GetMaterial() const
{
	return _Material;
}

void XE::Model::SetMaterial( XE::MaterialPtr val )
{
	_Material = std::move(val);
}
