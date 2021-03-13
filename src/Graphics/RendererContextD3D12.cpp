#include "RendererContextD3D12.h"

#if PLATFORM_OS & ( OS_WINDOWS | OS_XBOX )

#if PLATFORM_OS == OS_XBOX
#include <d3d12_x.h>
#else
#include <d3d12.h>
#include <D3DX12/d3dx12.h>
#endif

#include "DXGI.h"

#include "Utils/Logger.h"

namespace XE::D3D12
{
	enum class Rdt
	{
		SAMPLER,
		SRV,
		CBV,
		UAV,

		COUNT
	};

	typedef struct PIXEventsThreadInfo * ( * PFN_PIX_GET_THREAD_INFO )( );
	typedef uint64_t( * PFN_PIX_EVENTS_REPLACE_BLOCK )( bool _getEarliestTime );
	typedef HRESULT( * PFN_D3D12_GET_DEBUG_INTERFACE )( const IID &, void ** );
	typedef HRESULT( * PFN_D3D12_CREATE_DEVICE )( IUnknown *, D3D_FEATURE_LEVEL, const IID &, void ** );
	typedef HANDLE( * PFN_CREATE_EVENT_EX_A )( LPSECURITY_ATTRIBUTES _attrs, LPCSTR _name, DWORD _flags, DWORD _access );
	typedef HRESULT( * PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES )( uint32_t _numFeatures, const IID * _iids, void * _configurationStructs, uint32_t * _configurationStructSizes );
	typedef HRESULT( * PFN_D3D12_SERIALIZE_ROOT_SIGNATURE )( const D3D12_ROOT_SIGNATURE_DESC * pRootSignature, D3D_ROOT_SIGNATURE_VERSION Version, ID3DBlob ** ppBlob, ID3DBlob ** ppErrorBlob );

	XE::D3D12::PFN_CREATE_EVENT_EX_A					CreateEventExA;
	XE::D3D12::PFN_D3D12_CREATE_DEVICE					CreateDevice;
	XE::D3D12::PFN_PIX_GET_THREAD_INFO					PIXGetThreadInfo;
	XE::D3D12::PFN_D3D12_GET_DEBUG_INTERFACE			GetDebugInterface;
	XE::D3D12::PFN_PIX_EVENTS_REPLACE_BLOCK				PIXEventsReplaceBlock;
	XE::D3D12::PFN_D3D12_SERIALIZE_ROOT_SIGNATURE		SerializeRootSignature;
	XE::D3D12::PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES	EnableExperimentalFeatures;


	using DescriptorHeapHandle = XE::Handle< ID3D12DescriptorHeap >;

	struct HeapProperty
	{
		enum class Type
		{
			DEFAULT,
			TEXTURE,
			UPLOAD,
			READBACK,

			COUNT
		};

		D3D12_HEAP_PROPERTIES m_properties;
		D3D12_RESOURCE_STATES m_state;
	};

	struct PrimInfo
	{
		D3D_PRIMITIVE_TOPOLOGY m_topology;
		D3D12_PRIMITIVE_TOPOLOGY_TYPE m_topologyType;
		uint32_t m_min;
		uint32_t m_div;
		uint32_t m_sub;
	};

	struct TextureFormatInfo
	{
		DXGI_FORMAT m_fmt;
		DXGI_FORMAT m_fmtSrv;
		DXGI_FORMAT m_fmtDsv;
		DXGI_FORMAT m_fmtSrgb;
	};

	struct UavFormat
	{
		DXGI_FORMAT format[3];
		uint32_t    stride;
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

	constexpr GUID IID_ID3D12CommandAllocator = { 0x6102dee4, 0xaf59, 0x4b09, { 0xb9, 0x99, 0xb4, 0x4d, 0x73, 0xf0, 0x9b, 0x24 } };
	constexpr GUID IID_ID3D12CommandQueue = { 0x0ec870a6, 0x5d7e, 0x4c22, { 0x8c, 0xfc, 0x5b, 0xaa, 0xe0, 0x76, 0x16, 0xed } };
	constexpr GUID IID_ID3D12CommandSignature = { 0xc36a797c, 0xec80, 0x4f0a, { 0x89, 0x85, 0xa7, 0xb2, 0x47, 0x50, 0x82, 0xd1 } };
	constexpr GUID IID_ID3D12Debug = { 0x344488b7, 0x6846, 0x474b, { 0xb9, 0x89, 0xf0, 0x27, 0x44, 0x82, 0x45, 0xe0 } };
	constexpr GUID IID_ID3D12Debug1 = { 0xaffaa4ca, 0x63fe, 0x4d8e, { 0xb8, 0xad, 0x15, 0x90, 0x00, 0xaf, 0x43, 0x04 } };
	constexpr GUID IID_ID3D12DescriptorHeap = { 0x8efb471d, 0x616c, 0x4f49, { 0x90, 0xf7, 0x12, 0x7b, 0xb7, 0x63, 0xfa, 0x51 } };
	constexpr GUID IID_ID3D12Device = { 0x189819f1, 0x1db6, 0x4b57, { 0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7 } };
	constexpr GUID IID_ID3D12Device1 = { 0x77acce80, 0x638e, 0x4e65, { 0x88, 0x95, 0xc1, 0xf2, 0x33, 0x86, 0x86, 0x3e } };
	constexpr GUID IID_ID3D12Device2 = { 0x30baa41e, 0xb15b, 0x475c, { 0xa0, 0xbb, 0x1a, 0xf5, 0xc5, 0xb6, 0x43, 0x28 } };
	constexpr GUID IID_ID3D12Device3 = { 0x81dadc15, 0x2bad, 0x4392, { 0x93, 0xc5, 0x10, 0x13, 0x45, 0xc4, 0xaa, 0x98 } };
	constexpr GUID IID_ID3D12Device4 = { 0xe865df17, 0xa9ee, 0x46f9, { 0xa4, 0x63, 0x30, 0x98, 0x31, 0x5a, 0xa2, 0xe5 } };
	constexpr GUID IID_ID3D12Device5 = { 0x8b4f173b, 0x2fea, 0x4b80, { 0x8f, 0x58, 0x43, 0x07, 0x19, 0x1a, 0xb9, 0x5d } };
	constexpr GUID IID_ID3D12Fence = { 0x0a753dcf, 0xc4d8, 0x4b91, { 0xad, 0xf6, 0xbe, 0x5a, 0x60, 0xd9, 0x5a, 0x76 } };
	constexpr GUID IID_ID3D12GraphicsCommandList = { 0x5b160d0f, 0xac1b, 0x4185, { 0x8b, 0xa8, 0xb3, 0xae, 0x42, 0xa5, 0xa4, 0x55 } };
	constexpr GUID IID_ID3D12GraphicsCommandList1 = { 0x553103fb, 0x1fe7, 0x4557, { 0xbb, 0x38, 0x94, 0x6d, 0x7d, 0x0e, 0x7c, 0xa7 } };
	constexpr GUID IID_ID3D12GraphicsCommandList2 = { 0x38C3E585, 0xFF17, 0x412C, { 0x91, 0x50, 0x4F, 0xC6, 0xF9, 0xD7, 0x2A, 0x28 } };
	constexpr GUID IID_ID3D12GraphicsCommandList3 = { 0x6FDA83A7, 0xB84C, 0x4E38, { 0x9A, 0xC8, 0xC7, 0xBD, 0x22, 0x01, 0x6B, 0x3D } };
	constexpr GUID IID_ID3D12GraphicsCommandList4 = { 0x8754318e, 0xd3a9, 0x4541, { 0x98, 0xcf, 0x64, 0x5b, 0x50, 0xdc, 0x48, 0x74 } };
	constexpr GUID IID_ID3D12InfoQueue = { 0x0742a90b, 0xc387, 0x483f, { 0xb9, 0x46, 0x30, 0xa7, 0xe4, 0xe6, 0x14, 0x58 } };
	constexpr GUID IID_ID3D12PipelineState = { 0x765a30f3, 0xf624, 0x4c6f, { 0xa8, 0x28, 0xac, 0xe9, 0x48, 0x62, 0x24, 0x45 } };
	constexpr GUID IID_ID3D12Resource = { 0x696442be, 0xa72e, 0x4059, { 0xbc, 0x79, 0x5b, 0x5c, 0x98, 0x04, 0x0f, 0xad } };
	constexpr GUID IID_ID3D12RootSignature = { 0xc54a6b66, 0x72df, 0x4ee8, { 0x8b, 0xe5, 0xa9, 0x46, 0xa1, 0x42, 0x92, 0x14 } };
	constexpr GUID IID_ID3D12QueryHeap = { 0x0d9658ae, 0xed45, 0x469e, { 0xa6, 0x1d, 0x97, 0x0e, 0xc5, 0x83, 0xca, 0xb4 } };

	HeapProperty s_heapProperties[] =
	{
		{ { D3D12_HEAP_TYPE_DEFAULT,  D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 0, 0 }, D3D12_RESOURCE_STATE_COMMON       },
		{ { D3D12_HEAP_TYPE_DEFAULT,  D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 0, 0 }, D3D12_RESOURCE_STATE_COMMON       },
		{ { D3D12_HEAP_TYPE_UPLOAD,   D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 0, 0 }, D3D12_RESOURCE_STATE_GENERIC_READ },
		{ { D3D12_HEAP_TYPE_READBACK, D3D12_CPU_PAGE_PROPERTY_UNKNOWN, D3D12_MEMORY_POOL_UNKNOWN, 0, 0 }, D3D12_RESOURCE_STATE_COPY_DEST    },
	};

	const GUID s_d3dDeviceIIDs[] =
	{
		IID_ID3D12Device5,
		IID_ID3D12Device4,
		IID_ID3D12Device3,
		IID_ID3D12Device2,
		IID_ID3D12Device1,
	};

	const PrimInfo s_primInfo[] =
	{
		{ D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,  D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,  3, 3, 0 },
		{ D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,  3, 1, 2 },
		{ D3D_PRIMITIVE_TOPOLOGY_LINELIST,      D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,      2, 2, 0 },
		{ D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,     D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,      2, 1, 1 },
		{ D3D_PRIMITIVE_TOPOLOGY_POINTLIST,     D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,     1, 1, 0 },
		{ D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,     D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED, 0, 0, 0 },
	};

	const uint32_t s_checkMsaa[] =
	{
		0,
		2,
		4,
		8,
		16,
	};

	DXGI_SAMPLE_DESC s_msaa[] =
	{
		{  1, 0 },
		{  2, 0 },
		{  4, 0 },
		{  8, 0 },
		{ 16, 0 },
	};

	const D3D12_BLEND s_blendFactor[][2] =
	{
		{ D3D12_BLEND( 0 ),               D3D12_BLEND( 0 )               }, // ignored
		{ D3D12_BLEND_ZERO,             D3D12_BLEND_ZERO             }, // ZERO
		{ D3D12_BLEND_ONE,              D3D12_BLEND_ONE              }, // ONE
		{ D3D12_BLEND_SRC_COLOR,        D3D12_BLEND_SRC_ALPHA        }, // SRC_COLOR
		{ D3D12_BLEND_INV_SRC_COLOR,    D3D12_BLEND_INV_SRC_ALPHA    }, // INV_SRC_COLOR
		{ D3D12_BLEND_SRC_ALPHA,        D3D12_BLEND_SRC_ALPHA        }, // SRC_ALPHA
		{ D3D12_BLEND_INV_SRC_ALPHA,    D3D12_BLEND_INV_SRC_ALPHA    }, // INV_SRC_ALPHA
		{ D3D12_BLEND_DEST_ALPHA,       D3D12_BLEND_DEST_ALPHA       }, // DST_ALPHA
		{ D3D12_BLEND_INV_DEST_ALPHA,   D3D12_BLEND_INV_DEST_ALPHA   }, // INV_DST_ALPHA
		{ D3D12_BLEND_DEST_COLOR,       D3D12_BLEND_DEST_ALPHA       }, // DST_COLOR
		{ D3D12_BLEND_INV_DEST_COLOR,   D3D12_BLEND_INV_DEST_ALPHA   }, // INV_DST_COLOR
		{ D3D12_BLEND_SRC_ALPHA_SAT,    D3D12_BLEND_ONE              }, // SRC_ALPHA_SAT
		{ D3D12_BLEND_BLEND_FACTOR,     D3D12_BLEND_BLEND_FACTOR     }, // FACTOR
		{ D3D12_BLEND_INV_BLEND_FACTOR, D3D12_BLEND_INV_BLEND_FACTOR }, // INV_FACTOR
	};

	const D3D12_BLEND_OP s_blendEquation[] =
	{
		D3D12_BLEND_OP_ADD,
		D3D12_BLEND_OP_SUBTRACT,
		D3D12_BLEND_OP_REV_SUBTRACT,
		D3D12_BLEND_OP_MIN,
		D3D12_BLEND_OP_MAX,
	};

	const D3D12_COMPARISON_FUNC s_cmpFunc[] =
	{
		D3D12_COMPARISON_FUNC( 0 ), // ignored
		D3D12_COMPARISON_FUNC_LESS,
		D3D12_COMPARISON_FUNC_LESS_EQUAL,
		D3D12_COMPARISON_FUNC_EQUAL,
		D3D12_COMPARISON_FUNC_GREATER_EQUAL,
		D3D12_COMPARISON_FUNC_GREATER,
		D3D12_COMPARISON_FUNC_NOT_EQUAL,
		D3D12_COMPARISON_FUNC_NEVER,
		D3D12_COMPARISON_FUNC_ALWAYS,
	};

	const D3D12_STENCIL_OP s_stencilOp[] =
	{
		D3D12_STENCIL_OP_ZERO,
		D3D12_STENCIL_OP_KEEP,
		D3D12_STENCIL_OP_REPLACE,
		D3D12_STENCIL_OP_INCR,
		D3D12_STENCIL_OP_INCR_SAT,
		D3D12_STENCIL_OP_DECR,
		D3D12_STENCIL_OP_DECR_SAT,
		D3D12_STENCIL_OP_INVERT,
	};

	const D3D12_CULL_MODE s_cullMode[] =
	{
		D3D12_CULL_MODE_NONE,
		D3D12_CULL_MODE_FRONT,
		D3D12_CULL_MODE_BACK,
	};

	const D3D12_TEXTURE_ADDRESS_MODE s_textureAddress[] =
	{
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_MIRROR,
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
		D3D12_TEXTURE_ADDRESS_MODE_BORDER,
	};

	const uint8_t s_textureFilter[3][3] =
	{
		{
			0x10, // min linear
			0x00, // min point
			0x55, // anisotropic
		},
		{
			0x04, // mag linear
			0x00, // mag point
			0x55, // anisotropic
		},
		{
			0x01, // mip linear
			0x00, // mip point
			0x55, // anisotropic
		},
	};

	const TextureFormatInfo s_textureFormat[] =
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
		{ DXGI_FORMAT_R16_UNORM,          DXGI_FORMAT_R16_UNORM,             DXGI_FORMAT_UNKNOWN,           DXGI_FORMAT_UNKNOWN              }, // R16U
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

