#include "DepthStencilState.h"

USING_XE

BEG_META(DepthStencilState)
END_META()

XE::DepthStencilState::DepthStencilState()
{

}

DepthStencilState::~DepthStencilState()
{
	
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

XE::CompareType XE::DepthStencilState::GetStencilFrontFunc() const
{
	return _StencilFrontFunc;
}

void XE::DepthStencilState::SetStencilFrontFunc(XE::CompareType val)
{
	_StencilFrontFunc = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilFrontFailOp() const
{
	return _StencilFrontFailOp;
}

void XE::DepthStencilState::SetStencilFrontFailOp(XE::StencilOperation val)
{
	_StencilFrontFailOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilFrontPassOp() const
{
	return _StencilFrontPassOp;
}

void XE::DepthStencilState::SetStencilFrontPassOp(XE::StencilOperation val)
{
	_StencilFrontPassOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilFrontDepthFailOp() const
{
	return _StencilFrontDepthFailOp;
}

void XE::DepthStencilState::SetStencilFrontDepthFailOp(XE::StencilOperation val)
{
	_StencilFrontDepthFailOp = val;
}


XE::CompareType XE::DepthStencilState::GetStencilBackFunc() const
{
	return _StencilBackFunc;
}

void XE::DepthStencilState::SetStencilBackFunc(XE::CompareType val)
{
	_StencilBackFunc = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilBackFailOp() const
{
	return _StencilBackFailOp;
}

void XE::DepthStencilState::SetStencilBackFailOp(XE::StencilOperation val)
{
	_StencilBackFailOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilBackPassOp() const
{
	return _StencilBackPassOp;
}

void XE::DepthStencilState::SetStencilBackPassOp(XE::StencilOperation val)
{
	_StencilBackPassOp = val;
}

XE::StencilOperation XE::DepthStencilState::GetStencilBackDepthFailOp() const
{
	return _StencilBackDepthFailOp;
}

void XE::DepthStencilState::SetStencilBackDepthFailOp(XE::StencilOperation val)
{
	_StencilBackDepthFailOp = val;
}
