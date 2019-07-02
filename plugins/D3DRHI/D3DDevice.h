/*!
 * \file	D3DDevice.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/02
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef D3DDEVICE_H__404C2A61_7B6D_498F_9FC0_4DE0B648D467
#define D3DDEVICE_H__404C2A61_7B6D_498F_9FC0_4DE0B648D467

#include "Type.h"

BEG_XE_NAMESPACE

class D3DDevice : public XE::Device
{
	OBJECT( D3DDevice, Device )
	
public:
	D3DDevice();

	~D3DDevice() override;

public:
	void Startup() override;

	void Clearup() override;

public:
	DeviceType GetType() const override;

private:
	
};

END_XE_NAMESPACE

#endif // D3DDEVICE_H__404C2A61_7B6D_498F_9FC0_4DE0B648D467
