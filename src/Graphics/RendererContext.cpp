#include "RendererContext.h"

#include "Structs.h"
#include "Encoder.h"

struct XE::RendererContext::Private
{
	std::mutex _FrameMutex;
	XE::Frame * _SubmitFrame;
	XE::Frame * _RenderFrame;
	std::array<XE::Frame, 2> _Frames;

	XE::CapsInfo _Caps;
	XE::InitInfo _Init;

	std::array<View, GFX_MAX_VIEW> Views = {};

	XE::ConcurrentHandleAlloctor<XE::View, GFX_MAX_VIEW> _ViewHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::ShaderHandle, GFX_MAX_SHADERS> _ShaderHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::ProgramHandle, GFX_MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::TextureHandle, GFX_MAX_TEXTURES> _TextureHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::UniformHandle, GFX_MAX_UNIFORMS> _UniformHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::FrameBufferHandle, GFX_MAX_FRAME_BUFFERS> _FrameBufferHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::IndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  _IndexBufferHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::VertexLayoutHandle, GFX_MAX_VERTEX_LAYOUTS> _VertexLayoutHandleAlloc;
	XE::ConcurrentHandleAlloctor<XE::VertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> _VertexBufferHandleAlloc;
};

XE::RendererContext::RendererContext()
	:_p( new Private )
{

}

XE::RendererContext::~RendererContext()
{
	delete _p;
}

void XE::RendererContext::Init( const InitInfo & val )
{
	_p->_Init = val;

	_p->_Caps.TransientIbSize = val.transientIbSize;
	_p->_Caps.TransientVbSize = val.transientVbSize;
	_p->_Caps.VendorId = val.vendorId;
	_p->_Caps.DeviceId = val.deviceId;

	_p->_SubmitFrame = &_p->_Frames[0];
	_p->_RenderFrame = &_p->_Frames[1];
}

void XE::RendererContext::Shutdown()
{

}

void XE::RendererContext::Reset( XE::uint32 width, XE::uint32 height, XE::Flags<XE::ResetFlag> flags, XE::TextureFormat format )
{

}

XE::Encoder * XE::RendererContext::Begin()
{
	thread_local Encoder encoder;

	encoder.Discard();

	encoder.SetFrame( _p->_SubmitFrame );

	return &encoder;
}

void XE::RendererContext::End( XE::Encoder * val )
{
	val->Discard();

	val->SetFrame( nullptr );
}

void XE::RendererContext::Frame( bool capture )
{
	{
		std::unique_lock<std::mutex> lock( _p->_FrameMutex );

		std::swap( _p->_SubmitFrame, _p->_RenderFrame );
	}

	_p->_SubmitFrame->Reset();
}

void XE::RendererContext::Render()
{
	std::unique_lock<std::mutex> lock( _p->_FrameMutex );
	// TODO: render anytings
}

const XE::CapsInfo & XE::RendererContext::GetCaps() const
{
	return _p->_Caps;
}

const XE::InitInfo & XE::RendererContext::GetInitInfo() const
{
	return _p->_Init;
}
