/*!
 * \file	Backend.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/10
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef BACKEND_H__371ED714_DEA2_44E1_AF63_D12350FBD7B8
#define BACKEND_H__371ED714_DEA2_44E1_AF63_D12350FBD7B8

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Backend
{
public:
	Backend( DevicePtr device );

	~Backend();

public:
	bool ClearDepth( XE::real val );

	bool ClearStencil( XE::uint32 val );

	bool ClearColor( const Color & val );

	bool ClearDepthStencil( XE::real depth, XE::uint32 val );

	bool ClearColorDepthStencil( const Color & color, XE::real depth, XE::uint32 val );

public:
	void SetViewport( ViewportPtr val );

	void SetViewScissor( const Rect & val );

	void SetViewMatrix( const Mat4 & view );

	void SetProjectMatrix( const Mat4 & proj );

public:
	void SetQuery( QueryPtr val );

	void SetFrameBuffer( FrameBufferPtr val );

	void SetIndexBuffer( IndexBufferPtr val );

	void SetVertexBuffer( VertexBufferPtr val );

	void SetRenderTarget( RenderTargetPtr val );

	void SetPipelineState( PipelineStatePtr val );

};

END_XE_NAMESPACE

#endif // BACKEND_H__371ED714_DEA2_44E1_AF63_D12350FBD7B8
