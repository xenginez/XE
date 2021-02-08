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
		void Create( ID3D11Device * _device, XE::uint32 _size, void * _data, XE::BufferFlags _flags, XE::uint16 _stride = 0, bool _vertex = false );
		void Update( ID3D11DeviceContext * _deviceCtx, XE::uint32 _offset, XE::uint32 _size, void * _data, bool _discard = false );
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
		void Create( ID3D11Device * _device, XE::uint32 _size, void * _data, XE::VertexLayoutHandle _layoutHandle, XE::BufferFlags _flags );

		XE::VertexLayoutHandle _LayoutHandle;
	};

	struct Shader
	{
		void Create( ID3D11Device * _device, XE::ShaderType _type, XE::MemoryView _mem );
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
		void * CreateTexture2D( ID3D11DeviceContext * deviceCtx, const D3D11_TEXTURE2D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture2D ** _gpuTexture2d );
		void * CreateTexture3D( ID3D11DeviceContext * deviceCtx, const D3D11_TEXTURE3D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture3D ** _gpuTexture3d );
		void Destroy( ID3D11DeviceContext * deviceCtx );

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
		void * Create( XE::MemoryView _mem, XE::TextureFlags _flags, XE::uint8 _skip );
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

		union
		{
			ID3D11Resource * _RT = nullptr;
			ID3D11Texture2D * _RT2d;
		};

		ID3D11ShaderResourceView * _SRV = nullptr;
		ID3D11UnorderedAccessView * _UAV = nullptr;
		XE::TextureFlags _Flags = 0;
		XE::uint32 _Width = 0;
		XE::uint32 _Height = 0;
		XE::uint32 _Depth = 0;
		XE::uint32 _NumLayers = 0;
		XE::uint8  _Type = 0;
		XE::uint8  _RequestedFormat = 0;
		XE::uint8  _TextureFormat = 0;
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
		void Clear( const XE::ViewClearDesc & _clear, const float _palette[][4] );
		void Set();
		HRESULT Present( XE::uint32 _syncInterval );

		ID3D11RenderTargetView * _RTV[GFX_MAX_ATTACHMENTS - 1];
		ID3D11UnorderedAccessView * _UAV[GFX_MAX_ATTACHMENTS - 1];
		ID3D11ShaderResourceView * _SRV[GFX_MAX_ATTACHMENTS - 1];
		ID3D11DepthStencilView * _DSV;
		DXGI::SwapChainI * _SwapChain;
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

	struct TimerQuery
	{
		void PostReset();
		void PreReset();
		XE::uint32 Begin( XE::uint32 _resultIdx );
		void End( XE::uint32 _idx );
		bool Update();

		struct Query
		{
			ID3D11Query * _Disjoint;
			ID3D11Query * _Begin;
			ID3D11Query * _End;
			XE::uint32    _ResultIdx;
			bool          _Ready;
		};

		struct Result
		{
			void reset()
			{
				_Begin = 0;
				_End = 0;
				_Frequency = 1;
				_Pending = 0;
			}

			XE::uint64 _Begin;
			XE::uint64 _End;
			XE::uint64 _Frequency;
			XE::uint32 _Pending;
		};

		Result _Result[GFX_MAX_VIEW + 1];

		Query _Query[GFX_MAX_VIEW * 4];
		bx::RingBufferControl m_control;
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
		bx::RingBufferControl m_control;
	};

	void Buffer::Create( ID3D11Device * _device, XE::uint32 _size, void * _data, XE::BufferFlags _flags, XE::uint16 _stride /*= 0*/, bool _vertex /*= false */ )
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

			XE_ASSERT( SUCCEEDED( _device->CreateBuffer( &desc, NULL == _data ? NULL : &srd, &_Ptr ) ) );

			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			uavd.Format = format;
			uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
			uavd.Buffer.FirstElement = 0;
			uavd.Buffer.NumElements = _Size / stride;
			uavd.Buffer.Flags = 0;
			XE_ASSERT( SUCCEEDED( _device->CreateUnorderedAccessView( _Ptr, &uavd, &_UAV ) ) );
		}
		else if( _Dynamic )
		{
			desc.Usage = D3D11_USAGE_DYNAMIC;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

			XE_ASSERT( SUCCEEDED( _device->CreateBuffer( &desc, NULL, &_Ptr ) ) );
		}
		else
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE;
			desc.CPUAccessFlags = 0;

			XE_ASSERT( SUCCEEDED( _device->CreateBuffer( &desc, &srd, &_Ptr ) ) );
		}

		if( needSrv )
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			srvd.Format = format;
			srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
			srvd.Buffer.FirstElement = 0;
			srvd.Buffer.NumElements = _Size / stride;
			XE_ASSERT( SUCCEEDED( _device->CreateShaderResourceView( _Ptr, &srvd, &_SRV ) ) );
		}
	}

	void Buffer::Update( ID3D11DeviceContext * _deviceCtx, XE::uint32 _offset, XE::uint32 _size, void * _data, bool _discard /*= false */ )
	{
		XE_ASSERT( _Dynamic && "Must be dynamic!" );

		if( _discard )
		{
			D3D11_MAPPED_SUBRESOURCE mapped;
			XE_ASSERT( SUCCEEDED( _deviceCtx->Map( _Ptr, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped ) ) );
			std::memcpy( ( uint8_t * ) mapped.pData + _offset, _data, _size );
			_deviceCtx->Unmap( _Ptr, 0 );
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
			_deviceCtx->GetDevice( &device );

			ID3D11Buffer * ptr;
			XE_ASSERT( SUCCEEDED( device->CreateBuffer( &desc, &srd, &ptr ) ) );

			_deviceCtx->CopySubresourceRegion( _Ptr, 0, _offset, 0, 0, ptr, 0, &srcBox );

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

	void VertexBuffer::Create( ID3D11Device * _device, XE::uint32 _size, void * _data, XE::VertexLayoutHandle _layoutHandle, XE::BufferFlags _flags )
	{
		_LayoutHandle = _layoutHandle;

		D3D11::Buffer::Create( _device, _size, _data, _flags, 0, true );
	}

	void Shader::Create( ID3D11Device * _device, XE::ShaderType _type, XE::MemoryView _mem )
	{
		_Type = _type;

		switch( _type )
		{
		case XE::ShaderType::VS:
			XE_ASSERT( SUCCEEDED( _device->CreateVertexShader( _mem.data(), _mem.size(), nullptr, &_VertexShader ) ) );
			break;
		case XE::ShaderType::FS:
			XE_ASSERT( SUCCEEDED( _device->CreatePixelShader( _mem.data(), _mem.size(), nullptr, &_PixelShader ) ) );
			break;
		case XE::ShaderType::CS:
			XE_ASSERT( SUCCEEDED( _device->CreateComputeShader( _mem.data(), _mem.size(), nullptr, &_ComputeShader ) ) );
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

	void * DirectAccessResource::CreateTexture2D( ID3D11DeviceContext * deviceCtx, const D3D11_TEXTURE2D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture2D ** _gpuTexture2d )
	{
		ID3D11Device * device = nullptr;

		deviceCtx->GetDevice( &device );

		XE_ASSERT( SUCCEEDED( device->CreateTexture2D( _gpuDesc, _srd, _gpuTexture2d ) ) );

		D3D11_TEXTURE2D_DESC cpuDesc;
		std::memcpy( &cpuDesc, _gpuDesc, sizeof( cpuDesc ) );
		cpuDesc.BindFlags = 0;
		cpuDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		cpuDesc.Usage = D3D11_USAGE_STAGING;

		XE_ASSERT( SUCCEEDED( device->CreateTexture2D( &cpuDesc, NULL, &_Texture2d ) ) );

		deviceCtx->CopyResource( _Texture2d, *_gpuTexture2d );

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		deviceCtx->Map( _Texture2d, 0, D3D11_MAP_WRITE, 0, &mappedResource );
		_Descriptor = reinterpret_cast< IntelDirectAccessResourceDescriptor * >( mappedResource.pData );

		DX_RELEASE( device );

		return _Descriptor->_Ptr;
	}

	void * DirectAccessResource::CreateTexture3D( ID3D11DeviceContext * deviceCtx, const D3D11_TEXTURE3D_DESC * _gpuDesc, const D3D11_SUBRESOURCE_DATA * _srd, ID3D11Texture3D ** _gpuTexture3d )
	{
		ID3D11Device * device = nullptr;

		deviceCtx->GetDevice( &device );

		XE_ASSERT( SUCCEEDED( device->CreateTexture3D( _gpuDesc, _srd, _gpuTexture3d ) ) );

		D3D11_TEXTURE3D_DESC cpuDesc;
		std::memcpy( &cpuDesc, _gpuDesc, sizeof( cpuDesc ) );
		cpuDesc.BindFlags = 0;
		cpuDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		cpuDesc.Usage = D3D11_USAGE_STAGING;

		XE_ASSERT( SUCCEEDED( device->CreateTexture3D( &cpuDesc, NULL, &_Texture3d ) ) );

		deviceCtx->CopyResource( _Texture3d, *_gpuTexture3d );

		D3D11_MAPPED_SUBRESOURCE mappedResource;
		deviceCtx->Map( _Texture3d, 0, D3D11_MAP_WRITE, 0, &mappedResource );
		_Descriptor = reinterpret_cast< IntelDirectAccessResourceDescriptor * >( mappedResource.pData );

		DX_RELEASE( device );

		return _Descriptor->_Ptr;
	}

	void DirectAccessResource::Destroy( ID3D11DeviceContext * deviceCtx )
	{
		if( _Descriptor )
		{
			deviceCtx->Unmap( _Ptr, 0 );
			_Descriptor = nullptr;
			DX_RELEASE( _Ptr );
			_Ptr = nullptr;
		}
	}

	void * Texture::Create( XE::MemoryView _mem, XE::TextureFlags _flags, XE::uint8 _skip )
	{

	}

	void Texture::Destroy()
	{

	}

	void Texture::OverrideInternal( uintptr_t _ptr )
	{

	}

	void Texture::Update( XE::uint8 _side, XE::uint8 _mip, const XE::Recti & _rect, XE::uint16 _z, XE::uint16 _depth, XE::uint16 _pitch, XE::MemoryView _mem )
	{

	}

	void Texture::Commit( XE::uint8 _stage, XE::uint32 _flags, const float _palette[][4] )
	{

	}

	void Texture::Resolve( XE::uint8 _resolve ) const
	{

	}

	XE::TextureHandle Texture::GetHandle() const
	{

	}

	DXGI_FORMAT Texture::GetSRVFormat() const
	{

	}

	void FrameBuffer::Create( XE::uint8 _num, const XE::Attachment * _attachment )
	{

	}

	void FrameBuffer::Create( XE::uint16 _denseIdx, XE::WindowHandle _nwh, XE::uint32 _width, XE::uint32 _height, XE::TextureFormat _format, XE::TextureFormat _depthFormat )
	{

	}

	XE::uint16 FrameBuffer::Destroy()
	{

	}

	void FrameBuffer::PreReset( bool _force /*= false */ )
	{

	}

	void FrameBuffer::PostReset()
	{

	}

	void FrameBuffer::Resolve()
	{

	}

	void FrameBuffer::Clear( const XE::ViewClearDesc & _clear, const float _palette[][4] )
	{

	}

	void FrameBuffer::Set()
	{

	}

	HRESULT FrameBuffer::Present( XE::uint32 _syncInterval )
	{

	}

	void TimerQuery::PostReset()
	{

	}

	void TimerQuery::PreReset()
	{

	}

	XE::uint32 TimerQuery::Begin( XE::uint32 _resultIdx )
	{

	}

	void TimerQuery::End( XE::uint32 _idx )
	{

	}

	bool TimerQuery::Update()
	{

	}

	void OcclusionQuery::PostReset()
	{

	}

	void OcclusionQuery::PreReset()
	{

	}

	void OcclusionQuery::Begin( XE::RenderFrame * _render, OcclusionQueryHandle _handle )
	{

	}

	void OcclusionQuery::End()
	{

	}

	void OcclusionQuery::Resolve( XE::RenderFrame * _render, bool _wait /*= false */ )
	{

	}

	void OcclusionQuery::Invalidate( OcclusionQueryHandle _handle )
	{

	}
}
END_XE_NAMESPACE



struct XE::RendererContextDirectX11::Private
{
	XE::LibraryHandle _DX11Dll;

	DXGI * _Dxgi = nullptr;
	D3D_FEATURE_LEVEL _FeatureLevel;
	ID3D11Device * _Device = nullptr;
	ID3D11DeviceContext * _DeviceCtx = nullptr;

	std::array<D3D11::IndexBuffer, GFX_MAX_INDEX_BUFFERS> _IndexBuffers;
	std::array<D3D11::VertexBuffer, GFX_MAX_VERTEX_BUFFERS> _VertexBuffers;
	std::array<D3D11::Shader, GFX_MAX_SHADERS> _Shaders;
	std::array<D3D11::Program, GFX_MAX_PROGRAMS> _Programs;
	std::array<D3D11::Texture, GFX_MAX_TEXTURES> _Textures;
	std::array<D3D11::FrameBuffer, GFX_MAX_FRAME_BUFFERS> _FrameBuffers;

	std::map<XE::uint64, ID3D11BlendState> _BlendStateCahce;
	std::map<XE::uint64, ID3D11DepthStencilState> _DepthStencilStateCache;
	std::map<XE::uint64, ID3D11InputLayout> _InputLayoutCache;
	std::map<XE::uint64, ID3D11RasterizerState> _RasterizerStateCache;
	std::map<XE::uint64, ID3D11SamplerState> _SamplerStateCache;
};

XE::RendererContextDirectX11::RendererContextDirectX11()
	:_p( new Private )
{

}

XE::RendererContextDirectX11::~RendererContextDirectX11()
{
	delete _p;
}

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
	XE::CapsInfo caps = GetCaps();
	const XE::InitDesc & init = GetInit();

	_p->_DX11Dll = XE::Library::Open( "d3d11.dll" );
	auto D3D11CreateDevice = XE::Library::SymbolT< PFN_D3D11_CREATE_DEVICE>( _p->_DX11Dll, "D3D11CreateDevice" );
	XE_ASSERT( D3D11CreateDevice != nullptr && "Init error: Function D3D11CreateDevice not found." );

	_p->_Dxgi = new DXGI;
	_p->_Dxgi->Init( caps );


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
		for( uint32_t ii = 0; ii < sizeof( featureLevel ) && FAILED( hr );)
		{
			hr = D3D11CreateDevice( _p->_Dxgi->_Adapter
									, _p->_Dxgi->_DriverType
									, NULL
									, flags
									, &featureLevel[ii]
									, sizeof( featureLevel ) - ii
									, D3D11_SDK_VERSION
									, &_p->_Device
									, &_p->_FeatureLevel
									, &_p->_DeviceCtx
			);

			if( FAILED( hr ) )
			{
				XE_LOG( LoggerLevel::Warning, "Direct3D11 device feature level %1.%2.", ( _p->_FeatureLevel >> 12 ) & 0xf, ( _p->_FeatureLevel >> 8 ) & 0xf );
			}

			++ii;
		}

		if( FAILED( hr ) && D3D_DRIVER_TYPE_WARP != _p->_Dxgi->_DriverType )
		{
			_p->_Dxgi->_DriverType = D3D_DRIVER_TYPE_WARP;
			continue;
		}

		break;
	}

	_p->_Dxgi->Update( _p->_Device );



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
		caps.Supported |= ( _p->_FeatureLevel >= D3D_FEATURE_LEVEL_9_2 ) ? XE::CapsFlag::OCCLUSIONQUERY : XE::CapsFlag::NONE;
		caps.Supported |= XE::CapsFlag::ALPHATOCOVERAGE;
		caps.Supported |= XE::CapsFlag::TEXTURE2DARRAY;
		caps.Supported |= XE::CapsFlag::TEXTURECUBEARRAY;
		caps.Supported |= ( _p->_FeatureLevel >= D3D_FEATURE_LEVEL_11_1 ) ? XE::CapsFlag::FRAMEBUFFERRW : XE::CapsFlag::NONE;

		if( _p->_FeatureLevel <= D3D_FEATURE_LEVEL_9_2 )
		{
			caps.Limits.MaxTextureSize = D3D_FL9_1_REQ_TEXTURE2D_U_OR_V_DIMENSION;
			caps.Limits.MaxFBAttachments = std::min< XE::uint32 >( D3D_FL9_1_SIMULTANEOUS_RENDER_TARGET_COUNT, GFX_MAX_ATTACHMENTS );
			caps.Limits.MaxVertexStreams = std::min< XE::uint32 >( 16, GFX_MAX_VERTEX_BUFFERS );
		}
		else if( _p->_FeatureLevel == D3D_FEATURE_LEVEL_9_3 )
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
			caps.Limits.MaxComputeBindings = std::min( 16, D3D_FEATURE_LEVEL_11_1 <= _p->_FeatureLevel ? D3D11_1_UAV_SLOT_COUNT : D3D11_PS_CS_UAV_REGISTER_COUNT );
		}

		if( _p->_FeatureLevel >= D3D_FEATURE_LEVEL_9_2 )
		{
			caps.Supported |= XE::CapsFlag::INDEX32;
		}

		if( _p->_FeatureLevel >= D3D_FEATURE_LEVEL_10_1 )
		{
			caps.Supported |= XE::CapsFlag::BLENDINDEPENDENT;
		}

		if( _p->_FeatureLevel == D3D_FEATURE_LEVEL_10_0 || _p->_FeatureLevel == D3D_FEATURE_LEVEL_10_1 )
		{
			struct D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS
			{
				BOOL ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x;
			};

			D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS data;
			HRESULT hr = _p->_Device->CheckFeatureSupport( D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS, &data, sizeof( data ) );
			if( SUCCEEDED( hr ) && data.ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x )
			{
				caps.Supported |= XE::CapsFlag::COMPUTE;
			}
		}
		else if( _p->_FeatureLevel >= D3D_FEATURE_LEVEL_11_0 )
		{
			caps.Supported |= XE::CapsFlag::COMPUTE;
		}

		if( _p->_FeatureLevel >= D3D_FEATURE_LEVEL_9_3 )
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
			HRESULT hr = _p->_Device->CheckFeatureSupport( D3D11_FEATURE( 11 ) /*D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT*/, &data, sizeof( data ) );
			if( SUCCEEDED( hr ) && data.SimpleInstancingSupported )
			{
				caps.Supported |= XE::CapsFlag::INSTANCING;
			}
		}

		if( _p->_FeatureLevel <= D3D_FEATURE_LEVEL_9_3 )
		{
			struct D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT
			{
				BOOL SupportsDepthAsTextureWithLessEqualComparisonFilter;
			};

			D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT data;
			HRESULT hr = _p->_Device->CheckFeatureSupport( D3D11_FEATURE( 9 ) /*D3D11_FEATURE_D3D9_SHADOW_SUPPORT*/, &data, sizeof( data ) );
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
				HRESULT hr = _p->_Device->CheckFeatureSupport( D3D11_FEATURE_FORMAT_SUPPORT, &data, sizeof( data ) );
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
					hr = _p->_Device->CheckFeatureSupport( D3D11_FEATURE_FORMAT_SUPPORT2, &data, sizeof( data ) );
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
				HRESULT hr = _p->_Device->CheckFeatureSupport( D3D11_FEATURE_FORMAT_SUPPORT, &data, sizeof( data ) );
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
	_p->_DeviceCtx->ClearState();

	_p->_BlendStateCahce.clear();
	_p->_DepthStencilStateCache.clear();
	_p->_InputLayoutCache.clear();
	_p->_RasterizerStateCache.clear();
	_p->_SamplerStateCache.clear();

	for( auto i : _p->_IndexBuffers )
	{
		i.Destroy();
	}
	for( auto i : _p->_VertexBuffers )
	{
		i.Destroy();
	}
	for( auto i : _p->_Shaders )
	{
		i.Destroy();
	}
	for( auto i : _p->_Programs )
	{
		i.Destroy();
	}
	for( auto i : _p->_Textures )
	{
		i.Destroy();
	}
	for( auto i : _p->_FrameBuffers )
	{
		i.Destroy();
	}

	DX_RELEASE( _p->_DeviceCtx );
	DX_RELEASE( _p->_Device );

	_p->_Dxgi->Shutdown();
	delete _p->_Dxgi;
	_p->_Dxgi = nullptr;

	XE::Library::Close( _p->_DX11Dll );
	_p->_DX11Dll = XE::LibraryHandle::Invalid;
}

