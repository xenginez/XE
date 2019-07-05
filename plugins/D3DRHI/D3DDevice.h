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

using namespace DirectX;
using namespace Microsoft::WRL;

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

public:
	SwapChainHandle CreateSwapChain( WindowHandle handle, TextureFormat framefmt, XE::uint32 w, XE::uint32 h ) override;

	bool DestroySwapChain( SwapChainHandle handle ) override;

private:
	void CreateD3DDevice();

	DXGI_FORMAT ToFormat( TextureFormat val ) const;

private:
	Array< ComPtr<IDXGISwapChain> > _SwapChains;

	ComPtr<IDXGIFactory4> _Factory;
	ComPtr<ID3D12Device> _Device;
	ComPtr<ID3D12CommandQueue> _CommandQueue;
	ComPtr<ID3D12RootSignature> _RootSignature;
	ComPtr<ID3D12DescriptorHeap> _RTVDescriptorHeap;
	ComPtr<ID3D12CommandAllocator> _CommandAllocator;
	XE::uint32 _RTVDescSize;
};

END_XE_NAMESPACE

#endif // D3DDEVICE_H__404C2A61_7B6D_498F_9FC0_4DE0B648D467
