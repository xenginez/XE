#include "RendererContextDirectX12.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_XBOXONE)

#include <d3d12.h>

XE::RendererContextDirectX12::RendererContextDirectX12()
{

}

XE::RendererContextDirectX12::~RendererContextDirectX12()
{

}

void XE::RendererContextDirectX12::OnStartup()
{

}

void XE::RendererContextDirectX12::OnRender( XE::Frame* val )
{

}

void XE::RendererContextDirectX12::OnClearup()
{

}


XE::RendererContext * XE::CreateRendererContextDirectX12()
{
	return new XE::RendererContextDirectX12();
}
#else
XE::RendererContext * XE::CreateRendererContextDirectX12()
{
	return nullptr;
}
#endif