/*!
 * \file	RendererContextMetal.h
 *
 * \author	ZhengYuanQing
 * \date	2020/05/01
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF
#define RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF

#include "RendererContext.h"

BEG_XE_NAMESPACE

class RendererContextMetal : public XE::RendererContext
{
public:
	RendererContextMetal();

	~RendererContextMetal()() override;

public:
	void Init( const InitInfo & val );

	void Shutdown();

public:
	void ExecCommandBuffer( XE::Buffer & val ) override;

private:

};

END_XE_NAMESPACE

#endif // RENDERERCONTEXTMETAL_H__BF952A7B_7F86_459B_BBBC_1D37DED72BDF
