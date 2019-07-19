#include "RenderPass.h"

USING_XE

BEG_META(RenderPass)
END_META()

XE::RenderPass::RenderPass()
{

}

XE::RenderPass::~RenderPass()
{

}

void XE::RenderPass::Render()
{
	OnRender();
}

void XE::RenderPass::OnRender()
{

}
