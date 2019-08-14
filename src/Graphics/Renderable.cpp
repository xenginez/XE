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

void XE::Renderable::SetMaterial( const MaterialPtr & val )
{
	_Material = val;
}

const XE::Mat4& XE::Renderable::GetTransform() const
{
	return _Transform;
}

void XE::Renderable::SetTransform( const Mat4& val )
{
	_Transform = val;
}

void XE::Renderable::Startup( RenderContextPtr & context )
{
	OnStartup( context );
}

void XE::Renderable::Render( RenderContextPtr & context, RenderQueuePtr & queue )
{
	OnRender( context, queue );
}

void XE::Renderable::Clearup( RenderContextPtr & context )
{
	OnClearup( context );
}
