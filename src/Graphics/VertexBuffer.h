/*!
 * \file   VertexBuffer.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VERTEXBUFFER_H__08D46B55_A124_49C2_BCFB_A933DC1F8D3E
#define __VERTEXBUFFER_H__08D46B55_A124_49C2_BCFB_A933DC1F8D3E

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API VertexBuffer : public XE::Object
{
	OBJECT(VertexBuffer, Object)
	
public:
	VertexBuffer();

	VertexBuffer( const MemoryView * _mem, const VertexLayout& _decl, uint16 _flags = BGFX_BUFFER_NONE );

	~VertexBuffer();

public:
	VertexBufferHandle GetHandle() const;

private:
	VertexBufferHandle _Handle;
};

END_XE_NAMESAPCE

#endif // __VERTEXBUFFER_H__08D46B55_A124_49C2_BCFB_A933DC1F8D3E
