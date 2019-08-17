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

bool XE::BlendState::GetEnableIndependentBlend() const
{
	return _EnableIndependentBlend;
}

void XE::BlendState::SetEnableIndependentBlend( bool val )
{
	_EnableIndependentBlend = val;
}

bool XE::BlendState::GetAlphaToCoverageEnabled() const
{
	return _AlphaToCoverageEnabled;
}

void XE::BlendState::SetAlphaToCoverageEnabled( bool val )
{
	_AlphaToCoverageEnabled = val;
}

BEG_META( RasterizerState )
END_META()

XE::RasterizerState::RasterizerState()
{

}

XE::RasterizerState::~RasterizerState()
{

}

XE::FillType XE::RasterizerState::GetFillMode() const
{
	return _FillMode;
}

void XE::RasterizerState::SetFillMode( XE::FillType val )
{
	_FillMode = val;
}

XE::CullType XE::RasterizerState::GetCullMode() const
{
	return _CullMode;
}

void XE::RasterizerState::SetCullMode( XE::CullType val )
{
	_CullMode = val;
}

bool XE::RasterizerState::GetFrontCountClockwise() const
{
	return _FrontCountClockwise;
}

void XE::RasterizerState::SetFrontCountClockwise( bool val )
{
	_FrontCountClockwise = val;
}

XE::int32 XE::RasterizerState::GetDepthBias() const
{
	return _DepthBias;
}

void XE::RasterizerState::SetDepthBias( XE::int32 val )
{
	_DepthBias = val;
}

XE::float32 XE::RasterizerState::GetDepthBiasClamp() const
{
	return _DepthBiasClamp;
}

void XE::RasterizerState::SetDepthBiasClamp( XE::float32 val )
{
	_DepthBiasClamp = val;
}

XE::float32 XE::RasterizerState::GetSlopeSacleDepthBias() const
{
	return _SlopeSacleDepthBias;
}

void XE::RasterizerState::SetSlopeSacleDepthBias( XE::float32 val )
{
	_SlopeSacleDepthBias = val;
}

bool XE::RasterizerState::GetDepthClipEnable() const
{
	return _DepthClipEnable;
}

void XE::RasterizerState::SetDepthClipEnable( bool val )
{
	_DepthClipEnable = val;
}

bool XE::RasterizerState::GetMultisampleEnable() const
{
	return _MultisampleEnable;
}

void XE::RasterizerState::SetMultisampleEnable( bool val )
{
	_MultisampleEnable = val;
}

bool XE::RasterizerState::GetAntialiasedLineEnable() const
{
	return _AntialiasedLineEnable;
}

void XE::RasterizerState::SetAntialiasedLineEnable( bool val )
{
	_AntialiasedLineEnable = val;
}

XE::uint32 XE::RasterizerState::GetForcedSampleCount() const
{
	return _ForcedSampleCount;
}

void XE::RasterizerState::SetForcedSampleCount( XE::uint32 val )
{
	_ForcedSampleCount = val;
}

bool XE::RasterizerState::GetConservativeRaster() const
{
	return _ConservativeRaster;
}

void XE::RasterizerState::SetConservativeRaster( bool val )
{
	_ConservativeRaster = val;
}

BEG_META( DepthStencilState )
END_META()

XE::DepthStencilState::DepthStencilState()
{

}

XE::DepthStencilState::~DepthStencilState()
{

}

bool XE::DepthStencilState::GetDepthEnable() const
{
	return _DepthEnable;
}

void XE::DepthStencilState::SetDepthEnable( bool val )
{
	_DepthEnable = val;
}

bool XE::DepthStencilState::GetDepthWriteEnable() const
{
	return _DepthWriteEnable;
}

void XE::DepthStencilState::SetDepthWriteEnable( bool val )
{
	_DepthWriteEnable = val;
}

XE::CompareType XE::DepthStencilState::GetDepthFunc() const
{
	return _DepthFunc;
}

void XE::DepthStencilState::SetDepthFunc( XE::CompareType val )
{
	_DepthFunc = val;
}

bool XE::DepthStencilState::GetStencilEnable() const
{
	return _StencilEnable;
}

void XE::DepthStencilState::SetStencilEnable( bool val )
{
	_StencilEnable = val;
}

XE::uint8 XE::DepthStencilState::GetStencilReadMask() const
{
	return _StencilReadMask;
}

void XE::DepthStencilState::SetStencilReadMask( XE::uint8 val )
{
	_StencilReadMask = val;
}

XE::uint8 XE::DepthStencilState::GetStencilWriteMask() const
{
	return _StencilWriteMask;
}

void XE::DepthStencilState::SetStencilWriteMask( XE::uint8 val )
{
	_StencilWriteMask = val;
}

XE::CompareType XE::DepthStencilState::GetStencilFrontFunc() const
{
	return _StencilFrontFunc;
}

