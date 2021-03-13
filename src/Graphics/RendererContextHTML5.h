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

#include "RendererContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & ( OS_HTML5 )

class RendererContextHTML5 : public XE::RendererContext
{
public:
	RendererContextHTML5();

	~RendererContextHTML5();

protected:
	void OnRender( XE::RenderFrame * val ) override;

private:

};

XE_INLINE XE::RendererContext * CreateRendererContextHTML5()
{
	return new XE::RendererContextHTML5();
}

#else

XE_INLINE XE::RendererContext * CreateRendererContextHTML5()
{
	return nullptr;
}

#endif

END_XE_NAMESPACE

#endif // RENDERERCONTEXTHTML5_H__CF58E5EB_A7B3_4844_86FB_C2D702B30E93
