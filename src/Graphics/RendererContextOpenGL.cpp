#include "RendererContextOpenGL.h"

#include "GLContext.h"
#include "GLContextWGL.h"
#include "GLContextEGL.h"
#include "GLContextGLX.h"
#include "GLContextEAGL.h"
#include "GLContextNSGL.h"
#include "GLContextHTML5.h"

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
