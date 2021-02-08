#include "DXGI.h"
#if PLATFORM_OS & (OS_WINDOWS | OS_XBOX)

#include "Utils/Logger.h"

#include "Private.h"

typedef HRESULT( WINAPI * PFN_CREATE_DXGI_FACTORY )( REFIID _riid, void ** _factory );
typedef HRESULT( WINAPI * PFN_GET_DEBUG_INTERFACE )( REFIID _riid, void ** _debug );
typedef HRESULT( WINAPI * PFN_GET_DEBUG_INTERFACE1 )( UINT _flags, REFIID _riid, void ** _debug );


static const GUID IID_IDXGIFactory = { 0x7b7166ec, 0x21c7, 0x44ae, { 0xb2, 0x1a, 0xc9, 0xae, 0x32, 0x1a, 0xe3, 0x69 } };
static const GUID IID_IDXGIFactory2 = { 0x50c83a1c, 0xe072, 0x4c48, { 0x87, 0xb0, 0x36, 0x30, 0xfa, 0x36, 0xa6, 0xd0 } };
static const GUID IID_IDXGIFactory3 = { 0x25483823, 0xcd46, 0x4c7d, { 0x86, 0xca, 0x47, 0xaa, 0x95, 0xb8, 0x37, 0xbd } };
static const GUID IID_IDXGIFactory4 = { 0x1bc6ea02, 0xef36, 0x464f, { 0xbf, 0x0c, 0x21, 0xca, 0x39, 0xe5, 0x16, 0x8a } };
static const GUID IID_IDXGIFactory5 = { 0x7632e1f5, 0xee65, 0x4dca, { 0x87, 0xfd, 0x84, 0xcd, 0x75, 0xf8, 0x83, 0x8d } };
static const GUID IID_IDXGIDevice0 = { 0x54ec77fa, 0x1377, 0x44e6, { 0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c } };
static const GUID IID_IDXGIDevice1 = { 0x77db970f, 0x6276, 0x48ba, { 0xba, 0x28, 0x07, 0x01, 0x43, 0xb4, 0x39, 0x2c } };
static const GUID IID_IDXGIDevice2 = { 0x05008617, 0xfbfd, 0x4051, { 0xa7, 0x90, 0x14, 0x48, 0x84, 0xb4, 0xf6, 0xa9 } };
static const GUID IID_IDXGIDevice3 = { 0x6007896c, 0x3244, 0x4afd, { 0xbf, 0x18, 0xa6, 0xd3, 0xbe, 0xda, 0x50, 0x23 } };
static const GUID IID_IDXGIAdapter = { 0x2411e7e1, 0x12ac, 0x4ccf, { 0xbd, 0x14, 0x97, 0x98, 0xe8, 0x53, 0x4d, 0xc0 } };
static const GUID IID_IDXGIAdapter2 = { 0x0aa1ae0a, 0xfa0e, 0x4b84, { 0x86, 0x44, 0xe0, 0x5f, 0xf8, 0xe5, 0xac, 0xb5 } };
static const GUID IID_IDXGIAdapter3 = { 0x645967a4, 0x1392, 0x4310, { 0xa7, 0x98, 0x80, 0x53, 0xce, 0x3e, 0x93, 0xfd } };
static const GUID IID_IDXGIAdapter4 = { 0x3c8d99d1, 0x4fbf, 0x4181, { 0xa8, 0x2c, 0xaf, 0x66, 0xbf, 0x7b, 0xd2, 0x4e } };
static const GUID IID_IDXGISwapChain3 = { 0x94d99bdb, 0xf1f8, 0x4ab0, { 0xb2, 0x36, 0x7d, 0xa0, 0x17, 0x0e, 0xda, 0xb1 } };
static const GUID IID_IDXGISwapChain4 = { 0x3d585d5a, 0xbd4a, 0x489e, { 0xb1, 0xf4, 0x3d, 0xbc, 0xb6, 0x45, 0x2f, 0xfb } };
static const GUID IID_IDXGIOutput6 = { 0x068346e8, 0xaaec, 0x4b84, { 0xad, 0xd7, 0x13, 0x7f, 0x51, 0x3f, 0x77, 0xa1 } };

