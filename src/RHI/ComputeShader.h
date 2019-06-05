/*!
 * \file    ComputeShader.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __COMPUTESHADER_H__F61441FF_DCA0_4B5D_BA08_6F1BF83CC4FC
#define __COMPUTESHADER_H__F61441FF_DCA0_4B5D_BA08_6F1BF83CC4FC

#include "Shader.h"

BEG_XE_NAMESPACE

class RHI_API ComputeShader : public Shader
{
	OBJECT(ComputeShader, Shader)
	
public:
	ComputeShader();
	
	~ComputeShader() override;
};

END_XE_NAMESPACE

#endif //__COMPUTESHADER_H__F61441FF_DCA0_4B5D_BA08_6F1BF83CC4FC
