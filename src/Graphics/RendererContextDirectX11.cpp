#include "RendererContextDirectX11.h"

#if PLATFORM_OS & (OS_WINDOWS)

#include <d3d11_4.h>
#include <d3dcommon.h>

#include "Utils/Logger.h"

#include "DXGI.h"

#ifdef min
#undef min
#endif // min
#ifdef max
#undef max
#endif // max

static const GUID WKPDID_D3DDebugObjectName = { 0x429b8c22, 0x9188, 0x4b0c, { 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00 } };
static const GUID IID_ID3D11Texture2D = { 0x6f15aaf2, 0xd208, 0x4e89, { 0x9a, 0xb4, 0x48, 0x95, 0x35, 0xd3, 0x4f, 0x9c } };
static const GUID IID_ID3D11Device1 = { 0xa04bfb29, 0x08ef, 0x43d6, { 0xa4, 0x9c, 0xa9, 0xbd, 0xbd, 0xcb, 0xe6, 0x86 } };
static const GUID IID_ID3D11Device2 = { 0x9d06dffa, 0xd1e5, 0x4d07, { 0x83, 0xa8, 0x1b, 0xb1, 0x23, 0xf2, 0xf8, 0x41 } };
static const GUID IID_ID3D11Device3 = { 0xa05c8c37, 0xd2c6, 0x4732, { 0xb3, 0xa0, 0x9c, 0xe0, 0xb0, 0xdc, 0x9a, 0xe6 } };
static const GUID IID_ID3D11InfoQueue = { 0x6543dbb6, 0x1b48, 0x42f5, { 0xab, 0x82, 0xe9, 0x7e, 0xc7, 0x43, 0x26, 0xf6 } };
static const GUID IID_IDXGIDeviceRenderDoc = { 0xa7aa6116, 0x9c8d, 0x4bba, { 0x90, 0x83, 0xb4, 0xd8, 0x16, 0xb7, 0x1b, 0x78 } };
static const GUID IID_ID3DUserDefinedAnnotation = { 0xb2daad8b, 0x03d4, 0x4dbf, { 0x95, 0xeb, 0x32, 0xab, 0x4b, 0x63, 0xd0, 0xab } };

static DXGI_SAMPLE_DESC s_msaa[] =
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
	XE::uint32  stride;
};