static const char * ColorSpaceStr[] =
{
	// https://msdn.microsoft.com/en-us/library/windows/desktop/dn903661(v=vs.85).aspx
	"RGB,    0-255, 2.2,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709
	"RGB,    0-255, 1.0,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709
	"RGB,   16-235, 2.2,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709
	"RGB,   16-235, 2.2,  Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020
	"Reserved",                                    // DXGI_COLOR_SPACE_RESERVED
	"YCbCr,  0-255, 2.2,  Image, BT.709,  BT.601", // DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601
	"YCbCr, 16-235, 2.2,  Video, BT.601,  n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601
	"YCbCr,  0-255, 2.2,  Video, BT.601,  n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601
	"YCbCr, 16-235, 2.2,  Video, BT.709,  n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709
	"YCbCr,  0-255, 2.2,  Video, BT.709,  n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709
	"YCbCr, 16-235, 2.2,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020
	"YCbCr,  0-255, 2.2,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020
	"RGB,    0-255, 2084, Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020
	"YCbCr, 16-235, 2084, Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020
	"RGB,    0-255, 2084, Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020
	"YCbCr, 16-235, 2.2,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020
	"YCbCr, 16-235, 2084, Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020
	"RGB,    0-255, 2.2,  Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020
	"YCbCr, 16-235, HLG,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020
	"YCbCr,  0-255, HLG,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020
//	"RGB,   16-235, 2.4,  Image, BT.709,  n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709
//	"RGB,   16-235, 2.4,  Image, BT.2020, n/a",    // DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020
//	"YCbCr, 16-235, 2.4,  Video, BT.709,  n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709
//	"YCbCr, 16-235, 2.4,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020
//	"YCbCr, 16-235, 2.4,  Video, BT.2020, n/a",    // DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020
	"Custom",
};

