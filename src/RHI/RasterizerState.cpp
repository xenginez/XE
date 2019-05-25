#include "RasterizerState.h"

USING_XE

BEG_META(RasterizerState)
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

void XE::RasterizerState::SetFillMode(XE::FillType val)
{
	_FillMode = val;
}

XE::CullType XE::RasterizerState::GetCullMode() const
{
	return _CullMode;
}

void XE::RasterizerState::SetCullMode(XE::CullType val)
{
	_CullMode = val;
}

bool XE::RasterizerState::GetFrontCountClockwise() const
{
	return _FrontCountClockwise;
}

void XE::RasterizerState::SetFrontCountClockwise(bool val)
{
	_FrontCountClockwise = val;
}

bool XE::RasterizerState::GetDepthClipEnable() const
{
	return _DepthClipEnable;
}

void XE::RasterizerState::SetDepthClipEnable(bool val)
{
	_DepthClipEnable = val;
}

bool XE::RasterizerState::GetScissorEnable() const
{
	return _ScissorEnable;
}

void XE::RasterizerState::SetScissorEnable(bool val)
{
	_ScissorEnable = val;
}

bool XE::RasterizerState::GetAntialiasedLineEnable() const
{
	return _AntialiasedLineEnable;
}

void XE::RasterizerState::SetAntialiasedLineEnable(bool val)
{
	_AntialiasedLineEnable = val;
}

int32 XE::RasterizerState::GetDepthBias() const
{
	return _DepthBias;
}

void XE::RasterizerState::SetDepthBias(int32 val)
{
	_DepthBias = val;
}

float XE::RasterizerState::GetDepthBiasClamp() const
{
	return _DepthBiasClamp;
}

void XE::RasterizerState::SetDepthBiasClamp(float val)
{
	_DepthBiasClamp = val;
}

float XE::RasterizerState::GetSlopeSacleDepthBias() const
{
	return _SlopeSacleDepthBias;
}

void XE::RasterizerState::SetSlopeSacleDepthBias(float val)
{
	_SlopeSacleDepthBias = val;
}
