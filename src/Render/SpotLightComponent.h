/*!
 * \file   SpotLightComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SPOTLIGHTCOMPONENT_H__119F0141_C315_40BC_A471_D78436ACAE25
#define __SPOTLIGHTCOMPONENT_H__119F0141_C315_40BC_A471_D78436ACAE25

#include "LightComponent.h"

BEG_XE_NAMESPACE

class RENDER_API SpotLightComponent : public XE::LightComponent
{
	OBJECT( SpotLightComponent, LightComponent )

public:
	SpotLightComponent();

	~SpotLightComponent();

};

END_XE_NAMESPACE

#endif // __SPOTLIGHTCOMPONENT_H__119F0141_C315_40BC_A471_D78436ACAE25
