#include "RendererContextVulkan.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_ANDROID | OS_LINUX)

XE::RendererContextVulkan::RendererContextVulkan()
{

}

XE::RendererContextVulkan::~RendererContextVulkan()
{

}

void XE::RendererContextVulkan::OnRender( XE::Frame* val )
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