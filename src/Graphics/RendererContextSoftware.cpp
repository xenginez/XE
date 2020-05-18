#include "RendererContextSoftware.h"

XE::RendererContextSoftware::RendererContextSoftware()
{

}

XE::RendererContextSoftware::~RendererContextSoftware()
{

}

void XE::RendererContextSoftware::OnStartup()
{

}

void XE::RendererContextSoftware::OnRender( XE::Frame* val )
{

}

void XE::RendererContextSoftware::OnClearup()
{

}

XE::RendererContext * XE::CreateRendererContextSoftware()
{
	return new XE::RendererContextSoftware();
}
