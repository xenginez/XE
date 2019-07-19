/*!
 * \file	DrawCall.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef DRAWCALL_H__1D065B57_081D_456D_878F_B1CAAB041C89
#define DRAWCALL_H__1D065B57_081D_456D_878F_B1CAAB041C89

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API DrawCall
{
public:
	DrawCall() = default;

	~DrawCall() = default;

public:
	void SetRenderGroup( RenderGroup val );

public:
	void SetQuery( const QueryPtr & val );

	void SetScissor( const Rect & val );

	void SetSampler( const SamplerPtr & val );

	void SetUniform( const UniformBufferPtr & val );

	void SetIndexBuffer( const IndexBufferPtr & val );

	void SetVertexBuffer( const VertexBufferPtr & val );

	void SetIndirectBuffer( const IndirectBufferPtr & val );

	void SetInstanceBuffer( const InstanceBufferPtr & val );

public:
	void SetPipelineState( const PipelineStatePtr & val );

public:
	void SetTransform( const Mat4 & val );

public:
	void SetTexture( const TexturePtr & val );

public:
	void Submit( bool reserveState );

public:
	void Dispatch( XE::uint32 x, XE::uint32 y, XE::uint32 z );

};

END_XE_NAMESPACE

#endif // DRAWCALL_H__1D065B57_081D_456D_878F_B1CAAB041C89
