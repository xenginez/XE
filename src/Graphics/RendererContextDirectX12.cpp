#include "RendererContextDirectX12.h"

#if PLATFORM_OS & ( OS_WINDOWS | OS_XBOX )

#if PLATFORM_OS == OS_XBOX
#include <d3d12_x.h>
#else
#include <d3d12.h>
#include <D3DX12/d3dx12.h>
#endif

#include "DXGI.h"

namespace XE::D3D12
{
	using DescriptorHeapHandle = XE::Handle< ID3D12DescriptorHeap >;

	static constexpr GUID IID_ID3D12CommandAllocator = { 0x6102dee4, 0xaf59, 0x4b09, { 0xb9, 0x99, 0xb4, 0x4d, 0x73, 0xf0, 0x9b, 0x24 } };
	static constexpr GUID IID_ID3D12CommandQueue = { 0x0ec870a6, 0x5d7e, 0x4c22, { 0x8c, 0xfc, 0x5b, 0xaa, 0xe0, 0x76, 0x16, 0xed } };
	static constexpr GUID IID_ID3D12CommandSignature = { 0xc36a797c, 0xec80, 0x4f0a, { 0x89, 0x85, 0xa7, 0xb2, 0x47, 0x50, 0x82, 0xd1 } };
	static constexpr GUID IID_ID3D12Debug = { 0x344488b7, 0x6846, 0x474b, { 0xb9, 0x89, 0xf0, 0x27, 0x44, 0x82, 0x45, 0xe0 } };
	static constexpr GUID IID_ID3D12Debug1 = { 0xaffaa4ca, 0x63fe, 0x4d8e, { 0xb8, 0xad, 0x15, 0x90, 0x00, 0xaf, 0x43, 0x04 } };
	static constexpr GUID IID_ID3D12DescriptorHeap = { 0x8efb471d, 0x616c, 0x4f49, { 0x90, 0xf7, 0x12, 0x7b, 0xb7, 0x63, 0xfa, 0x51 } };
	static constexpr GUID IID_ID3D12Device = { 0x189819f1, 0x1db6, 0x4b57, { 0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7 } };
	static constexpr GUID IID_ID3D12Device1 = { 0x77acce80, 0x638e, 0x4e65, { 0x88, 0x95, 0xc1, 0xf2, 0x33, 0x86, 0x86, 0x3e } };
	static constexpr GUID IID_ID3D12Device2 = { 0x30baa41e, 0xb15b, 0x475c, { 0xa0, 0xbb, 0x1a, 0xf5, 0xc5, 0xb6, 0x43, 0x28 } };
	static constexpr GUID IID_ID3D12Device3 = { 0x81dadc15, 0x2bad, 0x4392, { 0x93, 0xc5, 0x10, 0x13, 0x45, 0xc4, 0xaa, 0x98 } };
	static constexpr GUID IID_ID3D12Device4 = { 0xe865df17, 0xa9ee, 0x46f9, { 0xa4, 0x63, 0x30, 0x98, 0x31, 0x5a, 0xa2, 0xe5 } };
	static constexpr GUID IID_ID3D12Device5 = { 0x8b4f173b, 0x2fea, 0x4b80, { 0x8f, 0x58, 0x43, 0x07, 0x19, 0x1a, 0xb9, 0x5d } };
	static constexpr GUID IID_ID3D12Fence = { 0x0a753dcf, 0xc4d8, 0x4b91, { 0xad, 0xf6, 0xbe, 0x5a, 0x60, 0xd9, 0x5a, 0x76 } };
	static constexpr GUID IID_ID3D12GraphicsCommandList = { 0x5b160d0f, 0xac1b, 0x4185, { 0x8b, 0xa8, 0xb3, 0xae, 0x42, 0xa5, 0xa4, 0x55 } };
	static constexpr GUID IID_ID3D12GraphicsCommandList1 = { 0x553103fb, 0x1fe7, 0x4557, { 0xbb, 0x38, 0x94, 0x6d, 0x7d, 0x0e, 0x7c, 0xa7 } };
	static constexpr GUID IID_ID3D12GraphicsCommandList2 = { 0x38C3E585, 0xFF17, 0x412C, { 0x91, 0x50, 0x4F, 0xC6, 0xF9, 0xD7, 0x2A, 0x28 } };
	static constexpr GUID IID_ID3D12GraphicsCommandList3 = { 0x6FDA83A7, 0xB84C, 0x4E38, { 0x9A, 0xC8, 0xC7, 0xBD, 0x22, 0x01, 0x6B, 0x3D } };
	static constexpr GUID IID_ID3D12GraphicsCommandList4 = { 0x8754318e, 0xd3a9, 0x4541, { 0x98, 0xcf, 0x64, 0x5b, 0x50, 0xdc, 0x48, 0x74 } };
	static constexpr GUID IID_ID3D12InfoQueue = { 0x0742a90b, 0xc387, 0x483f, { 0xb9, 0x46, 0x30, 0xa7, 0xe4, 0xe6, 0x14, 0x58 } };
	static constexpr GUID IID_ID3D12PipelineState = { 0x765a30f3, 0xf624, 0x4c6f, { 0xa8, 0x28, 0xac, 0xe9, 0x48, 0x62, 0x24, 0x45 } };
	static constexpr GUID IID_ID3D12Resource = { 0x696442be, 0xa72e, 0x4059, { 0xbc, 0x79, 0x5b, 0x5c, 0x98, 0x04, 0x0f, 0xad } };
	static constexpr GUID IID_ID3D12RootSignature = { 0xc54a6b66, 0x72df, 0x4ee8, { 0x8b, 0xe5, 0xa9, 0x46, 0xa1, 0x42, 0x92, 0x14 } };
	static constexpr GUID IID_ID3D12QueryHeap = { 0x0d9658ae, 0xed45, 0x469e, { 0xa6, 0x1d, 0x97, 0x0e, 0xc5, 0x83, 0xca, 0xb4 } };

