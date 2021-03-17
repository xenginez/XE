/*!
 * \file	GraphicsContextNull.h
 *
 * \author	ZhengYuanQing
 * \date	2021/03/17
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef GRAPHICSCONTEXTNULL_H__BB63153E_D14E_46FD_9DA0_230336E44B9A
#define GRAPHICSCONTEXTNULL_H__BB63153E_D14E_46FD_9DA0_230336E44B9A

#include "GraphicsContext.h"

BEG_XE_NAMESPACE

class GraphicsContextNull : public XE::GraphicsContext
{
public:
	GraphicsContextNull();

	~GraphicsContextNull();

protected:
	void OnRender( XE::RenderFrame * val ) override;

private:

};

XE_INLINE XE::GraphicsContext * CreateRendererContextNull()
{
	return new XE::GraphicsContextNull();
}

END_XE_NAMESPACE

#endif // GRAPHICSCONTEXTNULL_H__BB63153E_D14E_46FD_9DA0_230336E44B9A