static const UavFormat s_uavFormat[] =
{	//  BGFX_BUFFER_COMPUTE_TYPE_INT,  BGFX_BUFFER_COMPUTE_TYPE_UINT,  BGFX_BUFFER_COMPUTE_TYPE_FLOAT
	{ { DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN            },  0 }, // ignored
	{ { DXGI_FORMAT_R8_SINT,           DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_UNKNOWN            },  1 }, // BGFX_BUFFER_COMPUTE_FORMAT_8X1
	{ { DXGI_FORMAT_R8G8_SINT,         DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_UNKNOWN            },  2 }, // BGFX_BUFFER_COMPUTE_FORMAT_8X2
	{ { DXGI_FORMAT_R8G8B8A8_SINT,     DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_UNKNOWN            },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_8X4
	{ { DXGI_FORMAT_R16_SINT,          DXGI_FORMAT_R16_UINT,           DXGI_FORMAT_R16_FLOAT          },  2 }, // BGFX_BUFFER_COMPUTE_FORMAT_16X1
	{ { DXGI_FORMAT_R16G16_SINT,       DXGI_FORMAT_R16G16_UINT,        DXGI_FORMAT_R16G16_FLOAT       },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_16X2
	{ { DXGI_FORMAT_R16G16B16A16_SINT, DXGI_FORMAT_R16G16B16A16_UINT,  DXGI_FORMAT_R16G16B16A16_FLOAT },  8 }, // BGFX_BUFFER_COMPUTE_FORMAT_16X4
	{ { DXGI_FORMAT_R32_SINT,          DXGI_FORMAT_R32_UINT,           DXGI_FORMAT_R32_FLOAT          },  4 }, // BGFX_BUFFER_COMPUTE_FORMAT_32X1
	{ { DXGI_FORMAT_R32G32_SINT,       DXGI_FORMAT_R32G32_UINT,        DXGI_FORMAT_R32G32_FLOAT       },  8 }, // BGFX_BUFFER_COMPUTE_FORMAT_32X2
	{ { DXGI_FORMAT_R32G32B32A32_SINT, DXGI_FORMAT_R32G32B32A32_UINT,  DXGI_FORMAT_R32G32B32A32_FLOAT }, 16 }, // BGFX_BUFFER_COMPUTE_FORMAT_32X4
};

struct TextureFormatInfo
{
	DXGI_FORMAT m_fmt;
	DXGI_FORMAT m_fmtSrv;
	DXGI_FORMAT m_fmtDsv;
	DXGI_FORMAT m_fmtSrgb;
};

static const TextureFormatInfo s_textureFormat[] =
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
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ASTC4x4
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ASTC5x5
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ASTC6x6
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ASTC8x5
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ASTC8x6
	{ DXGI_FORMAT_UNKNOWN,            DXGI_FORMAT_UNKNOWN,               DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // ASTC10x5
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

struct ImageBlockInfo
{
	uint8_t bitsPerPixel;
	uint8_t blockWidth;
	uint8_t blockHeight;
	uint8_t blockSize;
	uint8_t minBlockX;
	uint8_t minBlockY;
	uint8_t depthBits;
	uint8_t stencilBits;
	uint8_t rBits;
	uint8_t gBits;
	uint8_t bBits;
	uint8_t aBits;
	uint8_t encoding;
};
enum class EncodingType
{
	Unorm,
	Int,
	Uint,
	Float,
	Snorm,

	Count
};

static const ImageBlockInfo s_imageBlockInfo[] =
{
	//  +--------------------------------------------- bits per pixel
	//  |   +----------------------------------------- block width
	//  |   |  +-------------------------------------- block height
	//  |   |  |   +---------------------------------- block size
	//  |   |  |   |  +------------------------------- min blocks x
	//  |   |  |   |  |  +---------------------------- min blocks y
	//  |   |  |   |  |  |   +------------------------ depth bits
	//  |   |  |   |  |  |   |  +--------------------- stencil bits
	//  |   |  |   |  |  |   |  |   +---+---+---+----- r, g, b, a bits
	//  |   |  |   |  |  |   |  |   r   g   b   a  +-- encoding type
	//  |   |  |   |  |  |   |  |   |   |   |   |  |
	{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // BC1
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // BC2
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // BC3
	{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // BC4
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // BC5
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Float ) }, // BC6H
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // BC7
	{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ETC1
	{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ETC2
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ETC2A
	{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ETC2A1
	{   2,  8, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // PTC12
	{   4,  4, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // PTC14
	{   2,  8, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // PTC12A
	{   4,  4, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // PTC14A
	{   2,  8, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // PTC22
	{   4,  4, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // PTC24
	{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ATC
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ATCE
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ATCI
	{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ASTC4x4
	{   6,  5, 5, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ASTC5x5
	{   4,  6, 6, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ASTC6x6
	{   4,  8, 5, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ASTC8x5
	{   3,  8, 6, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ASTC8x6
	{   3, 10, 5, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // ASTC10x5
	{   0,  0, 0,  0, 0, 0,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Count ) }, // Unknown
	{   1,  8, 1,  1, 1, 1,  0, 0,  1,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // R1
	{   8,  1, 1,  1, 1, 1,  0, 0,  0,  0,  0,  8, uint8_t( EncodingType::Unorm ) }, // A8
	{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // R8
	{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( EncodingType::Int ) }, // R8I
	{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( EncodingType::Uint ) }, // R8U
	{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( EncodingType::Snorm ) }, // R8S
	{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // R16
	{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( EncodingType::Int ) }, // R16I
	{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( EncodingType::Uint ) }, // R16U
	{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( EncodingType::Float ) }, // R16F
	{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( EncodingType::Snorm ) }, // R16S
	{  32,  1, 1,  4, 1, 1,  0, 0, 32,  0,  0,  0, uint8_t( EncodingType::Int ) }, // R32I
	{  32,  1, 1,  4, 1, 1,  0, 0, 32,  0,  0,  0, uint8_t( EncodingType::Uint ) }, // R32U
	{  32,  1, 1,  4, 1, 1,  0, 0, 32,  0,  0,  0, uint8_t( EncodingType::Float ) }, // R32F
	{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( EncodingType::Unorm ) }, // RG8
	{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( EncodingType::Int ) }, // RG8I
	{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( EncodingType::Uint ) }, // RG8U
	{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( EncodingType::Snorm ) }, // RG8S
	{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( EncodingType::Unorm ) }, // RG16
	{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( EncodingType::Int ) }, // RG16I
	{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( EncodingType::Uint ) }, // RG16U
	{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( EncodingType::Float ) }, // RG16F
	{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( EncodingType::Snorm ) }, // RG16S
	{  64,  1, 1,  8, 1, 1,  0, 0, 32, 32,  0,  0, uint8_t( EncodingType::Int ) }, // RG32I
	{  64,  1, 1,  8, 1, 1,  0, 0, 32, 32,  0,  0, uint8_t( EncodingType::Uint ) }, // RG32U
	{  64,  1, 1,  8, 1, 1,  0, 0, 32, 32,  0,  0, uint8_t( EncodingType::Float ) }, // RG32F
	{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( EncodingType::Unorm ) }, // RGB8
	{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( EncodingType::Int ) }, // RGB8I
	{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( EncodingType::Uint ) }, // RGB8U
	{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( EncodingType::Snorm ) }, // RGB8S
	{  32,  1, 1,  4, 1, 1,  0, 0,  9,  9,  9,  5, uint8_t( EncodingType::Float ) }, // RGB9E5F
	{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( EncodingType::Unorm ) }, // BGRA8
	{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( EncodingType::Unorm ) }, // RGBA8
	{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( EncodingType::Int ) }, // RGBA8I
	{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( EncodingType::Uint ) }, // RGBA8U
	{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( EncodingType::Snorm ) }, // RGBA8S
	{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( EncodingType::Unorm ) }, // RGBA16
	{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( EncodingType::Int ) }, // RGBA16I
	{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( EncodingType::Uint ) }, // RGBA16U
	{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( EncodingType::Float ) }, // RGBA16F
	{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( EncodingType::Snorm ) }, // RGBA16S
	{ 128,  1, 1, 16, 1, 1,  0, 0, 32, 32, 32, 32, uint8_t( EncodingType::Int ) }, // RGBA32I
	{ 128,  1, 1, 16, 1, 1,  0, 0, 32, 32, 32, 32, uint8_t( EncodingType::Uint ) }, // RGBA32U
	{ 128,  1, 1, 16, 1, 1,  0, 0, 32, 32, 32, 32, uint8_t( EncodingType::Float ) }, // RGBA32F
	{  16,  1, 1,  2, 1, 1,  0, 0,  5,  6,  5,  0, uint8_t( EncodingType::Unorm ) }, // R5G6B5
	{  16,  1, 1,  2, 1, 1,  0, 0,  4,  4,  4,  4, uint8_t( EncodingType::Unorm ) }, // RGBA4
	{  16,  1, 1,  2, 1, 1,  0, 0,  5,  5,  5,  1, uint8_t( EncodingType::Unorm ) }, // RGB5A1
	{  32,  1, 1,  4, 1, 1,  0, 0, 10, 10, 10,  2, uint8_t( EncodingType::Unorm ) }, // RGB10A2
	{  32,  1, 1,  4, 1, 1,  0, 0, 11, 11, 10,  0, uint8_t( EncodingType::Unorm ) }, // RG11B10F
	{   0,  0, 0,  0, 0, 0,  0, 0,  0,  0,  0,  0, uint8_t( EncodingType::Count ) }, // UnknownDepth
	{  16,  1, 1,  2, 1, 1, 16, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // D16
	{  24,  1, 1,  3, 1, 1, 24, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // D24
	{  32,  1, 1,  4, 1, 1, 24, 8,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // D24S8
	{  32,  1, 1,  4, 1, 1, 32, 0,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // D32
	{  16,  1, 1,  2, 1, 1, 16, 0,  0,  0,  0,  0, uint8_t( EncodingType::Float ) }, // D16F
	{  24,  1, 1,  3, 1, 1, 24, 0,  0,  0,  0,  0, uint8_t( EncodingType::Float ) }, // D24F
	{  32,  1, 1,  4, 1, 1, 32, 0,  0,  0,  0,  0, uint8_t( EncodingType::Float ) }, // D32F
	{   8,  1, 1,  1, 1, 1,  0, 8,  0,  0,  0,  0, uint8_t( EncodingType::Unorm ) }, // D0S8
};


BEG_XE_NAMESPACE
namespace D3D11
{
	struct Buffer
	{
		void Create( XE::uint32 _size, void * _data, XE::BufferFlags _flags, XE::uint16 _stride = 0, bool _vertex = false );
		void Update( XE::uint32 _offset, XE::uint32 _size, void * _data, bool _discard = false );
		void Destroy();

		ID3D11Buffer * _Ptr = nullptr;
		ID3D11ShaderResourceView * _SRV = nullptr;
		ID3D11UnorderedAccessView * _UAV = nullptr;
		XE::uint32 _Size = 0;
		XE::BufferFlags _Flags = XE::BufferFlag::NONE;
		bool _Dynamic = false;
	};

	typedef Buffer IndexBuffer;

	struct VertexBuffer : public Buffer
	{
		void Create( XE::uint32 _size, void * _data, XE::VertexLayoutHandle _layoutHandle, XE::BufferFlags _flags );

		XE::VertexLayoutHandle _LayoutHandle;
	};

	struct Shader
	{
		void Create( XE::ShaderType _type, XE::MemoryView _mem );
		void Destroy();

		union
		{
			ID3D11DeviceChild * _Ptr = nullptr;
			ID3D11PixelShader * _PixelShader;
			ID3D11VertexShader * _VertexShader;
			ID3D11ComputeShader * _ComputeShader;
		};

		XE::ShaderType _Type = ShaderType::CS;

		XE::Buffer _Code;
		ID3D11Buffer * _Buffer = nullptr;
		XE::Buffer _ConstantBuffer;

		XE::UniformDesc _PredefinedUniforms[GFX_MAX_UNIFORMS];
		XE::uint16 _AttrMask[( XE::uint64 )AttributeName::COUNT];

		XE::uint32 _Hash = 0;

		XE::uint16 _NumUniforms = 0;
		XE::uint8 _NumPredefined = 0;
		bool _HasDepthOp = 0;
	};

	struct Program
	{
		void Create( const D3D11::Shader * _vsh, const D3D11::Shader * _fsh );
		void Destroy();

		const D3D11::Shader * _VS;
		const D3D11::Shader * _FS;

		XE::uint8 _NumPredefined = 0;
		UniformDesc _PredefinedUniforms[GFX_MAX_UNIFORMS];
	};

	struct IntelDirectAccessResourceDescriptor
	{
		void * _Ptr = nullptr;
		XE::uint32 _XOffset = 0;
		XE::uint32 _YOffset = 0;
		XE::uint32 _TileFormat = 0;
		XE::uint32 _Pitch = 0;
		XE::uint32 _Size = 0;
	};

	struct DirectAccessResource
	{
		void * CreateTexture2D( const D3D11_TEXTURE2D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture2D ** _gpuTexture2d );
		void * CreateTexture3D( const D3D11_TEXTURE3D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture3D ** _gpuTexture3d );
		void Destroy();

		union
		{
			ID3D11Resource * _Ptr = nullptr;
			ID3D11Texture2D * _Texture2d;
			ID3D11Texture3D * _Texture3d;
		};

		D3D11::IntelDirectAccessResourceDescriptor * _Descriptor = nullptr;
	};

	struct Texture
	{
		void * Create( XE::MemoryView _mem, const XE::TextureDesc & desc );
		void Destroy();
		void OverrideInternal( uintptr_t _ptr );
		void Update( XE::uint8 _side, XE::uint8 _mip, const XE::Recti & _rect, XE::uint16 _z, XE::uint16 _depth, XE::uint16 _pitch, XE::MemoryView _mem );
		void Commit( XE::uint8 _stage, XE::uint32 _flags, const float _palette[][4] );
		void Resolve( XE::uint8 _resolve ) const;
		XE::TextureHandle GetHandle() const;
		DXGI_FORMAT GetSRVFormat() const;

		union
		{
			ID3D11Resource * _Ptr = nullptr;
			ID3D11Texture2D * _Texture2d;
			ID3D11Texture3D * _Texture3d;
		};

		D3D11::DirectAccessResource _DAR;
		ID3D11ShaderResourceView * _SRV = nullptr;
		ID3D11UnorderedAccessView * _UAV = nullptr;
		XE::TextureFlags _Flags = 0;
		XE::uint32 _Width = 0;
		XE::uint32 _Height = 0;
		XE::uint32 _Depth = 0;
		XE::uint32 _NumLayers = 0;
		XE::TextureType _Type = TextureType::TEXTURE_2D;
		XE::uint8  _RequestedFormat = 0;
		XE::TextureFormat  _TextureFormat = TextureFormat::RGBA8;
		XE::uint8  _NumMips = 0;
	};

	struct FrameBuffer
	{
		void Create( XE::uint8 _num, const XE::Attachment * _attachment );
		void Create( XE::uint16 _denseIdx, XE::WindowHandle _nwh, XE::uint32 _width, XE::uint32 _height, XE::TextureFormat _format, XE::TextureFormat _depthFormat );
		XE::uint16 Destroy();
		void PreReset( bool _force = false );
		void PostReset();
		void Resolve();
		void Clear( const XE::ViewClearDesc & _clear );
		void Set();
		HRESULT Present( XE::uint32 _syncInterval );

		ID3D11RenderTargetView * _RTV[GFX_MAX_ATTACHMENTS - 1];
		ID3D11UnorderedAccessView * _UAV[GFX_MAX_ATTACHMENTS - 1];
		ID3D11ShaderResourceView * _SRV[GFX_MAX_ATTACHMENTS - 1];
		ID3D11DepthStencilView * _DSV = nullptr;
		DXGI::SwapChainI * _SwapChain = nullptr;
		XE::WindowHandle _Window;
		XE::uint32 _Width;
		XE::uint32 _Height;

		XE::Attachment _Attachment[GFX_MAX_ATTACHMENTS];
		XE::uint16 _DenseIdx;
		XE::uint8 _Num;
		XE::uint8 _NumTh;
		XE::uint8 _NumUav;
		bool _NeedPresent;
	};

	struct OcclusionQuery
	{
		void PostReset();
		void PreReset();
		void Begin( XE::RenderFrame * _render, OcclusionQueryHandle _handle );
		void End();
		void Resolve( XE::RenderFrame * _render, bool _wait = false );
		void Invalidate( OcclusionQueryHandle _handle );

		struct Query
		{
			ID3D11Query * _Ptr;
			XE::OcclusionQueryHandle _Handle;
		};

		Query _Query[GFX_MAX_OCCLUSION];
		XE::RingBuffer m_control;
	};

	struct RenderContext
	{
		XE::LibraryHandle _DX11Dll;

		DXGI * _Dxgi = nullptr;
		D3D_FEATURE_LEVEL _FeatureLevel;
		ID3D11Device * _Device = nullptr;
		ID3D11DeviceContext * _DeviceCtx = nullptr;

		ID3D11RenderTargetView * _CurrentColor = NULL;
		ID3D11DepthStencilView * _CurrentDepthStencil = NULL;

		std::array<D3D11::IndexBuffer, GFX_MAX_INDEX_BUFFERS> _IndexBuffers;
		std::array<D3D11::VertexBuffer, GFX_MAX_VERTEX_BUFFERS> _VertexBuffers;
		std::array<D3D11::Shader, GFX_MAX_SHADERS> _Shaders;
		std::array<D3D11::Program, GFX_MAX_PROGRAMS> _Programs;
		std::array<D3D11::Texture, GFX_MAX_TEXTURES> _Textures;
		std::array<D3D11::FrameBuffer, GFX_MAX_FRAME_BUFFERS> _FrameBuffers;

		std::map<XE::uint64, ID3D11BlendState *> _BlendStateCahce;
		std::map<XE::uint64, ID3D11DepthStencilState *> _DepthStencilStateCache;
		std::map<XE::uint64, ID3D11InputLayout *> _InputLayoutCache;
		std::map<XE::uint64, ID3D11RasterizerState *> _RasterizerStateCache;
		std::map<XE::uint64, ID3D11SamplerState *> _SamplerStateCache;
	};
};

XE::D3D11::RenderContext * _rtx = nullptr;

namespace D3D11
{
	void Buffer::Create( XE::uint32 _size, void * _data, XE::BufferFlags _flags, XE::uint16 _stride /*= 0*/, bool _vertex /*= false */ )
	{
		_UAV = NULL;
		_Size = _size;
		_Flags = _flags;

		const bool needUav = _flags && XE::MakeFlags( XE::BufferFlag::COMPUTEWRITE, XE::BufferFlag::DRAWINDIRECT );
		const bool needSrv = _flags && XE::BufferFlag::COMPUTEREAD;
		const bool drawIndirect = _flags && XE::BufferFlag::DRAWINDIRECT;
		_Dynamic = NULL == _data && !needUav;

		D3D11_BUFFER_DESC desc;
		desc.ByteWidth = _size;
		desc.BindFlags = ( _vertex ? D3D11_BIND_VERTEX_BUFFER : D3D11_BIND_INDEX_BUFFER ) | ( needUav ? D3D11_BIND_UNORDERED_ACCESS : 0 ) | ( needSrv ? D3D11_BIND_SHADER_RESOURCE : 0 );
		desc.MiscFlags = ( drawIndirect ? D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS : 0 );
		desc.StructureByteStride = 0;

		DXGI_FORMAT format;
		XE::uint32  stride;

		if( drawIndirect )
		{
			format = DXGI_FORMAT_R32G32B32A32_UINT;
			stride = 16;
		}
		else
		{
			uint32_t uavFormat = ( _flags & XE::BufferFlag::COMPUTEFORMATMASK ).GetValue() >> ( XE::uint64 )XE::BufferFlag::COMPUTEFORMATSHIFT;
			if( 0 == uavFormat )
			{
				if( _vertex )
				{
					format = DXGI_FORMAT_R32G32B32A32_FLOAT;
					stride = 16;
				}
				else
				{
					if( 0 == ( _flags & XE::BufferFlag::INDEX32 ).GetValue() )
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
				const uint32_t uavType = Mathf::Satsub<XE::uint64>( ( _flags & XE::BufferFlag::COMPUTETYPEMASK ).GetValue() >> ( XE::uint64 )XE::BufferFlag::COMPUTETYPESHIFT, 1 );
				format = s_uavFormat[uavFormat].format[uavType];
				stride = s_uavFormat[uavFormat].stride;
			}
		}

		D3D11_SUBRESOURCE_DATA srd;
		srd.pSysMem = _data;
		srd.SysMemPitch = 0;
		srd.SysMemSlicePitch = 0;

		if( needUav )
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.CPUAccessFlags = 0;
			desc.StructureByteStride = _stride;

			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateBuffer( &desc, NULL == _data ? NULL : &srd, &_Ptr ) ) );

			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			uavd.Format = format;
			uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			uavd.Buffer.FirstElement = 0;
			uavd.Buffer.NumElements = _Size / stride;
			uavd.Buffer.Flags = 0;
			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateUnorderedAccessView( _Ptr, &uavd, &_UAV ) ) );
		}
		else if( _Dynamic )
		{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateBuffer( &desc, NULL, &_Ptr ) ) );
		}
		else
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.CPUAccessFlags = 0;

			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateBuffer( &desc, &srd, &_Ptr ) ) );
		}

		if( needSrv )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			srvd.Format = format;
			srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvd.Buffer.FirstElement = 0;
			srvd.Buffer.NumElements = _Size / stride;
			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateShaderResourceView( _Ptr, &srvd, &_SRV ) ) );
		}
	}

	void Buffer::Update( XE::uint32 _offset, XE::uint32 _size, void * _data, bool _discard /*= false */ )
	{
		XE_ASSERT( _Dynamic && "Must be dynamic!" );

		if( _discard )
		{
			D3D11_MAPPED_SUBRESOURCE mapped;
			XE_ASSERT( SUCCEEDED( _rtx->_DeviceCtx->Map( _Ptr, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped ) ) );
			std::memcpy( ( uint8_t * ) mapped.pData + _offset, _data, _size );
			_rtx->_DeviceCtx->Unmap( _Ptr, 0 );
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
			srd.pSysMem = _data;
			srd.SysMemPitch = 0;
			srd.SysMemSlicePitch = 0;

			D3D11_BOX srcBox;
			srcBox.left = 0;
			srcBox.top = 0;
			srcBox.front = 0;
			srcBox.right = _size;
			srcBox.bottom = 1;
			srcBox.back = 1;

			ID3D11Device * device = nullptr;
			_rtx->_DeviceCtx->GetDevice( &device );

			ID3D11Buffer * ptr;
			XE_ASSERT( SUCCEEDED( device->CreateBuffer( &desc, &srd, &ptr ) ) );

			_rtx->_DeviceCtx->CopySubresourceRegion( _Ptr, 0, _offset, 0, 0, ptr, 0, &srcBox );

			DX_RELEASE( device );
			DX_RELEASE( ptr );
		}
	}

	void Buffer::Destroy()
	{
		if( NULL != _Ptr )
		{
			DX_RELEASE( _Ptr );
			_Dynamic = false;
		}

		DX_RELEASE( _SRV );
		DX_RELEASE( _UAV );
	}

	void VertexBuffer::Create( XE::uint32 _size, void * _data, XE::VertexLayoutHandle _layoutHandle, XE::BufferFlags _flags )
	{
		_LayoutHandle = _layoutHandle;

		D3D11::Buffer::Create( _size, _data, _flags, 0, true );
	}

	void Shader::Create( XE::ShaderType _type, XE::MemoryView _mem )
	{
		_Type = _type;

		switch( _type )
		{
		case XE::ShaderType::VS:
			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateVertexShader( _mem.data(), _mem.size(), nullptr, &_VertexShader ) ) );
			break;
		case XE::ShaderType::FS:
			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreatePixelShader( _mem.data(), _mem.size(), nullptr, &_PixelShader ) ) );
			break;
		case XE::ShaderType::CS:
			XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateComputeShader( _mem.data(), _mem.size(), nullptr, &_ComputeShader ) ) );
			break;
		default:
			break;
		}
	}

	void Shader::Destroy()
	{
		DX_RELEASE( _Ptr );
	}

	void Program::Create( const D3D11::Shader * _vsh, const D3D11::Shader * _fsh )
	{
		_VS = _vsh;
		_FS = _fsh;
	}

	void Program::Destroy()
	{
		_VS = nullptr;
		_FS = nullptr;
	}

	void * DirectAccessResource::CreateTexture2D( const D3D11_TEXTURE2D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture2D ** _gpuTexture2d )
	{
		XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture2D( _gpuDesc, _srd, _gpuTexture2d ) ) );

		D3D11_TEXTURE2D_DESC cpuDesc;
		std::memcpy( &cpuDesc, _gpuDesc, sizeof( cpuDesc ) );
		cpuDesc.BindFlags = 0;
		cpuDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		cpuDesc.Usage = D3D11_USAGE_STAGING;

		XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture2D( &cpuDesc, NULL, &_Texture2d ) ) );

		_rtx->_DeviceCtx->CopyResource( _Texture2d, *_gpuTexture2d );

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		_rtx->_DeviceCtx->Map( _Texture2d, 0, D3D11_MAP_WRITE, 0, &mappedResource );
		_Descriptor = reinterpret_cast< IntelDirectAccessResourceDescriptor * >( mappedResource.pData );

		return _Descriptor->_Ptr;
	}

	void * DirectAccessResource::CreateTexture3D( const D3D11_TEXTURE3D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture3D ** _gpuTexture3d )
	{
		XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture3D( _gpuDesc, _srd, _gpuTexture3d ) ) );

		D3D11_TEXTURE3D_DESC cpuDesc;
		std::memcpy( &cpuDesc, _gpuDesc, sizeof( cpuDesc ) );
		cpuDesc.BindFlags = 0;
		cpuDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		cpuDesc.Usage = D3D11_USAGE_STAGING;

		XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture3D( &cpuDesc, NULL, &_Texture3d ) ) );

		_rtx->_DeviceCtx->CopyResource( _Texture3d, *_gpuTexture3d );

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		_rtx->_DeviceCtx->Map( _Texture3d, 0, D3D11_MAP_WRITE, 0, &mappedResource );
		_Descriptor = reinterpret_cast< IntelDirectAccessResourceDescriptor * >( mappedResource.pData );

		return _Descriptor->_Ptr;
	}

	void DirectAccessResource::Destroy()
	{
		if( _Descriptor )
		{
			_rtx->_DeviceCtx->Unmap( _Ptr, 0 );
			_Descriptor = nullptr;
			DX_RELEASE( _Ptr );
			_Ptr = nullptr;
		}
	}

	void * Texture::Create( XE::MemoryView _mem, const XE::TextureDesc & _desc )
	{
			void * directAccessPtr = NULL;

				_Flags = _desc.Flags;
				_Width = _desc.Width;
				_Height = _desc.Height;
				_Depth = _desc.Depth;
				_NumLayers = _desc.NumLayers;
				_TextureFormat = _desc.Format;
				_Type = _desc.Type;
				_NumMips = _desc.NumMips;

				const uint16_t numSides = _desc.NumLayers * ( _desc.HasMaps ? 6 : 1 );
				const uint32_t numSrd = numSides * _desc.NumMips;
				D3D11_SUBRESOURCE_DATA * srd = ( D3D11_SUBRESOURCE_DATA * ) alloca( numSrd * sizeof( D3D11_SUBRESOURCE_DATA ) );

				uint32_t kk = 0;

// 				for( uint16_t side = 0; side < numSides; ++side )
// 				{
// 					for( uint8_t lod = 0, num = _dsec.NumMips; lod < num; ++lod )
// 					{
// 						srd[kk].pSysMem = mip.m_data;
// 
// 						if( compressed )
// 						{
// 							srd[kk].SysMemPitch = ( mip.m_width / blockInfo.blockWidth ) * mip.m_blockSize;
// 							srd[kk].SysMemSlicePitch = ( mip.m_height / blockInfo.blockHeight ) * srd[kk].SysMemPitch;
// 						}
// 						else
// 						{
// 							srd[kk].SysMemPitch = mip.m_width * mip.m_bpp / 8;
// 						}
// 
// 						srd[kk].SysMemSlicePitch = mip.m_height * srd[kk].SysMemPitch;
// 						++kk;
// 					}
// 				}

				const bool writeOnly = _Flags && XE::MakeFlags( XE::TextureFlag::RTWRITEONLY, XE::TextureFlag::READBACK );
				const bool computeWrite = _Flags && XE::TextureFlag::COMPUTEWRITE;
				const bool renderTarget = _Flags && XE::TextureFlag::RTMASK;
				const bool srgb = _Flags && XE::TextureFlag::SRGB;
				const bool blit = _Flags && XE::TextureFlag::BLITDST;
				const bool readBack = _Flags && XE::TextureFlag::READBACK;
				const uint32_t msaaQuality = XE::Mathf::Satsub<XE::uint32>( ( ( _Flags & XE::TextureFlag::RTMSAAMASK ) >> XE::TextureFlag::RTMSAASHIFT ).GetValue(), 1 );
				const DXGI_SAMPLE_DESC & msaa = s_msaa[msaaQuality];
				const bool msaaSample = true
					&& 1 < msaa.Count
					&& ( _Flags && XE::TextureFlag::MSAASAMPLE )
					&& !writeOnly
					;
				const bool needResolve = true
					&& 1 < msaa.Count
					&& ( _Flags && XE::TextureFlag::MSAASAMPLE )
					&& !writeOnly
					;

				D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
				std::memset( &srvd, 0, sizeof( srvd ) );

				DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
				
				if( srgb )
				{
					format = s_textureFormat[( XE::uint64 )_TextureFormat].m_fmtSrgb;
					srvd.Format = format;
					if( format != DXGI_FORMAT_UNKNOWN )
					{
						XE_LOG( LoggerLevel::Warning, "sRGB not supported for texture format %1", ( XE::uint64 )_TextureFormat );
					}
				}

				if( format == DXGI_FORMAT_UNKNOWN )
				{
					// not swizzled and not sRGB, or sRGB unsupported
					format = s_textureFormat[( XE::uint64 )_TextureFormat].m_fmt;
					srvd.Format = GetSRVFormat();
				}

				const bool directAccess = !renderTarget && !readBack && !blit && !writeOnly;

				switch( _Type )
				{
				case TextureType::TEXTURE_2D:
				case TextureType::TEXTURE_CUBE:
				{
					D3D11_TEXTURE2D_DESC desc = {};
					desc.Width = _Width;
					desc.Height = _Height;
					desc.MipLevels = _NumMips;
					desc.ArraySize = numSides;
					desc.Format = format;
					desc.SampleDesc = msaa;
					desc.Usage = kk == 0 || blit ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = writeOnly ? 0 : D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags = 0;

					if( _TextureFormat >= TextureFormat::UNKNOWNDEPTH )
					{
						desc.BindFlags |= D3D11_BIND_DEPTH_STENCIL;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}
					else if( renderTarget )
					{
						desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
						desc.Usage = D3D11_USAGE_DEFAULT;
						desc.MiscFlags |= 0
							| ( 1 < _NumMips ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0 )
							;
					}

					if( computeWrite )
					{
						desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}

					if( readBack )
					{
						desc.BindFlags = 0;
						desc.Usage = D3D11_USAGE_STAGING;
						desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
					}

					if( _desc.HasMaps )
					{
						desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
						if( 1 < _NumLayers )
						{
							srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
							srvd.TextureCubeArray.MipLevels = _NumMips;
							srvd.TextureCubeArray.NumCubes = _NumLayers;
						}
						else
						{
							srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
							srvd.TextureCube.MipLevels = _NumMips;
						}
					}
					else
					{
						if( msaaSample )
						{
							if( 1 < _NumLayers )
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY;
								srvd.Texture2DMSArray.ArraySize = _NumLayers;
							}
							else
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
							}
						}
						else
						{
							if( 1 < _NumLayers )
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
								srvd.Texture2DArray.MipLevels = _NumMips;
								srvd.Texture2DArray.ArraySize = _NumLayers;
							}
							else
							{
								srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
								srvd.Texture2D.MipLevels = _NumMips;
							}
						}
					}

					if( needResolve )
					{
						XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture2D( &desc, NULL, &_Texture2d ) ) );
						desc.BindFlags &= ~( D3D11_BIND_RENDER_TARGET | D3D11_BIND_DEPTH_STENCIL );
						desc.SampleDesc = s_msaa[0];
					}

					if( directAccess )
					{
						directAccessPtr = _DAR.CreateTexture2D( &desc, kk == 0 ? NULL : srd, &_Texture2d );
					}
					else
					{
						XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture2D( &desc, kk == 0 ? NULL : srd, &_Texture2d ) ) );
					}
				}
				break;
				case TextureType::TEXTURE_3D:
				{
					_desc.Width;
					D3D11_TEXTURE3D_DESC desc = {};
					desc.Width = _Width;
					desc.Height = _Height;
					desc.Depth = _desc.Depth;
					desc.MipLevels = _NumMips;
					desc.Format = format;
					desc.Usage = kk == 0 || blit ? D3D11_USAGE_DEFAULT : D3D11_USAGE_IMMUTABLE;
					desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
					desc.CPUAccessFlags = 0;
					desc.MiscFlags = 0;

					if( renderTarget )
					{
						desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
						desc.Usage = D3D11_USAGE_DEFAULT;
						desc.MiscFlags |= 0
							| ( 1 < _NumMips ? D3D11_RESOURCE_MISC_GENERATE_MIPS : 0 )
							;
					}

					if( computeWrite )
					{
						desc.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
						desc.Usage = D3D11_USAGE_DEFAULT;
					}

					if( readBack )
					{
						desc.BindFlags = 0;
						desc.Usage = D3D11_USAGE_STAGING;
						desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
					}

					srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
					srvd.Texture3D.MipLevels = _NumMips;

					if( directAccess )
					{
						directAccessPtr = _DAR.CreateTexture3D( &desc, kk == 0 ? NULL : srd, &_Texture3d );
					}
					else
					{
						XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture3D( &desc, kk == 0 ? NULL : srd, & _Texture3d ) ) );
					}
				}
				break;
				}

				if( !writeOnly )
				{
					XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateShaderResourceView( _Ptr, &srvd, &_SRV ) ) );
				}

				if( computeWrite )
				{
					XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateUnorderedAccessView( _Ptr, NULL, &_UAV ) ) );
				}

			return directAccessPtr;
	}

	void Texture::Destroy()
	{
		_DAR.Destroy();

		//_rtx->m_srvUavLru.invalidateWithParent( GetHandle() );

		DX_RELEASE( _SRV );
		DX_RELEASE( _UAV );
		DX_RELEASE( _Ptr );
	}

	void Texture::OverrideInternal( uintptr_t _ptr )
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		const bool readable = ( _SRV != NULL );
		if( readable )
		{
			_SRV->GetDesc( &srvDesc );
		}

		Destroy();
		//m_flags |= BGFX_SAMPLER_INTERNAL_SHARED;
		_Ptr = ( ID3D11Resource * ) _ptr;

		if( readable )
		{
			ID3D11Device * device;
			_rtx->_DeviceCtx->GetDevice( &device );
			device->CreateShaderResourceView( _Ptr, &srvDesc, &_SRV );
			DX_RELEASE( device );
		}
	}

	void Texture::Update( XE::uint8 _side, XE::uint8 _mip, const XE::Recti & _rect, XE::uint16 _z, XE::uint16 _depth, XE::uint16 _pitch, XE::MemoryView _mem )
	{
		ID3D11DeviceContext * deviceCtx = _rtx->_DeviceCtx;

		D3D11_BOX box;
		box.left = _rect.x;
		box.top = _rect.y;
		box.right = box.left + _rect.width;
		box.bottom = box.top + _rect.height;

		uint32_t layer = 0;

		if( TextureType::TEXTURE_3D == _Type )
		{
			box.front = _z;
			box.back = box.front + _depth;
		}
		else
		{
			layer = _z * ( TextureType::TEXTURE_CUBE == _Type ? 6 : 1 );
			box.front = 0;
			box.back = 1;
		}

		const uint32_t subres = _mip + ( ( layer + _side ) * _NumMips );
		const bool     depth = ( _TextureFormat > TextureFormat::UNKNOWNDEPTH );
		const uint32_t bpp = s_imageBlockInfo[( XE::uint64 )_TextureFormat].bitsPerPixel;
		uint32_t rectpitch = _rect.width * bpp / 8;
		if( _TextureFormat < TextureFormat::UNKNOWN )
		{
			rectpitch = ( _rect.width / s_imageBlockInfo[( XE::uint64 )_TextureFormat].blockWidth ) * s_imageBlockInfo[( XE::uint64 )_TextureFormat].blockSize;
		}
		const uint32_t srcpitch = UINT16_MAX == _pitch ? rectpitch : _pitch;
		const uint32_t slicepitch = rectpitch * _rect.height;

		deviceCtx->UpdateSubresource( _Ptr, subres, depth ? NULL : &box, _mem.data(), srcpitch, TextureType::TEXTURE_CUBE == _Type ? slicepitch : 0 );
	}

	void Texture::Commit( XE::uint8 _stage, XE::uint32 _flags, const float _palette[][4] )
	{
// 		TextureStage & ts = s_renderD3D11->m_textureStage;
// 
// 		if( 0 != ( _flags & BGFX_SAMPLER_SAMPLE_STENCIL ) )
// 		{
// 			ts.m_srv[_stage] = s_renderD3D11->getCachedSrv(
// 				TextureHandle{ uint16_t( this - s_renderD3D11->m_textures ) }
// 				, 0
// 				, false
// 				, true
// 			);
// 		}
// 		else
// 		{
// 			ts.m_srv[_stage] = m_srv;
// 		}
// 
// 		const uint32_t flags = 0 == ( BGFX_SAMPLER_INTERNAL_DEFAULT & _flags )
// 			? _flags
// 			: uint32_t( m_flags )
// 			;
// 		uint32_t index = ( flags & BGFX_SAMPLER_BORDER_COLOR_MASK ) >> BGFX_SAMPLER_BORDER_COLOR_SHIFT;
// 		ts.m_sampler[_stage] = s_renderD3D11->getSamplerState( flags, _palette[index] );
	}

	void Texture::Resolve( XE::uint8 _resolve ) const
	{
// 		ID3D11DeviceContext * deviceCtx = _rtx->_DeviceCtx;
// 
// 		const bool needResolve = NULL != m_rt;
// 		if( needResolve )
// 		{
// 			deviceCtx->ResolveSubresource( _Texture2d, 0, m_rt, 0, s_textureFormat[m_textureFormat].m_fmt );
// 		}
// 
// 		const bool renderTarget = 0 != ( m_flags & BGFX_TEXTURE_RT_MASK );
// 		if( renderTarget
// 			&& 1 < _NumMips
// 			&& 0 != ( _resolve & BGFX_RESOLVE_AUTO_GEN_MIPS ) )
// 		{
// 			deviceCtx->GenerateMips( _SRV );
// 		}
	}

	XE::TextureHandle Texture::GetHandle() const
	{
		return { ( XE::uint64 )( this - _rtx->_Textures.data() ) };
	}

	DXGI_FORMAT Texture::GetSRVFormat() const
	{
		if( _TextureFormat > TextureFormat::UNKNOWNDEPTH )
		{
			return s_textureFormat[( XE::uint64 )_TextureFormat].m_fmtSrv;
		}

		return 0 != ( _Flags && XE::TextureFlag::SRGB ) ? s_textureFormat[( XE::uint64 )_TextureFormat].m_fmtSrgb : s_textureFormat[( XE::uint64 )_TextureFormat].m_fmt;
	}

	void FrameBuffer::Create( XE::uint8 _num, const XE::Attachment * _attachment )
	{
		for( uint32_t ii = 0; ii < XE::countof( _RTV ); ++ii )
		{
			_RTV[ii] = NULL;
		}

		for( uint32_t ii = 0; ii < XE::countof( _UAV ); ++ii )
		{
			_UAV[ii] = NULL;
		}

		_DSV = NULL;
		_SwapChain = NULL;

		_DenseIdx = UINT16_MAX;
		_NumTh = _num;
		_NeedPresent = false;
		std::memcpy( _Attachment, _attachment, _num * sizeof( Attachment ) );

		PostReset();
	}

	void FrameBuffer::Create( XE::uint16 _denseIdx, XE::WindowHandle _nwh, XE::uint32 _width, XE::uint32 _height, XE::TextureFormat _format, XE::TextureFormat _depthFormat )
	{
		SwapChainDesc scd;
		//bx::memCopy( &scd, &_rtx->m_scd, sizeof( SwapChainDesc ) );
		scd.format = TextureFormat::COUNT == _format ? scd.format : s_textureFormat[( XE::uint64 )_format].m_fmt;
		scd.width = _width;
		scd.height = _height;
		scd.nwh = ( void * ) _nwh.GetValue();
		scd.ndt = NULL;
		scd.sampleDesc = s_msaa[0];

		XE_ASSERT( SUCCEEDED( _rtx->_Dxgi->CreateSwapChain( _rtx->_Device, scd, &_SwapChain ) ) && "Failed to create swap chain." );

		XE_ASSERT( SUCCEEDED( _rtx->_Dxgi->_Factory->MakeWindowAssociation( ( HWND ) _nwh.GetValue(), 0 | DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER ) ) );

		ID3D11Resource * ptr;
		XE_ASSERT( SUCCEEDED( _SwapChain->GetBuffer( 0, IID_ID3D11Texture2D, ( void ** ) &ptr ) ) );
		XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateRenderTargetView( ptr, NULL, &_RTV[0] ) ) );
		DX_RELEASE( ptr );

		DXGI_FORMAT fmtDsv = ( _depthFormat > TextureFormat::UNKNOWNDEPTH ) ? s_textureFormat[( XE::uint64 )_depthFormat].m_fmtDsv : DXGI_FORMAT_D24_UNORM_S8_UINT;

		D3D11_TEXTURE2D_DESC dsd;
		dsd.Width = scd.width;
		dsd.Height = scd.height;
		dsd.MipLevels = 1;
		dsd.ArraySize = 1;
		dsd.Format = fmtDsv;
		dsd.SampleDesc = scd.sampleDesc;
		dsd.Usage = D3D11_USAGE_DEFAULT;
		dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		dsd.CPUAccessFlags = 0;
		dsd.MiscFlags = 0;

		ID3D11Texture2D * depthStencil;
		XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateTexture2D( &dsd, NULL, &depthStencil ) ) );
		XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateDepthStencilView( depthStencil, NULL, &_DSV ) ) );
		DX_RELEASE( depthStencil );

		_SRV[0] = NULL;
		_Window = _nwh;
		_DenseIdx = _denseIdx;
		_Num = 1;
	}

	XE::uint16 FrameBuffer::Destroy()
	{
		PreReset( true );

		DX_RELEASE( _SwapChain );

		_Num = 0;
		_Window = XE::WindowHandle::Invalid;
		_NumTh = 0;
		_NeedPresent = false;

		uint16_t denseIdx = _DenseIdx;
		_DenseIdx = UINT16_MAX;

		return denseIdx;
	}

	void FrameBuffer::PreReset( bool _force /*= false */ )
	{
		if( 0 < _NumTh || _force )
		{
			for( uint32_t ii = 0, num = _Num; ii < num; ++ii )
			{
				DX_RELEASE( _SRV[ii] );
				DX_RELEASE( _RTV[ii] );
			}

			DX_RELEASE( _DSV );
		}
	}

	void FrameBuffer::PostReset()
	{
		_Width = 0;
		_Height = 0;

		if( 0 < _NumTh )
		{
			_Num = 0;
			_NumUav = 0;

			for( uint32_t ii = 0; ii < _NumTh; ++ii )
			{
				const Attachment & at = _Attachment[ii];

				if( at.Handle )
				{
					const D3D11::Texture & texture = _rtx->_Textures[at.Handle.GetValue()];

					if( 0 == _Width )
					{
						switch( texture._Type )
						{
						case TextureType::TEXTURE_2D:
						case TextureType::TEXTURE_CUBE:
						{
							D3D11_TEXTURE2D_DESC desc;
							texture._Texture2d->GetDesc( &desc );
							_Width = desc.Width;
							_Height = desc.Height;
						}
							break;
						case TextureType::TEXTURE_3D:
						{
							D3D11_TEXTURE3D_DESC desc;
							texture._Texture3d->GetDesc( &desc );
							_Width = desc.Width;
							_Height = desc.Height;
						}
							break;
						}
					}

					const uint32_t msaaQuality = XE::Mathf::Satsub< XE::uint32 >( ( texture._Flags & XE::TextureFlag::RTMSAAMASK ).GetValue() >> ( XE::uint64 )XE::TextureFlag::RTMSAASHIFT, 1 );
					const DXGI_SAMPLE_DESC & msaa = s_msaa[msaaQuality];

					if( texture._TextureFormat > TextureFormat::UNKNOWNDEPTH )
					{
						XE_ASSERT( NULL != _DSV && "Frame buffer already has depth-stencil attached." );

						D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
						dsvDesc.Format = s_textureFormat[( XE::uint64 )texture._TextureFormat].m_fmtDsv;
						dsvDesc.Flags = 0;

						switch( texture._Type )
						{
						case TextureType::TEXTURE_2D:
						{
							if( 1 < msaa.Count )
							{
								if( 1 < texture._NumLayers )
								{
									dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
									dsvDesc.Texture2DMSArray.FirstArraySlice = at.Layer;
									dsvDesc.Texture2DMSArray.ArraySize = 1;
								}
								else
								{
									dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
								}
							}
							else
							{
								if( 1 < texture._NumLayers )
								{
									dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
									dsvDesc.Texture2DArray.FirstArraySlice = at.Layer;
									dsvDesc.Texture2DArray.ArraySize = 1;
									dsvDesc.Texture2DArray.MipSlice = at.Mip;
								}
								else
								{
									dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
									dsvDesc.Texture2D.MipSlice = at.Mip;
								}
							}

							XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateDepthStencilView( texture._Ptr, &dsvDesc, &_DSV ) ) );
						}
						break;
						case TextureType::TEXTURE_CUBE:
						{
							if( 1 < msaa.Count )
							{
								dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY;
								dsvDesc.Texture2DMSArray.FirstArraySlice = at.Layer;
								dsvDesc.Texture2DMSArray.ArraySize = 1;
							}
							else
							{
								dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
								dsvDesc.Texture2DArray.FirstArraySlice = at.Layer;
								dsvDesc.Texture2DArray.ArraySize = 1;
								dsvDesc.Texture2DArray.MipSlice = at.Mip;
							}
							XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateDepthStencilView( texture._Ptr, &dsvDesc, &_DSV ) ) );
						}
						break;
						case TextureType::TEXTURE_3D:
							break;
						}
					}
					else if( XE::AccessType::WRITE == at.Access )
					{
						D3D11_RENDER_TARGET_VIEW_DESC desc;
						desc.Format = texture.GetSRVFormat();
						switch( texture._Type )
						{
						case TextureType::TEXTURE_2D:
						{
							if( 1 < msaa.Count )
							{
								if( 1 < texture._NumLayers )
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
									desc.Texture2DMSArray.FirstArraySlice = at.Layer;
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
									desc.Texture2DArray.FirstArraySlice = at.Layer;
									desc.Texture2DArray.ArraySize = 1;
									desc.Texture2DArray.MipSlice = at.Mip;
								}
								else
								{
									desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
									desc.Texture2D.MipSlice = at.Mip;
								}
							}

							XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateRenderTargetView( texture._Ptr, & desc, & _RTV[_Num] ) ) );
						}
						break;
						case TextureType::TEXTURE_CUBE:
						{
							if( 1 < msaa.Count )
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY;
								desc.Texture2DMSArray.ArraySize = 1;
								desc.Texture2DMSArray.FirstArraySlice = at.Layer;
							}
							else
							{
								desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
								desc.Texture2DArray.ArraySize = 1;
								desc.Texture2DArray.FirstArraySlice = at.Layer;
								desc.Texture2DArray.MipSlice = at.Mip;
							}

							XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateRenderTargetView( texture._Ptr, &desc, &_RTV[_Num] ) ) );
						}
						break;
						case TextureType::TEXTURE_3D:
						{
							desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
							desc.Texture3D.MipSlice = at.Mip;
							desc.Texture3D.WSize = 1;
							desc.Texture3D.FirstWSlice = at.Layer;

							XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateRenderTargetView( texture._Ptr, &desc, &_RTV[_Num] ) ) );
						}
						break;
						}

						D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
						texture._SRV->GetDesc( &srvDesc );
						XE_ASSERT( SUCCEEDED( _rtx->_Device->CreateShaderResourceView( texture._Ptr, &srvDesc, &_SRV[_Num] ) ) );
						_Num++;
					}
					else
					{
						_UAV[_NumUav++] = texture._UAV;
					}
				}
			}
		}
	}

	void FrameBuffer::Resolve()
	{
		if( 0 < _NumTh )
		{
			for( uint32_t ii = 0; ii < _NumTh; ++ii )
			{
				const Attachment & at = _Attachment[ii];

				if( at.Handle )
				{
					const D3D11::Texture & texture = _rtx->_Textures[at.Handle];
					texture.Resolve( at.Resolve );
				}
			}
		}
	}

	void FrameBuffer::Clear( const XE::ViewClearDesc & _clear )
	{
		ID3D11DeviceContext * deviceCtx = _rtx->_DeviceCtx;

		if( _clear.Flags && XE::ClearFlag::COLOR )
		{
			XE::FColor rgba( _clear.Color );

			for( uint32_t ii = 0, num = _Num; ii < num; ++ii )
			{
				if( NULL != _RTV[ii] )
				{
					deviceCtx->ClearRenderTargetView( _RTV[ii], rgba.d );
				}
			}
		}

		if( NULL != _DSV && ( XE::MakeFlags( XE::ClearFlag::DEPTH, XE::ClearFlag::STENCIL ) && _clear.Flags ) )
		{
			DWORD flags = 0;
			flags |= ( _clear.Flags && XE::ClearFlag::DEPTH ) ? D3D11_CLEAR_DEPTH : 0;
			flags |= ( _clear.Flags && XE::ClearFlag::STENCIL ) ? D3D11_CLEAR_STENCIL : 0;
			deviceCtx->ClearDepthStencilView( _DSV, flags, _clear.Depth, _clear.Stencil );
		}
	}

	void FrameBuffer::Set()
	{
		if( 0 < _NumUav )
		{
			_rtx->_DeviceCtx->OMSetRenderTargetsAndUnorderedAccessViews( _Num, _RTV, _DSV, 16, _NumUav, _UAV, NULL );
		}
		else
		{
			_rtx->_DeviceCtx->OMSetRenderTargets( _Num, _RTV, _DSV );
		}

		_NeedPresent = UINT16_MAX != _DenseIdx;
		_rtx->_CurrentColor = _RTV[0];
		_rtx->_CurrentDepthStencil = _DSV;
	}

	HRESULT FrameBuffer::Present( XE::uint32 _syncInterval )
	{
		if( _NeedPresent )
		{
			HRESULT hr = _SwapChain->Present( _syncInterval, 0 );

			hr = !( hr == DXGI_ERROR_DEVICE_REMOVED
					|| hr == DXGI_ERROR_DEVICE_HUNG
					|| hr == DXGI_ERROR_DEVICE_RESET
					|| hr == DXGI_ERROR_DRIVER_INTERNAL_ERROR
					|| hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE ) ? S_OK : hr;
			_NeedPresent = false;
			return hr;
		}

		return S_OK;
	}

	void OcclusionQuery::PostReset()
	{
		ID3D11Device * device = _rtx->_Device;

		D3D11_QUERY_DESC desc;
		desc.Query = D3D11_QUERY_OCCLUSION;
		desc.MiscFlags = 0;
		for( uint32_t ii = 0; ii < XE::countof( _Query ); ++ii )
		{
			Query & query = _Query[ii];
			XE_ASSERT( SUCCEEDED( device->CreateQuery( &desc, &query._Ptr ) ) );
		}
	}

	void OcclusionQuery::PreReset()
	{
		for( uint32_t ii = 0; ii < XE::countof( _Query ); ++ii )
		{
			Query & query = _Query[ii];
			DX_RELEASE( query._Ptr );
		}
	}

	void OcclusionQuery::Begin( XE::RenderFrame * _render, OcclusionQueryHandle _handle )
	{
// 		while( 0 == m_control.reserve( 1 ) )
// 		{
// 			Resolve( _render, true );
// 		}
// 
// 		ID3D11DeviceContext * deviceCtx = _rtx->_DeviceCtx;
// 		Query & query = _Query[m_control.m_current];
// 		deviceCtx->Begin( query._Ptr );
// 		query._Handle = _handle;
	}

	void OcclusionQuery::End()
	{
// 		ID3D11DeviceContext * deviceCtx = _rtx->_DeviceCtx;
// 		Query & query = _Query[m_control.m_current];
// 		deviceCtx->End( query._Ptr );
// 		m_control.commit( 1 );
	}

	void OcclusionQuery::Resolve( XE::RenderFrame * _render, bool _wait /*= false */ )
	{
// 		ID3D11DeviceContext * deviceCtx = _rtx->_DeviceCtx;
// 
// 		while( 0 != m_control.available() )
// 		{
// 			Query & query = _Query[m_control.m_read];
// 
// 			if( query._Handle )
// 			{
// 				uint64_t result = 0;
// 				HRESULT hr = deviceCtx->GetData( query._Ptr, &result, sizeof( result ), _wait ? 0 : D3D11_ASYNC_GETDATA_DONOTFLUSH );
// 				if( S_FALSE == hr )
// 				{
// 					break;
// 				}
// 
// 				_render->Occlusion[query._Handle] = int32_t( result );
// 			}
// 
// 			m_control.consume( 1 );
//		}
	}

	void OcclusionQuery::Invalidate( OcclusionQueryHandle _handle )
	{
// 		const uint32_t size = m_control.m_size;
// 
// 		for( uint32_t ii = 0, num = m_control.available(); ii < num; ++ii )
// 		{
// 			Query & query = _Query[( m_control.m_read + ii ) % size];
// 			if( query._Handle== _handle )
// 			{
// 				query._Handle = OcclusionQueryHandle::Invalid;
// 			}
// 		}
	}
}
END_XE_NAMESPACE


