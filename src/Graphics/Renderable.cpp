#include "Renderable.h"

USING_XE

BEG_META(Renderable)
END_META()

XE::Renderable::Renderable()
{

}

XE::Renderable::~Renderable()
{

}

XE::MeshPtr XE::Renderable::GetMesh() const
{
	return _Mesh;
}

void XE::Renderable::SetMesh( const MeshPtr & val )
{
	_Mesh = val;
}

XE::MaterialPtr XE::Renderable::GetMaterial() const
{
	return _Material;
}

void XE::Renderable::SetMaterialPtr( const MaterialPtr & val )
{
	_Material = val;
}
