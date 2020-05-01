/*!
 * \file	RendererContextDirectX11.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTDIRECTX11_H__0BC8ECE7_63A4_479F_9079_39840765BAB4
#define RENDERERCONTEXTDIRECTX11_H__0BC8ECE7_63A4_479F_9079_39840765BAB4

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextDirectX11 : public XE::RendererContext
{
public:
	RendererContextDirectX11();

	~RendererContextDirectX11() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	void ExecCommandBuffer( XE::Buffer & val ) override;

private:

};

END_XE_NAMESPACE

#endif // RENDERERCONTEXTDIRECTX11_H__0BC8ECE7_63A4_479F_9079_39840765BAB4
