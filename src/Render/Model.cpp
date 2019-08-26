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

XE::MaterialPtr XE::Model::GetMaterial() const
{
	return _Material;
}

void XE::Model::SetMaterial( const MaterialPtr & val )
{
	_Material = val;
}

void XE::Model::OnStartup( IRenderContextPtr & context )
{

}

void XE::Model::OnRender( IRenderContextPtr & context, RenderQueuePtr & queue )
{

}

void XE::Model::OnClearup( IRenderContextPtr & context )
{

}