void XE::RendererContextDirectX11::CreateProgram( XE::RenderFrame * frame )
{
	XE::ProgramHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	_p->_Programs[handle].Create( &_p->_Shaders[desc.VS], &_p->_Shaders[desc.FS] );
}

void XE::RendererContextDirectX11::CreateFrameBuffer( XE::RenderFrame * frame )
{
	XE::FrameBufferHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	if( desc.Window )
	{
		_p->_FrameBuffers[handle].Create( 0, desc.Window, desc.Width, desc.Height, desc.ColorFormat, desc.DepthFormat );
	}
	else
	{
		_p->_FrameBuffers[handle].Create( desc.AttachmentCount, desc.Attachments );
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

	_p->_Shaders[handle].Create( _p->_Device, desc.Type, view );
}

void XE::RendererContextDirectX11::CreateTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );
	const auto & desc = GetDesc( handle );

	_p->_Textures[handle].Create( view, desc.Flags, 0 );
}

void XE::RendererContextDirectX11::CreateIndexBuffer( XE::RenderFrame * frame )
{
	XE::IndexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );
	const auto & desc = GetDesc( handle );

	_p->_IndexBuffers[handle].Create( _p->_Device, view.size(), ( void * ) view.data(), desc.Flags );
}

void XE::RendererContextDirectX11::CreateVertexBuffer( XE::RenderFrame * frame )
{
	XE::VertexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView view;
	frame->PrevCmd.Read( view );
	const auto & desc = GetDesc( handle );

	_p->_VertexBuffers[handle].Create( _p->_Device, view.size(), ( void * ) view.data(), desc.Layout, desc.Flags );
}

