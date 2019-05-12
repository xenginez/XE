#include "RenderPass.h"

#include "GFX.h"
#include "FrameBuffer.h"

#define MAX_RENDER_PASSES 1024

USING_XE

BEGIN_META(RenderPass)
END_META()

ViewHandle& get_counter()
{
	static ViewHandle id = 0;
	return id;
}

ViewHandle generate_id()
{
	auto& counter = get_counter();
	if ( counter == MAX_RENDER_PASSES - 1 )
	{
		GFX::Frame();
		counter = 0;
	}
	ViewHandle idx = counter++;

	return idx;
}

XE::RenderPass::RenderPass()
{

}

XE::RenderPass::RenderPass( const String& n )
{
	_Handle = generate_id();
	
	GFX::ResetView(_Handle);
	GFX::SetViewName(_Handle, n);
}

XE::RenderPass::~RenderPass()
{

}

XE::ViewHandle XE::RenderPass::GetHandle() const
{
	return _Handle;
}

void XE::RenderPass::Bind( FrameBufferPtr fb /*= nullptr */ ) const
{
	GFX::SetViewMode(_Handle, ViewMode::Sequential);

	if ( fb != nullptr )
	{
		const auto width = fb->GetWidth();
		const auto height = fb->GetHeight();
		GFX::SetViewRect(_Handle, uint16(0), uint16(0), uint16(width), uint16(height));
		GFX::SetViewScissor(_Handle, uint16(0), uint16(0), uint16(width), uint16(height));
		
		GFX::SetViewFrameBuffer(_Handle, fb->GetHandle());
	}
	else
	{
		GFX::SetViewFrameBuffer(_Handle, FrameBufferHandle());
	}

	Touch();
}

void XE::RenderPass::Touch() const
{
	GFX::Touch(_Handle);
}

void XE::RenderPass::Clear( uint16 _flags, uint32 _rgba /*= 0x000000ff*/, float _depth /*= 1.0f*/, uint8 _stencil /*= 0 */ ) const
{
	GFX::SetViewClear(_Handle, _flags, _rgba, _depth, _stencil);
	Touch();
}

void XE::RenderPass::Clear() const
{
	Clear( BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 0x000000FF, 1.0f, 0 );
}

void XE::RenderPass::SetViewProj( const float* v, const float* p )
{
	GFX::SetViewTransform(_Handle, v, p);
}

void XE::RenderPass::Reset()
{
	auto& count = get_counter();
	count = 0;
}

XE::ViewHandle XE::RenderPass::GetPass()
{
	auto counter = get_counter();
	if ( counter == 0 )
	{
		counter = MAX_RENDER_PASSES;
	}
	return counter - 1;
}
