/*!
 * \file   DXGI.h
 *
 * \author ZhengYuanQing
 * \date   2021/02/07
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef DXGI_H__B71F3738_305A_4B18_BDA1_FE3960BA5384
#define DXGI_H__B71F3738_305A_4B18_BDA1_FE3960BA5384

#include "Type.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_XBOX)

#include "Utils/Library.h"

#include <d3dcommon.h>
#include <dxgi1_6.h>

#ifdef max
#undef max
#endif // max
#ifdef TRANSPARENT
#undef TRANSPARENT
#endif // TRANSPARENT

#define DX_RELEASE(_ptr ) \
if( nullptr != ( _ptr ) ) \
{ \
	_ptr->Release(); \
	_ptr = nullptr; \
} \

BEG_XE_NAMESPACE

struct SwapChainDesc
{
	XE::uint32 width;
	XE::uint32 height;
	DXGI_FORMAT format;
	bool stereo;
	DXGI_SAMPLE_DESC sampleDesc;
	DXGI_USAGE bufferUsage;
	XE::uint32 bufferCount;
	DXGI_SCALING scaling;
	DXGI_SWAP_EFFECT swapEffect;
	DXGI_ALPHA_MODE alphaMode;
	XE::uint32 flags;
	XE::uint8 maxFrameLatency;
	void * nwh;
	void * ndt;
	bool windowed;
};

class DXGI
{
public:
	typedef ::IUnknown        UnknownI;
	typedef ::IDXGIAdapter3   AdapterI;
	typedef ::IDXGIFactory5   FactoryI;
	typedef ::IDXGISwapChain3 SwapChainI;
	typedef ::IDXGIOutput     OutputI;

public:
    DXGI() = default;

    ~DXGI() = default;

public:
	void Init( CapsInfo & caps );

    void Shutdown();

    void Update( UnknownI * device );

public:
	HRESULT CreateSwapChain( UnknownI * _device, const SwapChainDesc & _scd, SwapChainI ** _swapChain );

	void UpdateHdr10( SwapChainI * _swapChain, const SwapChainDesc & _scd );

	HRESULT ResizeBuffers( SwapChainI * _swapChain, const SwapChainDesc & _scd, const XE::uint32 * _nodeMask = NULL, UnknownI * const * _presentQueue = NULL );

public:
	XE::LibraryHandle _DXGIDll;
	XE::LibraryHandle _DXGIDebugDll;
	D3D_DRIVER_TYPE   _DriverType = D3D_DRIVER_TYPE_NULL;
	DXGI_ADAPTER_DESC _AdapterDesc;
	FactoryI * _Factory = nullptr;
	AdapterI * _Adapter = nullptr;
	OutputI * _Output = nullptr;
};

END_XE_NAMESPACE

#endif

#endif // DXGI_H__B71F3738_305A_4B18_BDA1_FE3960BA5384
