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

class RendererContextGL : public XE::RendererContext
{
public:
	RendererContextGL();

	~RendererContextGL() override;

protected:
	void OnRender( XE::Frame* val ) override;

private:

};

XE::RendererContext * CreateRendererContextGL();

END_XE_NAMESPACE

#endif // RENDERERCONTEXTOPENGL_H__685CAE87_13C6_4256_B001_DA575B559590
