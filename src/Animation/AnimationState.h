/*!
 * \file	AnimationState.h
 *
 * \author	ZhengYuanQing
 * \date	2020/10/19
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
#define ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8

#include "AI/AIState.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationState : public XE::AIState
{
	OBJECT( AnimationState, AIState )

public:
	AnimationState();

	~AnimationState() override;

public:
	XE::AnimationControllerPtr GetAnimationController() const;
};

END_XE_NAMESPACE

#endif // ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
