#include "GraphicsPipelineState.h"

USING_XE

BEG_META(GraphicsPipelineState)
END_META()

XE::GraphicsPipelineState::GraphicsPipelineState()
{

}

XE::GraphicsPipelineState::~GraphicsPipelineState()
{

}

XE::GraphicsPipelineStateHandle XE::GraphicsPipelineState::GetHandle() const
{
	return _Handle;
}

XE::HullShaderPtr XE::GraphicsPipelineState::GetHS() const
{
	return _HS;
}

void XE::GraphicsPipelineState::SetHS(XE::HullShaderPtr val)
{
	_HS = val;
}

XE::PixelShaderPtr XE::GraphicsPipelineState::GetPS() const
{
	return _PS;
}

void XE::GraphicsPipelineState::SetPS(XE::PixelShaderPtr val)
{
	_PS = val;
}

XE::VertexShaderPtr XE::GraphicsPipelineState::GetVS() const
{
	return _VS;
}

void XE::GraphicsPipelineState::SetVS(XE::VertexShaderPtr val)
{
	_VS = val;
}

XE::DomainShaderPtr XE::GraphicsPipelineState::GetDS() const
{
	return _DS;
}

void XE::GraphicsPipelineState::SetDS(XE::DomainShaderPtr val)
{
	_DS = val;
}

XE::GeometryShaderPtr XE::GraphicsPipelineState::GetGS() const
{
	return _GS;
}

void XE::GraphicsPipelineState::SetGS(XE::GeometryShaderPtr val)
{
	_GS = val;
}

XE::BlendStatePtr XE::GraphicsPipelineState::GetBlendState() const
{
	return _BlendState;
}

void XE::GraphicsPipelineState::SetBlendState(XE::BlendStatePtr val)
{
	_BlendState = val;
}

XE::RasterizerStatePtr XE::GraphicsPipelineState::GetRasterizerState() const
{
	return _RasterizerState;
}

void XE::GraphicsPipelineState::SetRasterizerState(XE::RasterizerStatePtr val)
{
	_RasterizerState = val;
}

XE::DepthStencilStatePtr XE::GraphicsPipelineState::GetDepthStencilState() const
{
	return _DepthStencilState;
}

void XE::GraphicsPipelineState::SetDepthStencilState(XE::DepthStencilStatePtr val)
{
	_DepthStencilState = val;
}

XE::InputLayoutPtr XE::GraphicsPipelineState::GetInputLayout() const
{
	return _InputLayout;
}

void XE::GraphicsPipelineState::SetInputLayout(XE::InputLayoutPtr val)
{
	_InputLayout = val;
}

XE::TopologyType XE::GraphicsPipelineState::GetPrimitiveTopology() const
{
	return _PrimitiveTopology;
}

void XE::GraphicsPipelineState::SetPrimitiveTopology(XE::TopologyType val)
{
	_PrimitiveTopology = val;
}

XE::TextureFormat XE::GraphicsPipelineState::GetRenderTargetFormat() const
{
	return _RenderTargetFormat;
}

void XE::GraphicsPipelineState::SetRenderTargetFormat(XE::TextureFormat val)
{
	_RenderTargetFormat = val;
}

XE::TextureFormat XE::GraphicsPipelineState::GetDepthStencilFormat() const
{
	return _DepthStencilFormat;
}

void XE::GraphicsPipelineState::SetDepthStencilFormat(XE::TextureFormat val)
{
	_DepthStencilFormat = val;
}

uint32 XE::GraphicsPipelineState::GetSampleMask() const
{
	return _SampleMask;
}

void XE::GraphicsPipelineState::SetSampleMask(uint32 val)
{
	_SampleMask = val;
}

uint8 XE::GraphicsPipelineState::GetSampleCount() const
{
	return _SampleCount;
}

void XE::GraphicsPipelineState::SetSampleCount(uint8 val)
{
	_SampleCount = val;
}

uint8 XE::GraphicsPipelineState::GetSampleQuality() const
{
	return _SampleQuality;
}

void XE::GraphicsPipelineState::SetSampleQuality(uint8 val)
{
	_SampleQuality = val;
}
