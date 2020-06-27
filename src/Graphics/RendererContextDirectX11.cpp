#include "RendererContextDirectX11.h"
#if PLATFORM_OS & (OS_WINDOWS)

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <d3dcommon.h>

#include "Structs.h"

#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxguid.lib" )
#pragma comment( lib, "d3dcompiler.lib" )

#define XE_CHECK( __X ) \
if( FAILED( __X ) ) \
{ \
	XE_ASSERT( false && #__X ); \
}

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

struct BufferD3D11
{
public:
	void create( ID3D11Device * device, XE::memory_view data, XE::Flags<XE::BufferFlags> flags, bool vertex = false )
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

	void update( ID3D11Device * device, ID3D11DeviceContext * deviceCtx, XE::uint32 offset, XE::memory_view data, bool discard = false )
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
	union
	{
		ID3D11ComputeShader * _ComputeShader;
		ID3D11PixelShader * _PixelShader;
		ID3D11VertexShader * _VertexShader;
		ID3D11DeviceChild * _Ptr;
	};

	XE::memory_view _Code;
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
	}

	const ShaderD3D11 * VS;
	const ShaderD3D11 * FS;
	XE::uint16 _NumPredefinedUniform;
	XE::PredefinedUniform PredefinedUniform[XE::PredefinedUniform::Type::COUNT * 2];
};
struct FrameBufferD3D11
{};
struct IndexBufferD3D11 : public BufferD3D11
{};
struct VertexBufferD3D11 : public BufferD3D11
{
public:
	void create( ID3D11Device * device, XE::memory_view data, XE::VertexLayoutHandle layoutHandle, XE::Flags<XE::BufferFlags> flags, uint16_t stride )
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
	enum Enum
	{
		Texture2D,
		Texture3D,
		TextureCube,
	};

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

