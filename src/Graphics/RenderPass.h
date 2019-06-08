/*!
 * \file    RenderPass.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-31
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERPASS_H__5D759133_C173_4B1A_8C1B_DFCF71280154
#define __RENDERPASS_H__5D759133_C173_4B1A_8C1B_DFCF71280154

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API RenderPass : public Object
{
	OBJECT(RenderPass, Object)
	
public:
	RenderPass();
	
	~RenderPass() override;
};

END_XE_NAMESPACE

#endif //__RENDERPASS_H__5D759133_C173_4B1A_8C1B_DFCF71280154
