/*!
 * \file   LightComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __LIGHTCOMPONENT_H__49C2FA98_A5B0_46A0_BB42_3EE1D45FB662
#define __LIGHTCOMPONENT_H__49C2FA98_A5B0_46A0_BB42_3EE1D45FB662

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API LightComponent : public XE::SceneComponent
{
	OBJECT( LightComponent, SceneComponent )

public:
	LightComponent();

	~LightComponent();

};

END_XE_NAMESPACE

#endif // __LIGHTCOMPONENT_H__49C2FA98_A5B0_46A0_BB42_3EE1D45FB662
