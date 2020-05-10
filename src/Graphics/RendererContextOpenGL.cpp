#include "RendererContextOpenGL.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_LINUX | OS_MAC)

XE::RendererContextOpenGL::RendererContextOpenGL()
{

}

XE::RendererContextOpenGL::~RendererContextOpenGL()
{

}

void XE::RendererContextOpenGL::Init( const InitInfo & val )
{

}

void XE::RendererContextOpenGL::Shutdown()
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