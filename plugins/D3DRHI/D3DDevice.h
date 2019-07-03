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
	bool CreateSwapChain( RenderWindowHandle handle ) override;

	FrameBufferPtr GetBackFrameBuffer( RenderWindowHandle handle ) override;

	FrameBufferPtr GetFrontFrameBuffer( RenderWindowHandle handle ) override;

	FrameBufferPtr GetCurrentFrameBuffer( RenderWindowHandle handle ) override;

	bool DestroySwapChain( RenderWindowHandle handle ) override;

private:
	void GetHardwareAdapter( IDXGIFactory2 * pFactory, IDXGIAdapter1 ** ppAdapter );

private:
	Array< Pair<RenderWindowHandle, ComPtr<IDXGISwapChain3>> > _SwapChains;



	// App resources.
	D3D12_VIEWPORT m_viewport;
	D3D12_RECT m_scissorRect;
	ComPtr<ID3D12Resource> m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
	ComPtr<IDXGISwapChain3> m_swapChain;
	ComPtr<ID3D12Resource> m_renderTargets[8];

	// Synchronization objects.
	UINT m_frameIndex;
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_fence;
	UINT64 m_fenceValue;


	ComPtr<IDXGIFactory4> m_factory;
	ComPtr<ID3D12Device> m_device;
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12PipelineState> m_pipelineState;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
	UINT m_rtvDescriptorSize;

};

END_XE_NAMESPACE

#endif // D3DDEVICE_H__404C2A61_7B6D_498F_9FC0_4DE0B648D467
