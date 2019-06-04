/*!
 * \file   DepthStencilState.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __DEPTHSTENCILSTATE_H__A830F9AA_F350_4085_B15B_11ADC272BF77
#define __DEPTHSTENCILSTATE_H__A830F9AA_F350_4085_B15B_11ADC272BF77

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API DepthStencilState : public Resource
{
	OBJECT(DepthStencilState, Resource)

public:
	DepthStencilState();

public:
	XE::DepthStencilStateHandle GetHandle() const;

public:
	bool GetDepthEnable() const;

	void SetDepthEnable(bool val);

	bool GetDepthWriteEnable() const;

	void SetDepthWriteEnable(bool val);

	XE::CompareType GetDepthFunc() const;

	void SetDepthFunc(XE::CompareType val);

	bool GetStencilEnable() const;

	void SetStencilEnable(bool val);

	uint8 GetStencilReadMask() const;

	void SetStencilReadMask(uint8 val);

	uint8 GetStencilWriteMask() const;

	void SetStencilWriteMask(uint8 val);

	XE::CompareType GetStencilFrontFunc() const;

	void SetStencilFrontFunc(XE::CompareType val);

	XE::StencilOperation GetStencilFrontFailOp() const;

	void SetStencilFrontFailOp(XE::StencilOperation val);

	XE::StencilOperation GetStencilFrontPassOp() const;

	void SetStencilFrontPassOp(XE::StencilOperation val);

	XE::StencilOperation GetStencilFrontDepthFailOp() const;

	void SetStencilFrontDepthFailOp(XE::StencilOperation val);

	XE::CompareType GetStencilBackFunc() const;

	void SetStencilBackFunc(XE::CompareType val);

	XE::StencilOperation GetStencilBackFailOp() const;

	void SetStencilBackFailOp(XE::StencilOperation val);

	XE::StencilOperation GetStencilBackPassOp() const;

	void SetStencilBackPassOp(XE::StencilOperation val);

	XE::StencilOperation GetStencilBackDepthFailOp() const;

	void SetStencilBackDepthFailOp(XE::StencilOperation val);

private:
	DepthStencilStateHandle _Handle;

	bool _DepthEnable;
	bool _DepthWriteEnable;
	CompareType _DepthFunc;
	bool _StencilEnable;
	uint8 _StencilReadMask;
	uint8 _StencilWriteMask;

	CompareType _StencilFrontFunc;
	StencilOperation _StencilFrontFailOp;
	StencilOperation _StencilFrontPassOp;
	StencilOperation _StencilFrontDepthFailOp;

	CompareType _StencilBackFunc;
	StencilOperation _StencilBackFailOp;
	StencilOperation _StencilBackPassOp;
	StencilOperation _StencilBackDepthFailOp;
};

END_XE_NAMESPACE

#endif // __DEPTHSTENCILSTATE_H__A830F9AA_F350_4085_B15B_11ADC272BF77
