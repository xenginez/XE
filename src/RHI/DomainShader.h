/*!
 * \file    DomainShader.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __DOMAINSHADER_H__6E5B6A58_6C7B_4426_B847_B538127B3A21
#define __DOMAINSHADER_H__6E5B6A58_6C7B_4426_B847_B538127B3A21

#include "Shader.h"

BEG_XE_NAMESPACE

class RHI_API DomainShader : public Shader
{
	OBJECT(DomainShader, Shader)
	
public:
	DomainShader();
	
	~DomainShader() override;
};

END_XE_NAMESPACE

#endif //__DOMAINSHADER_H__6E5B6A58_6C7B_4426_B847_B538127B3A21
