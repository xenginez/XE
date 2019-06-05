/*!
 * \file    GeometryShader.h
 *
 * \author  ZhengYuanQing
 * \date    2019-05-29
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __GEOMETRYSHADER_H__850C823A_64EB_4174_8631_080FE155711C
#define __GEOMETRYSHADER_H__850C823A_64EB_4174_8631_080FE155711C

#include "Shader.h"

BEG_XE_NAMESPACE

class RHI_API GeometryShader : public Shader
{
	OBJECT(GeometryShader, Shader)
	
public:
	GeometryShader();
	
	~GeometryShader() override;
};

END_XE_NAMESPACE

#endif //__GEOMETRYSHADER_H__850C823A_64EB_4174_8631_080FE155711C
