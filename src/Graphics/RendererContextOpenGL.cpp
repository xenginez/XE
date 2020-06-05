#include "RendererContextOpenGL.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_LINUX | OS_MAC)

XE::RendererContextOpenGL::RendererContextOpenGL()
{

}

XE::RendererContextOpenGL::~RendererContextOpenGL()
{

}

void XE::RendererContextOpenGL::OnRender( XE::Frame* val )
{

}

XE::RendererContext * XE::CreateRendererContextOpenGL()
{
	return new XE::RendererContextOpenGL();
}
#else
XE::RendererContext * XE::CreateRendererContextOpenGL()
{
	return nullptr;
}
#endif