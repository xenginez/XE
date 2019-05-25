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

	XE::CompareType GetStencilFunc() const;

	void SetStencilFunc(XE::CompareType val);

	XE::StencilOperation GetStencilFailOp() const;

	void SetStencilFailOp(XE::StencilOperation val);

	XE::StencilOperation GetStencilPassOp() const;

	void SetStencilPassOp(XE::StencilOperation val);

	XE::StencilOperation GetStencilDepthFailOp() const;

	void SetStencilDepthFailOp(XE::StencilOperation val);

private:
	DepthStencilStateHandle _Handle;

	bool _DepthEnable;
	bool _DepthWriteEnable;
	CompareType _DepthFunc;
	bool _StencilEnable;
	uint8 _StencilReadMask;
	uint8 _StencilWriteMask;
	CompareType _StencilFunc;
	StencilOperation _StencilFailOp;
	StencilOperation _StencilPassOp;
	StencilOperation _StencilDepthFailOp;
};

END_XE_NAMESAPCE

#endif // __DEPTHSTENCILSTATE_H__A830F9AA_F350_4085_B15B_11ADC272BF77
