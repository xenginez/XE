#include "RendererContextDirectX11.h"
#if PLATFORM_OS & (OS_WINDOWS)

#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <d3dcommon.h>

#pragma comment( lib, "dxgi.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxguid.lib" )

#include "Utils/Logger.h"

BEG_XE_NAMESPACE
namespace D3D11
{
	struct Buffer
	{

	};
	typedef Buffer IndexBuffer;
	struct VertexBuffer : public Buffer
	{

	};
	struct Shader
	{

	};
	struct Program
	{

	};
	struct IntelDirectAccessResourceDescriptor
	{

	};
	struct DirectAccessResource
	{

	};
	struct Texture
	{

	};
	struct FrameBuffer
	{

	};
	struct TimerQuery
	{

	};
	struct OcclusionQuery
	{

	};

}
END_XE_NAMESPACE

struct XE::RendererContextDirectX11::Private
{

};

XE::RendererContextDirectX11::RendererContextDirectX11()
{

}

XE::RendererContextDirectX11::~RendererContextDirectX11()
{

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

}

void XE::RendererContextDirectX11::Shutdown( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateProgram( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateFrameBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateVertexLayout( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateOcclusionQuery( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateIndirectBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateShader( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateTexture( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateIndexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateVertexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateDynamicIndexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::CreateDynamicVertexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::ReadTexture( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::UpdateTexture( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::RequestScreenShot( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::UpdateDynamicIndexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::UpdateDynamicVertexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryShader( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryProgram( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryTexture( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryFrameBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryIndexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryVertexLayout( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryVertexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryIndirectBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryOcclusionQuery( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryDynamicIndexBuffer( XE::RenderFrame * frame )
{

}

void XE::RendererContextDirectX11::DestoryDynamicVertexBuffer( XE::RenderFrame * frame )
{

}

#endif
