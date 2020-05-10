#include "RendererContextMetal.h"

#if PLATFORM_OS & (OS_MAC | OS_IOS)

XE::RendererContextMetal::RendererContextMetal()
{

}

XE::RendererContextMetal::~RendererContextMetal()
{

}

void XE::RendererContextMetal::Init( const InitInfo & val )
{

}

void XE::RendererContextMetal::Shutdown()
{

}

XE::RendererContext * XE::CreateRendererContextMetal()
{
	return new XE::RendererContextMetal();
}
#else
XE::RendererContext * XE::CreateRendererContextMetal()
{
	return nullptr;
}
#endif