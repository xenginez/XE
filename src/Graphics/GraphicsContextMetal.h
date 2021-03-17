/*!
 * \file	GraphicsContextMetal.h
 *
 * \author	ZhengYuanQing
 * \date	2021/03/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GRAPHICSCONTEXTMETAL_H__DD8FC9A4_C9A6_486F_AF95_DD819DC4D94F
#define GRAPHICSCONTEXTMETAL_H__DD8FC9A4_C9A6_486F_AF95_DD819DC4D94F

#include "GraphicsContext.h"

BEG_XE_NAMESPACE

#if PLATFORM_OS & ( OS_MAC | OS_IOS )

class GraphicsContextMetal : public XE::GraphicsContext
{
public:
	GraphicsContextMetal();

	~GraphicsContextMetal() override;

protected:
	void OnRender( XE::RenderFrame * val ) override;

private:

};

XE_INLINE XE::GraphicsContext * CreateRendererContextMetal()
{
	return new XE::GraphicsContextMetal();
}

#else

XE_INLINE XE::GraphicsContext * CreateRendererContextMetal()
{
	return nullptr;
}

#endif

END_XE_NAMESPACE

#endif // GRAPHICSCONTEXTMETAL_H__DD8FC9A4_C9A6_486F_AF95_DD819DC4D94F
