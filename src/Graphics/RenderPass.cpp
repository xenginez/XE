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

TechniquePtr XE::RenderPass::GetTechnuque() const
{
	return _Technique.lock();
}
