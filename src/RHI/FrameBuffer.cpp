#include "FrameBuffer.h"

#include "Buffer.h"
#include "RenderTarget.h"

XE::FrameBuffer::FrameBuffer()
	:_Colors( MaxRenderTargetCount )
{

}

XE::FrameBuffer::~FrameBuffer()
{

}

XE::DepthStencilBufferPtr XE::FrameBuffer::GetDepthStencil() const
{
	return _DepthStencil;
}

void XE::FrameBuffer::SetDepthStencil( const DepthStencilBufferPtr & val )
{
	_DepthStencil = val;
}

XE::RenderTargetPtr XE::FrameBuffer::GetColor( XE::uint64 index ) const
{
	return _Colors[index];
}

void XE::FrameBuffer::SetColor( XE::uint64 index, const RenderTargetPtr & val )
{
	_Colors[index] = val;
}

const XE::Array< XE::RenderTargetPtr > XE::FrameBuffer::GetColors() const
{
	return _Colors;
}
