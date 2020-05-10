#include "RendererContextSoftware.h"

XE::RendererContextSoftware::RendererContextSoftware()
{

}

XE::RendererContextSoftware::~RendererContextSoftware()
{

}

void XE::RendererContextSoftware::Init( const InitInfo & val )
{

}

void XE::RendererContextSoftware::Render( XE::Frame * frame )
{

}

void XE::RendererContextSoftware::Shutdown()
{

}

XE::RendererContext * XE::CreateRendererContextSoftware()
{
	return new XE::RendererContextSoftware();
}
