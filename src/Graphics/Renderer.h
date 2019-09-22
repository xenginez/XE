/*!
 * \file    Renderer.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERER_H__E2EF5FD6_6A10_4754_86CC_3EA007879A4F
#define __RENDERER_H__E2EF5FD6_6A10_4754_86CC_3EA007879A4F

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Renderer : public XE::Object
{
	OBJECT( Renderer, Object )
	
public:
	Renderer();
	
	virtual ~Renderer();

public:
	void Startup();

	void Render();

	void Clearup();

protected:
	virtual void OnStartup() = 0;

	virtual void OnRender() = 0;

	virtual void OnClearup() = 0;
};

END_XE_NAMESPACE

#endif //__RENDERER_H__E2EF5FD6_6A10_4754_86CC_3EA007879A4F