void XE::RendererContextDirectX11::CreateDynamicIndexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicIndexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	_p->_IndexBuffers[handle].Create( _p->_Device, desc.Size, nullptr, desc.Flags );
}

void XE::RendererContextDirectX11::CreateDynamicVertexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicVertexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	const auto & desc = GetDesc( handle );

	_p->_VertexBuffers[handle].Create( _p->_Device, desc.Size, nullptr, desc.Layout, desc.Flags );
}

void XE::RendererContextDirectX11::ReadTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PrevCmd.Read( handle );
	std::uintptr_t data;
	frame->PrevCmd.Read( data );
	XE::uint8 mip;
	frame->PrevCmd.Read( mip );


	const D3D11::Texture & texture = _p->_Textures[handle];
	D3D11_MAPPED_SUBRESOURCE mapped;

	XE_ASSERT( SUCCEEDED( _p->_DeviceCtx->Map( texture._Ptr, mip, D3D11_MAP_READ, 0, &mapped ) ) );

	uint32_t srcWidth =  std::max< XE::uint32 >( 1, texture._Width >> mip );
	uint32_t srcHeight = std::max< XE::uint32 >( 1, texture._Height >> mip );
	uint8_t * src = ( uint8_t * ) mapped.pData;
	uint32_t srcPitch = mapped.RowPitch;

	const uint8_t bpp = s_imageBlockInfo[texture._TextureFormat].bitsPerPixel;
	uint8_t * dst = ( uint8_t * ) data;
	uint32_t dstPitch = srcWidth * bpp / 8;

	uint32_t pitch = std::min( srcPitch, dstPitch );

	for( uint32_t yy = 0, height = srcHeight; yy < height; ++yy )
	{
		std::memcpy( dst, src, pitch );

		src += srcPitch;
		dst += dstPitch;
	}

	_p->_DeviceCtx->Unmap( texture._Ptr, mip );
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
	_p->_Textures[handle].Update( desc.Side, desc.Mip, rect, desc.Z, desc.Depth, desc.Layer, view );
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

	_p->_IndexBuffers[handle].Update( _p->_DeviceCtx, start, std::min( desc.Size, view.size() ), ( void * ) view.data() );
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

	_p->_VertexBuffers[handle].Update( _p->_DeviceCtx, start, std::min( desc.Size, view.size() ), ( void * ) view.data() );
}

