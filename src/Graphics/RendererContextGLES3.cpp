#include "RendererContextGLES3.h"

#if PLATFORM_OS & (OS_ANDROID)

XE::RendererContextGLES3::RendererContextGLES3()
{

}

XE::RendererContextGLES3::~RendererContextGLES3()
{

}

void XE::RendererContextGLES3::Init( const InitInfo & val )
{

}

void XE::RendererContextGLES3::Render( XE::Frame * frame )
{

}

void XE::RendererContextGLES3::Shutdown()
{

}

XE::RendererContext * XE::CreateRendererContextGLES3()
{
	return new XE::RendererContextGLES3();
}
#else
XE::RendererContext * XE::CreateRendererContextGLES3()
{
	return nullptr;
}
#endif