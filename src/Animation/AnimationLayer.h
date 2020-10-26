/*!
 * \file	AnimationLayer.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/26
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONLAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86
#define ANIMATIONLAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationLayer : XE::Object
{
	OBJECT( AnimationLayer, Object )

public:
	AnimationLayer();

	~AnimationLayer() override;
};

END_XE_NAMESPACE

#endif // ANIMATIONLAYER_H__D1AB3E0B_84D8_4D85_A51F_0C4AB1E28D86
