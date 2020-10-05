#include "RendererContextDirectX11.h"
#if 0//PLATFORM_OS & (OS_WINDOWS)

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <d3dcommon.h>

#ifdef max
#undef max
#endif // max

#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

#define XE_CHECK( __X ) \
if( FAILED( __X ) ) \
{ \
	XE_ASSERT( false && #__X ); \
}


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


static DXGI_SAMPLE_DESC G_MSAA[] =
{
	{  1, 0 },
	{  2, 0 },
	{  4, 0 },
	{  8, 0 },
	{ 16, 0 },
};

struct UavFormat
{
	DXGI_FORMAT format[3];
	uint32_t    stride;
};
static const UavFormat G_UAVFormat[] =
{
	{ { DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN            },  0 },
	{ { DXGI_FORMAT_R8_SINT,           DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_UNKNOWN            },  1 },
	{ { DXGI_FORMAT_R8G8_SINT,         DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_UNKNOWN            },  2 },
	{ { DXGI_FORMAT_R8G8B8A8_SINT,     DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_UNKNOWN            },  4 },
	{ { DXGI_FORMAT_R16_SINT,          DXGI_FORMAT_R16_UINT,           DXGI_FORMAT_R16_FLOAT          },  2 },
	{ { DXGI_FORMAT_R16G16_SINT,       DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R16G16_FLOAT       },  4 },
	{ { DXGI_FORMAT_R16G16B16A16_SINT, DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R16G16B16A16_FLOAT },  8 },
	{ { DXGI_FORMAT_R32_SINT,          DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_FLOAT          },  4 },
	{ { DXGI_FORMAT_R32G32_SINT,       DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_FLOAT       },  8 },
	{ { DXGI_FORMAT_R32G32B32A32_SINT, DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_FLOAT }, 16 },
};

static const char * G_ColorSpaceString[] =
{
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
	"Custom",
};
static constexpr XE::uint64 G_ColorSpaceString_Size = 21;

static const GUID G_DXGIDeviceIIDs[] =
{
	__uuidof( IDXGIDevice4 ),
	__uuidof( IDXGIDevice3 ),
	__uuidof( IDXGIDevice2 ),
	__uuidof( IDXGIDevice1 ),
};
static constexpr XE::uint64 G_DXGIDeviceIIDs_Size = 4;

static const GUID G_D3DDeviceIIDs[] =
{
	__uuidof( ID3D11Device5 ),
	__uuidof( ID3D11Device4 ),
	__uuidof( ID3D11Device3 ),
	__uuidof( ID3D11Device2 ),
	__uuidof( ID3D11Device1 ),
};
static constexpr XE::uint64 G_D3DDeviceIIDs_Size = 5;

struct TextureFormatInfo
{
	DXGI_FORMAT m_fmt;
	DXGI_FORMAT m_fmtSrv;
	DXGI_FORMAT m_fmtDsv;
	DXGI_FORMAT m_fmtSrgb;
};
static const TextureFormatInfo G_D3D11TextureFormat[] =
{
	{ DXGI_FORMAT_BC1_UNORM,          DXGI_FORMAT_BC1_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC1_UNORM_SRGB       }, // BC1
	{ DXGI_FORMAT_BC2_UNORM,          DXGI_FORMAT_BC2_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC2_UNORM_SRGB       }, // BC2
	{ DXGI_FORMAT_BC3_UNORM,          DXGI_FORMAT_BC3_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC3_UNORM_SRGB       }, // BC3
	{ DXGI_FORMAT_BC4_UNORM,          DXGI_FORMAT_BC4_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // BC4
	{ DXGI_FORMAT_BC5_UNORM,          DXGI_FORMAT_BC5_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // BC5
	{ DXGI_FORMAT_BC6H_SF16,          DXGI_FORMAT_BC6H_SF16,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // BC6H
	{ DXGI_FORMAT_BC7_UNORM,          DXGI_FORMAT_BC7_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_BC7_UNORM_SRGB       }, // BC7
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC1
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC2
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC2A
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ETC2A1
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC12
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC14
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC12A
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC14A
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC22
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // PTC24
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ATC
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ATCE
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ATCI
	{ DXGI_FORMAT_ASTC_4X4_UNORM,     DXGI_FORMAT_ASTC_4X4_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_4X4_UNORM_SRGB  }, // ASTC4x4
	{ DXGI_FORMAT_ASTC_5X5_UNORM,     DXGI_FORMAT_ASTC_5X5_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_5X5_UNORM_SRGB  }, // ASTC5x5
	{ DXGI_FORMAT_ASTC_6X6_UNORM,     DXGI_FORMAT_ASTC_6X6_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_6X6_UNORM_SRGB  }, // ASTC6x6
	{ DXGI_FORMAT_ASTC_8X5_UNORM,     DXGI_FORMAT_ASTC_8X5_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_8X5_UNORM_SRGB  }, // ASTC8x5
	{ DXGI_FORMAT_ASTC_8X6_UNORM,     DXGI_FORMAT_ASTC_8X6_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_8X6_UNORM_SRGB  }, // ASTC8x6
	{ DXGI_FORMAT_ASTC_10X5_UNORM,    DXGI_FORMAT_ASTC_10X5_UNORM,       DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_ASTC_10X5_UNORM_SRGB }, // ASTC10x5
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // Unknown
	{ DXGI_FORMAT_R1_UNORM,           DXGI_FORMAT_R1_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R1
	{ DXGI_FORMAT_A8_UNORM,           DXGI_FORMAT_A8_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // A8
	{ DXGI_FORMAT_R8_UNORM,           DXGI_FORMAT_R8_UNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8
	{ DXGI_FORMAT_R8_SINT,            DXGI_FORMAT_R8_SINT,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8I
	{ DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_R8_UINT,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8U
	{ DXGI_FORMAT_R8_SNORM,           DXGI_FORMAT_R8_SNORM,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R8S
	{ DXGI_FORMAT_R16_UNORM,          DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16
	{ DXGI_FORMAT_R16_SINT,           DXGI_FORMAT_R16_SINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16I
	{ DXGI_FORMAT_R16_UINT,           DXGI_FORMAT_R16_UINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16U
	{ DXGI_FORMAT_R16_FLOAT,          DXGI_FORMAT_R16_FLOAT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16F
	{ DXGI_FORMAT_R16_SNORM,          DXGI_FORMAT_R16_SNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16S
	{ DXGI_FORMAT_R32_SINT,           DXGI_FORMAT_R32_SINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R32I
	{ DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_UINT,              DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R32U
	{ DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R32F
	{ DXGI_FORMAT_R8G8_UNORM,         DXGI_FORMAT_R8G8_UNORM,            DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8
	{ DXGI_FORMAT_R8G8_SINT,          DXGI_FORMAT_R8G8_SINT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8I
	{ DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_R8G8_UINT,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8U
	{ DXGI_FORMAT_R8G8_SNORM,         DXGI_FORMAT_R8G8_SNORM,            DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG8S
	{ DXGI_FORMAT_R16G16_UNORM,       DXGI_FORMAT_R16G16_UNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16
	{ DXGI_FORMAT_R16G16_SINT,        DXGI_FORMAT_R16G16_SINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16I
	{ DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R16G16_UINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16U
	{ DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_FLOAT,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16F
	{ DXGI_FORMAT_R16G16_SNORM,       DXGI_FORMAT_R16G16_SNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG16S
	{ DXGI_FORMAT_R32G32_SINT,        DXGI_FORMAT_R32G32_SINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG32I
	{ DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_UINT,           DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG32U
	{ DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_R32G32_FLOAT,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG32F
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8I
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8U
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB8S
	{ DXGI_FORMAT_R9G9B9E5_SHAREDEXP, DXGI_FORMAT_R9G9B9E5_SHAREDEXP,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB9E5F
	{ DXGI_FORMAT_B8G8R8A8_UNORM,     DXGI_FORMAT_B8G8R8A8_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_B8G8R8A8_UNORM_SRGB  }, // BGRA8
	{ DXGI_FORMAT_R8G8B8A8_UNORM,     DXGI_FORMAT_R8G8B8A8_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB  }, // RGBA8
	{ DXGI_FORMAT_R8G8B8A8_SINT,      DXGI_FORMAT_R8G8B8A8_SINT,         DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB  }, // RGBA8I
	{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UINT,         DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_R8G8B8A8_UNORM_SRGB  }, // RGBA8U
	{ DXGI_FORMAT_R8G8B8A8_SNORM,     DXGI_FORMAT_R8G8B8A8_SNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA8S
	{ DXGI_FORMAT_R16G16B16A16_UNORM, DXGI_FORMAT_R16G16B16A16_UNORM,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16
	{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16I
	{ DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R16G16B16A16_UINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16U
	{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16F
	{ DXGI_FORMAT_R16G16B16A16_SNORM, DXGI_FORMAT_R16G16B16A16_SNORM,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA16S
	{ DXGI_FORMAT_R32G32B32A32_SINT,  DXGI_FORMAT_R32G32B32A32_SINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA32I
	{ DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_UINT,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA32U
	{ DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT,    DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA32F
	{ DXGI_FORMAT_B5G6R5_UNORM,       DXGI_FORMAT_B5G6R5_UNORM,          DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R5G6B5
	{ DXGI_FORMAT_B4G4R4A4_UNORM,     DXGI_FORMAT_B4G4R4A4_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGBA4
	{ DXGI_FORMAT_B5G5R5A1_UNORM,     DXGI_FORMAT_B5G5R5A1_UNORM,        DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB5A1
	{ DXGI_FORMAT_R10G10B10A2_UNORM,  DXGI_FORMAT_R10G10B10A2_UNORM,     DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RGB10A2
	{ DXGI_FORMAT_R11G11B10_FLOAT,    DXGI_FORMAT_R11G11B10_FLOAT,       DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // RG11B10F
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // UnknownDepth
	{ DXGI_FORMAT_R16_TYPELESS,       DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_D16_UNORM,         DXGI_FORMAT_UNKNOWN              }, // D16
	{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D24
	{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D24S8
	{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D32
	{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN              }, // D16F
	{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN              }, // D24F
	{ DXGI_FORMAT_R32_TYPELESS,       DXGI_FORMAT_R32_FLOAT,             DXGI_FORMAT_D32_FLOAT,         DXGI_FORMAT_UNKNOWN              }, // D32F
	{ DXGI_FORMAT_R24G8_TYPELESS,     DXGI_FORMAT_R24_UNORM_X8_TYPELESS, DXGI_FORMAT_D24_UNORM_S8_UINT, DXGI_FORMAT_UNKNOWN              }, // D0S8
};

struct BufferD3D11
{
public:
	void create( ID3D11Device * device, XE::MemoryView data, XE::Flags<XE::BufferFlags> flags, bool vertex = false )
	{
		_size = data.size();
		_flags = flags;

		const bool needUav = XE::BufferFlags::NONE != ( _flags & XE::MakeFlags( XE::BufferFlags::COMPUTEWRITE, XE::BufferFlags::DRAWINDIRECT ) );
		const bool needSrv = XE::BufferFlags::NONE != ( _flags & XE::BufferFlags::COMPUTEREAD );
		const bool drawIndirect = XE::BufferFlags::NONE != ( _flags & XE::BufferFlags::DRAWINDIRECT );
		_dynamic = ( data.empty() && !needUav );


		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = _size;
		desc.BindFlags = ( vertex ? D3D11_BIND_VERTEX_BUFFER : D3D11_BIND_INDEX_BUFFER ) |
			( needUav ? D3D11_BIND_UNORDERED_ACCESS : 0 ) |
			( needSrv ? D3D11_BIND_SHADER_RESOURCE : 0 );

		desc.MiscFlags = ( drawIndirect ? D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS : 0 );

		desc.StructureByteStride = 0;

		DXGI_FORMAT format;
		uint32_t    stride;

		if( drawIndirect )
		{
			format = DXGI_FORMAT_R32G32B32A32_UINT;
			stride = 16;
		}
		else
		{
			auto uavFormat = _flags & XE::BufferFlags::COMPUTEFORMATMASK;
			if( uavFormat == XE::BufferFlags::NONE )
			{
				if( vertex )
				{
					format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					stride = 16;
				}
				else
				{
					if( ( _flags & XE::BufferFlags::INDEX32 ) == XE::BufferFlags::NONE )
					{
						format = DXGI_FORMAT_R16_UINT;
						stride = 2;
					}
					else
					{
						format = DXGI_FORMAT_R32_UINT;
						stride = 4;
					}
				}
			}
			else
			{
				const XE::uint64 uavType = XE::Mathf::satsub<XE::uint64>( ( ( _flags & XE::BufferFlags::COMPUTETYPEMASK ) >> XE::BufferFlags::COMPUTETYPESHIFT ).GetValue(), 1 );
				format = G_UAVFormat[uavFormat.GetValue()].format[uavType];
				stride = G_UAVFormat[uavFormat.GetValue()].stride;
			}
		}


		D3D11_SUBRESOURCE_DATA srd;
		srd.pSysMem = data.data();
		srd.SysMemPitch = 0;
		srd.SysMemSlicePitch = 0;

		if( needUav )
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.CPUAccessFlags = 0;
			desc.StructureByteStride = stride;

			XE_CHECK( device->CreateBuffer( &desc, NULL == data.data() ? NULL : &srd, &_ptr ) );

			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			uavd.Format = format;
			uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			uavd.Buffer.FirstElement = 0;
			uavd.Buffer.NumElements = _size / stride;
			uavd.Buffer.Flags = 0;
			XE_CHECK( device->CreateUnorderedAccessView( _ptr, &uavd, &_uav ) );
		}
		else if( _dynamic )
		{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			XE_CHECK( device->CreateBuffer( &desc, NULL, &_ptr ) );
		}
		else
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.CPUAccessFlags = 0;

			XE_CHECK( device->CreateBuffer( &desc, &srd, &_ptr ) );
		}

		if( needSrv )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			srvd.Format = format;
			srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvd.Buffer.FirstElement = 0;
			srvd.Buffer.NumElements = _size / stride;
			XE_CHECK( device->CreateShaderResourceView( _ptr, &srvd, &_srv ) );
		}
	}

	void update( ID3D11Device * device, ID3D11DeviceContext * deviceCtx, XE::uint32 offset, XE::MemoryView data, bool discard = false )
	{
		XE_ASSERT( _dynamic );

		if( discard )
		{
			D3D11_MAPPED_SUBRESOURCE mapped;
			XE_CHECK( deviceCtx->Map( _ptr, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped ) );
			std::memcpy( ( XE::uint8 * ) mapped.pData + offset, data.data(), data.size() );
			deviceCtx->Unmap( _ptr, 0 );
		}
		else
		{
			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = _size;
			desc.Usage = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
			desc.MiscFlags = 0;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA srd;
			srd.pSysMem = data.data();
			srd.SysMemPitch = 0;
			srd.SysMemSlicePitch = 0;

			D3D11_BOX srcBox;
			srcBox.left = 0;
			srcBox.top = 0;
			srcBox.front = 0;
			srcBox.right = _size;
			srcBox.bottom = 1;
			srcBox.back = 1;

			ID3D11Buffer * ptr;
			XE_CHECK( device->CreateBuffer( &desc, &srd, &ptr ) );

			deviceCtx->CopySubresourceRegion( _ptr
											  , 0
											  , offset
											  , 0
											  , 0
											  , ptr
											  , 0
											  , &srcBox
			);

			ptr->Release();
		}
	}

	void destroy()
	{
		if( _ptr )
		{
			_ptr->Release();
		}

		if( _srv )
		{
			_srv->Release();
		}

		if( _uav )
		{
			_uav->Release();
		}

		_size = 0;
		_dynamic = false;
		_flags = XE::BufferFlags::NONE;
	}

public:
	XE::uint32 _size = 0;
	bool _dynamic = false;
	ID3D11Buffer * _ptr = nullptr;
	ID3D11ShaderResourceView * _srv = nullptr;
	ID3D11UnorderedAccessView * _uav = nullptr;
	XE::Flags<XE::BufferFlags> _flags = XE::BufferFlags::NONE;
};
struct ShaderD3D11
{
	void create( ID3D11Device * device, XE::ShaderType type, XE::MemoryView data )
	{
		switch( type )
		{
		case XE::ShaderType::VS:
			XE_CHECK( device->CreateVertexShader( data.data(), data.size(), nullptr, &_VertexShader ) );
			break;
		case XE::ShaderType::FS:
			XE_CHECK( device->CreatePixelShader( data.data(), data.size(), nullptr, &_PixelShader ) );
			break;
		case XE::ShaderType::CS:
			XE_CHECK( device->CreateComputeShader( data.data(), data.size(), nullptr, &_ComputeShader ) );
			break;
		default:
			break;
		}
	}

	void destroy()
	{
		if( _Uniform )
		{
			_Uniform = nullptr;
		}

		if( _Buffer )
		{
			_Buffer->Release();
			_Buffer = nullptr;
		}

		if( _Ptr )
		{
			_Ptr->Release();
			_Ptr = nullptr;
		}

		_NumPredefinedUniform = 0;
	}

	union
	{
		ID3D11ComputeShader * _ComputeShader;
		ID3D11PixelShader * _PixelShader;
		ID3D11VertexShader * _VertexShader;
		ID3D11DeviceChild * _Ptr;
	};

	ID3D11Buffer * _Buffer;
	XE::UniformBuffer * _Uniform;
	XE::uint16 _NumPredefinedUniform;
	std::array<XE::PredefinedUniform, XE::PredefinedUniform::Type::COUNT > _PredefinedUniform;
};
struct ProgramD3D11
{
	void create( const ShaderD3D11 * _vsh, const ShaderD3D11 * _fsh )
	{
		XE_ASSERT( nullptr != _vsh->_Ptr && "vertex shader doesn't exist." );

		VS = _vsh;
		std::memcpy( PredefinedUniform, _vsh->_PredefinedUniform.data(), _vsh->_NumPredefinedUniform * sizeof( XE::PredefinedUniform ) );
		_NumPredefinedUniform += _vsh->_NumPredefinedUniform;

		if( nullptr != _fsh )
		{
			XE_ASSERT( nullptr != _fsh->_Ptr && "fragment shader doesn't exist." );

			FS = _fsh;
			std::memcpy( &PredefinedUniform[_NumPredefinedUniform], _fsh->_PredefinedUniform.data(), _fsh->_NumPredefinedUniform * sizeof( XE::PredefinedUniform ) );
			_NumPredefinedUniform += _vsh->_NumPredefinedUniform;
		}
	}

	void destroy()
	{
		VS = nullptr;
		FS = nullptr;
		_NumPredefinedUniform = 0;
	}

	const ShaderD3D11 * VS;
	const ShaderD3D11 * FS;
	XE::uint16 _NumPredefinedUniform;
	XE::PredefinedUniform PredefinedUniform[XE::PredefinedUniform::Type::COUNT * 2];
};
struct FrameBufferD3D11
{
	void create( uint8_t num, const XE::Attachment * attachment )
	{
		std::memset( _RTV, 0, sizeof( _RTV ) * sizeof( ID3D11RenderTargetView * ) );
		std::memset( _SRV, 0, sizeof( _SRV ) * sizeof( ID3D11ShaderResourceView * ) );
		std::memset( _UAV, 0, sizeof( _UAV ) * sizeof( ID3D11UnorderedAccessView * ) );

		_DSV = nullptr;
		_SwapChain = nullptr;

		_DenseIndex = std::numeric_limits<XE::uint16>::max();
		_NumTh = num;
		_NeedPresent = false;

		std::memcpy( _Attachment, attachment, num * sizeof( XE::Attachment ) );

		postReset(nullptr);
	}

	void create( IDXGIFactory * factory, ID3D11Device * device, uint16_t _denseIdx, XE::WindowHandle _nwh, uint32_t _width, uint32_t _height, XE::TextureFormat _format, XE::TextureFormat _depthFormat )
	{
		DXGI_SWAP_CHAIN_DESC scd;

		scd.BufferDesc.Width = _width;
		scd.BufferDesc.Height = _height;
		scd.BufferDesc.RefreshRate.Numerator = 1;
		scd.BufferDesc.RefreshRate.Denominator = 60;
		scd.BufferDesc.Format = G_D3D11TextureFormat[(int)_format].m_fmt;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.BufferCount = 2;
		scd.OutputWindow = ( HWND )_nwh.GetValue();
		scd.Windowed = true;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = factory->CreateSwapChain( device, &scd, reinterpret_cast< IDXGISwapChain ** >( &_SwapChain ) );
		XE_CHECK( hr && "failed to create swap chain." );

		ID3D11Resource * ptr;
		XE_CHECK( _SwapChain->GetBuffer( 0, IID_ID3D11Texture2D, ( void ** )&ptr ) );
		XE_CHECK( device->CreateRenderTargetView( ptr, NULL, &_RTV[0] ) );
		ptr->Release();

		DXGI_FORMAT fmtDsv = 
			( _depthFormat > XE::TextureFormat::UNKNOWN_DEPTH && _depthFormat < XE::TextureFormat::COUNT ) ?
			G_D3D11TextureFormat[( int ) _depthFormat].m_fmtDsv : DXGI_FORMAT_D24_UNORM_S8_UINT;

		D3D11_TEXTURE2D_DESC dsd;
		dsd.Width = _width;
		dsd.Height = _height;
		dsd.MipLevels = 1;
		dsd.ArraySize = 1;
		dsd.Format = fmtDsv;
		dsd.SampleDesc = G_MSAA[0];
		dsd.Usage = D3D11_USAGE_DEFAULT;
		dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dsd.CPUAccessFlags = 0;
		dsd.MiscFlags = 0;

		ID3D11Texture2D * depthStencil;
		XE_CHECK( device->CreateTexture2D( &dsd, NULL, &depthStencil ) );
		XE_CHECK( device->CreateDepthStencilView( depthStencil, NULL, &_DSV ) );
		depthStencil->Release();

		_SRV[0] = NULL;
		_Hwnd = _nwh;
		_DenseIndex = _denseIdx;
		_Num = 1;
	}

	uint16_t destroy()
	{
		preReset( true );

		if( _SwapChain )
		{
			_SwapChain->Release();
			_SwapChain = nullptr;
		}

		_Num = 0;
		_Hwnd = XE::WindowHandle::Invalid;
		_NumTh = 0;
		_NeedPresent = false;

		auto index = _DenseIndex;
		_DenseIndex = std::numeric_limits<XE::uint16>::max();

		return index;
	}

	void preReset( bool _force = false )
	{
		if( 0 < _NumTh || _force )
		{
			for( XE::uint32 i = 0; i < _Num; ++i )
			{
				_SRV[i]->Release();
				_SRV[i] = nullptr;

				_RTV[i]->Release();
				_RTV[i] = nullptr;
			}

			_DSV->Release();
			_DSV = nullptr;
		}
	}

	void postReset( ID3D11Device * device )
	{
		_Width = 0;
		_Height = 0;

		if( 0 < _NumTh )
		{
			_Num = 0;
			_NumUAV = 0;

			for( uint32_t ii = 0; ii < _NumTh; ++ii )
			{
				const XE::Attachment & at = _Attachment[ii];

				if( at.handle )
				{
					const TextureD3D11 & texture = s_renderD3D11->m_textures[at.handle.GetValue()];

					if( 0 == _Width )
					{
						switch( texture._Type )
						{
						case XE::TextureType::TEXTURE_2D:
						case XE::TextureType::TEXTURE_CUBE:
						{
							D3D11_TEXTURE2D_DESC desc;
							texture._Texture2d->GetDesc( &desc );
							_Width = desc.Width;
							_Height = desc.Height;

							break;
						}
						case XE::TextureType::TEXTURE_3D:
						{
							D3D11_TEXTURE3D_DESC desc;
							texture._Texture3d->GetDesc( &desc );
							_Width = desc.Width;
							_Height = desc.Height;

							break;
						}
						}
					}

					const uint32_t msaaQuality = XE::Mathf::satsub( ( ( texture._Flags & XE::TextureFlags::RTMSAAMASK ) >> XE::TextureFlags::RTMSAASHIFT ).GetValue(), XE::uint64( 1 ) );
					const DXGI_SAMPLE_DESC & msaa = G_MSAA[msaaQuality];

					if( texture._TextureFormat > XE::TextureFormat::UNKNOWN_DEPTH && texture._TextureFormat < XE::TextureFormat::COUNT )
					{
						XE_CHECK( NULL == _DSV, "Frame buffer already has depth-stencil attached." );

						switch( texture._Type )
						{
						case XE::TextureType::TEXTURE_CUBE:
						{
							D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
							dsvDesc.Format = G_D3D11TextureFormat[texture._TextureFormat].m_fmtDsv;
							if( 1 < msaa.Count )
							{
								dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
								dsvDesc.Texture2DMSArray.ArraySize = 1;
								dsvDesc.Texture2DMSArray.FirstArraySlice = at.layer;
							}
							else
							{
								dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
								dsvDesc.Texture2DArray.ArraySize = 1;
								dsvDesc.Texture2DArray.FirstArraySlice = at.layer;
								dsvDesc.Texture2DArray.MipSlice = at.mip;
							}
							dsvDesc.Flags = 0;
							XE_CHECK( device->CreateDepthStencilView( texture._Ptr, &dsvDesc, &_DSV ) );

							break;
						}
						default:
						case XE::TextureType::TEXTURE_2D:
						{
							D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
							dsvDesc.Format = G_D3D11TextureFormat[texture._TextureFormat].m_fmtDsv;
							dsvDesc.ViewDimension = 1 < msaa.Count ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
							dsvDesc.Flags = 0;
							dsvDesc.Texture2D.MipSlice = at.mip;
							XE_CHECK( device->CreateDepthStencilView( NULL == texture._RT ? texture._Ptr : texture._RT, &dsvDesc, &_DSV ) );

							break;
						}
						}
					}
					else if( XE::Access::WRITE == at.access )
					{
						D3D11_RENDER_TARGET_VIEW_DESC desc;
						desc.Format = texture.GetSrvFormat();
						switch( texture._Type )
						{
						default:
						case XE::TextureType::TEXTURE_2D:
							if( 1 < msaa.Count )
							{
								if( 1 < texture._NumLayers )
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
									desc.Texture2DMSArray.FirstArraySlice = at.layer;
									desc.Texture2DMSArray.ArraySize = 1;
								}
								else
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
								}
							}
							else
							{
								if( 1 < texture._NumLayers )
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
									desc.Texture2DArray.FirstArraySlice = at.layer;
									desc.Texture2DArray.ArraySize = 1;
									desc.Texture2DArray.MipSlice = at.mip;
								}
								else
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
									desc.Texture2D.MipSlice = at.mip;
								}
							}

							XE_CHECK( device->CreateRenderTargetView( NULL == texture._RT ? texture._Ptr : texture._RT, & desc, & _RTV[_Num] ) );
							break;

						case XE::TextureType::TEXTURE_CUBE:
							if( 1 < msaa.Count )
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
								desc.Texture2DMSArray.ArraySize = 1;
								desc.Texture2DMSArray.FirstArraySlice = at.layer;
							}
							else
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
								desc.Texture2DArray.ArraySize = 1;
								desc.Texture2DArray.FirstArraySlice = at.layer;
								desc.Texture2DArray.MipSlice = at.mip;
							}

							XE_CHECK( device->CreateRenderTargetView( texture._Ptr, &desc, &_RTV[_Num] ) );
							break;

						case XE::TextureType::TEXTURE_3D:
							desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
							desc.Texture3D.MipSlice = at.mip;
							desc.Texture3D.WSize = 1;
							desc.Texture3D.FirstWSlice = at.layer;

							XE_CHECK( device->CreateRenderTargetView( texture._Ptr, &desc, &_RTV[_Num] ) );
							break;
						}

						XE_CHECK( device->CreateShaderResourceView( texture._Ptr, NULL, &_SRV[_Num] ) );
						_Num++;
					}
					else
					{
						_UAV[_NumUAV++] = texture._UAV;
					}
				}
			}
		}
	}

	void resolve()
	{
		if( 0 < _NumTh )
		{
			for( uint32_t ii = 0; ii < _NumTh; ++ii )
			{
				const XE::Attachment & at = _Attachment[ii];

				if( at.handle )
				{
					const TextureD3D11 & texture = s_renderD3D11->m_textures[at.handle.GetValue()];
					texture.resolve( at.resolve );
				}
			}
		}
	}

	void clear( ID3D11DeviceContext * deviceCtx, const XE::Flags<XE::ClearFlags> & _clear, const XE::Color & _palette )
	{
		if( _clear && XE::ClearFlags::COLOR )
		{
			if( _clear && XE::ClearFlags::COLOR_USE_PALETTE )
			{
				for( uint32_t ii = 0, num = _Num; ii < num; ++ii )
				{
					uint8_t index = _clear.m_index[ii];
					if( NULL != _RTV[ii]
						&& UINT8_MAX != index )
					{
						deviceCtx->ClearRenderTargetView( _RTV[ii], _palette[index] );
					}
				}
			}
			else
			{
				float frgba[4] =
				{
					_clear.m_index[0] * 1.0f / 255.0f,
					_clear.m_index[1] * 1.0f / 255.0f,
					_clear.m_index[2] * 1.0f / 255.0f,
					_clear.m_index[3] * 1.0f / 255.0f,
				};
				for( uint32_t ii = 0, num = _Num; ii < num; ++ii )
				{
					if( NULL != _RTV[ii] )
					{
						deviceCtx->ClearRenderTargetView( _RTV[ii], frgba );
					}
				}
			}
		}
	}

	void set();

	HRESULT present( uint32_t _syncInterval );

	ID3D11RenderTargetView * _RTV[XE::GFX_MAX_ATTACHMENTS - 1];
	ID3D11ShaderResourceView * _SRV[XE::GFX_MAX_ATTACHMENTS - 1];
	ID3D11UnorderedAccessView * _UAV[XE::GFX_MAX_ATTACHMENTS - 1];
	ID3D11DepthStencilView * _DSV = nullptr;
	IDXGISwapChain3 * _SwapChain = nullptr;
	XE::WindowHandle _Hwnd;
	XE::uint32 _Width = 0;
	XE::uint32 _Height = 0;

	XE::Attachment _Attachment[XE::GFX_MAX_ATTACHMENTS];
	XE::uint16 _DenseIndex = 0;
	XE::uint8 _Num = 0;
	XE::uint8 _NumTh = 0;
	XE::uint8 _NumUAV = 0;
	bool _NeedPresent = false;
};
struct IndexBufferD3D11 : public BufferD3D11
{};
struct VertexBufferD3D11 : public BufferD3D11
{
public:
	void create( ID3D11Device * device, XE::MemoryView data, XE::VertexLayoutHandle layoutHandle, XE::Flags<XE::BufferFlags> flags )
	{
		_layoutHandle = layoutHandle;

		BufferD3D11::create( device, data, flags );
	}

public:
	XE::VertexLayoutHandle _layoutHandle;
};
struct IntelDirectAccessResourceDescriptor
{
	void * _Ptr;
	XE::uint32 _Size;
	XE::uint32 _Pitch;
	XE::uint32 _XOffset;
	XE::uint32 _YOffset;
	XE::uint32 _TileFormat;
};
struct DirectAccessResourceD3D11
{
	void * createTexture2D( const D3D11_TEXTURE2D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture2D ** _gpuTexture2d );
	void * createTexture3D( const D3D11_TEXTURE3D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture3D ** _gpuTexture3d );
	void destroy();

	union
	{
		ID3D11Resource * _Ptr;
		ID3D11Texture2D * _Texture2d;
		ID3D11Texture3D * _Texture3d;
	};

	IntelDirectAccessResourceDescriptor * m_descriptor;
};
struct TextureD3D11
{
	union
	{
		ID3D11Resource * _Ptr;
		ID3D11Texture2D * _Texture2d;
		ID3D11Texture3D * _Texture3d;
	};

	DirectAccessResourceD3D11 m_dar;

	union
	{
		ID3D11Resource * _RT;
		ID3D11Texture2D * _RT2D;
	};


	DXGI_FORMAT GetSrvFormat() const
	{
		if( _TextureFormat > XE::TextureFormat::UNKNOWN_DEPTH && _TextureFormat < XE::TextureFormat::COUNT )
		{
			return G_D3D11TextureFormat[( int ) _TextureFormat].m_fmtSrv;
		}

		return 0 != ( _Flags & XE::TextureFlags::SRGB ).GetValue() ? G_D3D11TextureFormat[( int ) _TextureFormat].m_fmtSrgb : G_D3D11TextureFormat[( int ) _TextureFormat].m_fmt;
	}


	ID3D11ShaderResourceView * _SRV;
	ID3D11UnorderedAccessView * _UAV;
	XE::Flags<XE::TextureFlags> _Flags;
	XE::uint32 _Width;
	XE::uint32 _Height;
	XE::uint32 _Depth;
	XE::uint32 _NumLayers;
	XE::TextureType _Type;
	XE::uint8  _RequestedFormat;
	XE::TextureFormat _TextureFormat;
	XE::uint8  _NumMips;
};


struct XE::RendererContextDirectX11::Private
{
	D3D_FEATURE_LEVEL _FeatureLevel;

	IDXGIOutput * _Output = nullptr;
	IDXGIFactory6 * _Factory = nullptr;
	IDXGIAdapter4 * _Adapter = nullptr;
	D3D_DRIVER_TYPE   _DriverType;
	DXGI_ADAPTER_DESC _AdapterDesc;

	XE::uint32 _DeviceInterfaceVersion = 0;

	IDXGISwapChain4 * _SwapChain = nullptr;
	ID3D11Texture2D * _MsaaRt = nullptr;

	ID3D11Device * _Device = nullptr;
	ID3D11DeviceContext * _DeviceCtx = nullptr;
	ID3DUserDefinedAnnotation * _Annotation = nullptr;
	ID3D11InfoQueue * _InfoQueue = nullptr;

	ID3D11RenderTargetView * _BackBufferColor = nullptr;
	ID3D11DepthStencilView * _BackBufferDepthStencil = nullptr;
	ID3D11RenderTargetView * _CurrentColor = nullptr;
	ID3D11DepthStencilView * _CurrentDepthStencil = nullptr;

	ID3D11Texture2D * _CaptureTexture = nullptr;
	ID3D11Texture2D * _CaptureResolve = nullptr;


	ShaderD3D11 _Shaders[GFX_MAX_SHADERS];
	ProgramD3D11 _Programs[GFX_MAX_PROGRAMS];
	TextureD3D11 _Textures[GFX_MAX_TEXTURES];
	FrameBufferD3D11 _FrameBuffers[GFX_MAX_FRAME_BUFFERS];
	IndexBufferD3D11 _IndexBuffers[GFX_MAX_INDEX_BUFFERS];
	VertexBufferD3D11 _VertexBuffers[GFX_MAX_VERTEX_BUFFERS];
};

XE::RendererContextDirectX11::RendererContextDirectX11()
	:_p( new Private )
{

}

XE::RendererContextDirectX11::~RendererContextDirectX11()
{
	delete _p;
}

void XE::RendererContextDirectX11::OnRender( XE::Frame * val )
{
    ExecCommand( val->PrevCmd );

	RenderItems( val );

	RenderBlits( val );

	ExecCommand( val->PostCmd );
}

void XE::RendererContextDirectX11::RenderItems( XE::Frame * val )
{
	XE::uint64 size = val->RenderItemSize;
	XE::Array<XE::uint64> items( XE::MemoryResource::GetStackMemoryResource() );
	items.resize( size );
	for( XE::uint64 i = 0; i < size; ++i )
	{
		items[i] = i;
	}
	std::sort( items.begin(), items.end(), [ val ]( XE::uint64 left, XE::uint64 right )
		{
			return val->RenderItemKeys[left] < val->RenderItemKeys[right];
		} );

	for( XE::uint64 i = 0; i < size; ++i )
	{
		auto & item = val->RenderItems[items[i]];
		if( item.Type == RenderItem::ItemType::DRAW )
		{
			Draw( item.Draw, val->RenderBinds[items[i]] );
		}
		else
		{
			Compute( item.Compute, val->RenderBinds[items[i]] );
		}
	}
}

void XE::RendererContextDirectX11::RenderBlits( XE::Frame * val )
{
	XE::uint64 size = val->RenderBlitSize;
	XE::Array<XE::uint64> items( XE::MemoryResource::GetStackMemoryResource() );
	items.resize( size );
	for( XE::uint64 i = 0; i < size; ++i )
	{
		items[i] = i;
	}
	std::sort( items.begin(), items.end(), [ val ]( XE::uint64 left, XE::uint64 right )
		{
			return val->RenderBlitKeys[left] < val->RenderBlitKeys[right];
		} );

	for( XE::uint64 i = 0; i < size; ++i )
	{
		Blit( val->RenderBlits[items[i]] );
	}
}

void XE::RendererContextDirectX11::ExecCommand( XE::Buffer & buffer )
{
	buffer.Seek( XE::Buffer::END );

	auto end = buffer.ReadPos();

	buffer.Seek( XE::Buffer::BEG );
	while( buffer.ReadPos() < end )
	{
		XE::CommandType type;
		buffer.Read( type );

		switch( type )
		{
		case XE::CommandType::RENDERER_INIT:
			EXEC_RENDERER_INIT( buffer );
			break;
		case XE::CommandType::RENDERER_SHUTDOWN:
			EXEC_RENDERER_SHUTDOWN( buffer );
			break;
		case XE::CommandType::CREATE_VERTEX_LAYOUT:
			EXEC_CREATE_VERTEX_LAYOUT( buffer );
			break;
		case XE::CommandType::CREATE_INDEX_BUFFER:
			EXEC_CREATE_INDEX_BUFFER( buffer );
			break;
		case XE::CommandType::CREATE_VERTEX_BUFFER:
			EXEC_CREATE_VERTEX_BUFFER( buffer );
			break;
		case XE::CommandType::CREATE_DYNAMIC_INDEX_BUFFER:
			EXEC_CREATE_DYNAMIC_INDEX_BUFFER( buffer );
			break;
		case XE::CommandType::UPDATE_DYNAMIC_INDEX_BUFFER:
			EXEC_UPDATE_DYNAMIC_INDEX_BUFFER( buffer );
			break;
		case XE::CommandType::CREATE_DYNAMIC_VERTEX_BUFFER:
			EXEC_CREATE_DYNAMIC_VERTEX_BUFFER( buffer );
			break;
		case XE::CommandType::UPDATE_DYNAMIC_VERTEX_BUFFER:
			EXEC_UPDATE_DYNAMIC_VERTEX_BUFFER( buffer );
			break;
		case XE::CommandType::CREATE_TRANSIENT_INDEX_BUFFER:
			EXEC_CREATE_TRANSIENT_INDEX_BUFFER( buffer );
			break;
		case XE::CommandType::CREATE_TRANSIENT_VERTEX_BUFFER:
			EXEC_CREATE_TRANSIENT_VERTEX_BUFFER( buffer );
			break;
		case XE::CommandType::CREATE_SHADER:
			EXEC_CREATE_SHADER( buffer );
			break;
		case XE::CommandType::CREATE_PROGRAM:
			EXEC_CREATE_PROGRAM( buffer );
			break;
		case XE::CommandType::CREATE_TEXTURE:
			EXEC_CREATE_TEXTURE( buffer );
			break;
		case XE::CommandType::UPDATE_TEXTURE:
			EXEC_UPDATE_TEXTURE( buffer );
			break;
		case XE::CommandType::RESIZE_TEXTURE:
			EXEC_RESIZE_TEXTURE( buffer );
			break;
		case XE::CommandType::CREATE_FRAME_BUFFER:
			EXEC_CREATE_FRAME_BUFFER( buffer );
			break;
		case XE::CommandType::CREATE_UNIFORM:
			EXEC_CREATE_UNIFORM( buffer );
			break;
		case XE::CommandType::CREATE_OCCLUSION_QUERY:
			EXEC_CREATE_OCCLUSION_QUERY( buffer );
			break;
		case XE::CommandType::END:
			EXEC_END( buffer );
			break;
		case XE::CommandType::DESTROY_VERTEX_LAYOUT:
			EXEC_DESTROY_VERTEX_LAYOUT( buffer );
			break;
		case XE::CommandType::DESTROY_INDEX_BUFFER:
			EXEC_DESTROY_INDEX_BUFFER( buffer );
			break;
		case XE::CommandType::DESTROY_VERTEX_BUFFER:
			EXEC_DESTROY_VERTEX_BUFFER( buffer );
			break;
		case XE::CommandType::DESTROY_DYNAMIC_INDEX_BUFFER:
			EXEC_DESTROY_DYNAMIC_INDEX_BUFFER( buffer );
			break;
		case XE::CommandType::DESTROY_DYNAMIC_VERTEX_BUFFER:
			EXEC_DESTROY_DYNAMIC_VERTEX_BUFFER( buffer );
			break;
		case XE::CommandType::DESTROY_SHADER:
			EXEC_DESTROY_SHADER( buffer );
			break;
		case XE::CommandType::DESTROY_PROGRAM:
			EXEC_DESTROY_PROGRAM( buffer );
			break;
		case XE::CommandType::DESTROY_TEXTURE:
			EXEC_DESTROY_TEXTURE( buffer );
			break;
		case XE::CommandType::DESTROY_FRAMEBUFFER:
			EXEC_DESTROY_FRAMEBUFFER( buffer );
			break;
		case XE::CommandType::DESTROY_UNIFORM:
			EXEC_DESTROY_UNIFORM( buffer );
			break;
		case XE::CommandType::READ_TEXTURE:
			EXEC_READ_TEXTURE( buffer );
			break;
		case XE::CommandType::DESTROY_OCCLUSION_QUERY:
			EXEC_DESTROY_OCCLUSION_QUERY( buffer );
			break;
		case XE::CommandType::REQUEST_SCREEN_SHOT:
			EXEC_REQUEST_SCREEN_SHOT( buffer );
			break;
		default:
			break;
		}
	}
}

void XE::RendererContextDirectX11::Blit( const RenderBlit & blit )
{

}

void XE::RendererContextDirectX11::Draw( const RenderDraw & draw, const RenderBind & bind )
{

}

void XE::RendererContextDirectX11::Compute( const RenderCompute & compute, const RenderBind & bind )
{

}

void XE::RendererContextDirectX11::EXEC_RENDERER_INIT( XE::Buffer & buffer )
{
	HRESULT hr = S_OK;

	XE_CHECK( CreateDXGIFactory( __uuidof( IDXGIFactory ), ( void ** ) &_p->_Factory ) );

	IDXGIAdapter4 * adapter;
	for( uint32_t i = 0; DXGI_ERROR_NOT_FOUND != _p->_Factory->EnumAdapters( i, reinterpret_cast< IDXGIAdapter ** >( &adapter ) ) && i < 4; ++i )
	{
		{
			DXGI_ADAPTER_DESC desc;
			hr = adapter->GetDesc( &desc );
			if( SUCCEEDED( hr ) )
			{
				XE_LOG( XE::LoggerLevel::Message, "Adapter #%d", i );

				char description[128];
				wcstombs( description, desc.Description, 128 );

				XE_LOG( XE::LoggerLevel::Message, "\tDescription: %s", description );
				XE_LOG( XE::LoggerLevel::Message, "\tVendorId: %1, DeviceId: %2, SubSysId: %3, Revision: %4", desc.VendorId, desc.DeviceId, desc.SubSysId, desc.Revision );
				XE_LOG( XE::LoggerLevel::Message, "\tMemory: %1 (video), %2 (system), %3 (shared)", desc.DedicatedVideoMemory, desc.DedicatedSystemMemory, desc.SharedSystemMemory );

				GetCaps().gpu[i].VendorId = ( PciIdFlags )desc.VendorId;
				GetCaps().gpu[i].DeviceId = ( uint16_t )desc.DeviceId;
				++GetCaps().numGPUs;

				if( _p->_Adapter == nullptr )
				{
					if( ( PciIdFlags::NONE != GetCaps().VendorId || 0 != GetCaps().DeviceId ) &&
						( PciIdFlags::NONE != GetCaps().VendorId || ( PciIdFlags )desc.VendorId == GetCaps().VendorId ) &&
						( 0 != GetCaps().DeviceId || desc.DeviceId == GetCaps().DeviceId ) )
					{
						_p->_Adapter = adapter;
						_p->_Adapter->AddRef();
						_p->_DriverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN;
					}
				}
			}
		}

		bool hdr10 = false;

		IDXGIOutput * output;
		for( uint32_t j = 0; SUCCEEDED( adapter->EnumOutputs( j, &output ) ); ++j )
		{
			DXGI_OUTPUT_DESC outputDesc;
			hr = output->GetDesc( &outputDesc );
			if( SUCCEEDED( hr ) )
			{
				XE_LOG( XE::LoggerLevel::Message, "\tOutput #%d", j );

				char deviceName[32];
				wcstombs( deviceName, outputDesc.DeviceName, 32 );
				XE_LOG( XE::LoggerLevel::Message, "\t\t           DeviceName: %1", deviceName );
				XE_LOG( XE::LoggerLevel::Message, "\t\t   DesktopCoordinates: %1, %2, %3, %4"
						, outputDesc.DesktopCoordinates.left
						, outputDesc.DesktopCoordinates.top
						, outputDesc.DesktopCoordinates.right
						, outputDesc.DesktopCoordinates.bottom
				);
				XE_LOG( XE::LoggerLevel::Message, "\t\t    AttachedToDesktop: %1", outputDesc.AttachedToDesktop );
				XE_LOG( XE::LoggerLevel::Message, "\t\t             Rotation: %1", outputDesc.Rotation );

				IDXGIOutput6 * output6;
				hr = output->QueryInterface( __uuidof( IDXGIOutput6 ), ( void ** )&output6 );
				if( SUCCEEDED( hr ) )
				{
					DXGI_OUTPUT_DESC1 desc;
					hr = output6->GetDesc1( &desc );
					if( SUCCEEDED( hr ) )
					{
						XE_LOG( XE::LoggerLevel::Message, "\t\t         BitsPerColor: %1", desc.BitsPerColor );
						XE_LOG( XE::LoggerLevel::Message, "\t\t          Color space: %1 (colorspace, range, gamma, sitting, primaries, transform)", G_ColorSpaceString[std::min<uint32_t>( desc.ColorSpace, DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020 + 1 )] );
						XE_LOG( XE::LoggerLevel::Message, "\t\t           RedPrimary: %1, %2", desc.RedPrimary[0], desc.RedPrimary[1] );
						XE_LOG( XE::LoggerLevel::Message, "\t\t         GreenPrimary: %1, %2", desc.GreenPrimary[0], desc.GreenPrimary[1] );
						XE_LOG( XE::LoggerLevel::Message, "\t\t          BluePrimary: %1, %2", desc.BluePrimary[0], desc.BluePrimary[1] );
						XE_LOG( XE::LoggerLevel::Message, "\t\t           WhitePoint: %1, %2", desc.WhitePoint[0], desc.WhitePoint[1] );
						XE_LOG( XE::LoggerLevel::Message, "\t\t         MinLuminance: %1", desc.MinLuminance );
						XE_LOG( XE::LoggerLevel::Message, "\t\t         MaxLuminance: %1", desc.MaxLuminance );
						XE_LOG( XE::LoggerLevel::Message, "\t\tMaxFullFrameLuminance: %1", desc.MaxFullFrameLuminance );
						XE_LOG( XE::LoggerLevel::Message, "\t\t          HDR support: %1", DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 == desc.ColorSpace ? "true" : "false" );

						hdr10 |= DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 == desc.ColorSpace;
					}

					output6->Release();
				}

				output->Release();
			}
		}

		if( hdr10 )
		{
			GetCaps().Supported |= CapsFlags::HDR10;
		}

		adapter->Release();
	}

	if( _p->_Adapter == nullptr )
	{
		XE_CHECK( _p->_Factory->EnumAdapters( 0, reinterpret_cast< IDXGIAdapter ** >( &_p->_Adapter ) ) );

		_p->_DriverType = D3D_DRIVER_TYPE_UNKNOWN;
	}

	std::memset( &_p->_AdapterDesc, 0, sizeof( _p->_AdapterDesc ) );
	XE_CHECK( _p->_Adapter->GetDesc( &_p->_AdapterDesc ) );
	_p->_Adapter->EnumOutputs( 0, &_p->_Output );

	GetCaps().VendorId = _p->_AdapterDesc.VendorId == 0 ? PciIdFlags::SOFTWARERASTERIZER : ( PciIdFlags )_p->_AdapterDesc.VendorId;
	GetCaps().DeviceId = ( uint16_t )_p->_AdapterDesc.DeviceId;

	/////////////////////////////////////////////////////////////////

	D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
	static constexpr XE::uint32 featureLevel_Size = 2;

	for( ;;)
	{
		uint32_t flags = D3D11_CREATE_DEVICE_SINGLETHREADED |
			D3D11_CREATE_DEVICE_BGRA_SUPPORT |
			( GetInit().debug ? D3D11_CREATE_DEVICE_DEBUG : 0 );

		hr = E_FAIL;
		for( uint32_t ii = 0; ii < featureLevel_Size && FAILED( hr ); ++ii )
		{
			hr = D3D11CreateDevice( _p->_Adapter,
									_p->_DriverType
									, NULL
									, flags
									, &featureLevel[ii]
									, featureLevel_Size - ii
									, D3D11_SDK_VERSION
									, &_p->_Device
									, &_p->_FeatureLevel
									, &_p->_DeviceCtx
			);
			if( FAILED( hr ) )
			{
				flags &= ~D3D11_CREATE_DEVICE_DEBUG;
				XE_LOG( LoggerLevel::Error, "Direct3D11 device feature level %1.%2.", ( _p->_FeatureLevel >> 12 ) & 0xf, ( _p->_FeatureLevel >> 8 ) & 0xf );
			}
		}

		if( FAILED( hr ) && D3D_DRIVER_TYPE_WARP != _p->_DriverType )
		{
			_p->_DriverType = D3D_DRIVER_TYPE_WARP;
			continue;
		}

		break;
	}

	if( FAILED( hr ) )
	{
		XE_LOG( LoggerLevel::Error, "Init error: Unable to create Direct3D11 device." );
		XE_ASSERT( false && "Init error: Unable to create Direct3D11 device." );
	}

	{
		IDXGIDevice * dxgiDevice = NULL;
		for( uint32_t ii = 0; ii < G_DXGIDeviceIIDs_Size && FAILED( hr ); ++ii )
		{
			hr = _p->_Device->QueryInterface( G_DXGIDeviceIIDs[ii], ( void ** )&dxgiDevice );
			XE_LOG( LoggerLevel::Message, "DXGI device 11.%1, hr %2", 4 - 1 - ii, hr );
		}

		XE_CHECK( dxgiDevice->GetAdapter( reinterpret_cast< IDXGIAdapter ** >( &_p->_Adapter ) ) );

		std::memset( &_p->_AdapterDesc, 0, sizeof( _p->_AdapterDesc ) );
		hr = _p->_Adapter->GetDesc( &_p->_AdapterDesc );
		if( FAILED( hr ) )
		{
			XE_LOG( LoggerLevel::Message, "Adapter GetDesc failed %1.", hr );
		}

		XE_CHECK( _p->_Adapter->GetParent( __uuidof( IDXGIFactory2 ), ( void ** ) &_p->_Factory ) );

		dxgiDevice->Release();
	}


	{
		_p->_DeviceInterfaceVersion = 0;
		for( uint32_t ii = 0; ii < G_D3DDeviceIIDs_Size; ++ii )
		{
			ID3D11Device * device;
			hr = _p->_Device->QueryInterface( G_D3DDeviceIIDs[ii], ( void ** )&device );
			if( SUCCEEDED( hr ) )
			{
				device->Release(); // BK - ignore ref count.
				_p->_DeviceInterfaceVersion = G_D3DDeviceIIDs_Size - ii;
				break;
			}
		}

		{ // RenderDoc
// 			IDXGIDevice * renderdoc;
// 			hr = _p->_Device->QueryInterface( __uuidof( IDXGIDeviceRenderDoc ), (void **)&renderdoc );
// 			if( SUCCEEDED( hr ) )
// 			{
// 				setGraphicsDebuggerPresent( true );
// 				DX_RELEASE( renderdoc, 2 );
// 			}
// 			else
// 			{
// 				IUnknown * device = m_device;
// 				setGraphicsDebuggerPresent( 2 != getRefCount( device ) );
// 			}
		}


		if( GetInit().debug )
		{
			hr = _p->_Device->QueryInterface( __uuidof( ID3D11InfoQueue ), ( void ** )&_p->_InfoQueue );

			if( SUCCEEDED( hr ) )
			{
				_p->_InfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_CORRUPTION, true );
				_p->_InfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_ERROR, false );
				_p->_InfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_WARNING, false );
				_p->_InfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_INFO, false );
				_p->_InfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_MESSAGE, false );

				D3D11_INFO_QUEUE_FILTER filter;
				std::memset( &filter, 0, sizeof( filter ) );

				D3D11_MESSAGE_CATEGORY catlist[] =
				{
					D3D11_MESSAGE_CATEGORY_STATE_CREATION,
				};

				filter.DenyList.NumCategories = 1;
				filter.DenyList.pCategoryList = catlist;

				D3D11_MESSAGE_ID idlist[] =
				{
					D3D11_MESSAGE_ID_DEVICE_DRAW_RENDERTARGETVIEW_NOT_SET,
					D3D11_MESSAGE_ID_QUERY_BEGIN_ABANDONING_PREVIOUS_RESULTS,
				};

				filter.DenyList.NumIDs = 2;
				filter.DenyList.pIDList = idlist;

				_p->_InfoQueue->PushStorageFilter( &filter );
			}
		}


		{
			GetCaps().Supported = GetCaps().Supported
				| CapsFlags::TEXTURE3D
				| CapsFlags::VERTEXATTRIBHALF
				| CapsFlags::VERTEXATTRIBUINT10
				| CapsFlags::VERTEXID
				| CapsFlags::FRAGMENTDEPTH
				| CapsFlags::TEXTUREDIRECTACCESS
				| CapsFlags::SWAPCHAIN
				| CapsFlags::DRAWINDIRECT
				| CapsFlags::TEXTUREBLIT
				| CapsFlags::TEXTUREREADBACK
				| CapsFlags::OCCLUSIONQUERY
				| CapsFlags::ALPHATOCOVERAGE
				| CapsFlags::CONSERVATIVERASTER
				| CapsFlags::TEXTURE2DARRAY
				| CapsFlags::TEXTURECUBEARRAY
				| CapsFlags::FRAMEBUFFERRW;

			{
				GetCaps().MaxComputeBindings = D3D11_PS_CS_UAV_REGISTER_COUNT;
				GetCaps().MaxTextureSize = D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
				GetCaps().MaxTextureLayers = D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION;
				GetCaps().MaxFBAttachments = D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT;
				GetCaps().MaxVertexStreams = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT;
				GetCaps().Supported = GetCaps().Supported
					| CapsFlags::INDEX32
					| CapsFlags::BLENDINDEPENDENT
					| CapsFlags::COMPUTE
					| CapsFlags::INSTANCING;
			}

			GetCaps().SupportFormat = GetCaps().SupportFormat
				| CapsFormatFlags::TEXTURE2D
				| CapsFormatFlags::TEXTURE3D
				| CapsFormatFlags::TEXTURECUBE
				| CapsFormatFlags::TEXTUREIMAGE
				| CapsFormatFlags::TEXTUREVERTEX
				| CapsFormatFlags::TEXTUREIMAGE
				| CapsFormatFlags::TEXTUREFRAMEBUFFER
				| CapsFormatFlags::TEXTUREFRAMEBUFFERMSAA
				| CapsFormatFlags::TEXTUREMSAA
				;

			if( GetInit().debug && _p->_InfoQueue != nullptr )
			{
				_p->_InfoQueue->SetBreakOnSeverity( D3D11_MESSAGE_SEVERITY_ERROR, true );
			}
		}
	}
}

void XE::RendererContextDirectX11::EXEC_RENDERER_SHUTDOWN( XE::Buffer & buffer )
{
	_p->_CaptureTexture->Release();
	_p->_CaptureResolve->Release();

	_p->_BackBufferColor->Release();
	_p->_BackBufferDepthStencil->Release();
	_p->_CurrentColor->Release();
	_p->_CurrentDepthStencil->Release();

	_p->_Device->Release();
	_p->_DeviceCtx->Release();
	_p->_Annotation->Release();
	_p->_InfoQueue->Release();

	_p->_SwapChain->Release();
	_p->_MsaaRt->Release();

	_p->_Output->Release();
	_p->_Factory->Release();
	_p->_Adapter->Release();
}

void XE::RendererContextDirectX11::EXEC_CREATE_VERTEX_LAYOUT( XE::Buffer & buffer )
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_INDEX_BUFFER( XE::Buffer & buffer )
{
	XE::String name;
	XE::MemoryView mem;
	XE::IndexBufferHandle handle;
	XE::Flags< XE::BufferFlags > flags;

	buffer.Read( handle );
	buffer.Read( name );
	buffer.Read( mem );
	buffer.Read( flags );

	_p->_IndexBuffers[handle].create( _p->_Device, mem, flags, false );
}

void XE::RendererContextDirectX11::EXEC_CREATE_VERTEX_BUFFER( XE::Buffer & buffer )
{
	XE::String name;
	XE::MemoryView mem;
	XE::VertexBufferHandle handle;
	XE::VertexLayoutHandle layout;
	XE::Flags< XE::BufferFlags > flags;

	buffer.Read( handle );
	buffer.Read( name );
	buffer.Read( mem );
	buffer.Read( layout );
	buffer.Read( flags );

	_p->_VertexBuffers[handle].create( _p->_Device, mem, layout, flags );
}

void XE::RendererContextDirectX11::EXEC_CREATE_DYNAMIC_INDEX_BUFFER( XE::Buffer & buffer )
{
	XE::String name;
	XE::MemoryView mem;
	XE::IndexBufferHandle handle;
	XE::Flags< XE::BufferFlags > flags;

	buffer.Read( handle );
	buffer.Read( name );
	buffer.Read( mem );
	buffer.Read( flags );

	_p->_IndexBuffers[handle].create( _p->_Device, mem, flags, false );
}

void XE::RendererContextDirectX11::EXEC_UPDATE_DYNAMIC_INDEX_BUFFER( XE::Buffer & buffer )
{
	XE::uint64 start;
	XE::MemoryView mem;
	XE::DynamicIndexBufferHandle handle;

	buffer.Read( handle );
	buffer.Read( start );
	buffer.Read( mem );

	_p->_IndexBuffers[handle].update( _p->_Device, _p->_DeviceCtx, start, mem );
}

void XE::RendererContextDirectX11::EXEC_CREATE_DYNAMIC_VERTEX_BUFFER( XE::Buffer & buffer )
{
	XE::uint64 size;
	XE::VertexLayoutHandle layout;
	XE::Flags< XE::BufferFlags > flags;
	XE::DynamicVertexBufferHandle handle;

	buffer.Read( handle );
	buffer.Read( size );
	buffer.Read( layout );
	buffer.Read( flags );

	_p->_VertexBuffers[handle].create( _p->_Device, nullptr, layout, flags );
}

void XE::RendererContextDirectX11::EXEC_UPDATE_DYNAMIC_VERTEX_BUFFER( XE::Buffer & buffer )
{
	XE::uint64 start;
	XE::MemoryView mem;
	XE::DynamicVertexBufferHandle handle;

	buffer.Read( handle );
	buffer.Read( start );
	buffer.Read( mem );

	_p->_VertexBuffers[handle].update( _p->_Device, _p->_DeviceCtx, start, mem );
}

void XE::RendererContextDirectX11::EXEC_CREATE_TRANSIENT_INDEX_BUFFER( XE::Buffer & buffer )
{
	XE::MemoryView mem;
	XE::Flags< XE::BufferFlags > flags;
	XE::TransientIndexBufferHandle handle;

	buffer.Read( handle );
	buffer.Read( mem );
	buffer.Read( flags );


}

void XE::RendererContextDirectX11::EXEC_CREATE_TRANSIENT_VERTEX_BUFFER( XE::Buffer & buffer )
{
	XE::MemoryView mem;
	XE::VertexLayoutHandle layout;
	XE::Flags< XE::BufferFlags > flags;
	XE::TransientIndexBufferHandle handle;

	buffer.Read( handle );
	buffer.Read( mem );
	buffer.Read( flags );
	buffer.Read( flags );


}

void XE::RendererContextDirectX11::EXEC_CREATE_SHADER( XE::Buffer & buffer )
{
	XE::String name;
	XE::ShaderType type;
	XE::MemoryView mem;
	XE::ShaderHandle handle;

	buffer.Read( handle );
	buffer.Read( name );
	buffer.Read( type );
	buffer.Read( mem );

	_p->_Shaders[handle].create( _p->_Device, type, mem );
}

void XE::RendererContextDirectX11::EXEC_CREATE_PROGRAM( XE::Buffer & buffer )
{
	XE::ProgramHandle handle;
	XE::ShaderHandle vs;
	XE::ShaderHandle fs;

	buffer.Read( handle );
	buffer.Read( vs );
	buffer.Read( fs );

	_p->_Programs[handle].create( &_p->_Shaders[vs], &_p->_Shaders[fs] );
}

void XE::RendererContextDirectX11::EXEC_CREATE_TEXTURE( XE::Buffer & buffer )
{
	XE::TextureType type;
	XE::TextureHandle handle;

	buffer.Read( handle );
	buffer.Read( type );

	switch( type )
	{
	case XE::TextureType::TEXTURE_2D:
	{
		bool hasmips;
		XE::String name;
		XE::uint32 width;
		XE::uint32 height;
		XE::uint16 layers;
		XE::MemoryView mem;
		XE::TextureFormat format;
		XE::Flags< XE::TextureFlags > flags;
		XE::Flags< XE::SamplerFlags > sampler;

		buffer.Read( name );
		buffer.Read( width );
		buffer.Read( height );
		buffer.Read( hasmips );
		buffer.Read( layers );
		buffer.Read( format );
		buffer.Read( flags );
		buffer.Read( sampler );
		buffer.Read( mem );

		_p->_Textures[handle];
	}
		break;
	case XE::TextureType::TEXTURE_3D:
	{
		bool hasmips;
		XE::String name;
		XE::uint32 width;
		XE::uint32 height;
		XE::uint32 depth;
		XE::MemoryView mem;
		XE::TextureFormat format;
		XE::Flags< XE::TextureFlags > flags;
		XE::Flags< XE::SamplerFlags > sampler;

		buffer.Read( name );
		buffer.Read( width );
		buffer.Read( height );
		buffer.Read( depth );
		buffer.Read( hasmips );
		buffer.Read( format );
		buffer.Read( flags );
		buffer.Read( sampler );
		buffer.Read( mem );

		_p->_Textures[handle];
	}
		break;
	case XE::TextureType::TEXTURE_CUBE:
	{
		bool hasmips;
		XE::String name;
		XE::uint32 size;
		XE::uint16 layers;
		XE::MemoryView mem;
		XE::TextureFormat format;
		XE::Flags< XE::TextureFlags > flags;
		XE::Flags< XE::SamplerFlags > sampler;

		buffer.Read( name );
		buffer.Read( size );
		buffer.Read( hasmips );
		buffer.Read( layers );
		buffer.Read( format );
		buffer.Read( flags );
		buffer.Read( sampler );

		_p->_Textures[handle];
	}
		break;
	default:
		break;
	}
}

void XE::RendererContextDirectX11::EXEC_UPDATE_TEXTURE( XE::Buffer & buffer )
{
	XE::TextureType type;
	XE::TextureHandle handle;

	buffer.Read( handle );
	buffer.Read( type );

	switch( type )
	{
	case XE::TextureType::TEXTURE_2D:
	{
		XE::uint16 layer;
		XE::uint8 mip;
		XE::uint32 x;
		XE::uint32 y;
		XE::uint32 width;
		XE::uint32 height;
		XE::MemoryView mem;
		XE::uint32 pitch;

		buffer.Read( layer );
		buffer.Read( mip );
		buffer.Read( x );
		buffer.Read( y );
		buffer.Read( width );
		buffer.Read( height );
		buffer.Read( mem );
		buffer.Read( pitch );

		_p->_Textures[handle];
	}
		break;
	case XE::TextureType::TEXTURE_3D:
	{
		XE::uint8 mip;
		XE::uint32 x;
		XE::uint32 y;
		XE::uint32 z;
		XE::uint32 width;
		XE::uint32 height;
		XE::uint32 depth;
		XE::MemoryView mem;

		buffer.Read( mip );
		buffer.Read( x );
		buffer.Read( y );
		buffer.Read( z );
		buffer.Read( width );
		buffer.Read( height );
		buffer.Read( depth );
		buffer.Read( mem );

		_p->_Textures[handle];
	}
		break;
	case XE::TextureType::TEXTURE_CUBE:
	{
		XE::uint16 layer;
		XE::uint8 side;
		XE::uint8 mip;
		XE::uint32 x;
		XE::uint32 y;
		XE::uint32 z;
		XE::uint32 width;
		XE::uint32 height;
		XE::uint32 depth;
		XE::MemoryView mem;

		buffer.Read( layer );
		buffer.Read( side );
		buffer.Read( mip );
		buffer.Read( x );
		buffer.Read( y );
		buffer.Read( z );
		buffer.Read( width );
		buffer.Read( height );
		buffer.Read( depth );
		buffer.Read( mem );

		_p->_Textures[handle];
	}
		break;
	default:
		break;
	}
}

void XE::RendererContextDirectX11::EXEC_RESIZE_TEXTURE( XE::Buffer & buffer )
{
	// TODO: 
}

void XE::RendererContextDirectX11::EXEC_CREATE_FRAME_BUFFER( XE::Buffer & buffer )
{
}

void XE::RendererContextDirectX11::EXEC_CREATE_UNIFORM( XE::Buffer & buffer )
{
	XE::uint16 num;
	XE::String name;
	XE::UniformType type;
	XE::UniformHandle handle;

	buffer.Read( handle );
	buffer.Read( name );
	buffer.Read( type );
	buffer.Read( num );


}

void XE::RendererContextDirectX11::EXEC_CREATE_OCCLUSION_QUERY( XE::Buffer & buffer )
{
	XE::OcclusionQueryHandle handle;

	buffer.Read( handle );

	
}

void XE::RendererContextDirectX11::EXEC_END( XE::Buffer & buffer )
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_VERTEX_LAYOUT( XE::Buffer & buffer )
{
	XE::VertexLayoutHandle handle;

	buffer.Read( handle );


}

void XE::RendererContextDirectX11::EXEC_DESTROY_INDEX_BUFFER( XE::Buffer & buffer )
{
	XE::IndexBufferHandle handle;

	buffer.Read( handle );

	_p->_IndexBuffers[handle].destroy();
}

void XE::RendererContextDirectX11::EXEC_DESTROY_VERTEX_BUFFER( XE::Buffer & buffer )
{
	XE::VertexBufferHandle handle;

	buffer.Read( handle );

	_p->_VertexBuffers[handle].destroy();
}

void XE::RendererContextDirectX11::EXEC_DESTROY_DYNAMIC_INDEX_BUFFER( XE::Buffer & buffer )
{
	XE::DynamicIndexBufferHandle handle;

	buffer.Read( handle );

	_p->_IndexBuffers[handle].destroy();
}

void XE::RendererContextDirectX11::EXEC_DESTROY_DYNAMIC_VERTEX_BUFFER( XE::Buffer & buffer )
{
	XE::DynamicVertexBufferHandle handle;

	buffer.Read( handle );

	_p->_VertexBuffers[handle].destroy();
}

void XE::RendererContextDirectX11::EXEC_DESTROY_SHADER( XE::Buffer & buffer )
{
	XE::ShaderHandle handle;

	buffer.Read( handle );

	_p->_Shaders[handle];
}

void XE::RendererContextDirectX11::EXEC_DESTROY_PROGRAM( XE::Buffer & buffer )
{
	XE::ProgramHandle handle;

	buffer.Read( handle );

	_p->_Programs[handle].destroy();
}

void XE::RendererContextDirectX11::EXEC_DESTROY_TEXTURE( XE::Buffer & buffer )
{
	XE::TextureHandle handle;

	buffer.Read( handle );

	_p->_Textures[handle];
}

void XE::RendererContextDirectX11::EXEC_DESTROY_FRAMEBUFFER( XE::Buffer & buffer )
{
	XE::FrameBufferHandle handle;

	buffer.Read( handle );

	_p->_FrameBuffers[handle];
}

void XE::RendererContextDirectX11::EXEC_DESTROY_UNIFORM( XE::Buffer & buffer )
{
	XE::UniformHandle handle;

	buffer.Read( handle );

}

void XE::RendererContextDirectX11::EXEC_READ_TEXTURE( XE::Buffer & buffer )
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_OCCLUSION_QUERY( XE::Buffer & buffer )
{
	XE::OcclusionQueryHandle handle;

	buffer.Read( handle );
}

void XE::RendererContextDirectX11::EXEC_REQUEST_SCREEN_SHOT( XE::Buffer & buffer )
{
	XE::String path;
	XE::FrameBufferHandle handle;

	buffer.Read( handle );
	buffer.Read( path );


}

XE::RendererContext * XE::CreateRendererContextDirectX11()
{
	return new XE::RendererContextDirectX11();
}
#else
XE::RendererContext * XE::CreateRendererContextDirectX11()
{
	return nullptr;
}
#endif