/*!
 * \file   RasterizerState.h
 *
 * \author ZhengYuanQing
 * \date   2019/05/25
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RASTERIZERSTATE_H__C2B1E039_97FC_4403_98A3_FF59FD08787C
#define __RASTERIZERSTATE_H__C2B1E039_97FC_4403_98A3_FF59FD08787C

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API RasterizerState : public std::enable_shared_from_this<RasterizerState>
{
	OBJECT(RasterizerState)

public:
	RasterizerState();

	~RasterizerState();

public:
	XE::FillType GetFillMode() const;

	void SetFillMode(XE::FillType val);

	XE::CullType GetCullMode() const;

	void SetCullMode(XE::CullType val);

	bool GetFrontCountClockwise() const;

	void SetFrontCountClockwise(bool val);

	bool GetDepthClipEnable() const;

	void SetDepthClipEnable(bool val);

	bool GetScissorEnable() const;

	void SetScissorEnable(bool val);

	bool GetAntialiasedLineEnable() const;

	void SetAntialiasedLineEnable(bool val);

	int32 GetDepthBias() const;

	void SetDepthBias(int32 val);

	XE::float32 GetDepthBiasClamp() const;

	void SetDepthBiasClamp(XE::float32 val);

	XE::float32 GetSlopeSacleDepthBias() const;

	void SetSlopeSacleDepthBias(XE::float32 val);

private:
	FillType _FillMode;
	CullType _CullMode;
	bool _FrontCountClockwise;
	bool _DepthClipEnable;
	bool _ScissorEnable;
	bool _AntialiasedLineEnable;
	int32 _DepthBias;
	XE::float32 _DepthBiasClamp;
	XE::float32 _SlopeSacleDepthBias;
};

END_XE_NAMESPACE

#endif // __RASTERIZERSTATE_H__C2B1E039_97FC_4403_98A3_FF59FD08787C
