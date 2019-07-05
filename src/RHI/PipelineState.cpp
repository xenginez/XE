#include "PipelineState.h"

USING_XE

BEG_META( BlendState )
END_META()

XE::BlendState::BlendState()
{

}

XE::BlendState::~BlendState()
{

}

XE::Vec4 XE::BlendState::GetBlendFactor() const
{
	return {};
}

void XE::BlendState::SetBlendFactor( const Vec4 & val )
{

}

bool XE::BlendState::GetEnableIndependentBlend() const
{
	return false;
}

void XE::BlendState::SetEnableIndependentBlend( bool val )
{

}

bool XE::BlendState::GetAlphaToCoverageEnabled() const
{
	return false;
}

void XE::BlendState::SetAlphaToCoverageEnabled( bool val )
{

}

XE::uint64 XE::BlendState::GetRenderTargetCount() const
{
	return 0;
}

XE::RenderTargetPtr XE::BlendState::GetRenderTarget( XE::uint64 index ) const
{
	return nullptr;
}

void XE::BlendState::SetRenderTarget( XE::uint64 index, const RenderTargetPtr & val )
{

}

BEG_META( RasterizerState )
END_META()

XE::RasterizerState::RasterizerState()
{

}

XE::RasterizerState::~RasterizerState()
{

}

BEG_META( DepthStencilState )
END_META()

XE::DepthStencilState::DepthStencilState()
{

}

XE::DepthStencilState::~DepthStencilState()
{

}

BEG_META( ComputePipelineState )
END_META()

XE::ComputePipelineState::ComputePipelineState()
{

}

XE::ComputePipelineState::~ComputePipelineState()
{

}

XE::ComputeShaderPtr XE::ComputePipelineState::GetComputeShader() const
{
	return _CS;
}

void XE::ComputePipelineState::SetComputeShader(ComputeShaderPtr val)
{
	_CS = val;
}

BEG_META( GraphicsPipelineState )
END_META()

XE::GraphicsPipelineState::GraphicsPipelineState()
{

}

XE::GraphicsPipelineState::~GraphicsPipelineState()
{

}
