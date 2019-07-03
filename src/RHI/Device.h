/*!
 * \file	Device.h
 *
 * \author	ZhengYuanQing
 * \date	2019/06/30
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DEVICE_H__C8946AB4_1220_4FEE_AB78_53C9D8C6A6A3
#define DEVICE_H__C8946AB4_1220_4FEE_AB78_53C9D8C6A6A3

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Device
{
	OBJECT( Device )

public:
	Device();

	virtual ~Device();

public:
	virtual void Startup() = 0;

	virtual void Clearup() = 0;

public:
	virtual DeviceType GetType() const = 0;

public:
	virtual bool CreateSwapChain( RenderWindowHandle handle ) = 0;

	virtual FrameBufferPtr GetBackFrameBuffer( RenderWindowHandle handle ) = 0;

	virtual FrameBufferPtr GetFrontFrameBuffer( RenderWindowHandle handle ) = 0;

	virtual FrameBufferPtr GetCurrentFrameBuffer( RenderWindowHandle handle ) = 0;

	virtual bool DestroySwapChain( RenderWindowHandle handle ) = 0;

};

END_XE_NAMESPACE

#endif // DEVICE_H__C8946AB4_1220_4FEE_AB78_53C9D8C6A6A3
