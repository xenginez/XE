/*!
 * \file    VertexShader.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __VERTEXSHADER_H__6001907B_05D1_48E2_844F_5EAE824104B1
#define __VERTEXSHADER_H__6001907B_05D1_48E2_844F_5EAE824104B1

#include "Shader.h"

BEG_XE_NAMESPACE

class RHI_API VertexShader : public Shader
{
	OBJECT(VertexShader, Shader)
	
public:
	VertexShader();
	
	~VertexShader() override;
};

END_XE_NAMESPACE

#endif //__VERTEXSHADER_H__6001907B_05D1_48E2_844F_5EAE824104B1
