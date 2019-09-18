/*!
 * \file	AnimationIKConstraint.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/18
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONIKCONSTRAINT_H__401C278D_845B_4C72_9781_39DF13767EE0
#define ANIMATIONIKCONSTRAINT_H__401C278D_845B_4C72_9781_39DF13767EE0

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationIKConstraint : public XE::Object
{
	OBJECT( AnimationIKConstraint, Object )

public:
	AnimationIKConstraint();

	~AnimationIKConstraint();
};

END_XE_NAMESPACE

#endif // ANIMATIONIKCONSTRAINT_H__401C278D_845B_4C72_9781_39DF13767EE0
