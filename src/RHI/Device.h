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
	virtual SwapChainHandle CreateSwapChain( WindowHandle handle, TextureFormat framefmt, XE::uint32 w, XE::uint32 h ) = 0;

	virtual bool DestroySwapChain( SwapChainHandle handle ) = 0;

public:
	virtual XE::memory_view Map( ResourceHandle handle, XE::uint32 sub_resource, XE::uint64 begin, XE::uint64 end, XE::uint8 * read_data ) = 0;

	virtual void Unmap( ResourceHandle handle, XE::uint32 sub_resource, XE::uint64 begin, XE::uint64 end ) = 0;

public:
	virtual ResourceHandle CompileShader( const String & file, const String & entry, Array<XE::uint8> & byte ) = 0;

	virtual ResourceHandle CompileShader( memory_view byte, const String & entry ) = 0;

public:
	virtual SamplerHandle CreateSampler( SamplerPtr & desc ) = 0;

	virtual bool DestroySampler( SamplerHandle handle ) = 0;

public:
	virtual RenderTargetHandle CreateRenderTarget( RenderTargetPtr & desc ) = 0;

	virtual bool DestroyRenderTarget( RenderTargetHandle handle ) = 0;

};

END_XE_NAMESPACE

#endif // DEVICE_H__C8946AB4_1220_4FEE_AB78_53C9D8C6A6A3
