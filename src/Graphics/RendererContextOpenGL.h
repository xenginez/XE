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

#if PLATFORM_OS & (OS_WINDOWS | OS_LINUX | OS_MAC)

class RendererContextOpenGL : public XE::RendererContext
{
public:
	RendererContextOpenGL();

	~RendererContextOpenGL() override;

public:
	void Init( const InitInfo & val ) override;

	void Render( XE::Frame * frame ) override;

	void Shutdown() override;

private:

};

#endif

XE::RendererContext * CreateRendererContextOpenGL();

END_XE_NAMESPACE

#endif // RENDERERCONTEXTOPENGL_H__685CAE87_13C6_4256_B001_DA575B559590
