/*!
 * \file	RendererContextOpenGL.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTOPENGL_H__685CAE87_13C6_4256_B001_DA575B559590
#define RENDERERCONTEXTOPENGL_H__685CAE87_13C6_4256_B001_DA575B559590

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextOpenGL : public XE::RendererContext
{
public:
	RendererContextOpenGL();

	~RendererContextOpenGL()() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	void ExecCommandBuffer( XE::Buffer & val ) override;

private:

};

END_XE_NAMESPACE

#endif // RENDERERCONTEXTOPENGL_H__685CAE87_13C6_4256_B001_DA575B559590
