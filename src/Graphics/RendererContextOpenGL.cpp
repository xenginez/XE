#include "RendererContextOpenGL.h"

XE::RendererContextGL::RendererContextGL()
{

}

XE::RendererContextGL::~RendererContextGL()
{

}

void XE::RendererContextGL::OnRender( XE::Frame* val )
{

}

XE::RendererContext * XE::CreateRendererContextGL()
{
	return new XE::RendererContextGL();
}
