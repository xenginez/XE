#include "RendererContextGLES2.h"

#if PLATFORM_OS & (OS_ANDROID | OS_IOS)

XE::RendererContextGLES2::RendererContextGLES2()
{

}

XE::RendererContextGLES2::~RendererContextGLES2()
{

}

void XE::RendererContextGLES2::OnStartup()
{

}

void XE::RendererContextGLES2::OnRender( XE::Frame* val )
{

}

void XE::RendererContextGLES2::OnClearup()
{

}

XE::RendererContext * XE::CreateRendererContextGLES2()
{
	return new XE::RendererContextGLES2();
}
#else
XE::RendererContext * XE::CreateRendererContextGLES2()
{
	return nullptr;
}
#endif