void XE::RendererContextDirectX11::RequestScreenShot( XE::RenderFrame * frame )
{
	XE::FrameBufferHandle handle;
	frame->PostCmd.Read( handle );
	std::string userdata;
	frame->PostCmd.Read( userdata );
	ScreenShotCallbackType callback;
	frame->PostCmd.Read( ( uintptr_t & ) callback );

	IDXGISwapChain * swapChain = _p->_FrameBuffers[handle]._SwapChain;

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
	HRESULT hr = _p->_Device->CreateTexture2D( &desc, NULL, &texture );
	if( SUCCEEDED( hr ) )
	{
		if( backBufferDesc.SampleDesc.Count == 1 )
		{
			_p->_DeviceCtx->CopyResource( texture, backBuffer );
		}
		else
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.CPUAccessFlags = 0;
			ID3D11Texture2D * resolve;
			hr = _p->_Device->CreateTexture2D( &desc, NULL, &resolve );
			if( SUCCEEDED( hr ) )
			{
				_p->_DeviceCtx->ResolveSubresource( resolve, 0, backBuffer, 0, desc.Format );
				_p->_DeviceCtx->CopyResource( texture, resolve );
				DX_RELEASE( resolve, 0 );
			}
		}

		D3D11_MAPPED_SUBRESOURCE mapped;
		XE_ASSERT( SUCCEEDED( _p->_DeviceCtx->Map( texture, 0, D3D11_MAP_READ, 0, &mapped ) ) );

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

		_p->_DeviceCtx->Unmap( texture, 0 );

		DX_RELEASE( texture );
	}

	DX_RELEASE( backBuffer );
}