void XE::RendererContextDirectX11::OnRender( XE::RenderFrame * frame )
{
	ExecCommand( frame, &frame->PrevCmd );

	XE::Array<XE::uint64> keys( XE::MemoryResource::GetStackMemoryResource() );

	keys.resize( frame->RenderItemSize );
	for( XE::uint64 i = 0; i < keys.size(); ++i )
	{
		keys[i] = i;
	};
	std::sort( frame->RenderItemKeys.begin(), frame->RenderItemKeys.begin() + frame->RenderItemSize, [frame]( XE::uint64 left, XE::uint64 right )
			   {
				   return frame->RenderItemKeys[left] < frame->RenderItemKeys[right];
			   } );
	for( XE::uint64 i = 0; i < keys.size(); ++i )
	{
		if( ( keys[i] & ( XE::uint64( SortKey::DRAW_MAX_VALUE ) << ( 64 - SortKey::VIEW_NUM_BITS - SortKey::DRAW_NUM_BITS ) ) ) != 1 )
		{
			DrawCall( frame, ( ( XE::RenderDraw * )frame->RenderItems[keys[i]].Data ), &frame->RenderBinds[keys[i]] );
		}
		else
		{
			ComputeCall( frame, ( ( XE::RenderCompute * )frame->RenderItems[keys[i]].Data ), &frame->RenderBinds[keys[i]] );
		}
	}

	keys.resize( frame->BlitItemSize );
	for( XE::uint64 i = 0; i < keys.size(); ++i )
	{
		keys[i] = i;
	};
	std::sort( frame->BlitItemKeys.begin(), frame->BlitItemKeys.begin() + frame->BlitItemSize, [frame]( XE::uint64 left, XE::uint64 right )
			   {
				   return frame->BlitItemKeys[left] < frame->BlitItemKeys[right];
			   } );
	for( XE::uint64 i = 0; i < keys.size(); ++i )
	{
		BlitCall( frame, &frame->BlitItems[keys[i]] );
	}

	ExecCommand( frame, &frame->PostCmd );
}

