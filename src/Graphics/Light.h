/*!
 * \file	Light.h
 *
 * \author	ZhengYuanQing
 * \date	2019/07/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef LIGHT_H__DEEF3151_DC77_48A1_99DC_F515876C7CCF
#define LIGHT_H__DEEF3151_DC77_48A1_99DC_F515876C7CCF

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API Light : public XE::Object
{
	OBJECT( Light, Object )

public:
	Light();

	~Light() override;

};

class XE_API SpotLight : public Light
{
	OBJECT( SpotLight, Light )

public:
	SpotLight();

	~SpotLight() override;
};

class XE_API AreaLight : public Light
{
	OBJECT( AreaLight, Light )

public:
	AreaLight();

	~AreaLight() override;

};

class XE_API PointLight : public Light
{
	OBJECT( PointLight, Light )

public:
	PointLight();

	~PointLight() override;
};

class XE_API DirectionalLight : public Light
{
	OBJECT( DirectionalLight, Light )

public:
	DirectionalLight();

	~DirectionalLight() override;
};

END_XE_NAMESPACE

#endif // LIGHT_H__DEEF3151_DC77_48A1_99DC_F515876C7CCF
