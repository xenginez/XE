/*!
 * \file   Buffer.h
 *
 * \author ZhengYuanQing
 * \date   2019/06/03
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __BUFFER_H__D9EB5BDB_5A01_4C5C_8262_008E86007DFD
#define __BUFFER_H__D9EB5BDB_5A01_4C5C_8262_008E86007DFD

#include "Resource.h"

BEG_XE_NAMESPACE

class RHI_API Buffer : public Resource
{
	OBJECT(Buffer, Resource)
	
public:
    Buffer();

    ~Buffer() override;

public:
    memory_view Map(AccessType val);

    void Unmap();

    XE::uint64 GetSize() const;

private:
	AccessType _Access;
	Array<XE::uint8> _Data;
};

class RHI_API VertexBuffer : public Buffer
{
	OBJECT( VertexBuffer, Buffer )

public:
	VertexBuffer();

	~VertexBuffer() override;
};

class RHI_API IndexBuffer : public Buffer
{
	OBJECT( IndexBuffer, Buffer )

public:
	IndexBuffer();

	~IndexBuffer() override;
};

class RHI_API DepthStencilBuffer : public Buffer
{
	OBJECT( DepthStencilBuffer, Buffer )

public:
	DepthStencilBuffer();

	~DepthStencilBuffer() override;
};

class RHI_API DynamicIndexBuffer : public Buffer
{
	OBJECT( DynamicIndexBuffer, Buffer )

public:
	DynamicIndexBuffer();

	~DynamicIndexBuffer() override;
};

class RHI_API DynamicVertexBuffer : public Buffer
{
	OBJECT( DynamicVertexBuffer, Buffer )

public:
	DynamicVertexBuffer();

	~DynamicVertexBuffer() override;
};

class RHI_API UniformBuffer : public Buffer
{
	OBJECT( UniformBuffer, Buffer )

public:
	UniformBuffer();

	~UniformBuffer() override;
};

class RHI_API ComputeBuffer : public Buffer
{
	OBJECT( ComputeBuffer, Buffer )

public:
	ComputeBuffer();

	~ComputeBuffer() override;
};

class RHI_API ConstantBuffer : public Buffer
{
	OBJECT( ConstantBuffer, Buffer )

public:
	ConstantBuffer();

	~ConstantBuffer() override;
};

END_XE_NAMESPACE

#endif // __BUFFER_H__D9EB5BDB_5A01_4C5C_8262_008E86007DFD
