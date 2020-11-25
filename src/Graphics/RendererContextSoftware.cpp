#include "RendererContextSoftware.h"

#include <tbb/parallel_for.h>

struct PTriangle
{

};

struct XE::RendererContextSoftware::Private
{
	std::array<XE::uint8 *, GFX_MAX_SHADERS> _Shaders;
	std::array<XE::uint8 *, GFX_MAX_TEXTURES> _Textures;
	std::array<XE::uint8 *, GFX_MAX_INDEX_BUFFERS> _IndexBuffers;
	std::array<XE::uint8 *, GFX_MAX_VERTEX_BUFFERS> _VertexBuffers;
	std::array<XE::uint8 *, GFX_MAX_INDEX_BUFFERS> _DynamicIndexBuffers;
	std::array<XE::uint8 *, GFX_MAX_VERTEX_BUFFERS> _DynamicVertexBuffers;
	std::array<XE::uint8 *, GFX_MAX_DRAW_INDIRECT_BUFFERS> _IndirectBuffers;

	XE::Array<XE::OcclusionQueryHandle> _Occlusions;
};

XE::RendererContextSoftware::RendererContextSoftware()
	:_p( new Private )
{

}

XE::RendererContextSoftware::~RendererContextSoftware()
{
	delete _p;
}

void XE::RendererContextSoftware::OnRender( XE::RenderFrame * frame )
{
	bool cmd_exit = false;
	while( cmd_exit )
	{
		XE::CommandType cmd = XE::CommandType::END;
		frame->PrevCmd.Read( cmd );

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
		default:
			break;
		}
	}

	XE::Array<XE::uint64> keys( XE::MemoryResource::GetStackMemoryResource() );
	keys.resize( frame->RenderItemSize );
	for( XE::uint64 i = 0; i < keys.size(); ++i ) { keys[i] = i; };
	std::sort( frame->RenderItemKeys.begin(), frame->RenderItemKeys.begin() + frame->RenderItemSize, [frame]( XE::uint64 left, XE::uint64 right )
			   {
				   return frame->RenderItemKeys[left] < frame->RenderItemKeys[right];
			   } );
	for( XE::uint64 i = 0; i < keys.size(); ++i )
	{
		switch( frame->RenderItems[keys[i]].Type )
		{
		case XE::RenderItem::ItemType::BLIT:
			BlitCall( frame, ( ( XE::RenderBlit * )frame->RenderItems[keys[i]].Data ) );
			break;
		case XE::RenderItem::ItemType::DRAW:
			DrawCall( frame, ( ( XE::RenderDraw * )frame->RenderItems[keys[i]].Data ), &frame->RenderBinds[keys[i]] );
			break;
		case XE::RenderItem::ItemType::COMPUTE:
			ComputeCall( frame, ( ( XE::RenderCompute * )frame->RenderItems[keys[i]].Data ), &frame->RenderBinds[keys[i]] );
			break;
		default:
			break;
		}
	}

	cmd_exit = false;
	while( cmd_exit )
	{
		XE::CommandType cmd = XE::CommandType::END;
		frame->PostCmd.Read( cmd );

		switch( cmd )
		{
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
		case XE::CommandType::END:
			cmd_exit = true;
			break;
		default:
			break;
		}
	}
}

void XE::RendererContextSoftware::Init( XE::RenderFrame * frame )
{
	for( auto & it : _p->_Shaders ) it = nullptr;
	for( auto & it : _p->_Textures ) it = nullptr;
	for( auto & it : _p->_IndexBuffers ) it = nullptr;
	for( auto & it : _p->_VertexBuffers ) it = nullptr;
	for( auto & it : _p->_IndirectBuffers ) it = nullptr;
	for( auto & it : _p->_DynamicIndexBuffers ) it = nullptr;
	for( auto & it : _p->_DynamicVertexBuffers ) it = nullptr;

	XE::CapsInfo caps;



	SetCaps( caps );
}

void XE::RendererContextSoftware::Shutdown( XE::RenderFrame * frame )
{
	_p->_Occlusions.clear();

	for( auto it : _p->_Shaders ) delete it;
	for( auto it : _p->_Textures ) delete it;
	for( auto it : _p->_IndexBuffers ) delete it;
	for( auto it : _p->_VertexBuffers ) delete it;
	for( auto it : _p->_IndirectBuffers ) delete it;
	for( auto it : _p->_DynamicIndexBuffers ) delete it;
	for( auto it : _p->_DynamicVertexBuffers ) delete it;
}

void XE::RendererContextSoftware::BlitCall( XE::RenderFrame * frame, XE::RenderBlit * item )
{
	XE::uint8 * src = _p->_Textures[item->Src];
	XE::uint8 * dst = _p->_Textures[item->Dst];


}

