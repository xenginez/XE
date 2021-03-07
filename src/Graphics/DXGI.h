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

#define DX_RELEASE( _ptr ) \
if( nullptr != ( _ptr ) ) \
{ \
	_ptr->Release(); \
	_ptr = nullptr; \
} \

#define DX_CHECK( _call ) XE_ASSERT( SUCCEEDED( _call ) )

#define DXGI_FORMAT_ASTC_4X4_TYPELESS     DXGI_FORMAT(133)
#define DXGI_FORMAT_ASTC_4X4_UNORM        DXGI_FORMAT(134)
#define DXGI_FORMAT_ASTC_4X4_UNORM_SRGB   DXGI_FORMAT(135)
#define DXGI_FORMAT_ASTC_5X4_TYPELESS     DXGI_FORMAT(137)
#define DXGI_FORMAT_ASTC_5X4_UNORM        DXGI_FORMAT(138)
#define DXGI_FORMAT_ASTC_5X4_UNORM_SRGB   DXGI_FORMAT(139)
#define DXGI_FORMAT_ASTC_5X5_TYPELESS     DXGI_FORMAT(141)
#define DXGI_FORMAT_ASTC_5X5_UNORM        DXGI_FORMAT(142)
#define DXGI_FORMAT_ASTC_5X5_UNORM_SRGB   DXGI_FORMAT(143)
#define DXGI_FORMAT_ASTC_6X5_TYPELESS     DXGI_FORMAT(145)
#define DXGI_FORMAT_ASTC_6X5_UNORM        DXGI_FORMAT(146)
#define DXGI_FORMAT_ASTC_6X5_UNORM_SRGB   DXGI_FORMAT(147)
#define DXGI_FORMAT_ASTC_6X6_TYPELESS     DXGI_FORMAT(149)
#define DXGI_FORMAT_ASTC_6X6_UNORM        DXGI_FORMAT(150)
#define DXGI_FORMAT_ASTC_6X6_UNORM_SRGB   DXGI_FORMAT(151)
#define DXGI_FORMAT_ASTC_8X5_TYPELESS     DXGI_FORMAT(153)
#define DXGI_FORMAT_ASTC_8X5_UNORM        DXGI_FORMAT(154)
#define DXGI_FORMAT_ASTC_8X5_UNORM_SRGB   DXGI_FORMAT(155)
#define DXGI_FORMAT_ASTC_8X6_TYPELESS     DXGI_FORMAT(157)
#define DXGI_FORMAT_ASTC_8X6_UNORM        DXGI_FORMAT(158)
#define DXGI_FORMAT_ASTC_8X6_UNORM_SRGB   DXGI_FORMAT(159)
#define DXGI_FORMAT_ASTC_8X8_TYPELESS     DXGI_FORMAT(161)
#define DXGI_FORMAT_ASTC_8X8_UNORM        DXGI_FORMAT(162)
#define DXGI_FORMAT_ASTC_8X8_UNORM_SRGB   DXGI_FORMAT(163)
#define DXGI_FORMAT_ASTC_10X5_TYPELESS    DXGI_FORMAT(165)
#define DXGI_FORMAT_ASTC_10X5_UNORM       DXGI_FORMAT(166)
#define DXGI_FORMAT_ASTC_10X5_UNORM_SRGB  DXGI_FORMAT(167)
#define DXGI_FORMAT_ASTC_10X6_TYPELESS    DXGI_FORMAT(169)
#define DXGI_FORMAT_ASTC_10X6_UNORM       DXGI_FORMAT(170)
#define DXGI_FORMAT_ASTC_10X6_UNORM_SRGB  DXGI_FORMAT(171)
#define DXGI_FORMAT_ASTC_10X8_TYPELESS    DXGI_FORMAT(173)
#define DXGI_FORMAT_ASTC_10X8_UNORM       DXGI_FORMAT(174)
#define DXGI_FORMAT_ASTC_10X8_UNORM_SRGB  DXGI_FORMAT(175)
#define DXGI_FORMAT_ASTC_10X10_TYPELESS   DXGI_FORMAT(177)
#define DXGI_FORMAT_ASTC_10X10_UNORM      DXGI_FORMAT(178)
#define DXGI_FORMAT_ASTC_10X10_UNORM_SRGB DXGI_FORMAT(179)
#define DXGI_FORMAT_ASTC_12X10_TYPELESS   DXGI_FORMAT(181)
#define DXGI_FORMAT_ASTC_12X10_UNORM      DXGI_FORMAT(182)
#define DXGI_FORMAT_ASTC_12X10_UNORM_SRGB DXGI_FORMAT(183)
#define DXGI_FORMAT_ASTC_12X12_TYPELESS   DXGI_FORMAT(185)
#define DXGI_FORMAT_ASTC_12X12_UNORM      DXGI_FORMAT(186)
#define DXGI_FORMAT_ASTC_12X12_UNORM_SRGB DXGI_FORMAT(187)

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
