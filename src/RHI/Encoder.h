/*!
 * \file	Encoder.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ENCODER_H__22D33A1F_0748_4F3D_B760_3D566BB9D2BD
#define ENCODER_H__22D33A1F_0748_4F3D_B760_3D566BB9D2BD

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Encoder
{
public:
	Encoder( ContextPtr val );

	~Encoder();

	/*
public:
	void SetQuery(); // ( OcclusionQueryHandle _handle, bool _visible );

	void SetStencil(); // ( uint32_t _fstencil, uint32_t _bstencil = BGFX_STENCIL_NONE );

	void SetScissor(); // ( uint16_t _x, uint16_t _y, uint16_t _width, uint16_t _height );

	void SetUniform(); // ( UniformHandle _handle, const void * _value, uint16_t _num = 1 );

	void SetSampler(); // ( uint8_t _stage, UniformHandle _sampler, TextureHandle _handle, uint32_t _flags = UINT32_MAX );

	void SetIndexBuffer(); // ( IndexBufferHandle _handle );

	void SetIndexBuffer(); // ( IndexBufferHandle _handle, uint32_t _firstIndex, uint32_t _numIndices );

	void SetVertexBuffer(); // ( VertexBufferHandle _handle );

	void SetVertexBuffer(); // ( VertexBufferHandle _handle, uint32_t _startVertex, uint32_t _numVertices );

	void SetPipelineState(); // ( uint64_t _state, uint32_t _rgba = 0 );

	void SetInstanceBuffer(); // ( VertexBufferHandle _handle, uint32_t _start, uint32_t _num );

public:
	void SetTransform(); // ( const void * _mtx, uint16_t _num = 1 );

	void SetViewTransform(); // ( const void * _mtx, uint16_t _num = 1 );

public:
	void SetBuffer(); // ( uint8_t _stage, IndirectBufferHandle _handle, Access::Enum _access );

	void SetTexture(); // ( uint8_t _stage, TextureHandle _handle, uint8_t _mip, Access::Enum _access, TextureFormat::Enum _format = TextureFormat::Count );

public:
	void Touch(); // ( ViewId _id );

public:
	void Submit(); // ( ViewId _id, ProgramHandle _program, uint32_t _depth = 0, bool _preserveState = false );

	void Submit(); // ( ViewId _id, ProgramHandle _program, OcclusionQueryHandle _occlusionQuery, uint32_t _depth = 0, bool _preserveState = false );

	void Submit(); // ( ViewId _id, ProgramHandle _program, IndirectBufferHandle _indirectHandle, uint16_t _start = 0, uint16_t _num = 1, uint32_t _depth = 0, bool _preserveState = false );

public:
	void Dispatch(); // ( ViewId _id, ProgramHandle _handle, uint32_t _numX = 1, uint32_t _numY = 1, uint32_t _numZ = 1 );

	void Dispatch(); // ( ViewId _id, ProgramHandle _handle, IndirectBufferHandle _indirectHandle, uint16_t _start = 0, uint16_t _num = 1 );

public:
	void Discard(); // ();

public:
	void Blit(); // ( ViewId _id, TextureHandle _dst, uint16_t _dstX, uint16_t _dstY, TextureHandle _src, uint16_t _srcX = 0, uint16_t _srcY = 0, uint16_t _width = UINT16_MAX, uint16_t _height = UINT16_MAX );

	void Blit(); // ( ViewId _id, TextureHandle _dst, uint8_t _dstMip, uint16_t _dstX, uint16_t _dstY, uint16_t _dstZ, TextureHandle _src, uint8_t _srcMip = 0, uint16_t _srcX = 0, uint16_t _srcY = 0, uint16_t _srcZ = 0, uint16_t _width = UINT16_MAX, uint16_t _height = UINT16_MAX, uint16_t _depth = UINT16_MAX );
*/
};

END_XE_NAMESPACE

#endif // ENCODER_H__22D33A1F_0748_4F3D_B760_3D566BB9D2BD
