/*!
 * \file   WaterComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/20
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __WATERCOMPONENT_H__4BAF82FE_DE90_4387_B56D_E930B48E4C42
#define __WATERCOMPONENT_H__4BAF82FE_DE90_4387_B56D_E930B48E4C42

#include "Scene/SceneComponent.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API WaterComponent : public XE::SceneComponent
{
	OBJECT( WaterComponent, SceneComponent )

public:
	WaterComponent();

	~WaterComponent();
};

END_XE_NAMESPACE

#endif // __WATERCOMPONENT_H__4BAF82FE_DE90_4387_B56D_E930B48E4C42
