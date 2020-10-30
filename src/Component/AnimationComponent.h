/*!
 * \file	AnimationComponent.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/29
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCOMPONENT_H__39371F27_40F4_4BB0_BFF1_453387B3F8A2
#define ANIMATIONCOMPONENT_H__39371F27_40F4_4BB0_BFF1_453387B3F8A2

#include "Scene/BehaviorComponent.h"
#include "Animation/AnimationController.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationComponent : public XE::BehaviorComponent
{
	OBJECT( AnimationComponent, BehaviorComponent )

public:
	AnimationComponent();

	~AnimationComponent() override;

protected:
	void OnStartup() override;

	void OnUpdate( XE::float32 dt ) override;

	void OnClearup() override;

protected:
	virtual void OnAnimationIK();

private:
	XE::AnimationControllerPtr _AnimationController;
};

END_XE_NAMESPACE

#endif // ANIMATIONCOMPONENT_H__39371F27_40F4_4BB0_BFF1_453387B3F8A2
