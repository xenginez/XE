/*!
 * \file	AnimationState.h
 *
 * \author	ZhengYuanQing
 * \date	2019/09/16
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ANIMATIONSTATE_H__DE89A48E_E19F_4BE9_9D74_144BFB0D3029
#define ANIMATIONSTATE_H__DE89A48E_E19F_4BE9_9D74_144BFB0D3029

#include "Type.h"

BEG_XE_NAMESPACE

class ANIMATION_API AnimationState : public XE::Object
{
	OBJECT( AnimationState, Object )

public:
	AnimationState();

	~AnimationState() override;

public:
	virtual void Startup();

	virtual void Entry();

	virtual void Update( XE::float32 val );

	virtual void Exit();

	virtual void Clearup();

public:
	const Array<XE::uint32> & GetTransitions() const;

	void SetTransitions( const Array<XE::uint32> & val );

	AnimationControllerPtr GetAnimationController() const;

	void SetAnimationController( const AnimationControllerPtr & val );

private:
	Array<XE::uint32> _Transitions;
	AnimationControllerWPtr _Controller;
};

class ANIMATION_API AnimationStateEntry : public AnimationState
{
	OBJECT( AnimationStateEntry, AnimationState )
	
public:
	AnimationStateEntry();

	~AnimationStateEntry() override;

};

class ANIMATION_API AnimationStateAny : public AnimationState
{
	OBJECT( AnimationStateAny, AnimationState )

public:
	AnimationStateAny();

	~AnimationStateAny() override;

};

END_XE_NAMESPACE

#endif // ANIMATIONSTATE_H__DE89A48E_E19F_4BE9_9D74_144BFB0D3029
