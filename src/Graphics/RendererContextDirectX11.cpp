#include "RendererContextDirectX11.h"

#if PLATFORM_OS & (OS_WINDOWS)

XE::RendererContextDirectX11::RendererContextDirectX11()
{

}

XE::RendererContextDirectX11::~RendererContextDirectX11()
{

}

void XE::RendererContextDirectX11::OnStartup()
{

}

void XE::RendererContextDirectX11::OnRender( XE::Frame* val )
{

}

void XE::RendererContextDirectX11::OnClearup()
{

}

XE::RendererContext * XE::CreateRendererContextDirectX11()
{
	return new XE::RendererContextDirectX11();
}
#else
XE::RendererContext * XE::CreateRendererContextDirectX11()
{
	return nullptr;
}
#endif