void XE::RendererContextDirectX11::BlitCall( XE::RenderFrame * frame, XE::RenderBlit * item )
{

}

void XE::RendererContextDirectX11::DrawCall( XE::RenderFrame * frame, XE::RenderDraw * item, XE::RenderBind * bind )
{

}

void XE::RendererContextDirectX11::ComputeCall( XE::RenderFrame * frame, XE::RenderCompute * item, XE::RenderBind * bind )
{

}

void XE::RendererContextDirectX11::ExecCommand( XE::RenderFrame * frame, XE::Buffer * buffer )
{
	bool cmd_exit = false;
	while( cmd_exit )
	{
		XE::CommandType cmd = XE::CommandType::END;
		buffer->Read( cmd );

		switch( cmd )
		{
		case XE::CommandType::RENDERER_INIT:
			Init( frame );
			break;
		case XE::CommandType::CREATE_SHADER:
			CreateShader( frame );
			break;
		case XE::CommandType::CREATE_PROGRAM:
			CreateProgram( frame );
			break;
		case XE::CommandType::CREATE_TEXTURE:
			CreateTexture( frame );
			break;
		case XE::CommandType::CREATE_FRAME_BUFFER:
			CreateFrameBuffer( frame );
			break;
		case XE::CommandType::CREATE_INDEX_BUFFER:
			CreateIndexBuffer( frame );
			break;
		case XE::CommandType::CREATE_VERTEX_LAYOUT:
			CreateVertexLayout( frame );
			break;
		case XE::CommandType::CREATE_VERTEX_BUFFER:
			CreateVertexBuffer( frame );
			break;
		case XE::CommandType::CREATE_INDIRECT_BUFFER:
			CreateIndirectBuffer( frame );
			break;
		case XE::CommandType::CREATE_OCCLUSION_QUERY:
			CreateOcclusionQuery( frame );
			break;
		case XE::CommandType::CREATE_DYNAMIC_INDEX_BUFFER:
			CreateDynamicIndexBuffer( frame );
			break;
		case XE::CommandType::CREATE_DYNAMIC_VERTEX_BUFFER:
			CreateDynamicVertexBuffer( frame );
			break;
		case XE::CommandType::UPDATE_TEXTURE:
			UpdateTexture( frame );
			break;
		case XE::CommandType::UPDATE_DYNAMIC_INDEX_BUFFER:
			UpdateDynamicIndexBuffer( frame );
			break;
		case XE::CommandType::UPDATE_DYNAMIC_VERTEX_BUFFER:
			UpdateDynamicVertexBuffer( frame );
			break;
		case XE::CommandType::READ_TEXTURE:
			ReadTexture( frame );
			break;
		case XE::CommandType::END:
			cmd_exit = true;
			break;
		case XE::CommandType::RENDERER_SHUTDOWN:
			Shutdown( frame );
			break;
		case XE::CommandType::DESTROY_SHADER:
			DestoryShader( frame );
			break;
		case XE::CommandType::DESTROY_TEXTURE:
			DestoryTexture( frame );
			break;
		case XE::CommandType::DESTROY_PROGRAM:
			DestoryProgram( frame );
			break;
		case XE::CommandType::DESTROY_FRAMEBUFFER:
			DestoryFrameBuffer( frame );
			break;
		case XE::CommandType::DESTROY_INDEX_BUFFER:
			DestoryIndexBuffer( frame );
			break;
		case XE::CommandType::DESTROY_VERTEX_LAYOUT:
			DestoryVertexLayout( frame );
			break;
		case XE::CommandType::DESTROY_VERTEX_BUFFER:
			DestoryVertexBuffer( frame );
			break;
		case XE::CommandType::DESTROY_INDIRECT_BUFFER:
			DestoryIndirectBuffer( frame );
			break;
		case XE::CommandType::DESTROY_OCCLUSION_QUERY:
			DestoryOcclusionQuery( frame );
			break;
		case XE::CommandType::DESTROY_DYNAMIC_INDEX_BUFFER:
			DestoryDynamicIndexBuffer( frame );
			break;
		case XE::CommandType::DESTROY_DYNAMIC_VERTEX_BUFFER:
			DestoryDynamicVertexBuffer( frame );
			break;
		case XE::CommandType::REQUEST_SCREEN_SHOT:
			RequestScreenShot( frame );
			break;
		default:
			break;
		}
	}
}

