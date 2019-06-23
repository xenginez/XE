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
	OBJECT(Sampler, Resource)
	
public:
	Sampler();
	
	~Sampler() override;

public:
	SamplerFilter getMinFilter() const;
	
	void setMinFilter( SamplerFilter val );
	
	SamplerFilter getMagFilter() const;
	
	void setMagFilter( SamplerFilter val );
	
	SamplerFilter getMipFilter() const;
	
	void setMipFilter( SamplerFilter val );
	
	SamplerAddressType getAddressU() const;
	
	void setAddressU( SamplerAddressType val );
	
	SamplerAddressType getAddressV() const;
	
	void setAddressV( SamplerAddressType val );
	
	SamplerAddressType getAddressW() const;
	
	void setAddressW( SamplerAddressType val );
	
	XE::real getMipLodBias() const;
	
	void setMipLodBias( XE::real val );
	
	XE::uint32 getMaxAnisotropy() const;
	
	void setMaxAnisotropy( XE::uint32 val );
	
	CompareType getComparisonFunc() const;
	
	void setComparisonFunc( CompareType val );
	
	const XE::real * getBorderColor() const;
	
	XE::real getMinLOD() const;
	
	void setMinLOD( XE::real val );
	
	XE::real getMaxLOD() const;
	
	void setMaxLOD( XE::real val );

private:
	SamplerFilter _MinFilter;
	SamplerFilter _MagFilter;
	SamplerFilter _MipFilter;
	
	SamplerAddressType _AddressU;
	SamplerAddressType _AddressV;
	SamplerAddressType _AddressW;
	
	XE::real _MipLODBias;
	XE::uint32 _MaxAnisotropy;
	CompareType _ComparisonFunc;
	
	XE::real _BorderColor[4];
	
	XE::real _MinLOD;
	XE::real _MaxLOD;
};

END_XE_NAMESPACE

#endif //__SAMPLER_H__8CA19C8D_274C_4E0D_93A6_2447A8E1759E
