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

class RendererContextGLES2 : public XE::RendererContext
{
public:
	RendererContextGLES2();

	~RendererContextGLES2() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	void ExecCommandBuffer( XE::Buffer & val ) override;

private:

};

END_XE_NAMESPACE

#endif // RENDERERCONTEXTGLES2_H__FAC926B4_55D6_4E3B_9061_5CAEA87E68DE