void XE::RendererContextDirectX11::Init( XE::RenderFrame * frame )
{
	_rtx = new XE::D3D11::RenderContext;

	XE::CapsInfo caps = GetCaps();
	const XE::InitDesc & init = GetInit();

	_rtx->_DX11Dll = XE::Library::Open( "d3d11.dll" );
	auto D3D11CreateDevice = XE::Library::SymbolT< PFN_D3D11_CREATE_DEVICE>( _rtx->_DX11Dll, "D3D11CreateDevice" );
	XE_ASSERT( D3D11CreateDevice != nullptr && "Init error: Function D3D11CreateDevice not found." );

	_rtx->_Dxgi = new DXGI;
	_rtx->_Dxgi->Init( caps );


	D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	HRESULT hr = S_OK;

	for( ;;)
	{
		uint32_t flags = D3D11_CREATE_DEVICE_SINGLETHREADED | D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		hr = E_FAIL;
		for( uint32_t ii = 0; ii < XE::countof( featureLevel ) && FAILED( hr );)
		{
			hr = D3D11CreateDevice( _rtx->_Dxgi->_Adapter
									, _rtx->_Dxgi->_DriverType
									, NULL
									, flags
									, &featureLevel[ii]
									, XE::countof( featureLevel ) - ii
									, D3D11_SDK_VERSION
									, &_rtx->_Device
									, &_rtx->_FeatureLevel
									, &_rtx->_DeviceCtx
			);

			if( FAILED( hr ) )
			{
				XE_LOG( LoggerLevel::Warning, "Direct3D11 device feature level %1.%2.", ( _rtx->_FeatureLevel >> 12 ) & 0xf, ( _rtx->_FeatureLevel >> 8 ) & 0xf );
			}

			++ii;
		}

		if( FAILED( hr ) && D3D_DRIVER_TYPE_WARP != _rtx->_Dxgi->_DriverType )
		{
			_rtx->_Dxgi->_DriverType = D3D_DRIVER_TYPE_WARP;
			continue;
		}

		break;
	}

	_rtx->_Dxgi->Update( _rtx->_Device );



	{
		caps.Supported |= XE::CapsFlag::TEXTURE3D;
		caps.Supported |= XE::CapsFlag::VERTEXATTRIBHALF;
		caps.Supported |= XE::CapsFlag::VERTEXATTRIBUINT10;
		caps.Supported |= XE::CapsFlag::VERTEXID;
		caps.Supported |= XE::CapsFlag::FRAGMENTDEPTH;
		caps.Supported |= XE::CapsFlag::TEXTUREDIRECTACCESS;
		caps.Supported |= XE::CapsFlag::SWAPCHAIN;
		caps.Supported |= XE::CapsFlag::DRAWINDIRECT;
		caps.Supported |= XE::CapsFlag::TEXTUREBLIT;
		caps.Supported |= XE::CapsFlag::TEXTUREREADBACK;
		caps.Supported |= ( _rtx->_FeatureLevel >= D3D_FEATURE_LEVEL_9_2 ) ? XE::CapsFlag::OCCLUSIONQUERY : XE::CapsFlag::NONE;
		caps.Supported |= XE::CapsFlag::ALPHATOCOVERAGE;
		caps.Supported |= XE::CapsFlag::TEXTURE2DARRAY;
		caps.Supported |= XE::CapsFlag::TEXTURECUBEARRAY;
		caps.Supported |= ( _rtx->_FeatureLevel >= D3D_FEATURE_LEVEL_11_1 ) ? XE::CapsFlag::FRAMEBUFFERRW : XE::CapsFlag::NONE;

		if( _rtx->_FeatureLevel <= D3D_FEATURE_LEVEL_9_2 )
		{
			caps.Limits.MaxTextureSize = D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION;
			caps.Limits.MaxFBAttachments = std::min< XE::uint32 >( D3D_FL9_1_SIMULTANEOUS_RENDER_TARGET_COUNT, GFX_MAX_ATTACHMENTS );
			caps.Limits.MaxVertexStreams = std::min< XE::uint32 >( 16, GFX_MAX_VERTEX_BUFFERS );
		}
		else if( _rtx->_FeatureLevel == D3D_FEATURE_LEVEL_9_3 )
		{
			caps.Limits.MaxTextureSize = D3D_FL9_3_REQ_TEXTURE2D_U_OR_V_DIMENSION;
			caps.Limits.MaxFBAttachments = std::min< XE::uint32 >( D3D_FL9_3_SIMULTANEOUS_RENDER_TARGET_COUNT, GFX_MAX_ATTACHMENTS );
			caps.Limits.MaxVertexStreams = std::min< XE::uint32 >( 16, GFX_MAX_VERTEX_BUFFERS );
		}
		else
		{
			caps.Supported |= XE::CapsFlag::TEXTURECOMPAREALL;
			caps.Limits.MaxTextureSize = D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION;
			caps.Limits.MaxTextureLayers = D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION;
			caps.Limits.MaxFBAttachments = std::min< XE::uint32 >( D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, GFX_MAX_ATTACHMENTS );
			caps.Limits.MaxVertexStreams = std::min< XE::uint32 >( D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, GFX_MAX_VERTEX_BUFFERS );
			caps.Limits.MaxComputeBindings = std::min( 16, D3D_FEATURE_LEVEL_11_1 <= _rtx->_FeatureLevel ? D3D11_1_UAV_SLOT_COUNT : D3D11_PS_CS_UAV_REGISTER_COUNT );
		}

		if( _rtx->_FeatureLevel >= D3D_FEATURE_LEVEL_9_2 )
		{
			caps.Supported |= XE::CapsFlag::INDEX32;
		}

		if( _rtx->_FeatureLevel >= D3D_FEATURE_LEVEL_10_1 )
		{
			caps.Supported |= XE::CapsFlag::BLENDINDEPENDENT;
		}

		if( _rtx->_FeatureLevel == D3D_FEATURE_LEVEL_10_0 || _rtx->_FeatureLevel == D3D_FEATURE_LEVEL_10_1 )
		{
			struct D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS
			{
				BOOL ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x;
			};

			D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS data;
			HRESULT hr = _rtx->_Device->CheckFeatureSupport( D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &data, sizeof( data ) );
			if( SUCCEEDED( hr ) && data.ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x )
			{
				caps.Supported |= XE::CapsFlag::COMPUTE;
			}
		}
		else if( _rtx->_FeatureLevel >= D3D_FEATURE_LEVEL_11_0 )
		{
			caps.Supported |= XE::CapsFlag::COMPUTE;
		}

		if( _rtx->_FeatureLevel >= D3D_FEATURE_LEVEL_9_3 )
		{
			caps.Supported |= XE::CapsFlag::INSTANCING;
		}
		else
		{
			struct D3D11_FEATURE_DATA_D3D9_SIMPLE_INSTANCING_SUPPORT
			{
				BOOL SimpleInstancingSupported;
			};

			D3D11_FEATURE_DATA_D3D9_SIMPLE_INSTANCING_SUPPORT data;
			HRESULT hr = _rtx->_Device->CheckFeatureSupport( D3D11_FEATURE( 11 ) /*D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT*/, &data, sizeof( data ) );
			if( SUCCEEDED( hr ) && data.SimpleInstancingSupported )
			{
				caps.Supported |= XE::CapsFlag::INSTANCING;
			}
		}

		if( _rtx->_FeatureLevel <= D3D_FEATURE_LEVEL_9_3 )
		{
			struct D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT
			{
				BOOL SupportsDepthAsTextureWithLessEqualComparisonFilter;
			};

			D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT data;
			HRESULT hr = _rtx->_Device->CheckFeatureSupport( D3D11_FEATURE( 9 ) /*D3D11_FEATURE_D3D9_SHADOW_SUPPORT*/, &data, sizeof( data ) );
			if( SUCCEEDED( hr )
				&& data.SupportsDepthAsTextureWithLessEqualComparisonFilter )
			{
				caps.Supported |= XE::CapsFlag::TEXTURECOMPARELEQUAL;
			}
		}

		for( uint32_t ii = 0; ii < ( XE::uint32 )XE::TextureFormat::COUNT; ++ii )
		{
			XE::CapsFormatFlags support = XE::CapsFormatFlag::NONE;

			const DXGI_FORMAT fmt = ( XE::TextureFormat( ii ) >= XE::TextureFormat::D16 && XE::TextureFormat( ii ) <= XE::TextureFormat::D0S8 )
				? s_textureFormat[ii].m_fmtDsv
				: s_textureFormat[ii].m_fmt
				;
			const DXGI_FORMAT fmtSrgb = s_textureFormat[ii].m_fmtSrgb;

			if( DXGI_FORMAT_UNKNOWN != fmt )
			{
				struct D3D11_FEATURE_DATA_FORMAT_SUPPORT
				{
					DXGI_FORMAT InFormat;
					UINT OutFormatSupport;
				};

				D3D11_FEATURE_DATA_FORMAT_SUPPORT data; // D3D11_FEATURE_DATA_FORMAT_SUPPORT2
				data.InFormat = fmt;
				HRESULT hr = _rtx->_Device->CheckFeatureSupport( D3D11_FEATURE_FORMAT_SUPPORT, &data, sizeof( data ) );
				if( SUCCEEDED( hr ) )
				{
					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_TEXTURE2D | D3D11_FORMAT_SUPPORT_TEXTURE3D | D3D11_FORMAT_SUPPORT_TEXTURECUBE ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTURE2D;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_TEXTURE3D ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTURE3D;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_TEXTURECUBE ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTURECUBE;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_BUFFER | D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER | D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTUREVERTEX;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_SHADER_LOAD ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTUREIMAGE;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_RENDER_TARGET | D3D11_FORMAT_SUPPORT_DEPTH_STENCIL ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTUREFRAMEBUFFER;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTUREFRAMEBUFFERMSAA;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_MULTISAMPLE_LOAD ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTUREMSAA;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_MIP_AUTOGEN ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTUREMIPAUTOGEN;
					}
				}
				else
				{
					XE_LOG( LoggerLevel::Warning, "CheckFeatureSupport failed with %1 for format %2.", hr, ii );
				}

				if( ( support & XE::CapsFormatFlag::TEXTUREIMAGE ) != XE::CapsFormatFlag::NONE )
				{
					support &= ~XE::MakeFlags( XE::CapsFormatFlag::TEXTUREIMAGE );

					data.InFormat = s_textureFormat[ii].m_fmt;
					hr = _rtx->_Device->CheckFeatureSupport( D3D11_FEATURE_FORMAT_SUPPORT2, &data, sizeof( data ) );
					if( SUCCEEDED( hr ) )
					{
						if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT2_UAV_TYPED_LOAD | D3D11_FORMAT_SUPPORT2_UAV_TYPED_STORE ) ) )
						{
							support |= XE::CapsFormatFlag::TEXTUREIMAGE;
						}
					}
				}
			}

			if( DXGI_FORMAT_UNKNOWN != fmtSrgb )
			{
				struct D3D11_FEATURE_DATA_FORMAT_SUPPORT
				{
					DXGI_FORMAT InFormat;
					UINT OutFormatSupport;
				};

				D3D11_FEATURE_DATA_FORMAT_SUPPORT data; // D3D11_FEATURE_DATA_FORMAT_SUPPORT2
				data.InFormat = fmtSrgb;
				HRESULT hr = _rtx->_Device->CheckFeatureSupport( D3D11_FEATURE_FORMAT_SUPPORT, &data, sizeof( data ) );
				if( SUCCEEDED( hr ) )
				{
					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_TEXTURE2D ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTURE2DSRGB;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_TEXTURE3D ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTURE3DSRGB;
					}

					if( 0 != ( data.OutFormatSupport & ( D3D11_FORMAT_SUPPORT_TEXTURECUBE ) ) )
					{
						support |= XE::CapsFormatFlag::TEXTURECUBESRGB;
					}
				}
				else
				{
					XE_LOG( LoggerLevel::Warning, "CheckFeatureSupport failed with %1 for sRGB format %2.", hr, ii );
				}
			}

			caps.SupportFormat[ii] = support;
		}
	}


	SetCaps( caps );
}

