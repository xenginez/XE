/*!
 * \file    Sampler.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-25
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SAMPLER_H__8CA19C8D_274C_4E0D_93A6_2447A8E1759E
#define __SAMPLER_H__8CA19C8D_274C_4E0D_93A6_2447A8E1759E

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Sampler : public Resource
{
	OBJECT( Sampler )
	
public:
	Sampler();
	
	~Sampler() override;

public:
	SamplerFilter GetMinFilter() const;
	
	void SetMinFilter( SamplerFilter val );
	
	SamplerFilter GetMagFilter() const;
	
	void SetMagFilter( SamplerFilter val );
	
	SamplerFilter GetMipFilter() const;
	
	void SetMipFilter( SamplerFilter val );
	
	SamplerAddressType GetAddressU() const;
	
	void SetAddressU( SamplerAddressType val );
	
	SamplerAddressType GetAddressV() const;
	
	void SetAddressV( SamplerAddressType val );
	
	SamplerAddressType GetAddressW() const;
	
	void SetAddressW( SamplerAddressType val );
	
	XE::float32 GetMipLodBias() const;
	
	void SetMipLodBias( XE::float32 val );
	
	XE::uint32 GetMaxAnisotropy() const;
	
	void SetMaxAnisotropy( XE::uint32 val );
	
	CompareType GetComparisonFunc() const;
	
	void SetComparisonFunc( CompareType val );
	
	const XE::float32 * GetBorderColor() const;
	
	XE::float32 GetMinLOD() const;
	
	void SetMinLOD( XE::float32 val );
	
	XE::float32 GetMaxLOD() const;
	
	void SetMaxLOD( XE::float32 val );

private:
	SamplerFilter _MinFilter;
	SamplerFilter _MagFilter;
	SamplerFilter _MipFilter;
	
	SamplerAddressType _AddressU;
	SamplerAddressType _AddressV;
	SamplerAddressType _AddressW;
	
	XE::float32 _MipLODBias;
	XE::uint32 _MaxAnisotropy;
	CompareType _ComparisonFunc;
	
	XE::float32 _BorderColor[4];
	
	XE::float32 _MinLOD;
	XE::float32 _MaxLOD;
};

END_XE_NAMESPACE

#endif //__SAMPLER_H__8CA19C8D_274C_4E0D_93A6_2447A8E1759E
