/*!
 * \file    Renderer.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-15
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __RENDERER_H__110C5558_6667_4730_BB09_61799EF40CE0
#define __RENDERER_H__110C5558_6667_4730_BB09_61799EF40CE0

#include "Type.h"

BEG_XE_NAMESPACE

class RHI_API Renderer : public XE::Object
{
	OBJECT(Renderer, Object)
	
public:
	Renderer();
	
	~Renderer() override;
	
};

END_XE_NAMESAPCE

#endif //__RENDERER_H__110C5558_6667_4730_BB09_61799EF40CE0