void XE::RendererContextDirectX11::Shutdown( XE::RenderFrame * frame )
{
	_rtx->_DeviceCtx->ClearState();

	_rtx->_BlendStateCahce.clear();
	_rtx->_DepthStencilStateCache.clear();
	_rtx->_InputLayoutCache.clear();
	_rtx->_RasterizerStateCache.clear();
	_rtx->_SamplerStateCache.clear();

	for( auto i : _rtx->_IndexBuffers )
	{
		i.Destroy();
	}
	for( auto i : _rtx->_VertexBuffers )
	{
		i.Destroy();
	}
	for( auto i : _rtx->_Shaders )
	{
		i.Destroy();
	}
	for( auto i : _rtx->_Programs )
	{
		i.Destroy();
	}
	for( auto i : _rtx->_Textures )
	{
		i.Destroy();
	}
	for( auto i : _rtx->_FrameBuffers )
	{
		i.Destroy();
	}

	DX_RELEASE( _rtx->_DeviceCtx );
	DX_RELEASE( _rtx->_Device );

	_rtx->_Dxgi->Shutdown();
	delete _rtx->_Dxgi;
	_rtx->_Dxgi = nullptr;

	XE::Library::Close( _rtx->_DX11Dll );
	_rtx->_DX11Dll = XE::LibraryHandle::Invalid;

	delete _rtx;
	_rtx = nullptr;
}

