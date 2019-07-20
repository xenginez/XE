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
	void SetLayer( XE::uint32 val );

public:
	void SetQuery( const QueryPtr & val );

	void SetSampler( const SamplerPtr & val );

	void SetUniform( const UniformBufferPtr & val );

	void SetIndexBuffer( const IndexBufferPtr & val );

	void SetVertexBuffer( const VertexBufferPtr & val );

	void SetIndirectBuffer( const IndirectBufferPtr & val );

	void SetInstanceBuffer( const InstanceBufferPtr & val );

public:
	void SetTransform( const Mat4 & val );

	void SetBlendFactor( BlendFactor val );

	void SetTexture( const TexturePtr & val );

	void SetPipelineState( const PipelineStatePtr & val );

private:
	XE::uint32 _Layer;
	Rect _Scissor;
	Mat4 _Transform;

	QueryPtr _Query;
	SamplerPtr _Sampler;
	UniformBufferPtr _Uniform;
	IndexBufferPtr _IndexBuffer;
	VertexBufferPtr _VertexBuffer;
	IndirectBufferPtr _IndirectBuffer;
	InstanceBufferPtr _InstanceBuffer;
	PipelineStatePtr _PipelineState;
	TexturePtr _Texture;
};

END_XE_NAMESPACE

#endif // DRAWCALL_H__1D065B57_081D_456D_878F_B1CAAB041C89
