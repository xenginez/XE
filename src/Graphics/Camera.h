/*!
 * \file    Camera.h
 *
 * \author  ZhengYuanQing
 * \date    2019-06-05
 * \email   zhengyuanqing.95@gmail.com
 *
 */
#ifndef __CAMERA_H__AE26235A_1006_46EE_AF0E_2DD0626772A0
#define __CAMERA_H__AE26235A_1006_46EE_AF0E_2DD0626772A0

#include "Type.h"

BEG_XE_NAMESPACE

class GRAPHICS_API Camera : public Object
{
	OBJECT(Camera, Object)
	
public:
	Camera();
	
	~Camera() override;

};

END_XE_NAMESPACE

#endif //__CAMERA_H__AE26235A_1006_46EE_AF0E_2DD0626772A0
