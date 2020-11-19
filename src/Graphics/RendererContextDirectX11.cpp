#include "RendererContextDirectX11.h"
#if PLATFORM_OS & (OS_WINDOWS)

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <d3dcommon.h>

#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxguid.lib" )

#include "Utils/Logger.h"

XE::RendererContextDirectX11::RendererContextDirectX11()
{

}

XE::RendererContextDirectX11::~RendererContextDirectX11()
{

}

void XE::RendererContextDirectX11::OnRender( XE::Frame * val )
{

}

#endif
