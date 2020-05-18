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

#if PLATFORM_OS & (OS_MAC | OS_IOS)

class RendererContextMetal : public XE::RendererContext
{
public:
	RendererContextMetal();

	~RendererContextMetal() override;

protected:
	void OnStartup() override;

	void OnRender( XE::Frame* val ) override;

	void OnClearup() override;

private:

};

#endif

XE::RendererContext * CreateRendererContextMetal();

END_XE_NAMESPACE

#endif // RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF
