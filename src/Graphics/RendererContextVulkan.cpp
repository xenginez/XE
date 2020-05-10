#include "RendererContextVulkan.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_ANDROID | OS_LINUX)

XE::RendererContextVulkan::RendererContextVulkan()
{

}

XE::RendererContextVulkan::~RendererContextVulkan()
{

}

void XE::RendererContextVulkan::Init( const XE::InitInfo & val )
{

}

void XE::RendererContextVulkan::Render( XE::Frame * frame )
{

}

void XE::RendererContextVulkan::Shutdown()
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