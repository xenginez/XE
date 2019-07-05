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

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API BlendState : public std::enable_shared_from_this<BlendState>
{
	OBJECT( BlendState )

public:
	BlendState();

	~BlendState();

public:
	Vec4 GetBlendFactor() const;

	void SetBlendFactor( const Vec4 & val );

	bool GetEnableIndependentBlend() const;

	void SetEnableIndependentBlend( bool val );

	bool GetAlphaToCoverageEnabled() const;

	void SetAlphaToCoverageEnabled( bool val );

	XE::uint64 GetRenderTargetCount() const;

	RenderTargetPtr GetRenderTarget( XE::uint64 index ) const;

	void SetRenderTarget( XE::uint64 index, const RenderTargetPtr & val );

private:
	Vec4 _BlendFactor;
	bool _EnableIndependentBlend;
	bool _AlphaToCoverageEnabled;
	Array < RenderTargetPtr > _RenderTargets;
};

class RHI_API RasterizerState : public std::enable_shared_from_this<RasterizerState>
{
	OBJECT( RasterizerState )

public:
	RasterizerState();

	~RasterizerState();

public:
	XE::FillType GetFillMode() const;

	void SetFillMode( XE::FillType val );

	XE::CullType GetCullMode() const;

	void SetCullMode( XE::CullType val );

	bool GetFrontCountClockwise() const;

	void SetFrontCountClockwise( bool val );

	bool GetDepthClipEnable() const;

	void SetDepthClipEnable( bool val );

	bool GetScissorEnable() const;

	void SetScissorEnable( bool val );

	bool GetAntialiasedLineEnable() const;

	void SetAntialiasedLineEnable( bool val );

	XE::int32 GetDepthBias() const;

	void SetDepthBias( XE::int32 val );

	XE::real GetDepthBiasClamp() const;

	void SetDepthBiasClamp( XE::real val );

	XE::real GetSlopeSacleDepthBias() const;

	void SetSlopeSacleDepthBias( XE::real val );

private:
	FillType _FillMode;
	CullType _CullMode;
	bool _FrontCountClockwise;
	bool _DepthClipEnable;
	bool _ScissorEnable;
	bool _AntialiasedLineEnable;
	XE::int32 _DepthBias;
	XE::real _DepthBiasClamp;
	XE::real _SlopeSacleDepthBias;
};

class RHI_API DepthStencilState : public std::enable_shared_from_this<DepthStencilState>
{
	OBJECT( DepthStencilState )

public:
	DepthStencilState();

	~DepthStencilState();

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

class RHI_API ComputePipelineState : public std::enable_shared_from_this<ComputePipelineState>
{
	OBJECT( ComputePipelineState )

public:
	ComputePipelineState();

	~ComputePipelineState();

public:
	ComputeShaderPtr GetComputeShader() const;

	void SetComputeShader( ComputeShaderPtr val );

private:
	ComputeShaderPtr _CS;
	PipelineStateHandle _Handle;
};

class RHI_API GraphicsPipelineState : public std::enable_shared_from_this<GraphicsPipelineState>
{
	OBJECT( GraphicsPipelineState )

public:
	GraphicsPipelineState();

	~GraphicsPipelineState();

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

	FrameBufferPtr GetFrameBuffer() const;

	void SetFrameBuffer( const FrameBufferPtr & val );

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

	FrameBufferPtr _FBO;
	PipelineStateHandle _Handle;
};

END_XE_NAMESPACE

#endif // PIPELINESTATE_H__9370F22B_2DBA_453B_AC42_68E23F3A5B09
