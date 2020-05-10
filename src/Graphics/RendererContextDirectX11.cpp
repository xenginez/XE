#include "RendererContextDirectX11.h"

#if PLATFORM_OS & (OS_WINDOWS)

XE::RendererContextDirectX11::RendererContextDirectX11()
{

}

XE::RendererContextDirectX11::~RendererContextDirectX11()
{

}

void XE::RendererContextDirectX11::Init( const InitInfo & val )
{

}

void XE::RendererContextDirectX11::Shutdown()
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