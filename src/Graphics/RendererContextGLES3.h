/*!
 * \file	RendererContextGLES3.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTGLES3_H__249AD269_9E1C_4E09_B408_2500405B6C28
#define RENDERERCONTEXTGLES3_H__249AD269_9E1C_4E09_B408_2500405B6C28

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextGLES3 : public XE::RendererContext
{
public:
	RendererContextGLES3();

	~RendererContextGLES3() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	void ExecCommandBuffer( XE::Buffer & val ) override;

private:

};

END_XE_NAMESPACE

#endif // RENDERERCONTEXTGLES3_H__249AD269_9E1C_4E09_B408_2500405B6C28
