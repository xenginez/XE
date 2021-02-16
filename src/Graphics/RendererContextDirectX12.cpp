#include "RendererContextDirectX12.h"

#if PLATFORM_OS & (OS_WINDOWS | OS_XBOX)

#if PLATFORM_OS == OS_XBOX
#include <d3d12_x.h>
#else
#include <d3d12.h>
#include <D3DX12/d3dx12.h>
#endif

BEG_XE_NAMESPACE

namespace D3D12
{
	class ScratchBuffer
	{ };
	class DescriptorAllocator
	{ };
	class Buffer
	{ };
	class VertexBuffer
	{ };
	class Shader
	{ };
	class Program
	{ };
	class Texture
	{ };
	class FrameBuffer
	{ };
	class CommandQueue
	{ };
	class Batch
	{ };
	class TimerQuery
	{ };
	class OcclusionQuery
	{ };
	class RenderContext
	{ };
}

XE::D3D12::RenderContext * _RTX = nullptr;

namespace D3D12
{

}

END_XE_NAMESPACE

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