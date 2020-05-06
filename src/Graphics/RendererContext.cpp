#include "RendererContext.h"

#include "Structs.h"
#include "Encoder.h"

struct XE::RendererContext::Private
{
	XE::Frame * _SubmitFrame;
	XE::Frame * _BatchFrame;
	XE::Frame * _RenderFrame;
	std::array<XE::Frame, 3> _Frames;

	XE::Caps _Caps;

	XE::Array<Encoder *> _Encoders;
	std::array<View, GFX_MAX_VIEW> Views = {};

	XE::FreeHandleAlloctor<XE::View, GFX_MAX_VIEW> _ViewHandleAlloc;
	XE::FreeHandleAlloctor<XE::ShaderHandle, GFX_MAX_SHADERS> _ShaderHandleAlloc;
	XE::FreeHandleAlloctor<XE::ProgramHandle, GFX_MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::FreeHandleAlloctor<XE::TextureHandle, GFX_MAX_TEXTURES> _TextureHandleAlloc;
	XE::FreeHandleAlloctor<XE::UniformHandle, GFX_MAX_UNIFORMS> _UniformHandleAlloc;
	XE::FreeHandleAlloctor<XE::FrameBufferHandle, GFX_MAX_FRAME_BUFFERS> _FrameBufferHandleAlloc;
	XE::FreeHandleAlloctor<XE::IndexBufferHandle, GFX_MAX_INDEX_BUFFERS>  _IndexBufferHandleAlloc;
	XE::FreeHandleAlloctor<XE::VertexLayoutHandle, GFX_MAX_VERTEX_LAYOUTS> _VertexLayoutHandleAlloc;
	XE::FreeHandleAlloctor<XE::VertexBufferHandle, GFX_MAX_VERTEX_BUFFERS> _VertexBufferHandleAlloc;
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
	_p->_Caps.maxEncoders = val.maxEncoders != 0 ? val.maxEncoders : std::thread::hardware_concurrency();
	_p->_Caps.transientIbSize = val.transientIbSize;
	_p->_Caps.transientVbSize = val.transientVbSize;
	_p->_Caps.vendorId = val.vendorId;
	_p->_Caps.deviceId = val.deviceId;


}
