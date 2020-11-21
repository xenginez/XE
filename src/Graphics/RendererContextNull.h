/*!
 * \file	RendererContextNull.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTNULL_H__CD4625E3_4C5B_436B_B74B_455DDCF2DFB1
#define RENDERERCONTEXTNULL_H__CD4625E3_4C5B_436B_B74B_455DDCF2DFB1

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextNull : public XE::RendererContext
{
public:
	RendererContextNull();

	~RendererContextNull();

protected:
	void OnRender( XE::RenderFrame * val ) override;

private:

};

XE_INLINE XE::RendererContext * CreateRendererContextNull()
{
	return new XE::RendererContextNull();
}

END_XE_NAMESPACE

#endif // RENDERERCONTEXTNULL_H__CD4625E3_4C5B_436B_B74B_455DDCF2DFB1