void XE::RendererContextDirectX11::DestoryShader( XE::RenderFrame * frame )
{
	XE::ShaderHandle handle;
	frame->PostCmd.Read( handle );

	_p->_Shaders[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryProgram( XE::RenderFrame * frame )
{
	XE::ProgramHandle handle;
	frame->PostCmd.Read( handle );

	_p->_Programs[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PostCmd.Read( handle );

	_p->_Textures[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryFrameBuffer( XE::RenderFrame * frame )
{
	XE::FrameBufferHandle handle;
	frame->PostCmd.Read( handle );

	_p->_FrameBuffers[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryIndexBuffer( XE::RenderFrame * frame )
{
	XE::IndexBufferHandle handle;
	frame->PostCmd.Read( handle );

	_p->_IndexBuffers[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryVertexLayout( XE::RenderFrame * frame )
{
	( void ) ( frame );
}

void XE::RendererContextDirectX11::DestoryVertexBuffer( XE::RenderFrame * frame )
{
	XE::VertexBufferHandle handle;
	frame->PostCmd.Read( handle );

	_p->_VertexBuffers[handle].Destroy();
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

	_p->_IndexBuffers[handle].Destroy();
}

void XE::RendererContextDirectX11::DestoryDynamicVertexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicVertexBufferHandle handle;
	frame->PostCmd.Read( handle );

	_p->_VertexBuffers[handle].Destroy();
}

#endif
