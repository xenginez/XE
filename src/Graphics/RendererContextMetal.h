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

#if PLATFORM_OS & (OS_MAC | OS_IOS)

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextMetal : public XE::RendererContext
{
public:
	RendererContextMetal();

	~RendererContextMetal() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	XE::Caps GetCaps() override;

	XE::RendererContextType GetType() override;

private:

};

END_XE_NAMESPACE

XE::RendererContext * CreateRendererContextMetal()
{
	return new XE::RendererContextMetal();
}
#else
XE::RendererContext * CreateRendererContextMetal()
{
	return nullptr;
}
#endif

#endif // RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF
