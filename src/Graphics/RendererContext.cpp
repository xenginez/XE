#include "RendererContext.h"

#include "Structs.h"

struct XE::RendererContext::Private
{
	XE::Frame * _SubmitFrame;
	XE::Frame * _BatchFrame;
	XE::Frame * _RenderFrame;
	std::array<XE::Frame, 3> _Frames;

	XE::FreeHandleAlloctor<XE::View, MAX_VIEW> _ViewHandleAlloc;
	XE::FreeHandleAlloctor<XE::ShaderHandle, MAX_SHADERS> _ShaderHandleAlloc;
	XE::FreeHandleAlloctor<XE::ProgramHandle, MAX_PROGRAMS> _ProgramHandleAlloc;
	XE::FreeHandleAlloctor<XE::TextureHandle, MAX_TEXTURES> _TextureHandleAlloc;
	XE::FreeHandleAlloctor<XE::UniformHandle, MAX_UNIFORMS> _UniformHandleAlloc;
	XE::FreeHandleAlloctor<XE::FrameBufferHandle, MAX_FRAME_BUFFERS> _FrameBufferHandleAlloc;
	XE::FreeHandleAlloctor<XE::IndexBufferHandle, MAX_INDEX_BUFFERS>  _IndexBufferHandleAlloc;
	XE::FreeHandleAlloctor<XE::VertexLayoutHandle, MAX_VERTEX_LAYOUTS> _VertexLayoutHandleAlloc;
	XE::FreeHandleAlloctor<XE::VertexBufferHandle, MAX_VERTEX_BUFFERS> _VertexBufferHandleAlloc;
};

XE::RendererContext::RendererContext()
	:_p( new Private )
{

}

XE::RendererContext::~RendererContext()
{
	delete _p;
}
