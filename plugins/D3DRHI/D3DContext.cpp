#include "D3DContext.h"

#define ThrowIfFailed( EXPR ) if( FAILED( EXPR ) ) { XE_LOG( LoggerLevel::Error, #EXPR ); exit(0); }

USING_XE

BEG_META(D3DContext)
END_META()

XE::D3DContext::D3DContext()
{

}

XE::D3DContext::~D3DContext()
{

}

void XE::D3DContext::Startup()
{
#if defined(DEBUG)
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed( D3D12GetDebugInterface( IID_PPV_ARGS( &debugController ) ) );
		debugController->EnableDebugLayer();
	}
#endif

	ThrowIfFailed( CreateDXGIFactory1( IID_PPV_ARGS( &_Factory ) ) );

	CreateD3DDevice();

	// Describe and create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	ThrowIfFailed( _Device->CreateCommandQueue( &queueDesc, IID_PPV_ARGS( &_CommandQueue ) ) );

	// Create descriptor heaps.
// 	{
// 		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
// 		rtvHeapDesc.NumDescriptors = FrameCount;
// 		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
// 		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
// 		ThrowIfFailed( _Device->CreateDescriptorHeap( &rtvHeapDesc, IID_PPV_ARGS( &_RTVDescriptorHeap ) ) );
// 		_RTVDescSize = _Device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );
// 	}

	ThrowIfFailed( _Device->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS( &_CommandAllocator ) ) );
}

void XE::D3DContext::Clearup()
{
	_SwapChains.clear();

	_RTVDescriptorHeap.Reset();
	_CommandAllocator.Reset();
	_RootSignature.Reset();
	_CommandQueue.Reset();
	_Device.Reset();
	_Factory.Reset();
	_RTVDescSize = 0;
}

DeviceType XE::D3DContext::GetType() const
{
	return DeviceType::DIRECT3D12;
}

void XE::D3DContext::CreateD3DDevice()
{
	ComPtr<IDXGIAdapter1> adapter;

	for( UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != _Factory->EnumAdapters1( adapterIndex, &adapter ); ++adapterIndex )
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1( &desc );

		if( desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE )
		{
			continue;
		}

		if( SUCCEEDED( D3D12CreateDevice( adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS( &_Device ) ) ) )
		{
			break;
		}
	}
}

XE::SwapChainHandle XE::D3DContext::CreateSwapChain( SwapChainPtr & val )
{
	return SwapChainHandle::Invalid;
// 	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
// 	swapChainDesc.BufferCount = 1;
// 	swapChainDesc.BufferDesc.Width = w;
// 	swapChainDesc.BufferDesc.Height = h;
// 	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
// 	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
// 	swapChainDesc.BufferDesc.Format = ToFormat( framefmt );
// 	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
// 	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
// 	swapChainDesc.OutputWindow = reinterpret_cast< HWND >( handle.GetValue() );
// 	swapChainDesc.SampleDesc.Count = 1;
// 	swapChainDesc.Windowed = TRUE;
// 
// 	ComPtr<IDXGISwapChain> swapChain;
// 	ThrowIfFailed( _Factory->CreateSwapChain( _CommandQueue.Get(), &swapChainDesc, &swapChain ) );
// 	ThrowIfFailed( _Factory->MakeWindowAssociation( swapChainDesc.OutputWindow, DXGI_MWA_NO_ALT_ENTER ) );
// 
// 	for( int i = 0; i < _SwapChains.size(); ++i )
// 	{
// 		if( !_SwapChains[i] )
// 		{
// 			_SwapChains[i] = swapChain;
// 
// 			return i;
// 		}
// 	}
// 
// 	_SwapChains.push_back( swapChain );
// 
// 	return _SwapChains.size() - 1;
}

bool XE::D3DContext::DestroySwapChain( SwapChainHandle handle )
{
	if( _SwapChains.size() > handle.GetValue() && _SwapChains[handle.GetValue()] )
	{
		_SwapChains[handle.GetValue()].Reset();
		return true;
	}
	return false;
}

DXGI_FORMAT XE::D3DContext::ToFormat( TextureFormat val ) const
{
	// todo: 
	return DXGI_FORMAT_B8G8R8A8_TYPELESS;
}
