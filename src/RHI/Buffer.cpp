#include "Buffer.h"

#include "RenderContext.h"

USING_XE

BEG_META(Buffer)
END_META()

XE::Buffer::Buffer()
{

}

XE::Buffer::~Buffer()
{

}

XE::uint64 XE::Buffer::GetSize() const
{
	return _Data.size();
}

XE::memory_view XE::Buffer::GetMemoryView()
{
	return XE::memory_view();
}

BEG_META( IndexBuffer )
END_META()

XE::IndexBuffer::IndexBuffer()
{

}

XE::IndexBuffer::~IndexBuffer()
{
	GetRenderContext()->DestoryIndexBuffer( GetHandle() );
}

TextureFormat XE::IndexBuffer::GetFormat() const
{
	return _Format;
}

void XE::IndexBuffer::Preinitialize( RenderContextRPtr context )
{
	Super::Preinitialize( context );

	SetHandle( context->CreateIndexBuffer( XE_THIS( IndexBuffer ) ) );
}

BEG_META( VertexBuffer )
END_META()

XE::VertexBuffer::VertexBuffer()
{

}

XE::VertexBuffer::~VertexBuffer()
{
	GetRenderContext()->DestoryVertexBuffer( GetHandle() );
}

const XE::InputLayoutPtr & XE::VertexBuffer::GetInputLayout() const
{
	return _InputLayout;
}

void XE::VertexBuffer::Preinitialize( RenderContextRPtr context )
{
	Super::Preinitialize( context );

	SetHandle( context->CreateVertexBuffer( XE_THIS( VertexBuffer ) ) );
}

BEG_META( UniformBuffer )
END_META()

XE::UniformBuffer::UniformBuffer()
{

}

XE::UniformBuffer::~UniformBuffer()
{
	GetRenderContext()->DestoryUniformBuffer( GetHandle() );
}

void XE::UniformBuffer::Preinitialize( RenderContextRPtr context )
{
	Super::Preinitialize( context );

	SetHandle( context->CreateUniformBuffer( XE_THIS( UniformBuffer ) ) );
}

BEG_META( ComputeBuffer )
END_META()

XE::ComputeBuffer::ComputeBuffer()
{

}

XE::ComputeBuffer::~ComputeBuffer()
{
	GetRenderContext()->DestoryComputeBuffer( GetHandle() );
}

BEG_META( ConstantBuffer )
END_META()

XE::ConstantBuffer::ConstantBuffer()
{

}

XE::ConstantBuffer::~ConstantBuffer()
{
	GetRenderContext()->DestoryConstantBuffer( GetHandle() );
}

void XE::ConstantBuffer::Preinitialize( RenderContextRPtr context )
{
	Super::Preinitialize( context );

	SetHandle( context->CreateConstantBuffer( XE_THIS( ConstantBuffer ) ) );
}

BEG_META( IndirectBuffer )
END_META()

XE::IndirectBuffer::IndirectBuffer()
{

}

XE::IndirectBuffer::~IndirectBuffer()
{
	GetRenderContext()->DestoryIndirectBuffer( GetHandle() );
}

BEG_META( InstanceBuffer )
END_META()

XE::InstanceBuffer::InstanceBuffer()
{

}

XE::InstanceBuffer::~InstanceBuffer()
{
	GetRenderContext()->DestoryInstanceBuffer( GetHandle() );
}

void XE::InstanceBuffer::Preinitialize( RenderContextRPtr context )
{
	Super::Preinitialize( context );

	SetHandle( context->CreateInstanceBuffer( XE_THIS( InstanceBuffer ) ) );
}

BEG_META( DynamicIndexBuffer )
END_META()

XE::DynamicIndexBuffer::DynamicIndexBuffer()
{

}

XE::DynamicIndexBuffer::~DynamicIndexBuffer()
{
	GetRenderContext()->DestoryDynamicIndexBuffer( GetHandle() );
}

void XE::DynamicIndexBuffer::Preinitialize( RenderContextRPtr context )
{
	Super::Preinitialize( context );

	SetHandle( context->CreateDynamicIndexBuffer( XE_THIS( DynamicIndexBuffer ) ) );
}

BEG_META( DynamicVertexBuffer )
END_META()

XE::DynamicVertexBuffer::DynamicVertexBuffer()
{

}

XE::DynamicVertexBuffer::~DynamicVertexBuffer()
{
	GetRenderContext()->DestoryDynamicVertexBuffer( GetHandle() );
}

void XE::DynamicVertexBuffer::Preinitialize( RenderContextRPtr context )
{
	Super::Preinitialize( context );

	SetHandle( context->CreateDynamicVertexBuffer( XE_THIS( DynamicVertexBuffer ) ) );
}
