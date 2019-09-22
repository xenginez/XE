#include "Model.h"

USING_XE

BEG_META( Model )
END_META()

XE::Model::Model()
{

}

XE::Model::~Model()
{

}

XE::MeshPtr XE::Model::GetMesh() const
{
	return _Mesh;
}

void XE::Model::SetMesh( const MeshPtr & val )
{
	_Mesh = val;
}

XE::RenderMaterialPtr XE::Model::GetRenderMaterial() const
{
	return _Material;
}

void XE::Model::SetRenderMaterial( const RenderMaterialPtr & val )
{
	_Material = val;
}

void XE::Model::OnStartup()
{

}

void XE::Model::OnRender()
{

}

void XE::Model::OnClearup()
{

}
