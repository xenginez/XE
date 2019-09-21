/*!
 * \file	AnimationTransition.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONTRANSITION_H__081FE5B3_8914_4C3A_9E61_C5C52E6885EA
#define ANIMATIONTRANSITION_H__081FE5B3_8914_4C3A_9E61_C5C52E6885EA

#include "Type.h"

BEG_XE_NAMESPACE

class XE_API AnimationTransition : public XE::Object
{
	OBJECT( AnimationTransition, Object )

public:
	AnimationTransition();

	~AnimationTransition() override;

public:
	bool Condition();

public:
	XE::uint32 GetNextState() const;

	void SetNextState( XE::uint32 val );

	AnimationControllerPtr GetAnimationController() const;

	void SetAnimationController( const AnimationControllerPtr & val );

	const Array<AnimationConditionPtr> & GetAnimationConditions() const;

	void SetAnimationConditions( const Array<AnimationConditionPtr> & val );

private:
	XE::uint32 _State;
	AnimationControllerWPtr _Controller;
	Array<AnimationConditionPtr> _Conditions;
};

END_XE_NAMESPACE

#endif // ANIMATIONTRANSITION_H__081FE5B3_8914_4C3A_9E61_C5C52E6885EA