void XE::RendererContextDirectX11::CreateProgram( XE::RenderFrame * frame )
{
	XE::ProgramHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	_rtx->_Programs[handle].Create( &_rtx->_Shaders[desc.VS], &_rtx->_Shaders[desc.FS] );
}

void XE::RendererContextDirectX11::CreateFrameBuffer( XE::RenderFrame * frame )
{
	XE::FrameBufferHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	if( desc.Window )
	{
		_rtx->_FrameBuffers[handle].Create( 0, desc.Window, desc.Width, desc.Height, desc.ColorFormat, desc.DepthFormat );
	}
	else
	{
		_rtx->_FrameBuffers[handle].Create( desc.AttachmentCount, desc.Attachments );
	}
}

void XE::RendererContextDirectX11::CreateVertexLayout( XE::RenderFrame * frame )
{
	( void ) ( frame );
}

void XE::RendererContextDirectX11::CreateOcclusionQuery( XE::RenderFrame * frame )
{
	// TODO: 
}

void XE::RendererContextDirectX11::CreateIndirectBuffer( XE::RenderFrame * frame )
{
	// TODO: 
}

void XE::RendererContextDirectX11::CreateShader( XE::RenderFrame * frame )
{
	XE::ShaderHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );
	const auto & desc = GetDesc( handle );

	_rtx->_Shaders[handle].Create( desc.Type, view );
}