void XE::DXGI::Init( CapsInfo & caps )
{
	_DXGIDll = XE::Library::Open( "dxgi.dll" );
	_DXGIDebugDll = XE::Library::Open( "dxgidebug.dll" );

	PFN_CREATE_DXGI_FACTORY CreateDXGIFactory = XE::Library::SymbolT< PFN_CREATE_DXGI_FACTORY >( _DXGIDll, "CreateDXGIFactory1" );

	if( nullptr == CreateDXGIFactory )
	{
		CreateDXGIFactory = XE::Library::SymbolT< PFN_CREATE_DXGI_FACTORY >( _DXGIDll, "CreateDXGIFactory" );
	}

	XE_ASSERT( nullptr != CreateDXGIFactory && "Init error: Function CreateDXGIFactory not found." );

	HRESULT hr = CreateDXGIFactory( IID_IDXGIFactory, ( void ** ) &_Factory );

	XE_ASSERT( !FAILED( hr ) && "Init error: Unable to create DXGI factory." );

	_DriverType = XE::PciIdFlag::SOFTWARERASTERIZER == caps.VendorId ? D3D_DRIVER_TYPE_WARP : D3D_DRIVER_TYPE_HARDWARE;


	AdapterI * adapter = nullptr;
	for( XE::uint32 ii = 0; DXGI_ERROR_NOT_FOUND != _Factory->EnumAdapters( ii, reinterpret_cast< IDXGIAdapter ** >( &adapter ) ) && ii < sizeof( caps.Gpu ); ++ii )
	{
		{
			DXGI_ADAPTER_DESC desc;
			hr = adapter->GetDesc( &desc );

			if( SUCCEEDED( hr ) )
			{
				XE_LOG( LoggerLevel::Message, "Adapter %1", ii );

				char description[sizeof( desc.Description )];
				wcstombs( description, desc.Description, sizeof( desc.Description ) );
				XE_LOG( LoggerLevel::Message, "\tDescription: %s", description );
				XE_LOG( LoggerLevel::Message, "\tVendorId: %1, DeviceId: %2, SubSysId: %3, Revision: %4"
						, desc.VendorId
						, desc.DeviceId
						, desc.SubSysId
						, desc.Revision
				);
				XE_LOG( LoggerLevel::Message, "\tMemory: %1(video), %2(system), %3(shared)"
						, desc.DedicatedVideoMemory
						, desc.DedicatedSystemMemory
						, desc.SharedSystemMemory
				);

				caps.Gpu[ii].VendorId = ( XE::PciIdFlag ) desc.VendorId;
				caps.Gpu[ii].DeviceId = ( XE::uint16 ) desc.DeviceId;
				++caps.NumGPUs;

				if( nullptr == _Adapter )
				{
					if( ( XE::PciIdFlag::NONE != caps.VendorId || 0 != caps.DeviceId )
						&& ( XE::PciIdFlag::NONE == caps.VendorId || desc.VendorId == (XE::uint16)caps.VendorId )
						&& ( 0 == caps.DeviceId || desc.DeviceId == caps.DeviceId ) )
					{
						_Adapter = adapter;
						_Adapter->AddRef();
						_DriverType = D3D_DRIVER_TYPE_UNKNOWN;
					}
				}
			}
		}

		bool hdr10 = false;

		IDXGIOutput * output = nullptr;
		for( XE::uint32 jj = 0; SUCCEEDED( adapter->EnumOutputs( jj, &output ) ); ++jj )
		{
			DXGI_OUTPUT_DESC outputDesc;
			hr = output->GetDesc( &outputDesc );
			if( SUCCEEDED( hr ) )
			{
				XE_LOG( LoggerLevel::Message, "\tOutput %1", jj );

				char deviceName[sizeof( outputDesc.DeviceName )];
				wcstombs( deviceName, outputDesc.DeviceName, sizeof( outputDesc.DeviceName ) );
				XE_LOG( LoggerLevel::Message, "\t\tDeviceName: %1", deviceName );
				XE_LOG( LoggerLevel::Message, "\t\tDesktopCoordinates: %1, %2, %3, %4"
						, outputDesc.DesktopCoordinates.left
						, outputDesc.DesktopCoordinates.top
						, outputDesc.DesktopCoordinates.right
						, outputDesc.DesktopCoordinates.bottom
				);
				XE_LOG( LoggerLevel::Message, "\t\tAttachedToDesktop: %1", outputDesc.AttachedToDesktop );
				XE_LOG( LoggerLevel::Message, "\t\tRotation: %1", outputDesc.Rotation );

				IDXGIOutput6 * output6 = nullptr;
				hr = output->QueryInterface( IID_IDXGIOutput6, ( void ** ) &output6 );
				if( SUCCEEDED( hr ) )
				{
					DXGI_OUTPUT_DESC1 desc;
					hr = output6->GetDesc1( &desc );
					if( SUCCEEDED( hr ) )
					{
						XE_LOG( LoggerLevel::Message, "\t\tBitsPerColor: %1", desc.BitsPerColor );
						XE_LOG( LoggerLevel::Message, "\t\tColor space: %1 (colorspace, range, gamma, sitting, primaries, transform)"
								, ColorSpaceStr[std::min<uint32_t>( desc.ColorSpace, DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020 + 1 )]
						);
						XE_LOG( LoggerLevel::Message, "\t\tRedPrimary: %1, %2", desc.RedPrimary[0], desc.RedPrimary[1] );
						XE_LOG( LoggerLevel::Message, "\t\tGreenPrimary: %1, %2", desc.GreenPrimary[0], desc.GreenPrimary[1] );
						XE_LOG( LoggerLevel::Message, "\t\tBluePrimary: %1, %2", desc.BluePrimary[0], desc.BluePrimary[1] );
						XE_LOG( LoggerLevel::Message, "\t\tWhitePoint: %1, %2", desc.WhitePoint[0], desc.WhitePoint[1] );
						XE_LOG( LoggerLevel::Message, "\t\tMinLuminance: %1", desc.MinLuminance );
						XE_LOG( LoggerLevel::Message, "\t\tMaxLuminance: %1", desc.MaxLuminance );
						XE_LOG( LoggerLevel::Message, "\t\tMaxFullFrameLuminance: %1", desc.MaxFullFrameLuminance );
						XE_LOG( LoggerLevel::Message, "\t\tHDR support: %1", DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 == desc.ColorSpace ? "true" : "false" );

						hdr10 |= DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 == desc.ColorSpace;
					}

					DX_RELEASE( output6 );
				}

				DX_RELEASE( output );
			}
		}

		if( hdr10 )
		{
			caps.Supported |= XE::CapsFlag::HDR10;
		}

		DX_RELEASE( adapter );
	}

	if( nullptr == _Adapter )
	{
		hr = _Factory->EnumAdapters( 0, reinterpret_cast< IDXGIAdapter ** >( &_Adapter ) );
		if( FAILED( hr ) )
		{
			XE_LOG( LoggerLevel::Warning, "EnumAdapters failed %1.", hr );
		}
		_DriverType = D3D_DRIVER_TYPE_UNKNOWN;
	}

	std::memset( &_AdapterDesc, 0, sizeof( _AdapterDesc ) );
	hr = _Adapter->GetDesc( &_AdapterDesc );
	if( FAILED( hr ) )
	{
		XE_LOG( LoggerLevel::Warning, "Adapter GetDesc failed %1.", hr );
	}

	_Adapter->EnumOutputs( 0, &_Output );

	caps.VendorId = 0 == _AdapterDesc.VendorId ? XE::PciIdFlag::SOFTWARERASTERIZER : ( XE::PciIdFlag ) _AdapterDesc.VendorId;
	caps.DeviceId = ( XE::uint16 ) _AdapterDesc.DeviceId;
}

