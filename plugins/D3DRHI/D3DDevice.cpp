#include "D3DDevice.h"

USING_XE

BEG_META(D3DDevice)
END_META()

#define ThrowIfFailed( EXPR ) if( FAILED( EXPR ) ) { XE_LOG( LoggerLevel::Error, #EXPR ); exit(0); }

#define WHND_HANDLE nullptr
#define FrameCount 8
#define m_width 0
#define m_height 0



XE::D3DDevice::D3DDevice()
{

}

XE::D3DDevice::~D3DDevice()
{

}

void XE::D3DDevice::Startup()
{
#if defined(DEBUG)
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed( D3D12GetDebugInterface( IID_PPV_ARGS( &debugController ) ) );
		debugController->EnableDebugLayer();
	}
#endif

	ThrowIfFailed( CreateDXGIFactory1( IID_PPV_ARGS( &m_factory ) ) );

	ComPtr<IDXGIAdapter1> hardwareAdapter;
	GetHardwareAdapter( m_factory.Get(), &hardwareAdapter );
	ThrowIfFailed( D3D12CreateDevice( hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS( &m_device ) ) );

	// Describe and create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	ThrowIfFailed( m_device->CreateCommandQueue( &queueDesc, IID_PPV_ARGS( &m_commandQueue ) ) );

	// Describe and create the swap chain.
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = FrameCount;
	swapChainDesc.BufferDesc.Width = m_width;
	swapChainDesc.BufferDesc.Height = m_height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = WHND_HANDLE;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;
	ComPtr<IDXGISwapChain> swapChain;
	ThrowIfFailed( m_factory->CreateSwapChain( m_commandQueue.Get(), &swapChainDesc, &swapChain ) );
	ThrowIfFailed( swapChain.As( &m_swapChain ) );

	// This sample does not support fullscreen transitions.
	ThrowIfFailed( m_factory->MakeWindowAssociation( WHND_HANDLE, DXGI_MWA_NO_ALT_ENTER ) );
	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	// Create descriptor heaps.
	{
		// Describe and create a render target view (RTV) descriptor heap.
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = FrameCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed( m_device->CreateDescriptorHeap( &rtvHeapDesc, IID_PPV_ARGS( &m_rtvHeap ) ) );

		m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );
	}

	// Create frame resources.
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle( m_rtvHeap->GetCPUDescriptorHandleForHeapStart() );

		// Create a RTV for each frame.
		for( UINT n = 0; n < FrameCount; n++ )
		{
			ThrowIfFailed( m_swapChain->GetBuffer( n, IID_PPV_ARGS( &m_renderTargets[n] ) ) );
			m_device->CreateRenderTargetView( m_renderTargets[n].Get(), nullptr, rtvHandle );
			rtvHandle.Offset( 1, m_rtvDescriptorSize );
		}
	}

	ThrowIfFailed( m_device->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS( &m_commandAllocator ) ) );
}

void XE::D3DDevice::Clearup()
{

}

DeviceType XE::D3DDevice::GetType() const
{
	return DeviceType::DIRECT3D11;
}

void XE::D3DDevice::GetHardwareAdapter( IDXGIFactory2 * pFactory, IDXGIAdapter1 ** ppAdapter )
{
	ComPtr<IDXGIAdapter1> adapter;
	*ppAdapter = nullptr;

	for( UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1( adapterIndex, &adapter ); ++adapterIndex )
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1( &desc );

		if( desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE )
		{
			continue;
		}

		if( SUCCEEDED( D3D12CreateDevice( adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof( ID3D12Device ), nullptr ) ) )
		{
			break;
		}
	}

	*ppAdapter = adapter.Detach();
}

bool XE::D3DDevice::CreateSwapChain( RenderWindowHandle handle )
{
	return true;
}

XE::FrameBufferPtr XE::D3DDevice::GetBackFrameBuffer( RenderWindowHandle handle )
{
	return nullptr;
}

XE::FrameBufferPtr XE::D3DDevice::GetFrontFrameBuffer( RenderWindowHandle handle )
{
	return nullptr;
}

XE::FrameBufferPtr XE::D3DDevice::GetCurrentFrameBuffer( RenderWindowHandle handle )
{
	return nullptr;
}

bool XE::D3DDevice::DestroySwapChain( RenderWindowHandle handle )
{
	return true;
}
