#include "Renderer.h"

USING_XE

BEG_META(Renderer)
END_META()

XE::Renderer::Renderer()
{

}

XE::Renderer::~Renderer()
{

}

void XE::Renderer::Startup()
{
	OnStartup();
}

void XE::Renderer::Render()
{
	BeginFrame();
	
	OnRender();

	EndFrame();
}

void XE::Renderer::Clearup()
{
	OnClearup();
}
