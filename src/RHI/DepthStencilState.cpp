#include "DepthStencilState.h"

USING_XE

BEG_META(DepthStencilState)
END_META()

XE::DepthStencilState::DepthStencilState()
{

}

XE::DepthStencilStateHandle XE::DepthStencilState::GetHandle() const
{
	return _Handle;
}

bool XE::DepthStencilState::GetDepthEnable() const
{
	return _DepthEnable;
}

void XE::DepthStencilState::SetDepthEnable(bool val)
{
	_DepthEnable = val;
}

bool XE::DepthStencilState::GetDepthWriteEnable() const
{
	return _DepthWriteEnable;
}

void XE::DepthStencilState::SetDepthWriteEnable(bool val)
{
	_DepthWriteEnable = val;
}

XE::CompareType XE::DepthStencilState::GetDepthFunc() const
{
	return _DepthFunc;
}

void XE::DepthStencilState::SetDepthFunc(XE::CompareType val)
{
	_DepthFunc = val;
}

bool XE::DepthStencilState::GetStencilEnable() const
{
	return _StencilEnable;
}

void XE::DepthStencilState::SetStencilEnable(bool val)
{
	_StencilEnable = val;
}

uint8 XE::DepthStencilState::GetStencilReadMask() const
{
	return _StencilReadMask;
}

void XE::DepthStencilState::SetStencilReadMask(uint8 val)
{
	_StencilReadMask = val;
}

uint8 XE::DepthStencilState::GetStencilWriteMask() const
{
	return _StencilWriteMask;
}

void XE::DepthStencilState::SetStencilWriteMask(uint8 val)
{
	_StencilWriteMask = val;
}

XE::CompareType XE::DepthStencilState::GetStencilFunc() const
{
	return _StencilFunc;
}

void XE::DepthStencilState::SetStencilFunc(XE::CompareType val)
{
	_StencilFunc = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilFailOp() const
{
	return _StencilFailOp;
}

void XE::DepthStencilState::SetStencilFailOp(XE::StencilOperation val)
{
	_StencilFailOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilPassOp() const
{
	return _StencilPassOp;
}

void XE::DepthStencilState::SetStencilPassOp(XE::StencilOperation val)
{
	_StencilPassOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilDepthFailOp() const
{
	return _StencilDepthFailOp;
}

void XE::DepthStencilState::SetStencilDepthFailOp(XE::StencilOperation val)
{
	_StencilDepthFailOp = val;
}
