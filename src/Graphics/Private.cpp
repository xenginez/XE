#include "Private.h"

XE::uint32 XE::GfxRefCount::Inc()
{
	return ++_Count;
}

XE::uint32 XE::GfxRefCount::Dec()
{
	return --_Count;
}

void XE::GfxRefCount::Reset()
{
	_Count = 0;
}

void XE::RenderBind::Reset()
{
	for( auto & it : Binds )
	{
		it.Type = BindType::NONE;
		it.Mip = 0;
		it.Handle = std::numeric_limits<XE::uint64>::max();
		it.Access = XE::AccessType::COUNT;
		it.SamplerFlags = 0;
		it.Format = XE::TextureFormat::RGBA8;
	}
}

void XE::RenderDraw::Reset()
{
	IsDynamicIndices = false;
	Rgba = XE::Color::Black;
	StartMatrix = 0;
	NumMatrices = 0;
	InstanceDataOffset = 0;
	NumInstances = 0;
	StartIndirect = 0;
	NumIndirect = 0;
	Scissor = XE::Rectf::Zero;
	SubmitFlags = 0;
	StreamMask = 0;
	IsDynamicInstanceDataBuffer = false;
	Program = XE::ProgramHandle::Invalid;
	InstanceDataBuffer = XE::VertexBufferHandle::Invalid;
	IndirectBuffer = XE::IndirectBufferHandle::Invalid;
	OcclusionQuery = XE::OcclusionQueryHandle::Invalid;
	StateFlags = XE::StateFlag::NONE;
	FrontStencilFlags = XE::StencilFlag::NONE;
	BackStencilFlags = XE::StencilFlag::NONE;
}

void XE::RenderBlit::Reset()
{
	SrcX = 0;
	SrcY = 0;
	SrcZ = 0;
	DstX = 0;
	DstY = 0;
	DstZ = 0;
	Width = 0;
	Height = 0;
	Depth = 0;
	SrcMip = 0;
	DstMip = 0;
	Handle = XE::ViewHandle::Invalid;
	Src = XE::TextureHandle::Invalid;
	Dst = XE::TextureHandle::Invalid;
}

void XE::RenderCompute::Reset()
{
	StartMatrix = 0;
	NumMatrices = 0;

	StartIndirect = 0;
	NumIndirect = 0;

	NumX = 0;
	NumY = 0;
	NumZ = 0;

	Program = XE::ProgramHandle::Invalid;
	IndirectBuffer = XE::IndirectBufferHandle::Invalid;
}

void XE::RenderFrame::Reset()
{
	UniformsSize = 0;
	TransformsSize = 0;
	RenderItemSize = 0;
	RenderOcclusionSize = 0;

	PrevCmd.Reset();
	PostCmd.Reset();
	TransientBuffers.Reset();
}