void XE::DXGI::Shutdown()
{
	DX_RELEASE( _Output );
	DX_RELEASE( _Adapter );
	DX_RELEASE( _Factory );

	XE::Library::Close( _DXGIDll );
	XE::Library::Close( _DXGIDebugDll );

	_DXGIDll = XE::LibraryHandle::Invalid;
	_DXGIDebugDll = XE::LibraryHandle::Invalid;
}

void XE::DXGI::Update( UnknownI * device )
{
	static const GUID DeviceIIDs[] =
	{
		IID_IDXGIDevice3,
		IID_IDXGIDevice2,
		IID_IDXGIDevice1,
		IID_IDXGIDevice0,
	};

	IDXGIDevice * dxgiDevice = nullptr;
	HRESULT hr = E_FAIL;
	for( uint32_t ii = 0; ii < sizeof( DeviceIIDs ) && FAILED( hr ); ++ii )
	{
		hr = device->QueryInterface( DeviceIIDs[ii], ( void ** ) &dxgiDevice );
		XE_LOG( LoggerLevel::Message, "DXGI device 11.%1, hr %2", sizeof( DeviceIIDs ) - 1 - ii, hr );
	}

	if( nullptr == _Factory )
	{
		XE_ASSERT( !SUCCEEDED( dxgiDevice->GetAdapter( reinterpret_cast< IDXGIAdapter ** >( &_Adapter ) ) ) );

		std::memset( &_AdapterDesc, 0, sizeof( _AdapterDesc ) );
		hr = _Adapter->GetDesc( &_AdapterDesc );
		if( FAILED( hr ) )
		{
			XE_LOG( LoggerLevel::Warning, "Adapter GetDesc failed %1.", hr );
		}

		XE_ASSERT( !SUCCEEDED( _Adapter->GetParent( IID_IDXGIFactory2, ( void ** ) &_Factory ) ) );
	}

	DX_RELEASE( dxgiDevice );
}

