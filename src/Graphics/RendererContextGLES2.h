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

#include "RendererContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & (OS_ANDROID | OS_IOS)

class RendererContextGLES2 : public XE::RendererContext
{
public:
	RendererContextGLES2();

	~RendererContextGLES2() override;

public:
	void Init( const InitInfo & val ) override;

	void Render( XE::Frame * frame ) override;

	void Shutdown() override;

private:

};

#endif

XE::RendererContext * CreateRendererContextGLES2();

END_XE_NAMESPACE

#endif // RENDERERCONTEXTGLES2_H__FAC926B4_55D6_4E3B_9061_5CAEA87E68DE
