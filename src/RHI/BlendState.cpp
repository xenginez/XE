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

Vec4 BlendState::GetBlendFactor() const
{
    return _BlendFactor;
}

void BlendState::SetBlendFactor(const Vec4 &val)
{
    _BlendFactor = val;
}

bool BlendState::GetEnableIndependentBlend() const
{
    return _EnableIndependentBlend;
}

void BlendState::SetEnableIndependentBlend(bool val)
{
    _EnableIndependentBlend = val;
}

bool BlendState::GetAlphaToCoverageEnabled() const
{
    return _AlphaToCoverageEnabled;
}

void BlendState::SetAlphaToCoverageEnabled(bool val)
{
    _AlphaToCoverageEnabled = val;
}

XE::uint64 BlendState::GetRenderTargetCount() const
{
	return _RenderTargets.size();
}

RenderTargetPtr BlendState::GetRenderTarget( XE::uint64 index ) const
{
	return _RenderTargets[index];
}

void BlendState::SetRenderTarget( XE::uint64 index, const RenderTargetPtr &val )
{
	_RenderTargets[index] = val;
}