HRESULT XE::DXGI::CreateSwapChain( UnknownI * _device, const SwapChainDesc & _scd, SwapChainI * *_swapChain )
{
	static const GUID SwapChainIIDs[] =
	{
		IID_IDXGISwapChain4,
		IID_IDXGISwapChain3,
	};
	static const DXGI_COLOR_SPACE_TYPE ColorSpace[] =
	{
		DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709,    // gamma 2.2,  BT.709
		DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709,    // gamma 1.0,  BT.709
		DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020, // gamma 2084, BT.2020
	};


	HRESULT hr = S_OK;

	bool allowTearing = false;
	hr = _Factory->CheckFeatureSupport( DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof( allowTearing ) );
	XE_LOG( LoggerLevel::Message, "Allow tearing is %1supported.", allowTearing ? "" : "not " );

	DXGI_SWAP_CHAIN_DESC scd;
	scd.BufferDesc.Width = _scd.width;
	scd.BufferDesc.Height = _scd.height;
	scd.BufferDesc.RefreshRate.Numerator = 1;
	scd.BufferDesc.RefreshRate.Denominator = 60;
	scd.BufferDesc.Format = _scd.format;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = _scd.bufferUsage;
	scd.BufferCount = _scd.bufferCount;
	scd.OutputWindow = ( HWND ) _scd.nwh;
	scd.Windowed = _scd.windowed;
	scd.SwapEffect = _scd.swapEffect;
	scd.Flags = 0
		| _scd.flags
		| ( allowTearing ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0 )
		;

	hr = _Factory->CreateSwapChain(
		_device
		, &scd
		, reinterpret_cast< IDXGISwapChain ** >( _swapChain )
	);

	if( SUCCEEDED( hr ) )
	{
		IDXGIDevice1 * dxgiDevice1;
		_device->QueryInterface( IID_IDXGIDevice1, ( void ** ) &dxgiDevice1 );
		if( nullptr != dxgiDevice1 )
		{
			dxgiDevice1->SetMaximumFrameLatency( _scd.maxFrameLatency );
			DX_RELEASE( dxgiDevice1 );
		}
	}

	if( FAILED( hr ) )
	{
		XE_LOG( LoggerLevel::Warning, "Failed to create swap chain." );
		return hr;
	}

	if( SUCCEEDED( hr ) )
	{
		for( uint32_t ii = 0; ii < sizeof( SwapChainIIDs ); ++ii )
		{
			IDXGISwapChain1 * swapChain;
			hr = ( *_swapChain )->QueryInterface( SwapChainIIDs[ii], ( void ** ) &swapChain );
			XE_LOG( LoggerLevel::Message, "DXGI swap chain %d, hr %x", 4 - ii, hr );

			if( SUCCEEDED( hr ) )
			{
				DX_RELEASE( ( *_swapChain ) );
				*_swapChain = reinterpret_cast< SwapChainI * >( swapChain );

				XE_LOG( LoggerLevel::Message, "Color space support:" );
				for( uint32_t jj = 0; jj < sizeof( ColorSpace ); ++jj )
				{
					uint32_t colorSpaceSupport;
					reinterpret_cast< IDXGISwapChain3 * >( *_swapChain )->CheckColorSpaceSupport( ColorSpace[jj], &colorSpaceSupport );
					XE_LOG( LoggerLevel::Message, "\t%1: \"%2\", %3, %4"
							, ColorSpace[jj]
							, ColorSpaceStr[ColorSpace[jj]]
							, colorSpaceSupport
							, 0 != ( colorSpaceSupport & DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG_PRESENT ) ? "supported" : "-" );
				}

				break;
			}
		}
	}

	UpdateHdr10( *_swapChain, _scd );

	return S_OK;
}

