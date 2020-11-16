#include "RendererContextNull.h"

XE::RendererContextNull::RendererContextNull()
{

}

XE::RendererContextNull::~RendererContextNull()
{

}

void XE::RendererContextNull::OnRender( XE::Frame * val )
{

}

XE::RendererContext * XE::CreateRendererContextNull()
{
	return new XE::RendererContextNull();
}
