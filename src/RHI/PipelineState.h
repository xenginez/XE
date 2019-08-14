/*!
 * \file	PipelineState.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/05
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef PIPELINESTATE_H__9370F22B_2DBA_453B_AC42_68E23F3A5B09
#define PIPELINESTATE_H__9370F22B_2DBA_453B_AC42_68E23F3A5B09

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API BlendState : public XE::Object
{
	OBJECT( BlendState, Object )

public:
	BlendState();

	~BlendState() override;

public:
	bool GetEnableIndependentBlend() const;

	void SetEnableIndependentBlend( bool val );

	bool GetAlphaToCoverageEnabled() const;

	void SetAlphaToCoverageEnabled( bool val );

private:
	PipelineStateHandle _Handle;
	bool _EnableIndependentBlend;
	bool _AlphaToCoverageEnabled;
};

class RHI_API RasterizerState : public XE::Object
{
	OBJECT( RasterizerState, Object )

public:
	RasterizerState();

	~RasterizerState() override;

public:
	XE::FillType GetFillMode() const;

	void SetFillMode( XE::FillType val );

	XE::CullType GetCullMode() const;

	void SetCullMode( XE::CullType val );

	bool GetFrontCountClockwise() const;

	void SetFrontCountClockwise( bool val );

	XE::int32 GetDepthBias() const;

	void SetDepthBias( XE::int32 val );

	XE::real GetDepthBiasClamp() const;

	void SetDepthBiasClamp( XE::real val );

	XE::real GetSlopeSacleDepthBias() const;

	void SetSlopeSacleDepthBias( XE::real val );

	bool GetDepthClipEnable() const;

	void SetDepthClipEnable( bool val );

	bool GetMultisampleEnable() const;

	void SetMultisampleEnable( bool val );

	bool GetAntialiasedLineEnable() const;

	void SetAntialiasedLineEnable( bool val );

	XE::uint32 GetForcedSampleCount() const;

	void SetForcedSampleCount( XE::uint32 val );

	bool GetConservativeRaster() const;

	void SetConservativeRaster( bool val );

private:
	FillType _FillMode;
	CullType _CullMode;
	bool _FrontCountClockwise;
	XE::int32 _DepthBias;
	XE::real _DepthBiasClamp;
	XE::real _SlopeSacleDepthBias;
	bool _DepthClipEnable;
	bool _MultisampleEnable;
	bool _AntialiasedLineEnable;
	XE::uint32 _ForcedSampleCount;
	bool _ConservativeRaster;
};

class RHI_API DepthStencilState : public XE::Object
{
	OBJECT( DepthStencilState, Object )

public:
	DepthStencilState();

	~DepthStencilState() override;

public:
	bool GetDepthEnable() const;

	void SetDepthEnable( bool val );

	bool GetDepthWriteEnable() const;

	void SetDepthWriteEnable( bool val );

	XE::CompareType GetDepthFunc() const;

	void SetDepthFunc( XE::CompareType val );

	bool GetStencilEnable() const;

	void SetStencilEnable( bool val );

	XE::uint8 GetStencilReadMask() const;

	void SetStencilReadMask( XE::uint8 val );

	XE::uint8 GetStencilWriteMask() const;

	void SetStencilWriteMask( XE::uint8 val );

	XE::CompareType GetStencilFrontFunc() const;

	void SetStencilFrontFunc( XE::CompareType val );

	XE::StencilOperation GetStencilFrontFailOp() const;

	void SetStencilFrontFailOp( XE::StencilOperation val );

	XE::StencilOperation GetStencilFrontPassOp() const;

	void SetStencilFrontPassOp( XE::StencilOperation val );

	XE::StencilOperation GetStencilFrontDepthFailOp() const;

	void SetStencilFrontDepthFailOp( XE::StencilOperation val );

	XE::CompareType GetStencilBackFunc() const;

	void SetStencilBackFunc( XE::CompareType val );

	XE::StencilOperation GetStencilBackFailOp() const;

	void SetStencilBackFailOp( XE::StencilOperation val );

	XE::StencilOperation GetStencilBackPassOp() const;

	void SetStencilBackPassOp( XE::StencilOperation val );

	XE::StencilOperation GetStencilBackDepthFailOp() const;

	void SetStencilBackDepthFailOp( XE::StencilOperation val );

private:
	bool _DepthEnable;
	bool _DepthWriteEnable;
	CompareType _DepthFunc;
	bool _StencilEnable;
	XE::uint8 _StencilReadMask;
	XE::uint8 _StencilWriteMask;

	CompareType _StencilFrontFunc;
	StencilOperation _StencilFrontFailOp;
	StencilOperation _StencilFrontPassOp;
	StencilOperation _StencilFrontDepthFailOp;

	CompareType _StencilBackFunc;
	StencilOperation _StencilBackFailOp;
	StencilOperation _StencilBackPassOp;
	StencilOperation _StencilBackDepthFailOp;
};

class RHI_API PipelineState : public XE::Object
{
	OBJECT( PipelineState, Object )

public:
	PipelineState();

	~PipelineState() override;

public:
	virtual void Startup( RenderContextRPtr context ) = 0;

	virtual void Clearup( RenderContextRPtr context ) = 0;

public:
	PipelineStateHandle GetHandle() const;

	void SetHandle( PipelineStateHandle val );

private:
	PipelineStateHandle _Handle;
};

class RHI_API ComputePipelineState : public PipelineState
{
	OBJECT( ComputePipelineState, PipelineState )

public:
	ComputePipelineState();

	~ComputePipelineState() override;

public:
	ComputeShaderPtr GetComputeShader() const;

	void SetComputeShader( ComputeShaderPtr val );

private:
	ComputeShaderPtr _CS;
};

class RHI_API GraphicsPipelineState : public PipelineState
{
	OBJECT( GraphicsPipelineState, PipelineState )

public:
	GraphicsPipelineState();

	~GraphicsPipelineState() override;

private:
	XE::HullShaderPtr GetHS() const;

	void SetHS( XE::HullShaderPtr val );

	XE::PixelShaderPtr GetPS() const;

	void SetPS( XE::PixelShaderPtr val );

	XE::VertexShaderPtr GetVS() const;

	void SetVS( XE::VertexShaderPtr val );

	XE::DomainShaderPtr GetDS() const;

	void SetDS( XE::DomainShaderPtr val );

	XE::GeometryShaderPtr GetGS() const;

	void SetGS( XE::GeometryShaderPtr val );

	XE::BlendStatePtr GetBlendState() const;

	void SetBlendState( XE::BlendStatePtr val );

	XE::RasterizerStatePtr GetRasterizerState() const;

	void SetRasterizerState( XE::RasterizerStatePtr val );

	XE::DepthStencilStatePtr GetDepthStencilState() const;

	void SetDepthStencilState( XE::DepthStencilStatePtr val );

	XE::InputLayoutPtr GetInputLayout() const;

	void SetInputLayout( XE::InputLayoutPtr val );

	XE::TopologyType GetPrimitiveTopology() const;

	void SetPrimitiveTopology( XE::TopologyType val );

	XE::uint32 GetSampleMask() const;

	void SetSampleMask( XE::uint32 val );

public:
	XE::uint64 GetRenderTargetFormatCount() const;

	void SetRenderTargetFormatCount( XE::uint64 val );

	TextureFormat GetRenderTargetFormat( XE::uint64 index ) const;

	void SetRenderTargetFormat( XE::uint64 index, TextureFormat val );

	TextureFormat GetDepthStencilFormat() const;

	void SetDepthStencilFormat( TextureFormat val );

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

	XE::uint32 _SampleMask;
	StripCutValue _IBStripCutValue;

	XE::uint64 _RenderTargetCount;
	TextureFormat _DepthStencilFmt;
	TextureFormat _RenderTargetFmt[8];
};

END_XE_NAMESPACE

#endif // PIPELINESTATE_H__9370F22B_2DBA_453B_AC42_68E23F3A5B09