void XE::DXGI::UpdateHdr10( SwapChainI * _swapChain, const SwapChainDesc & _scd )
{
	::IDXGISwapChain4 * swapChain4;
	HRESULT hr = _swapChain->QueryInterface( IID_IDXGISwapChain4, ( void ** ) &swapChain4 );

	if( SUCCEEDED( hr ) )
	{
		const DXGI_COLOR_SPACE_TYPE colorSpace =
			_scd.format == DXGI_FORMAT_R10G10B10A2_UNORM ? DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020
			: _scd.format == DXGI_FORMAT_R16G16B16A16_FLOAT ? DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709
			: DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709
			;

		hr = swapChain4->SetColorSpace1( colorSpace );

		if( SUCCEEDED( hr ) )
		{
			DXGI_OUTPUT_DESC1 desc;

			IDXGIOutput * output;
			hr = _swapChain->GetContainingOutput( &output );
			if( SUCCEEDED( hr ) )
			{
				IDXGIOutput6 * output6;
				hr = output->QueryInterface( IID_IDXGIOutput6, ( void ** ) &output6 );
				if( SUCCEEDED( hr ) )
				{
					hr = output6->GetDesc1( &desc );
					if( SUCCEEDED( hr ) )
					{
						XE_LOG( LoggerLevel::Message, "Display specs:" );
						XE_LOG( LoggerLevel::Message, "\tBitsPerColor: %1", desc.BitsPerColor );
						XE_LOG( LoggerLevel::Message, "\tColor space: %1 (colorspace, range, gamma, sitting, primaries, transform)"
								, ColorSpaceStr[std::min<uint32_t>( desc.ColorSpace, DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020 + 1 )] );
						XE_LOG( LoggerLevel::Message, "\tRedPrimary: %1, %2", desc.RedPrimary[0], desc.RedPrimary[1] );
						XE_LOG( LoggerLevel::Message, "\tGreenPrimary: %1, %2", desc.GreenPrimary[0], desc.GreenPrimary[1] );
						XE_LOG( LoggerLevel::Message, "\tBluePrimary: %1, %2", desc.BluePrimary[0], desc.BluePrimary[1] );
						XE_LOG( LoggerLevel::Message, "\tWhitePoint: %1, %2", desc.WhitePoint[0], desc.WhitePoint[1] );
						XE_LOG( LoggerLevel::Message, "\tMinLuminance: %1", desc.MinLuminance );
						XE_LOG( LoggerLevel::Message, "\tMaxLuminance: %1", desc.MaxLuminance );
						XE_LOG( LoggerLevel::Message, "\tMaxFullFrameLuminance: %1", desc.MaxFullFrameLuminance );
					}

					DX_RELEASE( output6 );
				}

				DX_RELEASE( output );
			}

			DXGI_HDR_METADATA_HDR10 hdr10;
			hdr10.RedPrimary[0] = uint16_t( desc.RedPrimary[0] * 50000.0f );
			hdr10.RedPrimary[1] = uint16_t( desc.RedPrimary[1] * 50000.0f );
			hdr10.GreenPrimary[0] = uint16_t( desc.GreenPrimary[0] * 50000.0f );
			hdr10.GreenPrimary[1] = uint16_t( desc.GreenPrimary[1] * 50000.0f );
			hdr10.BluePrimary[0] = uint16_t( desc.BluePrimary[0] * 50000.0f );
			hdr10.BluePrimary[1] = uint16_t( desc.BluePrimary[1] * 50000.0f );
			hdr10.WhitePoint[0] = uint16_t( desc.WhitePoint[0] * 50000.0f );
			hdr10.WhitePoint[1] = uint16_t( desc.WhitePoint[1] * 50000.0f );
			hdr10.MaxMasteringLuminance = uint32_t( desc.MaxLuminance * 10000.0f );
			hdr10.MinMasteringLuminance = uint32_t( desc.MinLuminance * 10000.0f );
			hdr10.MaxContentLightLevel = uint16_t( desc.MaxFullFrameLuminance );
			hdr10.MaxFrameAverageLightLevel = uint16_t( desc.MaxFullFrameLuminance );
			hr = swapChain4->SetHDRMetaData( DXGI_HDR_METADATA_TYPE_HDR10, sizeof( DXGI_HDR_METADATA_HDR10 ), &hdr10 );
		}

		DX_RELEASE( swapChain4 );
	}
}

HRESULT XE::DXGI::ResizeBuffers( SwapChainI * _swapChain, const SwapChainDesc & _scd, const XE::uint32 * _nodeMask /*= nullptr*/, UnknownI * const * _presentQueue /*= nullptr */ )
{
	HRESULT hr;

	if( nullptr != _nodeMask && nullptr != _presentQueue )
	{
		hr = _swapChain->ResizeBuffers1(
			_scd.bufferCount
			, _scd.width
			, _scd.height
			, _scd.format
			, _scd.flags
			, _nodeMask
			, _presentQueue
		);
	}
	else
	{
		hr = _swapChain->ResizeBuffers(
			_scd.bufferCount
			, _scd.width
			, _scd.height
			, _scd.format
			, _scd.flags
		);
	}

	if( SUCCEEDED( hr ) )
	{
		UpdateHdr10( _swapChain, _scd );
	}

	return hr;
}

#endif