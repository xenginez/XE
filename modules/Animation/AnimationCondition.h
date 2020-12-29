/*!
 * \file	AnimationCondition.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/27
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONCONDITION_H__24310FDC_0A01_428B_819A_14C3C89FB606
#define ANIMATIONCONDITION_H__24310FDC_0A01_428B_819A_14C3C89FB606

#include "Utils/Object.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationCondition : public XE::Object
{
	OBJECT( AnimationCondition, Object )

public:
	AnimationCondition();

	~AnimationCondition();

public:
	virtual bool Judgment() const = 0;

public:
	XE::AnimationStateHandle GetNextStateHandle() const;

	void SetNextStateHandle( XE::AnimationStateHandle val );

	XE::AnimationControllerPtr GetAnimationController() const;

	void SetAnimationController( AnimationControllerPtr val );

private:
	XE::AnimationStateHandle _NextState;
	XE::AnimationControllerWPtr _AnimationController;
};

END_XE_NAMESPACE

#endif // ANIMATIONCONDITION_H__24310FDC_0A01_428B_819A_14C3C89FB606
