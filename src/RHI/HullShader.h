/*!
 * \file    HullShader.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __HULLSHADER_H__6A2085E6_816B_41FD_83A0_350E1E0F879D
#define __HULLSHADER_H__6A2085E6_816B_41FD_83A0_350E1E0F879D

#include "Shader.h"

BEG_XE_NAMESPACE

class RHI_API HullShader : public Shader
{
	OBJECT(HullShader, Shader)
	
public:
	HullShader();
	
	~HullShader() override;
};

END_XE_NAMESPACE

#endif //__HULLSHADER_H__6A2085E6_816B_41FD_83A0_350E1E0F879D
