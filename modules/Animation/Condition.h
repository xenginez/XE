/*!
 * \file	Condition.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef CONDITION_H__24310FDC_0A01_428B_819A_14C3C89FB606
#define CONDITION_H__24310FDC_0A01_428B_819A_14C3C89FB606

#include "Type.h"

BEG_ANIMATION_NAMESPACE

class ANIMATION_API Condition : public XE::Object
{
	OBJECT( Condition, Object )

public:
	Condition();

	~Condition();

public:
	virtual bool Judgment() const = 0;

public:
	Animation::StateHandle GetNextStateHandle() const;

	void SetNextStateHandle( Animation::StateHandle val );

	Animation::ControllerPtr GetAnimationController() const;

	void SetAnimationController( Animation::ControllerPtr val );

private:
	Animation::StateHandle _NextState;
	Animation::ControllerWPtr _AnimationController;
};

END_ANIMATION_NAMESPACE

#endif // CONDITION_H__24310FDC_0A01_428B_819A_14C3C89FB606
