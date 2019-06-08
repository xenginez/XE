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

class GRAPHICS_API Renderer : public Object
{
	OBJECT(Renderer, Object)
	
public:
	Renderer();
	
	~Renderer() override;
};

END_XE_NAMESPACE

#endif //__RENDERER_H__E2EF5FD6_6A10_4754_86CC_3EA007879A4F