void XE::RendererContextSoftware::DrawCall( XE::RenderFrame * frame, XE::RenderDraw * item, XE::RenderBind * bind )
{
	// vertex data
	XE::Array<PTriangle> triangles( XE::MemoryResource::GetStackMemoryResource() );

	// iter triangle
	tbb::parallel_for( XE::uint64( 0 ), XE::uint64( triangles.size() ), XE::uint64( 1 ), [this, frame, item, bind]( XE::uint64 i )
					   {
						   // vertex shader
						   if( GetDesc( item->Program ).CS )
						   {

						   }

						   // rasterization
						   {

						   }

						   // mesh shader

						   // fragment shader
						   if( GetDesc( item->Program ).FS )
						   {

						   }

						   // test and blend
						   {

						   }
					   } );
}

void XE::RendererContextSoftware::ComputeCall( XE::RenderFrame * frame, XE::RenderCompute * item, XE::RenderBind * bind )
{
	tbb::parallel_for( XE::uint64( 0 ), XE::uint64( item->NumX * item->NumY * item->NumZ ), XE::uint64( 1 ), [this, frame, item, bind]( XE::uint64 i )
					   {
						   if( GetDesc( item->Program ).CS )
						   {

						   }
					   } );
}

void XE::RendererContextSoftware::CreateProgram( XE::RenderFrame * frame )
{
	( void )( 0 );
}

void XE::RendererContextSoftware::CreateFrameBuffer( XE::RenderFrame * frame )
{
	XE::FrameBufferHandle handle;
	frame->PrevCmd.Read( handle );

	( void )( handle );
}

void XE::RendererContextSoftware::CreateVertexLayout( XE::RenderFrame * frame )
{
	XE::VertexLayoutHandle handle;
	frame->PrevCmd.Read( handle );

	( void )( handle );
}

void XE::RendererContextSoftware::CreateOcclusionQuery( XE::RenderFrame * frame )
{
	XE::OcclusionQueryHandle handle;
	frame->PrevCmd.Read( handle );

	_p->_Occlusions.push_back( handle );
}

void XE::RendererContextSoftware::CreateIndirectBuffer( XE::RenderFrame * frame )
{
	XE::IndirectBufferHandle handle;
	frame->PrevCmd.Read( handle );

	const XE::IndirectBufferDesc & desc = GetDesc( handle );

	_p->_IndirectBuffers[handle] = new XE::uint8[desc.Size];
}

void XE::RendererContextSoftware::CreateShader( XE::RenderFrame * frame )
{
	XE::ShaderHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView data;
	frame->PrevCmd.Read( data );

	_p->_Shaders[handle] = new XE::uint8[data.size()];

	std::memcpy( _p->_Shaders[handle], data.data(), data.size() );
}

void XE::RendererContextSoftware::CreateTexture( XE::RenderFrame * frame )
{
	XE::TextureHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView data;
	frame->PrevCmd.Read( data );

	const XE::TextureDesc & desc = GetDesc( handle );

	_p->_Textures[handle] = new XE::uint8[desc.Width * desc.Height * desc.Depth];

	if( data.size() )
	{
		std::memcpy( _p->_Textures[handle], data.data(), data.size() );
	}
}

void XE::RendererContextSoftware::CreateIndexBuffer( XE::RenderFrame * frame )
{
	XE::IndexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView data;
	frame->PrevCmd.Read( data );

	const XE::IndexBufferDesc & desc = GetDesc( handle );

	_p->_IndexBuffers[handle] = new XE::uint8[desc.Size];

	if( data.size() )
	{
		std::memcpy( _p->_IndexBuffers[handle], data.data(), data.size() );
	}
}

void XE::RendererContextSoftware::CreateVertexBuffer( XE::RenderFrame * frame )
{
	XE::VertexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView data;
	frame->PrevCmd.Read( data );

	const XE::VertexBufferDesc & desc = GetDesc( handle );

	_p->_VertexBuffers[handle] = new XE::uint8[desc.Size];

	if( data.size() )
	{
		std::memcpy( _p->_VertexBuffers[handle], data.data(), data.size() );
	}
}

void XE::RendererContextSoftware::CreateDynamicIndexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicIndexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView data;
	frame->PrevCmd.Read( data );

	const XE::DynamicIndexBufferDesc & desc = GetDesc( handle );

	_p->_DynamicIndexBuffers[handle] = new XE::uint8[desc.Size];

	if( data.size() )
	{
		std::memcpy( _p->_DynamicIndexBuffers[handle], data.data(), data.size() );
	}
}

void XE::RendererContextSoftware::CreateDynamicVertexBuffer( XE::RenderFrame * frame )
{
	XE::DynamicVertexBufferHandle handle;
	frame->PrevCmd.Read( handle );
	XE::MemoryView data;
	frame->PrevCmd.Read( data );

	const XE::DynamicVertexBufferDesc & desc = GetDesc( handle );

	_p->_DynamicVertexBuffers[handle] = new XE::uint8[desc.Size];

	if( data.size() )
	{
		std::memcpy( _p->_DynamicVertexBuffers[handle], data.data(), data.size() );
	}
}
