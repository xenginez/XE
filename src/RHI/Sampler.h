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
	
	XE::float32 getMipLodBias() const;
	
	void setMipLodBias( XE::float32 val );
	
	uint32 getMaxAnisotropy() const;
	
	void setMaxAnisotropy( uint32 val );
	
	CompareType getComparisonFunc() const;
	
	void setComparisonFunc( CompareType val );
	
	const XE::float32 * getBorderColor() const;
	
	XE::float32 getMinLOD() const;
	
	void setMinLOD( XE::float32 val );
	
	XE::float32 getMaxLOD() const;
	
	void setMaxLOD( XE::float32 val );

private:
	SamplerFilter _MinFilter;
	SamplerFilter _MagFilter;
	SamplerFilter _MipFilter;
	
	SamplerAddressType _AddressU;
	SamplerAddressType _AddressV;
	SamplerAddressType _AddressW;
	
	XE::float32 _MipLODBias;
	uint32 _MaxAnisotropy;
	CompareType _ComparisonFunc;
	
	XE::float32 _BorderColor[4];
	
	XE::float32 _MinLOD;
	XE::float32 _MaxLOD;
};

END_XE_NAMESAPCE

#endif //__SAMPLER_H__8CA19C8D_274C_4E0D_93A6_2447A8E1759E
