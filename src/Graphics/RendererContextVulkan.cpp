#include "RendererContextVulkan.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_ANDROID | OS_LINUX)

XE::RendererContextVulkan::RendererContextVulkan()
{

}

XE::RendererContextVulkan::~RendererContextVulkan()
{

}

void XE::RendererContextVulkan::OnStartup()
{

}

void XE::RendererContextVulkan::OnRender( XE::Frame* val )
{

}

void XE::RendererContextVulkan::OnClearup()
{

}

XE::RendererContext * XE::CreateRendererContextVulkan()
{
	return new XE::RendererContextVulkan();
}
#else
XE::RendererContext * XE::CreateRendererContextVulkan()
{
	return nullptr;
}
#endif