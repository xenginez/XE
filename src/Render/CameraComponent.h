/*!
 * \file   CameraComponent.h
 *
 * \author ZhengYuanQing
 * \date   2019/01/15
 * \email  zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CAMERACOMPONENT_H__80053273_5129_4AD0_901F_7E5A0E50DD44
#define __CAMERACOMPONENT_H__80053273_5129_4AD0_901F_7E5A0E50DD44

#include "Type.h"

BEG_XE_NAMESPACE

class RENDER_API CameraComponent : public XE::RenderComponent
{
	OBJECT( CameraComponent, RenderComponent )

public:
	CameraComponent();

	~CameraComponent();

};

END_XE_NAMESPACE

#endif // __CAMERACOMPONENT_H__80053273_5129_4AD0_901F_7E5A0E50DD44