	class ScratchBuffer
	{
	public:
		void create( XE::uint32 _size, XE::uint32 _maxDescriptors );
		void destroy();
		void reset( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle );

		void  allocEmpty( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle );

		void * allocCbv( D3D12_GPU_VIRTUAL_ADDRESS & _gpuAddress, XE::uint32 _size );

		void  allocSrv( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, struct TextureD3D12 & _texture, XE::uint8 _mip = 0 );
		void  allocSrv( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, struct BufferD3D12 & _buffer );

		void  allocUav( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, struct TextureD3D12 & _texture, XE::uint8 _mip = 0 );
		void  allocUav( D3D12_GPU_DESCRIPTOR_HANDLE & _gpuHandle, struct BufferD3D12 & _buffer );

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
	class DescriptorAllocator
	{
	public:
		void create( D3D12_DESCRIPTOR_HEAP_TYPE _type, XE::uint16 _maxDescriptors, XE::uint16 _numDescriptorsPerBlock = 1 );
		void destroy();

		XE::uint16 alloc( ID3D12Resource * _ptr, const D3D12_SHADER_RESOURCE_VIEW_DESC * _desc );
		XE::uint16 alloc( const XE::uint32 * _flags, XE::uint32 _num, const float _palette[][4] );
		void free( XE::uint16 _handle );
		void reset();

		D3D12_GPU_DESCRIPTOR_HANDLE get( XE::uint16 _handle );

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
		void create( XE::uint32 _size, void * _data, XE::uint16 _flags, bool _vertex, XE::uint32 _stride = 0 );
		void update( ID3D12GraphicsCommandList * _commandList, XE::uint32 _offset, XE::uint32 _size, void * _data, bool _discard = false );
		void destroy();

		D3D12_RESOURCE_STATES setState( ID3D12GraphicsCommandList * _commandList, D3D12_RESOURCE_STATES _state );

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource * m_ptr;
		D3D12_GPU_VIRTUAL_ADDRESS m_gpuVA;
		D3D12_RESOURCE_STATES m_state;
		XE::uint32 m_size;
		XE::uint16 m_flags;
		bool m_dynamic;
	};
	class VertexBuffer
	{
		void create( XE::uint32 _size, void * _data, XE::VertexLayoutHandle _layoutHandle, XE::uint16 _flags );

		XE::VertexLayoutHandle m_layoutHandle;
	};
	class Shader
	{
	public:
		void create( XE::MemoryView _mem );

		void destroy();

		const XE::MemoryView m_code;

// 		UniformBuffer * m_constantBuffer;
// 		PredefinedUniform m_predefined[PredefinedUniform::Count];
// 		XE::uint16 m_attrMask[Attrib::Count];

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
		void update( ID3D12GraphicsCommandList * _commandList, XE::uint8 _side, XE::uint8 _mip, const XE::Rectf & _rect, XE::uint16 _z, XE::uint16 _depth, XE::uint16 _pitch, const XE::MemoryView _mem );
		void resolve( ID3D12GraphicsCommandList * _commandList, XE::uint8 _resolve );
		D3D12_RESOURCE_STATES setState( ID3D12GraphicsCommandList * _commandList, D3D12_RESOURCE_STATES _state );

		D3D12_SHADER_RESOURCE_VIEW_DESC  m_srvd;
		D3D12_UNORDERED_ACCESS_VIEW_DESC m_uavd;
		ID3D12Resource * m_ptr;
		ID3D12Resource * m_singleMsaa;
		void * m_directAccessPtr;
		D3D12_RESOURCE_STATES m_state;
		XE::uint64 m_flags;
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
		void clear( ID3D12GraphicsCommandList * _commandList, const XE::ClearFlags & _clear, const float _palette[][4], const D3D12_RECT * _rect = NULL, XE::uint32 _num = 0 );
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

		ID3D12CommandQueue * m_commandQueue;
		XE::uint64 m_currentFence;
		XE::uint64 m_completedFence;
		ID3D12Fence * m_fence;
		CommandList m_commandList[256];
		//bx::RingBufferControl m_control;
		XE::Array<ID3D12Resource *> m_release[256];
	};
	class TimerQuery
	{
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
		//bx::RingBufferControl m_control;
	};
	class OcclusionQuery
	{
		void init();
		void shutdown();
		void begin( ID3D12GraphicsCommandList * _commandList, XE::RenderFrame * _render, OcclusionQueryHandle _handle );
		void end( ID3D12GraphicsCommandList * _commandList );
		void invalidate( OcclusionQueryHandle _handle );

		ID3D12Resource * m_readback;
		ID3D12QueryHeap * m_queryHeap;
		OcclusionQueryHandle m_handle[GFX_MAX_OCCLUSION];
		XE::uint64 * m_result;
		//bx::RingBufferControl m_control;
	};
	class RenderContext
	{
		DXGI m_dxgi;

		void * m_kernel32Dll;
		void * m_d3d12Dll;
		void * m_renderDocDll;
		void * m_winPixEvent;

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

//		XE::VertexLayout m_vertexLayouts[GFX_MAX_VERTEX_LAYOUTS];

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

	XE::D3D12::RenderContext * _RTX = nullptr;
}

XE::RendererContextDirectX12::RendererContextDirectX12()
{

}

XE::RendererContextDirectX12::~RendererContextDirectX12()
{

}

void XE::RendererContextDirectX12::OnRender( XE::RenderFrame * val )
{

}

#endif