	ID3D11ShaderResourceView * _SRV;
	ID3D11UnorderedAccessView * _UAV;
	XE::uint64 _Flags;
	XE::uint32 _Width;
	XE::uint32 _Height;
	XE::uint32 _Depth;
	XE::uint32 _NumLayers;
	XE::uint8  _Type;
	XE::uint8  _RequestedFormat;
	XE::uint8  _TextureFormat;
	XE::uint8  _NumMips;
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
			EXEC_RENDERER_INIT();
			break;
		case XE::CommandType::RENDERER_SHUTDOWN:
			EXEC_RENDERER_SHUTDOWN();
			break;
		case XE::CommandType::CREATE_VERTEX_LAYOUT:
			EXEC_CREATE_VERTEX_LAYOUT();
			break;
		case XE::CommandType::CREATE_INDEX_BUFFER:
			EXEC_CREATE_INDEX_BUFFER();
			break;
		case XE::CommandType::CREATE_VERTEX_BUFFER:
			EXEC_CREATE_VERTEX_BUFFER();
			break;
		case XE::CommandType::CREATE_DYNAMIC_INDEX_BUFFER:
			EXEC_CREATE_DYNAMIC_INDEX_BUFFER();
			break;
		case XE::CommandType::UPDATE_DYNAMIC_INDEX_BUFFER:
			EXEC_UPDATE_DYNAMIC_INDEX_BUFFER();
			break;
		case XE::CommandType::CREATE_DYNAMIC_VERTEX_BUFFER:
			EXEC_CREATE_DYNAMIC_VERTEX_BUFFER();
			break;
		case XE::CommandType::UPDATE_DYNAMIC_VERTEX_BUFFER:
			EXEC_UPDATE_DYNAMIC_VERTEX_BUFFER();
			break;
		case XE::CommandType::CREATE_TRANSIENT_INDEX_BUFFER:
			EXEC_CREATE_TRANSIENT_INDEX_BUFFER();
			break;
		case XE::CommandType::CREATE_TRANSIENT_VERTEX_BUFFER:
			EXEC_CREATE_TRANSIENT_VERTEX_BUFFER();
			break;
		case XE::CommandType::CREATE_SHADER:
			EXEC_CREATE_SHADER();
			break;
		case XE::CommandType::CREATE_PROGRAM:
			EXEC_CREATE_PROGRAM();
			break;
		case XE::CommandType::CREATE_TEXTURE:
			EXEC_CREATE_TEXTURE();
			break;
		case XE::CommandType::UPDATE_TEXTURE:
			EXEC_UPDATE_TEXTURE();
			break;
		case XE::CommandType::RESIZE_TEXTURE:
			EXEC_RESIZE_TEXTURE();
			break;
		case XE::CommandType::CREATE_FRAME_BUFFER:
			EXEC_CREATE_FRAME_BUFFER();
			break;
		case XE::CommandType::CREATE_UNIFORM:
			EXEC_CREATE_UNIFORM();
			break;
		case XE::CommandType::CREATE_OCCLUSION_QUERY:
			EXEC_CREATE_OCCLUSION_QUERY();
			break;
		case XE::CommandType::END:
			EXEC_END();
			break;
		case XE::CommandType::DESTROY_VERTEX_LAYOUT:
			EXEC_DESTROY_VERTEX_LAYOUT();
			break;
		case XE::CommandType::DESTROY_INDEX_BUFFER:
			EXEC_DESTROY_INDEX_BUFFER();
			break;
		case XE::CommandType::DESTROY_VERTEX_BUFFER:
			EXEC_DESTROY_VERTEX_BUFFER();
			break;
		case XE::CommandType::DESTROY_DYNAMIC_INDEX_BUFFER:
			EXEC_DESTROY_DYNAMIC_INDEX_BUFFER();
			break;
		case XE::CommandType::DESTROY_DYNAMIC_VERTEX_BUFFER:
			EXEC_DESTROY_DYNAMIC_VERTEX_BUFFER();
			break;
		case XE::CommandType::DESTROY_SHADER:
			EXEC_DESTROY_SHADER();
			break;
		case XE::CommandType::DESTROY_PROGRAM:
			EXEC_DESTROY_PROGRAM();
			break;
		case XE::CommandType::DESTROY_TEXTURE:
			EXEC_DESTROY_TEXTURE();
			break;
		case XE::CommandType::DESTROY_FRAMEBUFFER:
			EXEC_DESTROY_FRAMEBUFFER();
			break;
		case XE::CommandType::DESTROY_UNIFORM:
			EXEC_DESTROY_UNIFORM();
			break;
		case XE::CommandType::READ_TEXTURE:
			EXEC_READ_TEXTURE();
			break;
		case XE::CommandType::DESTROY_OCCLUSION_QUERY:
			EXEC_DESTROY_OCCLUSION_QUERY();
			break;
		case XE::CommandType::REQUEST_SCREEN_SHOT:
			EXEC_REQUEST_SCREEN_SHOT();
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

void XE::RendererContextDirectX11::EXEC_RENDERER_INIT()
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

void XE::RendererContextDirectX11::EXEC_RENDERER_SHUTDOWN()
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

void XE::RendererContextDirectX11::EXEC_CREATE_VERTEX_LAYOUT()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_INDEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_VERTEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_DYNAMIC_INDEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_UPDATE_DYNAMIC_INDEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_DYNAMIC_VERTEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_UPDATE_DYNAMIC_VERTEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_TRANSIENT_INDEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_TRANSIENT_VERTEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_SHADER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_PROGRAM()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_TEXTURE()
{

}

void XE::RendererContextDirectX11::EXEC_UPDATE_TEXTURE()
{

}

void XE::RendererContextDirectX11::EXEC_RESIZE_TEXTURE()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_FRAME_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_UNIFORM()
{

}

void XE::RendererContextDirectX11::EXEC_CREATE_OCCLUSION_QUERY()
{

}

void XE::RendererContextDirectX11::EXEC_END()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_VERTEX_LAYOUT()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_INDEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_VERTEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_DYNAMIC_INDEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_DYNAMIC_VERTEX_BUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_SHADER()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_PROGRAM()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_TEXTURE()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_FRAMEBUFFER()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_UNIFORM()
{

}

void XE::RendererContextDirectX11::EXEC_READ_TEXTURE()
{

}

void XE::RendererContextDirectX11::EXEC_DESTROY_OCCLUSION_QUERY()
{

}

void XE::RendererContextDirectX11::EXEC_REQUEST_SCREEN_SHOT()
{

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