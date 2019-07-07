/*!
 * \file    FrameBuffer.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __FRAMEBUFFER_H__9497B320_222D_4906_9A8A_18C2B942C654
#define __FRAMEBUFFER_H__9497B320_222D_4906_9A8A_18C2B942C654

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API FrameBuffer
{
public:
	static constexpr XE::uint64 MaxRenderTargetCount = 8;

public:
	FrameBuffer();
	
	~FrameBuffer();

public:
	DepthStencilBufferPtr GetDepthStencil() const;

	void SetDepthStencil( const DepthStencilBufferPtr & val );

	RenderTargetPtr GetColor( XE::uint64 index ) const;

	void SetColor( XE::uint64 index, const RenderTargetPtr & val );

	const Array< RenderTargetPtr > GetColors() const;

private:
	Array< RenderTargetPtr > _Colors;
	DepthStencilBufferPtr _DepthStencil;
};

END_XE_NAMESPACE

#endif //__FRAMEBUFFER_H__9497B320_222D_4906_9A8A_18C2B942C654
