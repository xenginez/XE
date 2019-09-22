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

const XE::Mat4& XE::Renderable::GetTransform() const
{
	return _Transform;
}

void XE::Renderable::SetTransform( const Mat4& val )
{
	_Transform = val;
}

void XE::Renderable::Startup()
{
	OnStartup();
}

void XE::Renderable::Render()
{
	OnRender();
}

void XE::Renderable::Clearup()
{
	OnClearup();
}
