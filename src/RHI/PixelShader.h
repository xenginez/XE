/*!
 * \file    PixelShader.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __PIXELSHADER_H__EEE5EA5D_A0F5_488A_BFCC_A00123873869
#define __PIXELSHADER_H__EEE5EA5D_A0F5_488A_BFCC_A00123873869

#include "Shader.h"

BEG_XE_NAMESPACE

class RHI_API PixelShader : public Shader
{
	OBJECT(PixelShader, Shader)
	
public:
	PixelShader();
	
	~PixelShader() override;
};

END_XE_NAMESPACE

#endif //__PIXELSHADER_H__EEE5EA5D_A0F5_488A_BFCC_A00123873869
