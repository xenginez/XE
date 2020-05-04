/*!
 * \file	RendererContextGLES2.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTGLES2_H__FAC926B4_55D6_4E3B_9061_5CAEA87E68DE
#define RENDERERCONTEXTGLES2_H__FAC926B4_55D6_4E3B_9061_5CAEA87E68DE

#if PLATFORM_OS & (OS_ANDROID | OS_IOS)

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextGLES2 : public XE::RendererContext
{
public:
	RendererContextGLES2();

	~RendererContextGLES2() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	XE::Caps GetCaps() override;

	XE::ContextType GetContextType() override;

public:
	void ExecCommandBuffer( XE::Buffer & val ) override;

private:

};

END_XE_NAMESPACE

XE::RendererContext * CreateRendererContextGLES2()
{
	return new XE::RendererContextGLES2();
}
#else
XE::RendererContext * CreateRendererContextGLES2()
{
	return nullptr;
}
#endif

#endif // RENDERERCONTEXTGLES2_H__FAC926B4_55D6_4E3B_9061_5CAEA87E68DE
