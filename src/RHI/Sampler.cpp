#include "Sampler.h"

USING_XE

BEG_META( Sampler )
END_META()

Sampler::Sampler()
{

}

Sampler::~Sampler()
{

}

SamplerFilter Sampler::GetMinFilter() const
{
	return _MinFilter;
}

void Sampler::SetMinFilter( SamplerFilter val )
{
	_MinFilter = val;
}

SamplerFilter Sampler::GetMagFilter() const
{
	return _MagFilter;
}

void Sampler::SetMagFilter( SamplerFilter val )
{
	_MagFilter = val;
}

SamplerFilter Sampler::GetMipFilter() const
{
	return _MipFilter;
}

void Sampler::SetMipFilter( SamplerFilter val )
{
	_MipFilter = val;
}

SamplerAddressType Sampler::GetAddressU() const
{
	return _AddressU;
}

void Sampler::SetAddressU( SamplerAddressType val )
{
	_AddressU = val;
}

SamplerAddressType Sampler::GetAddressV() const
{
	return _AddressV;
}

void Sampler::SetAddressV( SamplerAddressType val )
{
	_AddressV = val;
}

SamplerAddressType Sampler::GetAddressW() const
{
	return _AddressW;
}

void Sampler::SetAddressW( SamplerAddressType val )
{
	_AddressW = val;
}

XE::real Sampler::GetMipLodBias() const
{
	return _MipLODBias;
}

void Sampler::SetMipLodBias( XE::real val )
{
	_MipLODBias = val;
}

XE::uint32 Sampler::GetMaxAnisotropy() const
{
	return _MaxAnisotropy;
}

void Sampler::SetMaxAnisotropy( XE::uint32 val )
{
	_MaxAnisotropy = val;
}

CompareType Sampler::GetComparisonFunc() const
{
	return _ComparisonFunc;
}

void Sampler::SetComparisonFunc( CompareType val )
{
	_ComparisonFunc = val;
}

const XE::real * Sampler::GetBorderColor() const
{
	return _BorderColor;
}

XE::real Sampler::GetMinLOD() const
{
	return _MinLOD;
}

void Sampler::SetMinLOD( XE::real val )
{
	_MinLOD = val;
}

XE::real Sampler::GetMaxLOD() const
{
	return _MaxLOD;
}

void Sampler::SetMaxLOD( XE::real val )
{
	_MaxLOD = val;
}
