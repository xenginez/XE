#include "Sampler.h"

USING_XE

BEG_META(Sampler)
END_META()

Sampler::Sampler()
{

}

Sampler::~Sampler()
{

}

SamplerFilter Sampler::getMinFilter() const
{
	return _MinFilter;
}

void Sampler::setMinFilter( SamplerFilter val )
{
	_MinFilter = val;
}

SamplerFilter Sampler::getMagFilter() const
{
	return _MagFilter;
}

void Sampler::setMagFilter( SamplerFilter val )
{
	_MagFilter = val;
}

SamplerFilter Sampler::getMipFilter() const
{
	return _MipFilter;
}

void Sampler::setMipFilter( SamplerFilter val )
{
	_MipFilter = val;
}

SamplerAddressType Sampler::getAddressU() const
{
	return _AddressU;
}

void Sampler::setAddressU( SamplerAddressType val )
{
	_AddressU = val;
}

SamplerAddressType Sampler::getAddressV() const
{
	return _AddressV;
}

void Sampler::setAddressV( SamplerAddressType val )
{
	_AddressV = val;
}

SamplerAddressType Sampler::getAddressW() const
{
	return _AddressW;
}

void Sampler::setAddressW( SamplerAddressType val )
{
	_AddressW = val;
}

XE::float32 Sampler::getMipLodBias() const
{
	return _MipLODBias;
}

void Sampler::setMipLodBias( XE::float32 val )
{
	_MipLODBias = val;
}

uint32 Sampler::getMaxAnisotropy() const
{
	return _MaxAnisotropy;
}

void Sampler::setMaxAnisotropy( uint32 val )
{
	_MaxAnisotropy = val;
}

CompareType Sampler::getComparisonFunc() const
{
	return _ComparisonFunc;
}

void Sampler::setComparisonFunc( CompareType val )
{
	_ComparisonFunc = val;
}

const XE::float32 * Sampler::getBorderColor() const
{
	return _BorderColor;
}

XE::float32 Sampler::getMinLOD() const
{
	return _MinLOD;
}

void Sampler::setMinLOD( XE::float32 val )
{
	_MinLOD = val;
}

XE::float32 Sampler::getMaxLOD() const
{
	return _MaxLOD;
}

void Sampler::setMaxLOD( XE::float32 val )
{
	_MaxLOD = val;
}
