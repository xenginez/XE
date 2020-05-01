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

class RendererContextDirectX12 : public XE::RendererContext
{
public:
	RendererContextDirectX12();

	~RendererContextDirectX12() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	void ExecCommandBuffer( XE::Buffer & val ) override;

private:

};

END_XE_NAMESPACE

#endif // RENDERERCONTEXTDIRECTX12_H__F749BA89_7295_4D11_8DD4_664658D8DE3B
