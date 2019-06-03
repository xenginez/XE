#include "BlendState.h"

USING_XE

BEG_META(BlendState)
END_META()

XE::BlendState::BlendState()
{

}

XE::BlendState::~BlendState()
{

}

XE::BlendStateHandle XE::BlendState::GetHandle() const
{
	return _Handle;
}

Vec4 BlendState::BlendFactor() const
{
    return _BlendFactor;
}

void BlendState::setBlendFactor(const Vec4 &BlendFactor)
{
    _BlendFactor = BlendFactor;
}

bool BlendState::EnableIndependentBlend() const
{
    return _EnableIndependentBlend;
}

void BlendState::setEnableIndependentBlend(bool EnableIndependentBlend)
{
    _EnableIndependentBlend = EnableIndependentBlend;
}

bool BlendState::AlphaToCoverageEnabled() const
{
    return _AlphaToCoverageEnabled;
}

void BlendState::setAlphaToCoverageEnabled(bool AlphaToCoverageEnabled)
{
    _AlphaToCoverageEnabled = AlphaToCoverageEnabled;
}

Array<RenderTargetPtr> BlendState::RenderTargets() const
{
    return _RenderTargets;
}

void BlendState::setRenderTargets(const Array<RenderTargetPtr> &RenderTargets)
{
    _RenderTargets = RenderTargets;
}
