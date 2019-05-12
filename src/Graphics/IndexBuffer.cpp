#include "IndexBuffer.h"

#include "GFX.h"

USING_XE

BEGIN_META(IndexBuffer)
END_META()

XE::IndexBuffer::IndexBuffer()
{

}

XE::IndexBuffer::IndexBuffer( const MemoryView * _mem, std::uint16_t _flags /*= BGFX_BUFFER_NONE */ )
{
	_Handle = GFX::CreateIndexBuffer(_mem, _flags);
}

XE::IndexBuffer::~IndexBuffer()
{
	if (_Handle.idx != UINT16_MAX)
	{
		GFX::Destroy(_Handle);
	}
}

XE::IndexBufferHandle XE::IndexBuffer::GetHandle() const
{
	return _Handle;
}
