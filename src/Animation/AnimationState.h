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

#include "AI/State.h"

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationState : public XE::State
{
	OBJECT( AnimationState, State )

public:
	void AddAnimationEvent( XE::float32 time, const XE::EventPtr & val );

	void RemoveAnimationEvent( const XE::ConditionPtr & val );

	const XE::Array<XE::float32, XE::EventPtr> & GetAnimationEvents() const;

private:
	XE::Array<XE::float32, XE::EventPtr> _Events;
};

END_XE_NAMESPACE

#endif // ANIMATIONSTATE_H__C48F9826_7C1E_44A2_B4A1_1F579B74E9A8
