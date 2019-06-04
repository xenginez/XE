/*!
 * \file   GraphicsPipelineState.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GRAPHICSPIPELINESTATE_H__4F61BE78_59DE_486D_8F6D_C9782B5B65B0
#define __GRAPHICSPIPELINESTATE_H__4F61BE78_59DE_486D_8F6D_C9782B5B65B0

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API GraphicsPipelineState : public Resource
{
	OBJECT(GraphicsPipelineState, Resource)

public:
	GraphicsPipelineState();

	~GraphicsPipelineState() override;

public:
	GraphicsPipelineStateHandle GetHandle() const;

private:
	XE::HullShaderPtr GetHS() const;

	void SetHS(XE::HullShaderPtr val);

	XE::PixelShaderPtr GetPS() const;

	void SetPS(XE::PixelShaderPtr val);

	XE::VertexShaderPtr GetVS() const;

	void SetVS(XE::VertexShaderPtr val);

	XE::DomainShaderPtr GetDS() const;

	void SetDS(XE::DomainShaderPtr val);

	XE::GeometryShaderPtr GetGS() const;

	void SetGS(XE::GeometryShaderPtr val);

	XE::BlendStatePtr GetBlendState() const;

	void SetBlendState(XE::BlendStatePtr val);

	XE::RasterizerStatePtr GetRasterizerState() const;

	void SetRasterizerState(XE::RasterizerStatePtr val);

	XE::DepthStencilStatePtr GetDepthStencilState() const;

	void SetDepthStencilState(XE::DepthStencilStatePtr val);

	XE::InputLayoutPtr GetInputLayout() const;

	void SetInputLayout(XE::InputLayoutPtr val);

	XE::TopologyType GetPrimitiveTopology() const;

	void SetPrimitiveTopology(XE::TopologyType val);

	uint32 GetSampleMask() const;

	void SetSampleMask(uint32 val);

	FrameBufferPtr GetFrameBuffer() const;

	void SetFrameBuffer(const FrameBufferPtr &val);

private:
	HullShaderPtr _HS;
	PixelShaderPtr _PS;
	VertexShaderPtr _VS;
	DomainShaderPtr _DS;
	GeometryShaderPtr _GS;

	BlendStatePtr _BlendState;
	RasterizerStatePtr _RasterizerState;
	DepthStencilStatePtr _DepthStencilState;

	InputLayoutPtr _InputLayout;
	TopologyType _PrimitiveTopology;

	uint32 _SampleMask;

	FrameBufferPtr _FBO;

	GraphicsPipelineStateHandle _Handle;
};

END_XE_NAMESPACE

#endif // __GRAPHICSPIPELINESTATE_H__4F61BE78_59DE_486D_8F6D_C9782B5B65B0
