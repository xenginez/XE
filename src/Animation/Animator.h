/*!
 * \file	AnimationControllor.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/15
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCONTROLLOR_H__D062F72F_C871_4E50_8716_7A512A2D6EBC
#define ANIMATIONCONTROLLOR_H__D062F72F_C871_4E50_8716_7A512A2D6EBC

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API Animator : public XE::Object
{
	OBJECT( Animator, Object )

public:
	Animator();

	~Animator() override;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONTROLLOR_H__D062F72F_C871_4E50_8716_7A512A2D6EBC
