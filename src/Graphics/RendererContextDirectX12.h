/*!
 * \file	RendererContextDirectX12.h
 *
 * \author	ZhengYuanQing
 * \date	2020/04/07
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTDIRECTX12_H__F749BA89_7295_4D11_8DD4_664658D8DE3B
#define RENDERERCONTEXTDIRECTX12_H__F749BA89_7295_4D11_8DD4_664658D8DE3B

#include "RendererContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & (OS_WINDOWS | OS_XBOX)

class RendererContextDirectX12 : public XE::RendererContext
{
public:
	RendererContextDirectX12();

	~RendererContextDirectX12() override;

protected:
	void OnRender( XE::RenderFrame* val ) override;

private:

};

XE_INLINE XE::RendererContext * CreateRendererContextDirectX12()
{
	return new XE::RendererContextDirectX12();
}

#else

XE_INLINE XE::RendererContext * CreateRendererContextDirectX12()
{
	return nullptr;
}

#endif

END_XE_NAMESPACE

#endif // RENDERERCONTEXTDIRECTX12_H__F749BA89_7295_4D11_8DD4_664658D8DE3B
