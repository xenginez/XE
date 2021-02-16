/*!
 * \file	RendererContextMetal.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF
#define RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF

#include "RendererContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & ( OS_MAC | OS_IOS )

class RendererContextMetal : public XE::RendererContext
{
public:
	RendererContextMetal();

	~RendererContextMetal() override;

protected:
	void OnRender( XE::RenderFrame* val ) override;

private:

};

XE_INLINE XE::RendererContext * CreateRendererContextMetal()
{
	return new XE::RendererContextMetal();
}

#else

XE_INLINE XE::RendererContext * CreateRendererContextMetal()
{
	return nullptr;
}

#endif

END_XE_NAMESPACE

#endif // RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF
