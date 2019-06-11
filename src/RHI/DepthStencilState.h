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

class RHI_API DepthStencilState : public std::enable_shared_from_this<DepthStencilState>
{
	OBJECT(DepthStencilState)

public:
	DepthStencilState();

	~DepthStencilState();

public:
	bool GetDepthEnable() const;

	void SetDepthEnable(bool val);

	bool GetDepthWriteEnable() const;

	void SetDepthWriteEnable(bool val);

	XE::CompareType GetDepthFunc() const;

	void SetDepthFunc(XE::CompareType val);

	bool GetStencilEnable() const;

	void SetStencilEnable(bool val);

	XE::uint8 GetStencilReadMask() const;

	void SetStencilReadMask(XE::uint8 val);

	XE::uint8 GetStencilWriteMask() const;

	void SetStencilWriteMask(XE::uint8 val);

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

END_XE_NAMESPACE

#endif // __DEPTHSTENCILSTATE_H__A830F9AA_F350_4085_B15B_11ADC272BF77
