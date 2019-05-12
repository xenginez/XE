#include "VertexBuffer.h"

#include "GFX.h"

USING_XE

BEGIN_META(VertexBuffer)
END_META()

XE::VertexBuffer::VertexBuffer()
{

}

XE::VertexBuffer::VertexBuffer( const MemoryView * _mem, const VertexLayout& _decl, uint16 _flags /*= BGFX_BUFFER_NONE */ )
{
	_Handle = GFX::CreateVertexBuffer(_mem, _decl, _flags);
}

XE::VertexBuffer::~VertexBuffer()
{
	if ( _Handle.idx != UINT16_MAX )
	{
		GFX::Destroy(_Handle);
	}
}

XE::VertexBufferHandle XE::VertexBuffer::GetHandle() const
{
	return _Handle;
}
