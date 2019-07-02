#include "D3DDevice.h"

USING_XE

BEG_META(D3DDevice)
END_META()

void XE::D3DDevice::Startup()
{

}

void XE::D3DDevice::Clearup()
{

}

DeviceType XE::D3DDevice::GetType() const
{
	return DeviceType::DIRECT3D11;
}
