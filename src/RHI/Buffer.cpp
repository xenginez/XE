#include "Buffer.h"

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

BEG_META( IndexBuffer )
END_META()

XE::IndexBuffer::IndexBuffer()
{

}

XE::IndexBuffer::~IndexBuffer()
{

}

BEG_META( VertexBuffer )
END_META()

XE::VertexBuffer::VertexBuffer()
{

}

XE::VertexBuffer::~VertexBuffer()
{

}

BEG_META( UniformBuffer )
END_META()

XE::UniformBuffer::UniformBuffer()
{

}

XE::UniformBuffer::~UniformBuffer()
{

}

BEG_META( ComputeBuffer )
END_META()

XE::ComputeBuffer::ComputeBuffer()
{

}

XE::ComputeBuffer::~ComputeBuffer()
{

}

BEG_META( ConstantBuffer )
END_META()

XE::ConstantBuffer::ConstantBuffer()
{

}

XE::ConstantBuffer::~ConstantBuffer()
{

}

BEG_META( IndirectBuffer )
END_META()

XE::IndirectBuffer::IndirectBuffer()
{

}

XE::IndirectBuffer::~IndirectBuffer()
{

}

BEG_META( InstanceBuffer )
END_META()

XE::InstanceBuffer::InstanceBuffer()
{

}

XE::InstanceBuffer::~InstanceBuffer()
{

}

BEG_META( DepthStencilBuffer )
END_META()

XE::DepthStencilBuffer::DepthStencilBuffer()
{

}

XE::DepthStencilBuffer::~DepthStencilBuffer()
{

}

BEG_META( DynamicIndexBuffer )
END_META()

XE::DynamicIndexBuffer::DynamicIndexBuffer()
{

}

XE::DynamicIndexBuffer::~DynamicIndexBuffer()
{

}

BEG_META( DynamicVertexBuffer )
END_META()

XE::DynamicVertexBuffer::DynamicVertexBuffer()
{

}

XE::DynamicVertexBuffer::~DynamicVertexBuffer()
{

}
