/*!
 * \file   PointLightComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __POINTLIGHTCOMPONENT_H__8246E697_336E_46BE_89CB_48E7219C78D2
#define __POINTLIGHTCOMPONENT_H__8246E697_336E_46BE_89CB_48E7219C78D2

#include "LightComponent.h"

BEG_XE_NAMESPACE

class RENDER_API PointLightComponent : public XE::LightComponent
{
	OBJECT( PointLightComponent, LightComponent )

public:
	PointLightComponent();

	~PointLightComponent();
};

END_XE_NAMESAPCE

#endif // __POINTLIGHTCOMPONENT_H__8246E697_336E_46BE_89CB_48E7219C78D2
