/*!
 * \file	RendererContextHTML5.h
 *
 * \author	ZhengYuanQing
 * \date	2021/03/13
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTHTML5_H__CF58E5EB_A7B3_4844_86FB_C2D702B30E93
#define RENDERERCONTEXTHTML5_H__CF58E5EB_A7B3_4844_86FB_C2D702B30E93

#include "GraphicsContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & ( OS_HTML5 )

class GraphicsContextHTML5 : public XE::GraphicsContext
{
public:
	GraphicsContextHTML5();

	~GraphicsContextHTML5();

protected:
	void OnRender( XE::RenderFrame * val ) override;

private:

};

XE_INLINE XE::GraphicsContext * CreateRendererContextHTML5()
{
	return new XE::GraphicsContextHTML5();
}

#else

XE_INLINE XE::GraphicsContext * CreateRendererContextHTML5()
{
	return nullptr;
}

#endif

END_XE_NAMESPACE

#endif // RENDERERCONTEXTHTML5_H__CF58E5EB_A7B3_4844_86FB_C2D702B30E93