	const D3D12_INPUT_ELEMENT_DESC s_attrib[] =
	{
		{ "POSITION",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL",       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TANGENT",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BITANGENT",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",        0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",        1, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",        2, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",        3, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT,   0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BLENDWEIGHT",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     1, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     2, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     3, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     4, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     5, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     6, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",     7, DXGI_FORMAT_R32G32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	const DXGI_FORMAT s_attribType[][4][2] =
	{
		{ // Uint8
			{ DXGI_FORMAT_R8_UINT,            DXGI_FORMAT_R8_UNORM           },
			{ DXGI_FORMAT_R8G8_UINT,          DXGI_FORMAT_R8G8_UNORM         },
			{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UNORM     },
			{ DXGI_FORMAT_R8G8B8A8_UINT,      DXGI_FORMAT_R8G8B8A8_UNORM     },
		},
		{ // Uint10
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
			{ DXGI_FORMAT_R10G10B10A2_UINT,   DXGI_FORMAT_R10G10B10A2_UNORM  },
		},
		{ // Int16
			{ DXGI_FORMAT_R16_SINT,           DXGI_FORMAT_R16_SNORM          },
			{ DXGI_FORMAT_R16G16_SINT,        DXGI_FORMAT_R16G16_SNORM       },
			{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SNORM },
			{ DXGI_FORMAT_R16G16B16A16_SINT,  DXGI_FORMAT_R16G16B16A16_SNORM },
		},
		{ // Half
			{ DXGI_FORMAT_R16_FLOAT,          DXGI_FORMAT_R16_FLOAT          },
			{ DXGI_FORMAT_R16G16_FLOAT,       DXGI_FORMAT_R16G16_FLOAT       },
			{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT },
			{ DXGI_FORMAT_R16G16B16A16_FLOAT, DXGI_FORMAT_R16G16B16A16_FLOAT },
		},
		{ // Float
			{ DXGI_FORMAT_R32_FLOAT,          DXGI_FORMAT_R32_FLOAT          },
			{ DXGI_FORMAT_R32G32_FLOAT,       DXGI_FORMAT_R32G32_FLOAT       },
			{ DXGI_FORMAT_R32G32B32_FLOAT,    DXGI_FORMAT_R32G32B32_FLOAT    },
			{ DXGI_FORMAT_R32G32B32A32_FLOAT, DXGI_FORMAT_R32G32B32A32_FLOAT },
		},
	};

	const UavFormat s_uavFormat[] =
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

	const ImageBlockInfo s_imageBlockInfo[] =
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
		{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // BC1
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // BC2
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // BC3
		{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // BC4
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // BC5
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // BC6H
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // BC7
		{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ETC1
		{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ETC2
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ETC2A
		{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ETC2A1
		{   2,  8, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // PTC12
		{   4,  4, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // PTC14
		{   2,  8, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // PTC12A
		{   4,  4, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // PTC14A
		{   2,  8, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // PTC22
		{   4,  4, 4,  8, 2, 2,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // PTC24
		{   4,  4, 4,  8, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ATC
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ATCE
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ATCI
		{   8,  4, 4, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ASTC4x4
		{   6,  5, 5, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ASTC5x5
		{   4,  6, 6, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ASTC6x6
		{   4,  8, 5, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ASTC8x5
		{   3,  8, 6, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ASTC8x6
		{   3, 10, 5, 16, 1, 1,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // ASTC10x5
		{   0,  0, 0,  0, 0, 0,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::COUNT ) }, // Unknown
		{   1,  8, 1,  1, 1, 1,  0, 0,  1,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // R1
		{   8,  1, 1,  1, 1, 1,  0, 0,  0,  0,  0,  8, uint8_t( XE::EncodingType::UNORM ) }, // A8
		{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // R8
		{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( XE::EncodingType::INT ) }, // R8I
		{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( XE::EncodingType::UINT ) }, // R8U
		{   8,  1, 1,  1, 1, 1,  0, 0,  8,  0,  0,  0, uint8_t( XE::EncodingType::SNORM ) }, // R8S
		{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // R16
		{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( XE::EncodingType::INT ) }, // R16I
		{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( XE::EncodingType::UINT ) }, // R16U
		{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // R16F
		{  16,  1, 1,  2, 1, 1,  0, 0, 16,  0,  0,  0, uint8_t( XE::EncodingType::SNORM ) }, // R16S
		{  32,  1, 1,  4, 1, 1,  0, 0, 32,  0,  0,  0, uint8_t( XE::EncodingType::INT ) }, // R32I
		{  32,  1, 1,  4, 1, 1,  0, 0, 32,  0,  0,  0, uint8_t( XE::EncodingType::UINT ) }, // R32U
		{  32,  1, 1,  4, 1, 1,  0, 0, 32,  0,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // R32F
		{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // RG8
		{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( XE::EncodingType::INT ) }, // RG8I
		{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( XE::EncodingType::UINT ) }, // RG8U
		{  16,  1, 1,  2, 1, 1,  0, 0,  8,  8,  0,  0, uint8_t( XE::EncodingType::SNORM ) }, // RG8S
		{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // RG16
		{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( XE::EncodingType::INT ) }, // RG16I
		{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( XE::EncodingType::UINT ) }, // RG16U
		{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // RG16F
		{  32,  1, 1,  4, 1, 1,  0, 0, 16, 16,  0,  0, uint8_t( XE::EncodingType::SNORM ) }, // RG16S
		{  64,  1, 1,  8, 1, 1,  0, 0, 32, 32,  0,  0, uint8_t( XE::EncodingType::INT ) }, // RG32I
		{  64,  1, 1,  8, 1, 1,  0, 0, 32, 32,  0,  0, uint8_t( XE::EncodingType::UINT ) }, // RG32U
		{  64,  1, 1,  8, 1, 1,  0, 0, 32, 32,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // RG32F
		{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( XE::EncodingType::UNORM ) }, // RGB8
		{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( XE::EncodingType::INT ) }, // RGB8I
		{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( XE::EncodingType::UINT ) }, // RGB8U
		{  24,  1, 1,  3, 1, 1,  0, 0,  8,  8,  8,  0, uint8_t( XE::EncodingType::SNORM ) }, // RGB8S
		{  32,  1, 1,  4, 1, 1,  0, 0,  9,  9,  9,  5, uint8_t( XE::EncodingType::FLOAT ) }, // RGB9E5F
		{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( XE::EncodingType::UNORM ) }, // BGRA8
		{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( XE::EncodingType::UNORM ) }, // RGBA8
		{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( XE::EncodingType::INT ) }, // RGBA8I
		{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( XE::EncodingType::UINT ) }, // RGBA8U
		{  32,  1, 1,  4, 1, 1,  0, 0,  8,  8,  8,  8, uint8_t( XE::EncodingType::SNORM ) }, // RGBA8S
		{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( XE::EncodingType::UNORM ) }, // RGBA16
		{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( XE::EncodingType::INT ) }, // RGBA16I
		{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( XE::EncodingType::UINT ) }, // RGBA16U
		{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( XE::EncodingType::FLOAT ) }, // RGBA16F
		{  64,  1, 1,  8, 1, 1,  0, 0, 16, 16, 16, 16, uint8_t( XE::EncodingType::SNORM ) }, // RGBA16S
		{ 128,  1, 1, 16, 1, 1,  0, 0, 32, 32, 32, 32, uint8_t( XE::EncodingType::INT ) }, // RGBA32I
		{ 128,  1, 1, 16, 1, 1,  0, 0, 32, 32, 32, 32, uint8_t( XE::EncodingType::UINT ) }, // RGBA32U
		{ 128,  1, 1, 16, 1, 1,  0, 0, 32, 32, 32, 32, uint8_t( XE::EncodingType::FLOAT ) }, // RGBA32F
		{  16,  1, 1,  2, 1, 1,  0, 0,  5,  6,  5,  0, uint8_t( XE::EncodingType::UNORM ) }, // R5G6B5
		{  16,  1, 1,  2, 1, 1,  0, 0,  4,  4,  4,  4, uint8_t( XE::EncodingType::UNORM ) }, // RGBA4
		{  16,  1, 1,  2, 1, 1,  0, 0,  5,  5,  5,  1, uint8_t( XE::EncodingType::UNORM ) }, // RGB5A1
		{  32,  1, 1,  4, 1, 1,  0, 0, 10, 10, 10,  2, uint8_t( XE::EncodingType::UNORM ) }, // RGB10A2
		{  32,  1, 1,  4, 1, 1,  0, 0, 11, 11, 10,  0, uint8_t( XE::EncodingType::UNORM ) }, // RG11B10F
		{   0,  0, 0,  0, 0, 0,  0, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::COUNT ) }, // UnknownDepth
		{  16,  1, 1,  2, 1, 1, 16, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // D16
		{  24,  1, 1,  3, 1, 1, 24, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // D24
		{  32,  1, 1,  4, 1, 1, 24, 8,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // D24S8
		{  32,  1, 1,  4, 1, 1, 32, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // D32
		{  16,  1, 1,  2, 1, 1, 16, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // D16F
		{  24,  1, 1,  3, 1, 1, 24, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // D24F
		{  32,  1, 1,  4, 1, 1, 32, 0,  0,  0,  0,  0, uint8_t( XE::EncodingType::FLOAT ) }, // D32F
		{   8,  1, 1,  1, 1, 1,  0, 8,  0,  0,  0,  0, uint8_t( XE::EncodingType::UNORM ) }, // D0S8
	};

	D3D12_HEAP_PROPERTIES ID3D12DeviceGetCustomHeapProperties( ID3D12Device * device, UINT nodeMask, D3D12_HEAP_TYPE heapType )
	{
		union
		{
			D3D12_HEAP_PROPERTIES( STDMETHODCALLTYPE ID3D12Device:: * w )( UINT, D3D12_HEAP_TYPE );
			void ( STDMETHODCALLTYPE ID3D12Device:: * f )( D3D12_HEAP_PROPERTIES *, UINT, D3D12_HEAP_TYPE );
		} conversion = { &ID3D12Device::GetCustomHeapProperties };
		D3D12_HEAP_PROPERTIES ret;
		( device->*conversion.f )( &ret, nodeMask, heapType );
		return ret;
	}

	void initHeapProperties( ID3D12Device * _device, D3D12_HEAP_PROPERTIES & _properties )
	{
		if( D3D12_HEAP_TYPE_CUSTOM != _properties.Type )
		{
			_properties = ID3D12DeviceGetCustomHeapProperties( _device, 1, _properties.Type );
		}
	}

	void initHeapProperties( ID3D12Device * _device )
	{
		initHeapProperties( _device, s_heapProperties[( XE::uint64 )HeapProperty::Type::DEFAULT].m_properties );
		initHeapProperties( _device, s_heapProperties[( XE::uint64 )HeapProperty::Type::TEXTURE].m_properties );
		initHeapProperties( _device, s_heapProperties[( XE::uint64 )HeapProperty::Type::UPLOAD].m_properties );
		initHeapProperties( _device, s_heapProperties[( XE::uint64 )HeapProperty::Type::READBACK].m_properties );
	}

	ID3D12Resource * createCommittedResource( ID3D12Device * _device, HeapProperty::Type _heapProperty, const D3D12_RESOURCE_DESC * _resourceDesc, const D3D12_CLEAR_VALUE * _clearValue, bool _memSet = false )
	{
		const HeapProperty & heapProperty = s_heapProperties[( XE::uint64 )_heapProperty];
		ID3D12Resource * resource;
		DX_CHECK( _device->CreateCommittedResource( &heapProperty.m_properties
													, D3D12_HEAP_FLAG_NONE
													, _resourceDesc
													, heapProperty.m_state
													, _clearValue
													, IID_ID3D12Resource
													, ( void ** )&resource
		) );

	#if PLATFORM_OS == OS_XBOX
		if( _memSet )
		{
			void * ptr;
			DX_CHECK( resource->Map( 0, NULL, &ptr ) );
			D3D12_RESOURCE_ALLOCATION_INFO rai = _device->GetResourceAllocationInfo( 1, 1, _resourceDesc );
			std::memset( ptr, 0, size_t( rai.SizeInBytes ) );
			resource->Unmap( 0, NULL );
		}
	#endif

		return resource;
	}

	ID3D12Resource * createCommittedResource( ID3D12Device * _device, HeapProperty::Type _heapProperty, uint64_t _size, D3D12_RESOURCE_FLAGS _flags = D3D12_RESOURCE_FLAG_NONE )
	{
		D3D12_RESOURCE_DESC resourceDesc = {};
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
		resourceDesc.Alignment = 0;
		resourceDesc.Width = _size;
		resourceDesc.Height = 1;
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = DXGI_FORMAT_UNKNOWN;
		resourceDesc.SampleDesc.Count = 1;
		resourceDesc.SampleDesc.Quality = 0;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
		resourceDesc.Flags = _flags;

		return createCommittedResource( _device, _heapProperty, &resourceDesc, NULL );
	}

	bool isLost( HRESULT _hr )
	{
		return false
			|| _hr == DXGI_ERROR_DEVICE_REMOVED
			|| _hr == DXGI_ERROR_DEVICE_HUNG
			|| _hr == DXGI_ERROR_DEVICE_RESET
			|| _hr == DXGI_ERROR_DRIVER_INTERNAL_ERROR
			|| _hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE
			;
	}

	const char * getLostReason( HRESULT _hr )
	{
		switch( _hr )
		{
		case DXGI_ERROR_DEVICE_REMOVED:
			return "DXGI_ERROR_DEVICE_REMOVED";
		case DXGI_ERROR_DEVICE_HUNG:
			return "DXGI_ERROR_DEVICE_HUNG";
		case DXGI_ERROR_DEVICE_RESET:
			return "DXGI_ERROR_DEVICE_RESET";
		case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
			return "DXGI_ERROR_DRIVER_INTERNAL_ERROR";
		case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:
			return "DXGI_ERROR_NOT_CURRENTLY_AVAILABLE";
		case S_OK:
			return "S_OK";
		default:
			break;
		}

		return "Unknown HRESULT";
	}

	D3D12_CPU_DESCRIPTOR_HANDLE getCPUHandleHeapStart( ID3D12DescriptorHeap * _heap )
	{
	#if COMPILER == COMPILER_MSVC
		return _heap->GetCPUDescriptorHandleForHeapStart();
	#else
		D3D12_CPU_DESCRIPTOR_HANDLE handle;
		union
		{
			D3D12_CPU_DESCRIPTOR_HANDLE( WINAPI ID3D12DescriptorHeap:: * w )( );
			void ( WINAPI ID3D12DescriptorHeap:: * f )( D3D12_CPU_DESCRIPTOR_HANDLE * );
		} conversion = { &ID3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart };
		( _heap->*conversion.f )( &handle );
		return handle;
	#endif // BX_COMPILER_MSVC
	}

	D3D12_GPU_DESCRIPTOR_HANDLE getGPUHandleHeapStart( ID3D12DescriptorHeap * _heap )
	{
	#if COMPILER == COMPILER_MSVC
		return _heap->GetGPUDescriptorHandleForHeapStart();
	#else
		D3D12_GPU_DESCRIPTOR_HANDLE handle;
		union
		{
			D3D12_GPU_DESCRIPTOR_HANDLE( WINAPI ID3D12DescriptorHeap:: * w )( );
			void ( WINAPI ID3D12DescriptorHeap:: * f )( D3D12_GPU_DESCRIPTOR_HANDLE * );
		} conversion = { &ID3D12DescriptorHeap::GetGPUDescriptorHandleForHeapStart };
		( _heap->*conversion.f )( &handle );
		return handle;
	#endif
	}

	D3D12_RESOURCE_DESC getResourceDesc( ID3D12Resource * _resource )
	{
	#if COMPILER == COMPILER_MSVC
		return _resource->GetDesc();
	#else
		D3D12_RESOURCE_DESC desc;
		union
		{
			D3D12_RESOURCE_DESC( STDMETHODCALLTYPE ID3D12Resource:: * w )( );
			void ( STDMETHODCALLTYPE ID3D12Resource:: * f )( D3D12_RESOURCE_DESC * );
		} conversion = { &ID3D12Resource::GetDesc };
		( _resource->*conversion.f )( &desc );
		return desc;
	#endif
	}

	D3D12_INPUT_ELEMENT_DESC * fillVertexLayout( uint8_t _stream, D3D12_INPUT_ELEMENT_DESC * _out, const VertexLayoutDesc & _layout )
	{
		D3D12_INPUT_ELEMENT_DESC * elem = _out;

		// TODO: 
// 		for( uint32_t attr = 0; attr < ( XE::uint64 )AttributeName::COUNT; ++attr )
// 		{
// 			if( UINT16_MAX != _layout.Attr[attr] )
// 			{
// 				std::memcpy( elem, &s_attrib[attr], sizeof( D3D12_INPUT_ELEMENT_DESC ) );
// 
// 				elem->InputSlot = _stream;
// 
// 				if( 0 == _layout.Attr[attr] )
// 				{
// 					elem->AlignedByteOffset = 0;
// 				}
// 				else
// 				{
// 					uint8_t num;
// 					AttribType::Enum type;
// 					bool normalized;
// 					bool asInt;
// 					_layout.decode( Attrib::Enum( attr ), num, type, normalized, asInt );
// 					elem->Format = s_attribType[type][num - 1][normalized];
// 					elem->AlignedByteOffset = _layout.m_offset[attr];
// 				}
// 
// 				++elem;
// 			}
// 		}

		return elem;
	}

	void setResourceBarrier( ID3D12GraphicsCommandList * _commandList, const ID3D12Resource * _resource, D3D12_RESOURCE_STATES _stateBefore, D3D12_RESOURCE_STATES _stateAfter )
	{
		D3D12_RESOURCE_BARRIER barrier;
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = const_cast< ID3D12Resource * >( _resource );
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		barrier.Transition.StateBefore = _stateBefore;
		barrier.Transition.StateAfter = _stateAfter;
		_commandList->ResourceBarrier( 1, &barrier );
	}

	bool needBorderColor( XE::SamplerFlags _flags )
	{
		return ( _flags & XE::SamplerFlag::UBORDER ) == XE::SamplerFlag::UBORDER
			|| ( _flags & XE::SamplerFlag::VBORDER ) == XE::SamplerFlag::VBORDER
			|| ( _flags & XE::SamplerFlag::WBORDER ) == XE::SamplerFlag::WBORDER;
	}


	class RingBufferControl
	{
	public:
		RingBufferControl( uint32_t _size );

		~RingBufferControl();

		uint32_t available() const;

		uint32_t consume( uint32_t _size );

		uint32_t reserve( uint32_t _size, bool _mustSucceed = false );

		uint32_t commit( uint32_t _size );

		uint32_t distance( uint32_t _from, uint32_t _to ) const;

		void reset();

		uint32_t sels( uint32_t test, uint32_t _a, uint32_t _b ) const;
		
		const uint32_t m_size;
		uint32_t m_current;
		uint32_t m_write;
		uint32_t m_read;
	};

	class DescriptorAllocator
	{
	public:
		void create( D3D12_DESCRIPTOR_HEAP_TYPE _type, XE::uint16 _maxDescriptors, XE::uint16 _numDescriptorsPerBlock = 1 );

		void destroy();

		DescriptorHeapHandle alloc( ID3D12Resource * _ptr, const D3D12_SHADER_RESOURCE_VIEW_DESC * _desc );

		DescriptorHeapHandle alloc( const XE::SamplerFlags * _flags, XE::uint32 _num, const float _palette[][4] );

		void free( DescriptorHeapHandle _handle );

		void reset();

		D3D12_GPU_DESCRIPTOR_HANDLE get( DescriptorHeapHandle _handle );

		ID3D12DescriptorHeap * getHeap();

	private:
		ID3D12DescriptorHeap * m_heap;
		D3D12_CPU_DESCRIPTOR_HANDLE m_cpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE m_gpuHandle;
		XE::uint32 m_incrementSize;
		XE::uint16 m_numDescriptorsPerBlock;
		XE::QueueHandleAllocator< DescriptorHeapHandle > m_handleAlloc;
	};

	class Buffer
	{
	public:
		void create( XE::uint32 _size, void * _data, XE::BufferFlags _flags, bool _vertex, XE::uint32 _stride = 0 );

		void update( ID3D12GraphicsCommandList * _commandList, XE::uint32 _offset, XE::uint32 _size, void * _data, bool _discard = false );

		void destroy();

		D3D12_RESOURCE_STATES setState( ID3D12GraphicsCommandList * _commandList, D3D12_RESOURCE_STATES _state );

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource * m_ptr = nullptr;
		D3D12_GPU_VIRTUAL_ADDRESS m_gpuVA;
		D3D12_RESOURCE_STATES m_state = D3D12_RESOURCE_STATE_COMMON;
		XE::uint32 m_size = 0;
		XE::BufferFlags m_flags = XE::BufferFlag::NONE;
		bool m_dynamic = false;
	};

	class VertexBuffer : public Buffer
	{
	public:
		void create( XE::uint32 _size, void * _data, XE::VertexLayoutHandle _layoutHandle, XE::BufferFlags _flags );

		XE::VertexLayoutHandle m_layoutHandle;
	};

	class Shader
	{
	public:
		void create( XE::MemoryView _mem );

		void destroy();

		XE::Buffer m_code;

		// 		UniformBuffer * m_constantBuffer;
		// 		PredefinedUniform m_predefined[PredefinedUniform::Count];
		// 		XE::uint16 m_attrMask[AttributeName::COUNT];

		XE::uint32 m_hash;
		XE::uint16 m_numUniforms;
		XE::uint16 m_size;
		XE::uint8 m_numPredefined;
	};

	class Program
	{
	public:
		void create( const D3D12::Shader * _vsh, const D3D12::Shader * _fsh );

		void destroy();

		const D3D12::Shader * m_vsh;
		const D3D12::Shader * m_fsh;

		// 		PredefinedUniform m_predefined[PredefinedUniform::Count * 2];
		// 		XE::uint8 m_numPredefined;
	};

	class Texture
	{
	public:
		void * create( const XE::MemoryView _mem, XE::uint64 _flags, XE::uint8 _skip );

		void destroy();

		void overrideInternal( uintptr_t _ptr );

		void update( ID3D12GraphicsCommandList * _commandList, XE::uint8 _side, XE::uint8 _mip, const XE::Recti & _rect, XE::uint16 _z, XE::uint16 _depth, XE::uint16 _pitch, const XE::MemoryView _mem );

		void resolve( ID3D12GraphicsCommandList * _commandList, XE::uint8 _resolve );

		D3D12_RESOURCE_STATES setState( ID3D12GraphicsCommandList * _commandList, D3D12_RESOURCE_STATES _state );

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource * m_ptr;
		ID3D12Resource * m_singleMsaa;
		void * m_directAccessPtr;
		D3D12_RESOURCE_STATES m_state;
		XE::SamplerFlags m_flags;
		XE::uint32 m_width;
		XE::uint32 m_height;
		XE::uint32 m_depth;
		XE::uint32 m_numLayers;
		XE::uint16 m_samplerIdx;
		XE::uint8 m_type;
		XE::uint8 m_requestedFormat;
		XE::uint8 m_textureFormat;
		XE::uint8 m_numMips;
	};

	class FrameBuffer
	{
	public:
		void create( XE::uint8 _num, const Attachment * _attachment );

		void create( XE::uint16 _denseIdx, void * _nwh, XE::uint32 _width, XE::uint32 _height, XE::TextureFormat _format, XE::TextureFormat _depthFormat );

		XE::uint16 destroy();

		HRESULT present( XE::uint32 _syncInterval, XE::uint32 _flags );

		void preReset();

		void postReset();

		void resolve();

		void clear( ID3D12GraphicsCommandList * _commandList, const XE::ClearDesc & _clear, const float _palette[][4], const D3D12_RECT * _rect = NULL, XE::uint32 _num = 0 );

		D3D12_RESOURCE_STATES setState( ID3D12GraphicsCommandList * _commandList, XE::uint8 _idx, D3D12_RESOURCE_STATES _state );

		TextureHandle m_texture[GFX_MAX_ATTACHMENTS];
		TextureHandle m_depth;
		DXGI::SwapChainI * m_swapChain;
		void * m_nwh;
		XE::uint32 m_width;
		XE::uint32 m_height;
		XE::uint16 m_denseIdx;
		XE::uint8 m_num;
		XE::uint8 m_numTh;
		Attachment m_attachment[GFX_MAX_ATTACHMENTS];
		D3D12_RESOURCE_STATES m_state;
		bool m_needPresent;
	};

	class CommandQueue
	{
	public:
		CommandQueue()
			:m_control( 256 )
		{
		}

	public:
		void init( ID3D12Device * _device );

		void shutdown();

		ID3D12GraphicsCommandList * alloc();

		XE::uint64 kick();

		void finish( XE::uint64 _waitFence = UINT64_MAX, bool _finishAll = false );

		bool tryFinish( XE::uint64 _waitFence );

		void release( ID3D12Resource * _ptr );

		bool consume( XE::uint32 _ms = INFINITE );

		struct CommandList
		{
			ID3D12GraphicsCommandList * m_commandList;
			ID3D12CommandAllocator * m_commandAllocator;
			HANDLE m_event;
		};

		ID3D12CommandQueue * m_commandQueue = nullptr;
		XE::uint64 m_currentFence = 0;
		XE::uint64 m_completedFence = 0;
		ID3D12Fence * m_fence = nullptr;
		CommandList m_commandList[256];
		XE::Array<ID3D12Resource *> m_release[256];
		RingBufferControl m_control;
	};

	class TimerQuery
	{
	public:
		TimerQuery()
			:m_control( GFX_MAX_VIEW * 4 )
		{
		}

	public:
		void init();

		void shutdown();

		XE::uint32 begin( XE::uint32 _resultIdx );

		void end( XE::uint32 _idx );

		bool update();

		struct Query
		{
			XE::uint32 m_resultIdx;
			bool     m_ready;
			XE::uint64 m_fence;
		};

		struct Result
		{
			void reset()
			{
				m_begin = 0;
				m_end = 0;
				m_pending = 0;
			}

			XE::uint64 m_begin;
			XE::uint64 m_end;
			XE::uint32 m_pending;
		};

		XE::uint64 m_frequency;

		Result m_result[GFX_MAX_VIEW + 1];
		Query m_query[GFX_MAX_VIEW * 4];

		ID3D12Resource * m_readback;
		ID3D12QueryHeap * m_queryHeap;
		XE::uint64 * m_queryResult;
		RingBufferControl m_control;
	};

	class OcclusionQuery
	{
	public:
		OcclusionQuery()
			:m_control( GFX_MAX_OCCLUSION )
		{
		}

	public:
		void init();

		void shutdown();

		void begin( ID3D12GraphicsCommandList * _commandList, XE::RenderFrame * _render, OcclusionQueryHandle _handle );

		void end( ID3D12GraphicsCommandList * _commandList );

		void invalidate( OcclusionQueryHandle _handle );

		ID3D12Resource * m_readback;
		ID3D12QueryHeap * m_queryHeap;
		OcclusionQueryHandle m_handle[GFX_MAX_OCCLUSION];
		XE::uint64 * m_result;
		RingBufferControl m_control;
	};

	class ScratchBuffer
	{
	public:
		void create( XE::uint32 _size, XE::uint32 _maxDescriptors );

		void destroy();

		void reset( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle );

		void  allocEmpty( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle );

		void * allocCbv( D3D12_GPU_VIRTUAL_ADDRESS & _gpuAddress, XE::uint32 _size );

		void  allocSrv( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, Texture & _texture, XE::uint8 _mip = 0 );

		void  allocSrv( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, Buffer & _buffer );

		void  allocUav( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, Texture & _texture, XE::uint8 _mip = 0 );

		void  allocUav( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, Buffer & _buffer );

		ID3D12DescriptorHeap * getHeap();

	private:
		ID3D12DescriptorHeap * m_heap;
		ID3D12Resource * m_upload;
		D3D12_GPU_VIRTUAL_ADDRESS m_gpuVA;
		D3D12_CPU_DESCRIPTOR_HANDLE m_cpuHandle;
		D3D12_GPU_DESCRIPTOR_HANDLE m_gpuHandle;
		XE::uint32 m_incrementSize;
		XE::uint8 * m_data;
		XE::uint32 m_size;
		XE::uint32 m_pos;
	};

	class Bind
	{
	public:
		D3D12_GPU_DESCRIPTOR_HANDLE m_srvHandle;
		uint16_t m_samplerStateIdx;
	};

	class VertexLayout
	{
	public:
	};

	class RenderContext
	{
	public:
		D3D12_CPU_DESCRIPTOR_HANDLE getRtv( FrameBufferHandle _fbh );

		D3D12_CPU_DESCRIPTOR_HANDLE getRtv( FrameBufferHandle _fbh, uint8_t _attachment );

		void preReset();

		void postReset();

		void finishAll( bool _alloc = false );

		void invalidateCache();

		void finish();

	public:
		DXGI m_dxgi;

		XE::uint64 m_width;
		XE::uint64 m_height;
		XE::ResetFlags m_reset;
		XE::TextureFormat m_format;

		XE::LibraryHandle m_kernel32Dll;
		XE::LibraryHandle m_d3d12Dll;
		XE::LibraryHandle m_winPixEvent;

		D3D_FEATURE_LEVEL m_featureLevel;

		D3D_DRIVER_TYPE m_driverType;
		D3D12_FEATURE_DATA_ARCHITECTURE m_architecture;
		D3D12_FEATURE_DATA_D3D12_OPTIONS m_options;

		DXGI::SwapChainI * m_swapChain;
		ID3D12Resource * m_msaaRt;

		ID3D12InfoQueue * m_infoQueue;

		XE::int64 m_presentElapsed;
		XE::uint16 m_numWindows;
		FrameBufferHandle m_windows[GFX_MAX_FRAME_BUFFERS];

		ID3D12Device * m_device;
		D3D12::TimerQuery     m_gpuTimer;
		D3D12::OcclusionQuery m_occlusionQuery;

		XE::uint32 m_deviceInterfaceVersion;

		ID3D12DescriptorHeap * m_rtvDescriptorHeap;
		ID3D12DescriptorHeap * m_dsvDescriptorHeap;
		D3D12_CPU_DESCRIPTOR_HANDLE m_rtvHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE m_dsvHandle;
		D3D12_CPU_DESCRIPTOR_HANDLE * m_currentColor;
		D3D12_CPU_DESCRIPTOR_HANDLE * m_currentDepthStencil;
		ID3D12Resource * m_backBufferColor[GFX_MAX_BACK_BUFFERS];
		XE::uint64 m_backBufferColorFence[GFX_MAX_BACK_BUFFERS];
		ID3D12Resource * m_backBufferDepthStencil;

		D3D12::ScratchBuffer m_scratchBuffer[GFX_MAX_BACK_BUFFERS];
		D3D12::DescriptorAllocator m_samplerAllocator;

		ID3D12RootSignature * m_rootSignature;
		ID3D12CommandSignature * m_commandSignature[3];

		D3D12::CommandQueue m_cmd;
		ID3D12GraphicsCommandList * m_commandList;

		bool m_wireframe;
		bool m_lost;

		SwapChainDesc m_scd;
		XE::uint32 m_maxAnisotropy;
		bool m_depthClamp;

		D3D12::Buffer m_indexBuffers[GFX_MAX_INDEX_BUFFERS];
		D3D12::VertexBuffer m_vertexBuffers[GFX_MAX_VERTEX_BUFFERS];
		D3D12::Shader m_shaders[GFX_MAX_SHADERS];
		D3D12::Program m_program[GFX_MAX_PROGRAMS];
		D3D12::Texture m_textures[GFX_MAX_TEXTURES];
		D3D12::FrameBuffer m_frameBuffers[GFX_MAX_FRAME_BUFFERS];
		void * m_uniforms[GFX_MAX_UNIFORMS];

		D3D12::VertexLayout m_vertexLayouts[GFX_MAX_VERTEX_LAYOUTS];

		// 		Matrix4 m_predefinedUniforms[PredefinedUniform::Count];
		// 		UniformRegistry m_uniformReg;
		// 
		// 		StateCacheT<ID3D12PipelineState> m_pipelineStateCache;
		// 		StateCache m_samplerStateCache;
		// 
		// 		TextVideoMem m_textVideoMem;

		XE::uint8 m_fsScratch[64 << 10];
		XE::uint8 m_vsScratch[64 << 10];

		XE::FrameBufferHandle m_fbh;
		XE::uint32 m_backBufferColorIdx;
		bool m_rtMsaa;
		bool m_directAccessSupport;
	};

};

XE::D3D12::RenderContext * _RTX = nullptr;

namespace XE::D3D12
{
	RingBufferControl::RingBufferControl( uint32_t _size )
		: m_size( _size )
		, m_current( 0 )
		, m_write( 0 )
		, m_read( 0 )
	{

	}

	RingBufferControl::~RingBufferControl()
	{

	}

	uint32_t RingBufferControl::available() const
	{
		return distance( m_read, m_current );
	}

	uint32_t RingBufferControl::consume( uint32_t _size )
	{
		const uint32_t maxSize = distance( m_read, m_current );
		const uint32_t sizeNoSign = _size & 0x7fffffff;
		const uint32_t test = sizeNoSign - maxSize;
		const uint32_t size = sels( test, _size, maxSize );
		const uint32_t advance = m_read + size;
		const uint32_t read = advance % m_size;
		m_read = read;
		return size;
	}

	uint32_t RingBufferControl::reserve( uint32_t _size, bool _mustSucceed /*= false */ )
	{
		const uint32_t dist = distance( m_write, m_read ) - 1;
		const uint32_t maxSize = sels( dist, m_size - 1, dist );
		const uint32_t sizeNoSign = _size & 0x7fffffff;
		const uint32_t test = sizeNoSign - maxSize;
		const uint32_t size = sels( test, _size, maxSize );
		const uint32_t advance = m_write + size;
		const uint32_t write = advance % m_size;
		m_write = write;
		return size;
	}

	uint32_t RingBufferControl::commit( uint32_t _size )
	{
		const uint32_t maxSize = distance( m_current, m_write );
		const uint32_t sizeNoSign = _size & 0x7fffffff;
		const uint32_t test = sizeNoSign - maxSize;
		const uint32_t size = sels( test, _size, maxSize );
		const uint32_t advance = m_current + size;
		const uint32_t current = advance % m_size;

	#if COMPILER == COMPILER_MSVC
	#	if CPU == CPU_X86
		_mm_mfence();
	#	else
		MemoryBarrier();
	#	endif
	#else
		__sync_synchronize();
	#endif

		m_current = current;
		return size;
	}

	uint32_t RingBufferControl::distance( uint32_t _from, uint32_t _to ) const
	{
		const uint32_t diff = _to - _from;
		const uint32_t le = m_size + diff;

		const uint32_t result = sels( diff, le, diff );

		return result;
	}

	void RingBufferControl::reset()
	{
		m_current = 0;
		m_write = 0;
		m_read = 0;
	}

	uint32_t RingBufferControl::sels( uint32_t test, uint32_t _a, uint32_t _b ) const
	{
		const uint32_t mask = test >> 31;
		const uint32_t sel_a = _a & mask;
		const uint32_t sel_b = _b & ~mask;
		const uint32_t result = sel_a | sel_b;

		return result;
	}

	void ScratchBuffer::create( XE::uint32 _size, XE::uint32 _maxDescriptors )
	{
		m_size = _size;

		ID3D12Device * device = _RTX->m_device;
		m_incrementSize = device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV );

		D3D12_DESCRIPTOR_HEAP_DESC desc;
		desc.NumDescriptors = _maxDescriptors;
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask = 1;
		DX_CHECK( device->CreateDescriptorHeap( &desc
												, IID_ID3D12DescriptorHeap
												, ( void ** )&m_heap
		) );

		m_upload = createCommittedResource( device, HeapProperty::Type::UPLOAD, desc.NumDescriptors * 1024 );
		m_gpuVA = m_upload->GetGPUVirtualAddress();
		D3D12_RANGE readRange = { 0, 0 };
		m_upload->Map( 0, &readRange, ( void ** )&m_data );

		reset( m_gpuHandle );
	}

	void ScratchBuffer::destroy()
	{
		D3D12_RANGE writeRange = { 0, 0 };
		m_upload->Unmap( 0, &writeRange );

		DX_RELEASE( m_upload );
		DX_RELEASE( m_heap );
	}

	void ScratchBuffer::reset( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle )
	{
		m_pos = 0;
		m_cpuHandle = getCPUHandleHeapStart( m_heap );
		m_gpuHandle = getGPUHandleHeapStart( m_heap );
		_gpuHandle = m_gpuHandle;
	}

	void ScratchBuffer::allocEmpty( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle )
	{
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void * ScratchBuffer::allocCbv( D3D12_GPU_VIRTUAL_ADDRESS & _gpuAddress, XE::uint32 _size )
	{
		_gpuAddress = m_gpuVA + m_pos;
		void * data = &m_data[m_pos];

		m_pos += ALIGNED256( _size );

		return data;
	}

	void ScratchBuffer::allocSrv( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, Texture & _texture, XE::uint8 _mip )
	{
		ID3D12Device * device = _RTX->m_device;

		D3D12_SHADER_RESOURCE_VIEW_DESC tmpSrvd;
		D3D12_SHADER_RESOURCE_VIEW_DESC * srvd = &_texture.m_srvd;
		if( 0 != _mip )
		{
			std::memcpy( &tmpSrvd, srvd, sizeof( tmpSrvd ) );
			srvd = &tmpSrvd;

			switch( _texture.m_srvd.ViewDimension )
			{
			default:
			case D3D12_SRV_DIMENSION_TEXTURE2D:
				srvd->Texture2D.MostDetailedMip = _mip;
				srvd->Texture2D.MipLevels = 1;
				srvd->Texture2D.PlaneSlice = 0;
				srvd->Texture2D.ResourceMinLODClamp = 0;
				break;

			case D3D12_SRV_DIMENSION_TEXTURECUBE:
				srvd->TextureCube.MostDetailedMip = _mip;
				srvd->TextureCube.MipLevels = 1;
				srvd->TextureCube.ResourceMinLODClamp = 0;
				break;

			case D3D12_SRV_DIMENSION_TEXTURE3D:
				srvd->Texture3D.MostDetailedMip = _mip;
				srvd->Texture3D.MipLevels = 1;
				srvd->Texture3D.ResourceMinLODClamp = 0;
				break;
			}
		}

		device->CreateShaderResourceView( NULL != _texture.m_singleMsaa ? _texture.m_singleMsaa : _texture.m_ptr
										  , srvd
										  , m_cpuHandle
		);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void ScratchBuffer::allocSrv( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, D3D12::Buffer & _buffer )
	{
		ID3D12Device * device = _RTX->m_device;
		device->CreateShaderResourceView( _buffer.m_ptr
										  , &_buffer.m_srvd
										  , m_cpuHandle
		);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void ScratchBuffer::allocUav( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, Texture & _texture, XE::uint8 _mip )
	{
		ID3D12Device * device = _RTX->m_device;

		D3D12_UNORDERED_ACCESS_VIEW_DESC tmpUavd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC * uavd = &_texture.m_uavd;

		if( 0 != _mip )
		{
			std::memcpy( &tmpUavd, uavd, sizeof( tmpUavd ) );
			uavd = &tmpUavd;

			switch( _texture.m_uavd.ViewDimension )
			{
			default:
			case D3D12_UAV_DIMENSION_TEXTURE2D:
				uavd->Texture2D.MipSlice = _mip;
				uavd->Texture2D.PlaneSlice = 0;
				break;
			case D3D12_UAV_DIMENSION_TEXTURE2DARRAY:
				uavd->Texture2DArray.MipSlice = _mip;
				uavd->Texture2DArray.PlaneSlice = 0;
				break;

			case D3D12_UAV_DIMENSION_TEXTURE3D:
				uavd->Texture3D.MipSlice = _mip;
				break;
			}
		}

		device->CreateUnorderedAccessView( _texture.m_ptr
										   , NULL
										   , uavd
										   , m_cpuHandle
		);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	void ScratchBuffer::allocUav( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, D3D12::Buffer & _buffer )
	{
		ID3D12Device * device = _RTX->m_device;
		device->CreateUnorderedAccessView( _buffer.m_ptr
										   , NULL
										   , &_buffer.m_uavd
										   , m_cpuHandle
		);
		m_cpuHandle.ptr += m_incrementSize;

		_gpuHandle = m_gpuHandle;
		m_gpuHandle.ptr += m_incrementSize;
	}

	ID3D12DescriptorHeap * ScratchBuffer::getHeap()
	{
		return m_heap;
	}

	void DescriptorAllocator::create( D3D12_DESCRIPTOR_HEAP_TYPE _type, XE::uint16 _maxDescriptors, XE::uint16 _numDescriptorsPerBlock /*= 1 */ )
	{
		m_numDescriptorsPerBlock = _numDescriptorsPerBlock;

		ID3D12Device * device = _RTX->m_device;

		m_incrementSize = device->GetDescriptorHandleIncrementSize( _type );

		D3D12_DESCRIPTOR_HEAP_DESC desc;
		desc.NumDescriptors = _maxDescriptors;
		desc.Type = _type;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		desc.NodeMask = 1;
		DX_CHECK( device->CreateDescriptorHeap( &desc, IID_ID3D12DescriptorHeap, ( void ** )&m_heap ) );

		m_cpuHandle = getCPUHandleHeapStart( m_heap );
		m_gpuHandle = getGPUHandleHeapStart( m_heap );
	}

	void DescriptorAllocator::destroy()
	{
		DX_RELEASE( m_heap );
	}

	DescriptorHeapHandle DescriptorAllocator::alloc( ID3D12Resource * _ptr, const D3D12_SHADER_RESOURCE_VIEW_DESC * _desc )
	{
		DescriptorHeapHandle idx = m_handleAlloc.Alloc();

		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = { m_cpuHandle.ptr + idx * m_incrementSize };

		ID3D12Device * device = _RTX->m_device;
		device->CreateShaderResourceView( _ptr
										  , _desc
										  , cpuHandle
		);

		return idx;
	}

	DescriptorHeapHandle DescriptorAllocator::alloc( const XE::SamplerFlags * _flags, XE::uint32 _num, const float _palette[][4] )
	{
		uint16_t idx = m_handleAlloc.Alloc();

		ID3D12Device * device = _RTX->m_device;
		uint32_t maxAnisotropy = _RTX->m_maxAnisotropy;

		for( uint32_t ii = 0; ii < _num; ++ii )
		{
			XE::SamplerFlags flags = _flags[ii];

			const uint32_t cmpFunc = ( ( flags & XE::SamplerFlag::COMPAREMASK ) >> XE::SamplerFlag::COMPARESHIFT ).GetValue();
			const uint8_t  minFilter = s_textureFilter[0][( ( flags & XE::SamplerFlag::MINMASK ) >> XE::SamplerFlag::MINSHIFT ).GetValue()];
			const uint8_t  magFilter = s_textureFilter[1][( ( flags & XE::SamplerFlag::MAGMASK ) >> XE::SamplerFlag::MAGSHIFT ).GetValue()];
			const uint8_t  mipFilter = s_textureFilter[2][( ( flags & XE::SamplerFlag::MIPMASK ) >> XE::SamplerFlag::MIPSHIFT ).GetValue()];
			const uint8_t  filter = 0 == cmpFunc ? 0 : D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT;

			D3D12_SAMPLER_DESC sd;
			sd.Filter = ( D3D12_FILTER )( filter | minFilter | magFilter | mipFilter );
			sd.AddressU = s_textureAddress[( ( flags & XE::SamplerFlag::UMASK ) >> XE::SamplerFlag::USHIFT ).GetValue()];
			sd.AddressV = s_textureAddress[( ( flags & XE::SamplerFlag::VMASK ) >> XE::SamplerFlag::VSHIFT ).GetValue()];
			sd.AddressW = s_textureAddress[( ( flags & XE::SamplerFlag::WMASK ) >> XE::SamplerFlag::WSHIFT ).GetValue()];
			sd.MipLODBias = 0;
			sd.MaxAnisotropy = maxAnisotropy;
			sd.ComparisonFunc = 0 == cmpFunc ? D3D12_COMPARISON_FUNC_NEVER : s_cmpFunc[cmpFunc];

			uint32_t index = ( ( flags & XE::SamplerFlag::BORDERCOLORMASK ) >> XE::SamplerFlag::BORDERCOLORSHIFT ).GetValue();

			if( NULL != _palette
				&& needBorderColor( flags ) )
			{
				const float * rgba = _palette[index];
				sd.BorderColor[0] = rgba[0];
				sd.BorderColor[1] = rgba[1];
				sd.BorderColor[2] = rgba[2];
				sd.BorderColor[3] = rgba[3];
			}
			else
			{
				sd.BorderColor[0] = 0.0f;
				sd.BorderColor[1] = 0.0f;
				sd.BorderColor[2] = 0.0f;
				sd.BorderColor[3] = 0.0f;
			}
			sd.MinLOD = 0;
			sd.MaxLOD = D3D12_FLOAT32_MAX;

			D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle =
			{
				m_cpuHandle.ptr + ( idx * m_numDescriptorsPerBlock + ii ) * m_incrementSize
			};

			device->CreateSampler( &sd, cpuHandle );
		}

		return idx;
	}

	void DescriptorAllocator::free( DescriptorHeapHandle _handle )
	{
		m_handleAlloc.Free( _handle );
	}

	void DescriptorAllocator::reset()
	{
		m_handleAlloc.Reset();
	}

	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorAllocator::get( DescriptorHeapHandle _handle )
	{
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = { m_gpuHandle.ptr + _handle.GetValue() * m_numDescriptorsPerBlock * m_incrementSize };
		return gpuHandle;
	}

	ID3D12DescriptorHeap * DescriptorAllocator::getHeap()
	{
		return m_heap;
	}

	void Buffer::create( XE::uint32 _size, void * _data, XE::BufferFlags _flags, bool _vertex, XE::uint32 _stride /*= 0 */ )
	{
		m_size = _size;
		m_flags = _flags;

		const bool needUav = 0 != ( _flags & XE::MakeFlags( XE::BufferFlag::COMPUTEWRITE, XE::BufferFlag::DRAWINDIRECT ) ).GetValue();
		const bool drawIndirect = 0 != ( _flags & XE::BufferFlag::DRAWINDIRECT ).GetValue();
		m_dynamic = NULL == _data || needUav;

		DXGI_FORMAT format;
		uint32_t    stride;

		uint32_t flags = needUav
			? D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
			: D3D12_RESOURCE_FLAG_NONE
			;

		if( drawIndirect )
		{
		#if PLATFORM_OS == OS_XBOX
			flags |= D3D12XBOX_RESOURCE_FLAG_ALLOW_INDIRECT_BUFFER;
		#endif
			format = DXGI_FORMAT_R32G32B32A32_UINT;
			stride = 16;
		}
		else
		{
			uint32_t uavFormat = ( ( _flags & XE::BufferFlag::COMPUTEFORMATMASK ) >> XE::BufferFlag::COMPUTEFORMATSHIFT ).GetValue();
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
				const uint32_t uavType = XE::Mathf::Satsub( ( ( _flags & XE::BufferFlag::COMPUTETYPEMASK ) >> XE::BufferFlag::COMPUTETYPESHIFT ).GetValue(), XE::uint64( 1 ) );
				format = s_uavFormat[uavFormat].format[uavType];
				stride = s_uavFormat[uavFormat].stride;
			}
		}

		stride = 0 == _stride ? stride : _stride;

		m_srvd.Format = format;
		m_srvd.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		m_srvd.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		m_srvd.Buffer.FirstElement = 0;
		m_srvd.Buffer.NumElements = m_size / stride;
		m_srvd.Buffer.StructureByteStride = 0;
		m_srvd.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;

		m_uavd.Format = format;
		m_uavd.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
		m_uavd.Buffer.FirstElement = 0;
		m_uavd.Buffer.NumElements = m_size / stride;
		m_uavd.Buffer.StructureByteStride = 0;
		m_uavd.Buffer.CounterOffsetInBytes = 0;
		m_uavd.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

		ID3D12Device * device = _RTX->m_device;
		ID3D12GraphicsCommandList * commandList = _RTX->m_commandList;

		m_ptr = createCommittedResource( device, HeapProperty::Type::DEFAULT, _size, D3D12_RESOURCE_FLAGS( flags ) );
		m_gpuVA = m_ptr->GetGPUVirtualAddress();
		setState( commandList, drawIndirect
				  ? D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT
				  : D3D12_RESOURCE_STATE_GENERIC_READ
		);

		if( !m_dynamic )
		{
			update( commandList, 0, _size, _data );
		}
	}

	void Buffer::update( ID3D12GraphicsCommandList * _commandList, XE::uint32 _offset, XE::uint32 _size, void * _data, bool _discard /*= false */ )
	{
		ID3D12Resource * staging = createCommittedResource( _RTX->m_device, HeapProperty::Type::UPLOAD, _size );
		uint8_t * data;

		D3D12_RANGE readRange = { 0, 0 };
		DX_CHECK( staging->Map( 0, &readRange, ( void ** )&data ) );
		std::memcpy( data, _data, _size );
		D3D12_RANGE writeRange = { 0, _size };
		staging->Unmap( 0, &writeRange );

		D3D12_RESOURCE_STATES state = setState( _commandList, D3D12_RESOURCE_STATE_COPY_DEST );
		_commandList->CopyBufferRegion( m_ptr, _offset, staging, 0, _size );
		setState( _commandList, state );

		_RTX->m_cmd.release( staging );
	}

	void Buffer::destroy()
	{
		if( NULL != m_ptr )
		{
			_RTX->m_cmd.release( m_ptr );
			m_dynamic = false;
			m_state = D3D12_RESOURCE_STATE_COMMON;
		}
	}

	D3D12_RESOURCE_STATES Buffer::setState( ID3D12GraphicsCommandList * _commandList, D3D12_RESOURCE_STATES _state )
	{
		if( m_state != _state )
		{
			setResourceBarrier( _commandList
								, m_ptr
								, m_state
								, _state
			);

			std::swap( m_state, _state );
		}

		return _state;
	}

	void VertexBuffer::create( XE::uint32 _size, void * _data, XE::VertexLayoutHandle _layoutHandle, XE::BufferFlags _flags )
	{
		Buffer::create( _size, _data, _flags, true );
		m_layoutHandle = _layoutHandle;
	}

	void Shader::create( XE::MemoryView _mem )
	{

	}

	void Shader::destroy()
	{
		// 		if( NULL != m_constantBuffer )
		// 		{
		// 			UniformBuffer::destroy( m_constantBuffer );
		// 			m_constantBuffer = NULL;
		// 		}

		m_numPredefined = 0;

		if( m_code.Size() != 0 )
		{
			m_code.Clear();

			m_hash = 0;
		}
	}

	void Program::create( const D3D12::Shader * _vsh, const D3D12::Shader * _fsh )
	{
		XE_ASSERT( _vsh->m_code.Size() && "Vertex shader doesn't exist." );
		m_vsh = _vsh;
		// 		bx::memCopy( &m_predefined[0], _vsh->m_predefined, _vsh->m_numPredefined * sizeof( PredefinedUniform ) );
		// 		m_numPredefined = _vsh->m_numPredefined;

		if( NULL != _fsh )
		{
			XE_ASSERT( _fsh->m_code.Size() && "Fragment shader doesn't exist." );
			m_fsh = _fsh;
			// 			bx::memCopy( &m_predefined[m_numPredefined], _fsh->m_predefined, _fsh->m_numPredefined * sizeof( PredefinedUniform ) );
			// 			m_numPredefined += _fsh->m_numPredefined;
		}
	}

	void Program::destroy()
	{
		//		m_numPredefined = 0;
		m_vsh = NULL;
		m_fsh = NULL;
	}

	void * Texture::create( const XE::MemoryView _mem, XE::uint64 _flags, XE::uint8 _skip )
	{
		// TODO: 

		return m_directAccessPtr;
	}

	void Texture::destroy()
	{
		if( NULL != m_ptr )
		{
			if( NULL != m_directAccessPtr )
			{
				D3D12_RANGE writeRange = { 0, 0 };
				m_ptr->Unmap( 0, &writeRange );
				m_directAccessPtr = NULL;
			}

			if( 0 == ( m_flags & XE::SamplerFlag::INTERNALSHARED ).GetValue() )
			{
				_RTX->m_cmd.release( m_ptr );
				m_ptr = NULL;
				m_state = D3D12_RESOURCE_STATE_COMMON;

				if( NULL != m_singleMsaa )
				{
					_RTX->m_cmd.release( m_singleMsaa );
					m_singleMsaa = NULL;
				}
			}
		}
	}

	void Texture::overrideInternal( uintptr_t _ptr )
	{
		destroy();
		m_flags |= XE::SamplerFlag::INTERNALSHARED;
		m_ptr = ( ID3D12Resource * )_ptr;
	}

	void Texture::update( ID3D12GraphicsCommandList * _commandList, XE::uint8 _side, XE::uint8 _mip, const XE::Recti & _rect, XE::uint16 _z, XE::uint16 _depth, XE::uint16 _pitch, const XE::MemoryView _mem )
	{
		// TODO: 
	}

	void Texture::resolve( ID3D12GraphicsCommandList * _commandList, XE::uint8 _resolve )
	{
		( void )( _resolve );

		bool needResolve = NULL != m_singleMsaa;
		if( needResolve )
		{
			D3D12_RESOURCE_STATES state = setState( _commandList, D3D12_RESOURCE_STATE_RESOLVE_SOURCE );

			setResourceBarrier( _commandList
								, m_singleMsaa
								, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
								, D3D12_RESOURCE_STATE_RESOLVE_DEST
			);

			_commandList->ResolveSubresource( m_singleMsaa
											  , 0
											  , m_ptr
											  , 0
											  , s_textureFormat[m_textureFormat].m_fmt
			);

			setResourceBarrier( _commandList
								, m_singleMsaa
								, D3D12_RESOURCE_STATE_RESOLVE_DEST
								, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
			);

			setState( _commandList, state );
		}
	}

	D3D12_RESOURCE_STATES Texture::setState( ID3D12GraphicsCommandList * _commandList, D3D12_RESOURCE_STATES _state )
	{
		if( m_state != _state )
		{
			setResourceBarrier( _commandList
								, m_ptr
								, m_state
								, _state
			);

			std::swap( m_state, _state );
		}

		return _state;
	}

	void FrameBuffer::create( XE::uint8 _num, const Attachment * _attachment )
	{
		m_denseIdx = UINT16_MAX;
		m_numTh = _num;
		std::memcpy( m_attachment, _attachment, _num * sizeof( Attachment ) );

		postReset();
	}

	void FrameBuffer::create( XE::uint16 _denseIdx, void * _nwh, XE::uint32 _width, XE::uint32 _height, XE::TextureFormat _format, XE::TextureFormat _depthFormat )
	{
		( void )( _nwh, _width, _height, _depthFormat );

	#if  PLATFORM_OS == OS_WINDOWS
		SwapChainDesc scd;
		std::memcpy( &scd, &_RTX->m_scd, sizeof( SwapChainDesc ) );
		scd.format = TextureFormat::COUNT == _format ? scd.format : s_textureFormat[( XE::uint64 )_format].m_fmt;
		scd.width = _width;
		scd.height = _height;
		scd.nwh = _nwh;
		scd.sampleDesc = s_msaa[0];

		DX_CHECK( _RTX->m_dxgi.CreateSwapChain( _RTX->m_device, scd, &m_swapChain ) );

		m_state = D3D12_RESOURCE_STATE_PRESENT;

		DX_CHECK( _RTX->m_dxgi._Factory->MakeWindowAssociation(
			( HWND )_nwh
			, 0
			| DXGI_MWA_NO_WINDOW_CHANGES
			| DXGI_MWA_NO_ALT_ENTER
		) );

		ID3D12Device * device = _RTX->m_device;
		FrameBufferHandle fbh = { uint16_t( this - _RTX->m_frameBuffers ) };

		for( uint32_t ii = 0, num = scd.bufferCount; ii < num; ++ii )
		{
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = _RTX->getRtv( fbh, uint8_t( ii ) );

			ID3D12Resource * colorBuffer;
			DX_CHECK( m_swapChain->GetBuffer( ii
											  , IID_ID3D12Resource
											  , ( void ** )&colorBuffer
			) );
			device->CreateRenderTargetView( colorBuffer, NULL, rtvHandle );
			DX_RELEASE( colorBuffer );
		}
	#endif

		m_nwh = _nwh;
		m_denseIdx = _denseIdx;
		m_num = 1;
	}

	XE::uint16 FrameBuffer::destroy()
	{
		DX_RELEASE( m_swapChain );

		m_nwh = NULL;
		m_numTh = 0;
		m_needPresent = false;

		m_depth = TextureHandle::Invalid;

		uint16_t denseIdx = m_denseIdx;
		m_denseIdx = UINT16_MAX;

		return denseIdx;
	}

	HRESULT FrameBuffer::present( XE::uint32 _syncInterval, XE::uint32 _flags )
	{
		if( m_needPresent )
		{
			HRESULT hr = m_swapChain->Present( _syncInterval, _flags );
			hr = !isLost( hr ) ? S_OK : hr;
			m_needPresent = false;
			return hr;
		}

		return S_OK;
	}

	void FrameBuffer::preReset()
	{

	}

	void FrameBuffer::postReset()
	{

	}

	void FrameBuffer::resolve()
	{
		if( 0 < m_numTh )
		{
			for( uint32_t ii = 0; ii < m_numTh; ++ii )
			{
				const Attachment & at = m_attachment[ii];

				if( at.Handle )
				{
					D3D12::Texture & texture = _RTX->m_textures[at.Handle];
					texture.resolve( _RTX->m_commandList, at.Resolve );
				}
			}
		}
	}

	void FrameBuffer::clear( ID3D12GraphicsCommandList * _commandList, const XE::ClearDesc & _clear, const float _palette[][4], const D3D12_RECT * _rect /*= NULL*/, XE::uint32 _num /*= 0 */ )
	{
		ID3D12Device * device = _RTX->m_device;
		FrameBufferHandle fbh = { ( uint16_t )( this - _RTX->m_frameBuffers ) };
		D3D12_CPU_DESCRIPTOR_HANDLE rtv = _RTX->getRtv( fbh );
		uint32_t rtvDescriptorSize = device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

		if( ( XE::ClearFlag::COLOR & _clear.Flags ).GetValue() && m_num != 0 )
		{
			float frgba[4] =
			{
				_clear.Color[0] * 1.0f / 255.0f,
				_clear.Color[1] * 1.0f / 255.0f,
				_clear.Color[2] * 1.0f / 255.0f,
				_clear.Color[3] * 1.0f / 255.0f,
			};
			for( uint32_t ii = 0, num = m_num; ii < num; ++ii )
			{
				_commandList->ClearRenderTargetView( rtv
													 , frgba
													 , _num
													 , _rect
				);
				rtv.ptr += rtvDescriptorSize;
			}
		}

		if( m_depth && ( XE::MakeFlags( XE::ClearFlag::DEPTH, XE::ClearFlag::STENCIL ) & _clear.Flags ).GetValue() != 0 )
		{
			D3D12_CPU_DESCRIPTOR_HANDLE dsvDescriptor = getCPUHandleHeapStart( _RTX->m_dsvDescriptorHeap );
			uint32_t dsvDescriptorSize = device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_DSV );
			dsvDescriptor.ptr += ( 1 + fbh ) * dsvDescriptorSize;

			DWORD flags = 0;
			flags |= ( _clear.Flags & XE::ClearFlag::DEPTH ).GetValue() ? D3D12_CLEAR_FLAG_DEPTH : 0;
			flags |= ( _clear.Flags & XE::ClearFlag::STENCIL ).GetValue() ? D3D12_CLEAR_FLAG_STENCIL : 0;

			_commandList->ClearDepthStencilView( dsvDescriptor
												 , D3D12_CLEAR_FLAGS( flags )
												 , _clear.Depth
												 , _clear.Stencil
												 , _num
												 , _rect
			);
		}
	}

	D3D12_RESOURCE_STATES FrameBuffer::setState( ID3D12GraphicsCommandList * _commandList, XE::uint8 _idx, D3D12_RESOURCE_STATES _state )
	{
		if( m_state != _state )
		{
			ID3D12Resource * colorBuffer;
			DX_CHECK( m_swapChain->GetBuffer( _idx
											  , IID_ID3D12Resource
											  , ( void ** )&colorBuffer
			) );

			setResourceBarrier( _commandList
								, colorBuffer
								, m_state
								, _state
			);

			DX_RELEASE( colorBuffer );

			std::swap( m_state, _state );
		}

		return _state;
	}

	void CommandQueue::init( ID3D12Device * _device )
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = 0;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 1;
		DX_CHECK( _device->CreateCommandQueue( &queueDesc
											   , IID_ID3D12CommandQueue
											   , ( void ** )&m_commandQueue
		) );

		m_completedFence = 0;
		m_currentFence = 0;
		DX_CHECK( _device->CreateFence( 0
										, D3D12_FENCE_FLAG_NONE
										, IID_ID3D12Fence
										, ( void ** )&m_fence
		) );

		for( uint32_t ii = 0; ii < XE::countof( m_commandList ); ++ii )
		{
			DX_CHECK( _device->CreateCommandAllocator( D3D12_COMMAND_LIST_TYPE_DIRECT
													   , IID_ID3D12CommandAllocator
													   , ( void ** )&m_commandList[ii].m_commandAllocator
			) );

			DX_CHECK( _device->CreateCommandList( 0
												  , D3D12_COMMAND_LIST_TYPE_DIRECT
												  , m_commandList[ii].m_commandAllocator
												  , NULL
												  , IID_ID3D12GraphicsCommandList
												  , ( void ** )&m_commandList[ii].m_commandList
			) );

			DX_CHECK( m_commandList[ii].m_commandList->Close() );
		}
	}

	void CommandQueue::shutdown()
	{
		finish( UINT64_MAX, true );

		DX_RELEASE( m_fence );

		for( uint32_t ii = 0; ii < XE::countof( m_commandList ); ++ii )
		{
			DX_RELEASE( m_commandList[ii].m_commandAllocator );
			DX_RELEASE( m_commandList[ii].m_commandList );
		}

		DX_RELEASE( m_commandQueue );
	}

	ID3D12GraphicsCommandList * CommandQueue::alloc()
	{
		while( 0 == m_control.reserve( 1 ) )
		{
			consume();
		}

		CommandList & commandList = m_commandList[m_control.m_current];
		DX_CHECK( commandList.m_commandAllocator->Reset() );
		DX_CHECK( commandList.m_commandList->Reset( commandList.m_commandAllocator, NULL ) );
		return commandList.m_commandList;
	}

	XE::uint64 CommandQueue::kick()
	{
		CommandList & commandList = m_commandList[m_control.m_current];
		DX_CHECK( commandList.m_commandList->Close() );

		ID3D12CommandList * commandLists[] = { commandList.m_commandList };
		m_commandQueue->ExecuteCommandLists( XE::countof( commandLists ), commandLists );

		commandList.m_event = CreateEventExA( NULL, NULL, 0, EVENT_ALL_ACCESS );
		const uint64_t fence = m_currentFence++;
		m_commandQueue->Signal( m_fence, fence );
		m_fence->SetEventOnCompletion( fence, commandList.m_event );

		m_control.commit( 1 );

		return fence;
	}

	void CommandQueue::finish( XE::uint64 _waitFence /*= UINT64_MAX*/, bool _finishAll /*= false */ )
	{
		while( 0 < m_control.available() )
		{
			consume();

			if( !_finishAll
				&& _waitFence <= m_completedFence )
			{
				return;
			}
		}

		XE_ASSERT( 0 == m_control.available() && "" );
	}

	bool CommandQueue::tryFinish( XE::uint64 _waitFence )
	{
		if( 0 < m_control.available() )
		{
			if( consume( 0 )
				&& _waitFence <= m_completedFence )
			{
				return true;
			}
		}

		return false;
	}

	void CommandQueue::release( ID3D12Resource * _ptr )
	{
		m_release[m_control.m_current].push_back( _ptr );
	}

	bool CommandQueue::consume( XE::uint32 _ms /*= INFINITE */ )
	{
		CommandList & commandList = m_commandList[m_control.m_read];
		if( WAIT_OBJECT_0 == WaitForSingleObject( commandList.m_event, _ms ) )
		{
			CloseHandle( commandList.m_event );
			commandList.m_event = NULL;
			m_completedFence = m_fence->GetCompletedValue();
			if( UINT64_MAX != m_completedFence )
			{
				XE_LOG( XE::LoggerLevel::Warning, "D3D12: Device lost." );
			}

			m_commandQueue->Wait( m_fence, m_completedFence );

			for( auto i : m_release[m_control.m_read] )
			{
				DX_RELEASE( i );
			}

			m_control.consume( 1 );

			return true;
		}

		return false;
	}

	void TimerQuery::init()
	{

	}

	void TimerQuery::shutdown()
	{

	}

	XE::uint32 TimerQuery::begin( XE::uint32 _resultIdx )
	{
		return 0;
	}

	void TimerQuery::end( XE::uint32 _idx )
	{

	}

	bool TimerQuery::update()
	{
		return false;
	}

	void OcclusionQuery::init()
	{

	}

	void OcclusionQuery::shutdown()
	{

	}

	void OcclusionQuery::begin( ID3D12GraphicsCommandList * _commandList, XE::RenderFrame * _render, OcclusionQueryHandle _handle )
	{

	}

	void OcclusionQuery::end( ID3D12GraphicsCommandList * _commandList )
	{

	}

	void OcclusionQuery::invalidate( OcclusionQueryHandle _handle )
	{

	}

	D3D12_CPU_DESCRIPTOR_HANDLE RenderContext::getRtv( FrameBufferHandle _fbh )
	{
		D3D12::FrameBuffer & frameBuffer = m_frameBuffers[_fbh];

		if( NULL != frameBuffer.m_swapChain )
		{
		#if PLATFORM_OS == OS_WINDOWS
			uint8_t idx = uint8_t( frameBuffer.m_swapChain->GetCurrentBackBufferIndex() );
			frameBuffer.setState( m_commandList, idx, D3D12_RESOURCE_STATE_RENDER_TARGET );
			return getRtv( _fbh, idx );
		#endif
		}

		return getRtv( _fbh, 0 );
	}

	D3D12_CPU_DESCRIPTOR_HANDLE RenderContext::getRtv( FrameBufferHandle _fbh, uint8_t _attachment )
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvDescriptor = getCPUHandleHeapStart( m_rtvDescriptorHeap );
		uint32_t rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );
		D3D12_CPU_DESCRIPTOR_HANDLE result =
		{
			rtvDescriptor.ptr + ( XE::countof( m_backBufferColor ) + _fbh.GetValue() * GFX_MAX_ATTACHMENTS + _attachment ) * rtvDescriptorSize
		};
		return result;
	}

	void RenderContext::preReset()
	{
		finishAll();

		if( NULL != m_swapChain )
		{
			for( uint32_t ii = 0, num = m_scd.bufferCount; ii < num; ++ii )
			{
				DX_RELEASE( m_backBufferColor[ii] );
			}

			DX_RELEASE( m_backBufferDepthStencil );
		}

		for( uint32_t ii = 0; ii < XE::countof( m_frameBuffers ); ++ii )
		{
			m_frameBuffers[ii].preReset();
		}

		invalidateCache();
	}

	void RenderContext::postReset()
	{
		std::memset( m_backBufferColorFence, 0, sizeof( m_backBufferColorFence ) );

		uint32_t rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

		if( NULL != m_swapChain )
		{
			for( uint32_t ii = 0, num = m_scd.bufferCount; ii < num; ++ii )
			{
				D3D12_CPU_DESCRIPTOR_HANDLE handle = getCPUHandleHeapStart( m_rtvDescriptorHeap );
				handle.ptr += ii * rtvDescriptorSize;
				DX_CHECK( m_swapChain->GetBuffer( ii
												  , IID_ID3D12Resource
												  , ( void ** )&m_backBufferColor[ii]
				) );

				D3D12_RENDER_TARGET_VIEW_DESC rtvDesc;
				rtvDesc.Format = ( m_reset & XE::ResetFlag::SRGBBACKBUFFER ) ? s_textureFormat[( XE::uint64 )m_format].m_fmtSrgb : s_textureFormat[( XE::uint64 )m_format].m_fmt;

				if( 1 < getResourceDesc( m_backBufferColor[ii] ).DepthOrArraySize )
				{
					rtvDesc.ViewDimension = ( NULL == m_msaaRt ) ?
						D3D12_RTV_DIMENSION_TEXTURE2DARRAY : D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY;
					rtvDesc.Texture2DArray.FirstArraySlice = 0;
					rtvDesc.Texture2DArray.ArraySize = getResourceDesc( m_backBufferColor[ii] ).DepthOrArraySize;
					rtvDesc.Texture2DArray.MipSlice = 0;
					rtvDesc.Texture2DArray.PlaneSlice = 0;
				}
				else
				{
					rtvDesc.ViewDimension = ( NULL == m_msaaRt ) ?
						D3D12_RTV_DIMENSION_TEXTURE2D : D3D12_RTV_DIMENSION_TEXTURE2DMS;
					rtvDesc.Texture2D.MipSlice = 0;
					rtvDesc.Texture2D.PlaneSlice = 0;
				}

				m_device->CreateRenderTargetView(
					NULL == m_msaaRt
					? m_backBufferColor[ii]
					: m_msaaRt
					, &rtvDesc
					, handle
				);

				if( PLATFORM_OS & OS_XBOX )
				{
					ID3D12Resource * resource = m_backBufferColor[ii];

					XE_ASSERT( DXGI_FORMAT_R8G8B8A8_UNORM == m_scd.format && "" );
					const uint32_t size = m_scd.width * m_scd.height * 4;

					void * ptr;
					DX_CHECK( resource->Map( 0, NULL, &ptr ) );
					std::memset( ptr, 0, size );
					resource->Unmap( 0, NULL );
				}
			}
		}

		D3D12_RESOURCE_DESC resourceDesc;
		resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		resourceDesc.Alignment = 1 < m_scd.sampleDesc.Count ? D3D12_DEFAULT_MSAA_RESOURCE_PLACEMENT_ALIGNMENT : 0;
		resourceDesc.Width = std::max<XE::uint64>( m_width, 1 );
		resourceDesc.Height = std::max<XE::uint64>( m_height, 1 );
		resourceDesc.DepthOrArraySize = 1;
		resourceDesc.MipLevels = 1;
		resourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		resourceDesc.SampleDesc = m_scd.sampleDesc;
		resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
		resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

		D3D12_CLEAR_VALUE clearValue;
		clearValue.Format = resourceDesc.Format;
		clearValue.DepthStencil.Depth = 1.0f;
		clearValue.DepthStencil.Stencil = 0;

		m_commandList = m_cmd.alloc();

		m_backBufferDepthStencil = createCommittedResource( m_device, HeapProperty::Type::DEFAULT, &resourceDesc, &clearValue );
		m_device->CreateDepthStencilView( m_backBufferDepthStencil, NULL, getCPUHandleHeapStart( m_dsvDescriptorHeap ) );

		setResourceBarrier( m_commandList
							, m_backBufferDepthStencil
							, D3D12_RESOURCE_STATE_COMMON
							, D3D12_RESOURCE_STATE_DEPTH_WRITE
		);

		for( uint32_t ii = 0; ii < XE::countof( m_frameBuffers ); ++ii )
		{
			m_frameBuffers[ii].postReset();
		}

		if( NULL != m_msaaRt )
		{
			setResourceBarrier( m_commandList
								, m_msaaRt
								, D3D12_RESOURCE_STATE_COMMON
								, D3D12_RESOURCE_STATE_RESOLVE_SOURCE
			);
		}
	}

	void RenderContext::finishAll( bool _alloc /*= false */ )
	{
		uint64_t fence = m_cmd.kick();
		m_cmd.finish( fence, true );
		m_commandList = _alloc ? m_cmd.alloc() : NULL;
	}

	void RenderContext::invalidateCache()
	{
		// 		m_pipelineStateCache.invalidate();
		// 		m_samplerStateCache.invalidate();

		m_samplerAllocator.reset();
	}

	void RenderContext::finish()
	{
		m_cmd.kick();
		m_cmd.finish();
		m_commandList = NULL;
	}

}


XE::RendererContextD3D12::RendererContextD3D12()
{

}

XE::RendererContextD3D12::~RendererContextD3D12()
{

}

void XE::RendererContextD3D12::OnRender( XE::RenderFrame * val )
{
	ExecCommands( val->PrevCmd );





	ExecCommands( val->PostCmd );
}

void XE::RendererContextD3D12::ExecCommands( XE::Buffer & buffer )
{
	while( !buffer.Eof() )
	{
		CommandType type = CommandType::END;

		buffer.Read( type );

		switch( type )
		{
		case XE::CommandType::RENDERER_INIT:
		{
			Init();
		}
		break;
		case XE::CommandType::RENDERER_SHUTDOWN:
		{
			Shutdown();
		}
		break;
		case XE::CommandType::CREATE_SHADER:
		{
			XE::ShaderHandle handle;
			XE::MemoryView data;

			buffer.Read( handle );
			buffer.Read( data );

			CreateShader( handle, data );
		}
		break;
		case XE::CommandType::CREATE_PROGRAM:
		{
			XE::ProgramHandle handle;

			buffer.Read( handle );

			CreateProgram( handle );
		}
		break;
		case XE::CommandType::CREATE_TEXTURE:
		{
			XE::TextureHandle handle;
			XE::MemoryView data;

			buffer.Read( handle );
			buffer.Read( data );

			CreateTexture( handle, data );
		}
		break;
		case XE::CommandType::CREATE_FRAME_BUFFER:
		{
			XE::FrameBufferHandle handle;

			buffer.Read( handle );

			CreateFrameBuffer( handle );
		}
		break;
		case XE::CommandType::CREATE_INDEX_BUFFER:
		{
			XE::IndexBufferHandle handle;
			XE::MemoryView data;

			buffer.Read( handle );
			buffer.Read( data );

			CreateIndexBuffer( handle, data );
		}
		break;
		case XE::CommandType::CREATE_VERTEX_LAYOUT:
		{
			XE::VertexLayoutHandle handle;

			buffer.Read( handle );

			CreateVertexLayout( handle );
		}
		break;
		case XE::CommandType::CREATE_VERTEX_BUFFER:
		{
			XE::VertexBufferHandle handle;
			XE::MemoryView data;

			buffer.Read( handle );
			buffer.Read( data );

			CreateVertexBuffer( handle, data );
		}
		break;
		case XE::CommandType::CREATE_INDIRECT_BUFFER:
		{
			XE::IndirectBufferHandle handle;

			buffer.Read( handle );

			CreateIndirectBuffer( handle );
		}
		break;
		case XE::CommandType::CREATE_OCCLUSION_QUERY:
		{
			XE::OcclusionQueryHandle handle;

			buffer.Read( handle );

			CreateOcclusionQuery( handle );
		}
		break;
		case XE::CommandType::CREATE_DYNAMIC_INDEX_BUFFER:
		{
			XE::DynamicIndexBufferHandle handle;

			buffer.Read( handle );

			CreateDynamicIndexBuffer( handle );
		}
		break;
		case XE::CommandType::CREATE_DYNAMIC_VERTEX_BUFFER:
		{
			XE::DynamicVertexBufferHandle handle;

			buffer.Read( handle );

			CreateDynamicVertexBuffer( handle );
		}
		break;
		case XE::CommandType::READ_TEXTURE:
		{
			XE::TextureHandle handle;
			std::uintptr_t data;
			XE::uint8 mip;

			buffer.Read( handle );
			buffer.Read( data );
			buffer.Read( mip );

			ReadTexture( handle, ( XE::uint8 * )data, mip );
		}
		break;
		case XE::CommandType::UPDATE_TEXTURE:
		{
			XE::UpdateTextureDesc desc;
			XE::MemoryView data;

			buffer.Read( desc );
			buffer.Read( data );

			UpdateTexture( desc, data );
		}
		break;
		case XE::CommandType::UPDATE_DYNAMIC_INDEX_BUFFER:
		{
			XE::DynamicIndexBufferHandle handle;
			XE::uint64 start;
			XE::MemoryView mem;

			buffer.Read( handle );
			buffer.Read( start );
			buffer.Read( mem );

			UpdateDynamicIndexBuffer( handle, start, mem );
		}
		break;
		case XE::CommandType::UPDATE_DYNAMIC_VERTEX_BUFFER:
		{
			XE::DynamicVertexBufferHandle handle;
			XE::uint64 start;
			XE::MemoryView mem;

			buffer.Read( handle );
			buffer.Read( start );
			buffer.Read( mem );

			UpdateDynamicVertexBuffer( handle, start, mem );
		}
		break;
		case XE::CommandType::END:
			return;
		case XE::CommandType::DESTROY_SHADER:
		{
			XE::ShaderHandle handle;

			buffer.Read( handle );

			DestroyShader( handle );
		}
		break;
		case XE::CommandType::DESTROY_TEXTURE:
		{
			XE::TextureHandle handle;

			buffer.Read( handle );

			DestroyTexture( handle );
		}
		break;
		case XE::CommandType::DESTROY_PROGRAM:
		{
			XE::ProgramHandle handle;

			buffer.Read( handle );

			DestroyProgram( handle );
		}
		break;
		case XE::CommandType::DESTROY_FRAMEBUFFER:
		{
			XE::FrameBufferHandle handle;

			buffer.Read( handle );

			DestroyFrameBuffer( handle );
		}
		break;
		case XE::CommandType::DESTROY_INDEX_BUFFER:
		{
			XE::IndexBufferHandle handle;

			buffer.Read( handle );

			DestroyIndexBuffer( handle );
		}
		break;
		case XE::CommandType::DESTROY_VERTEX_LAYOUT:
		{
			XE::VertexLayoutHandle handle;

			buffer.Read( handle );

			DestroyVertexLayout( handle );
		}
		break;
		case XE::CommandType::DESTROY_VERTEX_BUFFER:
		{
			XE::VertexBufferHandle handle;

			buffer.Read( handle );

			DestroyVertexBuffer( handle );
		}
		break;
		case XE::CommandType::DESTROY_INDIRECT_BUFFER:
		{
			XE::IndirectBufferHandle handle;

			buffer.Read( handle );

			DestroyIndirectBuffer( handle );
		}
		break;
		case XE::CommandType::DESTROY_OCCLUSION_QUERY:
		{
			XE::OcclusionQueryHandle handle;

			buffer.Read( handle );

			DestroyOcclusionQuery( handle );
		}
		break;
		case XE::CommandType::DESTROY_DYNAMIC_INDEX_BUFFER:
		{
			XE::DynamicIndexBufferHandle handle;

			buffer.Read( handle );

			DestroyDynamicIndexBuffer( handle );
		}
		break;
		case XE::CommandType::DESTROY_DYNAMIC_VERTEX_BUFFER:
		{
			XE::DynamicVertexBufferHandle handle;

			buffer.Read( handle );

			DestroyDynamicVertexBuffer( handle );
		}
		break;
		case XE::CommandType::REQUEST_SCREEN_SHOT:
		{
			XE::FrameBufferHandle handle;
			std::string userdata;
			std::uintptr_t callback;

			buffer.Read( handle );
			buffer.Read( userdata );
			buffer.Read( callback );

			RequestScreenShot( handle, userdata, ( ScreenShotCallbackType )callback );
		}
		break;
		default:
			break;
		}
	}
}

void XE::RendererContextD3D12::Init()
{
	_RTX->m_winPixEvent = XE::Library::Open( "WinPixEventRuntime.dll" );
	XE_ASSERT( _RTX->m_winPixEvent && "Init error: Failed to load WinPixEventRuntime.dll." );

	XE::D3D12::PIXGetThreadInfo = XE::Library::SymbolT<XE::D3D12::PFN_PIX_GET_THREAD_INFO>( _RTX->m_winPixEvent, "PIXGetThreadInfo" );
	XE_ASSERT( XE::D3D12::PIXGetThreadInfo && "Init error: Function PIXGetThreadInfo not found." );

	XE::D3D12::PIXEventsReplaceBlock = XE::Library::SymbolT<XE::D3D12::PFN_PIX_EVENTS_REPLACE_BLOCK>( _RTX->m_winPixEvent, "PIXEventsReplaceBlock" );
	XE_ASSERT( XE::D3D12::PIXEventsReplaceBlock && "Init error: Function PIXEventsReplaceBlock not found." );


	_RTX->m_kernel32Dll = XE::Library::Open( "kernel32.dll" );
	XE_ASSERT( _RTX->m_kernel32Dll && "Init error: Failed to load kernel32.dll." );

	XE::D3D12::CreateEventExA = XE::Library::SymbolT<XE::D3D12::PFN_CREATE_EVENT_EX_A>( _RTX->m_kernel32Dll, "CreateEventExA" );
	XE_ASSERT( NULL == XE::D3D12::CreateEventExA && "Init error: Function CreateEventExA not found." );


	_RTX->m_d3d12Dll = XE::Library::Open( "d3d12.dll" );
	XE_ASSERT( NULL == _RTX->m_d3d12Dll && "Init error: Failed to load d3d12.dll." );

	XE::D3D12::EnableExperimentalFeatures = XE::Library::SymbolT<XE::D3D12::PFN_D3D12_ENABLE_EXPERIMENTAL_FEATURES>( _RTX->m_d3d12Dll, "EnableExperimentalFeatures" );
	XE_ASSERT( NULL != XE::D3D12::EnableExperimentalFeatures && "Function EnableExperimentalFeatures not found." );

	XE::D3D12::CreateDevice = XE::Library::SymbolT<XE::D3D12::PFN_D3D12_CREATE_DEVICE>( _RTX->m_d3d12Dll, "CreateDevice" );
	XE_ASSERT( NULL != XE::D3D12::CreateDevice && "Function CreateDevice not found." );

	XE::D3D12::GetDebugInterface = XE::Library::SymbolT<XE::D3D12::PFN_D3D12_GET_DEBUG_INTERFACE>( _RTX->m_d3d12Dll, "GetDebugInterface" );
	XE_ASSERT( NULL != XE::D3D12::GetDebugInterface && "Function GetDebugInterface not found." );

	XE::D3D12::SerializeRootSignature = XE::Library::SymbolT<XE::D3D12::PFN_D3D12_SERIALIZE_ROOT_SIGNATURE>( _RTX->m_d3d12Dll, "SerializeRootSignature" );
	XE_ASSERT( NULL != XE::D3D12::SerializeRootSignature && "Function SerializeRootSignature not found." );


	_RTX->m_dxgi.Init( Caps() );


	D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	HRESULT hr = E_FAIL;
	for( uint32_t ii = 0; ii < XE::countof( featureLevel ) && FAILED( hr ); ++ii )
	{
		hr = D3D12::CreateDevice( _RTX->m_dxgi._Adapter
								, featureLevel[ii]
								, D3D12::IID_ID3D12Device
								, ( void ** )&_RTX->m_device
		);

		if( FAILED( hr ) )
		{
			XE_LOG( XE::LoggerLevel::Warning, "Direct3D12 device feature level %1.%2.", ( featureLevel[ii] >> 12 ) & 0xf, ( featureLevel[ii] >> 8 ) & 0xf );
		}

		_RTX->m_featureLevel = featureLevel[ii];
	}

	_RTX->m_dxgi.Update( _RTX->m_device );

	{
		_RTX->m_deviceInterfaceVersion = 0;
		for( uint32_t ii = 0; ii < XE::countof( D3D12::s_d3dDeviceIIDs ); ++ii )
		{
			ID3D12Device * device;
			hr = _RTX->m_device->QueryInterface( D3D12::s_d3dDeviceIIDs[ii], ( void ** )&device );
			if( SUCCEEDED( hr ) )
			{
				device->Release();
				_RTX->m_deviceInterfaceVersion = XE::countof( D3D12::s_d3dDeviceIIDs ) - ii;
				break;
			}
		}
	}

	{
		uint32_t numNodes = _RTX->m_device->GetNodeCount();
		XE_LOG( XE::LoggerLevel::Message, "D3D12 GPU Architecture (num nodes: %1):", numNodes );
		for( uint32_t ii = 0; ii < numNodes; ++ii )
		{
			D3D12_FEATURE_DATA_ARCHITECTURE architecture;
			architecture.NodeIndex = ii;
			DX_CHECK( _RTX->m_device->CheckFeatureSupport( D3D12_FEATURE_ARCHITECTURE, &architecture, sizeof( architecture ) ) );

			XE_LOG( XE::LoggerLevel::Message, "\tNode %1: TileBasedRenderer %2, UMA %3, CacheCoherentUMA %4", ii, architecture.TileBasedRenderer, architecture.UMA, architecture.CacheCoherentUMA );

			if( 0 == ii )
			{
				std::memcpy( &_RTX->m_architecture, &architecture, sizeof( architecture ) );
			}
		}
	}

	DX_CHECK( _RTX->m_device->CheckFeatureSupport( D3D12_FEATURE_D3D12_OPTIONS, &_RTX->m_options, sizeof( _RTX->m_options ) ) );

	XE_LOG( XE::LoggerLevel::Message, "D3D12 options:" );
	XE_LOG( XE::LoggerLevel::Message, "\tTiledResourcesTier %1", _RTX->m_options.TiledResourcesTier );
	XE_LOG( XE::LoggerLevel::Message, "\tResourceBindingTier %1", _RTX->m_options.ResourceBindingTier );
	XE_LOG( XE::LoggerLevel::Message, "\tROVsSupported %1", _RTX->m_options.ROVsSupported );
	XE_LOG( XE::LoggerLevel::Message, "\tConservativeRasterizationTier %1", _RTX->m_options.ConservativeRasterizationTier );
	XE_LOG( XE::LoggerLevel::Message, "\tCrossNodeSharingTier %1", _RTX->m_options.CrossNodeSharingTier );
	XE_LOG( XE::LoggerLevel::Message, "\tResourceHeapTier %1", _RTX->m_options.ResourceHeapTier );

	D3D12::initHeapProperties( _RTX->m_device );

	_RTX->m_cmd.init( _RTX->m_device );
	_RTX->m_device->SetPrivateDataInterface( D3D12::IID_ID3D12CommandQueue, _RTX->m_cmd.m_commandQueue );


	_RTX->m_presentElapsed = 0;


	{
		_RTX->m_numWindows = 0;

		D3D12_DESCRIPTOR_HEAP_DESC rtvDescHeap;
		rtvDescHeap.NumDescriptors = XE::countof( _RTX->m_backBufferColor ) + GFX_MAX_FRAME_BUFFERS * GFX_MAX_ATTACHMENTS;
		rtvDescHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvDescHeap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		rtvDescHeap.NodeMask = 1;
		DX_CHECK( _RTX->m_device->CreateDescriptorHeap( &rtvDescHeap, D3D12::IID_ID3D12DescriptorHeap, ( void ** )&_RTX->m_rtvDescriptorHeap ) );

		D3D12_DESCRIPTOR_HEAP_DESC dsvDescHeap;
		dsvDescHeap.NumDescriptors = 1 + GFX_MAX_FRAME_BUFFERS;
		dsvDescHeap.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		dsvDescHeap.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		dsvDescHeap.NodeMask = 1;
		DX_CHECK( _RTX->m_device->CreateDescriptorHeap( &dsvDescHeap, D3D12::IID_ID3D12DescriptorHeap, ( void ** )&_RTX->m_dsvDescriptorHeap ) );

		for( uint32_t ii = 0; ii < XE::countof( _RTX->m_scratchBuffer ); ++ii )
		{
			_RTX->m_scratchBuffer[ii].create( GFX_MAX_DRAWCALLS * 1024, GFX_MAX_TEXTURES + GFX_MAX_SHADERS + GFX_MAX_DRAWCALLS );
		}
		_RTX->m_samplerAllocator.create( D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER, 1024, GFX_MAX_TEXTURE_SAMPLERS );

		D3D12_DESCRIPTOR_RANGE descRange[] =
		{
			{ D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER, GFX_MAX_TEXTURE_SAMPLERS, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
			{ D3D12_DESCRIPTOR_RANGE_TYPE_SRV,     GFX_MAX_TEXTURE_SAMPLERS, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
			{ D3D12_DESCRIPTOR_RANGE_TYPE_CBV,     1,                        0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
			{ D3D12_DESCRIPTOR_RANGE_TYPE_UAV,     GFX_MAX_TEXTURE_SAMPLERS, 0, 0, D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND },
		};

		D3D12_ROOT_PARAMETER rootParameter[] =
		{
			{ D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { { 1, &descRange[( XE::uint64 )D3D12::Rdt::SAMPLER] } }, D3D12_SHADER_VISIBILITY_ALL },
			{ D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { { 1, &descRange[( XE::uint64 )D3D12::Rdt::SRV]     } }, D3D12_SHADER_VISIBILITY_ALL },
			{ D3D12_ROOT_PARAMETER_TYPE_CBV,              { { 0, 0                                             } }, D3D12_SHADER_VISIBILITY_ALL },
			{ D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE, { { 1, &descRange[( XE::uint64 )D3D12::Rdt::UAV]     } }, D3D12_SHADER_VISIBILITY_ALL },
		};
		rootParameter[( XE::uint64 )D3D12::Rdt::CBV].Descriptor.RegisterSpace = 0;
		rootParameter[( XE::uint64 )D3D12::Rdt::CBV].Descriptor.ShaderRegister = 0;

		D3D12_ROOT_SIGNATURE_DESC descRootSignature;
		descRootSignature.NumParameters = XE::countof( rootParameter );
		descRootSignature.pParameters = rootParameter;
		descRootSignature.NumStaticSamplers = 0;
		descRootSignature.pStaticSamplers = NULL;
		descRootSignature.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		ID3DBlob * outBlob;
		ID3DBlob * errorBlob;
		DX_CHECK( D3D12::SerializeRootSignature( &descRootSignature
											   , D3D_ROOT_SIGNATURE_VERSION_1
											   , &outBlob
											   , &errorBlob
		) );

		DX_CHECK( _RTX->m_device->CreateRootSignature( 0, outBlob->GetBufferPointer(), outBlob->GetBufferSize(), D3D12::IID_ID3D12RootSignature, ( void ** )&_RTX->m_rootSignature ) );

		_RTX->m_directAccessSupport = PLATFORM_OS == OS_XBOX && _RTX->m_architecture.UMA;

		Caps().Supported |= XE::MakeFlags( XE::CapsFlag::NONE )
			| XE::CapsFlag::TEXTURE_3D
			| XE::CapsFlag::TEXTURE_COMPARE_ALL
			| XE::CapsFlag::INDEX32
			| XE::CapsFlag::INSTANCING
			| XE::CapsFlag::DRAW_INDIRECT
			| XE::CapsFlag::VERTEX_ATTRIB_HALF
			| XE::CapsFlag::VERTEX_ATTRIB_UINT10
			| XE::CapsFlag::VERTEX_ID
			| XE::CapsFlag::FRAGMENT_DEPTH
			| XE::CapsFlag::BLEND_INDEPENDENT
			| XE::CapsFlag::COMPUTE
			| ( _RTX->m_options.ROVsSupported ? XE::CapsFlag::FRAGMENT_ORDERING : XE::CapsFlag::NONE )
			| ( _RTX->m_directAccessSupport ? XE::CapsFlag::TEXTURE_DIRECT_ACCESS : XE::CapsFlag::NONE )
			| ( PLATFORM_OS == OS_WINDOWS ? XE::CapsFlag::SWAP_CHAIN : XE::CapsFlag::NONE )
			| XE::CapsFlag::TEXTURE_BLIT
			| XE::CapsFlag::TEXTURE_READ_BACK
			| XE::CapsFlag::OCCLUSION_QUERY
			| XE::CapsFlag::ALPHA_TO_COVERAGE
			| XE::CapsFlag::TEXTURE_2D_ARRAY
			| XE::CapsFlag::TEXTURE_CUBE_ARRAY
			| XE::CapsFlag::IMAGE_RW;

		Caps().Limits.MaxTextureSize = D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION;
		Caps().Limits.MaxTextureLayers = D3D12_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION;
		Caps().Limits.MaxFBAttachments = std::min<uint32_t>( 16, GFX_MAX_ATTACHMENTS );
		Caps().Limits.MaxComputeBindings = std::min<uint32_t>( D3D12_UAV_SLOT_COUNT, GFX_MAX_TEXTURE_SAMPLERS );
		Caps().Limits.MaxVertexStreams = 4;

		for( uint32_t ii = 0; ii < ( XE::uint64 )XE::TextureFormat::COUNT; ++ii )
		{
			XE::CapsFormatFlags support = XE::CapsFormatFlag::NONE;

			const DXGI_FORMAT fmt = ( XE::TextureFormat( ii ) > XE::TextureFormat::UNKNOWNDEPTH ) ? D3D12::s_textureFormat[ii].m_fmtDsv : D3D12::s_textureFormat[ii].m_fmt;
			const DXGI_FORMAT fmtSrgb = D3D12::s_textureFormat[ii].m_fmtSrgb;

			if( DXGI_FORMAT_UNKNOWN != fmt )
			{
				D3D12_FEATURE_DATA_FORMAT_SUPPORT data;
				data.Format = fmt;
				hr = _RTX->m_device->CheckFeatureSupport( D3D12_FEATURE_FORMAT_SUPPORT, &data, sizeof( data ) );
				if( SUCCEEDED( hr ) )
				{
					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_TEXTURE2D
														) )
						? XE::CapsFormatFlag::TEXTURE_2D
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_TEXTURE3D
														) )
						? XE::CapsFormatFlag::TEXTURE_3D
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_TEXTURECUBE
														) )
						? XE::CapsFormatFlag::TEXTURE_CUBE
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_BUFFER
														| D3D12_FORMAT_SUPPORT1_IA_VERTEX_BUFFER
														| D3D12_FORMAT_SUPPORT1_IA_INDEX_BUFFER
														) )
						? XE::CapsFormatFlag::TEXTURE_VERTEX
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_SHADER_LOAD
														) )
						? XE::CapsFormatFlag::TEXTURE_IMAGE_READ
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_RENDER_TARGET
														| D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL
														) )
						? XE::CapsFormatFlag::TEXTURE_FRAMEBUFFER
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET
														) )
						? XE::CapsFormatFlag::TEXTURE_FRAMEBUFFER_MSAA
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_MULTISAMPLE_LOAD
														) )
						? XE::CapsFormatFlag::TEXTURE_MSAA
						: XE::CapsFormatFlag::NONE
						;
				}

				if( ( support & XE::CapsFormatFlag::TEXTURE_IMAGE_READ ) != XE::CapsFormatFlag::NONE )
				{
					support &= ~XE::MakeFlags( XE::CapsFormatFlag::TEXTURE_IMAGE_READ );

					data.Format = D3D12::s_textureFormat[ii].m_fmt;
					hr = _RTX->m_device->CheckFeatureSupport( D3D12_FEATURE_FORMAT_SUPPORT, &data, sizeof( data ) );
					if( SUCCEEDED( hr ) )
					{
						support |= 0 != ( data.Support2 & ( 0
															| D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD
															) )
							? XE::CapsFormatFlag::TEXTURE_IMAGE_READ
							: XE::CapsFormatFlag::NONE
							;

						support |= 0 != ( data.Support2 & ( 0
															| D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE
															) )
							? XE::CapsFormatFlag::TEXTURE_IMAGE_WRITE
							: XE::CapsFormatFlag::NONE
							;
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

				D3D12_FEATURE_DATA_FORMAT_SUPPORT data;
				data.Format = fmtSrgb;
				hr = _RTX->m_device->CheckFeatureSupport( D3D12_FEATURE_FORMAT_SUPPORT, &data, sizeof( data ) );
				if( SUCCEEDED( hr ) )
				{
					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_TEXTURE2D
														) )
						? XE::CapsFormatFlag::TEXTURE_2D_SRGB
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_TEXTURE3D
														) )
						? XE::CapsFormatFlag::TEXTURE_3D_SRGB
						: XE::CapsFormatFlag::NONE
						;

					support |= 0 != ( data.Support1 & ( 0
														| D3D12_FORMAT_SUPPORT1_TEXTURECUBE
														) )
						? XE::CapsFormatFlag::TEXTURE_CUBE_SRGB
						: XE::CapsFormatFlag::NONE
						;
				}
			}

			Caps().SupportFormat[ii] = support;
		}

		_RTX->postReset();

		_RTX->m_gpuTimer.init();
		_RTX->m_occlusionQuery.init();

		{
			D3D12_INDIRECT_ARGUMENT_TYPE argType[] =
			{
				D3D12_INDIRECT_ARGUMENT_TYPE_DISPATCH,
				D3D12_INDIRECT_ARGUMENT_TYPE_DRAW,
				D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED,
			};

			D3D12_INDIRECT_ARGUMENT_DESC argDesc;
			std::memset( &argDesc, 0, sizeof( argDesc ) );

			for( uint32_t ii = 0; ii < XE::countof( _RTX->m_commandSignature ); ++ii )
			{
				argDesc.Type = argType[ii];
				D3D12_COMMAND_SIGNATURE_DESC commandSignatureDesc = { GFX_MAX_DRAW_INDIRECT_STRIDE, 1, &argDesc, 1 };

				_RTX->m_commandSignature[ii] = NULL;
				DX_CHECK( _RTX->m_device->CreateCommandSignature( &commandSignatureDesc, NULL, D3D12::IID_ID3D12CommandSignature, ( void ** )&_RTX->m_commandSignature[ii] ) );
			}
		}
	}
}

void XE::RendererContextD3D12::Shutdown()
{
	_RTX->m_cmd.finish();

	_RTX->preReset();

	_RTX->m_gpuTimer.shutdown();
	_RTX->m_occlusionQuery.shutdown();

	_RTX->m_samplerAllocator.destroy();

	for( uint32_t ii = 0; ii < XE::countof( _RTX->m_scratchBuffer ); ++ii )
	{
		_RTX->m_scratchBuffer[ii].destroy();
	}

	//_RTX->m_pipelineStateCache.invalidate();

	for( uint32_t ii = 0; ii < XE::countof( _RTX->m_indexBuffers ); ++ii )
	{
		_RTX->m_indexBuffers[ii].destroy();
	}

	for( uint32_t ii = 0; ii < XE::countof( _RTX->m_vertexBuffers ); ++ii )
	{
		_RTX->m_vertexBuffers[ii].destroy();
	}

	for( uint32_t ii = 0; ii < XE::countof( _RTX->m_shaders ); ++ii )
	{
		_RTX->m_shaders[ii].destroy();
	}

	for( uint32_t ii = 0; ii < XE::countof( _RTX->m_textures ); ++ii )
	{
		_RTX->m_textures[ii].destroy();
	}

	DX_RELEASE( _RTX->m_infoQueue );
	DX_RELEASE( _RTX->m_rtvDescriptorHeap );
	DX_RELEASE( _RTX->m_dsvDescriptorHeap );

	for( uint32_t ii = 0; ii < XE::countof( _RTX->m_commandSignature ); ++ii )
	{
		DX_RELEASE( _RTX->m_commandSignature[ii] );
	}

	DX_RELEASE( _RTX->m_rootSignature );
	DX_RELEASE( _RTX->m_msaaRt );
	DX_RELEASE( _RTX->m_swapChain );

	_RTX->m_device->SetPrivateDataInterface( D3D12::IID_ID3D12CommandQueue, NULL );
	_RTX->m_cmd.shutdown();

	DX_RELEASE( _RTX->m_device );

	_RTX->m_dxgi.Shutdown();

	XE::Library::Close( _RTX->m_winPixEvent );
	XE::Library::Close( _RTX->m_d3d12Dll );
	XE::Library::Close( _RTX->m_kernel32Dll );

	_RTX->m_winPixEvent = nullptr;
	_RTX->m_d3d12Dll = nullptr;
	_RTX->m_kernel32Dll = nullptr;
}

void XE::RendererContextD3D12::CreateShader( XE::ShaderHandle handle, XE::MemoryView data )
{
	_RTX->m_shaders[handle].create( data );
}

void XE::RendererContextD3D12::CreateProgram( XE::ProgramHandle handle )
{
	_RTX->m_program[handle].create( &_RTX->m_shaders[GetDesc( handle ).CS], &_RTX->m_shaders[GetDesc( handle ).VS] );
}

void XE::RendererContextD3D12::CreateTexture( XE::TextureHandle handle, XE::MemoryView data )
{
	_RTX->m_textures[handle].create( data, GetDesc( handle ).Flags, GetDesc( handle ).NumMips );
}

void XE::RendererContextD3D12::CreateFrameBuffer( XE::FrameBufferHandle handle )
{
	const auto & desc = GetDesc( handle );

	if( desc.Window )
	{
		_RTX->m_frameBuffers[handle].create( 0, ( void * )desc.Window.GetValue(), desc.Width, desc.Height, desc.ColorFormat, desc.DepthFormat );
	}
	else
	{
		_RTX->m_frameBuffers[handle].create( desc.AttachmentCount, desc.Attachments );
	}
}

void XE::RendererContextD3D12::CreateIndexBuffer( XE::IndexBufferHandle handle, XE::MemoryView data )
{
	_RTX->m_indexBuffers[handle].create( data.size(), ( void * )data.data(), GetDesc( handle ).Flags, false );
}

void XE::RendererContextD3D12::CreateVertexLayout( XE::VertexLayoutHandle handle )
{

}

void XE::RendererContextD3D12::CreateVertexBuffer( XE::VertexBufferHandle handle, XE::MemoryView data )
{
	_RTX->m_vertexBuffers[handle].create( data.size(), ( void * )data.data(), GetDesc( handle ).Layout, GetDesc( handle ).Flags );
}

void XE::RendererContextD3D12::CreateIndirectBuffer( XE::IndirectBufferHandle handle )
{

}

void XE::RendererContextD3D12::CreateOcclusionQuery( XE::OcclusionQueryHandle handle )
{

}

void XE::RendererContextD3D12::CreateDynamicIndexBuffer( XE::DynamicIndexBufferHandle handle )
{
	_RTX->m_indexBuffers[handle].create( GetDesc( handle ).Size, nullptr, GetDesc( handle ).Flags, false );
}

void XE::RendererContextD3D12::CreateDynamicVertexBuffer( XE::DynamicVertexBufferHandle handle )
{
	_RTX->m_vertexBuffers[handle].create( GetDesc( handle ).Size, nullptr, GetDesc( handle ).Layout, GetDesc( handle ).Flags );
}

void XE::RendererContextD3D12::ReadTexture( XE::TextureHandle handle, XE::uint8 * data, XE::uint8 mip )
{
	_RTX->m_textures[handle].overrideInternal( ( uintptr_t )data );

	const D3D12::Texture & texture = _RTX->m_textures[handle];

	D3D12_RESOURCE_DESC desc = D3D12::getResourceDesc( texture.m_ptr );

	D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
	uint32_t numRows;
	uint64_t total;
	_RTX->m_device->GetCopyableFootprints( &desc, mip, 1, 0, &layout, &numRows, NULL, &total );

	uint32_t srcPitch = layout.Footprint.RowPitch;

	ID3D12Resource * readback = D3D12::createCommittedResource( _RTX->m_device, D3D12::HeapProperty::Type::READBACK, total );

	uint32_t srcWidth = std::max< uint32_t>( 1, texture.m_width >> mip );
	uint32_t srcHeight = std::max< uint32_t>( 1, texture.m_height >> mip );

	D3D12_BOX box;
	box.left = 0;
	box.top = 0;
	box.right = srcWidth;
	box.bottom = srcHeight;
	box.front = 0;
	box.back = 1;

	D3D12_TEXTURE_COPY_LOCATION dstLocation = { readback,      D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,  { layout } };
	D3D12_TEXTURE_COPY_LOCATION srcLocation = { texture.m_ptr, D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, { } };
	srcLocation.SubresourceIndex = mip;
	_RTX->m_commandList->CopyTextureRegion( &dstLocation, 0, 0, 0, &srcLocation, &box );

	_RTX->finish();
	_RTX->m_commandList = _RTX->m_cmd.alloc();

	const uint8_t bpp = D3D12::s_imageBlockInfo[( XE::uint64 )texture.m_textureFormat].bitsPerPixel;
	uint8_t * dst = ( uint8_t * )data;
	uint32_t dstPitch = srcWidth * bpp / 8;

	uint32_t pitch = std::min< uint32_t>( srcPitch, dstPitch );

	uint8_t * src;
	readback->Map( 0, NULL, ( void ** )&src );

	for( uint32_t yy = 0, height = srcHeight; yy < height; ++yy )
	{
		std::memcpy( dst, src, pitch );

		src += srcPitch;
		dst += dstPitch;
	}

	D3D12_RANGE writeRange = { 0, 0 };
	readback->Unmap( 0, &writeRange );

	DX_RELEASE( readback );
}

void XE::RendererContextD3D12::UpdateTexture( const XE::UpdateTextureDesc & desc, XE::MemoryView data )
{
	_RTX->m_textures[desc.Handle].update( nullptr, desc.Side, desc.Mip, { desc.X, desc.Y, desc.Width, desc.Height }, desc.Z, desc.Depth, desc.Layer, data );
}

void XE::RendererContextD3D12::UpdateDynamicIndexBuffer( XE::DynamicIndexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	_RTX->m_indexBuffers[handle].update( nullptr, start, mem.size(), ( void * )mem.data() );
}

void XE::RendererContextD3D12::UpdateDynamicVertexBuffer( XE::DynamicVertexBufferHandle handle, XE::uint64 start, XE::MemoryView mem )
{
	_RTX->m_indexBuffers[handle].update( nullptr, start, mem.size(), ( void * )mem.data() );
}

void XE::RendererContextD3D12::DestroyShader( XE::ShaderHandle handle )
{
	_RTX->m_shaders[handle].destroy();
}

void XE::RendererContextD3D12::DestroyTexture( XE::TextureHandle handle )
{
	_RTX->m_textures[handle].destroy();
}

void XE::RendererContextD3D12::DestroyProgram( XE::ProgramHandle handle )
{
	_RTX->m_program[handle].destroy();
}

void XE::RendererContextD3D12::DestroyFrameBuffer( XE::FrameBufferHandle handle )
{
	_RTX->m_frameBuffers[handle].destroy();
}

void XE::RendererContextD3D12::DestroyIndexBuffer( XE::IndexBufferHandle handle )
{
	_RTX->m_indexBuffers[handle].destroy();
}

void XE::RendererContextD3D12::DestroyVertexLayout( XE::VertexLayoutHandle handle )
{

}

void XE::RendererContextD3D12::DestroyVertexBuffer( XE::VertexBufferHandle handle )
{
	_RTX->m_vertexBuffers[handle].destroy();
}

void XE::RendererContextD3D12::DestroyIndirectBuffer( XE::IndirectBufferHandle handle )
{

}

void XE::RendererContextD3D12::DestroyOcclusionQuery( XE::OcclusionQueryHandle handle )
{

}

void XE::RendererContextD3D12::DestroyDynamicIndexBuffer( XE::DynamicIndexBufferHandle handle )
{
	_RTX->m_indexBuffers[handle].destroy();
}

void XE::RendererContextD3D12::DestroyDynamicVertexBuffer( XE::DynamicVertexBufferHandle handle )
{
	_RTX->m_vertexBuffers[handle].destroy();
}

void XE::RendererContextD3D12::RequestScreenShot( XE::FrameBufferHandle handle, const std::string & userdata, ScreenShotCallbackType callback )
{
	uint32_t idx = ( _RTX->m_backBufferColorIdx - 1 ) % _RTX->m_scd.bufferCount;
	_RTX->m_cmd.finish( _RTX->m_backBufferColorFence[idx] );
	ID3D12Resource * backBuffer = _RTX->m_backBufferColor[idx];

	D3D12_RESOURCE_DESC desc = D3D12::getResourceDesc( backBuffer );

	const uint32_t width = ( uint32_t )desc.Width;
	const uint32_t height = ( uint32_t )desc.Height;

	D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
	uint32_t numRows;
	uint64_t total;
	uint64_t pitch;
	_RTX->m_device->GetCopyableFootprints( &desc
									 , 0
									 , 1
									 , 0
									 , &layout
									 , &numRows
									 , &pitch
									 , &total
	);

	ID3D12Resource * readback = D3D12::createCommittedResource( _RTX->m_device, D3D12::HeapProperty::Type::READBACK, total );

	D3D12_BOX box;
	box.left = 0;
	box.top = 0;
	box.right = width;
	box.bottom = height;
	box.front = 0;
	box.back = 1;

	D3D12::setResourceBarrier( _RTX->m_commandList, backBuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_COPY_SOURCE );
	D3D12_TEXTURE_COPY_LOCATION dst = { readback,   D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT,  { layout } };
	D3D12_TEXTURE_COPY_LOCATION src = { backBuffer, D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX, {} };
	_RTX->m_commandList->CopyTextureRegion( &dst, 0, 0, 0, &src, &box );
	D3D12::setResourceBarrier( _RTX->m_commandList, backBuffer, D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_PRESENT );
	_RTX->finish();
	_RTX->m_commandList = _RTX->m_cmd.alloc();

	void * data;
	readback->Map( 0, NULL, ( void ** )&data );

// 	bimg::imageSwizzleBgra8(
// 		data
// 		, layout.Footprint.RowPitch
// 		, width
// 		, height
// 		, data
// 		, layout.Footprint.RowPitch
// 	);
	
	callback( userdata.c_str(), width, height, layout.Footprint.RowPitch, ( const XE::uint8 * )data, total, false );

	D3D12_RANGE writeRange = { 0, 0 };
	readback->Unmap( 0, &writeRange );

	DX_RELEASE( readback );
}

#endif