void XE::RendererContextDirectX11::CreateTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );
	const auto & desc = GetDesc( handle );

	_rtx->_Textures[handle].Create( view, desc );
}

void XE::RendererContextDirectX11::CreateIndexBuffer( XE::RenderFrame * frame )
{
	XE::IndexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );
	const auto & desc = GetDesc( handle );

	_rtx->_IndexBuffers[handle].Create( view.size(), ( void * ) view.data(), desc.Flags );
}

void XE::RendererContextDirectX11::CreateVertexBuffer( XE::RenderFrame * frame )
{
	XE::VertexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );
	const auto & desc = GetDesc( handle );

	_rtx->_VertexBuffers[handle].Create( view.size(), ( void * ) view.data(), desc.Layout, desc.Flags );
}

void XE::RendererContextDirectX11::CreateDynamicIndexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicIndexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	_rtx->_IndexBuffers[handle].Create( desc.Size, nullptr, desc.Flags );
}

void XE::RendererContextDirectX11::CreateDynamicVertexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicVertexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	_rtx->_VertexBuffers[handle].Create( desc.Size, nullptr, desc.Layout, desc.Flags );
}

void XE::RendererContextDirectX11::ReadTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PrevCmd.Read( handle );
	std::uintptr_t data;
	frame->PrevCmd.Read( data );
	XE::uint8 mip;
	frame->PrevCmd.Read( mip );


	const D3D11::Texture & texture = _rtx->_Textures[handle];
	D3D11_MAPPED_SUBRESOURCE mapped;

	XE_ASSERT( SUCCEEDED( _rtx->_DeviceCtx->Map( texture._Ptr, mip, D3D11_MAP_READ, 0, &mapped ) ) );

	uint32_t srcWidth =  std::max< XE::uint32 >( 1, texture._Width >> mip );
	uint32_t srcHeight = std::max< XE::uint32 >( 1, texture._Height >> mip );
	uint8_t * src = ( uint8_t * ) mapped.pData;
	uint32_t srcPitch = mapped.RowPitch;

	const uint8_t bpp = s_imageBlockInfo[( XE::uint64 )texture._TextureFormat].bitsPerPixel;
	uint8_t * dst = ( uint8_t * ) data;
	uint32_t dstPitch = srcWidth * bpp / 8;

	uint32_t pitch = std::min( srcPitch, dstPitch );

	for( uint32_t yy = 0, height = srcHeight; yy < height; ++yy )
	{
		std::memcpy( dst, src, pitch );

		src += srcPitch;
		dst += dstPitch;
	}

	_rtx->_DeviceCtx->Unmap( texture._Ptr, mip );
}

void XE::RendererContextDirectX11::UpdateTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PrevCmd.Read( handle );
	XE::UpdateTextureDesc desc;
	frame->PrevCmd.Read( desc );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );

	XE::Recti rect( desc.X, desc.Y, desc.Width, desc.Height );
	_rtx->_Textures[handle].Update( desc.Side, desc.Mip, rect, desc.Z, desc.Depth, desc.Layer, view );
}

void XE::RendererContextDirectX11::UpdateDynamicIndexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicIndexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::uint64 start;
	frame->PrevCmd.Read( start );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );

	const auto & desc = GetDesc( handle );

	_rtx->_IndexBuffers[handle].Update( start, std::min( desc.Size, view.size() ), ( void * ) view.data() );
}

void XE::RendererContextDirectX11::UpdateDynamicVertexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicVertexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::uint64 start;
	frame->PrevCmd.Read( start );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );

	const auto & desc = GetDesc( handle );

	_rtx->_VertexBuffers[handle].Update( start, std::min( desc.Size, view.size() ), ( void * ) view.data() );
}

void XE::RendererContextDirectX11::RequestScreenShot( XE::RenderFrame * frame )
{
	XE::FrameBufferHandle handle;
	frame->PostCmd.Read( handle );
	std::string userdata;
	frame->PostCmd.Read( userdata );
	ScreenShotCallbackType callback;
	frame->PostCmd.Read( ( uintptr_t & ) callback );

	IDXGISwapChain * swapChain = _rtx->_FrameBuffers[handle]._SwapChain;

	if( NULL == swapChain )
	{
		XE_LOG( LoggerLevel::Warning, "Unable to capture screenshot %1.", userdata );
		return;
	}

	ID3D11Texture2D * backBuffer;
	XE_ASSERT( SUCCEEDED( swapChain->GetBuffer( 0, IID_ID3D11Texture2D, ( void ** ) &backBuffer ) ) );

	D3D11_TEXTURE2D_DESC backBufferDesc;
	backBuffer->GetDesc( &backBufferDesc );

	D3D11_TEXTURE2D_DESC desc;
	std::memcpy( &desc, &backBufferDesc, sizeof( desc ) );
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	ID3D11Texture2D * texture;
	HRESULT hr = _rtx->_Device->CreateTexture2D( &desc, NULL, &texture );
	if( SUCCEEDED( hr ) )
	{
		if( backBufferDesc.SampleDesc.Count == 1 )
		{
			_rtx->_DeviceCtx->CopyResource( texture, backBuffer );
		}
		else
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.CPUAccessFlags = 0;
			ID3D11Texture2D * resolve;
			hr = _rtx->_Device->CreateTexture2D( &desc, NULL, &resolve );
			if( SUCCEEDED( hr ) )
			{
				_rtx->_DeviceCtx->ResolveSubresource( resolve, 0, backBuffer, 0, desc.Format );
				_rtx->_DeviceCtx->CopyResource( texture, resolve );
				DX_RELEASE( resolve );
			}
		}

		D3D11_MAPPED_SUBRESOURCE mapped;
		XE_ASSERT( SUCCEEDED( _rtx->_DeviceCtx->Map( texture, 0, D3D11_MAP_READ, 0, &mapped ) ) );

		// TODO: 
// 		bimg::imageSwizzleBgra8(
// 			mapped.pData
// 			, mapped.RowPitch
// 			, backBufferDesc.Width
// 			, backBufferDesc.Height
// 			, mapped.pData
// 			, mapped.RowPitch
// 		);

		callback( userdata.c_str(), backBufferDesc.Width, backBufferDesc.Height, mapped.RowPitch, ( const XE::uint8 * )mapped.pData, backBufferDesc.Height * mapped.RowPitch, false );

		_rtx->_DeviceCtx->Unmap( texture, 0 );

		DX_RELEASE( texture );
	}

	DX_RELEASE( backBuffer );
}

void XE::RendererContextDirectX11::DestoryShader( XE::RenderFrame * frame )
{
	XE::ShaderHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_Shaders[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryProgram( XE::RenderFrame * frame )
{
	XE::ProgramHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_Programs[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_Textures[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryFrameBuffer( XE::RenderFrame * frame )
{
	XE::FrameBufferHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_FrameBuffers[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryIndexBuffer( XE::RenderFrame * frame )
{
	XE::IndexBufferHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_IndexBuffers[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryVertexLayout( XE::RenderFrame * frame )
{
	( void ) ( frame );
}

void XE::RendererContextDirectX11::DestoryVertexBuffer( XE::RenderFrame * frame )
{
	XE::VertexBufferHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_VertexBuffers[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryIndirectBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryOcclusionQuery( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryDynamicIndexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicIndexBufferHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_IndexBuffers[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryDynamicVertexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicVertexBufferHandle handle;
	frame->PostCmd.Read( handle );

	_rtx->_VertexBuffers[handle].Destroy();
}

#endif