void XE::DepthStencilState::SetStencilFrontFunc( XE::CompareType val )
{
	_StencilFrontFunc = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilFrontFailOp() const
{
	return _StencilFrontFailOp;
}

void XE::DepthStencilState::SetStencilFrontFailOp( XE::StencilOperation val )
{
	_StencilFrontFailOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilFrontPassOp() const
{
	return _StencilFrontPassOp;
}

void XE::DepthStencilState::SetStencilFrontPassOp( XE::StencilOperation val )
{
	_StencilFrontPassOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilFrontDepthFailOp() const
{
	return _StencilFrontDepthFailOp;
}

void XE::DepthStencilState::SetStencilFrontDepthFailOp( XE::StencilOperation val )
{
	_StencilFrontDepthFailOp = val;
}

XE::CompareType XE::DepthStencilState::GetStencilBackFunc() const
{
	return _StencilBackFunc;
}

void XE::DepthStencilState::SetStencilBackFunc( XE::CompareType val )
{
	_StencilBackFunc = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilBackFailOp() const
{
	return _StencilBackFailOp;
}

void XE::DepthStencilState::SetStencilBackFailOp( XE::StencilOperation val )
{
	_StencilBackFailOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilBackPassOp() const
{
	return _StencilBackPassOp;
}

void XE::DepthStencilState::SetStencilBackPassOp( XE::StencilOperation val )
{
	_StencilBackPassOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilBackDepthFailOp() const
{
	return _StencilBackDepthFailOp;
}

void XE::DepthStencilState::SetStencilBackDepthFailOp( XE::StencilOperation val )
{
	_StencilBackDepthFailOp = val;
}

BEG_META( PipelineState )
END_META()

XE::PipelineState::PipelineState()
{

}

XE::PipelineState::~PipelineState()
{

}

XE::PipelineStateHandle XE::PipelineState::GetHandle() const
{
	return _Handle;
}

void XE::PipelineState::SetHandle( PipelineStateHandle val )
{
	_Handle = val;
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

XE::HullShaderPtr XE::GraphicsPipelineState::GetHS() const
{
	return _HS;
}

void XE::GraphicsPipelineState::SetHS( XE::HullShaderPtr val )
{
	_HS = val;
}

XE::PixelShaderPtr XE::GraphicsPipelineState::GetPS() const
{
	return _PS;
}

void XE::GraphicsPipelineState::SetPS( XE::PixelShaderPtr val )
{
	_PS = val;
}

XE::VertexShaderPtr XE::GraphicsPipelineState::GetVS() const
{
	return _VS;
}

void XE::GraphicsPipelineState::SetVS( XE::VertexShaderPtr val )
{
	_VS = val;
}

XE::DomainShaderPtr XE::GraphicsPipelineState::GetDS() const
{
	return _DS;
}

void XE::GraphicsPipelineState::SetDS( XE::DomainShaderPtr val )
{
	_DS = val;
}

XE::GeometryShaderPtr XE::GraphicsPipelineState::GetGS() const
{
	return _GS;
}

void XE::GraphicsPipelineState::SetGS( XE::GeometryShaderPtr val )
{
	_GS = val;
}

XE::BlendStatePtr XE::GraphicsPipelineState::GetBlendState() const
{
	return _BlendState;
}

void XE::GraphicsPipelineState::SetBlendState( XE::BlendStatePtr val )
{
	_BlendState = val;
}

XE::RasterizerStatePtr XE::GraphicsPipelineState::GetRasterizerState() const
{
	return _RasterizerState;
}

void XE::GraphicsPipelineState::SetRasterizerState( XE::RasterizerStatePtr val )
{
	_RasterizerState = val;
}

XE::DepthStencilStatePtr XE::GraphicsPipelineState::GetDepthStencilState() const
{
	return _DepthStencilState;
}

void XE::GraphicsPipelineState::SetDepthStencilState( XE::DepthStencilStatePtr val )
{
	_DepthStencilState = val;
}

XE::InputLayoutPtr XE::GraphicsPipelineState::GetInputLayout() const
{
	return _InputLayout;
}

void XE::GraphicsPipelineState::SetInputLayout( XE::InputLayoutPtr val )
{
	_InputLayout = val;
}

XE::TopologyType XE::GraphicsPipelineState::GetPrimitiveTopology() const
{
	return _PrimitiveTopology;
}

void XE::GraphicsPipelineState::SetPrimitiveTopology( XE::TopologyType val )
{
	_PrimitiveTopology = val;
}

XE::uint32 XE::GraphicsPipelineState::GetSampleMask() const
{
	return _SampleMask;
}

void XE::GraphicsPipelineState::SetSampleMask( XE::uint32 val )
{
	_SampleMask = val;
}

XE::uint64 XE::GraphicsPipelineState::GetRenderTargetFormatCount() const
{
	return _RenderTargetCount;
}

void XE::GraphicsPipelineState::SetRenderTargetFormatCount( XE::uint64 val )
{
	_RenderTargetCount = val;
}

XE::TextureFormat XE::GraphicsPipelineState::GetRenderTargetFormat( XE::uint64 index ) const
{
	return _RenderTargetFmt[index];
}

void XE::GraphicsPipelineState::SetRenderTargetFormat( XE::uint64 index, TextureFormat val )
{
	_RenderTargetFmt[index] = val;
}

XE::TextureFormat XE::GraphicsPipelineState::GetDepthStencilFormat() const
{
	return _DepthStencilFmt;
}

void XE::GraphicsPipelineState::SetDepthStencilFormat( TextureFormat val )
{
	_DepthStencilFmt = val;
}
