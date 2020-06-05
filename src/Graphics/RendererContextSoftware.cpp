#include "RendererContextSoftware.h"

XE::RendererContextSoftware::RendererContextSoftware()
{

}

XE::RendererContextSoftware::~RendererContextSoftware()
{

}

void XE::RendererContextSoftware::OnRender( XE::Frame* val )
{

}

XE::RendererContext * XE::CreateRendererContextSoftware()
{
	return new XE::RendererContextSoftware();
}
