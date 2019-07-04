/*!
 * \file	SwapChain.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/04
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SWAPCHAIN_H__65376452_277D_4CC7_A486_344E613C7C39
#define SWAPCHAIN_H__65376452_277D_4CC7_A486_344E613C7C39

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API SwapChain : public std::enable_shared_from_this< SwapChain >
{
public:
	SwapChain( DevicePtr device, RenderWindowHandle handle );

	~SwapChain();

public:
	SwapChainHandle GetHandle() const;

private:
	DevicePtr _Device;
	SwapChainHandle _Handle;
};

END_XE_NAMESPACE

#endif // SWAPCHAIN_H__65376452_277D_4CC7_A486_344E613C7C39
