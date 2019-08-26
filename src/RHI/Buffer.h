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
#include "InputLayout.h"

BEG_XE_NAMESPACE

class RHI_API Buffer : public Resource
{
	OBJECT( Buffer, Resource )
	
public:
    Buffer();

    ~Buffer() override;

public:
    XE::uint64 GetSize() const;

public:
	virtual XE::memory_view GetMemoryView() = 0;

private:
	AccessType _Access;
	Array<XE::uint8> _Data;
};

class RHI_API IndexBuffer : public Buffer
{
	OBJECT( IndexBuffer, Buffer )

public:
	IndexBuffer();

	~IndexBuffer() override;

public:
	void Preinitialize( IRenderContextRPtr context ) override;

public:
	TextureFormat GetFormat() const;

private:
	// TextureFormat::R16U | TextureFormat::R32U
	TextureFormat _Format;
};

class RHI_API VertexBuffer : public Buffer
{
	OBJECT( VertexBuffer, Buffer )

public:
	VertexBuffer();

	~VertexBuffer() override;

public:
	void Preinitialize( IRenderContextRPtr context ) override;

public:
	const InputLayoutPtr & GetInputLayout() const;

private:
	InputLayoutPtr _InputLayout;
};

class RHI_API UniformBuffer : public Buffer
{
	OBJECT( UniformBuffer, Buffer )

public:
	UniformBuffer();

	~UniformBuffer() override;

public:
	void Preinitialize( IRenderContextRPtr context ) override;

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

public:
	void Preinitialize( IRenderContextRPtr context ) override;

};

class RHI_API IndirectBuffer : public Buffer
{
	OBJECT( IndirectBuffer, Buffer )

public:
	IndirectBuffer();

	~IndirectBuffer() override;
};

class RHI_API InstanceBuffer : public Buffer
{
	OBJECT( InstanceBuffer, Buffer )

public:
	InstanceBuffer();

	~InstanceBuffer() override;

public:
	void Preinitialize( IRenderContextRPtr context ) override;

};

class RHI_API DynamicIndexBuffer : public IndexBuffer
{
	OBJECT( DynamicIndexBuffer, IndexBuffer )

public:
	DynamicIndexBuffer();

	~DynamicIndexBuffer() override;

public:
	void Preinitialize( IRenderContextRPtr context ) override;

};

class RHI_API DynamicVertexBuffer : public VertexBuffer
{
	OBJECT( DynamicVertexBuffer, VertexBuffer )

public:
	DynamicVertexBuffer();

	~DynamicVertexBuffer() override;

public:
	void Preinitialize( IRenderContextRPtr context ) override;

};

END_XE_NAMESPACE

#endif // __BUFFER_H__D9EB5BDB_5A01_4C5C_8262_008E86007DFD
