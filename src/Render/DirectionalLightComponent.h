/*!
 * \file   DirectionalLightComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __DIRECTIONALLIGHTCOMPONENT_H__E3898899_E6BA_41DA_8951_B58A11503DDE
#define __DIRECTIONALLIGHTCOMPONENT_H__E3898899_E6BA_41DA_8951_B58A11503DDE

#include "LightComponent.h"

BEG_XE_NAMESPACE

class RENDER_API DirectionalLightComponent : public LightComponent
{
	OBJECT( DirectionalLightComponent, LightComponent )

public:
	DirectionalLightComponent();

	~DirectionalLightComponent();
};

END_XE_NAMESPACE

#endif // __DIRECTIONALLIGHTCOMPONENT_H__E3898899_E6BA_41DA_8951_B58A11503DDE
