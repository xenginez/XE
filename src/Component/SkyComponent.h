/*!
 * \file   SkyComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/16
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __SKYCOMPONENT_H__C9FCFAE6_51A5_4DC0_B377_32C724EFFB8A
#define __SKYCOMPONENT_H__C9FCFAE6_51A5_4DC0_B377_32C724EFFB8A

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API SkyComponent : public XE::SceneComponent
{
	OBJECT( SkyComponent, SceneComponent )

public:
	SkyComponent();

	~SkyComponent();

};

END_XE_NAMESPACE

#endif // __SKYCOMPONENT_H__C9FCFAE6_51A5_4DC0_B377_32C724EFFB8A
