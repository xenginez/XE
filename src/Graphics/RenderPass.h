/*!
 * \file   RenderPass.h
 *
 * \author ZhengYuanQing
 * \date   2019/03/10
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERPASS_H__172B1F4D_7256_4A78_8C5D_2D3280DF17BE
#define __RENDERPASS_H__172B1F4D_7256_4A78_8C5D_2D3280DF17BE

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderPass : public std::enable_shared_from_this<RenderPass>
{
public:
	RenderPass( const String& n );

	~RenderPass();

public:
	ViewHandle GetHandle() const;

public:
	void Bind( FrameBufferPtr fb = nullptr ) const;

	void Touch() const;

	void Clear( uint16 _flags, uint32 _rgba = 0x000000ff, float _depth = 1.0f, uint8 _stencil = 0 ) const;

	void Clear() const;

	void SetViewProj( const float* v, const float* p );

	static void Reset();

	static ViewHandle GetPass();

private:
	ViewHandle _Handle;
};

END_XE_NAMESAPCE

#endif // __RENDERPASS_H__172B1F4D_7256_4A78_8C5D_2D3280DF17BE
