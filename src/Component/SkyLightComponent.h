/*!
 * \file   SkyLightComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SKYLIGHTCOMPONENT_H__891FBE7F_5571_4ED6_BA66_E3BC97F5E4C8
#define __SKYLIGHTCOMPONENT_H__891FBE7F_5571_4ED6_BA66_E3BC97F5E4C8

#include "LightComponent.h"

BEG_XE_NAMESPACE

class XE_API SkyLightComponent : public XE::LightComponent
{
	OBJECT( SkyLightComponent, LightComponent )

public:
	SkyLightComponent();

	~SkyLightComponent();

private:

};

END_XE_NAMESPACE

#endif // __SKYLIGHTCOMPONENT_H__891FBE7F_5571_4ED6_BA66_E3BC97F5E4C8
