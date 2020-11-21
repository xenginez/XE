#include "RendererContextDirectX12.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_XBOXONE)

#include <d3d12.h>

#pragma comment( lib, "d3d12.lib" )

XE::RendererContextDirectX12::RendererContextDirectX12()
{

}

XE::RendererContextDirectX12::~RendererContextDirectX12()
{

}

void XE::RendererContextDirectX12::OnRender( XE::RenderFrame* val )
{

}

#endif